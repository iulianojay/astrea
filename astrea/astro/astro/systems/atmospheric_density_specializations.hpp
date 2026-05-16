/**
 * @file atmospheric_density_specializations.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Explicit specialisations of find_atmospheric_density<body>(state) for all bodies with atmospheres.
 * @details This file is intentionally separate from the planet headers because it requires
 *          State.hpp (which pulls in frames.hpp) while the planet headers must remain
 *          lightweight to avoid circular includes during frame-system initialisation.
 *          Include this file only from a high-level aggregator that is processed AFTER
 *          all frame definitions are complete (e.g. system_utilities.hpp or astro.hpp).
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the
 * GNU Lesser General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details. You should have received a
 * copy of the GNU General Public License along with Astrea.
 * If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

#include <units/units.hpp>

#include <astro/state/State.hpp>
#include <astro/state/angular_elements/instances/Geodetic.hpp>
#include <astro/systems/celestial_body_utilities.hpp>
#include <astro/systems/planets/Earth/Earth.hpp>
#include <astro/systems/planets/Earth/atmosphere/HarrisPriester.hpp>
#include <astro/systems/planets/Earth/atmosphere/JacciaRoberts.hpp>
#include <astro/systems/planets/Mars/Mars.hpp>
#include <astro/systems/planets/Saturn/Titan.hpp>
#include <astro/systems/planets/Venus/Venus.hpp>

namespace astrea {
namespace astro {

// ---------------------------------------------------------------------------
// Earth
// ---------------------------------------------------------------------------

/**
 * @brief Find the atmospheric density for Earth using the configured atmosphere model.
 *
 * @param state The current Cartesian state vector (position and velocity).
 * @return Density The atmospheric density at the position encoded in @p state.
 */
template <>
inline Density find_atmospheric_density<planets::Earth>(const State& state)
{
    return HarrisPriesterAtmosphere::find_atmospheric_density(state, get_equitorial_radius<planets::Earth>(), get_polar_radius<planets::Earth>());
}

// ---------------------------------------------------------------------------
// Venus
// ---------------------------------------------------------------------------

template <>
inline Density find_atmospheric_density<planets::Venus>(const State& state)
{
    const auto& position = state.get_position_in_frame<frames::venus::venus_fixed>();
    const auto [latitude, longitude, altitude] =
        convert_body_fixed_to_geodetic(position, get_equitorial_radius<planets::Venus>(), get_polar_radius<planets::Venus>());

    const auto iter = planets::venutianAtmosphere.upper_bound(altitude);
    return (iter != planets::venutianAtmosphere.end()) ? iter->second : Density::zero();
}

// ---------------------------------------------------------------------------
// Mars
// ---------------------------------------------------------------------------

template <>
inline Density find_atmospheric_density<planets::Mars>(const State& state)
{
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;

    const auto& position = state.get_position_in_frame<frames::mars::mars_fixed>();
    const auto [latitude, longitude, altitude] =
        convert_body_fixed_to_geodetic(position, get_equitorial_radius<planets::Mars>(), get_polar_radius<planets::Mars>());

    Unitless altitudeValue = altitude / astrea::detail::distance_unit;
    if (altitude <= 80.0 * km) {
        const auto iter = planets::martianAtmosphere.upper_bound(altitude);
        return (iter != planets::martianAtmosphere.end()) ? iter->second : Density::zero();
    }
    else if (altitude < 200.0 * km) {
        return exp(-2.55314e-10 * mp_units::pow<5>(altitudeValue) + 2.31927e-7 * mp_units::pow<4>(altitudeValue) -
                   8.33206e-5 * mp_units::pow<3>(altitudeValue) + 0.0151947 * mp_units::pow<2>(altitudeValue) -
                   1.52799 * altitudeValue + 48.69659) *
               kg / mp_units::pow<3>(km);
    }
    else if (altitude < 300.0 * km) {
        return exp(2.65472e-11 * mp_units::pow<5>(altitudeValue) - 2.45558e-8 * mp_units::pow<4>(altitudeValue) +
                   6.31410e-6 * mp_units::pow<3>(altitudeValue) + 4.73359e-4 * mp_units::pow<2>(altitudeValue) -
                   0.443712 * altitudeValue + 23.79408) *
               kg / mp_units::pow<3>(km);
    }
    else {
        return Density::zero();
    }
}

// ---------------------------------------------------------------------------
// Titan
// ---------------------------------------------------------------------------

template <>
inline Density find_atmospheric_density<planets::Titan>(const State& state)
{
    using mp_units::si::unit_symbols::cm;
    using mp_units::si::unit_symbols::g;

    const auto& position = state.get_position_in_frame<frames::titan::titan_fixed>();
    const auto [latitude, longitude, altitude] =
        convert_body_fixed_to_geodetic(position, get_equitorial_radius<planets::Titan>(), get_polar_radius<planets::Titan>());

    const auto iter = planets::titanicAtmosphere.upper_bound(altitude);
    return (iter != planets::titanicAtmosphere.end()) ? iter->second : 0.0 * g / (cm * cm * cm);
}

} // namespace astro
} // namespace astrea
