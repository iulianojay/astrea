#pragma once

#include <sqlite3.h>
#include <vector>

#include <sqlite_orm/sqlite_orm.h>

// mp-units
#include <mp-units/systems/angular.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>

#include <snapshot/http-queries/spacetrack/SpaceTrackGP.hpp>

namespace waveguide {
namespace snapshot {

using Distance = mp_units::quantity<mp_units::si::unit_symbols::km>;

template <class T>
class DatabaseUtilityWrapper {
  public:
    DatabaseUtilityWrapper(T&& db) :
        _database(db)
    {
    }
    ~DatabaseUtilityWrapper() = default;

    const T& get_database() const;

    template <typename... Args>
    std::vector<SpaceTrackGP> get_all(Args&&... args) const;

    SpaceTrackGP get_sat_from_norad_id(const unsigned& id) const;

    std::vector<SpaceTrackGP> get_sats_by_name(const std::string& name) const;

    std::vector<SpaceTrackGP> get_sats_in_range(const Distance& minPeriapsis, const Distance& maxApoapsis) const;

  private:
    T _database;
};

template <typename T>
DatabaseUtilityWrapper<typename std::decay<T>::type> make_database(T&& database)
{
    return DatabaseUtilityWrapper<typename std::decay<T>::type>{ std::forward<T>(database) };
}

inline auto get_snapshot()
{
    return sqlite_orm::make_storage(
        "/home/jay/projects/waveguide/waveguide/snapshot/snapshot/database/snapshot.db", // TODO: Fix the pathing
        sqlite_orm::make_table(
            "SpaceTrackGP",
            sqlite_orm::make_column("DB_ID", &snapshot::SpaceTrackGP::DB_ID, sqlite_orm::primary_key().autoincrement()),
            sqlite_orm::make_column("APOAPSIS", &snapshot::SpaceTrackGP::APOAPSIS),
            sqlite_orm::make_column("ARG_OF_PERICENTER", &snapshot::SpaceTrackGP::ARG_OF_PERICENTER),
            sqlite_orm::make_column("BSTAR", &snapshot::SpaceTrackGP::BSTAR),
            sqlite_orm::make_column("CCSDS_OMM_VERS", &snapshot::SpaceTrackGP::CCSDS_OMM_VERS),
            sqlite_orm::make_column("CENTER_NAME", &snapshot::SpaceTrackGP::CENTER_NAME),
            sqlite_orm::make_column("CLASSIFICATION_TYPE", &snapshot::SpaceTrackGP::CLASSIFICATION_TYPE),
            sqlite_orm::make_column("COMMENT", &snapshot::SpaceTrackGP::COMMENT),
            sqlite_orm::make_column("COUNTRY_CODE", &snapshot::SpaceTrackGP::COUNTRY_CODE),
            sqlite_orm::make_column("CREATION_DATE", &snapshot::SpaceTrackGP::CREATION_DATE),
            sqlite_orm::make_column("DECAY_DATE", &snapshot::SpaceTrackGP::DECAY_DATE),
            sqlite_orm::make_column("ECCENTRICITY", &snapshot::SpaceTrackGP::ECCENTRICITY),
            sqlite_orm::make_column("ELEMENT_SET_NO", &snapshot::SpaceTrackGP::ELEMENT_SET_NO),
            sqlite_orm::make_column("EPHEMERIS_TYPE", &snapshot::SpaceTrackGP::EPHEMERIS_TYPE),
            sqlite_orm::make_column("EPOCH", &snapshot::SpaceTrackGP::EPOCH),
            sqlite_orm::make_column("FILE", &snapshot::SpaceTrackGP::FILE),
            sqlite_orm::make_column("GP_ID", &snapshot::SpaceTrackGP::GP_ID, sqlite_orm::unique()),
            sqlite_orm::make_column("INCLINATION", &snapshot::SpaceTrackGP::INCLINATION),
            sqlite_orm::make_column("LAUNCH_DATE", &snapshot::SpaceTrackGP::LAUNCH_DATE),
            sqlite_orm::make_column("MEAN_ANOMALY", &snapshot::SpaceTrackGP::MEAN_ANOMALY),
            sqlite_orm::make_column("MEAN_ELEMENT_THEORY", &snapshot::SpaceTrackGP::MEAN_ELEMENT_THEORY),
            sqlite_orm::make_column("MEAN_MOTION", &snapshot::SpaceTrackGP::MEAN_MOTION),
            sqlite_orm::make_column("MEAN_MOTION_DDOT", &snapshot::SpaceTrackGP::MEAN_MOTION_DDOT),
            sqlite_orm::make_column("MEAN_MOTION_DOT", &snapshot::SpaceTrackGP::MEAN_MOTION_DOT),
            sqlite_orm::make_column("NORAD_CAT_ID", &snapshot::SpaceTrackGP::NORAD_CAT_ID, sqlite_orm::unique()),
            sqlite_orm::make_column("OBJECT_ID", &snapshot::SpaceTrackGP::OBJECT_ID),
            sqlite_orm::make_column("OBJECT_NAME", &snapshot::SpaceTrackGP::OBJECT_NAME),
            sqlite_orm::make_column("OBJECT_TYPE", &snapshot::SpaceTrackGP::OBJECT_TYPE),
            sqlite_orm::make_column("ORIGINATOR", &snapshot::SpaceTrackGP::ORIGINATOR),
            sqlite_orm::make_column("PERIAPSIS", &snapshot::SpaceTrackGP::PERIAPSIS),
            sqlite_orm::make_column("PERIOD", &snapshot::SpaceTrackGP::PERIOD),
            sqlite_orm::make_column("RA_OF_ASC_NODE", &snapshot::SpaceTrackGP::RA_OF_ASC_NODE),
            sqlite_orm::make_column("RCS_SIZE", &snapshot::SpaceTrackGP::RCS_SIZE),
            sqlite_orm::make_column("REF_FRAME", &snapshot::SpaceTrackGP::REF_FRAME),
            sqlite_orm::make_column("REV_AT_EPOCH", &snapshot::SpaceTrackGP::REV_AT_EPOCH),
            sqlite_orm::make_column("SEMIMAJOR_AXIS", &snapshot::SpaceTrackGP::SEMIMAJOR_AXIS),
            sqlite_orm::make_column("SITE", &snapshot::SpaceTrackGP::SITE),
            sqlite_orm::make_column("TIME_SYSTEM", &snapshot::SpaceTrackGP::TIME_SYSTEM),
            sqlite_orm::make_column("TLE_LINE0", &snapshot::SpaceTrackGP::TLE_LINE0),
            sqlite_orm::make_column("TLE_LINE1", &snapshot::SpaceTrackGP::TLE_LINE1),
            sqlite_orm::make_column("TLE_LINE2", &snapshot::SpaceTrackGP::TLE_LINE2)
        )
    );
}

inline auto make_snapshot_wrapper() { return make_database(get_snapshot()); }

} // namespace snapshot
} // namespace waveguide

#include <snapshot/database/Database.ipp>