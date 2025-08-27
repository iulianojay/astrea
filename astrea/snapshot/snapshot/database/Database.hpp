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

#include <astro/state/orbital_data_formats/instances/GeneralPerturbations.hpp>

namespace astrea {
namespace snapshot {

/**
 * @brief Database utility wrapper for the snapshot module.
 *
 * This class provides a wrapper around the SQLite database used in the snapshot module,
 * allowing for easy access to GeneralPerturbations data and other database operations.
 *
 * @tparam T The type of the database (e.g., sqlite_orm::Storage<GeneralPerturbations>).
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
     * @brief Gets all GeneralPerturbations records from the database.
     *
     * @tparam Args Types of the optional arguments.
     * @param args Optional arguments to pass to the database query.
     * @return A vector containing all GeneralPerturbations records.
     */
    template <typename... Args>
    std::vector<astro::GeneralPerturbations> get_all(Args&&... args) const;

    /**
     * @brief Gets a GeneralPerturbations record by its NORAD ID.
     *
     * @param id The NORAD ID of the GeneralPerturbations record to retrieve.
     * @return A GeneralPerturbations object corresponding to the given NORAD ID.
     */
    astro::GeneralPerturbations get_sat_from_norad_id(const unsigned& id) const;

    /**
     * @brief Gets a GeneralPerturbations record by its name
     *
     * @param name The name of the GeneralPerturbations record to retrieve.
     * @return A GeneralPerturbations object corresponding to the given name.
     */
    std::vector<astro::GeneralPerturbations> get_sats_by_name(const std::string& name) const;

    /**
     * @brief Gets GeneralPerturbations records within a specified range of periapsis and apoapsis.
     *
     * @param minPeriapsis The minimum periapsis distance.
     * @param maxApoapsis The maximum apoapsis distance.
     * @return A vector containing GeneralPerturbations records that fall within the specified range.
     */
    std::vector<astro::GeneralPerturbations> get_sats_in_range(const Distance& minPeriapsis, const Distance& maxApoapsis) const;

  private:
    T _database; //!< The wrapped database instance.
};

/**
 * @brief Creates a DatabaseUtilityWrapper instance for the given database.
 *
 * This function is a convenience wrapper to create a DatabaseUtilityWrapper
 * for the provided database instance.
 *
 * @tparam T The type of the database (e.g., sqlite_orm::Storage<GeneralPerturbations>).
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
    static const std::string root = std::getenv("ASTREA_ROOT");
    return sqlite_orm::make_storage(
        root + "/astrea/snapshot/snapshot/database/snapshot.db",
        sqlite_orm::make_table(
            "GeneralPerturbations",
            sqlite_orm::make_column("DB_ID", &astro::GeneralPerturbations::DB_ID, sqlite_orm::primary_key().autoincrement()),
            sqlite_orm::make_column("APOAPSIS", &astro::GeneralPerturbations::APOAPSIS),
            sqlite_orm::make_column("ARG_OF_PERICENTER", &astro::GeneralPerturbations::ARG_OF_PERICENTER),
            sqlite_orm::make_column("BSTAR", &astro::GeneralPerturbations::BSTAR),
            sqlite_orm::make_column("CCSDS_OMM_VERS", &astro::GeneralPerturbations::CCSDS_OMM_VERS),
            sqlite_orm::make_column("CENTER_NAME", &astro::GeneralPerturbations::CENTER_NAME),
            sqlite_orm::make_column("CLASSIFICATION_TYPE", &astro::GeneralPerturbations::CLASSIFICATION_TYPE),
            sqlite_orm::make_column("COMMENT", &astro::GeneralPerturbations::COMMENT),
            sqlite_orm::make_column("COUNTRY_CODE", &astro::GeneralPerturbations::COUNTRY_CODE),
            sqlite_orm::make_column("CREATION_DATE", &astro::GeneralPerturbations::CREATION_DATE),
            sqlite_orm::make_column("DECAY_DATE", &astro::GeneralPerturbations::DECAY_DATE),
            sqlite_orm::make_column("ECCENTRICITY", &astro::GeneralPerturbations::ECCENTRICITY),
            sqlite_orm::make_column("ELEMENT_SET_NO", &astro::GeneralPerturbations::ELEMENT_SET_NO),
            sqlite_orm::make_column("EPHEMERIS_TYPE", &astro::GeneralPerturbations::EPHEMERIS_TYPE),
            sqlite_orm::make_column("EPOCH", &astro::GeneralPerturbations::EPOCH),
            sqlite_orm::make_column("FILE", &astro::GeneralPerturbations::FILE),
            sqlite_orm::make_column("GP_ID", &astro::GeneralPerturbations::GP_ID, sqlite_orm::unique()),
            sqlite_orm::make_column("INCLINATION", &astro::GeneralPerturbations::INCLINATION),
            sqlite_orm::make_column("LAUNCH_DATE", &astro::GeneralPerturbations::LAUNCH_DATE),
            sqlite_orm::make_column("MEAN_ANOMALY", &astro::GeneralPerturbations::MEAN_ANOMALY),
            sqlite_orm::make_column("MEAN_ELEMENT_THEORY", &astro::GeneralPerturbations::MEAN_ELEMENT_THEORY),
            sqlite_orm::make_column("MEAN_MOTION", &astro::GeneralPerturbations::MEAN_MOTION),
            sqlite_orm::make_column("MEAN_MOTION_DDOT", &astro::GeneralPerturbations::MEAN_MOTION_DDOT),
            sqlite_orm::make_column("MEAN_MOTION_DOT", &astro::GeneralPerturbations::MEAN_MOTION_DOT),
            sqlite_orm::make_column("NORAD_CAT_ID", &astro::GeneralPerturbations::NORAD_CAT_ID, sqlite_orm::unique()),
            sqlite_orm::make_column("OBJECT_ID", &astro::GeneralPerturbations::OBJECT_ID),
            sqlite_orm::make_column("OBJECT_NAME", &astro::GeneralPerturbations::OBJECT_NAME),
            sqlite_orm::make_column("OBJECT_TYPE", &astro::GeneralPerturbations::OBJECT_TYPE),
            sqlite_orm::make_column("ORIGINATOR", &astro::GeneralPerturbations::ORIGINATOR),
            sqlite_orm::make_column("PERIAPSIS", &astro::GeneralPerturbations::PERIAPSIS),
            sqlite_orm::make_column("PERIOD", &astro::GeneralPerturbations::PERIOD),
            sqlite_orm::make_column("RA_OF_ASC_NODE", &astro::GeneralPerturbations::RA_OF_ASC_NODE),
            sqlite_orm::make_column("RCS_SIZE", &astro::GeneralPerturbations::RCS_SIZE),
            sqlite_orm::make_column("REF_FRAME", &astro::GeneralPerturbations::REF_FRAME),
            sqlite_orm::make_column("REV_AT_EPOCH", &astro::GeneralPerturbations::REV_AT_EPOCH),
            sqlite_orm::make_column("SEMIMAJOR_AXIS", &astro::GeneralPerturbations::SEMIMAJOR_AXIS),
            sqlite_orm::make_column("SITE", &astro::GeneralPerturbations::SITE),
            sqlite_orm::make_column("TIME_SYSTEM", &astro::GeneralPerturbations::TIME_SYSTEM),
            sqlite_orm::make_column("TLE_LINE0", &astro::GeneralPerturbations::TLE_LINE0),
            sqlite_orm::make_column("TLE_LINE1", &astro::GeneralPerturbations::TLE_LINE1),
            sqlite_orm::make_column("TLE_LINE2", &astro::GeneralPerturbations::TLE_LINE2)
        )
    );
}

/**
 * @brief Creates a DatabaseUtilityWrapper for the snapshot database.
 *
 * This function creates a DatabaseUtilityWrapper instance for the snapshot database,
 * allowing easy access to GeneralPerturbations data and other database operations.
 *
 * @return A DatabaseUtilityWrapper instance wrapping the snapshot database.
 */
inline auto make_snapshot_wrapper() { return make_database(get_snapshot()); }

} // namespace snapshot
} // namespace astrea

#include <snapshot/database/Database.ipp>