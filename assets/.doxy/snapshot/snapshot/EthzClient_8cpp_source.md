

# File EthzClient.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**snapshot**](dir_ad01b7a66bf2103e1e551598d7ba094a.md) **>** [**snapshot**](dir_d7d302d432d8a6ab561803ec6eec1eed.md) **>** [**http-queries**](dir_e3fe50636e6aa25df3bf26a0e7917672.md) **>** [**ethz**](dir_31d12700b25e15af9e5493b70ce27e08.md) **>** [**EthzClient.cpp**](EthzClient_8cpp.md)

[Go to the documentation of this file](EthzClient_8cpp.md)


```C++
/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */



#include <snapshot/http-queries/ethz/EthzClient.hpp>

#include <iostream>
#include <stdexcept>

#include <utilities/string_util.hpp>

namespace astrea {
namespace snapshot {

nlohmann::json EthzClient::query(const astro::Date& startDate, const astro::Date& endDate, const std::string& name, const bool& includeFrequencyData)
{
    return query_impl(startDate, endDate, name, 0, includeFrequencyData);
}
nlohmann::json EthzClient::query(const astro::Date& startDate, const astro::Date& endDate, const unsigned& noradId, const bool& includeFrequencyData)
{
    return query_impl(startDate, endDate, "", noradId, includeFrequencyData);
}

nlohmann::json
    EthzClient::query_impl(const astro::Date& startDate, const astro::Date& endDate, const std::string& name, const unsigned& noradId, const bool& includeFrequencyData)
{
    /*
        https://satdb.ethz.ch/api-documentation/:
    */

    // Ensure reasonable search terms
    if (name.empty() && noradId == 0) {
        throw std::runtime_error("Either a serach name or a NORAD ID must be specified.");
    }

    if (startDate < _minStartDate) {
        throw std::runtime_error(
            "This database started continuously collecting and archiving data on March 10th, "
            "2023. All queries must be after that."
        );
    }

    if (endDate > astro::Date::now()) {
        throw std::runtime_error(
            "This database started continuously collecting and archiving data on March 10th, "
            "2023. All queries must be after that."
        );
    }

    // Parse dates
    const std::string startStr = std::format("{:%Y%m%dT%H%M}", startDate.sys());
    const std::string endStr   = std::format("{:%Y%m%dT%H%M}", endDate.sys());

    // Replace whitespace in name with "+"
    const std::string searchName = utilities::replace_all(name, " ", "+");

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


void EthzClient::clean_result(nlohmann::json& result)
{
    std::string misformattedEntry = result["norad_str"];

    std::stringstream ss(misformattedEntry);
    std::string line;
    if (!misformattedEntry.empty()) {
        size_t iLine = 0;
        while (std::getline(ss, line, '\n')) {
            if (iLine == 0) { result["norad_str"] = utilities::trim(line); }
            else {
                result["tle"][iLine - 1] = utilities::trim(line);
            }
            ++iLine;
        }
    }
}

} // namespace snapshot
} // namespace astrea
```


