/**
 * @file trace.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the access module
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

#include <trace/analysis/access_analysis.hpp>

#include <trace/platforms/ground/Grid.hpp>
#include <trace/platforms/ground/GroundArchitecture.hpp>
#include <trace/platforms/ground/GroundPoint.hpp>
#include <trace/platforms/ground/GroundStation.hpp>

#include <trace/platforms/sensors/Antenna.hpp>
#include <trace/platforms/sensors/Sensor.hpp>
#include <trace/platforms/sensors/fov/FieldOfView.hpp>

#include <trace/platforms/vehicles/Viewer.hpp>

#include <trace/risesets/AccessArray.hpp>
#include <trace/risesets/RiseSetArray.hpp>
#include <trace/risesets/riseset_utils.hpp>

#include <trace/types/typedefs.hpp>
