#include <snapshot/http-queries/SpaceTrackClient.hpp>

#include <chrono>
#include <iostream>
#include <set>
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

nlohmann::json SpaceTrackClient::query(
    const std::string& username,
    const std::string& password,
    const Controller& controller,
    const Action& action,
    const SpaceTrackClient::RequestClass& requestClass,
    const std::vector<std::pair<std::string, std::string>> predicates
)
{
    cpr::Url queryUrl = build_query_url(controller, action, requestClass, predicates);
    return query_impl(username, password, queryUrl);
}

nlohmann::json SpaceTrackClient::retrieve_all(const std::string& username, const std::string& password)
{
    cpr::Url queryUrl =
        "https://www.space-track.org/"
        "basicspacedata/query/class/gp/decay_date/null-val/epoch/%3Enow-30/orderby/norad_cat_id/format/json";
    return query_impl(username, password, queryUrl);
}

std::string SpaceTrackClient::controller_to_string(const Controller& controller) const
{
    switch (controller) {
        case (Controller::BASIC_SPACE_DATA): {
            return "basicspacedata";
        }
        case (Controller::PUBLIC_FILES): {
            return "publicfiles";
        }
    }
    throw std::runtime_error("Unregonized contoller requested.");
}

std::string SpaceTrackClient::action_to_string(const Action& action) const
{
    switch (action) {
        case (Action::QUERY): {
            return "query";
        }
        case (Action::MODEL_DEF): {
            return "modeldef";
        }
    }
    throw std::runtime_error("Unregonized action requested.");
}

std::string SpaceTrackClient::class_to_string(const RequestClass& requestClass) const
{
    return std::visit([&](const auto& x) -> std::string { return class_to_string(x); }, requestClass);
}

std::string SpaceTrackClient::class_to_string(const SpaceDataClass& requestClass) const
{
    switch (requestClass) {
        case (SpaceDataClass::ANNOUNCEMENT): {
            return "announcement";
        }
        case (SpaceDataClass::BOX_SCORE): {
            return "boxscore";
            break;
        }
        case (SpaceDataClass::CDM_PUBLIC): {
            return "cdm_public";
        }
        case (SpaceDataClass::DECAY): {
            return "decay";
        }
        case (SpaceDataClass::GP): {
            return "gp";
        }
        case (SpaceDataClass::GP_HISTORY): {
            return "gp_history";
        }
        case (SpaceDataClass::LAUNCH_SITE): {
            return "launch_site";
        }
        case (SpaceDataClass::SATCAT): {
            return "satcat";
        }
        case (SpaceDataClass::SATCAT_CHANGE): {
            return "satcat_change";
        }
        case (SpaceDataClass::SATCAT_DEBUT): {
            return "satcat_debut";
        }
        case (SpaceDataClass::TIP): {
            return "tip";
        }
    }
    throw std::runtime_error("Unexpected request class for Space Data controller.");
}

std::string SpaceTrackClient::class_to_string(const PublicFilesClass& requestClass) const
{
    switch (requestClass) {
        case (PublicFilesClass::DIRS): {
            return "dirs";
        }
        case (PublicFilesClass::DOWNLOAD): {
            return "download";
        }
        case (PublicFilesClass::FILES): {
            return "files";
        }
        case (PublicFilesClass::LOAD_PUBLIC_DATA): {
            return "loadpublicdata";
        }
    }
    throw std::runtime_error("Unexpected request class for Public Files controller.");
}

cpr::Url SpaceTrackClient::build_query_url(
    const Controller& controller,
    const Action& action,
    const SpaceTrackClient::RequestClass& requestClass,
    const std::vector<std::pair<std::string, std::string>> predicates
) const
{
    cpr::Url url = _base + "/" + controller_to_string(controller) + "/" + action_to_string(action) + "/class/" +
                   class_to_string(requestClass);
    for (const auto& [predicate, value] : predicates) {
        url += "/" + predicate + "/" + value;
    }
    return url;
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
    if (queryHistory.contains(username)) {
        const Time oneMinuteAgo = now - std::chrono::minutes(1);
        const Time oneHourAgo   = now - std::chrono::hours(1);

        std::size_t idx         = 0;
        std::size_t nLastHour   = 0;
        std::size_t nLastMinute = 0;
        std::set<std::size_t> oldQueries;
        for (const auto& timestamp : queryHistory[username]) {
            // Stream date string into time point
            std::istringstream timestampStream{ timestamp.template get<std::string>() };
            Time queryTime;
            timestampStream >> date::parse(TIMESTAMP_FORMAT, queryTime);

            if (queryTime < oneHourAgo) { oldQueries.insert(idx); }
            else {
                ++nLastHour;
                if (queryTime >= oneMinuteAgo) { ++nLastMinute; }
            }
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

nlohmann::json SpaceTrackClient::query_impl(const std::string& username, const std::string& password, cpr::Url queryUrl)
{
    // Login
    if (!valid_cookies()) { login(username, password); }

    // Make sure we're not violating the user-agreement
    check_query_history(username);

    // Query
    cpr::Response r = cpr::Get(queryUrl, _loginCookies);

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

    return response;
}

} // namespace snapshot