#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <sqlite3.h>
#include <stdexcept>
#include <string>

#include <nlohmann/json.hpp>
#include <sqlite_orm/sqlite_orm.h>

#include <astro/time/Date.hpp>


template <typename T>
T extract_from_json(const nlohmann::json& json, const std::string& key);

template <typename T>
std::optional<T> extract_optional_from_json(const nlohmann::json& json, const std::string& key);

std::string clean_entry(const nlohmann::json& entry)
{
    std::string entryStr = entry.template get<std::string>();
    entryStr.erase(std::remove(entryStr.begin(), entryStr.end(), '"'), entryStr.end());
    return entryStr;
}

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
            std::stringstream(clean_entry(json[key])) >> retval;
            return retval;
        }
    }
    throw std::runtime_error("Key not found.");
}


// https://www.space-track.org/basicspacedata/modeldef/class/gp/format/html
struct SpaceTrackGP {
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

SpaceTrackGP build_gp_from_json(const nlohmann::json& data);

int main()
{
    // Build connection and connect
    using namespace sqlite_orm;
    using json = nlohmann::json;

    auto storage = make_storage(
        "./waveguide/snapshot/snapshot/data/snapshot.db",
        make_table(
            "SpaceTrackGP",
            make_column("DB_ID", &SpaceTrackGP::DB_ID, primary_key().autoincrement()),
            make_column("APOAPSIS", &SpaceTrackGP::APOAPSIS),
            make_column("ARG_OF_PERICENTER", &SpaceTrackGP::ARG_OF_PERICENTER),
            make_column("BSTAR", &SpaceTrackGP::BSTAR),
            make_column("CCSDS_OMM_VERS", &SpaceTrackGP::CCSDS_OMM_VERS),
            make_column("CENTER_NAME", &SpaceTrackGP::CENTER_NAME),
            make_column("CLASSIFICATION_TYPE", &SpaceTrackGP::CLASSIFICATION_TYPE),
            make_column("COMMENT", &SpaceTrackGP::COMMENT),
            make_column("COUNTRY_CODE", &SpaceTrackGP::COUNTRY_CODE),
            make_column("CREATION_DATE", &SpaceTrackGP::CREATION_DATE),
            make_column("DECAY_DATE", &SpaceTrackGP::DECAY_DATE),
            make_column("ECCENTRICITY", &SpaceTrackGP::ECCENTRICITY),
            make_column("ELEMENT_SET_NO", &SpaceTrackGP::ELEMENT_SET_NO),
            make_column("EPHEMERIS_TYPE", &SpaceTrackGP::EPHEMERIS_TYPE),
            make_column("EPOCH", &SpaceTrackGP::EPOCH),
            make_column("FILE", &SpaceTrackGP::FILE),
            make_column("GP_ID", &SpaceTrackGP::GP_ID, unique()),
            make_column("INCLINATION", &SpaceTrackGP::INCLINATION),
            make_column("LAUNCH_DATE", &SpaceTrackGP::LAUNCH_DATE),
            make_column("MEAN_ANOMALY", &SpaceTrackGP::MEAN_ANOMALY),
            make_column("MEAN_ELEMENT_THEORY", &SpaceTrackGP::MEAN_ELEMENT_THEORY),
            make_column("MEAN_MOTION", &SpaceTrackGP::MEAN_MOTION),
            make_column("MEAN_MOTION_DDOT", &SpaceTrackGP::MEAN_MOTION_DDOT),
            make_column("MEAN_MOTION_DOT", &SpaceTrackGP::MEAN_MOTION_DOT),
            make_column("NORAD_CAT_ID", &SpaceTrackGP::NORAD_CAT_ID, unique()),
            make_column("OBJECT_ID", &SpaceTrackGP::OBJECT_ID),
            make_column("OBJECT_NAME", &SpaceTrackGP::OBJECT_NAME),
            make_column("OBJECT_TYPE", &SpaceTrackGP::OBJECT_TYPE),
            make_column("ORIGINATOR", &SpaceTrackGP::ORIGINATOR),
            make_column("PERIAPSIS", &SpaceTrackGP::PERIAPSIS),
            make_column("PERIOD", &SpaceTrackGP::PERIOD),
            make_column("RA_OF_ASC_NODE", &SpaceTrackGP::RA_OF_ASC_NODE),
            make_column("RCS_SIZE", &SpaceTrackGP::RCS_SIZE),
            make_column("REF_FRAME", &SpaceTrackGP::REF_FRAME),
            make_column("REV_AT_EPOCH", &SpaceTrackGP::REV_AT_EPOCH),
            make_column("SEMIMAJOR_AXIS", &SpaceTrackGP::SEMIMAJOR_AXIS),
            make_column("SITE", &SpaceTrackGP::SITE),
            make_column("TIME_SYSTEM", &SpaceTrackGP::TIME_SYSTEM),
            make_column("TLE_LINE0", &SpaceTrackGP::TLE_LINE0),
            make_column("TLE_LINE1", &SpaceTrackGP::TLE_LINE1),
            make_column("TLE_LINE2", &SpaceTrackGP::TLE_LINE2)
        )
    );
    storage.sync_schema();
    // storage.remove_all<SpaceTrackGP>();

    std::ifstream inFileStream("./waveguide/snapshot/snapshot/data/spacetrack_data.json");
    json spaceTrackData = json::parse(inFileStream);


    std::size_t barWidth = 50;
    std::size_t iRecord  = 0;
    std::size_t nRecords = spaceTrackData.size();
    for (const auto& data : spaceTrackData) {

        if (iRecord % 10 == 0) {
            std::cout << "Progress: [";
            double progress = static_cast<double>(iRecord) / static_cast<double>(nRecords);
            std::size_t pos = barWidth * progress;
            for (std::size_t ii = 0; ii < barWidth; ++ii) {
                if (ii < pos)
                    std::cout << "=";
                else if (ii == pos)
                    std::cout << ">";
                else
                    std::cout << " ";
            }
            std::cout << "] " << int(progress * 100.0) << " %\r";
            std::cout.flush();
        }

        SpaceTrackGP gp = build_gp_from_json(data);

        // Insert or update
        auto all = storage.get_all<SpaceTrackGP>(where(c(&SpaceTrackGP::NORAD_CAT_ID) == gp.NORAD_CAT_ID));
        if (all.size() == 0) { storage.insert(gp); }
        else {
            storage.update(gp);
        }

        ++iRecord;

        // try {
        //     auto gp = storage.get_all<SpaceTrackGP>(where(c(&SpaceTrackGP::NORAD_CAT_ID) == gp.NORAD_CAT_ID));
        //     std::cout << "NORAD_CAT_ID = " << gp[0].NORAD_CAT_ID << std::endl;
        //     std::cout << "GP_ID = " << gp[0].GP_ID << std::endl;
        // }
        // catch (const std::system_error& e) {
        //     std::cout << e.what() << std::endl;
        // }
        // catch (...) {
        //     std::cout << "unknown exeption" << std::endl;
        // }
    }

    return 0;
}


SpaceTrackGP build_gp_from_json(const nlohmann::json& data)
{
    return { -1,
             extract_optional_from_json<double>(data, "APOAPSIS"),
             extract_optional_from_json<long double>(data, "ARG_OF_PERICENTER"),
             extract_optional_from_json<long double>(data, "BSTAR"),
             extract_from_json<std::string>(data, "CCSDS_OMM_VERS"),
             extract_from_json<std::string>(data, "CENTER_NAME"),
             extract_optional_from_json<char>(data, "CLASSIFICATION_TYPE"),
             extract_from_json<std::string>(data, "COMMENT"),
             extract_optional_from_json<std::string>(data, "COUNTRY_CODE"),
             extract_optional_from_json<std::string>(data, "CREATION_DATE"),
             extract_optional_from_json<std::string>(data, "DECAY_DATE"),
             extract_optional_from_json<long double>(data, "ECCENTRICITY"),
             extract_optional_from_json<short>(data, "ELEMENT_SET_NO"),
             extract_optional_from_json<short unsigned>(data, "EPHEMERIS_TYPE"),
             extract_optional_from_json<std::string>(data, "EPOCH"),
             extract_optional_from_json<long unsigned>(data, "FILE"),
             extract_from_json<unsigned>(data, "GP_ID"),
             extract_optional_from_json<long double>(data, "INCLINATION"),
             extract_optional_from_json<std::string>(data, "LAUNCH_DATE"),
             extract_optional_from_json<double>(data, "MEAN_ANOMALY"),
             extract_from_json<std::string>(data, "MEAN_ELEMENT_THEORY"),
             extract_optional_from_json<long double>(data, "MEAN_MOTION"),
             extract_optional_from_json<long double>(data, "MEAN_MOTION_DDOT"),
             extract_optional_from_json<long double>(data, "MEAN_MOTION_DOT"),
             extract_from_json<unsigned>(data, "NORAD_CAT_ID"),
             extract_optional_from_json<std::string>(data, "OBJECT_ID"),
             extract_optional_from_json<std::string>(data, "OBJECT_NAME"),
             extract_optional_from_json<std::string>(data, "OBJECT_TYPE"),
             extract_from_json<std::string>(data, "ORIGINATOR"),
             extract_optional_from_json<double>(data, "PERIAPSIS"),
             extract_optional_from_json<double>(data, "PERIOD"),
             extract_optional_from_json<long double>(data, "RA_OF_ASC_NODE"),
             extract_optional_from_json<std::string>(data, "RCS_SIZE"),
             extract_from_json<std::string>(data, "REF_FRAME"),
             extract_optional_from_json<unsigned>(data, "REV_AT_EPOCH"),
             extract_optional_from_json<double>(data, "SEMIMAJOR_AXIS"),
             extract_optional_from_json<std::string>(data, "SITE"),
             extract_from_json<std::string>(data, "TIME_SYSTEM"),
             extract_optional_from_json<std::string>(data, "TLE_LINE0"),
             extract_optional_from_json<std::string>(data, "TLE_LINE1"),
             extract_optional_from_json<std::string>(data, "TLE_LINE2") };
}