/*
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/frames/FrameReference.hpp>

#include <mp-units/systems/si.h>

#include <units/typedefs.hpp>

#include <astro/frames/CartesianVector.hpp>


namespace astrea {
namespace astro {


AccelerationVector<frames::earth::icrf> FrameReference::get_inertial_acceleration(const Date& date) const
{
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;
    return AccelerationVector<frames::earth::icrf>{ 0.0 * km / s / s, 0.0 * km / s / s, 0.0 * km / s / s };
};


} // namespace astro
} // namespace astrea