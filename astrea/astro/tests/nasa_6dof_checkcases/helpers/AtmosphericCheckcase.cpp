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

#include <tests/nasa_6dof_checkcases/helpers/AtmosphericCheckcase.hpp>

#include <utilities/json_util.hpp>
#include <utilities/string_util.hpp>

namespace astrea {
namespace astro {
namespace tests {

using nlohmann::json;
using utilities::extract_from_json;
using utilities::extract_optional_from_json;
using utilities::extract_optional_string_from_json;
using utilities::extract_string_from_json;

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::optional<T>& opt)
{
    return opt ? os << opt.value() : os << "Unassigned";
}

AtmosphericCheckcase::AtmosphericCheckcase(const std::filesystem::path& filepath) :
    id(-1)
{
    // Just use the folder name
    name = filepath.parent_path().stem().string();

    // Pull the rest from the filename
    const std::string filename            = filepath.stem().string();
    const std::vector<std::string> tokens = utilities::split(filename, "_");
    checkcase_num                         = std::stoul(tokens[1]);
    sim_num                               = std::stoul(tokens[tokens.size() - 1]);
}

AtmosphericCheckcaseRow::AtmosphericCheckcaseRow(const unsigned& checkcase_num, const unsigned& sim_num, const nlohmann::json& data) :
    id(-1),
    checkcase_num(checkcase_num),
    sim_num(sim_num),
    time(extract_from_json<double>(data, "time")),
    eiPosition_ft_X(extract_optional_from_json<double>(data, "eiPosition_ft_X")),
    eiPosition_ft_Y(extract_optional_from_json<double>(data, "eiPosition_ft_Y")),
    eiPosition_ft_Z(extract_optional_from_json<double>(data, "eiPosition_ft_Z")),
    gePosition_ft_X(extract_optional_from_json<double>(data, "gePosition_ft_X")),
    gePosition_ft_Y(extract_optional_from_json<double>(data, "gePosition_ft_Y")),
    gePosition_ft_Z(extract_optional_from_json<double>(data, "gePosition_ft_Z")),
    eiVelocity_ft_s_X(extract_optional_from_json<double>(data, "eiVelocity_ft_s_X")),
    eiVelocity_ft_s_Y(extract_optional_from_json<double>(data, "eiVelocity_ft_s_Y")),
    eiVelocity_ft_s_Z(extract_optional_from_json<double>(data, "eiVelocity_ft_s_Z")),
    feVelocity_ft_s_X(extract_from_json<double>(data, "feVelocity_ft_s_X")),
    feVelocity_ft_s_Y(extract_from_json<double>(data, "feVelocity_ft_s_Y")),
    feVelocity_ft_s_Z(extract_from_json<double>(data, "feVelocity_ft_s_Z")),
    altitudeMsl_ft(extract_from_json<double>(data, "altitudeMsl_ft")),
    longitude_deg(extract_from_json<double>(data, "longitude_deg")),
    latitude_deg(extract_from_json<double>(data, "latitude_deg")),
    localGravity_ft_s2(extract_from_json<double>(data, "localGravity_ft_s2")),
    eulerAngle_deg_Yaw(extract_optional_from_json<double>(data, "eulerAngle_deg_Yaw")),
    eulerAngle_deg_Pitch(extract_optional_from_json<double>(data, "eulerAngle_deg_Pitch")),
    eulerAngle_deg_Roll(extract_optional_from_json<double>(data, "eulerAngle_deg_Roll")),
    bodyAngularVelocityWrtEi_deg_s_Roll(extract_optional_from_json<double>(data, "bodyAngularVelocityWrtEi_deg_s_Roll")),
    bodyAngularVelocityWrtEi_deg_s_Pitch(extract_optional_from_json<double>(data, "bodyAngularVelocityWrtEi_deg_s_Pitch")),
    bodyAngularVelocityWrtEi_deg_s_Yaw(extract_optional_from_json<double>(data, "bodyAngularVelocityWrtEi_deg_s_Yaw")),
    altitudeRateWrtMsl_ft_min(extract_optional_from_json<double>(data, "altitudeRateWrtMsl_ft_min")),
    speedOfSound_ft_s(extract_from_json<double>(data, "speedOfSound_ft_s")),
    airDensity_slug_ft3(extract_from_json<double>(data, "airDensity_slug_ft3")),
    ambientPressure_lbf_ft2(extract_from_json<double>(data, "ambientPressure_lbf_ft2")),
    ambientTemperature_dgR(extract_from_json<double>(data, "ambientTemperature_dgR")),
    aero_bodyForce_lbf_X(extract_from_json<double>(data, "aero_bodyForce_lbf_X")),
    aero_bodyForce_lbf_Y(extract_from_json<double>(data, "aero_bodyForce_lbf_Y")),
    aero_bodyForce_lbf_Z(extract_from_json<double>(data, "aero_bodyForce_lbf_Z")),
    aero_bodyMoment_ftlbf_L(extract_from_json<double>(data, "aero_bodyMoment_ftlbf_L")),
    aero_bodyMoment_ftlbf_M(extract_from_json<double>(data, "aero_bodyMoment_ftlbf_M")),
    aero_bodyMoment_ftlbf_N(extract_from_json<double>(data, "aero_bodyMoment_ftlbf_N")),
    mach(extract_optional_from_json<double>(data, "mach")),
    dynamicPressure_lbf_ft2(extract_optional_from_json<double>(data, "dynamicPressure_lbf_ft2")),
    trueAirspeed_nmi_h(extract_optional_from_json<double>(data, "trueAirspeed_nmi_h"))
{
}

std::ostream& operator<<(std::ostream& os, const AtmosphericCheckcaseRow& atmosphericRow)
{
    os << "id: " << atmosphericRow.id << std::endl;
    os << "checkcase_num: " << atmosphericRow.checkcase_num << std::endl;
    os << "time: " << atmosphericRow.time << std::endl;
    os << "eiPosition_ft_X: " << atmosphericRow.eiPosition_ft_X << std::endl;
    os << "eiPosition_ft_Y: " << atmosphericRow.eiPosition_ft_Y << std::endl;
    os << "eiPosition_ft_Z: " << atmosphericRow.eiPosition_ft_Z << std::endl;
    os << "gePosition_ft_X: " << atmosphericRow.gePosition_ft_X << std::endl;
    os << "gePosition_ft_Y: " << atmosphericRow.gePosition_ft_Y << std::endl;
    os << "gePosition_ft_Z: " << atmosphericRow.gePosition_ft_Z << std::endl;
    os << "eiVelocity_ft_s_X: " << atmosphericRow.eiVelocity_ft_s_X << std::endl;
    os << "eiVelocity_ft_s_Y: " << atmosphericRow.eiVelocity_ft_s_Y << std::endl;
    os << "eiVelocity_ft_s_Z: " << atmosphericRow.eiVelocity_ft_s_Z << std::endl;
    os << "feVelocity_ft_s_X: " << atmosphericRow.feVelocity_ft_s_X << std::endl;
    os << "feVelocity_ft_s_Y: " << atmosphericRow.feVelocity_ft_s_Y << std::endl;
    os << "feVelocity_ft_s_Z: " << atmosphericRow.feVelocity_ft_s_Z << std::endl;
    os << "altitudeMsl_ft: " << atmosphericRow.altitudeMsl_ft << std::endl;
    os << "longitude_deg: " << atmosphericRow.longitude_deg << std::endl;
    os << "latitude_deg: " << atmosphericRow.latitude_deg << std::endl;
    os << "localGravity_ft_s2: " << atmosphericRow.localGravity_ft_s2 << std::endl;
    os << "eulerAngle_deg_Yaw: " << atmosphericRow.eulerAngle_deg_Yaw << std::endl;
    os << "eulerAngle_deg_Pitch: " << atmosphericRow.eulerAngle_deg_Pitch << std::endl;
    os << "eulerAngle_deg_Roll: " << atmosphericRow.eulerAngle_deg_Roll << std::endl;
    os << "bodyAngularVelocityWrtEi_deg_s_Roll: " << atmosphericRow.bodyAngularVelocityWrtEi_deg_s_Roll << std::endl;
    os << "bodyAngularVelocityWrtEi_deg_s_Pitch: " << atmosphericRow.bodyAngularVelocityWrtEi_deg_s_Pitch << std::endl;
    os << "bodyAngularVelocityWrtEi_deg_s_Yaw: " << atmosphericRow.bodyAngularVelocityWrtEi_deg_s_Yaw << std::endl;
    os << "altitudeRateWrtMsl_ft_min: " << atmosphericRow.altitudeRateWrtMsl_ft_min << std::endl;
    os << "speedOfSound_ft_s: " << atmosphericRow.speedOfSound_ft_s << std::endl;
    os << "airDensity_slug_ft3: " << atmosphericRow.airDensity_slug_ft3 << std::endl;
    os << "ambientPressure_lbf_ft2: " << atmosphericRow.ambientPressure_lbf_ft2 << std::endl;
    os << "ambientTemperature_dgR: " << atmosphericRow.ambientTemperature_dgR << std::endl;
    os << "aero_bodyForce_lbf_X: " << atmosphericRow.aero_bodyForce_lbf_X << std::endl;
    os << "aero_bodyForce_lbf_Y: " << atmosphericRow.aero_bodyForce_lbf_Y << std::endl;
    os << "aero_bodyForce_lbf_Z: " << atmosphericRow.aero_bodyForce_lbf_Z << std::endl;
    os << "aero_bodyMoment_ftlbf_L: " << atmosphericRow.aero_bodyMoment_ftlbf_L << std::endl;
    os << "aero_bodyMoment_ftlbf_M: " << atmosphericRow.aero_bodyMoment_ftlbf_M << std::endl;
    os << "aero_bodyMoment_ftlbf_N: " << atmosphericRow.aero_bodyMoment_ftlbf_N << std::endl;
    os << "mach: " << atmosphericRow.mach << std::endl;
    os << "dynamicPressure_lbf_ft2: " << atmosphericRow.dynamicPressure_lbf_ft2 << std::endl;
    os << "trueAirspeed_nmi_h: " << atmosphericRow.trueAirspeed_nmi_h << std::endl;

    return os;
}

} // namespace tests
} // namespace astro
} // namespace astrea