/**
 * @file PerturbingForce.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the PerturbingForce class, which defines the interface for force models in astrodynamics.
 * @date 2025-08-02
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

#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/frames/definitions.hpp>
#include <astro/frames/definitions/primary_frame.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Struct to hold the results of a perturbation force computation, including both acceleration and torque.
 */
struct Perturbation {
    ForceVector<frames::primary> force = { 0.0 * mp_units::si::unit_symbols::N }; //!< The computed force vector due to the perturbing force.
    TorqueVector<frames::primary> torque = { 0.0 * mp_units::si::unit_symbols::N * mp_units::si::unit_symbols::m }; //!< The computed torque vector due to the perturbing force.
};

} // namespace astro
} // namespace astrea