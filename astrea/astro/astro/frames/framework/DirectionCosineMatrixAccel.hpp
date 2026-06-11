/**
 * @file DirectionCosineMatrixAccel.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the DirectionCosineMatrixAccel class in the astro namespace
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

using namespace mp_units;
using mp_units::si::unit_symbols::s;

} // namespace

/**
 * @brief Class representing a direction cosine matrix (DCM) for transforming vectors between state/frames.
 *
 * This class provides methods to create DCMs for various rotations and to apply them to vectors.
 *
 * @tparam out_frame The frame type to which the DCM applies.
 */
template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
struct DirectionCosineMatrixAccel : public Matrix3x3<quantity<one / pow<2>(s)>> {

    static constexpr auto in_frame  = _in_frame_;  //!< The input frame of the DCM.
    static constexpr auto out_frame = _out_frame_; //!< The output frame of the DCM

    /**
     * @brief Constructor for DirectionCosineMatrixAccel from an array of CartesianVectors.
     *
     * @param matrix An array containing the three rows of the DCM, each represented as a CartesianVector.
     */
    inline constexpr DirectionCosineMatrixAccel(const std::array<quantity<one / pow<2>(s)>, 9>& matrix) :
        Matrix3x3<quantity<one / pow<2>(s)>>{ matrix }
    {
    }

    /**
     * @brief Constructor for DirectionCosineMatrixAccel from three rows of CartesianVectors.
     *
     * @param row1 An array containing the three elements of the first row of the DCM.
     * @param row2 An array containing the three elements of the second row of the DCM.
     * @param row3 An array containing the three elements of the third row of the DCM.
     */
    inline constexpr DirectionCosineMatrixAccel(
        const std::array<quantity<one / pow<2>(s)>, 3>& row1,
        const std::array<quantity<one / pow<2>(s)>, 3>& row2,
        const std::array<quantity<one / pow<2>(s)>, 3>& row3
    ) :
        Matrix3x3<quantity<one / pow<2>(s)>>{ row1, row2, row3 }
    {
    }

    /**
     * @brief Constructor for DirectionCosineMatrixAccel from a Matrix3x3 of quantity<one / pow<2>(s)>.
     *
     * @param matrix A Matrix3x3 containing the elements of the DCM.
     */
    inline constexpr DirectionCosineMatrixAccel(const Matrix3x3<quantity<one / pow<2>(s)>>& matrix) :
        Matrix3x3<quantity<one / pow<2>(s)>>{ matrix }
    {
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis.
     *
     * @param theta The angle of rotation around the X-axis.
     * @param thetaDot The rate of change of the angle of rotation around the X-axis.
     * @return DirectionCosineMatrixAccel<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixAccel<in_frame, out_frame>
        X(const Angle& theta, const AngularRate& thetaDot, const AngularAccel& thetaDotDot)
    {
        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);

        const auto xx = 1.0 * one / pow<2>(s);
        const auto xy = 0.0 * one / pow<2>(s);
        const auto xz = 0.0 * one / pow<2>(s);
        const auto yx = 0.0 * one / pow<2>(s);
        const auto yy = (-thetaDotDot * sinTheta - pow<2>(thetaDot) * cosTheta) / pow<2>(s);
        const auto yz = (-thetaDotDot * cosTheta + pow<2>(thetaDot) * sinTheta) / pow<2>(s);
        const auto zx = 0.0 * one / pow<2>(s);
        const auto zy = (thetaDotDot * cosTheta - pow<2>(thetaDot) * sinTheta) / pow<2>(s);
        const auto zz = (-thetaDotDot * sinTheta - pow<2>(thetaDot) * cosTheta) / pow<2>(s);

        return DirectionCosineMatrixAccel<in_frame, out_frame>{ { xx, xy, xz, yx, yy, yz, zx, zy, zz } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis.
     *
     * @param theta The angle of rotation around the Y-axis.
     * @param thetaDot The rate of change of the angle of rotation around the Y-axis.
     * @return DirectionCosineMatrixAccel<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixAccel<in_frame, out_frame>
        Y(const Angle& theta, const AngularRate& thetaDot, const AngularAccel& thetaDotDot)
    {
        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);

        const auto xx = (-thetaDotDot * cosTheta + pow<2>(thetaDot) * sinTheta) / pow<2>(s);
        const auto xy = 0.0 * one / pow<2>(s);
        const auto xz = (thetaDotDot * sinTheta + pow<2>(thetaDot) * cosTheta) / pow<2>(s);
        const auto yx = 0.0 * one / pow<2>(s);
        const auto yy = 0.0 * one / pow<2>(s);
        const auto yz = 0.0 * one / pow<2>(s);
        const auto zx = (thetaDotDot * sinTheta + pow<2>(thetaDot) * cosTheta) / pow<2>(s);
        const auto zy = 0.0 * one / pow<2>(s);
        const auto zz = (-thetaDotDot * cosTheta + pow<2>(thetaDot) * sinTheta) / pow<2>(s);

        return DirectionCosineMatrixAccel<in_frame, out_frame>{ { xx, xy, xz, yx, yy, yz, zx, zy, zz } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis.
     *
     * @param theta The angle of rotation around the Z-axis.
     * @param thetaDot The rate of change of the angle of rotation around the Z-axis.
     * @return DirectionCosineMatrixAccel<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixAccel<in_frame, out_frame>
        Z(const Angle& theta, const AngularRate& thetaDot, const AngularAccel& thetaDotDot)
    {
        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);

        const auto xx = (-thetaDotDot * cosTheta + pow<2>(thetaDot) * sinTheta) / pow<2>(s);
        const auto xy = (thetaDotDot * sinTheta + pow<2>(thetaDot) * cosTheta) / pow<2>(s);
        const auto xz = 0.0 * one / pow<2>(s);
        const auto yx = (-thetaDotDot * sinTheta - pow<2>(thetaDot) * cosTheta) / pow<2>(s);
        const auto yy = (-thetaDotDot * cosTheta + pow<2>(thetaDot) * sinTheta) / pow<2>(s);
        const auto yz = 0.0 * one / pow<2>(s);
        const auto zx = 0.0 * one / pow<2>(s);
        const auto zy = 0.0 * one / pow<2>(s);
        const auto zz = 0.0 * one / pow<2>(s);

        return DirectionCosineMatrixAccel<in_frame, out_frame>{ { xx, xy, xz, yx, yy, yz, zx, zy, zz } };
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
     * @return DirectionCosineMatrixAccel<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixAccel<in_frame, out_frame>
        XZX(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularRate& alphaDot,
            const AngularRate& betaDot,
            const AngularRate& gammaDot,
            const AngularAccel& alphaDotDot,
            const AngularAccel& betaDotDot,
            const AngularAccel& gammaDotDot)
    {
        const auto X     = DirectionCosineMatrix<in_frame, out_frame>::X(alpha);
        const auto Xdot  = DirectionCosineMatrixRate<in_frame, out_frame>::X(alpha, alphaDot);
        const auto Xddot = DirectionCosineMatrixAccel<in_frame, out_frame>::X(alpha, alphaDot, alphaDotDot);

        const auto Z     = DirectionCosineMatrix<in_frame, out_frame>::Z(beta);
        const auto Zdot  = DirectionCosineMatrixRate<in_frame, out_frame>::Z(beta, betaDot);
        const auto Zddot = DirectionCosineMatrixAccel<in_frame, out_frame>::Z(beta, betaDot, betaDotDot);

        const auto X2     = DirectionCosineMatrix<in_frame, out_frame>::X(gamma);
        const auto X2dot  = DirectionCosineMatrixRate<in_frame, out_frame>::X(gamma, gammaDot);
        const auto X2ddot = DirectionCosineMatrixAccel<in_frame, out_frame>::X(gamma, gammaDot, gammaDotDot);

        return Xddot * Z * X2 + X * Zddot * X2 + X * Z * X2ddot + 2.0 * (Xdot * Zdot * X2 + Xdot * Z * X2dot + X * Zdot * X2dot);
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
     * @return DirectionCosineMatrixAccel<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixAccel<in_frame, out_frame>
        XYX(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularRate& alphaDot,
            const AngularRate& betaDot,
            const AngularRate& gammaDot,
            const AngularAccel& alphaDotDot,
            const AngularAccel& betaDotDot,
            const AngularAccel& gammaDotDot)
    {
        const auto X     = DirectionCosineMatrix<in_frame, out_frame>::X(alpha);
        const auto Xdot  = DirectionCosineMatrixRate<in_frame, out_frame>::X(alpha, alphaDot);
        const auto Xddot = DirectionCosineMatrixAccel<in_frame, out_frame>::X(alpha, alphaDot, alphaDotDot);

        const auto Y     = DirectionCosineMatrix<in_frame, out_frame>::Y(beta);
        const auto Ydot  = DirectionCosineMatrixRate<in_frame, out_frame>::Y(beta, betaDot);
        const auto Yddot = DirectionCosineMatrixAccel<in_frame, out_frame>::Y(beta, betaDot, betaDotDot);

        const auto X2     = DirectionCosineMatrix<in_frame, out_frame>::X(gamma);
        const auto X2dot  = DirectionCosineMatrixRate<in_frame, out_frame>::X(gamma, gammaDot);
        const auto X2ddot = DirectionCosineMatrixAccel<in_frame, out_frame>::X(gamma, gammaDot, gammaDotDot);

        return Xddot * Y * X2 + X * Yddot * X2 + X * Y * X2ddot + 2.0 * (Xdot * Ydot * X2 + Xdot * Y * X2dot + X * Ydot * X2dot);
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
     * @return DirectionCosineMatrixAccel<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixAccel<in_frame, out_frame>
        YZY(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularRate& alphaDot,
            const AngularRate& betaDot,
            const AngularRate& gammaDot,
            const AngularAccel& alphaDotDot,
            const AngularAccel& betaDotDot,
            const AngularAccel& gammaDotDot)
    {
        const auto Y     = DirectionCosineMatrix<in_frame, out_frame>::Y(alpha);
        const auto Ydot  = DirectionCosineMatrixRate<in_frame, out_frame>::Y(alpha, alphaDot);
        const auto Yddot = DirectionCosineMatrixAccel<in_frame, out_frame>::Y(alpha, alphaDot, alphaDotDot);

        const auto Z     = DirectionCosineMatrix<in_frame, out_frame>::Z(beta);
        const auto Zdot  = DirectionCosineMatrixRate<in_frame, out_frame>::Z(beta, betaDot);
        const auto Zddot = DirectionCosineMatrixAccel<in_frame, out_frame>::Z(beta, betaDot, betaDotDot);

        const auto Y2     = DirectionCosineMatrix<in_frame, out_frame>::Y(gamma);
        const auto Y2dot  = DirectionCosineMatrixRate<in_frame, out_frame>::Y(gamma, gammaDot);
        const auto Y2ddot = DirectionCosineMatrixAccel<in_frame, out_frame>::Y(gamma, gammaDot, gammaDotDot);

        return Yddot * Z * Y2 + Y * Zddot * Y2 + Y * Z * Y2ddot + 2.0 * (Ydot * Zdot * Y2 + Ydot * Z * Y2dot + Y * Zdot * Y2dot);
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
     * @return DirectionCosineMatrixAccel<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixAccel<in_frame, out_frame>
        ZXZ(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularRate& alphaDot,
            const AngularRate& betaDot,
            const AngularRate& gammaDot,
            const AngularAccel& alphaDotDot,
            const AngularAccel& betaDotDot,
            const AngularAccel& gammaDotDot)
    {
        const auto Z     = DirectionCosineMatrix<in_frame, out_frame>::Z(alpha);
        const auto Zdot  = DirectionCosineMatrixRate<in_frame, out_frame>::Z(alpha, alphaDot);
        const auto Zddot = DirectionCosineMatrixAccel<in_frame, out_frame>::Z(alpha, alphaDot, alphaDotDot);

        const auto X     = DirectionCosineMatrix<in_frame, out_frame>::X(beta);
        const auto Xdot  = DirectionCosineMatrixRate<in_frame, out_frame>::X(beta, betaDot);
        const auto Xddot = DirectionCosineMatrixAccel<in_frame, out_frame>::X(beta, betaDot, betaDotDot);

        const auto Z2     = DirectionCosineMatrix<in_frame, out_frame>::Z(gamma);
        const auto Z2dot  = DirectionCosineMatrixRate<in_frame, out_frame>::Z(gamma, gammaDot);
        const auto Z2ddot = DirectionCosineMatrixAccel<in_frame, out_frame>::Z(gamma, gammaDot, gammaDotDot);

        return Zddot * X * Z2 + Z * Xddot * Z2 + Z * X * Z2ddot + 2.0 * (Zdot * Xdot * Z2 + Zdot * X * Z2dot + Z * Xdot * Z2dot);
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
     * @return DirectionCosineMatrixAccel<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixAccel<in_frame, out_frame>
        ZYZ(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularRate& alphaDot,
            const AngularRate& betaDot,
            const AngularRate& gammaDot,
            const AngularAccel& alphaDotDot,
            const AngularAccel& betaDotDot,
            const AngularAccel& gammaDotDot)
    {
        const auto Z     = DirectionCosineMatrix<in_frame, out_frame>::Z(alpha);
        const auto Zdot  = DirectionCosineMatrixRate<in_frame, out_frame>::Z(alpha, alphaDot);
        const auto Zddot = DirectionCosineMatrixAccel<in_frame, out_frame>::Z(alpha, alphaDot, alphaDotDot);

        const auto Y     = DirectionCosineMatrix<in_frame, out_frame>::Y(beta);
        const auto Ydot  = DirectionCosineMatrixRate<in_frame, out_frame>::Y(beta, betaDot);
        const auto Yddot = DirectionCosineMatrixAccel<in_frame, out_frame>::Y(beta, betaDot, betaDotDot);

        const auto Z2     = DirectionCosineMatrix<in_frame, out_frame>::Z(gamma);
        const auto Z2dot  = DirectionCosineMatrixRate<in_frame, out_frame>::Z(gamma, gammaDot);
        const auto Z2ddot = DirectionCosineMatrixAccel<in_frame, out_frame>::Z(gamma, gammaDot, gammaDotDot);

        return Zddot * Y * Z2 + Z * Yddot * Z2 + Z * Y * Z2ddot + 2.0 * (Zdot * Ydot * Z2 + Zdot * Y * Z2dot + Z * Ydot * Z2dot);
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
     * @return DirectionCosineMatrixAccel<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixAccel<in_frame, out_frame>
        YXY(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularRate& alphaDot,
            const AngularRate& betaDot,
            const AngularRate& gammaDot,
            const AngularAccel& alphaDotDot,
            const AngularAccel& betaDotDot,
            const AngularAccel& gammaDotDot)
    {
        const auto Y     = DirectionCosineMatrix<in_frame, out_frame>::Y(alpha);
        const auto Ydot  = DirectionCosineMatrixRate<in_frame, out_frame>::Y(alpha, alphaDot);
        const auto Yddot = DirectionCosineMatrixAccel<in_frame, out_frame>::Y(alpha, alphaDot, alphaDotDot);

        const auto X     = DirectionCosineMatrix<in_frame, out_frame>::X(beta);
        const auto Xdot  = DirectionCosineMatrixRate<in_frame, out_frame>::X(beta, betaDot);
        const auto Xddot = DirectionCosineMatrixAccel<in_frame, out_frame>::X(beta, betaDot, betaDotDot);

        const auto Y2     = DirectionCosineMatrix<in_frame, out_frame>::Y(gamma);
        const auto Y2dot  = DirectionCosineMatrixRate<in_frame, out_frame>::Y(gamma, gammaDot);
        const auto Y2ddot = DirectionCosineMatrixAccel<in_frame, out_frame>::Y(gamma, gammaDot, gammaDotDot);

        return Yddot * X * Y2 + Y * Xddot * Y2 + Y * X * Y2ddot + 2.0 * (Ydot * Xdot * Y2 + Ydot * X * Y2dot + Y * Xdot * Y2dot);
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
     * @return DirectionCosineMatrixAccel<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixAccel<in_frame, out_frame>
        XYZ(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularRate& alphaDot,
            const AngularRate& betaDot,
            const AngularRate& gammaDot,
            const AngularAccel& alphaDotDot,
            const AngularAccel& betaDotDot,
            const AngularAccel& gammaDotDot)
    {
        const auto X     = DirectionCosineMatrixAccel<in_frame, out_frame>::X(alpha);
        const auto Xdot  = DirectionCosineMatrixRate<in_frame, out_frame>::X(alpha, alphaDot);
        const auto Xddot = DirectionCosineMatrixAccel<in_frame, out_frame>::X(alpha, alphaDot, alphaDotDot);

        const auto Y     = DirectionCosineMatrix<in_frame, out_frame>::Y(beta);
        const auto Ydot  = DirectionCosineMatrixRate<in_frame, out_frame>::Y(beta, betaDot);
        const auto Yddot = DirectionCosineMatrixAccel<in_frame, out_frame>::Y(beta, betaDot, betaDotDot);

        const auto Z     = DirectionCosineMatrix<in_frame, out_frame>::Z(gamma);
        const auto Zdot  = DirectionCosineMatrixRate<in_frame, out_frame>::Z(gamma, gammaDot);
        const auto Zddot = DirectionCosineMatrixAccel<in_frame, out_frame>::Z(gamma, gammaDot, gammaDotDot);

        return Xddot * Y * Z + X * Yddot * Z + X * Y * Zddot + 2.0 * (Xdot * Ydot * Z + Xdot * Y * Zdot + X * Ydot * Zdot);
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
     * @return DirectionCosineMatrixAccel<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixAccel<in_frame, out_frame>
        YZX(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularRate& alphaDot,
            const AngularRate& betaDot,
            const AngularRate& gammaDot,
            const AngularAccel& alphaDotDot,
            const AngularAccel& betaDotDot,
            const AngularAccel& gammaDotDot)
    {
        const auto Y     = DirectionCosineMatrix<in_frame, out_frame>::Y(alpha);
        const auto Ydot  = DirectionCosineMatrixRate<in_frame, out_frame>::Y(alpha, alphaDot);
        const auto Yddot = DirectionCosineMatrixAccel<in_frame, out_frame>::Y(alpha, alphaDot, alphaDotDot);

        const auto Z     = DirectionCosineMatrix<in_frame, out_frame>::Z(beta);
        const auto Zdot  = DirectionCosineMatrixRate<in_frame, out_frame>::Z(beta, betaDot);
        const auto Zddot = DirectionCosineMatrixAccel<in_frame, out_frame>::Z(beta, betaDot, betaDotDot);

        const auto X     = DirectionCosineMatrix<in_frame, out_frame>::X(gamma);
        const auto Xdot  = DirectionCosineMatrixRate<in_frame, out_frame>::X(gamma, gammaDot);
        const auto Xddot = DirectionCosineMatrixAccel<in_frame, out_frame>::X(gamma, gammaDot, gammaDotDot);

        return Yddot * Z * X + Y * Zddot * X + Y * Z * Xddot + 2.0 * (Ydot * Zdot * X + Ydot * Z * Xdot + Y * Zdot * Xdot);
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
     * @return DirectionCosineMatrixAccel<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixAccel<in_frame, out_frame>
        ZXY(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularRate& alphaDot,
            const AngularRate& betaDot,
            const AngularRate& gammaDot,
            const AngularAccel& alphaDotDot,
            const AngularAccel& betaDotDot,
            const AngularAccel& gammaDotDot)
    {
        const auto Z     = DirectionCosineMatrix<in_frame, out_frame>::Z(alpha);
        const auto Zdot  = DirectionCosineMatrixRate<in_frame, out_frame>::Z(alpha, alphaDot);
        const auto Zddot = DirectionCosineMatrixAccel<in_frame, out_frame>::Z(alpha, alphaDot, alphaDotDot);

        const auto X     = DirectionCosineMatrix<in_frame, out_frame>::X(beta);
        const auto Xdot  = DirectionCosineMatrixRate<in_frame, out_frame>::X(beta, betaDot);
        const auto Xddot = DirectionCosineMatrixAccel<in_frame, out_frame>::X(beta, betaDot, betaDotDot);

        const auto Y     = DirectionCosineMatrix<in_frame, out_frame>::Y(gamma);
        const auto Ydot  = DirectionCosineMatrixRate<in_frame, out_frame>::Y(gamma, gammaDot);
        const auto Yddot = DirectionCosineMatrixAccel<in_frame, out_frame>::Y(gamma, gammaDot, gammaDotDot);

        return Zddot * X * Y + Z * Xddot * Y + Z * X * Yddot + 2.0 * (Zdot * Xdot * Y + Zdot * X * Ydot + Z * Xdot * Ydot);
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
     * @return DirectionCosineMatrixAccel<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixAccel<in_frame, out_frame>
        XZY(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularRate& alphaDot,
            const AngularRate& betaDot,
            const AngularRate& gammaDot,
            const AngularAccel& alphaDotDot,
            const AngularAccel& betaDotDot,
            const AngularAccel& gammaDotDot)
    {
        return DirectionCosineMatrixAccel<in_frame, out_frame>::YZX(gamma, gammaDot, beta, betaDot, alpha, alphaDot, gammaDotDot, betaDotDot, alphaDotDot);
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
     * @return DirectionCosineMatrixAccel<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixAccel<in_frame, out_frame>
        ZYX(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularRate& alphaDot,
            const AngularRate& betaDot,
            const AngularRate& gammaDot,
            const AngularAccel& alphaDotDot,
            const AngularAccel& betaDotDot,
            const AngularAccel& gammaDotDot)
    {
        return DirectionCosineMatrixAccel<in_frame, out_frame>::XYZ(gamma, gammaDot, beta, betaDot, alpha, alphaDot, gammaDotDot, betaDotDot, alphaDotDot);
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
     * @return DirectionCosineMatrixAccel<out_frame> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixAccel<in_frame, out_frame>
        YXZ(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularRate& alphaDot,
            const AngularRate& betaDot,
            const AngularRate& gammaDot,
            const AngularAccel& alphaDotDot,
            const AngularAccel& betaDotDot,
            const AngularAccel& gammaDotDot)
    {
        return DirectionCosineMatrixAccel<in_frame, out_frame>::ZXY(gamma, gammaDot, beta, betaDot, alpha, alphaDot, gammaDotDot, betaDotDot, alphaDotDot);
    }

    /**
     * @brief Creates an identity direction cosine matrix (no rotation).
     *
     * @return DirectionCosineMatrixAccel<out_frame> The identity direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixAccel<in_frame, out_frame> identity() {
        return DirectionCosineMatrixAccel<in_frame, out_frame>{ Matrix3x3<quantity<one / pow<2>(s)>>::identity() }
    };
}

/**
 * @brief Transposes the direction cosine matrix, effectively inverting the transformation.
 *
 * @return DirectionCosineMatrixAccel<out_frame, in_frame> The transposed direction cosine matrix.
 */
inline constexpr DirectionCosineMatrixAccel<out_frame, in_frame>
    transpose() const
{
    return DirectionCosineMatrixAccel<out_frame, in_frame>{ { _matrix[0][0], _matrix[1][0], _matrix[2][0] },
                                                            { _matrix[0][1], _matrix[1][1], _matrix[2][1] },
                                                            { _matrix[0][2], _matrix[1][2], _matrix[2][2] } };
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
 * @return DirectionCosineMatrixAccel<out_frame> The resulting direction cosine matrix.
 */
template <RotationSequence sequence>
static inline constexpr DirectionCosineMatrixAccel<in_frame, out_frame>
    from_euler_angles(const Angle& alpha, const Angle& beta, const Angle& gamma, const AngularRate& alphaDot, const AngularRate& betaDot, const AngularRate& gammaDot)
{
    if constexpr (sequence == RotationSequence::ZXZ) {
        return DirectionCosineMatrixAccel<in_frame, out_frame>::ZXZ(alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot);
    }
    else if constexpr (sequence == RotationSequence::XYX) {
        return DirectionCosineMatrixAccel<in_frame, out_frame>::XYX(alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot);
    }
    else if constexpr (sequence == RotationSequence::YZY) {
        return DirectionCosineMatrixAccel<in_frame, out_frame>::YZY(alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot);
    }
    else if constexpr (sequence == RotationSequence::ZYZ) {
        return DirectionCosineMatrixAccel<in_frame, out_frame>::ZYZ(alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot);
    }
    else if constexpr (sequence == RotationSequence::XZX) {
        return DirectionCosineMatrixAccel<in_frame, out_frame>::XZX(alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot);
    }
    else if constexpr (sequence == RotationSequence::YXY) {
        return DirectionCosineMatrixAccel<in_frame, out_frame>::YXY(alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot);
    }
    else if constexpr (sequence == RotationSequence::XYZ) {
        return DirectionCosineMatrixAccel<in_frame, out_frame>::XYZ(alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot);
    }
    else if constexpr (sequence == RotationSequence::YZX) {
        return DirectionCosineMatrixAccel<in_frame, out_frame>::YZX(alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot);
    }
    else if constexpr (sequence == RotationSequence::ZXY) {
        return DirectionCosineMatrixAccel<in_frame, out_frame>::ZXY(alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot);
    }
    else if constexpr (sequence == RotationSequence::XZY) {
        return DirectionCosineMatrixAccel<in_frame, out_frame>::XZY(alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot);
    }
    else if constexpr (sequence == RotationSequence::ZYX) {
        return DirectionCosineMatrixAccel<in_frame, out_frame>::ZYX(alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot);
    }
    else if constexpr (sequence == RotationSequence::YXZ) {
        return DirectionCosineMatrixAccel<in_frame, out_frame>::YXZ(alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot);
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
inline constexpr CartesianVector<decltype(Value_T{} / s), out_frame> operator*(const CartesianVector<Value_T, in_frame>& vec) const
{
    return { row(0).dot(vec), row(1).dot(vec), row(2).dot(vec) };
}

/**
 * @brief Compose this direction cosine matrix rate with a DCM, resulting in a new DCM rate.
 *
 * @tparam in_frame_u The input frame of the other DCM.
 * @tparam out_frame_u The output frame of the other DCM.
 * @param dcm The other DCM to compose with this one.
 * @return DirectionCosineMatrixAccel<in_frame, out_frame> The resulting composed DCM rate.
 */
inline constexpr DirectionCosineMatrixAccel<in_frame, out_frame> operator*(DirectionCosineMatrixAccel<in_frame, out_frame> dcm) const
{
    return { static_cast<Matrix3x3<quantity<one / pow<2>(s)>>>(*this) * static_cast<Matrix3x3<Unitless>>(dcm) };
}

/**
 * @brief Compose two direction cosine matrices (matrix multiplication).
 *
 * Produces DCM<in_frame, new_out_frame> = this * rhs, where this is
 * DCM<in_frame, out_frame> and rhs is DCM<out_frame, new_out_frame>.
 *
 * @tparam new_out_frame The output frame of the right-hand-side DCM.
 * @param accel The right-hand-side DCM to compose with.
 * @return DirectionCosineMatrixAccelAccel<in_frame, new_out_frame> The composed DCM.
 */
template <IsFrame auto new_out_frame>
inline constexpr DirectionCosineMatrixAccelAccel<in_frame, new_out_frame>
    operator*(const DirectionCosineMatrixAccel<out_frame, new_out_frame>& accel) const;

/**
 * @brief Add two direction cosine matrices element-wise.
 *
 * @param other The other DCM to add to this DCM.
 * @return DirectionCosineMatrixAccel<in_frame, out_frame> The resulting DCM after addition.
 */
inline constexpr DirectionCosineMatrixAccel operator+(const DirectionCosineMatrixAccel& other) const
{
    return { static_cast<Matrix3x3<quantity<one / pow<2>(s)>>>(*this) + static_cast<Matrix3x3<quantity<one / pow<2>(s)>>>(other) };
}

/**
 * @brief Negate the direction cosine matrix element-wise.
 *
 * @return DirectionCosineMatrixAccel<in_frame, out_frame> The resulting DCM after negation.
 */
inline constexpr DirectionCosineMatrixAccel operator-() const
{
    return { -static_cast<Matrix3x3<quantity<one / pow<2>(s)>>>(*this) };
}

/**
 * @brief Subtract another direction cosine matrix from this one element-wise.
 *
 * @param other The other DCM to subtract from this DCM.
 * @return DirectionCosineMatrixAccel<in_frame, out_frame> The resulting DCM after subtraction.
 */
inline constexpr DirectionCosineMatrixAccel operator-(const DirectionCosineMatrixAccel& other) const
{
    return { static_cast<Matrix3x3<quantity<one / pow<2>(s)>>>(*this) - static_cast<Matrix3x3<quantity<one / pow<2>(s)>>>(other) };
}

/**
 * @brief Multiply this direction cosine matrix by another DCM element-wise.
 *
 * Note: This is not the same as matrix multiplication (composition of rotations). This is an element-wise operation.
 *
 * @param other The other DCM to multiply with this DCM.
 * @return DirectionCosineMatrixAccel<in_frame, out_frame> The resulting DCM after element-wise multiplication.
 */
inline constexpr DirectionCosineMatrixAccel operator*(const DirectionCosineMatrixAccel& other) const
{
    return { static_cast<Matrix3x3<quantity<one / pow<2>(s)>>>(*this) * static_cast<Matrix3x3<quantity<one / pow<2>(s)>>>(other) };
}
};


/**
 * @brief Alias for DirectionCosineMatrixAccel with a specific output frame type.
 *
 * This alias simplifies the usage of DirectionCosineMatrixAccel by allowing the user to specify the output frame type.
 *
 * @tparam out_frame The frame type to which the DCM applies.
 */
template <IsFrame auto in_frame, IsFrame auto out_frame>
using DcmAccel = DirectionCosineMatrixAccel<in_frame, out_frame>;

// Defined template function and then delete it so we can enforce lookup restrictions
template <IsFrame auto frame, IsFrame auto frame_u>
inline constexpr DcmAccel<frame, frame_u> get_dcm_accel(const Date& date) = delete;


/**
 * @brief Compose two direction cosine matrices (matrix multiplication).
 *
 * Produces DCM<in_frame, new_out_frame> = this * rhs, where this is
 * DCM<in_frame, out_frame> and rhs is DCM<out_frame, new_out_frame>.
 *
 * @tparam new_out_frame The output frame of the right-hand-side DCM.
 * @param other The right-hand-side DCM to compose with.
 * @return DirectionCosineMatrixAccel<in_frame, new_out_frame> The composed DCM.
 */
template <IsFrame auto new_out_frame>
inline constexpr DirectionCosineMatrixAccel<in_frame, new_out_frame>
    operator*(const DirectionCosineMatrixAccel<out_frame, new_out_frame>& other) const
{
    return DirectionCosineMatrixAccel<in_frame, new_out_frame>{
        { _matrix[0][0] * other[0, 0] + _matrix[0][1] * other[1, 0] + _matrix[0][2] * other[2, 0],
          _matrix[0][0] * other[0, 1] + _matrix[0][1] * other[1, 1] + _matrix[0][2] * other[2, 1],
          _matrix[0][0] * other[0, 2] + _matrix[0][1] * other[1, 2] + _matrix[0][2] * other[2, 2] },
        { _matrix[1][0] * other[0, 0] + _matrix[1][1] * other[1, 0] + _matrix[1][2] * other[2, 0],
          _matrix[1][0] * other[0, 1] + _matrix[1][1] * other[1, 1] + _matrix[1][2] * other[2, 1],
          _matrix[1][0] * other[0, 2] + _matrix[1][1] * other[1, 2] + _matrix[1][2] * other[2, 2] },
        { _matrix[2][0] * other[0, 0] + _matrix[2][1] * other[1, 0] + _matrix[2][2] * other[2, 0],
          _matrix[2][0] * other[0, 1] + _matrix[2][1] * other[1, 1] + _matrix[2][2] * other[2, 1],
          _matrix[2][0] * other[0, 2] + _matrix[2][1] * other[1, 2] + _matrix[2][2] * other[2, 2] }
    };
}

} // namespace astro
} // namespace astrea