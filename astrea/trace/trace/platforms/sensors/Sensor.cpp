/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <trace/platforms/sensors/Sensor.hpp>

#include <astro/frames/definitions.hpp>
#include <astro/frames/definitions/dynamic_frames.hpp>
#include <astro/frames/framework/CartesianVector.hpp>

namespace astrea {
namespace trace {

bool Sensor::contains(const astro::RadiusVector<astro::frames::earth::icrf>& sensor2target, const astro::Date& date) const
{
    if (!_parameters.get_fov()) { return false; } // No FOV means no access
    const astro::RadiusVector<astro::frames::earth::icrf> parentPosition   = get_parent()->get_position(date);
    const astro::VelocityVector<astro::frames::earth::icrf> parentVelocity = get_parent()->get_velocity(date);
    const auto frame = astro::frames::dynamic::ric.instantaneous(parentPosition, parentVelocity); // RIC frame of parent
    const astro::RadiusVector<astro::frames::earth::icrf> boresightEci = // Rotate boresight from RIC to ECI frame
        frame.rotate_out_of_this_frame(_parameters.get_boresight(), date); // Don't convert to avoid re-centering of boresight
    return _parameters.get_fov()->contains(boresightEci, sensor2target); // Check if the target is within the FOV
}

} // namespace trace
} // namespace astrea