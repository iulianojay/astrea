/**
 * @file Matrix3x3.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Matrix3x3 class in the astro namespace
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
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
#include <mp-units/systems/angular/math.h>

#include <utilities/string_util.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing a 3x3 matrix, used for matrices and their rates/accelerations.
 *
 * @note I didn't generalize this matrix definition and I'm not going to
 */
template <typename Value_T>
struct Matrix3x3 {

    friend std::ostream& operator<<(std::ostream& os, const Matrix3x3& matrix)
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
     * @brief Constructor for Matrix3x3 from an array of values.
     *
     * @param matrix An array containing the nine elements of the matrix in row-major order.
     */
    inline constexpr Matrix3x3(const std::array<Value_T, 9>& matrix) :
        _matrix{ matrix }
    {
    }

    /**
     * @brief Constructor for Matrix3x3 from three rows represented as arrays.
     *
     * @param row1 An array containing the three elements of the first row of the matrix.
     * @param row2 An array containing the three elements of the second row of the matrix.
     * @param row3 An array containing the three elements of the third row of the matrix.
     */
    inline constexpr Matrix3x3(const std::array<Value_T, 3>& row1, const std::array<Value_T, 3>& row2, const std::array<Value_T, 3>& row3) :
        _matrix{ row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2] }
    {
    }

    /**
     * @brief Access operator for the elements of the matrix.
     *
     * @param row The row index (0, 1, or 2).
     * @param col The column index (0, 1, or 2).
     * @return Value_T& Reference to the element at the specified row and column.
     */
    inline constexpr Value_T& operator[](std::size_t row, std::size_t col) { return _matrix[row * 3 + col]; }

    /**
     * @brief Const access operator for the elements of the matrix.
     *
     * @param row The row index (0, 1, or 2).
     * @param col The column index (0, 1, or 2).
     * @return const Value_T& Reference to the element at the specified row and column.
     */
    inline constexpr const Value_T& operator[](std::size_t row, std::size_t col) const
    {
        return _matrix[row * 3 + col];
    }

    /**
     * @brief Add two matrices together (element-wise addition).
     *
     * @param other The matrix to add to this one.
     * @return Matrix3x3 The resulting matrix from the addition.
     */
    inline constexpr Matrix3x3 operator+(const Matrix3x3& other) const
    {
        return Matrix3x3{ { _matrix[0] + other._matrix[0],
                            _matrix[1] + other._matrix[1],
                            _matrix[2] + other._matrix[2],
                            _matrix[3] + other._matrix[3],
                            _matrix[4] + other._matrix[4],
                            _matrix[5] + other._matrix[5],
                            _matrix[6] + other._matrix[6],
                            _matrix[7] + other._matrix[7],
                            _matrix[8] + other._matrix[8] } };
    }

    /**
     * @brief Negate the matrix (element-wise negation).
     *
     * @return Matrix3x3 The resulting negated matrix.
     */
    inline constexpr Matrix3x3 operator-() const
    {
        return Matrix3x3{
            { -_matrix[0], -_matrix[1], -_matrix[2], -_matrix[3], -_matrix[4], -_matrix[5], -_matrix[6], -_matrix[7], -_matrix[8] }
        };
    }

    /**
     * @brief Subtract another matrix from this one (element-wise subtraction).
     *
     * @param other The matrix to subtract from this one.
     * @return Matrix3x3 The resulting matrix from the subtraction.
     */
    inline constexpr Matrix3x3 operator-(const Matrix3x3& other) const { return *this + (-other); }

    /**
     * @brief Compose two direction matrices (matrix multiplication).
     *
     * @tparam _newout_frame The output frame of the right-hand-side matrix.
     * @param other The right-hand-side matrix to compose with.
     * @return Matrix3x3 The composed matrix.
     */
    template <typename Value_U>
    inline constexpr Matrix3x3<decltype(Value_T{} * Value_U{})> operator*(const Matrix3x3<Value_U>& other) const
    {
        // whatever
        return Matrix3x3<decltype(Value_T{} * Value_U{})>{
            { _matrix[0 * 3 + 0] * other[0, 0] + _matrix[0 * 3 + 1] * other[1, 0] + _matrix[0 * 3 + 2] * other[2, 0],
              _matrix[0 * 3 + 0] * other[0, 1] + _matrix[0 * 3 + 1] * other[1, 1] + _matrix[0 * 3 + 2] * other[2, 1],
              _matrix[0 * 3 + 0] * other[0, 2] + _matrix[0 * 3 + 1] * other[1, 2] + _matrix[0 * 3 + 2] * other[2, 2],
              _matrix[1 * 3 + 0] * other[0, 0] + _matrix[1 * 3 + 1] * other[1, 0] + _matrix[1 * 3 + 2] * other[2, 0],
              _matrix[1 * 3 + 0] * other[0, 1] + _matrix[1 * 3 + 1] * other[1, 1] + _matrix[1 * 3 + 2] * other[2, 1],
              _matrix[1 * 3 + 0] * other[0, 2] + _matrix[1 * 3 + 1] * other[1, 2] + _matrix[1 * 3 + 2] * other[2, 2],
              _matrix[2 * 3 + 0] * other[0, 0] + _matrix[2 * 3 + 1] * other[1, 0] + _matrix[2 * 3 + 2] * other[2, 0],
              _matrix[2 * 3 + 0] * other[0, 1] + _matrix[2 * 3 + 1] * other[1, 1] + _matrix[2 * 3 + 2] * other[2, 1],
              _matrix[2 * 3 + 0] * other[0, 2] + _matrix[2 * 3 + 1] * other[1, 2] + _matrix[2 * 3 + 2] * other[2, 2] }
        };
    }

    /**
     * @brief Get a specific row of the matrix.
     *
     * @param idx The index of the row to retrieve (0, 1, or 2).
     * @return const CartesianVector<Value_T, in_frame>& The requested row as a CartesianVector.
     */
    inline constexpr std::array<Value_T, 3> row(const std::size_t& idx) const
    {
        return { _matrix[idx * 3 + 0], _matrix[idx * 3 + 1], _matrix[idx * 3 + 2] };
    }

    /**
     * @brief Creates an identity matrix (no rotation).
     *
     * @return Matrix3x3 The identity matrix.
     */
    static inline constexpr Matrix3x3 identity()
    {
        static constexpr auto unit = Value_T::unit;
        return Matrix3x3{ { 1.0 * unit, 0.0 * unit, 0.0 * unit },
                          { 0.0 * unit, 1.0 * unit, 0.0 * unit },
                          { 0.0 * unit, 0.0 * unit, 1.0 * unit } };
    }

    static inline constexpr Matrix3x3 zero()
    {
        return Matrix3x3{ { 0.0 * Value_T::unit, 0.0 * Value_T::unit, 0.0 * Value_T::unit },
                          { 0.0 * Value_T::unit, 0.0 * Value_T::unit, 0.0 * Value_T::unit },
                          { 0.0 * Value_T::unit, 0.0 * Value_T::unit, 0.0 * Value_T::unit } };
    }

    /**
     * @brief Transposes the matrix, effectively inverting the transformation.
     *
     * @return Matrix3x3 The transposed matrix.
     */
    inline constexpr Matrix3x3 transpose() const
    {
        return Matrix3x3{ { _matrix[0 * 3 + 0], _matrix[1 * 3 + 0], _matrix[2 * 3 + 0] },
                          { _matrix[0 * 3 + 1], _matrix[1 * 3 + 1], _matrix[2 * 3 + 1] },
                          { _matrix[0 * 3 + 2], _matrix[1 * 3 + 2], _matrix[2 * 3 + 2] } };
    }

    /**
     * @brief Get the trace of the matrix (the sum of the diagonal elements).
     *
     * @return Value_T The trace of the matrix.
     */
    inline constexpr Value_T trace() const { return _matrix[0 * 3 + 0] + _matrix[1 * 3 + 1] + _matrix[2 * 3 + 2]; }

    /**
     * @brief Get the determinant of the matrix.
     *
     * @return Value_T The determinant of the matrix.
     */
    inline constexpr Value_T determinant() const
    {
        return _matrix[0 * 3 + 0] * (_matrix[1 * 3 + 1] * _matrix[2 * 3 + 2] - _matrix[1 * 3 + 2] * _matrix[2 * 3 + 1]) -
               _matrix[0 * 3 + 1] * (_matrix[1 * 3 + 0] * _matrix[2 * 3 + 2] - _matrix[1 * 3 + 2] * _matrix[2 * 3 + 0]) +
               _matrix[0 * 3 + 2] * (_matrix[1 * 3 + 0] * _matrix[2 * 3 + 1] - _matrix[1 * 3 + 1] * _matrix[2 * 3 + 0]);
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

        const Unitless det = determinant().force_in(one);
        if (is_eq_zero(det)) {
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

  protected:
    std::array<Value_T, 9> _matrix; //!< 3x3 matrix to hold the direction cosines.

    /**
     * @brief Normalizes the matrix by scaling all elements by the given factor.
     *
     * @param scale The factor to scale the matrix elements by to achieve normalization.
     */
    inline constexpr void _normalize(const Unitless& scale)
    {
        using namespace mp_units;

        for (auto& element : _matrix) {
            element *= scale;
            // Avoid very small values that should be zero
            if (mp_units::abs(element) < 1.0e-15 * one) { element = 0.0 * one; }
        }
    }
};

} // namespace astro
} // namespace astrea