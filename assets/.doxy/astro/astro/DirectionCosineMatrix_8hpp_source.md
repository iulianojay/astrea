

# File DirectionCosineMatrix.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**framework**](dir_aa3952657448f7008c08b8ed45c303ac.md) **>** [**DirectionCosineMatrix.hpp**](DirectionCosineMatrix_8hpp.md)

[Go to the documentation of this file](DirectionCosineMatrix_8hpp.md)


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
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

inline constexpr auto sin_cos_pack(const Angle& angle)
{
    using mp_units::angular::cos;
    using mp_units::angular::sin;
    return std::make_pair(sin(angle), cos(angle));
}

// TODO: Probably should use eigen instead of arrays, might not matter for these small matrices used in
//  rotation but worth looking into
template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
struct DirectionCosineMatrix : public DcmInterface<Unitless, _in_frame_, _out_frame_> {

    inline constexpr DirectionCosineMatrix(const std::array<Unitless, 9>& matrix) :
        DcmInterface<Unitless, _in_frame_, _out_frame_>{ matrix }
    {
        this->normalize();
    }

    inline constexpr DirectionCosineMatrix(const std::array<Unitless, 3>& row1, const std::array<Unitless, 3>& row2, const std::array<Unitless, 3>& row3) :
        DcmInterface<Unitless, _in_frame_, _out_frame_>{ row1, row2, row3 }
    {
        this->normalize();
    }

    inline constexpr DirectionCosineMatrix(const DcmInterface<Unitless, _in_frame_, _out_frame_>& matrix) :
        DcmInterface<Unitless, _in_frame_, _out_frame_>{ matrix }
    {
        this->normalize();
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> X(const Angle& theta)
    {
        using mp_units::one;
        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);
        return { { 1.0 * one, 0.0 * one, 0.0 * one }, { 0.0 * one, cosTheta, -sinTheta }, { 0.0 * one, sinTheta, cosTheta } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> Y(const Angle& theta)
    {
        using mp_units::one;
        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);
        return { { cosTheta, 0.0 * one, sinTheta }, { 0.0 * one, 1.0 * one, 0.0 * one }, { -sinTheta, 0.0 * one, cosTheta } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> Z(const Angle& theta)
    {
        using mp_units::one;
        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);
        return { { cosTheta, -sinTheta, 0.0 * one }, { sinTheta, cosTheta, 0.0 * one }, { 0.0 * one, 0.0 * one, 1.0 * one } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> XZX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return { { cosBeta, -cosGamma * sinBeta, sinBeta * sinGamma },
                 { cosAlpha * sinBeta, cosAlpha * cosBeta * cosGamma - sinAlpha * sinGamma, -cosGamma * sinAlpha - cosAlpha * cosBeta * sinGamma },
                 { sinAlpha * sinBeta, cosAlpha * sinBeta + cosBeta * cosGamma * sinAlpha, cosAlpha * cosGamma - cosBeta * sinGamma * sinAlpha } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> XYX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return { { cosBeta, sinBeta * sinGamma, cosGamma * sinBeta },
                 { sinAlpha * sinBeta, cosAlpha * cosBeta - cosGamma * sinAlpha * sinBeta, -cosAlpha * sinGamma - cosBeta * cosGamma * sinAlpha },
                 { -cosAlpha * sinBeta, cosGamma * cosAlpha * sinBeta + cosBeta * sinAlpha, cosAlpha * cosBeta * cosGamma - sinAlpha * sinGamma } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> YZY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return {
            { cosAlpha * cosBeta * cosGamma - sinAlpha * sinGamma, cosGamma * sinAlpha + cosAlpha * cosBeta * sinGamma, -cosAlpha * sinBeta },
            { -cosGamma * sinBeta, sinBeta * sinGamma, cosBeta },
            { cosBeta * cosGamma * sinAlpha + cosAlpha * sinGamma, cosAlpha * cosGamma - cosBeta * sinAlpha * sinGamma, sinAlpha * sinBeta }
        };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> ZXZ(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return { { cosAlpha * cosGamma - cosBeta * sinAlpha * sinGamma, -cosAlpha * sinGamma - cosBeta * cosGamma * sinAlpha, sinAlpha * sinBeta },
                 { cosGamma * sinAlpha + cosAlpha * cosBeta * sinGamma, cosAlpha * cosBeta * cosGamma - sinAlpha * sinGamma, -cosAlpha * sinBeta },
                 { sinBeta * sinGamma, cosGamma * sinBeta, cosBeta } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> ZYZ(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return { { cosAlpha * cosBeta * cosGamma - sinAlpha * sinGamma, -cosGamma * sinAlpha - cosAlpha * cosBeta * sinGamma, cosAlpha * sinBeta },
                 { cosAlpha * sinGamma + cosBeta * cosGamma * sinAlpha, cosAlpha * cosGamma - cosBeta * sinAlpha * sinGamma, sinAlpha * sinBeta },
                 { -cosGamma * sinBeta, sinBeta * sinGamma, cosBeta } };
    }


    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> YXY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return { { cosAlpha * cosGamma - cosBeta * sinAlpha * sinGamma, sinBeta * sinGamma, cosGamma * sinAlpha + cosAlpha * cosBeta * sinGamma },
                 { sinAlpha * sinBeta, cosBeta, -cosAlpha * sinBeta },
                 { -cosBeta * cosGamma * sinAlpha - cosAlpha * sinGamma,
                   cosGamma * sinBeta,
                   cosAlpha * cosBeta * cosGamma - sinAlpha * sinGamma } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> XYZ(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return {
            { cosBeta * cosGamma, -cosBeta * sinGamma, sinBeta },
            { cosAlpha * sinGamma + cosGamma * sinAlpha * sinBeta, cosAlpha * cosGamma - sinAlpha * sinBeta * sinGamma, -cosBeta * sinAlpha },
            { sinAlpha * sinGamma - cosAlpha * cosGamma * sinBeta, cosGamma * sinAlpha + cosAlpha * sinBeta * sinGamma, cosAlpha * cosBeta }
        };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> YZX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return { { cosAlpha * cosBeta, -sinBeta, cosBeta * sinAlpha },
                 { cosGamma * sinAlpha + cosAlpha * sinBeta * sinGamma, cosBeta * cosGamma, sinAlpha * sinBeta * sinGamma - cosAlpha * cosGamma },
                 { sinAlpha * sinGamma - cosAlpha * cosGamma * sinBeta, cosGamma * sinBeta, cosAlpha * sinGamma + cosGamma * sinAlpha * sinBeta } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> ZXY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return { { cosAlpha * cosGamma - sinAlpha * sinBeta * sinGamma, -cosBeta * sinAlpha, cosAlpha * sinGamma + cosGamma * sinAlpha * sinBeta },
                 { cosGamma * sinAlpha + cosAlpha * sinBeta * sinGamma, cosAlpha * cosBeta, sinAlpha * sinGamma - cosAlpha * cosGamma * sinBeta },
                 { -cosGamma * sinBeta, sinBeta, cosBeta * cosGamma } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> XZY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        return DirectionCosineMatrix<_in_frame_, _out_frame_>::YZX(gamma, beta, alpha);
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> ZYX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        return DirectionCosineMatrix<_in_frame_, _out_frame_>::XYZ(gamma, beta, alpha);
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> YXZ(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        return DirectionCosineMatrix<_in_frame_, _out_frame_>::ZXY(gamma, beta, alpha);
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> from_vectors(
        const CartesianVector<Unitless, _in_frame_>& x,
        const CartesianVector<Unitless, _in_frame_>& y,
        const CartesianVector<Unitless, _in_frame_>& z
    )
    {
        return { { x[0], x[1], x[2] }, { y[0], y[1], y[2] }, { z[0], z[1], z[2] } };
    }

    template <RotationSequence sequence>
    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_>
        from_euler_angles(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        if constexpr (sequence == RotationSequence::ZXZ) {
            return DirectionCosineMatrix<_in_frame_, _out_frame_>::ZXZ(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::XYX) {
            return DirectionCosineMatrix<_in_frame_, _out_frame_>::XYX(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::YZY) {
            return DirectionCosineMatrix<_in_frame_, _out_frame_>::YZY(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::ZYZ) {
            return DirectionCosineMatrix<_in_frame_, _out_frame_>::ZYZ(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::XZX) {
            return DirectionCosineMatrix<_in_frame_, _out_frame_>::XZX(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::YXY) {
            return DirectionCosineMatrix<_in_frame_, _out_frame_>::YXY(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::XYZ) {
            return DirectionCosineMatrix<_in_frame_, _out_frame_>::XYZ(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::YZX) {
            return DirectionCosineMatrix<_in_frame_, _out_frame_>::YZX(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::ZXY) {
            return DirectionCosineMatrix<_in_frame_, _out_frame_>::ZXY(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::XZY) {
            return DirectionCosineMatrix<_in_frame_, _out_frame_>::XZY(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::ZYX) {
            return DirectionCosineMatrix<_in_frame_, _out_frame_>::ZYX(alpha, beta, gamma);
        }
        else if constexpr (sequence == RotationSequence::YXZ) {
            return DirectionCosineMatrix<_in_frame_, _out_frame_>::YXZ(alpha, beta, gamma);
        }
    }

    inline constexpr DirectionCosineMatrix<_out_frame_, _in_frame_> transpose() const
    {
        return { static_cast<DcmInterface<Unitless, _in_frame_, _out_frame_>>(*this).transpose() };
    }

    static inline constexpr DirectionCosineMatrix identity()
    {
        return { DcmInterface<Unitless, _in_frame_, _out_frame_>::identity() };
    }

    static inline constexpr DirectionCosineMatrix zero()
    {
        return { DcmInterface<Unitless, _in_frame_, _out_frame_>::zero() };
    }
};

template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
using DCM = DirectionCosineMatrix<_in_frame_, _out_frame_>;

// Defined template function and then delete it so we can enforce lookup restrictions
template <IsFrame auto frame, IsFrame auto frame_u>
inline constexpr DCM<frame, frame_u> get_dcm(const Date& date) = delete;

} // namespace astro
} // namespace astrea
```


