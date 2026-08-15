

# File DirectionCosineMatrixAccel.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**framework**](dir_aa3952657448f7008c08b8ed45c303ac.md) **>** [**DirectionCosineMatrixAccel.hpp**](DirectionCosineMatrixAccel_8hpp.md)

[Go to the documentation of this file](DirectionCosineMatrixAccel_8hpp.md)


```C++

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
#include <astro/frames/framework/DirectionCosineMatrixRate.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
struct DirectionCosineMatrixAccel : public DcmInterface<Chirp, _in_frame_, _out_frame_> {

    inline constexpr DirectionCosineMatrixAccel(const std::array<Chirp, 9>& matrix) :
        DcmInterface<Chirp, _in_frame_, _out_frame_>{ matrix }
    {
    }

    inline constexpr DirectionCosineMatrixAccel(const std::array<Chirp, 3>& row1, const std::array<Chirp, 3>& row2, const std::array<Chirp, 3>& row3) :
        DcmInterface<Chirp, _in_frame_, _out_frame_>{ row1, row2, row3 }
    {
    }

    inline constexpr DirectionCosineMatrixAccel(const DcmInterface<Chirp, _in_frame_, _out_frame_>& matrix) :
        DcmInterface<Chirp, _in_frame_, _out_frame_>{ matrix }
    {
    }

    static inline constexpr DirectionCosineMatrixAccel<_in_frame_, _out_frame_>
        X(const Angle& theta, const AngularVelocity& thetaDot, const AngularAcceleration& thetaDotDot)
    {
        using namespace mp_units;
        using mp_units::si::unit_symbols::s;

        const auto [sinTheta, cosTheta] = math::sin_cos_pack(theta);

        // Disolve angular unit
        const auto thetaDotUnitless    = thetaDot / thetaDot.unit;
        const auto thetaDotDotUnitless = thetaDotDot / thetaDotDot.unit;
        const auto thetaDotSquared     = pow<2>(thetaDotUnitless);

        const auto xx = 0.0 * one / pow<2>(s);
        const auto xy = 0.0 * one / pow<2>(s);
        const auto xz = 0.0 * one / pow<2>(s);
        const auto yx = 0.0 * one / pow<2>(s);
        const auto yy = (-thetaDotDotUnitless * sinTheta - thetaDotSquared * cosTheta);
        const auto yz = (-thetaDotDotUnitless * cosTheta + thetaDotSquared * sinTheta);
        const auto zx = 0.0 * one / pow<2>(s);
        const auto zy = (thetaDotDotUnitless * cosTheta - thetaDotSquared * sinTheta);
        const auto zz = (-thetaDotDotUnitless * sinTheta - thetaDotSquared * cosTheta);

        return { { xx, xy, xz, yx, yy, yz, zx, zy, zz } };
    }

    static inline constexpr DirectionCosineMatrixAccel<_in_frame_, _out_frame_>
        Y(const Angle& theta, const AngularVelocity& thetaDot, const AngularAcceleration& thetaDotDot)
    {
        using namespace mp_units;
        using mp_units::si::unit_symbols::s;

        const auto [sinTheta, cosTheta] = math::sin_cos_pack(theta);

        // Disolve angular unit
        const auto thetaDotUnitless    = thetaDot / thetaDot.unit;
        const auto thetaDotDotUnitless = thetaDotDot / thetaDotDot.unit;
        const auto thetaDotSquared     = pow<2>(thetaDotUnitless);

        const auto xx = (-thetaDotDotUnitless * cosTheta + thetaDotSquared * sinTheta);
        const auto xy = 0.0 * one / pow<2>(s);
        const auto xz = (thetaDotDotUnitless * sinTheta + thetaDotSquared * cosTheta);
        const auto yx = 0.0 * one / pow<2>(s);
        const auto yy = 0.0 * one / pow<2>(s);
        const auto yz = 0.0 * one / pow<2>(s);
        const auto zx = (thetaDotDotUnitless * sinTheta + thetaDotSquared * cosTheta);
        const auto zy = 0.0 * one / pow<2>(s);
        const auto zz = (-thetaDotDotUnitless * cosTheta + thetaDotSquared * sinTheta);

        return { { xx, xy, xz, yx, yy, yz, zx, zy, zz } };
    }

    static inline constexpr DirectionCosineMatrixAccel<_in_frame_, _out_frame_>
        Z(const Angle& theta, const AngularVelocity& thetaDot, const AngularAcceleration& thetaDotDot)
    {
        using namespace mp_units;
        using mp_units::si::unit_symbols::s;

        const auto [sinTheta, cosTheta] = math::sin_cos_pack(theta);

        // Disolve angular unit
        const auto thetaDotUnitless    = thetaDot / thetaDot.unit;
        const auto thetaDotDotUnitless = thetaDotDot / thetaDotDot.unit;
        const auto thetaDotSquared     = pow<2>(thetaDotUnitless);

        const auto xx = (-thetaDotDotUnitless * cosTheta + thetaDotSquared * sinTheta);
        const auto xy = (thetaDotDotUnitless * sinTheta + thetaDotSquared * cosTheta);
        const auto xz = 0.0 * one / pow<2>(s);
        const auto yx = (-thetaDotDotUnitless * sinTheta - thetaDotSquared * cosTheta);
        const auto yy = (-thetaDotDotUnitless * cosTheta + thetaDotSquared * sinTheta);
        const auto yz = 0.0 * one / pow<2>(s);
        const auto zx = 0.0 * one / pow<2>(s);
        const auto zy = 0.0 * one / pow<2>(s);
        const auto zz = 0.0 * one / pow<2>(s);

        return { { xx, xy, xz, yx, yy, yz, zx, zy, zz } };
    }

    static inline constexpr DirectionCosineMatrixAccel<_in_frame_, _out_frame_>
        XZX(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot,
            const AngularAcceleration& alphaDotDot,
            const AngularAcceleration& betaDotDot,
            const AngularAcceleration& gammaDotDot)
    {
        const auto X     = DirectionCosineMatrix<_in_frame_, _out_frame_>::X(alpha);
        const auto Xdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::X(alpha, alphaDot);
        const auto Xddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::X(alpha, alphaDot, alphaDotDot);

        const auto Z     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Z(beta);
        const auto Zdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Z(beta, betaDot);
        const auto Zddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::Z(beta, betaDot, betaDotDot);

        const auto X2     = DirectionCosineMatrix<_in_frame_, _out_frame_>::X(gamma);
        const auto X2dot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::X(gamma, gammaDot);
        const auto X2ddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::X(gamma, gammaDot, gammaDotDot);

        return Xddot * Z * X2 + X * Zddot * X2 + X * Z * X2ddot + 2.0 * (Xdot * Zdot * X2 + Xdot * Z * X2dot + X * Zdot * X2dot);
    }

    static inline constexpr DirectionCosineMatrixAccel<_in_frame_, _out_frame_>
        XYX(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot,
            const AngularAcceleration& alphaDotDot,
            const AngularAcceleration& betaDotDot,
            const AngularAcceleration& gammaDotDot)
    {
        const auto X     = DirectionCosineMatrix<_in_frame_, _out_frame_>::X(alpha);
        const auto Xdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::X(alpha, alphaDot);
        const auto Xddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::X(alpha, alphaDot, alphaDotDot);

        const auto Y     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Y(beta);
        const auto Ydot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Y(beta, betaDot);
        const auto Yddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::Y(beta, betaDot, betaDotDot);

        const auto X2     = DirectionCosineMatrix<_in_frame_, _out_frame_>::X(gamma);
        const auto X2dot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::X(gamma, gammaDot);
        const auto X2ddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::X(gamma, gammaDot, gammaDotDot);

        return Xddot * Y * X2 + X * Yddot * X2 + X * Y * X2ddot + 2.0 * (Xdot * Ydot * X2 + Xdot * Y * X2dot + X * Ydot * X2dot);
    }

    static inline constexpr DirectionCosineMatrixAccel<_in_frame_, _out_frame_>
        YZY(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot,
            const AngularAcceleration& alphaDotDot,
            const AngularAcceleration& betaDotDot,
            const AngularAcceleration& gammaDotDot)
    {
        const auto Y     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Y(alpha);
        const auto Ydot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Y(alpha, alphaDot);
        const auto Yddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::Y(alpha, alphaDot, alphaDotDot);

        const auto Z     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Z(beta);
        const auto Zdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Z(beta, betaDot);
        const auto Zddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::Z(beta, betaDot, betaDotDot);

        const auto Y2     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Y(gamma);
        const auto Y2dot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Y(gamma, gammaDot);
        const auto Y2ddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::Y(gamma, gammaDot, gammaDotDot);

        return Yddot * Z * Y2 + Y * Zddot * Y2 + Y * Z * Y2ddot + 2.0 * (Ydot * Zdot * Y2 + Ydot * Z * Y2dot + Y * Zdot * Y2dot);
    }

    static inline constexpr DirectionCosineMatrixAccel<_in_frame_, _out_frame_>
        ZXZ(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot,
            const AngularAcceleration& alphaDotDot,
            const AngularAcceleration& betaDotDot,
            const AngularAcceleration& gammaDotDot)
    {
        const auto Z     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Z(alpha);
        const auto Zdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Z(alpha, alphaDot);
        const auto Zddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::Z(alpha, alphaDot, alphaDotDot);

        const auto X     = DirectionCosineMatrix<_in_frame_, _out_frame_>::X(beta);
        const auto Xdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::X(beta, betaDot);
        const auto Xddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::X(beta, betaDot, betaDotDot);

        const auto Z2     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Z(gamma);
        const auto Z2dot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Z(gamma, gammaDot);
        const auto Z2ddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::Z(gamma, gammaDot, gammaDotDot);

        return Zddot * X * Z2 + Z * Xddot * Z2 + Z * X * Z2ddot + 2.0 * (Zdot * Xdot * Z2 + Zdot * X * Z2dot + Z * Xdot * Z2dot);
    }

    static inline constexpr DirectionCosineMatrixAccel<_in_frame_, _out_frame_>
        ZYZ(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot,
            const AngularAcceleration& alphaDotDot,
            const AngularAcceleration& betaDotDot,
            const AngularAcceleration& gammaDotDot)
    {
        const auto Z     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Z(alpha);
        const auto Zdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Z(alpha, alphaDot);
        const auto Zddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::Z(alpha, alphaDot, alphaDotDot);

        const auto Y     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Y(beta);
        const auto Ydot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Y(beta, betaDot);
        const auto Yddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::Y(beta, betaDot, betaDotDot);

        const auto Z2     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Z(gamma);
        const auto Z2dot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Z(gamma, gammaDot);
        const auto Z2ddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::Z(gamma, gammaDot, gammaDotDot);

        return Zddot * Y * Z2 + Z * Yddot * Z2 + Z * Y * Z2ddot + 2.0 * (Zdot * Ydot * Z2 + Zdot * Y * Z2dot + Z * Ydot * Z2dot);
    }

    static inline constexpr DirectionCosineMatrixAccel<_in_frame_, _out_frame_>
        YXY(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot,
            const AngularAcceleration& alphaDotDot,
            const AngularAcceleration& betaDotDot,
            const AngularAcceleration& gammaDotDot)
    {
        const auto Y     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Y(alpha);
        const auto Ydot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Y(alpha, alphaDot);
        const auto Yddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::Y(alpha, alphaDot, alphaDotDot);

        const auto X     = DirectionCosineMatrix<_in_frame_, _out_frame_>::X(beta);
        const auto Xdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::X(beta, betaDot);
        const auto Xddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::X(beta, betaDot, betaDotDot);

        const auto Y2     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Y(gamma);
        const auto Y2dot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Y(gamma, gammaDot);
        const auto Y2ddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::Y(gamma, gammaDot, gammaDotDot);

        return Yddot * X * Y2 + Y * Xddot * Y2 + Y * X * Y2ddot + 2.0 * (Ydot * Xdot * Y2 + Ydot * X * Y2dot + Y * Xdot * Y2dot);
    }

    static inline constexpr DirectionCosineMatrixAccel<_in_frame_, _out_frame_>
        XYZ(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot,
            const AngularAcceleration& alphaDotDot,
            const AngularAcceleration& betaDotDot,
            const AngularAcceleration& gammaDotDot)
    {
        const auto X     = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::X(alpha);
        const auto Xdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::X(alpha, alphaDot);
        const auto Xddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::X(alpha, alphaDot, alphaDotDot);

        const auto Y     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Y(beta);
        const auto Ydot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Y(beta, betaDot);
        const auto Yddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::Y(beta, betaDot, betaDotDot);

        const auto Z     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Z(gamma);
        const auto Zdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Z(gamma, gammaDot);
        const auto Zddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::Z(gamma, gammaDot, gammaDotDot);

        return Xddot * Y * Z + X * Yddot * Z + X * Y * Zddot + 2.0 * (Xdot * Ydot * Z + Xdot * Y * Zdot + X * Ydot * Zdot);
    }

    static inline constexpr DirectionCosineMatrixAccel<_in_frame_, _out_frame_>
        YZX(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot,
            const AngularAcceleration& alphaDotDot,
            const AngularAcceleration& betaDotDot,
            const AngularAcceleration& gammaDotDot)
    {
        const auto Y     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Y(alpha);
        const auto Ydot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Y(alpha, alphaDot);
        const auto Yddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::Y(alpha, alphaDot, alphaDotDot);

        const auto Z     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Z(beta);
        const auto Zdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Z(beta, betaDot);
        const auto Zddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::Z(beta, betaDot, betaDotDot);

        const auto X     = DirectionCosineMatrix<_in_frame_, _out_frame_>::X(gamma);
        const auto Xdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::X(gamma, gammaDot);
        const auto Xddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::X(gamma, gammaDot, gammaDotDot);

        return Yddot * Z * X + Y * Zddot * X + Y * Z * Xddot + 2.0 * (Ydot * Zdot * X + Ydot * Z * Xdot + Y * Zdot * Xdot);
    }

    static inline constexpr DirectionCosineMatrixAccel<_in_frame_, _out_frame_>
        ZXY(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot,
            const AngularAcceleration& alphaDotDot,
            const AngularAcceleration& betaDotDot,
            const AngularAcceleration& gammaDotDot)
    {
        const auto Z     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Z(alpha);
        const auto Zdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Z(alpha, alphaDot);
        const auto Zddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::Z(alpha, alphaDot, alphaDotDot);

        const auto X     = DirectionCosineMatrix<_in_frame_, _out_frame_>::X(beta);
        const auto Xdot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::X(beta, betaDot);
        const auto Xddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::X(beta, betaDot, betaDotDot);

        const auto Y     = DirectionCosineMatrix<_in_frame_, _out_frame_>::Y(gamma);
        const auto Ydot  = DirectionCosineMatrixRate<_in_frame_, _out_frame_>::Y(gamma, gammaDot);
        const auto Yddot = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::Y(gamma, gammaDot, gammaDotDot);

        return Zddot * X * Y + Z * Xddot * Y + Z * X * Yddot + 2.0 * (Zdot * Xdot * Y + Zdot * X * Ydot + Z * Xdot * Ydot);
    }

    static inline constexpr DirectionCosineMatrixAccel<_in_frame_, _out_frame_>
        XZY(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot,
            const AngularAcceleration& alphaDotDot,
            const AngularAcceleration& betaDotDot,
            const AngularAcceleration& gammaDotDot)
    {
        return DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::YZX(gamma, gammaDot, beta, betaDot, alpha, alphaDot, gammaDotDot, betaDotDot, alphaDotDot);
    }

    static inline constexpr DirectionCosineMatrixAccel<_in_frame_, _out_frame_>
        ZYX(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot,
            const AngularAcceleration& alphaDotDot,
            const AngularAcceleration& betaDotDot,
            const AngularAcceleration& gammaDotDot)
    {
        return DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::XYZ(gamma, gammaDot, beta, betaDot, alpha, alphaDot, gammaDotDot, betaDotDot, alphaDotDot);
    }

    static inline constexpr DirectionCosineMatrixAccel<_in_frame_, _out_frame_>
        YXZ(const Angle& alpha,
            const Angle& beta,
            const Angle& gamma,
            const AngularVelocity& alphaDot,
            const AngularVelocity& betaDot,
            const AngularVelocity& gammaDot,
            const AngularAcceleration& alphaDotDot,
            const AngularAcceleration& betaDotDot,
            const AngularAcceleration& gammaDotDot)
    {
        return DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::ZXY(gamma, gammaDot, beta, betaDot, alpha, alphaDot, gammaDotDot, betaDotDot, alphaDotDot);
    }

    template <RotationSequence sequence>
    static inline constexpr DirectionCosineMatrixAccel<_in_frame_, _out_frame_> from_euler_angles(
        const Angle& alpha,
        const Angle& beta,
        const Angle& gamma,
        const AngularVelocity& alphaDot,
        const AngularVelocity& betaDot,
        const AngularVelocity& gammaDot,
        const AngularAcceleration& alphaDotDot,
        const AngularAcceleration& betaDotDot,
        const AngularAcceleration& gammaDotDot
    )
    {
        if constexpr (sequence == RotationSequence::ZXZ) {
            return DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::ZXZ(
                alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot
            );
        }
        else if constexpr (sequence == RotationSequence::XYX) {
            return DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::XYX(
                alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot
            );
        }
        else if constexpr (sequence == RotationSequence::YZY) {
            return DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::YZY(
                alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot
            );
        }
        else if constexpr (sequence == RotationSequence::ZYZ) {
            return DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::ZYZ(
                alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot
            );
        }
        else if constexpr (sequence == RotationSequence::XZX) {
            return DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::XZX(
                alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot
            );
        }
        else if constexpr (sequence == RotationSequence::YXY) {
            return DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::YXY(
                alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot
            );
        }
        else if constexpr (sequence == RotationSequence::XYZ) {
            return DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::XYZ(
                alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot
            );
        }
        else if constexpr (sequence == RotationSequence::YZX) {
            return DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::YZX(
                alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot
            );
        }
        else if constexpr (sequence == RotationSequence::ZXY) {
            return DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::ZXY(
                alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot
            );
        }
        else if constexpr (sequence == RotationSequence::XZY) {
            return DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::XZY(
                alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot
            );
        }
        else if constexpr (sequence == RotationSequence::ZYX) {
            return DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::ZYX(
                alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot
            );
        }
        else if constexpr (sequence == RotationSequence::YXZ) {
            return DirectionCosineMatrixAccel<_in_frame_, _out_frame_>::YXZ(
                alpha, alphaDot, beta, betaDot, gamma, gammaDot, alphaDotDot, betaDotDot, gammaDotDot
            );
        }
    }

    inline constexpr DirectionCosineMatrixAccel<_out_frame_, _in_frame_> transpose() const
    {
        return { static_cast<DcmInterface<Chirp, _in_frame_, _out_frame_>>(*this).transpose() };
    }

    static inline constexpr DirectionCosineMatrixAccel identity()
    {
        return { DcmInterface<Chirp, _in_frame_, _out_frame_>::identity() };
    }

    static inline constexpr DirectionCosineMatrixAccel zero()
    {
        return { DcmInterface<Chirp, _in_frame_, _out_frame_>::zero() };
    }
};


template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
using DcmAccel = DirectionCosineMatrixAccel<_in_frame_, _out_frame_>;

// Defined template function and then delete it so we can enforce lookup restrictions
template <IsFrame auto frame, IsFrame auto frame_u>
inline constexpr DcmAccel<frame, frame_u> get_dcm_accel(const Date& date) = delete;

} // namespace astro
} // namespace astrea
```


