/**
 * @file custom.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Custom units for astrea project
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <mp-units/systems/angular.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>

namespace astrea {

/**
 * @brief Definition for a Julian Century as 36525 days.
 */
inline constexpr struct JulianCentury final : mp_units::named_unit<"JulianCentury", mp_units::mag<36525> * mp_units::non_si::day> {
} JulianCentury;

} // namespace astrea