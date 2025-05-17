#include <snapshot/http-queries/EthzQuerier.hpp>

#include <iostream>
#include <stdexcept>

#include <snapshot/utilities/string_util.hpp>

namespace snapshot {

nlohmann::json EthzQuerier::query(const astro::Date& startDate, const astro::Date& endDate, const std::string& name, const bool& includeFrequencyData)
{
    return query_impl(startDate, endDate, name, 0, includeFrequencyData);
}
nlohmann::json EthzQuerier::query(const astro::Date& startDate, const astro::Date& endDate, const unsigned& noradId, const bool& includeFrequencyData)
{
    return query_impl(startDate, endDate, "", noradId, includeFrequencyData);
}

nlohmann::json
    EthzQuerier::query_impl(const astro::Date& startDate, const astro::Date& endDate, const std::string& name, const unsigned& noradId, const bool& includeFrequencyData)
{
    /*
        https://satdb.ethz.ch/api-documentation/:
    */

    // Ensure reasonable search terms
    if (name.empty() && noradId == 0) {
        throw std::runtime_error("Either a serach name or a NORAD ID must be specified.");
    }

    if (startDate < _minStartDate) {
        throw std::runtime_error("This database started continuously collecting and archiving data on March 10th, "
                                 "2023. All queries must be after that.");
    }

    if (endDate > astro::Date::now()) {
        throw std::runtime_error("This database started continuously collecting and archiving data on March 10th, "
                                 "2023. All queries must be after that.");
    }

    // Parse dates
    const std::string startStr = std::format("{:%Y%m%dT%H%M}", startDate.sys());
    const std::string endStr   = std::format("{:%Y%m%dT%H%M}", endDate.sys());

    // Replace whitespace in name with "+"
    const std::string searchName = replace_all(name, " ", "+");

    // Query online db
    // cpr::Parameters params = {
    //     { "start-datetime", start },                                          // start date YYYYMMDDThhmm
    //     { "end-datetime", end },                                              // end date
    //     { "norad-id", std::to_string(noradId) },                              // exact norad id
    //     { "without-frequency-data", includeFrequencyData ? "False" : "True" } // include frequency data
    //                                                                           // { "frequency-list", "[10.7-12.7,13.85-14.5]" },
    // };
    cpr::Parameters params = {
        { "start-datetime", startStr },                                       // start date YYYYMMDDThhmm
        { "end-datetime", endStr },                                           // end date
        { "object-name", searchName },                                        // search name
        { "without-frequency-data", includeFrequencyData ? "False" : "True" } // include frequency data
                                                                              // { "frequency-list", "[10.7-12.7,13.85-14.5]" },
    };
    cpr::Response r = cpr::Get(_satDataUrl, _auth, params);

    // Extract response into json
    nlohmann::json response = nlohmann::json::parse(r.text);

    if (response["results"].size() == 0) {
        std::ostringstream errorStream;
        errorStream << "Query failed. No data matching search was found.\n\n";
        errorStream << "Query Data: \n";
        errorStream << "    Status Code: " << std::to_string(r.status_code) << "\n";
        errorStream << "    Text: " << r.text << "\n";
        errorStream << "    Url: " << r.url << "\n";
        errorStream << "    Error: " << r.error.message << "\n";
        errorStream << "    Status Line: " << r.status_line << "\n";
        errorStream << "    Reason: " << r.reason << "\n";
        // errorStream << "    Raw Header: \n\n" << r.raw_header;

        throw std::runtime_error(errorStream.str());
    }

    // Clean up weird TLE formatting
    for (auto& result : response["results"]) {
        clean_result(result);
    }

    return response;
}


void EthzQuerier::clean_result(nlohmann::json& result)
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