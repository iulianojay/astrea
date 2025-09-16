/**
 * @file conversions.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file contains functions for converting between different coordinate systems and formats in astrodynamics.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

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
 * @brief Sanitize an angle to ensure it is within the range [0, 2π).
 *
 * @param ang The angle to sanitize.
 * @return The sanitized angle.
 */
Angle sanitize_angle(const Angle& ang);

} // namespace astro
} // namespace astrea
