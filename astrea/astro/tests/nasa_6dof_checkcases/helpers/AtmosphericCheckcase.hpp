/**
 * @file AtmosphericCheckcaseRow.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief AtmosphericCheckcaseRow data structure for the astro module
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

#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include <units/typedefs.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {
namespace tests {

/**
 * @brief Definition for a force quantity.
 *
 * @note: We put this here to avoid conflicts with abstract Force class in astro
 */
using Force = mp_units::quantity<astrea::detail::force_unit>;

/**
 * @brief AtmosphericCheckcase structure representing a NASA 6DOF atmospheric checkcase.
 */
struct AtmosphericCheckcase {

    /**
     * @brief Default constructor for AtmosphericCheckcase.
     */
    AtmosphericCheckcase() = default;

    /**
     * @brief Constructor that initializes AtmosphericCheckcase from a file.
     *
     * @param filepath The path to the file containing the checkcase data.
     */
    AtmosphericCheckcase(const std::filesystem::path& filepath);

    /**
     * @brief Default destructor for AtmosphericCheckcase.
     */
    ~AtmosphericCheckcase() = default;

    unsigned id;            //!< Database ID
    unsigned checkcase_num; //!< Checkcase number
    unsigned sim_num;       //!< Simulation number
    std::string name;       //!< Checkcase name
};

/**
 * @brief AtmosphericCheckcaseRow structure representing a single row from the NASA 6DOF atmospheric checkcases.
 */
struct AtmosphericCheckcaseRow {

    /**
     * @brief Default constructor for AtmosphericCheckcaseRow.
     */
    AtmosphericCheckcaseRow() = default;

    /**
     * @brief Constructor that initializes AtmosphericCheckcaseRow from a JSON object.
     *
     * @param data The JSON object containing the checkcase row data.
     */
    AtmosphericCheckcaseRow(const unsigned& checkcase_num, const unsigned& sim_num, const nlohmann::json& data);

    /**
     * @brief Default destructor for AtmosphericCheckcaseRow.
     */
    ~AtmosphericCheckcaseRow() = default;

    int id;                                     //!< Database ID for the checkcase row
    unsigned checkcase_num;                     //!< Checkcase database ID
    unsigned sim_num;                           //!< Simulation number
    double time;                                //!< Time in seconds??
    std::optional<double> eiPosition_ft_X;      //!< Earth-inertial position X in feet
    std::optional<double> eiPosition_ft_Y;      //!< Earth-inertial position Y in feet
    std::optional<double> eiPosition_ft_Z;      //!< Earth-inertial position Z in feet
    std::optional<double> gePosition_ft_X;      //!< Geodetic position X in feet
    std::optional<double> gePosition_ft_Y;      //!< Geodetic position Y in feet
    std::optional<double> gePosition_ft_Z;      //!< Geodetic position Z in feet
    std::optional<double> eiVelocity_ft_s_X;    //!< Earth-inertial velocity X in feet/second
    std::optional<double> eiVelocity_ft_s_Y;    //!< Earth-inertial velocity Y in feet/second
    std::optional<double> eiVelocity_ft_s_Z;    //!< Earth-inertial velocity Z in feet/second
    double feVelocity_ft_s_X;                   //!< Geodetic velocity X in feet/second
    double feVelocity_ft_s_Y;                   //!< Geodetic velocity Y in feet/second
    double feVelocity_ft_s_Z;                   //!< Geodetic velocity Z in feet/second
    double altitudeMsl_ft;                      //!< Altitude above mean sea level in feet
    double longitude_deg;                       //!< Longitude in degrees
    double latitude_deg;                        //!< Latitude in degrees
    double localGravity_ft_s2;                  //!< Local gravity in feet/second^2
    std::optional<double> eulerAngle_deg_Yaw;   //!< Yaw angle in degrees
    std::optional<double> eulerAngle_deg_Pitch; //!< Pitch angle in degrees
    std::optional<double> eulerAngle_deg_Roll;  //!< Roll angle in degrees
    std::optional<double> bodyAngularVelocityWrtEi_deg_s_Roll; //!< Body angular rate with respect to Earth-inertial frame (Roll) in degrees/second
    std::optional<double> bodyAngularVelocityWrtEi_deg_s_Pitch; //!< Body angular rate with respect to Earth-inertial frame (Pitch) in degrees/second
    std::optional<double> bodyAngularVelocityWrtEi_deg_s_Yaw; //!< Body angular rate with respect to Earth-inertial frame (Yaw) in degrees/second
    std::optional<double> altitudeRateWrtMsl_ft_min; //!< Altitude rate with respect to mean sea level in feet/minute
    double speedOfSound_ft_s;                        //!< Speed of sound in feet/second
    double airDensity_slug_ft3;                      //!< Air density in slugs/ft^3
    double ambientPressure_lbf_ft2;                  //!< Ambient pressure in pounds-force/ft^2
    double ambientTemperature_dgR;                   //!< Ambient temperature in degrees Rankine
    double aero_bodyForce_lbf_X;                     //!< Aerodynamic body force X in pounds-force
    double aero_bodyForce_lbf_Y;                     //!< Aerodynamic body force Y in pounds-force
    double aero_bodyForce_lbf_Z;                     //!< Aerodynamic body force Z in pounds-force
    double aero_bodyMoment_ftlbf_L;                  //!< Aerodynamic body moment L in foot-pounds-force
    double aero_bodyMoment_ftlbf_M;                  //!< Aerodynamic body moment M in foot-pounds-force
    double aero_bodyMoment_ftlbf_N;                  //!< Aerodynamic body moment N in foot-pounds-force
    std::optional<double> mach;                      //!< Mach number
    std::optional<double> dynamicPressure_lbf_ft2;   //!< Dynamic pressure in pounds-force/ft^2
    std::optional<double> trueAirspeed_nmi_h;        //!< True airspeed in nautical miles/hour
};

/**
 * @brief Overloaded output stream operator for AtmosphericCheckcaseRow.
 *
 * This function allows printing the contents of a AtmosphericCheckcaseRow object to an output stream.
 *
 * @param os The output stream to write to.
 * @param checkcase The AtmosphericCheckcaseRow object to print.
 * @return The output stream after writing the GP data.
 */
std::ostream& operator<<(std::ostream& os, const AtmosphericCheckcaseRow& checkcase);

} // namespace tests
} // namespace astro
} // namespace astrea
