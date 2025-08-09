/**
 * @file SpaceTrackGP.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief SpaceTrackGP data structure for the snapshot module
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <iostream>
#include <optional>
#include <string>

#include <nlohmann/json.hpp>

namespace waveguide {
namespace snapshot {

/**
 * @brief SpaceTrackGP structure representing a Ground Position (GP) object from SpaceTrack.
 *
 * This structure is used to hold data retrieved from the SpaceTrack API, specifically for GP objects.
 * It includes various attributes such as APOAPSIS, ECCENTRICITY, and others, which are relevant to
 * satellite tracking and orbital mechanics.
 * * @note: definition can be found here https://www.space-track.org/basicspacedata/modeldef/class/gp/format/html
 */
struct SpaceTrackGP { // TODO: Right now, units are implied, but they should be used if possible. At least look into

    /**
     * @brief Default constructor for SpaceTrackGP.
     */
    SpaceTrackGP() = default;

    /**
     * @brief Constructor that initializes SpaceTrackGP from a JSON object.
     *
     * @param data The JSON object containing the GP data.
     */
    SpaceTrackGP(const nlohmann::json& data);

    /**
     * @brief Default destructor for SpaceTrackGP.
     */
    ~SpaceTrackGP() = default;

    int DB_ID;                                    //!< Database ID for the GP object
    std::optional<double> APOAPSIS;               //!< Apoapsis altitude in kilometers
    std::optional<long double> ARG_OF_PERICENTER; //!< Argument of pericenter in degrees
    std::optional<long double> BSTAR;             //!< B* drag term (BSTAR) in inverse Earth radii
    std::string CCSDS_OMM_VERS;                   //!< CCSDS OMM version
    std::string CENTER_NAME;                      //!< Name of the center
    std::optional<char> CLASSIFICATION_TYPE;      //!< Classification type
    std::string COMMENT;                          //!< Comment
    std::optional<std::string> COUNTRY_CODE;      //!< Country code
    std::optional<std::string> CREATION_DATE;     //!< Creation date
    std::optional<std::string> DECAY_DATE;        //!< Decay date
    std::optional<long double> ECCENTRICITY;      //!< Eccentricity
    std::optional<short> ELEMENT_SET_NO;          //!< Element set number
    std::optional<short unsigned> EPHEMERIS_TYPE; //!< Ephemeris type
    std::optional<std::string> EPOCH;             //!< Epoch
    std::optional<long unsigned> FILE;            //!< File number
    unsigned GP_ID;                               //!< General Perturbations ID
    std::optional<long double> INCLINATION;       //!< Inclination in degrees
    std::optional<std::string> LAUNCH_DATE;       //!< Launch date
    std::optional<double> MEAN_ANOMALY;           //!< Mean anomaly in degrees
    std::string MEAN_ELEMENT_THEORY;              //!< Mean element theory
    std::optional<long double> MEAN_MOTION;       //!< Mean motion in revolutions per day
    std::optional<long double> MEAN_MOTION_DDOT;  //!< Mean motion derivative in revolutions per day squared
    std::optional<long double> MEAN_MOTION_DOT;   //!< Mean motion second derivative in revolutions per day cubed
    unsigned NORAD_CAT_ID;                        //!< NORAD catalog ID
    std::optional<std::string> OBJECT_ID;         //!< Object ID
    std::optional<std::string> OBJECT_NAME;       //!< Object name
    std::optional<std::string> OBJECT_TYPE;       //!< Object type
    std::string ORIGINATOR;                       //!< Originator of the data
    std::optional<double> PERIAPSIS;              //!< Periapsis altitude in kilometers
    std::optional<double> PERIOD;                 //!< Orbital period in minutes
    std::optional<long double> RA_OF_ASC_NODE;    //!< Right ascension of ascending node in degrees
    std::optional<std::string> RCS_SIZE;          //!< Radar cross-section size
    std::string REF_FRAME;                        //!< Reference frame
    std::optional<unsigned> REV_AT_EPOCH;         //!< Revolution number at epoch
    std::optional<double> SEMIMAJOR_AXIS;         //!< Semimajor axis in kilometers
    std::optional<std::string> SITE;              //!< Site of the GP object
    std::string TIME_SYSTEM;                      //!< Time system used for the GP object
    std::optional<std::string> TLE_LINE0;         //!< TLE line 0 (usually the satellite name)
    std::optional<std::string> TLE_LINE1;         //!< TLE line 1 (first line of TLE data)
    std::optional<std::string> TLE_LINE2;         //!< TLE line 2 (second line of TLE data)
};

/**
 * @brief Cleans a JSON entry by removing quotes and returning it as a string.
 *
 * @param entry The JSON entry to clean.
 * @return A cleaned string without quotes.
 */
std::string clean_entry(const nlohmann::json& entry);

/**
 * @brief Extracts a value of type T from a JSON object using the specified key.
 *
 * @tparam T The type of the value to extract.
 * @param json The JSON object to extract from.
 * @param key The key to look for in the JSON object.
 * @return The extracted value of type T.
 * @throws std::runtime_error if the key is not found or if the value is null.
 */
template <typename T>
T extract_from_json(const nlohmann::json& json, const std::string& key)
{
    if (json.contains(key)) {
        if (json[key].empty() || json[key].is_null()) { throw std::runtime_error("Null value not allowed."); }
        else {
            T retval;
            std::stringstream(clean_entry(json[key])) >> retval;
            return retval;
        }
    }
    throw std::runtime_error("Key not found.");
}

/**
 * @brief Extracts an optional value of type T from a JSON object using the specified key.
 *
 * @tparam T The type of the value to extract.
 * @param json The JSON object to extract from.
 * @param key The key to look for in the JSON object.
 * @return An std::optional containing the extracted value, or std::nullopt if the key is not found or the value is null.
 * @throws std::runtime_error if the key is not found.
 */
template <typename T>
std::optional<T> extract_optional_from_json(const nlohmann::json& json, const std::string& key)
{
    if (json.contains(key)) {
        if (json[key].empty() || json[key].is_null()) { return std::nullopt; }
        else {
            T retval;
            const std::string output = clean_entry(json[key]);
            std::stringstream(output) >> retval;
            return retval;
        }
    }
    throw std::runtime_error("Key not found.");
}

/**
 * @brief Extracts a string value from a JSON object using the specified key.
 *
 * @param json The JSON object to extract from.
 * @param key The key to look for in the JSON object.
 * @return The extracted string value.
 * @throws std::runtime_error if the key is not found or if the value is null.
 */
std::string extract_string_from_json(const nlohmann::json& json, const std::string& key);

/**
 * @brief Extracts an optional string value from a JSON object using the specified key.
 *
 * @param json The JSON object to extract from.
 * @param key The key to look for in the JSON object.
 * @return An std::optional containing the extracted string value, or std::nullopt if the key is not found or the value is null.
 * @throws std::runtime_error if the key is not found.
 */
std::optional<std::string> extract_optional_string_from_json(const nlohmann::json& json, const std::string& key);

/**
 * @brief Overloaded output stream operator for an optional type.
 *
 * This function allows printing the contents of an optional type to an output stream.
 *
 * @param os The output stream to write to.
 * @param opt The optional object to print.
 * @return The output stream after writing the optional data.
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, std::optional<T> const& opt)
{
    return opt ? os << opt.value() : os << "Unassigned";
}

/**
 * @brief Overloaded output stream operator for SpaceTrackGP.
 *
 * This function allows printing the contents of a SpaceTrackGP object to an output stream.
 *
 * @param os The output stream to write to.
 * @param gp The SpaceTrackGP object to print.
 * @return The output stream after writing the GP data.
 */
std::ostream& operator<<(std::ostream& os, const SpaceTrackGP& gp);

} // namespace snapshot
} // namespace waveguide