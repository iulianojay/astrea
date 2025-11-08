/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <tests/nasa_6dof_checkcases/OrbitalCheckcase.hpp>

#include <utilities/json_util.hpp>
#include <utilities/string_util.hpp>

namespace astrea {
namespace astro {
namespace tests {

using utilities::extract_from_json;
using utilities::extract_optional_from_json;
using utilities::extract_optional_string_from_json;
using utilities::extract_string_from_json;

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::optional<T>& opt)
{
    return opt ? os << opt.value() : os << "Unassigned";
}

OrbitalCheckcaseRow::OrbitalCheckcaseRow(const unsigned& checkcase_id, const nlohmann::json& data) :
    id(-1),
    checkcase_id(checkcase_id),
    time(extract_from_json<double>(data, "time")),
    gePosition_m_X(extract_optional_from_json<double>(data, "gePosition_m_X")),
    gePosition_m_Y(extract_optional_from_json<double>(data, "gePosition_m_Y")),
    gePosition_m_Z(extract_optional_from_json<double>(data, "gePosition_m_Z")),
    eiPosition_m_X(extract_from_json<double>(data, "eiPosition_m_X")),
    eiPosition_m_Y(extract_from_json<double>(data, "eiPosition_m_Y")),
    eiPosition_m_Z(extract_from_json<double>(data, "eiPosition_m_Z")),
    eiVelocity_m_s_X(extract_from_json<double>(data, "eiVelocity_m_s_X")),
    eiVelocity_m_s_Y(extract_from_json<double>(data, "eiVelocity_m_s_Y")),
    eiVelocity_m_s_Z(extract_from_json<double>(data, "eiVelocity_m_s_Z")),
    eiAccel_m_s2_X(extract_from_json<double>(data, "eiAccel_m_s2_X")),
    eiAccel_m_s2_Y(extract_from_json<double>(data, "eiAccel_m_s2_Y")),
    eiAccel_m_s2_Z(extract_from_json<double>(data, "eiAccel_m_s2_Z")),
    semiMajorAxis_m(extract_optional_from_json<double>(data, "semiMajorAxis_m")),
    gast_rad(extract_optional_from_json<double>(data, "gast_rad")),
    eulerAngle_rad_Roll(extract_optional_from_json<double>(data, "eulerAngle_rad_Roll")),
    eulerAngle_rad_Pitch(extract_optional_from_json<double>(data, "eulerAngle_rad_Pitch")),
    eulerAngle_rad_Yaw(extract_optional_from_json<double>(data, "eulerAngle_rad_Yaw")),
    eulerAngleWrtEi_rad_Roll(extract_optional_from_json<double>(data, "eulerAngleWrtEi_rad_Roll")),
    eulerAngleWrtEi_rad_Pitch(extract_optional_from_json<double>(data, "eulerAngleWrtEi_rad_Pitch")),
    eulerAngleWrtEi_rad_Yaw(extract_optional_from_json<double>(data, "eulerAngleWrtEi_rad_Yaw")),
    bodyAngularRateWrtEi_rad_s_Roll(extract_optional_from_json<double>(data, "bodyAngularRateWrtEi_rad_s_Roll")),
    bodyAngularRateWrtEi_rad_s_Pitch(extract_optional_from_json<double>(data, "bodyAngularRateWrtEi_rad_s_Pitch")),
    bodyAngularRateWrtEi_rad_s_Yaw(extract_optional_from_json<double>(data, "bodyAngularRateWrtEi_rad_s_Yaw")),
    altitudeMsl_m(extract_optional_from_json<double>(data, "altitudeMsl_m")),
    airDensity_kg_m3(extract_optional_from_json<double>(data, "airDensity_kg_m3")),
    ambientTemperature_dgK(extract_optional_from_json<double>(data, "ambientTemperature_dgK")),
    eiGravitation_m_s2_X(extract_from_json<double>(data, "eiGravitation_m_s2_X")),
    eiGravitation_m_s2_Y(extract_from_json<double>(data, "eiGravitation_m_s2_Y")),
    eiGravitation_m_s2_Z(extract_from_json<double>(data, "eiGravitation_m_s2_Z"))
{
}

std::ostream& operator<<(std::ostream& os, const OrbitalCheckcaseRow& orbitalRow)
{
    os << "id: " << orbitalRow.id << std::endl;
    os << "checkcase_id: " << orbitalRow.checkcase_id << std::endl;
    os << "time: " << orbitalRow.time << std::endl;
    os << "gePosition_m_X: " << orbitalRow.gePosition_m_X << std::endl;
    os << "gePosition_m_Y: " << orbitalRow.gePosition_m_Y << std::endl;
    os << "gePosition_m_Z: " << orbitalRow.gePosition_m_Z << std::endl;
    os << "eiPosition_m_X: " << orbitalRow.eiPosition_m_X << std::endl;
    os << "eiPosition_m_Y: " << orbitalRow.eiPosition_m_Y << std::endl;
    os << "eiPosition_m_Z: " << orbitalRow.eiPosition_m_Z << std::endl;
    os << "eiVelocity_m_s_X: " << orbitalRow.eiVelocity_m_s_X << std::endl;
    os << "eiVelocity_m_s_Y: " << orbitalRow.eiVelocity_m_s_Y << std::endl;
    os << "eiVelocity_m_s_Z: " << orbitalRow.eiVelocity_m_s_Z << std::endl;
    os << "eiAccel_m_s2_X: " << orbitalRow.eiAccel_m_s2_X << std::endl;
    os << "eiAccel_m_s2_Y: " << orbitalRow.eiAccel_m_s2_Y << std::endl;
    os << "eiAccel_m_s2_Z: " << orbitalRow.eiAccel_m_s2_Z << std::endl;
    os << "semiMajorAxis_m: " << orbitalRow.semiMajorAxis_m << std::endl;
    os << "gast_rad: " << orbitalRow.gast_rad << std::endl;
    os << "eulerAngle_rad_Roll: " << orbitalRow.eulerAngle_rad_Roll << std::endl;
    os << "eulerAngle_rad_Pitch: " << orbitalRow.eulerAngle_rad_Pitch << std::endl;
    os << "eulerAngle_rad_Yaw: " << orbitalRow.eulerAngle_rad_Yaw << std::endl;
    os << "eulerAngleWrtEi_rad_Roll: " << orbitalRow.eulerAngleWrtEi_rad_Roll << std::endl;
    os << "eulerAngleWrtEi_rad_Pitch: " << orbitalRow.eulerAngleWrtEi_rad_Pitch << std::endl;
    os << "eulerAngleWrtEi_rad_Yaw: " << orbitalRow.eulerAngleWrtEi_rad_Yaw << std::endl;
    os << "bodyAngularRateWrtEi_rad_s_Roll: " << orbitalRow.bodyAngularRateWrtEi_rad_s_Roll << std::endl;
    os << "bodyAngularRateWrtEi_rad_s_Pitch: " << orbitalRow.bodyAngularRateWrtEi_rad_s_Pitch << std::endl;
    os << "bodyAngularRateWrtEi_rad_s_Yaw: " << orbitalRow.bodyAngularRateWrtEi_rad_s_Yaw << std::endl;
    os << "altitudeMsl_m: " << orbitalRow.altitudeMsl_m << std::endl;
    os << "airDensity_kg_m3: " << orbitalRow.airDensity_kg_m3 << std::endl;
    os << "ambientTemperature_dgK: " << orbitalRow.ambientTemperature_dgK << std::endl;
    os << "eiGravitation_m_s2_X: " << orbitalRow.eiGravitation_m_s2_X << std::endl;
    os << "eiGravitation_m_s2_Y: " << orbitalRow.eiGravitation_m_s2_Y << std::endl;
    os << "eiGravitation_m_s2_Z: " << orbitalRow.eiGravitation_m_s2_Z << std::endl;

    return os;
}

} // namespace tests
} // namespace astro
} // namespace astrea