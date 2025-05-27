#include <snapshot/http-queries/spacetrack/SpaceTrackGP.hpp>

namespace snapshot {


SpaceTrackGP::SpaceTrackGP(const nlohmann::json& data) :
    DB_ID(-1),
    APOAPSIS(extract_optional_from_json<double>(data, "APOAPSIS")),
    ARG_OF_PERICENTER(extract_optional_from_json<long double>(data, "ARG_OF_PERICENTER")),
    BSTAR(extract_optional_from_json<long double>(data, "BSTAR")),
    CCSDS_OMM_VERS(extract_from_json<std::string>(data, "CCSDS_OMM_VERS")),
    CENTER_NAME(extract_from_json<std::string>(data, "CENTER_NAME")),
    CLASSIFICATION_TYPE(extract_optional_from_json<char>(data, "CLASSIFICATION_TYPE")),
    COMMENT(extract_from_json<std::string>(data, "COMMENT")),
    COUNTRY_CODE(extract_optional_from_json<std::string>(data, "COUNTRY_CODE")),
    CREATION_DATE(extract_optional_from_json<std::string>(data, "CREATION_DATE")),
    DECAY_DATE(extract_optional_from_json<std::string>(data, "DECAY_DATE")),
    ECCENTRICITY(extract_optional_from_json<long double>(data, "ECCENTRICITY")),
    ELEMENT_SET_NO(extract_optional_from_json<short>(data, "ELEMENT_SET_NO")),
    EPHEMERIS_TYPE(extract_optional_from_json<short unsigned>(data, "EPHEMERIS_TYPE")),
    EPOCH(extract_optional_from_json<std::string>(data, "EPOCH")),
    FILE(extract_optional_from_json<long unsigned>(data, "FILE")),
    GP_ID(extract_from_json<unsigned>(data, "GP_ID")),
    INCLINATION(extract_optional_from_json<long double>(data, "INCLINATION")),
    LAUNCH_DATE(extract_optional_from_json<std::string>(data, "LAUNCH_DATE")),
    MEAN_ANOMALY(extract_optional_from_json<double>(data, "MEAN_ANOMALY")),
    MEAN_ELEMENT_THEORY(extract_from_json<std::string>(data, "MEAN_ELEMENT_THEORY")),
    MEAN_MOTION(extract_optional_from_json<long double>(data, "MEAN_MOTION")),
    MEAN_MOTION_DDOT(extract_optional_from_json<long double>(data, "MEAN_MOTION_DDOT")),
    MEAN_MOTION_DOT(extract_optional_from_json<long double>(data, "MEAN_MOTION_DOT")),
    NORAD_CAT_ID(extract_from_json<unsigned>(data, "NORAD_CAT_ID")),
    OBJECT_ID(extract_optional_from_json<std::string>(data, "OBJECT_ID")),
    OBJECT_NAME(extract_optional_from_json<std::string>(data, "OBJECT_NAME")),
    OBJECT_TYPE(extract_optional_from_json<std::string>(data, "OBJECT_TYPE")),
    ORIGINATOR(extract_from_json<std::string>(data, "ORIGINATOR")),
    PERIAPSIS(extract_optional_from_json<double>(data, "PERIAPSIS")),
    PERIOD(extract_optional_from_json<double>(data, "PERIOD")),
    RA_OF_ASC_NODE(extract_optional_from_json<long double>(data, "RA_OF_ASC_NODE")),
    RCS_SIZE(extract_optional_from_json<std::string>(data, "RCS_SIZE")),
    REF_FRAME(extract_from_json<std::string>(data, "REF_FRAME")),
    REV_AT_EPOCH(extract_optional_from_json<unsigned>(data, "REV_AT_EPOCH")),
    SEMIMAJOR_AXIS(extract_optional_from_json<double>(data, "SEMIMAJOR_AXIS")),
    SITE(extract_optional_from_json<std::string>(data, "SITE")),
    TIME_SYSTEM(extract_from_json<std::string>(data, "TIME_SYSTEM")),
    TLE_LINE0(extract_optional_from_json<std::string>(data, "TLE_LINE0")),
    TLE_LINE1(extract_optional_from_json<std::string>(data, "TLE_LINE1")),
    TLE_LINE2(extract_optional_from_json<std::string>(data, "TLE_LINE2"))
{
}

std::string clean_entry(const nlohmann::json& entry)
{
    std::string entryStr = entry.template get<std::string>();
    entryStr.erase(std::remove(entryStr.begin(), entryStr.end(), '"'), entryStr.end());
    return entryStr;
}

} // namespace snapshot