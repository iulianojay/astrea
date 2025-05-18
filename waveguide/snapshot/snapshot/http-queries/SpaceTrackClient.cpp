#include <snapshot/http-queries/SpaceTrackClient.hpp>

#include <chrono>
#include <iostream>
#include <stdexcept>

#include <date/date.h> // NOTE: This is standard in std::chrono as of GNU 13.2
#include <nlohmann/json.hpp>

#include <snapshot/utilities/string_util.hpp>

namespace snapshot {

void SpaceTrackClient::login(const std::string& username, const std::string& password)
{
    cpr::Payload loginParams    = { { "identity", username }, { "password", password } };
    cpr::Response loginResponse = cpr::Post(_loginUrl, loginParams);
    _loginCookies               = loginResponse.cookies;
}

nlohmann::json SpaceTrackClient::query(const std::string& username, const std::string& password)
{
    return query_impl(username, password);
}

void SpaceTrackClient::check_query_history(const std::string& username) const
{
    // Query limits - https://www.space-track.org/documentation#api
    static const std::size_t MAX_QUERIES_PER_MINUTE = 30;
    static const std::size_t MAX_QUERIES_PER_HOUR   = 300;
    static const std::filesystem::path QUERY_HISTORY_FILE =
        "./waveguide/snapshot/snapshot/data/spacetrack.query-history.json";
    static const std::string TIMESTAMP_FORMAT = "%Y-%m-%d %H:%M:%S";

    // Ingest query history
    nlohmann::json queryHistory;
    if (std::filesystem::exists(QUERY_HISTORY_FILE)) {
        std::ifstream queryHistroyStream(QUERY_HISTORY_FILE);
        queryHistory = nlohmann::json::parse(queryHistroyStream);
    }

    // Now
    using Time     = std::chrono::sys_time<std::chrono::milliseconds>;
    const Time now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());

    // Check query frequency
    std::vector<std::size_t> oldQueries;
    if (queryHistory.contains(username)) {
        const Time oneMinuteAgo = now - std::chrono::minutes(1);
        const Time oneHourAgo   = now - std::chrono::hours(1);

        std::size_t idx         = 0;
        std::size_t nLastHour   = 0;
        std::size_t nLastMinute = 0;
        for (const auto& timestamp : queryHistory[username]) {
            // Stream date string into time point
            std::istringstream timestampStream{ timestamp.template get<std::string>() };
            Time queryTime;
            timestampStream >> date::parse(TIMESTAMP_FORMAT, queryTime);

            if (queryTime < oneHourAgo) { oldQueries.push_back(idx); }
            if (queryTime >= oneHourAgo) { ++nLastHour; }
            if (queryTime >= oneMinuteAgo) { ++nLastMinute; }
            ++idx;
        }

        // Clean old queries
        for (auto it = oldQueries.rbegin(); it != oldQueries.rend(); ++it) {
            queryHistory[username].erase(*it);
        }

        // Throw
        if (nLastHour >= MAX_QUERIES_PER_HOUR) {
            throw std::runtime_error("Error: Maximum number of hourly queries reached (300). Exiting so SpaceTrack "
                                     "doesn't ban you.");
        }
        if (nLastMinute >= MAX_QUERIES_PER_MINUTE) {
            throw std::runtime_error("Error: Maximum number of queries per minute reached (30). Exiting so SpaceTrack "
                                     "doesn't ban you.");
        }
    }

    // If it didn't throw, log the query time
    std::ostringstream outStream;
    outStream << now;
    queryHistory[username].push_back(outStream.str());

    // Save
    std::ofstream outFileStream(QUERY_HISTORY_FILE);
    outFileStream << std::setw(4) << queryHistory << std::endl;
}

bool SpaceTrackClient::valid_cookies() const
{
    if (_loginCookies.empty()) { return false; }
    for (const auto& cookie : _loginCookies) {
        auto now = std::chrono::system_clock::now();
        if (now >= cookie.GetExpires()) { return false; }
    }
    return true;
}

nlohmann::json SpaceTrackClient::query_impl(const std::string& username, const std::string& password)
{
    // Login
    if (!valid_cookies()) { login(username, password); }

    // Make sure we're not violating the user-agreement
    check_query_history(username);

    // Query
    const cpr::Url url = std::string("https://www.space-track.org/basicspacedata/query/class/decay/DECAY_EPOCH/"
                                     "2012-07-02--2012-07-09/orderby/NORAD_CAT_ID,PRECEDENCE/format/json");

    cpr::Response r = cpr::Get(url, _loginCookies);

    // Extract response into json
    nlohmann::json response = nlohmann::json::parse(r.text);

    if (response.size() == 0) {
        std::ostringstream errorStream;
        errorStream << "Query failed. No data matching search was found.\n\n";
        errorStream << "Query Data: \n";
        errorStream << "    Status Code: " << std::to_string(r.status_code) << "\n";
        errorStream << "    Text: " << r.text << "\n";
        errorStream << "    Url: " << r.url << "\n";
        errorStream << "    Error: " << r.error.message << "\n";
        errorStream << "    Status Line: " << r.status_line << "\n";
        errorStream << "    Reason: " << r.reason << "\n";
        errorStream << "    Raw Header: \n\n" << r.raw_header;

        std::cout << errorStream.str();
    }

    std::cout << std::setw(4) << response << std::endl;

    // // Clean up weird TLE formatting
    // for (auto& result : response["results"]) {
    //     clean_result(result);
    // }

    return response;
}


void SpaceTrackClient::clean_result(nlohmann::json& result)
{
    std::string misformattedEntry = result["norad_str"];

    std::stringstream ss(misformattedEntry);
    std::string line;
    if (!misformattedEntry.empty()) {
        size_t iLine = 0;
        while (std::getline(ss, line, '\n')) {
            if (iLine == 0) { result["norad_str"] = trim(line); }
            else {
                result["tle"][iLine - 1] = trim(line);
            }
            ++iLine;
        }
    }
}

} // namespace snapshot