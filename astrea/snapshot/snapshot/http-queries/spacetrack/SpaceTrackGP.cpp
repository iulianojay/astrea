#include <snapshot/http-queries/spacetrack/SpaceTrackGP.hpp>

#include <utilities/json_util.hpp>

namespace astrea {
namespace snapshot {

using utilities::extract_from_json;
using utilities::extract_optional_from_json;
using utilities::extract_optional_string_from_json;
using utilities::extract_string_from_json;

SpaceTrackGP::SpaceTrackGP(const nlohmann::json& data) :
    DB_ID(-1),
    APOAPSIS(extract_optional_from_json<double>(data, "APOAPSIS")),
    ARG_OF_PERICENTER(extract_optional_from_json<long double>(data, "ARG_OF_PERICENTER")),
    BSTAR(extract_optional_from_json<long double>(data, "BSTAR")),
    CCSDS_OMM_VERS(extract_string_from_json(data, "CCSDS_OMM_VERS")),
    CENTER_NAME(extract_string_from_json(data, "CENTER_NAME")),
    CLASSIFICATION_TYPE(extract_optional_from_json<char>(data, "CLASSIFICATION_TYPE")),
    COMMENT(extract_string_from_json(data, "COMMENT")),
    COUNTRY_CODE(extract_optional_string_from_json(data, "COUNTRY_CODE")),
    CREATION_DATE(extract_optional_string_from_json(data, "CREATION_DATE")),
    DECAY_DATE(extract_optional_string_from_json(data, "DECAY_DATE")),
    ECCENTRICITY(extract_optional_from_json<long double>(data, "ECCENTRICITY")),
    ELEMENT_SET_NO(extract_optional_from_json<short>(data, "ELEMENT_SET_NO")),
    EPHEMERIS_TYPE(extract_optional_from_json<short unsigned>(data, "EPHEMERIS_TYPE")),
    EPOCH(extract_optional_string_from_json(data, "EPOCH")),
    FILE(extract_optional_from_json<long unsigned>(data, "FILE")),
    GP_ID(extract_from_json<unsigned>(data, "GP_ID")),
    INCLINATION(extract_optional_from_json<long double>(data, "INCLINATION")),
    LAUNCH_DATE(extract_optional_string_from_json(data, "LAUNCH_DATE")),
    MEAN_ANOMALY(extract_optional_from_json<double>(data, "MEAN_ANOMALY")),
    MEAN_ELEMENT_THEORY(extract_string_from_json(data, "MEAN_ELEMENT_THEORY")),
    MEAN_MOTION(extract_optional_from_json<long double>(data, "MEAN_MOTION")),
    MEAN_MOTION_DDOT(extract_optional_from_json<long double>(data, "MEAN_MOTION_DDOT")),
    MEAN_MOTION_DOT(extract_optional_from_json<long double>(data, "MEAN_MOTION_DOT")),
    NORAD_CAT_ID(extract_from_json<unsigned>(data, "NORAD_CAT_ID")),
    OBJECT_ID(extract_optional_string_from_json(data, "OBJECT_ID")),
    OBJECT_NAME(extract_optional_string_from_json(data, "OBJECT_NAME")),
    OBJECT_TYPE(extract_optional_string_from_json(data, "OBJECT_TYPE")),
    ORIGINATOR(extract_string_from_json(data, "ORIGINATOR")),
    PERIAPSIS(extract_optional_from_json<double>(data, "PERIAPSIS")),
    PERIOD(extract_optional_from_json<double>(data, "PERIOD")),
    RA_OF_ASC_NODE(extract_optional_from_json<long double>(data, "RA_OF_ASC_NODE")),
    RCS_SIZE(extract_optional_string_from_json(data, "RCS_SIZE")),
    REF_FRAME(extract_string_from_json(data, "REF_FRAME")),
    REV_AT_EPOCH(extract_optional_from_json<unsigned>(data, "REV_AT_EPOCH")),
    SEMIMAJOR_AXIS(extract_optional_from_json<double>(data, "SEMIMAJOR_AXIS")),
    SITE(extract_optional_string_from_json(data, "SITE")),
    TIME_SYSTEM(extract_string_from_json(data, "TIME_SYSTEM")),
    TLE_LINE0(extract_optional_string_from_json(data, "TLE_LINE0")),
    TLE_LINE1(extract_optional_string_from_json(data, "TLE_LINE1")),
    TLE_LINE2(extract_optional_string_from_json(data, "TLE_LINE2"))
{
}

std::ostream& operator<<(std::ostream& os, const SpaceTrackGP& gp)
{
    os << "DB_ID: " << gp.DB_ID << std::endl;
    os << "APOAPSIS: " << gp.APOAPSIS << std::endl;
    os << "ARG_OF_PERICENTER: " << gp.ARG_OF_PERICENTER << std::endl;
    os << "BSTAR: " << gp.BSTAR << std::endl;
    os << "CCSDS_OMM_VERS: " << gp.CCSDS_OMM_VERS << std::endl;
    os << "CENTER_NAME: " << gp.CENTER_NAME << std::endl;
    os << "CLASSIFICATION_TYPE: " << gp.CLASSIFICATION_TYPE << std::endl;
    os << "COMMENT: " << gp.COMMENT << std::endl;
    os << "COUNTRY_CODE: " << gp.COUNTRY_CODE << std::endl;
    os << "CREATION_DATE: " << gp.CREATION_DATE << std::endl;
    os << "DECAY_DATE: " << gp.DECAY_DATE << std::endl;
    os << "ECCENTRICITY: " << gp.ECCENTRICITY << std::endl;
    os << "ELEMENT_SET_NO: " << gp.ELEMENT_SET_NO << std::endl;
    os << "EPHEMERIS_TYPE: " << gp.EPHEMERIS_TYPE << std::endl;
    os << "EPOCH: " << gp.EPOCH << std::endl;
    os << "FILE: " << gp.FILE << std::endl;
    os << "GP_ID: " << gp.GP_ID << std::endl;
    os << "INCLINATION: " << gp.INCLINATION << std::endl;
    os << "LAUNCH_DATE: " << gp.LAUNCH_DATE << std::endl;
    os << "MEAN_ANOMALY: " << gp.MEAN_ANOMALY << std::endl;
    os << "MEAN_ELEMENT_THEORY: " << gp.MEAN_ELEMENT_THEORY << std::endl;
    os << "MEAN_MOTION: " << gp.MEAN_MOTION << std::endl;
    os << "MEAN_MOTION_DDOT: " << gp.MEAN_MOTION_DDOT << std::endl;
    os << "MEAN_MOTION_DOT: " << gp.MEAN_MOTION_DOT << std::endl;
    os << "NORAD_CAT_ID: " << gp.NORAD_CAT_ID << std::endl;
    os << "OBJECT_ID: " << gp.OBJECT_ID << std::endl;
    os << "OBJECT_NAME: " << gp.OBJECT_NAME << std::endl;
    os << "OBJECT_TYPE: " << gp.OBJECT_TYPE << std::endl;
    os << "ORIGINATOR: " << gp.ORIGINATOR << std::endl;
    os << "PERIAPSIS: " << gp.PERIAPSIS << std::endl;
    os << "PERIOD: " << gp.PERIOD << std::endl;
    os << "RA_OF_ASC_NODE: " << gp.RA_OF_ASC_NODE << std::endl;
    os << "RCS_SIZE: " << gp.RCS_SIZE << std::endl;
    os << "REF_FRAME: " << gp.REF_FRAME << std::endl;
    os << "REV_AT_EPOCH: " << gp.REV_AT_EPOCH << std::endl;
    os << "SEMIMAJOR_AXIS: " << gp.SEMIMAJOR_AXIS << std::endl;
    os << "SITE: " << gp.SITE << std::endl;
    os << "TIME_SYSTEM: " << gp.TIME_SYSTEM << std::endl;
    os << "TLE_LINE0: " << gp.TLE_LINE0 << std::endl;
    os << "TLE_LINE1: " << gp.TLE_LINE1 << std::endl;
    os << "TLE_LINE2: " << gp.TLE_LINE2 << std::endl;

    return os;
}


} // namespace snapshot
} // namespace astrea