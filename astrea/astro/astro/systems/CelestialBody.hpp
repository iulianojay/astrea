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
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/Frame.hpp>
#include <astro/frames/Origin.hpp>
#include <astro/systems/CelestialBodyParameters.hpp>
#include <astro/systems/system_concepts.hpp>
#include <astro/time/Date.hpp>

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
    static constexpr auto parent_icrf =
        Frame<_name_ + "_icrf", _parent_, axes::icrf>{}; //!< The inertial frame centered on the parent body, used for ephemeris data.
    static constexpr auto parent_j2000 =
        Frame<_name_ + "_j2000", _parent_, axes::j2000>{}; //!< The inertial frame centered on the parent body, used for ephemeris data.
};


/**
 * @brief CelestialBody class represents a celestial body in an astrodynamics system.
 */
template <mp_units::basic_fixed_string _name_, IsOrigin auto _parent_>
struct CelestialBody : Origin<_name_, _parent_> {
    static constexpr auto parent_icrf =
        Frame<_name_ + "_icrf", _parent_, axes::icrf>{}; //!< The inertial frame centered on the parent body, used for ephemeris data.
    static constexpr auto parent_j2000 =
        Frame<_name_ + "_j2000", _parent_, axes::j2000>{}; //!< The inertial frame centered on the parent body, used for ephemeris data.
};

// ---------------------------------------------------------------------------
// Primary template declarations.
// These live here (not in celestial_body_utilities.hpp) so that planet headers
// can specialise them without triggering the heavy State/Keplerian/frames include
// chain that celestial_body_utilities.hpp used to pull in.
// ---------------------------------------------------------------------------

/// Primary template — must be specialised for each body.
template <IsCelestialBody auto _body_>
constexpr CelestialBodyParameters get_celestial_body_parameters() = delete;

/// Primary template for atmospheric density — returns zero by default.
/// State is only forward-declared here; specialisations with bodies live in
/// atmospheric_density_specializations.hpp which can safely include State.hpp.
template <IsCelestialBody auto _body_>
inline Density find_atmospheric_density(const State& state)
{
    return Density::zero();
}

/// Primary templates for ephemeris position/velocity (NTTP-based, auto return).
/// Specialisations are defined in ephemeris_specializations.hpp.
template <IsOrigin auto _body_>
constexpr auto get_position_at(const Date& date) = delete;

template <IsOrigin auto _body_>
constexpr auto get_velocity_at(const Date& date) = delete;

} // namespace astro
} // namespace astrea

// celestial_body_utilities.hpp provides lightweight inline helpers (get_mu, get_mass, etc.)
// and get_position_at_impl / get_velocity_at_impl.  It is lightweight — no State.hpp dependency.
#include <astro/systems/celestial_body_utilities.hpp>
