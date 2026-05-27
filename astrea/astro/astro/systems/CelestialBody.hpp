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

#include <mp-units/framework/symbol_text.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/Axis.hpp>
#include <astro/frames/BodyFixedFrame.hpp>
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/Frame.hpp>
#include <astro/frames/Origin.hpp>
#include <astro/systems/CelestialBodyParameters.hpp>
#include <astro/systems/system_concepts.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

namespace detail {

struct CelestialBodyBase {};

} // namespace detail

// Reference axes defined by the International Reference Pole (IPM) and the International Reference Meridian (IRM).
template <mp_units::symbol_text _name_>
struct ReferenceAxes : Axis<_name_ + mp_units::symbol_text{ " reference axes" }> {};

// Geocentric axes defined by the geographic pole and meridian.
template <mp_units::symbol_text _name_>
struct GeocentricAxes : Axis<_name_ + mp_units::symbol_text{ " geocentric axes" }> {};

/**
 * @brief CelestialBody class represents a celestial body in an astrodynamics system.
 */
template <mp_units::symbol_text _name_, IsOrigin auto _parent_>
struct CelestialBody : Origin<_name_, _parent_>, detail::CelestialBodyBase {
    static constexpr ReferenceAxes<_name_> reference_axes{};
    static constexpr GeocentricAxes<_name_> geocentric_axes{};
};

// ---------------------------------------------------------------------------
// Primary template declarations.
// These live here (not in celestial_reference_getters.hpp) so that planet headers
// can specialise them without triggering the heavy State/Keplerian/frames include
// chain that celestial_reference_getters.hpp used to pull in.
// ---------------------------------------------------------------------------

/// Primary template — must be specialised for each body.
/// Uses unconstrained auto _body_ so GCC can match explicit specialisations
/// of the form get_celestial_body_parameters<planets::Earth>().
template <auto _body_>
inline consteval CelestialBodyParameters get_celestial_body_parameters() = delete;

/// Primary template for atmospheric density — returns zero by default.
template <auto _body_>
inline Density find_atmospheric_density(const State& state)
{
    return Density::zero();
}

/// Primary template declarations for ephemeris position/velocity (NTTP-based).
/// Explicit specialisations are provided in planet headers (Chebyshev ephemeris).
/// The primary template definition (Keplerian fallback) is provided by
/// celestial_reference_default_getters.hpp, which celestial_bodies.hpp includes after all planet headers.
template <auto _body_>
auto get_position_at(const Date& date);

template <auto _body_>
auto get_velocity_at(const Date& date);

} // namespace astro
} // namespace astrea

// celestial_reference_getters.hpp provides lightweight inline helpers (get_mu, get_mass, etc.)
// and get_position_at_impl / get_velocity_at_impl.  It is lightweight — no State.hpp dependency.
#include <astro/systems/celestial_reference_getters.hpp>
