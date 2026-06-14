

# File DirectionCosineMatrixRate.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**framework**](dir_aa3952657448f7008c08b8ed45c303ac.md) **>** [**DirectionCosineMatrixRate.hpp**](DirectionCosineMatrixRate_8hpp.md)

[Go to the documentation of this file](DirectionCosineMatrixRate_8hpp.md)


```C++

#pragma once

#include <array>
#include <cmath>
#include <iostream>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>

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

template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
struct DirectionCosineMatrixRate : public DcmInterface<Frequency, _in_frame_, _out_frame_> {

    inline constexpr DirectionCosineMatrixRate(const std::array<Frequency, 9>& matrix) :
        DcmInterface<Frequency, _in_frame_, _out_frame_>{ matrix }
    {
    }

    inline constexpr DirectionCosineMatrixRate(
        const std::array<Frequency, 3>& row1,
        const std::array<Frequency, 3>& row2,
        const std::array<Frequency, 3>& row3
    ) :
        DcmInterface<Frequency, _in_frame_, _out_frame_>{ row1, row2, row3 }
    {
    }

    inline constexpr DirectionCosineMatrixRate(const DcmInterface<Frequency, _in_frame_, _out_frame_>& matrix) :
        DcmInterface<Frequency, _in_frame_, _out_frame_>{ matrix }
    {
    }

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

template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
using DcmRate = DirectionCosineMatrixRate<_in_frame_, _out_frame_>;

// Defined template function and then delete it so we can enforce lookup restrictions
template <IsFrame auto frame, IsFrame auto frame_u>
inline constexpr DcmRate<frame, frame_u> get_dcm_rate(const Date& date) = delete;

} // namespace astro
} // namespace astrea
```


