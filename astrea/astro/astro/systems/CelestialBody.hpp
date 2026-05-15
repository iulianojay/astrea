/**
 * @file CelestialBody.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the CelestialBody class, which represents a celestial body in an astrodynamics system.
 * @date 2025-08-02
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

#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/Axis.hpp>
#include <astro/frames/Frame.hpp>
#include <astro/frames/Origin.hpp>

namespace astrea {
namespace astro {

namespace detail {

struct BarycenterBase {};
struct CelestialBodyBase {};

} // namespace detail

template <auto...>
struct Barycenter;

template <mp_units::basic_fixed_string _name_>
struct Barycenter<_name_> : Origin<_name_> {};

template <mp_units::basic_fixed_string _name_, IsOrigin auto _parent_>
struct Barycenter<_name_, _parent_> : Origin<_name_, _parent_> {
    using ParentIcrf = Frame<_name_ + "_icrf", _parent_, axes::icrf>; //!< The inertial frame centered on the parent body, used for ephemeris data.
    using ParentJ2000 = Frame<_name_ + "_j2000", _parent_, axes::j2000>; //!< The inertial frame centered on the parent body, used for ephemeris data.
};


/**
 * @brief CelestialBody class represents a celestial body in an astrodynamics system.
 */
template <mp_units::basic_fixed_string _name_, IsOrigin auto _parent_>
struct CelestialBody : Origin<_name_, _parent_> {
    using ParentIcrf = Frame<_name_ + "_icrf", _parent_, axes::icrf>; //!< The inertial frame centered on the parent body, used for ephemeris data.
    using ParentJ2000 = Frame<_name_ + "_j2000", _parent_, axes::j2000>; //!< The inertial frame centered on the parent body, used for ephemeris data.
};

} // namespace astro
} // namespace astrea

#include <astro/systems/celestial_body_utilities.hpp>
