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
#include <astro/frames/framework/Matrix3x3.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
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
 * @tparam out_frame The frame type to which the DCM applies.
 */
template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
class DirectionCosineMatrix : public Matrix3x3<Unitless> {

  public:
    static constexpr auto in_frame  = _in_frame_;  //!< The input frame of the DCM.
    static constexpr auto out_frame = _out_frame_; //!< The output frame of the DCM

    /**
     * @brief Constructor for DirectionCosineMatrix from an array of CartesianVectors.
     *
     * @param matrix An array containing the three rows of the DCM, each represented as a CartesianVector.
     */
    inline constexpr DirectionCosineMatrix(const std::array<Unitless, 9>& matrix) :
        Matrix3x3<Unitless>{ matrix }
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
        Matrix3x3<Unitless>{ row1, row2, row3 }
    {
        normalize();
    }

    inline constexpr DirectionCosineMatrix(const Matrix3x3<Unitless>& matrix) :
        Matrix3x3<Unitless>{ matrix }
    {
        normalize();
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis.
     *
     * @param theta The angle of rotation around the X-axis.
     * @return DirectionCosineMatrix<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<in_frame, out_frame> X(const Angle& theta)
    {
        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);
        return DirectionCosineMatrix<in_frame, out_frame>{ { 1.0 * one, 0.0 * one, 0.0 * one },
                                                           { 0.0 * one, cosTheta, -sinTheta },
                                                           { 0.0 * one, sinTheta, cosTheta } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis.
     *
     * @param theta The angle of rotation around the Y-axis.
     * @return DirectionCosineMatrix<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<in_frame, out_frame> Y(const Angle& theta)
    {
        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);
        return DirectionCosineMatrix<in_frame, out_frame>{ { cosTheta, 0.0 * one, sinTheta },
                                                           { 0.0 * one, 1.0 * one, 0.0 * one },
                                                           { -sinTheta, 0.0 * one, cosTheta } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis.
     *
     * @param theta The angle of rotation around the Z-axis.
     * @return DirectionCosineMatrix<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<in_frame, out_frame> Z(const Angle& theta)
    {
        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);
        return DirectionCosineMatrix<in_frame, out_frame>{ { cosTheta, -sinTheta, 0.0 * one },
                                                           { sinTheta, cosTheta, 0.0 * one },
                                                           { 0.0 * one, 0.0 * one, 1.0 * one } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis, the Z-axis, and the X-axis again.
     *
     * @param alpha The angle of rotation around the X-axis.
     * @param beta The angle of rotation around the Z-axis.
     * @param gamma The angle of rotation around the X-axis.
     * @return DirectionCosineMatrix<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<in_frame, out_frame> XZX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return DirectionCosineMatrix<in_frame, out_frame>{
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
     * @return DirectionCosineMatrix<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<in_frame, out_frame> XYX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return DirectionCosineMatrix<in_frame, out_frame>{
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
     * @return DirectionCosineMatrix<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<in_frame, out_frame> YZY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return DirectionCosineMatrix<in_frame, out_frame>{
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
     * @return DirectionCosineMatrix<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<in_frame, out_frame> ZXZ(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return DirectionCosineMatrix<in_frame, out_frame>{ { cosAlpha * cosGamma - cosBeta * sinAlpha * sinGamma,
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
     * @return DirectionCosineMatrix<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<in_frame, out_frame> ZYZ(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return DirectionCosineMatrix<in_frame, out_frame>{
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
     * @return DirectionCosineMatrix<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<in_frame, out_frame> YXY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return DirectionCosineMatrix<in_frame, out_frame>{
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
     * @return DirectionCosineMatrix<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<in_frame, out_frame> XYZ(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return DirectionCosineMatrix<in_frame, out_frame>{
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
     * @return DirectionCosineMatrix<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<in_frame, out_frame> YZX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return DirectionCosineMatrix<in_frame, out_frame>{
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
     * @return DirectionCosineMatrix<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<in_frame, out_frame> ZXY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return DirectionCosineMatrix<in_frame, out_frame>{
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
     * @return DirectionCosineMatrix<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<in_frame, out_frame> XZY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        return DirectionCosineMatrix<in_frame, out_frame>::YZX(gamma, beta, alpha);
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis, then Y-axis, then X-axis.
     *
     * @param alpha The angle of rotation around the Z-axis.
     * @param beta The angle of rotation around the Y-axis.
     * @param gamma The angle of rotation around the X-axis.
     * @return DirectionCosineMatrix<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<in_frame, out_frame> ZYX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        return DirectionCosineMatrix<in_frame, out_frame>::XYZ(gamma, beta, alpha);
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis, then X-axis, then Z-axis.
     *
     * @param alpha The angle of rotation around the Y-axis.
     * @param beta The angle of rotation around the X-axis.
     * @param gamma The angle of rotation around the Z-axis.
     * @return DirectionCosineMatrix<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<in_frame, out_frame> YXZ(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        return DirectionCosineMatrix<in_frame, out_frame>::ZXY(gamma, beta, alpha);
    }

    /**
     * @brief Creates a direction cosine matrix from three orthonormal vectors.
     *
     * @param x The unit vector in the X direction.
     * @param y The unit vector in the Y direction.
     * @param z The unit vector in the Z direction.
     * @return DirectionCosineMatrix<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<in_frame, out_frame> from_vectors(
        const CartesianVector<Unitless, in_frame>& x,
        const CartesianVector<Unitless, in_frame>& y,
        const CartesianVector<Unitless, in_frame>& z
    )
    {
        return DirectionCosineMatrix<in_frame, out_frame>{ { x[0], x[1], x[2] }, { y[0], y[1], y[2] }, { z[0], z[1], z[2] } };
    }

    /**
     * @brief Creates an identity direction cosine matrix (no rotation).
     *
     * @return DirectionCosineMatrix<out_frame> The identity direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<in_frame, out_frame> identity()
    {
        return DirectionCosineMatrix<in_frame, out_frame>{ Matrix3x3<Unitless>::identity() };
    }

    static inline constexpr DirectionCosineMatrix<in_frame, out_frame> zero()
    {
        return DirectionCosineMatrix<in_frame, out_frame>{ Matrix3x3<Unitless>::zero() };
    }

    /**
     * @brief Transposes the direction cosine matrix, effectively inverting the transformation.
     *
     * @return DirectionCosineMatrix<out_frame, in_frame> The transposed direction cosine matrix.
     */
    inline constexpr DirectionCosineMatrix<out_frame, in_frame> transpose() const
    {
        return DirectionCosineMatrix<out_frame, in_frame>{ static_cast<Matrix3x3<Unitless>>(*this).transpose() };
    }

    /**
     * @brief Creates a direction cosine matrix from Euler angles based on a specified rotation sequence.
     *
     * @tparam sequence The rotation sequence to use for the Euler angles (e.g., XYZ, ZYX, etc.).
     * @param alpha The first Euler angle (rotation around the first axis in the sequence).
     * @param beta The second Euler angle (rotation around the second axis in the sequence).
     * @param gamma The third Euler angle (rotation around the third axis in the sequence).
     * @return DirectionCosineMatrix<out_frame> The resulting direction cosine matrix.
     */
    template <RotationSequence sequence>
    static inline constexpr DirectionCosineMatrix<in_frame, out_frame>
        from_euler_angles(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        if constexpr (sequence == RotationSequence::ZXZ) {
            return DirectionCosineMatrix<in_frame, out_frame>::ZXZ(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::XYX) {
            return DirectionCosineMatrix<in_frame, out_frame>::XYX(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::YZY) {
            return DirectionCosineMatrix<in_frame, out_frame>::YZY(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::ZYZ) {
            return DirectionCosineMatrix<in_frame, out_frame>::ZYZ(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::XZX) {
            return DirectionCosineMatrix<in_frame, out_frame>::XZX(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::YXY) {
            return DirectionCosineMatrix<in_frame, out_frame>::YXY(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::XYZ) {
            return DirectionCosineMatrix<in_frame, out_frame>::XYZ(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::YZX) {
            return DirectionCosineMatrix<in_frame, out_frame>::YZX(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::ZXY) {
            return DirectionCosineMatrix<in_frame, out_frame>::ZXY(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::XZY) {
            return DirectionCosineMatrix<in_frame, out_frame>::XZY(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::ZYX) {
            return DirectionCosineMatrix<in_frame, out_frame>::ZYX(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::YXZ) {
            return DirectionCosineMatrix<in_frame, out_frame>::YXZ(alpha, beta, gamma);
        }
    }

    /**
     * @brief Apply the direction cosine matrix to a CartesianVector.
     *
     * @tparam Value_T The type of the vector components.
     * @param vec The CartesianVector to which the DCM will be applied.
     * @return CartesianVector<Value_T, out_frame> The transformed CartesianVector in the output frame.
     */
    template <typename Value_T>
    inline constexpr CartesianVector<Value_T, out_frame> operator*(const CartesianVector<Value_T, in_frame>& vec) const
    {
        return { Matrix3x3<Unitless>::operator*(vec) };
    }

    /**
     * @brief Compose two direction cosine matrices (matrix multiplication). This creates a new rotation.
     *
     * Produces DCM<in_frame, new_out_frame> = this * rhs, where this is
     * DCM<in_frame, out_frame> and rhs is DCM<out_frame, new_out_frame>.
     *
     * @tparam new_out_frame The output frame of the right-hand-side DCM.
     * @param other The right-hand-side DCM to compose with.
     * @return DirectionCosineMatrix<in_frame, new_out_frame> The composed DCM.
     */
    template <IsFrame auto new_out_frame>
    inline constexpr DirectionCosineMatrix<in_frame, new_out_frame>
        operator*(const DirectionCosineMatrix<out_frame, new_out_frame>& other) const
    {
        return { Matrix3x3<Unitless>::operator*(other) };
    }

    /**
     * @brief Add two direction cosine matrices element-wise.
     *
     * @param other The other DCM to add to this DCM.
     * @return DirectionCosineMatrix<in_frame, out_frame> The resulting DCM after addition.
     */
    inline constexpr DirectionCosineMatrix operator+(const DirectionCosineMatrix& other) const
    {
        return { static_cast<Matrix3x3<Unitless>>(*this) + static_cast<Matrix3x3<Unitless>>(other) };
    }

    /**
     * @brief Negate the direction cosine matrix element-wise.
     *
     * @return DirectionCosineMatrix<in_frame, out_frame> The resulting DCM after negation.
     */
    inline constexpr DirectionCosineMatrix operator-() const { return { -static_cast<Matrix3x3<Unitless>>(*this) }; }

    /**
     * @brief Subtract another direction cosine matrix from this one element-wise.
     *
     * @param other The other DCM to subtract from this DCM.
     * @return DirectionCosineMatrix<in_frame, out_frame> The resulting DCM after subtraction.
     */
    inline constexpr DirectionCosineMatrix operator-(const DirectionCosineMatrix& other) const
    {
        return { static_cast<Matrix3x3<Unitless>>(*this) - static_cast<Matrix3x3<Unitless>>(other) };
    }

    /**
     * @brief Multiply this direction cosine matrix by another DCM element-wise.
     *
     * Note: This is not the same as matrix multiplication (composition of rotations). This is an element-wise operation.
     *
     * @param other The other DCM to multiply with this DCM.
     * @return DirectionCosineMatrix<in_frame, out_frame> The resulting DCM after element-wise multiplication.
     */
    inline constexpr DirectionCosineMatrix operator*(const DirectionCosineMatrix& other) const
    {
        return { static_cast<Matrix3x3<Unitless>>(*this) * static_cast<Matrix3x3<Unitless>>(other) };
    }
};

/**
 * @brief Alias for DirectionCosineMatrix with a specific output frame type.
 *
 * This alias simplifies the usage of DirectionCosineMatrix by allowing the user to specify the output frame type.
 *
 * @tparam out_frame The frame type to which the DCM applies.
 */
template <IsFrame auto in_frame, IsFrame auto out_frame>
using DCM = DirectionCosineMatrix<in_frame, out_frame>;

// Defined template function and then delete it so we can enforce lookup restrictions
template <IsFrame auto frame, IsFrame auto frame_u>
inline constexpr DCM<frame, frame_u> get_dcm(const Date& date) = delete;

} // namespace astro
} // namespace astrea