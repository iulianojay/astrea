

# File Database.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**snapshot**](dir_ad01b7a66bf2103e1e551598d7ba094a.md) **>** [**snapshot**](dir_d7d302d432d8a6ab561803ec6eec1eed.md) **>** [**database**](dir_51ef3faf157d043087a4594bebbd2397.md) **>** [**Database.hpp**](Database_8hpp.md)

[Go to the documentation of this file](Database_8hpp.md)


```C++

#pragma once

#include <sqlite3.h>
#include <vector>

#include <sqlite_orm/sqlite_orm.h>

// mp-units
#include <mp-units/systems/iau.h>
#include <mp-units/systems/si.h>

#include <units/typedefs.hpp>

#include <astro/astro.macros.hpp>
#include <astro/state/orbital_data_formats/GeneralPerturbations.hpp>

#include <snapshot/snapshot.macros.hpp>

namespace astrea {
namespace snapshot {

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
    std::vector<astro::GeneralPerturbations> get_all(Args&&... args) const;

    astro::GeneralPerturbations get_sat_from_norad_id(const unsigned& id) const;

    std::vector<astro::GeneralPerturbations> get_sats_by_name(const std::string& name) const;

    std::vector<astro::GeneralPerturbations> get_sats_in_range(const Distance& minPeriapsis, const Distance& maxApoapsis) const;

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
    auto storage = sqlite_orm::make_storage(
        std::string(_SNAPSHOT_ROOT_) + "/snapshot/database/snapshot.db",
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

    // Apply SQLite performance optimizations
    try {
        storage.pragma.journal_mode(sqlite_orm::journal_mode::WAL);
    }
    catch (...) {
        // If optimizations fail, continue with defaults
    }

    return storage;
}

inline auto make_snapshot_wrapper() { return make_database(get_snapshot()); }

} // namespace snapshot
} // namespace astrea

#include <snapshot/database/Database.ipp>
```


