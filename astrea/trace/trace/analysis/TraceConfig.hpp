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

#include <nlohmann/json.hpp>

namespace astrea {
namespace trace {

/**
 * @brief Configuration for a trace analysis run.
 *
 * All parameters have sensible defaults that replicate the original hard-coded behaviour.
 * The struct can be constructed from a JSON object whose keys follow snake_case field names
 * (see the explicit constructor below).  Any key absent from the JSON retains its default.
 */
struct TraceConfig {
    // Simulation timing
    double simTimeDays   = 30.0;
    double resolutionMin = 1.0;

    // Constellation (3-shell Walker)
    double altitudeKm          = 560.0;
    double inclinationDeg      = 97.6316;
    std::size_t nSats          = 4; ///< Satellites per plane per shell
    std::size_t nPlanes        = 4; ///< Planes per shell
    double anchorRaanDeg       = 20.0;
    double crossTrackOffsetDeg = 7.39; ///< RAAN offset between shells 1 and 2
    double phasingDeg          = 7.39; ///< True-anomaly phasing between shells

    // Sensor
    double fovHalfAngleDeg = 30.0;

    // Ground grid
    double gridSpacingDeg = 5.0;
    double llLon          = -180.0; ///< Lower-left  longitude  (LatLon second arg)
    double llLat          = -90.0;  ///< Lower-left  latitude   (LatLon first  arg)
    double urLon          = 180.0;  ///< Upper-right longitude
    double urLat          = 90.0;   ///< Upper-right latitude

    // Output  (used by the trace driver binary; ignored by the library analysis code)
    std::string outdir = ""; ///< Empty → <TRACE_ROOT>/trace/drivers/results/global
    std::string dbName = "analysis.db";

    // Flags  (driver-level; ignored by the library analysis code)
    bool printProgress = true;
    bool runPlotter    = true;
    bool saveResults   = true;

    TraceConfig() = default;

    /**
     * @brief Construct a TraceConfig from a JSON object.
     *
     * Every key is optional; missing keys keep the default value.
     *
     * | JSON key                | Field                  |
     * |-------------------------|------------------------|
     * | sim_time_days           | simTimeDays            |
     * | resolution_min          | resolutionMin          |
     * | altitude_km             | altitudeKm             |
     * | inclination_deg         | inclinationDeg         |
     * | n_sats                  | nSats                  |
     * | n_planes                | nPlanes                |
     * | anchor_raan_deg         | anchorRaanDeg          |
     * | cross_track_offset_deg  | crossTrackOffsetDeg    |
     * | phasing_deg             | phasingDeg             |
     * | fov_half_angle_deg      | fovHalfAngleDeg        |
     * | grid_spacing_deg        | gridSpacingDeg         |
     * | ll_lon                  | llLon                  |
     * | ll_lat                  | llLat                  |
     * | ur_lon                  | urLon                  |
     * | ur_lat                  | urLat                  |
     * | outdir                  | outdir                 |
     * | db_name                 | dbName                 |
     * | print_progress          | printProgress          |
     * | run_plotter             | runPlotter             |
     * | save_results            | saveResults            |
     */
    explicit TraceConfig(const nlohmann::json& json)
    {
        simTimeDays         = json.value("sim_time_days", simTimeDays);
        resolutionMin       = json.value("resolution_min", resolutionMin);
        altitudeKm          = json.value("altitude_km", altitudeKm);
        inclinationDeg      = json.value("inclination_deg", inclinationDeg);
        nSats               = json.value("n_sats", nSats);
        nPlanes             = json.value("n_planes", nPlanes);
        anchorRaanDeg       = json.value("anchor_raan_deg", anchorRaanDeg);
        crossTrackOffsetDeg = json.value("cross_track_offset_deg", crossTrackOffsetDeg);
        phasingDeg          = json.value("phasing_deg", phasingDeg);
        fovHalfAngleDeg     = json.value("fov_half_angle_deg", fovHalfAngleDeg);
        gridSpacingDeg      = json.value("grid_spacing_deg", gridSpacingDeg);
        llLon               = json.value("ll_lon", llLon);
        llLat               = json.value("ll_lat", llLat);
        urLon               = json.value("ur_lon", urLon);
        urLat               = json.value("ur_lat", urLat);
        outdir              = json.value("outdir", outdir);
        dbName              = json.value("db_name", dbName);
        printProgress       = json.value("print_progress", printProgress);
        runPlotter          = json.value("run_plotter", runPlotter);
        saveResults         = json.value("save_results", saveResults);
    }
};

} // namespace trace
} // namespace astrea
