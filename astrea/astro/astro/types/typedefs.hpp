/**
 * @file typedefs.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Contains type definitions for the astrea astro library.
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Type alias for a vector representing a radius in 3D space.
 */
template <typename Frame_T>
using RadiusVector = CartesianVector<Distance, Frame_T>;

/**
 * @brief Type alias for a vector representing velocity in 3D space.
 */
template <typename Frame_T>
using VelocityVector = CartesianVector<Velocity, Frame_T>;

/**
 * @brief Type alias for a vector representing acceleration in 3D space.
 */
template <typename Frame_T>
using AccelerationVector = CartesianVector<Acceleration, Frame_T>;

/**
 * @brief Type alias for a vector representing unit vectors in 3D space.
 *
 * This is used for direction vectors that do not have units of distance, velocity, or acceleration.
 */
template <typename Frame_T>
using UnitVector = CartesianVector<Unitless, Frame_T>;

} // namespace astro
} // namespace astrea