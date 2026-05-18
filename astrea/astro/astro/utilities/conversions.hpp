/**
 * @file conversions.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file contains functions for converting between different coordinate systems and formats in astrodynamics.
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

#include <numbers>

#include <mp-units/math.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Convert the mean anomaly to the true anomaly. Accurate to O(e^4).
 *
 * @param ma The mean anomaly.
 * @param ecc The eccentricity.
 * @return The true anomaly.
 */
Angle convert_mean_anomaly_to_true_anomaly(const Angle& ma, const Unitless ecc);

/**
 * @brief Convert the true anomaly to the mean anomaly. Accurate to O(e^5).
 *
 * @param ta The true anomaly.
 * @param ecc The eccentricity.
 * @return Angle The mean anomaly.
 */
Angle convert_true_anomaly_to_mean_anomaly(const Angle& ta, const Unitless ecc);

/**
 * @brief Convert the eccentric anomaly to the mean anomaly.
 *
 * @param ea The eccentric anomaly.
 * @param ecc The eccentricity.
 * @return The mean anomaly.
 */
Angle convert_eccentric_anomaly_to_mean_anomaly(const Angle& ea, const Unitless ecc);

/**
 * @brief Convert the mean anomaly to the eccentric anomaly using Newton's method.
 *
 * @param ma The mean anomaly.
 * @param ecc The eccentricity.
 * @return The eccentric anomaly.
 */
Angle convert_mean_anomaly_to_eccentric_anomaly(const Angle& ma, const Unitless ecc);

/**
 * @brief Sanitize an angle to ensure it is within the range [0, 2π).
 *
 * @param ang The angle to sanitize.
 * @return The sanitized angle.
 */
inline constexpr Angle wrap_angle(const Angle& angle) noexcept
{
    using mp_units::angular::unit_symbols::rad;
    static constexpr Angle twoPi = 2.0 * (std::numbers::pi * rad);

    Angle ang = angle;
    while (ang < 0.0 * rad) {
        ang += twoPi;
    }
    return mp_units::fmod(ang, twoPi);
}

/**
 * @brief Sanitize an angle to ensure it is within the range [0, π).
 *
 * @param ang The angle to sanitize.
 * @return The sanitized angle.
 */
inline constexpr Angle wrap_angle_to_pi(const Angle& angle) noexcept
{
    using mp_units::angular::unit_symbols::rad;
    static constexpr Angle onePi = std::numbers::pi * rad;

    Angle ang = angle;
    while (ang < 0.0 * rad) {
        ang += onePi;
    }
    return mp_units::fmod(ang, onePi);
}

} // namespace astro
} // namespace astrea
