/**
 * @file OrbitalCheckcase.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief OrbitalCheckcase data structure for the astro module
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

#include <astro/frames/definitions.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {
namespace tests {

/**
 * @brief OrbitalCheckcase structure representing a NASA 6DOF orbital checkcase.
 */
struct OrbitalCheckcase {

    /**
     * @brief Default constructor for OrbitalCheckcase.
     */
    OrbitalCheckcase() = default;

    /**
     * @brief Constructor that initializes OrbitalCheckcase from a file.
     *
     * @param filepath The path to the file containing the checkcase data.
     */
    OrbitalCheckcase(const std::filesystem::path& filepath);

    /**
     * @brief Default destructor for OrbitalCheckcase.
     */
    ~OrbitalCheckcase() = default;

    unsigned id;            //!< Database ID
    unsigned checkcase_num; //!< Checkcase number
    unsigned sim_num;       //!< Simulation number
    std::string name;       //!< Checkcase name
};

/**
 * @brief OrbitalCheckcaseRow structure representing a single row from the NASA 6DOF orbital checkcases.
 */
struct OrbitalCheckcaseRow {

    /**
     * @brief Default constructor for OrbitalCheckcaseRow.
     */
    OrbitalCheckcaseRow() = default;

    /**
     * @brief Constructor that initializes OrbitalCheckcaseRow from a JSON object.
     *
     * @param checkcase_num The checkcase number associated with this row.
     * @param sim_num The simulation number associated with this row.
     * @param data The JSON object containing the checkcase row data.
     */
    OrbitalCheckcaseRow(const unsigned& checkcase_num, const unsigned& sim_num, const nlohmann::json& data);

    /**
     * @brief Default destructor for OrbitalCheckcaseRow.
     */
    ~OrbitalCheckcaseRow() = default;

    int id;                                         //!< Database ID for the checkcase row
    unsigned checkcase_num;                         //!< Checkcase ID
    unsigned sim_num;                               //!< Simulation number
    double time;                                    //!< Time in seconds
    std::optional<double> gePosition_m_X;           //!< Geodetic position X in meters
    std::optional<double> gePosition_m_Y;           //!< Geodetic position Y in meters
    std::optional<double> gePosition_m_Z;           //!< Geodetic position Z in meters
    double eiPosition_m_X;                          //!< Earth inertial position X in meters
    double eiPosition_m_Y;                          //!< Earth inertial position Y in meters
    double eiPosition_m_Z;                          //!< Earth inertial position Z in meters
    double eiVelocity_m_s_X;                        //!< Earth inertial velocity X in meters per second
    double eiVelocity_m_s_Y;                        //!< Earth inertial velocity Y in meters per second
    double eiVelocity_m_s_Z;                        //!< Earth inertial velocity Z in meters per second
    double eiAccel_m_s2_X;                          //!< Earth inertial acceleration X in meters per second squared
    double eiAccel_m_s2_Y;                          //!< Earth inertial acceleration Y in meters per second squared
    double eiAccel_m_s2_Z;                          //!< Earth inertial acceleration Z in meters per second squared
    std::optional<double> semiMajorAxis_m;          //!< Semi-major axis in meters
    std::optional<double> gast_rad;                 //!< Greenwich apparent sidereal time in radians
    std::optional<double> eulerAngle_rad_Roll;      //!< Euler angle (roll) in radians
    std::optional<double> eulerAngle_rad_Pitch;     //!< Euler angle (pitch) in radians
    std::optional<double> eulerAngle_rad_Yaw;       //!< Euler angle (yaw) in radians
    std::optional<double> eulerAngleWrtEi_rad_Roll; //!< Euler angle (roll) with respect to Earth inertial frame in radians
    std::optional<double> eulerAngleWrtEi_rad_Pitch; //!< Euler angle (pitch) with respect to Earth inertial frame in radians
    std::optional<double> eulerAngleWrtEi_rad_Yaw; //!< Euler angle (yaw) with respect to Earth inertial frame in radians
    std::optional<double> bodyAngularVelocityWrtEi_rad_s_Roll; //!< Body angular rate (roll) with respect to Earth inertial frame in radians per second
    std::optional<double> bodyAngularVelocityWrtEi_rad_s_Pitch; //!< Body angular rate (pitch) with respect to Earth inertial frame in radians per second
    std::optional<double> bodyAngularVelocityWrtEi_rad_s_Yaw; //!< Body angular rate (yaw) with respect to Earth inertial frame in radians per second
    std::optional<double> altitudeMsl_m;          //!< Altitude above mean sea level in meters
    std::optional<double> airDensity_kg_m3;       //!< Air density in kilograms per cubic meter
    std::optional<double> ambientTemperature_dgK; //!< Ambient temperature in degrees Kelvin
    double eiGravitation_m_s2_X;                  //!< Earth inertial gravitation X in meters per second squared
    double eiGravitation_m_s2_Y;                  //!< Earth inertial gravitation Y in meters per second squared
    double eiGravitation_m_s2_Z;                  //!< Earth inertial gravitation Z in meters per second squared
};

/**
 * @brief Overloaded output stream operator for OrbitalCheckcaseRow.
 *
 * This function allows printing the contents of a OrbitalCheckcaseRow object to an output stream.
 *
 * @param os The output stream to write to.
 * @param orbitalRow The OrbitalCheckcaseRow object to print.
 * @return The output stream after writing the row.
 */
std::ostream& operator<<(std::ostream& os, const OrbitalCheckcaseRow& orbitalRow);

} // namespace tests
} // namespace astro
} // namespace astrea
