/**
 * @file DirectionCosineMatrixRate.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the DirectionCosineMatrixRate class in the astro namespace
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
#include <astro/frames/framework/DirectionCosineMatrixRate.hpp>
#include <astro/frames/framework/Matrix3x3.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

template <IsFrame auto in_frame, IsFrame auto out_frame>
class DirectionCosineMatrixRateAccel;

/**
 * @brief Class representing a direction cosine matrix (DCM) for transforming vectors between state/frames.
 *
 * This class provides methods to create DCMs for various rotations and to apply them to vectors.
 *
 * @tparam out_frame The frame type to which the DCM applies.
 */
template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
struct DirectionCosineMatrixRate : public Matrix3x3<Frequency> {

    static constexpr auto in_frame  = _in_frame_;  //!< The input frame of the DCM.
    static constexpr auto out_frame = _out_frame_; //!< The output frame of the DCM

    /**
     * @brief Constructor for DirectionCosineMatrixRate from an array of CartesianVectors.
     *
     * @param matrix An array containing the three rows of the DCM rate, each represented as a CartesianVector.
     */
    inline constexpr DirectionCosineMatrixRate(const std::array<Frequency, 9>& matrix) :
        Matrix3x3<Frequency>{ matrix }
    {
    }

    /**
     * @brief Constructor for DirectionCosineMatrixRate from three rows of CartesianVectors.
     *
     * @param row1 The first row of the DCM rate.
     * @param row2 The second row of the DCM rate.
     * @param row3 The third row of the DCM rate.
     */
    inline constexpr DirectionCosineMatrixRate(
        const std::array<Frequency, 3>& row1,
        const std::array<Frequency, 3>& row2,
        const std::array<Frequency, 3>& row3
    ) :
        Matrix3x3<Frequency>{ row1, row2, row3 }
    {
    }

    /**
     * @brief Constructor for DirectionCosineMatrixRate from a Matrix3x3 of Frequency.
     *
     * @param matrix A Matrix3x3 containing the elements of the DCM rate.
     */
    inline constexpr DirectionCosineMatrixRate(const Matrix3x3<Frequency>& matrix) :
        Matrix3x3<Frequency>{ matrix }
    {
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis.
     *
     * @param theta The angle of rotation around the X-axis.
     * @param thetaDot The rate of change of the angle of rotation around the X-axis.
     * @return DirectionCosineMatrixRate<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<in_frame, out_frame> X(const Angle& theta, const AngularRate& thetaDot)
    {
        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);
        return DirectionCosineMatrixRate<in_frame, out_frame>{ { 1.0 * one / s, 0.0 * one / s, 0.0 * one / s },
                                                               { 0.0 * one / s, -thetaDot * sinTheta / s, -thetaDot * cosTheta / s },
                                                               { 0.0 * one / s, thetaDot * cosTheta / s, thetaDot * sinTheta / s } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis.
     *
     * @param theta The angle of rotation around the Y-axis.
     * @param thetaDot The rate of change of the angle of rotation around the Y-axis.
     * @return DirectionCosineMatrixRate<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<in_frame, out_frame> Y(const Angle& theta, const AngularRate& thetaDot)
    {
        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);
        return DirectionCosineMatrixRate<in_frame, out_frame>{ { -thetaDot * sinTheta / s, 0.0 * one / s, thetaDot * cosTheta / s },
                                                               { 0.0 * one / s, 0.0 * one / s, 0.0 * one / s },
                                                               { -thetaDot * cosTheta / s, 0.0 * one / s, -thetaDot * sinTheta / s } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis.
     *
     * @param theta The angle of rotation around the Z-axis.
     * @param thetaDot The rate of change of the angle of rotation around the Z-axis.
     * @return DirectionCosineMatrixRate<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<in_frame, out_frame> Z(const Angle& theta, const AngularRate& thetaDot)
    {
        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);
        return DirectionCosineMatrixRate<in_frame, out_frame>{ { -thetaDot * sinTheta / s, -thetaDot * cosTheta / s, 0.0 * one / s },
                                                               { thetaDot * cosTheta / s, -thetaDot * sinTheta / s, 0.0 * one / s },
                                                               { 0.0 * one / s, 0.0 * one / s, 0.0 * one / s } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis, the Z-axis, and the X-axis again.
     *
     * @param alpha The angle of rotation around the X-axis.
     * @param beta The angle of rotation around the Z-axis.
     * @param gamma The angle of rotation around the X-axis.
     * @param alphaDot The rate of change of the angle of rotation around the X-axis.
     * @param betaDot The rate of change of the angle of rotation around the Z-axis.
     * @param gammaDot The rate of change of the angle of rotation around the X-axis.
     * @return DirectionCosineMatrixRate<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<in_frame, out_frame>
        XZX(const Angle& alpha, const Angle& beta, const Angle& gamma, const AngularRate& alphaDot, const AngularRate& betaDot, const AngularRate& gammaDot)
    {
        const auto X     = DirectionCosineMatrix<in_frame, out_frame>::X(alpha);
        const auto Xdot  = DirectionCosineMatrixRate<in_frame, out_frame>::X(alpha, alphaDot);
        const auto Z     = DirectionCosineMatrix<in_frame, out_frame>::Z(beta);
        const auto Zdot  = DirectionCosineMatrixRate<in_frame, out_frame>::Z(beta, betaDot);
        const auto X2    = DirectionCosineMatrix<in_frame, out_frame>::X(gamma);
        const auto X2dot = DirectionCosineMatrixRate<in_frame, out_frame>::X(gamma, gammaDot);
        return Xdot * Z * X2 + X * Zdot * X2 + X * Z * X2dot;
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis, the Y-axis, and the X-axis again.
     *
     * @param alpha The angle of rotation around the X-axis.
     * @param beta The angle of rotation around the Y-axis.
     * @param gamma The angle of rotation around the X-axis.
     * @param alphaDot The rate of change of the angle of rotation around the X-axis.
     * @param betaDot The rate of change of the angle of rotation around the Y-axis.
     * @param gammaDot The rate of change of the angle of rotation around the X-axis.
     * @return DirectionCosineMatrixRate<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<in_frame, out_frame>
        XYX(const Angle& alpha, const Angle& beta, const Angle& gamma, const AngularRate& alphaDot, const AngularRate& betaDot, const AngularRate& gammaDot)
    {
        const auto X     = DirectionCosineMatrix<in_frame, out_frame>::X(alpha);
        const auto Xdot  = DirectionCosineMatrixRate<in_frame, out_frame>::X(alpha, alphaDot);
        const auto Y     = DirectionCosineMatrix<in_frame, out_frame>::Y(beta);
        const auto Ydot  = DirectionCosineMatrixRate<in_frame, out_frame>::Y(beta, betaDot);
        const auto X2    = DirectionCosineMatrix<in_frame, out_frame>::X(gamma);
        const auto X2dot = DirectionCosineMatrixRate<in_frame, out_frame>::X(gamma, gammaDot);
        return Xdot * Y * X2 + X * Ydot * X2 + X * Y * X2dot;
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis, the Z-axis, and the Y-axis again.
     *
     * @param alpha The angle of rotation around the Y-axis.
     * @param beta The angle of rotation around the Z-axis.
     * @param gamma The angle of rotation around the Y-axis.
     * @param alphaDot The rate of change of the angle of rotation around the Y-axis.
     * @param betaDot The rate of change of the angle of rotation around the Z-axis.
     * @param gammaDot The rate of change of the angle of rotation around the Y-axis.
     * @return DirectionCosineMatrixRate<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<in_frame, out_frame>
        YZY(const Angle& alpha, const Angle& beta, const Angle& gamma, const AngularRate& alphaDot, const AngularRate& betaDot, const AngularRate& gammaDot)
    {
        const auto Y     = DirectionCosineMatrix<in_frame, out_frame>::Y(alpha);
        const auto Ydot  = DirectionCosineMatrixRate<in_frame, out_frame>::Y(alpha, alphaDot);
        const auto Z     = DirectionCosineMatrix<in_frame, out_frame>::Z(beta);
        const auto Zdot  = DirectionCosineMatrixRate<in_frame, out_frame>::Z(beta, betaDot);
        const auto Y2    = DirectionCosineMatrix<in_frame, out_frame>::Y(gamma);
        const auto Y2dot = DirectionCosineMatrixRate<in_frame, out_frame>::Y(gamma, gammaDot);
        return Ydot * Z * Y2 + Y * Zdot * Y2 + Y * Z * Y2dot;
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis, the X-axis, and the Z-axis again.
     *
     * @param alpha The angle of rotation around the Z-axis.
     * @param beta The angle of rotation around the X-axis.
     * @param gamma The angle of rotation around the Z-axis.
     * @param alphaDot The rate of change of the angle of rotation around the Z-axis.
     * @param betaDot The rate of change of the angle of rotation around the X-axis.
     * @param gammaDot The rate of change of the angle of rotation around the Z-axis.
     * @return DirectionCosineMatrixRate<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<in_frame, out_frame>
        ZXZ(const Angle& alpha, const Angle& beta, const Angle& gamma, const AngularRate& alphaDot, const AngularRate& betaDot, const AngularRate& gammaDot)
    {
        const auto Z     = DirectionCosineMatrix<in_frame, out_frame>::Z(alpha);
        const auto Zdot  = DirectionCosineMatrixRate<in_frame, out_frame>::Z(alpha, alphaDot);
        const auto X     = DirectionCosineMatrix<in_frame, out_frame>::X(beta);
        const auto Xdot  = DirectionCosineMatrixRate<in_frame, out_frame>::X(beta, betaDot);
        const auto Z2    = DirectionCosineMatrix<in_frame, out_frame>::Z(gamma);
        const auto Z2dot = DirectionCosineMatrixRate<in_frame, out_frame>::Z(gamma, gammaDot);
        return Zdot * X * Z2 + Z * Xdot * Z2 + Z * X * Z2dot;
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis, the Y-axis, and the Z-axis again.
     *
     * @param alpha The angle of rotation around the Z-axis.
     * @param beta The angle of rotation around the Y-axis.
     * @param gamma The angle of rotation around the Z-axis.
     * @param alphaDot The rate of change of the angle of rotation around the Z-axis.
     * @param betaDot The rate of change of the angle of rotation around the Y-axis.
     * @param gammaDot The rate of change of the angle of rotation around the Z-axis.
     * @return DirectionCosineMatrixRate<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<in_frame, out_frame>
        ZYZ(const Angle& alpha, const Angle& beta, const Angle& gamma, const AngularRate& alphaDot, const AngularRate& betaDot, const AngularRate& gammaDot)
    {
        const auto Z     = DirectionCosineMatrix<in_frame, out_frame>::Z(alpha);
        const auto Zdot  = DirectionCosineMatrixRate<in_frame, out_frame>::Z(alpha, alphaDot);
        const auto Y     = DirectionCosineMatrix<in_frame, out_frame>::Y(beta);
        const auto Ydot  = DirectionCosineMatrixRate<in_frame, out_frame>::Y(beta, betaDot);
        const auto Z2    = DirectionCosineMatrix<in_frame, out_frame>::Z(gamma);
        const auto Z2dot = DirectionCosineMatrixRate<in_frame, out_frame>::Z(gamma, gammaDot);
        return Zdot * Y * Z2 + Z * Ydot * Z2 + Z * Y * Z2dot;
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis, the X-axis, and the Y-axis again.
     *
     * @param alpha The angle of rotation around the Y-axis.
     * @param beta The angle of rotation around the X-axis.
     * @param gamma The angle of rotation around the Y-axis.
     * @param alphaDot The rate of change of the angle of rotation around the Y-axis.
     * @param betaDot The rate of change of the angle of rotation around the X-axis.
     * @param gammaDot The rate of change of the angle of rotation around the Y-axis.
     * @return DirectionCosineMatrixRate<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<in_frame, out_frame>
        YXY(const Angle& alpha, const Angle& beta, const Angle& gamma, const AngularRate& alphaDot, const AngularRate& betaDot, const AngularRate& gammaDot)
    {
        const auto Y     = DirectionCosineMatrix<in_frame, out_frame>::Y(alpha);
        const auto Ydot  = DirectionCosineMatrixRate<in_frame, out_frame>::Y(alpha, alphaDot);
        const auto X     = DirectionCosineMatrix<in_frame, out_frame>::X(beta);
        const auto Xdot  = DirectionCosineMatrixRate<in_frame, out_frame>::X(beta, betaDot);
        const auto Y2    = DirectionCosineMatrix<in_frame, out_frame>::Y(gamma);
        const auto Y2dot = DirectionCosineMatrixRate<in_frame, out_frame>::Y(gamma, gammaDot);
        return Ydot * X * Y2 + Y * Xdot * Y2 + Y * X * Y2dot;
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis, then Y-axis, then Z-axis.
     *
     * @param alpha The angle of rotation around the X-axis.
     * @param beta The angle of rotation around the Y-axis.
     * @param gamma The angle of rotation around the Z-axis.
     * @param alphaDot The rate of change of the angle of rotation around the X-axis.
     * @param betaDot The rate of change of the angle of rotation around the Y-axis.
     * @param gammaDot The rate of change of the angle of rotation around the Z-axis.
     * @return DirectionCosineMatrixRate<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<in_frame, out_frame>
        XYZ(const Angle& alpha, const Angle& beta, const Angle& gamma, const AngularRate& alphaDot, const AngularRate& betaDot, const AngularRate& gammaDot)
    {
        const auto X    = DirectionCosineMatrix<in_frame, out_frame>::X(alpha);
        const auto Xdot = DirectionCosineMatrixRate<in_frame, out_frame>::X(alpha, alphaDot);
        const auto Y    = DirectionCosineMatrix<in_frame, out_frame>::Y(beta);
        const auto Ydot = DirectionCosineMatrixRate<in_frame, out_frame>::Y(beta, betaDot);
        const auto Z    = DirectionCosineMatrix<in_frame, out_frame>::Z(gamma);
        const auto Zdot = DirectionCosineMatrixRate<in_frame, out_frame>::Z(gamma, gammaDot);
        return Xdot * Y * Z + X * Ydot * Z + X * Y * Zdot;
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis, then Z-axis, then X-axis.
     *
     * @param alpha The angle of rotation around the Y-axis.
     * @param beta The angle of rotation around the Z-axis.
     * @param gamma The angle of rotation around the X-axis.
     * @param alphaDot The rate of change of the angle of rotation around the Y-axis.
     * @param betaDot The rate of change of the angle of rotation around the Z-axis.
     * @param gammaDot The rate of change of the angle of rotation around the X-axis.
     * @return DirectionCosineMatrixRate<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<in_frame, out_frame>
        YZX(const Angle& alpha, const Angle& beta, const Angle& gamma, const AngularRate& alphaDot, const AngularRate& betaDot, const AngularRate& gammaDot)
    {
        const auto Y    = DirectionCosineMatrix<in_frame, out_frame>::Y(alpha);
        const auto Ydot = DirectionCosineMatrixRate<in_frame, out_frame>::Y(alpha, alphaDot);
        const auto Z    = DirectionCosineMatrix<in_frame, out_frame>::Z(beta);
        const auto Zdot = DirectionCosineMatrixRate<in_frame, out_frame>::Z(beta, betaDot);
        const auto X    = DirectionCosineMatrix<in_frame, out_frame>::X(gamma);
        const auto Xdot = DirectionCosineMatrixRate<in_frame, out_frame>::X(gamma, gammaDot);
        return Ydot * Z * X + Y * Zdot * X + Y * Z * Xdot;
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis, then X-axis, then Y-axis.
     *
     * @param alpha The angle of rotation around the Z-axis.
     * @param beta The angle of rotation around the X-axis.
     * @param gamma The angle of rotation around the Y-axis.
     * @param alphaDot The rate of change of the angle of rotation around the Z-axis.
     * @param betaDot The rate of change of the angle of rotation around the X-axis.
     * @param gammaDot The rate of change of the angle of rotation around the Y-axis.
     * @return DirectionCosineMatrixRate<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<in_frame, out_frame>
        ZXY(const Angle& alpha, const Angle& beta, const Angle& gamma, const AngularRate& alphaDot, const AngularRate& betaDot, const AngularRate& gammaDot)
    {
        const auto Z    = DirectionCosineMatrix<in_frame, out_frame>::Z(alpha);
        const auto Zdot = DirectionCosineMatrixRate<in_frame, out_frame>::Z(alpha, alphaDot);
        const auto X    = DirectionCosineMatrix<in_frame, out_frame>::X(beta);
        const auto Xdot = DirectionCosineMatrixRate<in_frame, out_frame>::X(beta, betaDot);
        const auto Y    = DirectionCosineMatrix<in_frame, out_frame>::Y(gamma);
        const auto Ydot = DirectionCosineMatrixRate<in_frame, out_frame>::Y(gamma, gammaDot);
        return Zdot * X * Y + Z * Xdot * Y + Z * X * Ydot;
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis, then Z-axis, then Y-axis.
     *
     * @param alpha The angle of rotation around the X-axis.
     * @param beta The angle of rotation around the Z-axis.
     * @param gamma The angle of rotation around the Y-axis.
     * @param alphaDot The rate of change of the angle of rotation around the X-axis.
     * @param betaDot The rate of change of the angle of rotation around the Z-axis.
     * @param gammaDot The rate of change of the angle of rotation around the Y-axis.
     * @return DirectionCosineMatrixRate<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<in_frame, out_frame>
        XZY(const Angle& alpha, const Angle& beta, const Angle& gamma, const AngularRate& alphaDot, const AngularRate& betaDot, const AngularRate& gammaDot)
    {
        return DirectionCosineMatrixRate<in_frame, out_frame>::YZX(gamma, gammaDot, beta, betaDot, alpha, alphaDot);
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis, then Y-axis, then X-axis.
     *
     * @param alpha The angle of rotation around the Z-axis.
     * @param beta The angle of rotation around the Y-axis.
     * @param gamma The angle of rotation around the X-axis.
     * @param alphaDot The rate of change of the angle of rotation around the Z-axis.
     * @param betaDot The rate of change of the angle of rotation around the Y-axis.
     * @param gammaDot The rate of change of the angle of rotation around the X-axis.
     * @return DirectionCosineMatrixRate<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<in_frame, out_frame>
        ZYX(const Angle& alpha, const Angle& beta, const Angle& gamma, const AngularRate& alphaDot, const AngularRate& betaDot, const AngularRate& gammaDot)
    {
        return DirectionCosineMatrixRate<in_frame, out_frame>::XYZ(gamma, gammaDot, beta, betaDot, alpha, alphaDot);
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis, then X-axis, then Z-axis.
     *
     * @param alpha The angle of rotation around the Y-axis.
     * @param beta The angle of rotation around the X-axis.
     * @param gamma The angle of rotation around the Z-axis.
     * @param alphaDot The rate of change of the angle of rotation around the Y-axis.
     * @param betaDot The rate of change of the angle of rotation around the X-axis.
     * @param gammaDot The rate of change of the angle of rotation around the Z-axis.
     * @return DirectionCosineMatrixRate<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<in_frame, out_frame>
        YXZ(const Angle& alpha, const Angle& beta, const Angle& gamma, const AngularRate& alphaDot, const AngularRate& betaDot, const AngularRate& gammaDot)
    {
        return DirectionCosineMatrixRate<in_frame, out_frame>::ZXY(gamma, gammaDot, beta, betaDot, alpha, alphaDot);
    }

    /**
     * @brief Creates an identity direction cosine matrix (no rotation).
     *
     * @return DirectionCosineMatrixRate<out_frame> The identity direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<in_frame, out_frame> identity()
    {
        return DirectionCosineMatrixRate<in_frame, out_frame>{ Matrix3x3<Frequency>::identity() };
    }

    /**
     * @brief Transposes the direction cosine matrix, effectively inverting the transformation.
     *
     * @return DirectionCosineMatrixRate<out_frame, in_frame> The transposed direction cosine matrix.
     */
    inline constexpr DirectionCosineMatrixRate<out_frame, in_frame> transpose() const
    {
        return DirectionCosineMatrixRate<out_frame, in_frame>{ static_cast<Matrix3x3<Frequency>>(*this).transpose() };
    }

    /**
     * @brief Creates a direction cosine matrix from Euler angles based on a specified rotation sequence.
     *
     * @tparam sequence The rotation sequence to use for the Euler angles (e.g., XYZ, ZYX, etc.).
     * @param alpha The first Euler angle (rotation around the first axis in the sequence).
     * @param beta The second Euler angle (rotation around the second axis in the sequence).
     * @param gamma The third Euler angle (rotation around the third axis in the sequence).
     * @param alphaDot The rate of change of the first Euler angle.
     * @param betaDot The rate of change of the second Euler angle.
     * @param gammaDot The rate of change of the third Euler angle.
     * @return DirectionCosineMatrixRate<out_frame> The resulting direction cosine matrix.
     */
    template <RotationSequence sequence>
    static inline constexpr DirectionCosineMatrixRate<in_frame, out_frame>
        from_euler_angles(const Angle& alpha, const Angle& beta, const Angle& gamma, const AngularRate& alphaDot, const AngularRate& betaDot, const AngularRate& gammaDot)
    {
        if constexpr (sequence == RotationSequence::ZXZ) {
            return DirectionCosineMatrixRate<in_frame, out_frame>::ZXZ(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::XYX) {
            return DirectionCosineMatrixRate<in_frame, out_frame>::XYX(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::YZY) {
            return DirectionCosineMatrixRate<in_frame, out_frame>::YZY(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::ZYZ) {
            return DirectionCosineMatrixRate<in_frame, out_frame>::ZYZ(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::XZX) {
            return DirectionCosineMatrixRate<in_frame, out_frame>::XZX(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::YXY) {
            return DirectionCosineMatrixRate<in_frame, out_frame>::YXY(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::XYZ) {
            return DirectionCosineMatrixRate<in_frame, out_frame>::XYZ(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::YZX) {
            return DirectionCosineMatrixRate<in_frame, out_frame>::YZX(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::ZXY) {
            return DirectionCosineMatrixRate<in_frame, out_frame>::ZXY(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::XZY) {
            return DirectionCosineMatrixRate<in_frame, out_frame>::XZY(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::ZYX) {
            return DirectionCosineMatrixRate<in_frame, out_frame>::ZYX(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::YXZ) {
            return DirectionCosineMatrixRate<in_frame, out_frame>::YXZ(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
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
    inline constexpr CartesianVector<decltype(Value_T{} / s), out_frame>
        operator*(const CartesianVector<Value_T, in_frame>& vec) const
    {
        return { row(0).dot(vec), row(1).dot(vec), row(2).dot(vec) };
    }

    /**
     * @brief Compose this direction cosine matrix rate with a DCM, resulting in a new DCM rate.
     *
     * @tparam in_frame_u The input frame of the other DCM.
     * @tparam out_frame_u The output frame of the other DCM.
     * @param dcm The other DCM to compose with this one.
     * @return DirectionCosineMatrixRate<in_frame, out_frame> The resulting composed DCM rate.
     */
    inline constexpr DirectionCosineMatrixRate<in_frame, out_frame> operator*(DirectionCosineMatrixRate<in_frame, out_frame> dcm) const
    {
        return { static_cast<Matrix3x3<Frequency>>(*this) * static_cast<Matrix3x3<Unitless>>(dcm) };
    }

    /**
     * @brief Compose two direction cosine matrices (matrix multiplication).
     *
     * Produces DCM<in_frame, new_out_frame> = this * rhs, where this is
     * DCM<in_frame, out_frame> and rhs is DCM<out_frame, new_out_frame>.
     *
     * @tparam new_out_frame The output frame of the right-hand-side DCM.
     * @param accel The right-hand-side DCM to compose with.
     * @return DirectionCosineMatrixRateAccel<in_frame, new_out_frame> The composed DCM.
     */
    template <IsFrame auto new_out_frame>
    inline constexpr DirectionCosineMatrixRateAccel<in_frame, new_out_frame>
        operator*(const DirectionCosineMatrixRate<out_frame, new_out_frame>& accel) const;

    /**
     * @brief Add two direction cosine matrices element-wise.
     *
     * @param other The other DCM to add to this DCM.
     * @return DirectionCosineMatrixRate<in_frame, out_frame> The resulting DCM after addition.
     */
    inline constexpr DirectionCosineMatrixRate operator+(const DirectionCosineMatrixRate& other) const
    {
        return { static_cast<Matrix3x3<Frequency>>(*this) + static_cast<Matrix3x3<Frequency>>(other) };
    }

    /**
     * @brief Negate the direction cosine matrix element-wise.
     *
     * @return DirectionCosineMatrixRate<in_frame, out_frame> The resulting DCM after negation.
     */
    inline constexpr DirectionCosineMatrixRate operator-() const
    {
        return { -static_cast<Matrix3x3<Frequency>>(*this) };
    }

    /**
     * @brief Subtract another direction cosine matrix from this one element-wise.
     *
     * @param other The other DCM to subtract from this DCM.
     * @return DirectionCosineMatrixRate<in_frame, out_frame> The resulting DCM after subtraction.
     */
    inline constexpr DirectionCosineMatrixRate operator-(const DirectionCosineMatrixRate& other) const
    {
        return { static_cast<Matrix3x3<Frequency>>(*this) - static_cast<Matrix3x3<Frequency>>(other) };
    }

    /**
     * @brief Multiply this direction cosine matrix by another DCM element-wise.
     *
     * Note: This is not the same as matrix multiplication (composition of rotations). This is an element-wise operation.
     *
     * @param other The other DCM to multiply with this DCM.
     * @return DirectionCosineMatrixRate<in_frame, out_frame> The resulting DCM after element-wise multiplication.
     */
    inline constexpr DirectionCosineMatrixRate operator*(const DirectionCosineMatrixRate& other) const
    {
        return { static_cast<Matrix3x3<Frequency>>(*this) * static_cast<Matrix3x3<Frequency>>(other) };
    }
};

/**
 * @brief Alias for DirectionCosineMatrixRate with a specific output frame type.
 *
 * This alias simplifies the usage of DirectionCosineMatrixRate by allowing the user to specify the output frame type.
 *
 * @tparam out_frame The frame type to which the DCM applies.
 */
template <IsFrame auto in_frame, IsFrame auto out_frame>
using DcmRate = DirectionCosineMatrixRate<in_frame, out_frame>;

// Defined template function and then delete it so we can enforce lookup restrictions
template <IsFrame auto frame, IsFrame auto frame_u>
inline constexpr DcmRate<frame, frame_u> get_dcm_rate(const Date& date) = delete;

/**
 * @brief Compose a direction cosine matrix with a direction cosine matrix rate, resulting in a new direction cosine matrix rate.
 *
 * @tparam in_frame The input frame of the DCM and DCM rate.
 * @tparam out_frame The output frame of the DCM and DCM rate.
 * @param dcm The direction cosine matrix to compose with the DCM rate.
 * @param rate The direction cosine matrix rate to compose with the DCM.
 * @return DirectionCosineMatrixRate<in_frame, out_frame> The resulting composed DCM rate.
 */
template <IsFrame auto in_frame, IsFrame auto out_frame>
inline constexpr DirectionCosineMatrixRate<in_frame, out_frame>
    operator*(DirectionCosineMatrixRate<in_frame, out_frame> dcm, DirectionCosineMatrixRate<in_frame, out_frame> rate) const
{
    return DirectionCosineMatrixRate<in_frame, out_frame>{ static_cast<Matrix3x3<Frequency>>(dcm) *
                                                           static_cast<Matrix3x3<Unitless>>(rate) };
};

} // namespace astro
} // namespace astrea