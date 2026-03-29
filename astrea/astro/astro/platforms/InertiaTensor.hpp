/**
 * @file InertiaTensor.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A class representing an inertia matrix in the astrea astro platform.
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

#include <mp-units/framework.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/instances/dynamic_body_frame.hpp>

namespace astrea {
namespace astro {

/**
 * @brief A class representing an inertia matrix in the astrea astro platform.
 *
 * @tparam Frame_T The frame in which the inertia tensor is defined. Defaults to `frames::dynamic::body`.
 */
template <class Frame_T = frames::dynamic::body>
class InertiaTensor {

    static constexpr MomentOfInertia zero =
        0.0 * mp_units::si::unit_symbols::kg * mp_units::pow<2>(mp_units::si::unit_symbols::m);
    static constexpr MomentOfInertia one =
        1.0 * mp_units::si::unit_symbols::kg * mp_units::pow<2>(mp_units::si::unit_symbols::m);

  public:
    /**
     * @brief Default constructor for an inertia tensor.
     */
    constexpr InertiaTensor() :
        _tensor{ { { one, zero, zero }, { zero, one, zero }, { zero, zero, one } } }
    {
    }

    /**
     * @brief Default destructor for an inertia tensor.
     */
    ~InertiaTensor() = default;

    /**
     * @brief Constructs an inertia tensor with the specified moments of inertia.
     *
     * @param Ixx Moment of inertia about the x-axis.
     * @param Ixy Product of inertia about the x and y axes.
     * @param Ixz Product of inertia about the x and z axes.
     * @param Iyy Moment of inertia about the y-axis.
     * @param Iyz Product of inertia about the y and z axes.
     * @param Izz Moment of inertia about the z-axis.
     */
    InertiaTensor(
        const MomentOfInertia& Ixx,
        const MomentOfInertia& Ixy,
        const MomentOfInertia& Ixz,
        const MomentOfInertia& Iyy,
        const MomentOfInertia& Iyz,
        const MomentOfInertia& Izz
    ) :
        _tensor{ { { Ixx, -Ixy, -Ixz }, { -Ixy, Iyy, -Iyz }, { -Ixz, -Iyz, Izz } } }
    {
    }

    /**
     * @brief Constructs a diagonal inertia tensor with the specified moments of inertia along the principal axes.
     *
     * @param Ixx Moment of inertia about the x-axis.
     * @param Iyy Moment of inertia about the y-axis.
     * @param Izz Moment of inertia about the z-axis.
     */
    InertiaTensor(const MomentOfInertia& Ixx, const MomentOfInertia& Iyy, const MomentOfInertia& Izz) :
        _tensor{ { { Ixx, zero, zero }, { zero, Iyy, zero }, { zero, zero, Izz } } }
    {
    }

    /**
     * @brief Accesses the inertia tensor element at the specified row and column.
     */
    MomentOfInertia& operator[](size_t i, size_t j) { return _tensor[i][j]; }

    /**
     * @brief Accesses the inertia tensor element at the specified row and column (const version).
     */
    const MomentOfInertia& operator[](size_t i, size_t j) const { return _tensor[i][j]; }

    /**
     * @brief Computes the determinant of the inertia tensor.
     *
     * @return auto The determinant of the inertia tensor.
     */
    auto determinant() const
    {
        return _tensor[0][0] * (_tensor[1][1] * _tensor[2][2] - _tensor[1][2] * _tensor[2][1]) -
               _tensor[0][1] * (_tensor[1][0] * _tensor[2][2] - _tensor[1][2] * _tensor[2][0]) +
               _tensor[0][2] * (_tensor[1][0] * _tensor[2][1] - _tensor[1][1] * _tensor[2][0]);
    }

    /**
     * @brief Multiplies the inertia tensor by a CartesianVector, effectively applying the inertia tensor to the vector.
     */
    template <typename Value_U>
    CartesianVector<decltype(Value_U{} / MomentOfInertia{}), Frame_T>
        inverse_multiply(const CartesianVector<Value_U, Frame_T>& vec) const
    {
        // Compute the determinant
        // TODO: Generalize a 3x3 matrix class and use it with the DCM as well
        const auto det = determinant();

        if (is_eq_zero(det)) { throw std::runtime_error("Inertia tensor is singular and cannot be inverted."); }

        // Compute the inverse using the formula for the inverse of a 3x3 matrix
        const auto invDet = 1.0 / det;
        const auto xx     = invDet * (_tensor[1][1] * _tensor[2][2] - _tensor[1][2] * _tensor[2][1]);
        const auto xy     = invDet * (_tensor[0][2] * _tensor[2][1] - _tensor[0][1] * _tensor[2][2]);
        const auto xz     = invDet * (_tensor[0][1] * _tensor[1][2] - _tensor[0][2] * _tensor[1][1]);
        const auto yx     = invDet * (_tensor[1][0] * _tensor[2][2] - _tensor[1][2] * _tensor[2][0]);
        const auto yy     = invDet * (_tensor[0][2] * _tensor[2][0] - _tensor[0][0] * _tensor[2][2]);
        const auto yz     = invDet * (_tensor[0][0] * _tensor[1][1] - _tensor[0][1] * _tensor[1][0]);
        const auto zx     = invDet * (_tensor[1][0] * _tensor[2][1] - _tensor[1][1] * _tensor[2][0]);
        const auto zy     = invDet * (_tensor[0][1] * _tensor[2][0] - _tensor[0][0] * _tensor[2][1]);
        const auto zz     = invDet * (_tensor[0][0] * _tensor[1][1] - _tensor[0][1] * _tensor[1][0]);

        return { xx * vec[0] + xy * vec[1] + xz * vec[2],
                 yx * vec[0] + yy * vec[1] + yz * vec[2],
                 zx * vec[0] + zy * vec[1] + zz * vec[2] };
    }

  private:
    std::array<std::array<MomentOfInertia, 3>, 3> _tensor; //!< Inertia tensor of the body in the dynamic body frame
};

} // namespace astro
} // namespace astrea