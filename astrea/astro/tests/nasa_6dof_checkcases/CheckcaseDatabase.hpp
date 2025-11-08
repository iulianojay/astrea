/**
 * @file CheckcaseDatabase.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Database utility wrapper for astro testing
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
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

#include <tests/nasa_6dof_checkcases/AtmosphericCheckcase.hpp>
#include <tests/nasa_6dof_checkcases/OrbitalCheckcase.hpp>

namespace astrea {
namespace astro {
namespace tests {

/**
 * @brief Database utility wrapper for the snapshot module.
 *
 * This class provides a wrapper around the SQLite database used in the snapshot module,
 * allowing for easy access to AtmosphericCheckcaseRow data and other database operations.
 *
 * @tparam T The type of the database (e.g., sqlite_orm::Storage<AtmosphericCheckcaseRow>).
 */
template <class T>
class CheckcaseDatabaseUtilityWrapper {
  public:
    /**
     * @brief Default constructor for CheckcaseDatabaseUtilityWrapper.
     *
     * Initializes the CheckcaseDatabaseUtilityWrapper with the provided database instance.
     *
     * @param db The database instance to wrap.
     */
    CheckcaseDatabaseUtilityWrapper(T&& db) :
        _database(db)
    {
    }

    /**
     * @brief Default destructor for CheckcaseDatabaseUtilityWrapper.
     */
    ~CheckcaseDatabaseUtilityWrapper() = default;

    /**
     * @brief Gets the underlying database instance.
     *
     * @return A reference to the wrapped database instance.
     */
    const T& get_database() const;

    /**
     * @brief Gets all AtmosphericCheckcaseRow records from the database.
     *
     * @tparam Args Types of the optional arguments.
     * @param args Optional arguments to pass to the database query.
     * @return A vector containing all AtmosphericCheckcaseRow records.
     */
    template <typename... Args>
    std::vector<AtmosphericCheckcaseRow> get_all(Args&&... args) const;

    /**
     * @brief Gets all OrbitalCheckcaseRow records from the database.
     *
     * @tparam Args Types of the optional arguments.
     * @param args Optional arguments to pass to the database query.
     * @return A vector containing all OrbitalCheckcaseRow records.
     */
    template <typename... Args>
    std::vector<OrbitalCheckcaseRow> get_all(Args&&... args) const;

  private:
    T _database; //!< The wrapped database instance.
};

/**
 * @brief Creates a CheckcaseDatabaseUtilityWrapper instance for the given database.
 *
 * This function is a convenience wrapper to create a CheckcaseDatabaseUtilityWrapper
 * for the provided database instance.
 *
 * @tparam T The type of the database (e.g., sqlite_orm::Storage<AtmosphericCheckcaseRow>).
 * @param database The database instance to wrap.
 * @return A CheckcaseDatabaseUtilityWrapper instance wrapping the provided database.
 */
template <typename T>
CheckcaseDatabaseUtilityWrapper<typename std::decay<T>::type> make_database(T&& database)
{
    return CheckcaseDatabaseUtilityWrapper<typename std::decay<T>::type>{ std::forward<T>(database) };
}

/**
 * @brief Gets the checkcase database instance.
 *
 * This function creates and returns a SQLite storage instance for the checkcase database.
 *
 * @return A sqlite_orm::Storage instance configured for the checkcase database.
 */
inline auto get_checkcase_database()
{
    static const std::string root = std::getenv("ASTREA_ROOT");
    return sqlite_orm::make_storage(
        root + "/astrea/astro/tests/data/nasa_6dof_checkcases/checkcases/checkcases.db",
        sqlite_orm::make_table(
            "AtmosphericCheckcaseRows",
            sqlite_orm::make_column("id", &AtmosphericCheckcaseRow::id, sqlite_orm::primary_key().autoincrement()),
            sqlite_orm::make_column("checkcase_id", &AtmosphericCheckcaseRow::checkcase_id),
            sqlite_orm::make_column("time", &AtmosphericCheckcaseRow::time),
            sqlite_orm::make_column("eiPosition_ft_X", &AtmosphericCheckcaseRow::eiPosition_ft_X),
            sqlite_orm::make_column("eiPosition_ft_Y", &AtmosphericCheckcaseRow::eiPosition_ft_Y),
            sqlite_orm::make_column("eiPosition_ft_Z", &AtmosphericCheckcaseRow::eiPosition_ft_Z),
            sqlite_orm::make_column("gePosition_ft_X", &AtmosphericCheckcaseRow::gePosition_ft_X),
            sqlite_orm::make_column("gePosition_ft_Y", &AtmosphericCheckcaseRow::gePosition_ft_Y),
            sqlite_orm::make_column("gePosition_ft_Z", &AtmosphericCheckcaseRow::gePosition_ft_Z),
            sqlite_orm::make_column("eiVelocity_ft_s_X", &AtmosphericCheckcaseRow::eiVelocity_ft_s_X),
            sqlite_orm::make_column("eiVelocity_ft_s_Y", &AtmosphericCheckcaseRow::eiVelocity_ft_s_Y),
            sqlite_orm::make_column("eiVelocity_ft_s_Z", &AtmosphericCheckcaseRow::eiVelocity_ft_s_Z),
            sqlite_orm::make_column("feVelocity_ft_s_X", &AtmosphericCheckcaseRow::feVelocity_ft_s_X),
            sqlite_orm::make_column("feVelocity_ft_s_Y", &AtmosphericCheckcaseRow::feVelocity_ft_s_Y),
            sqlite_orm::make_column("feVelocity_ft_s_Z", &AtmosphericCheckcaseRow::feVelocity_ft_s_Z),
            sqlite_orm::make_column("altitudeMsl_ft", &AtmosphericCheckcaseRow::altitudeMsl_ft),
            sqlite_orm::make_column("longitude_deg", &AtmosphericCheckcaseRow::longitude_deg),
            sqlite_orm::make_column("latitude_deg", &AtmosphericCheckcaseRow::latitude_deg),
            sqlite_orm::make_column("localGravity_ft_s2", &AtmosphericCheckcaseRow::localGravity_ft_s2),
            sqlite_orm::make_column("eulerAngle_deg_Yaw", &AtmosphericCheckcaseRow::eulerAngle_deg_Yaw),
            sqlite_orm::make_column("eulerAngle_deg_Pitch", &AtmosphericCheckcaseRow::eulerAngle_deg_Pitch),
            sqlite_orm::make_column("eulerAngle_deg_Roll", &AtmosphericCheckcaseRow::eulerAngle_deg_Roll),
            sqlite_orm::make_column("bodyAngularRateWrtEi_deg_s_Roll", &AtmosphericCheckcaseRow::bodyAngularRateWrtEi_deg_s_Roll),
            sqlite_orm::make_column("bodyAngularRateWrtEi_deg_s_Pitch", &AtmosphericCheckcaseRow::bodyAngularRateWrtEi_deg_s_Pitch),
            sqlite_orm::make_column("bodyAngularRateWrtEi_deg_s_Yaw", &AtmosphericCheckcaseRow::bodyAngularRateWrtEi_deg_s_Yaw),
            sqlite_orm::make_column("altitudeRateWrtMsl_ft_min", &AtmosphericCheckcaseRow::altitudeRateWrtMsl_ft_min),
            sqlite_orm::make_column("speedOfSound_ft_s", &AtmosphericCheckcaseRow::speedOfSound_ft_s),
            sqlite_orm::make_column("airDensity_slug_ft3", &AtmosphericCheckcaseRow::airDensity_slug_ft3),
            sqlite_orm::make_column("ambientPressure_lbf_ft2", &AtmosphericCheckcaseRow::ambientPressure_lbf_ft2),
            sqlite_orm::make_column("ambientTemperature_dgR", &AtmosphericCheckcaseRow::ambientTemperature_dgR),
            sqlite_orm::make_column("aero_bodyForce_lbf_X", &AtmosphericCheckcaseRow::aero_bodyForce_lbf_X),
            sqlite_orm::make_column("aero_bodyForce_lbf_Y", &AtmosphericCheckcaseRow::aero_bodyForce_lbf_Y),
            sqlite_orm::make_column("aero_bodyForce_lbf_Z", &AtmosphericCheckcaseRow::aero_bodyForce_lbf_Z),
            sqlite_orm::make_column("aero_bodyMoment_ftlbf_L", &AtmosphericCheckcaseRow::aero_bodyMoment_ftlbf_L),
            sqlite_orm::make_column("aero_bodyMoment_ftlbf_M", &AtmosphericCheckcaseRow::aero_bodyMoment_ftlbf_M),
            sqlite_orm::make_column("aero_bodyMoment_ftlbf_N", &AtmosphericCheckcaseRow::aero_bodyMoment_ftlbf_N),
            sqlite_orm::make_column("mach", &AtmosphericCheckcaseRow::mach),
            sqlite_orm::make_column("dynamicPressure_lbf_ft2", &AtmosphericCheckcaseRow::dynamicPressure_lbf_ft2),
            sqlite_orm::make_column("trueAirspeed_nmi_h", &AtmosphericCheckcaseRow::trueAirspeed_nmi_h)
        ),
        sqlite_orm::make_table(
            "OrbitalCheckcaseRows",
            sqlite_orm::make_column("id", &OrbitalCheckcaseRow::id, sqlite_orm::primary_key().autoincrement()),
            sqlite_orm::make_column("checkcase_id", &OrbitalCheckcaseRow::checkcase_id),
            sqlite_orm::make_column("time", &OrbitalCheckcaseRow::time),
            sqlite_orm::make_column("gePosition_m_X", &OrbitalCheckcaseRow::gePosition_m_X),
            sqlite_orm::make_column("gePosition_m_Y", &OrbitalCheckcaseRow::gePosition_m_Y),
            sqlite_orm::make_column("gePosition_m_Z", &OrbitalCheckcaseRow::gePosition_m_Z),
            sqlite_orm::make_column("eiPosition_m_X", &OrbitalCheckcaseRow::eiPosition_m_X),
            sqlite_orm::make_column("eiPosition_m_Y", &OrbitalCheckcaseRow::eiPosition_m_Y),
            sqlite_orm::make_column("eiPosition_m_Z", &OrbitalCheckcaseRow::eiPosition_m_Z),
            sqlite_orm::make_column("eiVelocity_m_s_X", &OrbitalCheckcaseRow::eiVelocity_m_s_X),
            sqlite_orm::make_column("eiVelocity_m_s_Y", &OrbitalCheckcaseRow::eiVelocity_m_s_Y),
            sqlite_orm::make_column("eiVelocity_m_s_Z", &OrbitalCheckcaseRow::eiVelocity_m_s_Z),
            sqlite_orm::make_column("eiAccel_m_s2_X", &OrbitalCheckcaseRow::eiAccel_m_s2_X),
            sqlite_orm::make_column("eiAccel_m_s2_Y", &OrbitalCheckcaseRow::eiAccel_m_s2_Y),
            sqlite_orm::make_column("eiAccel_m_s2_Z", &OrbitalCheckcaseRow::eiAccel_m_s2_Z),
            sqlite_orm::make_column("semiMajorAxis_m", &OrbitalCheckcaseRow::semiMajorAxis_m),
            sqlite_orm::make_column("gast_rad", &OrbitalCheckcaseRow::gast_rad),
            sqlite_orm::make_column("eulerAngle_rad_Roll", &OrbitalCheckcaseRow::eulerAngle_rad_Roll),
            sqlite_orm::make_column("eulerAngle_rad_Pitch", &OrbitalCheckcaseRow::eulerAngle_rad_Pitch),
            sqlite_orm::make_column("eulerAngle_rad_Yaw", &OrbitalCheckcaseRow::eulerAngle_rad_Yaw),
            sqlite_orm::make_column("eulerAngleWrtEi_rad_Roll", &OrbitalCheckcaseRow::eulerAngleWrtEi_rad_Roll),
            sqlite_orm::make_column("eulerAngleWrtEi_rad_Pitch", &OrbitalCheckcaseRow::eulerAngleWrtEi_rad_Pitch),
            sqlite_orm::make_column("eulerAngleWrtEi_rad_Yaw", &OrbitalCheckcaseRow::eulerAngleWrtEi_rad_Yaw),
            sqlite_orm::make_column("bodyAngularRateWrtEi_rad_s_Roll", &OrbitalCheckcaseRow::bodyAngularRateWrtEi_rad_s_Roll),
            sqlite_orm::make_column("bodyAngularRateWrtEi_rad_s_Pitch", &OrbitalCheckcaseRow::bodyAngularRateWrtEi_rad_s_Pitch),
            sqlite_orm::make_column("bodyAngularRateWrtEi_rad_s_Yaw", &OrbitalCheckcaseRow::bodyAngularRateWrtEi_rad_s_Yaw),
            sqlite_orm::make_column("altitudeMsl_m", &OrbitalCheckcaseRow::altitudeMsl_m),
            sqlite_orm::make_column("airDensity_kg_m3", &OrbitalCheckcaseRow::airDensity_kg_m3),
            sqlite_orm::make_column("ambientTemperature_dgK", &OrbitalCheckcaseRow::ambientTemperature_dgK),
            sqlite_orm::make_column("eiGravitation_m_s2_X", &OrbitalCheckcaseRow::eiGravitation_m_s2_X),
            sqlite_orm::make_column("eiGravitation_m_s2_Y", &OrbitalCheckcaseRow::eiGravitation_m_s2_Y),
            sqlite_orm::make_column("eiGravitation_m_s2_Z", &OrbitalCheckcaseRow::eiGravitation_m_s2_Z)
        ),
        sqlite_orm::make_table(
            "AtmosphericCheckcases",
            sqlite_orm::make_column("id", &AtmosphericCheckcase::id, sqlite_orm::primary_key().autoincrement()),
            sqlite_orm::make_column("checkcase_num", &AtmosphericCheckcase::checkcase_num),
            sqlite_orm::make_column("sim_num", &AtmosphericCheckcase::sim_num),
            sqlite_orm::make_column("name", &AtmosphericCheckcase::name)
        ),
        sqlite_orm::make_table(
            "OrbitalCheckcases",
            sqlite_orm::make_column("id", &OrbitalCheckcase::id, sqlite_orm::primary_key().autoincrement()),
            sqlite_orm::make_column("checkcase_num", &OrbitalCheckcase::checkcase_num),
            sqlite_orm::make_column("sim_num", &OrbitalCheckcase::sim_num),
            sqlite_orm::make_column("name", &OrbitalCheckcase::name)
        )
    );
}

/**
 * @brief Creates a CheckcaseDatabaseUtilityWrapper for the snapshot database.
 *
 * This function creates a CheckcaseDatabaseUtilityWrapper instance for the snapshot database,
 * allowing easy access to AtmosphericCheckcaseRow data and other database operations.
 *
 * @return A CheckcaseDatabaseUtilityWrapper instance wrapping the snapshot database.
 */
inline auto make_checkcase_database_wrapper() { return make_database(get_checkcase_database()); }

} // namespace tests
} // namespace astro
} // namespace astrea

#include <tests/nasa_6dof_checkcases/CheckcaseDatabase.ipp>