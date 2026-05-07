/**
 * @file DirectionCosineMatrix.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the DirectionCosineMatrix class in the astro namespace
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
#include <astro/frames/frame_concepts.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

namespace {

using mp_units::one;

inline constexpr auto sin_cos_pack(const Angle& angle)
{
    using mp_units::angular::cos;
    using mp_units::angular::sin;
    return std::make_pair(sin(angle), cos(angle));
}

} // namespace

// TODO: Probably should use eigen instead of arrays, might not matter for these small matrices used in
//  rotation but worth looking into
/**
 * @brief Class representing a direction cosine matrix (DCM) for transforming vectors between state/frames.
 *
 * This class provides methods to create DCMs for various rotations and to apply them to vectors.
 *
 * @tparam Out_Frame_T The frame type to which the DCM applies.
 */
template <typename In_Frame_T, typename Out_Frame_T>
class DirectionCosineMatrix {

    friend std::ostream& operator<<(std::ostream& os, const DirectionCosineMatrix& dcm)
    {
        for (const auto& row : dcm._matrix) {
            os << "| ";
            for (const auto& element : row) {
                os << element << " ";
            }
            os << "|\n";
        }
        return os;
    }

  public:
    /**
     * @brief Constructor for DirectionCosineMatrix from an array of CartesianVectors.
     *
     * @param matrix An array containing the three rows of the DCM, each represented as a CartesianVector.
     */
    inline constexpr DirectionCosineMatrix(const std::array<std::array<Unitless, 3>, 3>& matrix) :
        _matrix{ matrix }
    {
        normalize();
    }

    /**
     * @brief Constructor for DirectionCosineMatrix from an array of CartesianVectors.
     *
     * @param row1 An array containing the three elements of the first row of the DCM.
     * @param row2 An array containing the three elements of the second row of the DCM.
     * @param row3 An array containing the three elements of the third row of the DCM.
     */
    inline constexpr DirectionCosineMatrix(const std::array<Unitless, 3>& row1, const std::array<Unitless, 3>& row2, const std::array<Unitless, 3>& row3) :
        _matrix{ row1, row2, row3 }
    {
        normalize();
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis.
     *
     * @param theta The angle of rotation around the X-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T> X(const Angle& theta)
    {
        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{ { 1.0 * one, 0.0 * one, 0.0 * one },
                                                               { 0.0 * one, cosTheta, -sinTheta },
                                                               { 0.0 * one, sinTheta, cosTheta } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis.
     *
     * @param theta The angle of rotation around the Y-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T> Y(const Angle& theta)
    {
        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{ { cosTheta, 0.0 * one, sinTheta },
                                                               { 0.0 * one, 1.0 * one, 0.0 * one },
                                                               { -sinTheta, 0.0 * one, cosTheta } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis.
     *
     * @param theta The angle of rotation around the Z-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T> Z(const Angle& theta)
    {
        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{ { cosTheta, -sinTheta, 0.0 * one },
                                                               { sinTheta, cosTheta, 0.0 * one },
                                                               { 0.0 * one, 0.0 * one, 1.0 * one } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis, the Z-axis, and the X-axis again.
     *
     * @param alpha The angle of rotation around the X-axis.
     * @param beta The angle of rotation around the Z-axis.
     * @param gamma The angle of rotation around the X-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T> XZX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{
            { cosBeta, -cosGamma * sinBeta, sinBeta * sinGamma },
            { cosAlpha * sinBeta, cosAlpha * cosBeta * cosGamma - sinAlpha * sinGamma, -cosGamma * sinAlpha - cosAlpha * cosBeta * sinGamma },
            { sinAlpha * sinBeta, cosAlpha * sinBeta + cosBeta * cosGamma * sinAlpha, cosAlpha * cosGamma - cosBeta * sinGamma * sinAlpha }
        };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis, the Y-axis, and the X-axis again.
     *
     * @param alpha The angle of rotation around the X-axis.
     * @param beta The angle of rotation around the Y-axis.
     * @param gamma The angle of rotation around the X-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T> XYX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{
            { cosBeta, sinBeta * sinGamma, cosGamma * sinBeta },
            { sinAlpha * sinBeta, cosAlpha * cosBeta - cosGamma * sinAlpha * sinBeta, -cosAlpha * sinGamma - cosBeta * cosGamma * sinAlpha },
            { -cosAlpha * sinBeta, cosGamma * cosAlpha * sinBeta + cosBeta * sinAlpha, cosAlpha * cosBeta * cosGamma - sinAlpha * sinGamma }
        };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis, the Z-axis, and the Y-axis again.
     *
     * @param alpha The angle of rotation around the Y-axis.
     * @param beta The angle of rotation around the Z-axis.
     * @param gamma The angle of rotation around the Y-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T> YZY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{
            { cosAlpha * cosBeta * cosGamma - sinAlpha * sinGamma, cosGamma * sinAlpha + cosAlpha * cosBeta * sinGamma, -cosAlpha * sinBeta },
            { -cosGamma * sinBeta, sinBeta * sinGamma, cosBeta },
            { cosBeta * cosGamma * sinAlpha + cosAlpha * sinGamma, cosAlpha * cosGamma - cosBeta * sinAlpha * sinGamma, sinAlpha * sinBeta }
        };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis, the X-axis, and the Z-axis again.
     *
     * @param alpha The angle of rotation around the Z-axis.
     * @param beta The angle of rotation around the X-axis.
     * @param gamma The angle of rotation around the Z-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T> ZXZ(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{ { cosAlpha * cosGamma - cosBeta * sinAlpha * sinGamma,
                                                                 -cosAlpha * sinGamma - cosBeta * cosGamma * sinAlpha,
                                                                 sinAlpha * sinBeta },
                                                               { cosGamma * sinAlpha + cosAlpha * cosBeta * sinGamma,
                                                                 cosAlpha * cosBeta * cosGamma - sinAlpha * sinGamma,
                                                                 -cosAlpha * sinBeta },
                                                               { sinBeta * sinGamma, cosGamma * sinBeta, cosBeta } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis, the Y-axis, and the Z-axis again.
     *
     * @param alpha The angle of rotation around the Z-axis.
     * @param beta The angle of rotation around the Y-axis.
     * @param gamma The angle of rotation around the Z-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T> ZYZ(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{
            { cosAlpha * cosBeta * cosGamma - sinAlpha * sinGamma, -cosGamma * sinAlpha - cosAlpha * cosBeta * sinGamma, cosAlpha * sinBeta },
            { cosAlpha * sinGamma + cosBeta * cosGamma * sinAlpha, cosAlpha * cosGamma - cosBeta * sinAlpha * sinGamma, sinAlpha * sinBeta },
            { -cosGamma * sinBeta, sinBeta * sinGamma, cosBeta }
        };
    }


    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis, the X-axis, and the Y-axis again.
     *
     * @param alpha The angle of rotation around the Y-axis.
     * @param beta The angle of rotation around the X-axis.
     * @param gamma The angle of rotation around the Y-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T> YXY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{
            { cosAlpha * cosGamma - cosBeta * sinAlpha * sinGamma, sinBeta * sinGamma, cosGamma * sinAlpha + cosAlpha * cosBeta * sinGamma },
            { sinAlpha * sinBeta, cosBeta, -cosAlpha * sinBeta },
            { -cosBeta * cosGamma * sinAlpha - cosAlpha * sinGamma, cosGamma * sinBeta, cosAlpha * cosBeta * cosGamma - sinAlpha * sinGamma }
        };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis, then Y-axis, then Z-axis.
     *
     * @param alpha The angle of rotation around the X-axis.
     * @param beta The angle of rotation around the Y-axis.
     * @param gamma The angle of rotation around the Z-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T> XYZ(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{
            { cosBeta * cosGamma, -cosBeta * sinGamma, sinBeta },
            { cosAlpha * sinGamma + cosGamma * sinAlpha * sinBeta, cosAlpha * cosGamma - sinAlpha * sinBeta * sinGamma, -cosBeta * sinAlpha },
            { sinAlpha * sinGamma - cosAlpha * cosGamma * sinBeta, cosGamma * sinAlpha + cosAlpha * sinBeta * sinGamma, cosAlpha * cosBeta }
        };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis, then Z-axis, then X-axis.
     *
     * @param alpha The angle of rotation around the Y-axis.
     * @param beta The angle of rotation around the Z-axis.
     * @param gamma The angle of rotation around the X-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T> YZX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{
            { cosAlpha * cosBeta, -sinBeta, cosBeta * sinAlpha },
            { cosGamma * sinAlpha + cosAlpha * sinBeta * sinGamma, cosBeta * cosGamma, sinAlpha * sinBeta * sinGamma - cosAlpha * cosGamma },
            { sinAlpha * sinGamma - cosAlpha * cosGamma * sinBeta, cosGamma * sinBeta, cosAlpha * sinGamma + cosGamma * sinAlpha * sinBeta }
        };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis, then X-axis, then Y-axis.
     *
     * @param alpha The angle of rotation around the Z-axis.
     * @param beta The angle of rotation around the X-axis.
     * @param gamma The angle of rotation around the Y-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T> ZXY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{
            { cosAlpha * cosGamma - sinAlpha * sinBeta * sinGamma, -cosBeta * sinAlpha, cosAlpha * sinGamma + cosGamma * sinAlpha * sinBeta },
            { cosGamma * sinAlpha + cosAlpha * sinBeta * sinGamma, cosAlpha * cosBeta, sinAlpha * sinGamma - cosAlpha * cosGamma * sinBeta },
            { -cosGamma * sinBeta, sinBeta, cosBeta * cosGamma }
        };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis, then Z-axis, then Y-axis.
     *
     * @param alpha The angle of rotation around the X-axis.
     * @param beta The angle of rotation around the Z-axis.
     * @param gamma The angle of rotation around the Y-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T> XZY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::YZX(gamma, beta, alpha);
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis, then Y-axis, then X-axis.
     *
     * @param alpha The angle of rotation around the Z-axis.
     * @param beta The angle of rotation around the Y-axis.
     * @param gamma The angle of rotation around the X-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T> ZYX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::XYZ(gamma, beta, alpha);
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis, then X-axis, then Z-axis.
     *
     * @param alpha The angle of rotation around the Y-axis.
     * @param beta The angle of rotation around the X-axis.
     * @param gamma The angle of rotation around the Z-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T> YXZ(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::ZXY(gamma, beta, alpha);
    }

    /**
     * @brief Creates a direction cosine matrix from three orthonormal vectors.
     *
     * @param x The unit vector in the X direction.
     * @param y The unit vector in the Y direction.
     * @param z The unit vector in the Z direction.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T> from_vectors(
        const CartesianVector<Unitless, In_Frame_T>& x,
        const CartesianVector<Unitless, In_Frame_T>& y,
        const CartesianVector<Unitless, In_Frame_T>& z
    )
    {
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{ { x[0], x[1], x[2] }, { y[0], y[1], y[2] }, { z[0], z[1], z[2] } };
    }

    /**
     * @brief Creates an identity direction cosine matrix (no rotation).
     *
     * @return DirectionCosineMatrix<Out_Frame_T> The identity direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T> identity()
    {
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{ { 1.0 * one, 0.0 * one, 0.0 * one },
                                                               { 0.0 * one, 1.0 * one, 0.0 * one },
                                                               { 0.0 * one, 0.0 * one, 1.0 * one } };
    }

    /**
     * @brief Transposes the direction cosine matrix, effectively inverting the transformation.
     *
     * @return DirectionCosineMatrix<Out_Frame_T, In_Frame_T> The transposed direction cosine matrix.
     */
    inline constexpr DirectionCosineMatrix<Out_Frame_T, In_Frame_T> transpose() const
    {
        return DirectionCosineMatrix<Out_Frame_T, In_Frame_T>{ { _matrix[0][0], _matrix[1][0], _matrix[2][0] },
                                                               { _matrix[0][1], _matrix[1][1], _matrix[2][1] },
                                                               { _matrix[0][2], _matrix[1][2], _matrix[2][2] } };
    }

    template <RotationSequence sequence>
    static inline constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T>
        from_euler_angles(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        if constexpr (sequence == RotationSequence::ZXZ) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::ZXZ(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::XYX) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::XYX(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::YZY) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::YZY(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::ZYZ) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::ZYZ(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::XZX) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::XZX(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::YXY) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::YXY(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::XYZ) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::XYZ(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::YZX) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::YZX(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::ZXY) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::ZXY(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::XZY) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::XZY(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::ZYX) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::ZYX(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::YXZ) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::YXZ(alpha, beta, gamma);
        }
    }

    /**
     * @brief Access operator for the elements of the direction cosine matrix.
     *
     * @param row The row index (0, 1, or 2).
     * @param col The column index (0, 1, or 2).
     * @return Unitless& Reference to the element at the specified row and column.
     */
    inline constexpr Unitless& operator[](std::size_t row, std::size_t col) { return _matrix[row][col]; }

    /**
     * @brief Const access operator for the elements of the direction cosine matrix.
     *
     * @param row The row index (0, 1, or 2).
     * @param col The column index (0, 1, or 2).
     * @return const Unitless& Reference to the element at the specified row and column.
     */
    inline constexpr const Unitless& operator[](std::size_t row, std::size_t col) const { return _matrix[row][col]; }

    /**
     * @brief Apply the direction cosine matrix to a CartesianVector.
     *
     * @tparam Value_T The type of the vector components.
     * @tparam Frame_T The frame of the CartesianVector.
     * @param vec The CartesianVector to which the DCM will be applied.
     * @return CartesianVector<Value_T, Out_Frame_T> The transformed CartesianVector in the output frame.
     */
    template <typename Value_T>
    inline constexpr CartesianVector<Value_T, Out_Frame_T> operator*(const CartesianVector<Value_T, In_Frame_T>& vec) const
    {
        return CartesianVector<Value_T, Out_Frame_T>(row(0).dot(vec), row(1).dot(vec), row(2).dot(vec));
    }
    /**
     * @brief Get a specific row of the direction cosine matrix.
     *
     * @param idx The index of the row to retrieve (0, 1, or 2).
     * @return const CartesianVector<Value_T, In_Frame_T>& The requested row as a CartesianVector.
     */
    inline constexpr CartesianVector<Unitless, In_Frame_T> row(const std::size_t& idx) const
    {
        return { _matrix[idx][0], _matrix[idx][1], _matrix[idx][2] };
    }

    /**
     * @brief Get the trace of the direction cosine matrix (the sum of the diagonal elements).
     *
     * @return Unitless The trace of the direction cosine matrix.
     */
    inline constexpr Unitless trace() const { return _matrix[0][0] + _matrix[1][1] + _matrix[2][2]; }

    /**
     * @brief Get the determinant of the direction cosine matrix.
     *
     * @return Unitless The determinant of the direction cosine matrix.
     */
    inline constexpr Unitless determinant() const
    {
        return _matrix[0][0] * (_matrix[1][1] * _matrix[2][2] - _matrix[1][2] * _matrix[2][1]) -
               _matrix[0][1] * (_matrix[1][0] * _matrix[2][2] - _matrix[1][2] * _matrix[2][0]) +
               _matrix[0][2] * (_matrix[1][0] * _matrix[2][1] - _matrix[1][1] * _matrix[2][0]);
    }

    /**
     * @brief Normalizes the direction cosine matrix to ensure it represents a valid rotation.
     *
     * This method scales the elements of the matrix so that the determinant is 1, which is a requirement for a
     * valid rotation matrix. If the determinant is zero, an exception is thrown since the matrix cannot be
     * normalized. Uses a linear approximation when the determinant is close to 1 for numerical efficiency.
     */
    inline constexpr void normalize()
    {
        using namespace mp_units;

        const Unitless det = determinant();
        if (is_eq_zero(det)) {
            throw std::runtime_error("Cannot normalize a zero-value determinant DCM. The matrix is likely singular.");
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

  private:
    std::array<std::array<Unitless, 3>, 3> _matrix; //!< 3x3 matrix to hold the direction cosines.

    /**
     * @brief Normalizes the direction cosine matrix by scaling all elements by the given factor.
     *
     * @param scale The factor to scale the matrix elements by to achieve normalization.
     */
    inline constexpr void _normalize(const Unitless& scale)
    {
        for (auto& row : _matrix) {
            for (auto& element : row) {
                element *= scale;
                // Avoid very small values that should be zero
                if (mp_units::abs(element) < 1.0e-15 * one) { element = 0.0 * one; }
            }
        }
    }
};

/**
 * @brief Alias for DirectionCosineMatrix with a specific output frame type.
 *
 * This alias simplifies the usage of DirectionCosineMatrix by allowing the user to specify the output frame type.
 *
 * @tparam Out_Frame_T The frame type to which the DCM applies.
 */
template <typename In_Frame_T, typename Out_Frame_T>
using DCM = DirectionCosineMatrix<In_Frame_T, Out_Frame_T>;

// Defined template function and then delete it so we cosAlphan enforce lookup restrictions
template <typename Frame_T, typename Frame_U>
inline constexpr DCM<Frame_T, Frame_U> get_dcm(const Date& date) = delete;

} // namespace astro
} // namespace astrea