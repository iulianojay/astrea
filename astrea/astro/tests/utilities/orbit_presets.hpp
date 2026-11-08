/**
 * @file orbit_presets.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Shared predefined orbit preset factories for orbital element classes.
 * @date 2026-11-08
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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

#include <concepts>

#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

enum class OrbitPreset {
    LEO,
    LMEO,
    GPS,
    HMEO,
    GEO,
};

template <typename ElementSet>
inline ElementSet make_orbit_preset(const OrbitPreset preset, const GravParam& mu = {})
{
    using mp_units::one;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::rad;

    using KeplerianT = Keplerian<ElementSet::frame>;

    const Distance semimajor = [&]() {
        switch (preset) {
            case OrbitPreset::LEO: return 7000.0 * km;
            case OrbitPreset::LMEO: return 10000.0 * km;
            case OrbitPreset::GPS: return 22000.0 * km;
            case OrbitPreset::HMEO: return 30000.0 * km;
            case OrbitPreset::GEO: return 42164.0 * km;
        }
        return 0.0 * km;
    }();

    const KeplerianT kep(semimajor, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad);

    if constexpr (std::same_as<ElementSet, KeplerianT>) { return kep; }
    else {
        return ElementSet(kep, mu);
    }
}

} // namespace astro
} // namespace astrea