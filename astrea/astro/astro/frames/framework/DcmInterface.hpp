/**
 * @file DcmInterface.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the DcmInterface class in the astro namespace
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you cosAlphan redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <array>
#include <cmath>
#include <iostream>

#include <mp-units/math.h>
#include <mp-units/systems/si/math.h>

#include <utilities/string_util.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

// TODO: Make this CRTP to avoid weird casting issues

/**
 * @brief Class representing a 3x3 matrix, used for matrices and their rates/accelerations.
 *
 * @note I didn't generalize this matrix definition and I'm not going to
 */
template <typename Value_T, IsFrame auto _in_frame_, IsFrame auto _out_frame_>
struct DcmInterface {

    template <typename Value_U, IsFrame auto in_frame_u, IsFrame auto out_frame_u>
    friend struct DcmInterface;

    static constexpr auto in_frame  = _in_frame_;  //!< The input frame of the matrix.
    static constexpr auto out_frame = _out_frame_; //!< The output frame of the matrix.

    friend std::ostream& operator<<(std::ostream& os, const DcmInterface& matrix)
    {
        for (std::size_t i = 0; i < 3; ++i) {
            os << "| ";
            for (std::size_t j = 0; j < 3; ++j) {
                os << matrix[i, j] << " ";
            }
            os << "|\n";
        }
        return os;
    }

    /**
     * @brief Constructor for DcmInterface from an array of values.
     *
     * @param matrix An array containing the nine elements of the matrix in row-major order.
     */
    inline constexpr DcmInterface(const std::array<Value_T, 9>& matrix) :
        _data{ matrix }
    {
    }

    /**
     * @brief Constructor for DcmInterface from three rows represented as arrays.
     *
     * @param row1 An array containing the three elements of the first row of the matrix.
     * @param row2 An array containing the three elements of the second row of the matrix.
     * @param row3 An array containing the three elements of the third row of the matrix.
     */
    inline constexpr DcmInterface(const std::array<Value_T, 3>& row1, const std::array<Value_T, 3>& row2, const std::array<Value_T, 3>& row3) :
        _data{ row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2] }
    {
    }

    template <typename Value_U, auto in_frame_u, auto out_frame_u>
        requires(requires { Value_T{ Value_U{} }; } && equivalent(in_frame, in_frame_u) && equivalent(out_frame, out_frame_u))
    inline constexpr DcmInterface(const DcmInterface<Value_U, in_frame_u, out_frame_u>& matrix) :
        _data{ matrix._data }
    {
    }

    template <typename Value_U, auto in_frame_u, auto out_frame_u>
        requires(requires { Value_T{ Value_U{} }; } && equivalent(in_frame, in_frame_u) && equivalent(out_frame, out_frame_u))
    inline constexpr DcmInterface(DcmInterface<Value_U, in_frame_u, out_frame_u>&& matrix) :
        _data{ std::move(matrix._data) }
    {
    }

    /**
     * @brief Access operator for the elements of the matrix.
     *
     * @param row The row index (0, 1, or 2).
     * @param col The column index (0, 1, or 2).
     * @return Value_T& Reference to the element at the specified row and column.
     */
    inline constexpr Value_T& operator[](std::size_t row, std::size_t col) { return _data[row * 3 + col]; }

    /**
     * @brief Const access operator for the elements of the matrix.
     *
     * @param row The row index (0, 1, or 2).
     * @param col The column index (0, 1, or 2).
     * @return const Value_T& Reference to the element at the specified row and column.
     */
    inline constexpr const Value_T& operator[](std::size_t row, std::size_t col) const { return _data[row * 3 + col]; }

    /**
     * @brief Add two matrices together (element-wise addition).
     *
     * @param other The matrix to add to this one.
     * @return DcmInterface The resulting matrix from the addition.
     */
    template <typename Value_U, auto in_frame_u, auto out_frame_u>
        requires(equivalent(in_frame, in_frame_u) && equivalent(out_frame, out_frame_u))
    inline constexpr DcmInterface operator+(const DcmInterface<Value_U, in_frame_u, out_frame_u>& other) const
    {
        return { { _data[0] + other._data[0],
                   _data[1] + other._data[1],
                   _data[2] + other._data[2],
                   _data[3] + other._data[3],
                   _data[4] + other._data[4],
                   _data[5] + other._data[5],
                   _data[6] + other._data[6],
                   _data[7] + other._data[7],
                   _data[8] + other._data[8] } };
    }

    /**
     * @brief Negate the matrix (element-wise negation).
     *
     * @return DcmInterface The resulting negated matrix.
     */
    inline constexpr DcmInterface operator-() const
    {
        return { { -_data[0], -_data[1], -_data[2], -_data[3], -_data[4], -_data[5], -_data[6], -_data[7], -_data[8] } };
    }

    /**
     * @brief Subtract another matrix from this one (element-wise subtraction).
     *
     * @param other The matrix to subtract from this one.
     * @return DcmInterface The resulting matrix from the subtraction.
     */
    template <typename Value_U, auto in_frame_u, auto out_frame_u>
        requires(equivalent(in_frame, in_frame_u) && equivalent(out_frame, out_frame_u))
    inline constexpr DcmInterface operator-(const DcmInterface<Value_U, in_frame_u, out_frame_u>& other) const
    {
        return *this + (-other);
    }

    /**
     * @brief Compose two direction matrices (matrix multiplication).
     *
     * Note: This overload is identically-framed matrices so the output frame is the same as the input frame.
     *
     * @tparam _newout_frame The output frame of the right-hand-side matrix.
     * @param other The right-hand-side matrix to compose with.
     * @return DcmInterface The composed matrix.
     */
    template <typename Value_U, auto in_frame_u, auto out_frame_u>
        requires(equivalent(in_frame, in_frame_u) && equivalent(out_frame, out_frame_u))
    inline constexpr DcmInterface<decltype(Value_T{} * Value_U{}), in_frame, out_frame>
        operator*(const DcmInterface<Value_U, in_frame_u, out_frame_u>& other) const
    {
        return _multiply(other.data());
    }

    /**
     * @brief Compose two direction matrices (matrix multiplication).
     *
     * Note: This overload is for stacked rotations where mat_1^2 * mat_2^3 -> mat_1^3
     *
     * @tparam _newout_frame The output frame of the right-hand-side matrix.
     * @param other The right-hand-side matrix to compose with.
     * @return DcmInterface The composed matrix.
     */
    template <typename Value_U, auto in_frame_u, auto out_frame_u>
        requires(!(equivalent(in_frame, in_frame_u) && equivalent(out_frame, out_frame_u)) && equivalent(out_frame, in_frame_u))
    inline constexpr DcmInterface<decltype(Value_T{} * Value_U{}), in_frame, out_frame_u>
        operator*(const DcmInterface<Value_U, in_frame_u, out_frame_u>& other) const
    {
        return _multiply(other.data());
    }

    /**
     * @brief Multiply this matrix by a Cartesian vector.
     *
     * @tparam Value_U The type of the elements in the Cartesian vector.
     * @tparam in_frame_u The input frame of the Cartesian vector.
     * @param vec The Cartesian vector to multiply the matrix by.
     * @return CartesianVector The resulting vector from the multiplication.
     */
    template <typename Value_U, auto in_frame_u>
        requires(equivalent(in_frame, in_frame_u))
    inline constexpr CartesianVector<decltype(Value_T{} * Value_U{}), out_frame>
        operator*(const CartesianVector<Value_U, in_frame_u>& vec) const
    {
        return { row(0).dot(vec), row(1).dot(vec), row(2).dot(vec) };
    }

    /**
     * @brief Multiply the matrix by a scalar value (element-wise multiplication).
     *
     * @param scalar The scalar value to multiply the matrix by.
     * @return DcmInterface The resulting matrix from the scalar multiplication.
     */
    template <typename Value_U>
        requires(std::is_arithmetic_v<Value_U> || mp_units::Quantity<Value_U>)
    inline constexpr DcmInterface<decltype(Value_T{} * Value_U{}), in_frame, out_frame> operator*(const Value_U& scalar) const
    {
        return { { _data[0] * scalar, _data[1] * scalar, _data[2] * scalar },
                 { _data[3] * scalar, _data[4] * scalar, _data[5] * scalar },
                 { _data[6] * scalar, _data[7] * scalar, _data[8] * scalar } };
    }

    /**
     * @brief Get a specific row of the matrix as a Cartesian vector.
     *
     * @param idx The index of the row to retrieve (0, 1, or 2).
     * @return const CartesianVector<Value_T, _in_frame_>& The requested row as a Cartesian vector.
     */
    inline constexpr CartesianVector<Value_T, _in_frame_> row(const std::size_t& idx) const
    {
        return { _data[idx * 3 + 0], _data[idx * 3 + 1], _data[idx * 3 + 2] };
    }

    /**
     * @brief Transposes the matrix, effectively inverting the transformation.
     *
     * @return DcmInterface The transposed matrix.
     */
    inline constexpr DcmInterface<Value_T, _out_frame_, _in_frame_> transpose() const
    {
        return { { _data[0], _data[3], _data[6] }, { _data[1], _data[4], _data[7] }, { _data[2], _data[5], _data[8] } };
    }

    /**
     * @brief Get the trace of the matrix (the sum of the diagonal elements).
     *
     * @return Value_T The trace of the matrix.
     */
    inline constexpr Value_T trace() const { return _data[0] + _data[4] + _data[8]; }

    /**
     * @brief Get the determinant of the matrix.
     *
     * @return Value_T The determinant of the matrix.
     */
    inline constexpr Value_T determinant() const
    {
        return _data[0] * (_data[4] * _data[8] - _data[5] * _data[7]) -
               _data[1] * (_data[3] * _data[8] - _data[5] * _data[6]) + _data[2] * (_data[3] * _data[7] - _data[4] * _data[6]);
    }

    /**
     * @brief Normalizes the matrix to ensure it represents a valid rotation.
     *
     * This method scales the elements of the matrix so that the determinant is 1, which is a requirement for a
     * valid rotation matrix. If the determinant is zero, an exception is thrown since the matrix cannot be
     * normalized. Uses a linear approximation when the determinant is close to 1 for numerical efficiency.
     */
    inline constexpr void normalize()
    {
        using namespace mp_units;

        const Unitless det = determinant().in(one);
        if (det == 0.0) {
            throw std::runtime_error("Cannot normalize a zero-value determinant matrix. The matrix is likely singular.");
        }

        // For 3x3 matrices, determinant scales as k^3 where k is the scaling factor
        // Use linear approximation when determinant is close to 1: k ≈ 1 - (det-1)/3
        // https://stackoverflow.com/questions/11667783/quaternion-and-normalization
        if (abs(1.0 * one - det) < 2.107342e-08 * one) { _normalize(1.0 * one - (det - 1.0 * one) / 3.0); }
        else {
            // Exact formula: k = (1/det)^(1/3) to make k^3 * det = 1
            _normalize(1.0 * one / cbrt(det));
        }
    }

    /**
     * @brief Get the underlying data of the matrix as an array.
     *
     * @return std::array<Value_T, 9> The elements of the matrix in row-major order.
     */
    inline constexpr std::array<Value_T, 9> data() const { return _data; }

  protected:
    std::array<Value_T, 9> _data; //!< 3x3 matrix to hold the direction cosines.

    /**
     * @brief Normalizes the matrix by scaling all elements by the given factor.
     *
     * @param scale The factor to scale the matrix elements by to achieve normalization.
     */
    inline constexpr void _normalize(const Unitless& scale)
    {
        using namespace mp_units;

        for (auto& element : _data) {
            element *= scale;
            // Avoid very small values that should be zero
            if (mp_units::abs(element) < 1.0e-15 * one) { element = 0.0 * one; }
        }
    }

    // Helper function for matrix multiplication
    template <typename Value_U>
    std::array<decltype(Value_T{} * Value_U{}), 9> _multiply(const std::array<Value_U, 9>& other) const
    {
        // lmao whatever
        return { _data[0] * other[0] + _data[1] * other[3] + _data[2] * other[6],
                 _data[0] * other[1] + _data[1] * other[4] + _data[2] * other[7],
                 _data[0] * other[2] + _data[1] * other[5] + _data[2] * other[8],
                 _data[3] * other[0] + _data[4] * other[3] + _data[5] * other[6],
                 _data[3] * other[1] + _data[4] * other[4] + _data[5] * other[7],
                 _data[3] * other[2] + _data[4] * other[5] + _data[5] * other[8],
                 _data[6] * other[0] + _data[7] * other[3] + _data[8] * other[6],
                 _data[6] * other[1] + _data[7] * other[4] + _data[8] * other[7],
                 _data[6] * other[2] + _data[7] * other[5] + _data[8] * other[8] };
    }

    /**
     * @brief Creates an identity matrix (no rotation).
     *
     * @return DcmInterface The identity matrix.
     */
    static inline constexpr DcmInterface identity()
    {
        static constexpr auto one = 1.0 * Value_T::unit;
        return { { one, Value_T::zero(), Value_T::zero() },
                 { Value_T::zero(), one, Value_T::zero() },
                 { Value_T::zero(), Value_T::zero(), one } };
    }

    /**
     * @brief Creates a zero matrix (invalid rotation).
     *
     * @return DcmInterface The zero matrix.
     */
    static inline constexpr DcmInterface zero()
    {
        return { { Value_T::zero(), Value_T::zero(), Value_T::zero() },
                 { Value_T::zero(), Value_T::zero(), Value_T::zero() },
                 { Value_T::zero(), Value_T::zero(), Value_T::zero() } };
    }
};


/**
 * @brief Multiply the matrix by a scalar value (element-wise multiplication).
 *
 * @param scalar The scalar value to multiply the matrix by.
 * @return DcmInterface The resulting matrix from the scalar multiplication.
 */
template <typename Value_T, typename Value_U, IsFrame auto in_frame, IsFrame auto out_frame>
    requires(std::is_arithmetic_v<Value_U> || mp_units::Quantity<Value_U>)
inline constexpr DcmInterface<decltype(Value_T{} * Value_U{}), in_frame, out_frame>
    operator*(const Value_T& scalar, const DcmInterface<Value_U, in_frame, out_frame>& matrix)
{
    return matrix * scalar;
}


} // namespace astro
} // namespace astrea