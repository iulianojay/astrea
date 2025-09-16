/**
 * @file EthzClient.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief EthzClient class for interacting with the ETHZ satellite database API
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <string>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <astro/time/Date.hpp>

namespace astrea {
namespace snapshot {

/**
 * @brief EthzClient class for interacting with the ETHZ satellite database API.
 *
 * This class provides methods to query satellite data from the ETHZ satellite database.
 * It supports querying by date range and satellite name or NORAD ID, and can include frequency data if requested.
 */
class EthzClient {
  public:
    /**
     * @brief Default constructor for EthzClient.
     *
     * Initializes the EthzClient with a minimum start date of 2023-03-10 00:00:00.0.
     */
    EthzClient() :
        _minStartDate("2023-03-10 00:00:00.0") {};

    /**
     * @brief Default destructor for EthzClient.
     */
    ~EthzClient() = default;

    /**
     * @brief Queries the ETHZ satellite database for satellite data.
     *
     * This function sends a request to the ETHZ satellite database API to retrieve satellite data
     * within the specified date range and optionally includes frequency data.
     *
     * @param startDate The start date for the query.
     * @param endDate The end date for the query.
     * @param name Optional name of the satellite to filter results.
     * @param noradId Optional NORAD ID of the satellite to filter results.
     * @param includeFrequencyData Whether to include frequency data in the results (default is false).
     * @return A JSON object containing the query results.
     */
    nlohmann::json query(const astro::Date& startDate, const astro::Date& endDate, const std::string& name, const bool& includeFrequencyData = false);

    /**
     * @brief Queries the ETHZ satellite database for satellite data by NORAD ID.
     *
     * This function sends a request to the ETHZ satellite database API to retrieve satellite data
     * for a specific NORAD ID within the specified date range and optionally includes frequency data.
     *
     * @param startDate The start date for the query.
     * @param endDate The end date for the query.
     * @param noradId The NORAD ID of the satellite to filter results.
     * @param includeFrequencyData Whether to include frequency data in the results (default is false).
     * @return A JSON object containing the query results.
     */
    nlohmann::json query(const astro::Date& startDate, const astro::Date& endDate, const unsigned& noradId, const bool& includeFrequencyData = false);

  private:
    const cpr::Url _base               = "https://satdb.ethz.ch/api"; //!< Base URL for the ETHZ satellite database API
    const cpr::Url _satDataUrl         = _base + "/satellitedata";    //!< URL for satellite data endpoint
    const cpr::Url _satUrl             = _base + "/satellite";        //!< URL for satellite endpoint
    const cpr::Url _frequencySourceUrl = _base + "/frequencysource";  //!< URL for frequency source endpoint
    const cpr::Url _frequencyUrl       = _base + "/frequency";        //!< URL for frequency endpoint
    const cpr::Authentication _auth    = { "user", "pass", cpr::AuthMode::BASIC }; //!< Authentication for the ETHZ API

    const astro::Date _minStartDate; //!< Minimum start date for queries (2023-03-10 00:00:00.0)

    /**
     * @brief Performs the actual query to the ETHZ satellite database API.
     *
     * This function sends a request to the ETHZ satellite database API using the provided parameters
     * and returns the response as a JSON object.
     *
     * @param startDate The start date for the query.
     * @param endDate The end date for the query.
     * @param name Optional name of the satellite to filter results.
     * @param noradId Optional NORAD ID of the satellite to filter results.
     * @param includeFrequencyData Whether to include frequency data in the results (default is false).
     * @return A JSON object containing the query results.
     */
    nlohmann::json query_impl(
        const astro::Date& startDate,
        const astro::Date& endDate,
        const std::string& name          = "",
        const unsigned& noradId          = 0,
        const bool& includeFrequencyData = false
    );

    /**
     * @brief Cleans the result JSON object by removing unnecessary fields.
     *
     * This function processes the JSON result to remove fields that are not needed for further processing.
     *
     * @param result The JSON object to clean.
     */
    void clean_result(nlohmann::json& result);
};

} // namespace snapshot
} // namespace astrea