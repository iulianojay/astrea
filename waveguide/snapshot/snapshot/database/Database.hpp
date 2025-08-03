/**
 * @file Database.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Database utility wrapper for the snapshot module
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <sqlite3.h>
#include <vector>

#include <sqlite_orm/sqlite_orm.h>

// mp-units
#include <mp-units/systems/angular.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>

#include <units/typedefs.hpp>

#include <snapshot/http-queries/spacetrack/SpaceTrackGP.hpp>

namespace waveguide {
namespace snapshot {

/**
 * @brief Database utility wrapper for the snapshot module.
 *
 * This class provides a wrapper around the SQLite database used in the snapshot module,
 * allowing for easy access to SpaceTrackGP data and other database operations.
 *
 * @tparam T The type of the database (e.g., sqlite_orm::Storage<SpaceTrackGP>).
 */
template <class T>
class DatabaseUtilityWrapper {
  public:
    /**
     * @brief Default constructor for DatabaseUtilityWrapper.
     *
     * Initializes the DatabaseUtilityWrapper with the provided database instance.
     *
     * @param db The database instance to wrap.
     */
    DatabaseUtilityWrapper(T&& db) :
        _database(db)
    {
    }

    /**
     * @brief Default destructor for DatabaseUtilityWrapper.
     */
    ~DatabaseUtilityWrapper() = default;

    /**
     * @brief Gets the underlying database instance.
     *
     * @return A reference to the wrapped database instance.
     */
    const T& get_database() const;

    /**
     * @brief Gets all SpaceTrackGP records from the database.
     *
     * @tparam Args Types of the optional arguments.
     * @param args Optional arguments to pass to the database query.
     * @return A vector containing all SpaceTrackGP records.
     */
    template <typename... Args>
    std::vector<SpaceTrackGP> get_all(Args&&... args) const;

    /**
     * @brief Gets a SpaceTrackGP record by its NORAD ID.
     *
     * @param id The NORAD ID of the SpaceTrackGP record to retrieve.
     * @return A SpaceTrackGP object corresponding to the given NORAD ID.
     */
    SpaceTrackGP get_sat_from_norad_id(const unsigned& id) const;

    /**
     * @brief Gets a SpaceTrackGP record by its name
     *
     * @param name The name of the SpaceTrackGP record to retrieve.
     * @return A SpaceTrackGP object corresponding to the given name.
     */
    std::vector<SpaceTrackGP> get_sats_by_name(const std::string& name) const;

    /**
     * @brief Gets SpaceTrackGP records within a specified range of periapsis and apoapsis.
     *
     * @param minPeriapsis The minimum periapsis distance.
     * @param maxApoapsis The maximum apoapsis distance.
     * @return A vector containing SpaceTrackGP records that fall within the specified range.
     */
    std::vector<SpaceTrackGP> get_sats_in_range(const Distance& minPeriapsis, const Distance& maxApoapsis) const;

  private:
    T _database; //!< The wrapped database instance.
};

/**
 * @brief Creates a DatabaseUtilityWrapper instance for the given database.
 *
 * This function is a convenience wrapper to create a DatabaseUtilityWrapper
 * for the provided database instance.
 *
 * @tparam T The type of the database (e.g., sqlite_orm::Storage<SpaceTrackGP>).
 * @param database The database instance to wrap.
 * @return A DatabaseUtilityWrapper instance wrapping the provided database.
 */
template <typename T>
DatabaseUtilityWrapper<typename std::decay<T>::type> make_database(T&& database)
{
    return DatabaseUtilityWrapper<typename std::decay<T>::type>{ std::forward<T>(database) };
}

/**
 * @brief Gets the snapshot database instance.
 *
 * This function creates and returns a SQLite storage instance for the snapshot database.
 *
 * @return A sqlite_orm::Storage instance configured for the snapshot database.
 */
inline auto get_snapshot()
{
    static const std::string root = std::getenv("WAVEGUIDE_ROOT");
    return sqlite_orm::make_storage(
        root + "/waveguide/snapshot/snapshot/database/snapshot.db",
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

/**
 * @brief Creates a DatabaseUtilityWrapper for the snapshot database.
 *
 * This function creates a DatabaseUtilityWrapper instance for the snapshot database,
 * allowing easy access to SpaceTrackGP data and other database operations.
 *
 * @return A DatabaseUtilityWrapper instance wrapping the snapshot database.
 */
inline auto make_snapshot_wrapper() { return make_database(get_snapshot()); }

} // namespace snapshot
} // namespace waveguide

#include <snapshot/database/Database.ipp>