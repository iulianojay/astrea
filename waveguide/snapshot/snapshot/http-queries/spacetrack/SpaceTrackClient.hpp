/**
 * @file SpaceTrackClient.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief SpaceTrackClient class for interacting with the SpaceTrack API
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <filesystem>
#include <variant>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <astro/time/Date.hpp>

#include <snapshot/types/typedefs.hpp>

namespace waveguide {
namespace snapshot {

/**
 * @brief SpaceTrackClient class for interacting with the SpaceTrack API.
 *
 * This class provides methods to login, query data, and retrieve information from the SpaceTrack API.
 * It supports various controllers and actions to access different types of space data.
 * @note WARNING: Do NOT use this for automated scripts. I have NOT setup a check to make sure we're
 * within the automated script limits and you could get your SpaceTrack account banned.
 */
class SpaceTrackClient {
  public:
    /**
     * @brief Enumeration for the different controllers available in SpaceTrack.
     *
     * This enumeration defines the various controllers that can be used to access different types of data
     * from the SpaceTrack API.
     */
    enum class Controller : EnumType {
        BASIC_SPACE_DATA, //<! Basic Space Data
        // EXPANDED_SPACE_DATA, //<! USSPACECOM SSA Sharing Agreements
        // FILE_SHARE,          //<! Permission Controlled
        // COMBINED_OPS_DATA,   //<! Permission Controlled
        PUBLIC_FILES //<! Public Files
    };

    /**
     * @brief Enumeration for the different actions that can be performed in SpaceTrack.
     *
     * This enumeration defines the various actions that can be performed when querying data from the SpaceTrack API.
     */
    enum class Action : EnumType {
        QUERY,     //<! Query action
        MODEL_DEF, //<! Model definition action
    };

    /**
     * @brief Enumeration for the different classes of space data available in SpaceTrack.
     *
     * This enumeration defines the various classes of space data that can be queried from the SpaceTrack API.
     */
    enum class SpaceDataClass : EnumType {
        ANNOUNCEMENT,  //<! Announcement data
        BOX_SCORE,     //<! Box score data
        CDM_PUBLIC,    //<! Conjunction Data Message (CDM) public data
        DECAY,         //<! Decay data
        GP,            //<! General Perturbation (GP) data
        GP_HISTORY,    //<! General Perturbation (GP) history data
        LAUNCH_SITE,   //<! Launch site data
        SATCAT,        //<! Satellite Catalog (SATCAT) data
        SATCAT_CHANGE, //<! Satellite Catalog change data
        SATCAT_DEBUT,  //<! Satellite Catalog debut data
        TIP            //<! Tracking and Information Processing (TIP) data
    };

    /**
     * @brief Enumeration for the different classes of public files available in SpaceTrack.
     *
     * This enumeration defines the various classes of public files that can be accessed from the SpaceTrack API.
     */
    enum class PublicFilesClass : EnumType {
        DIRS,            //<! Directories of public files
        DOWNLOAD,        //<! Download public files
        FILES,           //<! List of public files
        LOAD_PUBLIC_DATA //<! Load public data files
    };

    /**
     * @brief Type alias for the request class, which can be either SpaceDataClass or PublicFilesClass.
     *
     * This type alias allows for a unified way to handle different types of requests in the SpaceTrackClient.
     */
    using RequestClass = std::variant<SpaceDataClass, PublicFilesClass>;

    /**
     * @brief Default constructor for SpaceTrackClient.
     *
     * Initializes the SpaceTrackClient instance.
     */
    SpaceTrackClient() = default;

    /**
     * @brief Default destructor for SpaceTrackClient.
     *
     * Cleans up the SpaceTrackClient instance.
     */
    ~SpaceTrackClient() = default;

    /**
     * @brief Logs in to the SpaceTrack API.
     *
     * This function authenticates the user with the SpaceTrack API using the provided
     * username and password.
     *
     * @param username The username for the SpaceTrack account.
     * @param password The password for the SpaceTrack account.
     */
    void login(const std::string& username, const std::string& password);

    /**
     * @brief Queries the SpaceTrack API for data.
     *
     * This function sends a query to the SpaceTrack API using the specified parameters
     * and returns the response as a JSON object.
     *
     * @param username The username for the SpaceTrack account.
     * @param password The password for the SpaceTrack account.
     * @param controller The controller to use for the query.
     * @param action The action to perform (e.g., QUERY, MODEL_DEF).
     * @param requestClass The class of data to request (e.g., GP, SATCAT).
     * @param predicates Optional predicates to filter the query results.
     * @return A JSON object containing the query results.
     */
    nlohmann::json query(
        const std::string& username,
        const std::string& password,
        const Controller& controller                                      = Controller::BASIC_SPACE_DATA,
        const Action& action                                              = Action::QUERY,
        const RequestClass& requestClass                                  = SpaceDataClass::GP,
        const std::vector<std::pair<std::string, std::string>> predicates = {}
    );

    /**
     * @brief Retrieves all data from the SpaceTrack API.
     *
     * This function retrieves all data available in the SpaceTrack API for the specified user.
     *
     * @param username The username for the SpaceTrack account.
     * @param password The password for the SpaceTrack account.
     * @return A JSON object containing all available data.
     */
    nlohmann::json retrieve_all(const std::string& username, const std::string& password);

  private:
    const cpr::Url _base = "https://www.space-track.org"; //<! Base URL for the SpaceTrack API

    // Login
    const cpr::Url _loginUrl = _base + "/ajaxauth/login"; //<! URL for the login endpoint
    cpr::Cookies _loginCookies;                           //<! Cookies for the login session

    /**
     * @brief Checks if the login cookies are valid and have not expired.
     *
     * @return true if the cookies are valid, false otherwise.
     */
    bool valid_cookies() const;

    /**
     * @brief Checks if the user has exceeded the query limits.
     *
     * @param username The username for the SpaceTrack account.
     * @return true if the user has exceeded the limits, false otherwise.
     */
    void check_query_history(const std::string& username) const;

    /**
     * @brief Converts a Controller enum value to its string representation.
     *
     * @param controller The Controller enum value to convert.
     * @return The string representation of the Controller.
     */
    std::string controller_to_string(const Controller& controller) const;

    /**
     * @brief Converts an Action enum value to its string representation.
     *
     * @param action The Action enum value to convert.
     * @return The string representation of the Action.
     */
    std::string action_to_string(const Action& action) const;

    /**
     * @brief Converts a RequestClass variant to its string representation.
     *
     * @param requestClass The RequestClass variant to convert.
     * @return The string representation of the RequestClass.
     */
    std::string class_to_string(const RequestClass& requestClass) const;

    /**
     * @brief Converts a SpaceDataClass enum value to its string representation.
     *
     * @param requestClass The SpaceDataClass enum value to convert.
     * @return The string representation of the SpaceDataClass.
     */
    std::string class_to_string(const SpaceDataClass& requestClass) const;

    /**
     * @brief Converts a PublicFilesClass enum value to its string representation.
     *
     * @param requestClass The PublicFilesClass enum value to convert.
     * @return The string representation of the PublicFilesClass.
     */
    std::string class_to_string(const PublicFilesClass& requestClass) const;

    /**
     * @brief Builds the query URL for the SpaceTrack API.
     *
     * This function constructs the URL for querying the SpaceTrack API based on the provided parameters.
     *
     * @param controller The controller to use for the query.
     * @param action The action to perform (e.g., QUERY, MODEL_DEF).
     * @param requestClass The class of data to request (e.g., GP, SATCAT).
     * @param predicates Optional predicates to filter the query results.
     * @return A cpr::Url object representing the constructed query URL.
     */
    cpr::Url build_query_url(
        const Controller& controller,
        const Action& action,
        const RequestClass& requestClass,
        const std::vector<std::pair<std::string, std::string>> predicates
    ) const;

    /**
     * @brief Performs the actual query to the SpaceTrack API.
     *
     * This function sends a request to the SpaceTrack API using the provided username, password, and query URL,
     * and returns the response as a JSON object.
     *
     * @param username The username for the SpaceTrack account.
     * @param password The password for the SpaceTrack account.
     * @param queryUrl The URL to query.
     * @return A JSON object containing the query results.
     */
    nlohmann::json query_impl(const std::string& username, const std::string& password, cpr::Url queryUrl);
};

} // namespace snapshot
} // namespace waveguide