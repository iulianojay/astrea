/**
 * @file DirectionCosineMatrixRate.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the DirectionCosineMatrixRate class in the astro namespace
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

#include <units/units.hpp>
#include <utilities/string_util.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/framework/DcmInterface.hpp>
#include <astro/frames/framework/DirectionCosineMatrix.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
class DirectionCosineMatrixAccel;

/**
 * @brief Class representing a direction cosine matrix (DCM) for transforming vectors between state/frames.
 *
 * This class provides methods to create DCMs for various rotations and to apply them to vectors.
 *
 * @tparam _out_frame_ The frame type to which the DCM applies.
 */
template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
struct DirectionCosineMatrixRate : public DcmInterface<Frequency, _in_frame_, _out_frame_> {

    /**
     * @brief Constructor for DirectionCosineMatrixRate from an array of CartesianVectors.
     *
     * @param matrix An array containing the three rows of the DCM rate, each represented as a CartesianVector.
     */
    inline constexpr DirectionCosineMatrixRate(const std::array<Frequency, 9>& matrix) :
        DcmInterface<Frequency, _in_frame_, _out_frame_>{ matrix }
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
        DcmInterface<Frequency, _in_frame_, _out_frame_>{ row1, row2, row3 }
    {
    }

    /**
     * @brief Constructor for DirectionCosineMatrixRate from a DcmInterface of Frequency.
     *
     * @param matrix A DcmInterface containing the elements of the DCM rate.
     */
    inline constexpr DirectionCosineMatrixRate(const DcmInterface<Frequency, _in_frame_, _out_frame_>& matrix) :
        DcmInterface<Frequency, _in_frame_, _out_frame_>{ matrix }
    {
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis.
     *
     * @param theta The angle of rotation around the X-axis.
     * @param thetaDot The rate of change of the angle of rotation around the X-axis.
     * @return DirectionCosineMatrixRate<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<_in_frame_, _out_frame_> X(const Angle& theta, const AngularVelocity& thetaDot)
    {
        using namespace mp_units;
        using mp_units::si::unit_symbols::s;

        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);
        // Disolve angular unit
        const auto thetaDotUnitless = thetaDot / thetaDot.unit;
        return { { 0.0 * one / s, 0.0 * one / s, 0.0 * one / s },
                 { 0.0 * one / s, -thetaDotUnitless * sinTheta, -thetaDotUnitless * cosTheta },
                 { 0.0 * one / s, thetaDotUnitless * cosTheta, thetaDotUnitless * sinTheta } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis.
     *
     * @param theta The angle of rotation around the Y-axis.
     * @param thetaDot The rate of change of the angle of rotation around the Y-axis.
     * @return DirectionCosineMatrixRate<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<_in_frame_, _out_frame_> Y(const Angle& theta, const AngularVelocity& thetaDot)
    {
        using namespace mp_units;
        using mp_units::si::unit_symbols::s;

        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);
        // Disolve angular unit
        const auto thetaDotUnitless = thetaDot / thetaDot.unit;
        return { { -thetaDotUnitless * sinTheta, 0.0 * one / s, thetaDotUnitless * cosTheta },
                 { 0.0 * one / s, 0.0 * one / s, 0.0 * one / s },
                 { -thetaDotUnitless * cosTheta, 0.0 * one / s, -thetaDotUnitless * sinTheta } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis.
     *
     * @param theta The angle of rotation around the Z-axis.
     * @param thetaDot The rate of change of the angle of rotation around the Z-axis.
     * @return DirectionCosineMatrixRate<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<_in_frame_, _out_frame_> Z(const Angle& theta, const AngularVelocity& thetaDot)
    {
        using namespace mp_units;
        using mp_units::si::unit_symbols::s;

        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);
        // Disolve angular unit
        const auto thetaDotUnitless = thetaDot / thetaDot.unit;
        return { { -thetaDotUnitless * sinTheta, -thetaDotUnitless * cosTheta, 0.0 * one / s },
                 { thetaDotUnitless * cosTheta, -thetaDotUnitless * sinTheta, 0.0 * one / s },
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
     * @return DirectionCosineMatrixRate<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<_in_frame_, _out_frame_>
        XZX(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot)
    {
        const auto X     = DirectionCosineMatrix<_in_frame_, _out_frame_>::X(alpha);
        const auto Xdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::X(alpha, alphaDot);
        const auto Z     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Z(beta);
        const auto Zdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Z(beta, betaDot);
        const auto X2    = DirectionCosineMatrix<_in_frame_, _out_frame_>::X(gamma);
        const auto X2dot = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::X(gamma, gammaDot);
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
     * @return DirectionCosineMatrixRate<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<_in_frame_, _out_frame_>
        XYX(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot)
    {
        const auto X     = DirectionCosineMatrix<_in_frame_, _out_frame_>::X(alpha);
        const auto Xdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::X(alpha, alphaDot);
        const auto Y     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Y(beta);
        const auto Ydot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Y(beta, betaDot);
        const auto X2    = DirectionCosineMatrix<_in_frame_, _out_frame_>::X(gamma);
        const auto X2dot = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::X(gamma, gammaDot);
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
     * @return DirectionCosineMatrixRate<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<_in_frame_, _out_frame_>
        YZY(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot)
    {
        const auto Y     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Y(alpha);
        const auto Ydot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Y(alpha, alphaDot);
        const auto Z     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Z(beta);
        const auto Zdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Z(beta, betaDot);
        const auto Y2    = DirectionCosineMatrix<_in_frame_, _out_frame_>::Y(gamma);
        const auto Y2dot = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Y(gamma, gammaDot);
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
     * @return DirectionCosineMatrixRate<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<_in_frame_, _out_frame_>
        ZXZ(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot)
    {
        const auto Z     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Z(alpha);
        const auto Zdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Z(alpha, alphaDot);
        const auto X     = DirectionCosineMatrix<_in_frame_, _out_frame_>::X(beta);
        const auto Xdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::X(beta, betaDot);
        const auto Z2    = DirectionCosineMatrix<_in_frame_, _out_frame_>::Z(gamma);
        const auto Z2dot = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Z(gamma, gammaDot);
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
     * @return DirectionCosineMatrixRate<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<_in_frame_, _out_frame_>
        ZYZ(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot)
    {
        const auto Z     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Z(alpha);
        const auto Zdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Z(alpha, alphaDot);
        const auto Y     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Y(beta);
        const auto Ydot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Y(beta, betaDot);
        const auto Z2    = DirectionCosineMatrix<_in_frame_, _out_frame_>::Z(gamma);
        const auto Z2dot = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Z(gamma, gammaDot);
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
     * @return DirectionCosineMatrixRate<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<_in_frame_, _out_frame_>
        YXY(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot)
    {
        const auto Y     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Y(alpha);
        const auto Ydot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Y(alpha, alphaDot);
        const auto X     = DirectionCosineMatrix<_in_frame_, _out_frame_>::X(beta);
        const auto Xdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::X(beta, betaDot);
        const auto Y2    = DirectionCosineMatrix<_in_frame_, _out_frame_>::Y(gamma);
        const auto Y2dot = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Y(gamma, gammaDot);
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
     * @return DirectionCosineMatrixRate<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<_in_frame_, _out_frame_>
        XYZ(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot)
    {
        const auto X    = DirectionCosineMatrix<_in_frame_, _out_frame_>::X(alpha);
        const auto Xdot = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::X(alpha, alphaDot);
        const auto Y    = DirectionCosineMatrix<_in_frame_, _out_frame_>::Y(beta);
        const auto Ydot = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Y(beta, betaDot);
        const auto Z    = DirectionCosineMatrix<_in_frame_, _out_frame_>::Z(gamma);
        const auto Zdot = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Z(gamma, gammaDot);
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
     * @return DirectionCosineMatrixRate<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<_in_frame_, _out_frame_>
        YZX(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot)
    {
        const auto Y    = DirectionCosineMatrix<_in_frame_, _out_frame_>::Y(alpha);
        const auto Ydot = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Y(alpha, alphaDot);
        const auto Z    = DirectionCosineMatrix<_in_frame_, _out_frame_>::Z(beta);
        const auto Zdot = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Z(beta, betaDot);
        const auto X    = DirectionCosineMatrix<_in_frame_, _out_frame_>::X(gamma);
        const auto Xdot = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::X(gamma, gammaDot);
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
     * @return DirectionCosineMatrixRate<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<_in_frame_, _out_frame_>
        ZXY(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot)
    {
        const auto Z    = DirectionCosineMatrix<_in_frame_, _out_frame_>::Z(alpha);
        const auto Zdot = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Z(alpha, alphaDot);
        const auto X    = DirectionCosineMatrix<_in_frame_, _out_frame_>::X(beta);
        const auto Xdot = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::X(beta, betaDot);
        const auto Y    = DirectionCosineMatrix<_in_frame_, _out_frame_>::Y(gamma);
        const auto Ydot = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Y(gamma, gammaDot);
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
     * @return DirectionCosineMatrixRate<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<_in_frame_, _out_frame_>
        XZY(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot)
    {
        return DirectionCosineMatrixRate<_in_frame_, _out_frame_>::YZX(gamma, gammaDot, beta, betaDot, alpha, alphaDot);
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
     * @return DirectionCosineMatrixRate<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<_in_frame_, _out_frame_>
        ZYX(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot)
    {
        return DirectionCosineMatrixRate<_in_frame_, _out_frame_>::XYZ(gamma, gammaDot, beta, betaDot, alpha, alphaDot);
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
     * @return DirectionCosineMatrixRate<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrixRate<_in_frame_, _out_frame_>
        YXZ(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot)
    {
        return DirectionCosineMatrixRate<_in_frame_, _out_frame_>::ZXY(gamma, gammaDot, beta, betaDot, alpha, alphaDot);
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
     * @return DirectionCosineMatrixRate<_out_frame_> The resulting direction cosine matrix.
     */
    template <RotationSequence sequence>
    static inline constexpr DirectionCosineMatrixRate<_in_frame_, _out_frame_>
        from_euler_angles(const Angle& alpha, const Angle& beta, const Angle& gamma, const AngularVelocity& alphaDot, const AngularVelocity& betaDot, const AngularVelocity& gammaDot)
    {
        if constexpr (sequence == RotationSequence::ZXZ) {
            return DirectionCosineMatrixRate<_in_frame_, _out_frame_>::ZXZ(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::XYX) {
            return DirectionCosineMatrixRate<_in_frame_, _out_frame_>::XYX(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::YZY) {
            return DirectionCosineMatrixRate<_in_frame_, _out_frame_>::YZY(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::ZYZ) {
            return DirectionCosineMatrixRate<_in_frame_, _out_frame_>::ZYZ(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::XZX) {
            return DirectionCosineMatrixRate<_in_frame_, _out_frame_>::XZX(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::YXY) {
            return DirectionCosineMatrixRate<_in_frame_, _out_frame_>::YXY(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::XYZ) {
            return DirectionCosineMatrixRate<_in_frame_, _out_frame_>::XYZ(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::YZX) {
            return DirectionCosineMatrixRate<_in_frame_, _out_frame_>::YZX(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::ZXY) {
            return DirectionCosineMatrixRate<_in_frame_, _out_frame_>::ZXY(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::XZY) {
            return DirectionCosineMatrixRate<_in_frame_, _out_frame_>::XZY(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::ZYX) {
            return DirectionCosineMatrixRate<_in_frame_, _out_frame_>::ZYX(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
        else if constexpr (sequence == RotationSequence::YXZ) {
            return DirectionCosineMatrixRate<_in_frame_, _out_frame_>::YXZ(alpha, alphaDot, beta, betaDot, gamma, gammaDot);
        }
    }

    inline constexpr DirectionCosineMatrixRate<_out_frame_, _in_frame_> transpose() const
    {
        return { static_cast<DcmInterface<Frequency, _in_frame_, _out_frame_>>(*this).transpose() };
    }

    static inline constexpr DirectionCosineMatrixRate identity()
    {
        return { DcmInterface<Frequency, _in_frame_, _out_frame_>::identity() };
    }

    static inline constexpr DirectionCosineMatrixRate zero()
    {
        return { DcmInterface<Frequency, _in_frame_, _out_frame_>::zero() };
    }
};

/**
 * @brief Alias for DirectionCosineMatrixRate with a specific output frame type.
 *
 * This alias simplifies the usage of DirectionCosineMatrixRate by allowing the user to specify the output frame type.
 *
 * @tparam _out_frame_ The frame type to which the DCM applies.
 */
template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
using DcmRate = DirectionCosineMatrixRate<_in_frame_, _out_frame_>;

// Defined template function and then delete it so we can enforce lookup restrictions
template <IsFrame auto frame, IsFrame auto frame_u>
inline constexpr DcmRate<frame, frame_u> get_dcm_rate(const Date& date) = delete;

} // namespace astro
} // namespace astrea