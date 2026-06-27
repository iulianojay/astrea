/**
 * @file TraceConfig.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for trace configuration in the astrea trace library.
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

#include <string>

#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>
#include <nlohmann/json.hpp>

#include <astro/astro.hpp>
#include <units/units.hpp>

#include <trace/types/typedefs.hpp>

namespace astrea {
namespace trace {

struct AnalysisSettings {
    Time simTime;      //!< Total simulation time
    Time resolution;   //!< Time resolution of the simulation
    astro::Date epoch; //!< Epoch of the simulation

    AnalysisSettings() = default;

    AnalysisSettings(const nlohmann::json& json)
    {
        using mp_units::non_si::day;
        using mp_units::si::unit_symbols::min;

        simTime    = json.at("sim_time_days").get<double>() * day;
        resolution = json.at("resolution_min").get<double>() * min;
        epoch      = astro::Date(json.at("epoch").get<std::string>());
    }
};

struct ConstellationSettings {
    Distance altitude;       //!< Altitude of the constellation
    Angle inclination;       //!< Inclination of the constellation
    std::size_t nSats;       //!< Number of satellites per plane
    std::size_t nPlanes;     //!< Number of planes in the constellation
    Unitless phasing;        //!< Phasing parameter for walkers
    Angle anchorRaan;        //!< Right ascension of the ascending node for the anchor satellite
    Angle anchorTrueAnomaly; //!< True anomaly of the anchor satellite

    ConstellationSettings() = default;

    ConstellationSettings(const nlohmann::json& json)
    {
        using namespace mp_units;
        using mp_units::angular::unit_symbols::deg;
        using mp_units::si::unit_symbols::km;

        altitude          = json.at("altitude_km").get<double>() * km;
        inclination       = json.at("inclination_deg").get<double>() * deg;
        nSats             = json.at("n_sats").get<std::size_t>();
        nPlanes           = json.at("n_planes").get<std::size_t>();
        phasing           = json.at("phasing").get<double>() * one;
        anchorRaan        = json.at("anchor_raan_deg").get<double>() * deg;
        anchorTrueAnomaly = json.at("anchor_true_anomaly_deg").get<double>() * deg;
    }
};

struct SensorSettings {
    std::string name;                                        //!< Name of the sensor
    std::string type;                                        //!< Type of sensor (e.g., "circular")
    Angle halfConeAngle;                                     //!< Half-angle of the sensor's field of view
    astro::Direction<astro::frames::dynamic::ric> boresight; //!< Boresight direction of the sensor in RIC

    SensorSettings() = default;

    SensorSettings(const nlohmann::json& json)
    {
        using namespace mp_units;
        using mp_units::angular::unit_symbols::deg;

        name          = json.at("name").get<std::string>();
        type          = json.at("fov").at("type").get<std::string>();
        halfConeAngle = json.at("fov").at("half_cone_angle_deg").get<double>() * deg;
        if (json.contains("boresight")) {
            const auto& boresightArray = json.at("boresight");
            if (boresightArray.is_array() && boresightArray.size() == 3) {
                boresight = astro::Direction<astro::frames::dynamic::ric>{ boresightArray[0].get<double>() * one,
                                                                           boresightArray[1].get<double>() * one,
                                                                           boresightArray[2].get<double>() * one };
            }
            else {
                throw std::runtime_error("Boresight must be an array of 3 elements.");
            }
        }
    }
};

struct GridSettings {
    std::string type;  //!< Type of grid (e.g., "uniform")
    Angle spacing;     //!< Spacing of the grid points
    LatRange latRange; //!< Latitude range of the grid
    LonRange lonRange; //!< Longitude range of the grid

    GridSettings() = default;

    GridSettings(const nlohmann::json& json)
    {
        using namespace mp_units;
        using mp_units::angular::unit_symbols::deg;

        type    = json.at("type").get<std::string>();
        spacing = json.at("spacing_deg").get<double>() * deg;
        if (json.contains("lat_range_deg") && json.at("lat_range_deg").is_array() && json.at("lat_range_deg").size() == 2) {
            latRange = LatRange{ json.at("lat_range_deg")[0].get<double>() * deg, json.at("lat_range_deg")[1].get<double>() * deg };
        }
        if (json.contains("lon_range_deg") && json.at("lon_range_deg").is_array() && json.at("lon_range_deg").size() == 2) {
            lonRange = LonRange{ json.at("lon_range_deg")[0].get<double>() * deg, json.at("lon_range_deg")[1].get<double>() * deg };
        }
    }
};

struct GroundSettings {
    GridSettings gridSettings; //!< Settings for the ground grid

    GroundSettings() = default;

    GroundSettings(const nlohmann::json& json) { gridSettings = GridSettings(json.at("grids")[0]); }
};

struct OutputSettings {
    std::string outdir; //!< Output directory for results
    std::string dbName; //!< Name of the output database
    bool printProgress; //!< Flag to print progress during analysis
    bool runPlotter;    //!< Flag to run the plotter after analysis
    bool saveResults;   //!< Flag to save results to the database

    OutputSettings() = default;

    OutputSettings(const nlohmann::json& json)
    {
        outdir        = json.at("outdir").get<std::string>();
        dbName        = json.at("db_name").get<std::string>();
        printProgress = json.at("print_progress").get<bool>();
        runPlotter    = json.at("run_plotter").get<bool>();
        saveResults   = json.at("save_results").get<bool>();
    }
};

/**
 * @brief Configuration for a trace analysis run.
 *
 * All parameters have sensible defaults that replicate the original hard-coded behaviour.
 * The struct can be constructed from a JSON object whose keys follow snake_case field names
 * (see the explicit constructor below).  Any key absent from the JSON retains its default.
 */
struct TraceConfig {
    AnalysisSettings analysisSettings;
    ConstellationSettings constellationSettings;
    SensorSettings sensorSettings;
    GroundSettings groundSettings;
    OutputSettings outputSettings;

    TraceConfig() = default;

    /**
     * @brief Construct a TraceConfig from a JSON object.
     */
    TraceConfig(const nlohmann::json& json)
    {
        analysisSettings      = AnalysisSettings(json.at("analysis"));
        constellationSettings = ConstellationSettings(json.at("constellation"));
        sensorSettings        = SensorSettings(json.at("sensors")[0]);
        groundSettings        = GroundSettings(json.at("grounds"));
        outputSettings        = OutputSettings(json.at("output"));
    }
};

} // namespace trace
} // namespace astrea
