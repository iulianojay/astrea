/**
 * @file typedefs.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Contains type definitions for the astrea astro library.
 * @date 2025-08-03
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

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Type alias for a vector representing a radius in 3D space.
 */
template <IsFrame auto _frame_>
using RadiusVector = CartesianVector<Distance, Frame_T>;

/**
 * @brief Type alias for a vector representing velocity in 3D space.
 */
template <IsFrame auto _frame_>
using VelocityVector = CartesianVector<Velocity, Frame_T>;

/**
 * @brief Type alias for a vector representing acceleration in 3D space.
 */
template <IsFrame auto _frame_>
using AccelerationVector = CartesianVector<Acceleration, Frame_T>;

/**
 * @brief Type alias for a vector representing unit vectors in 3D space.
 *
 * This is used for direction vectors that do not have units of distance, velocity, or acceleration.
 */
template <IsFrame auto _frame_>
using UnitVector = CartesianVector<Unitless, Frame_T>;

/**
 * @brief Type alias for a vector representing force vectors in 3D space.
 *
 * This is used for vectors that represent forces acting on a vehicle.
 */
template <IsFrame auto _frame_>
using ForceVector = CartesianVector<Force, Frame_T>;

/**
 * @brief Type alias for a vector representing moment vectors in 3D space.
 *
 * This is used for vectors that represent moments (torques) acting on a vehicle.
 */
template <IsFrame auto _frame_>
using TorqueVector = CartesianVector<Moment, Frame_T>;

} // namespace astro
} // namespace astrea