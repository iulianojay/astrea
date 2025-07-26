#pragma once

#include <iostream>
#include <optional>
#include <string>

#include <nlohmann/json.hpp>

namespace waveguide {
namespace snapshot {

// https://www.space-track.org/basicspacedata/modeldef/class/gp/format/html
struct SpaceTrackGP { // TODO: Right now, units are implied, but they should be used if possible. At least look into

    SpaceTrackGP() = default;
    SpaceTrackGP(const nlohmann::json& data);
    ~SpaceTrackGP() = default;

    int DB_ID;
    std::optional<double> APOAPSIS;
    std::optional<long double> ARG_OF_PERICENTER;
    std::optional<long double> BSTAR;
    std::string CCSDS_OMM_VERS;
    std::string CENTER_NAME;
    std::optional<char> CLASSIFICATION_TYPE;
    std::string COMMENT;
    std::optional<std::string> COUNTRY_CODE;
    std::optional<std::string> CREATION_DATE;
    std::optional<std::string> DECAY_DATE;
    std::optional<long double> ECCENTRICITY;
    std::optional<short> ELEMENT_SET_NO;
    std::optional<short unsigned> EPHEMERIS_TYPE;
    std::optional<std::string> EPOCH;
    std::optional<long unsigned> FILE;
    unsigned GP_ID;
    std::optional<long double> INCLINATION;
    std::optional<std::string> LAUNCH_DATE;
    std::optional<double> MEAN_ANOMALY;
    std::string MEAN_ELEMENT_THEORY;
    std::optional<long double> MEAN_MOTION;
    std::optional<long double> MEAN_MOTION_DDOT;
    std::optional<long double> MEAN_MOTION_DOT;
    unsigned NORAD_CAT_ID;
    std::optional<std::string> OBJECT_ID;
    std::optional<std::string> OBJECT_NAME;
    std::optional<std::string> OBJECT_TYPE;
    std::string ORIGINATOR;
    std::optional<double> PERIAPSIS;
    std::optional<double> PERIOD;
    std::optional<long double> RA_OF_ASC_NODE;
    std::optional<std::string> RCS_SIZE;
    std::string REF_FRAME;
    std::optional<unsigned> REV_AT_EPOCH;
    std::optional<double> SEMIMAJOR_AXIS;
    std::optional<std::string> SITE;
    std::string TIME_SYSTEM;
    std::optional<std::string> TLE_LINE0;
    std::optional<std::string> TLE_LINE1;
    std::optional<std::string> TLE_LINE2;
};

std::string clean_entry(const nlohmann::json& entry);

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

std::string extract_string_from_json(const nlohmann::json& json, const std::string& key);
std::optional<std::string> extract_optional_string_from_json(const nlohmann::json& json, const std::string& key);

template <typename T>
std::ostream& operator<<(std::ostream& os, std::optional<T> const& opt)
{
    return opt ? os << opt.value() : os << "Unassigned";
}

std::ostream& operator<<(std::ostream& os, const SpaceTrackGP& gp);

} // namespace snapshot
} // namespace waveguide