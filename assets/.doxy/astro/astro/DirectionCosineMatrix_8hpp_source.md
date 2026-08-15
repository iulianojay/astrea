

# File DirectionCosineMatrix.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**framework**](dir_aa3952657448f7008c08b8ed45c303ac.md) **>** [**DirectionCosineMatrix.hpp**](DirectionCosineMatrix_8hpp.md)

[Go to the documentation of this file](DirectionCosineMatrix_8hpp.md)


```C++

#pragma once

#include <array>
#include <cmath>
#include <iostream>

#include <mp-units/math.h>
#include <mp-units/systems/si/math.h>

#include <math/trig.hpp>
#include <units/units.hpp>
#include <utilities/string_util.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/framework/DcmInterface.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

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

    template <IsFrame auto in_frame_u, IsFrame auto out_frame_u>
        requires(equivalent(in_frame_u, _in_frame_) && equivalent(out_frame_u, _out_frame_))
    inline constexpr DirectionCosineMatrix(const DirectionCosineMatrix<in_frame_u, out_frame_u>& other) :
        DcmInterface<Unitless, _in_frame_, _out_frame_>{ other.data() }
    {
        this->normalize();
    }

    template <IsFrame auto in_frame_u, IsFrame auto out_frame_u>
        requires(equivalent(in_frame_u, _in_frame_) && equivalent(out_frame_u, _out_frame_))
    inline constexpr DirectionCosineMatrix(DirectionCosineMatrix<in_frame_u, out_frame_u>&& other) :
        DcmInterface<Unitless, _in_frame_, _out_frame_>{ std::move(other.data()) }
    {
        this->normalize();
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> X(const Angle& theta)
    {
        using mp_units::one;
        const auto [sinTheta, cosTheta] = math::sin_cos_pack(theta);
        return { { 1.0 * one, 0.0 * one, 0.0 * one }, { 0.0 * one, cosTheta, -sinTheta }, { 0.0 * one, sinTheta, cosTheta } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> Y(const Angle& theta)
    {
        using mp_units::one;
        const auto [sinTheta, cosTheta] = math::sin_cos_pack(theta);
        return { { cosTheta, 0.0 * one, sinTheta }, { 0.0 * one, 1.0 * one, 0.0 * one }, { -sinTheta, 0.0 * one, cosTheta } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> Z(const Angle& theta)
    {
        using mp_units::one;
        const auto [sinTheta, cosTheta] = math::sin_cos_pack(theta);
        return { { cosTheta, -sinTheta, 0.0 * one }, { sinTheta, cosTheta, 0.0 * one }, { 0.0 * one, 0.0 * one, 1.0 * one } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> XZX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = math::sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = math::sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = math::sin_cos_pack(gamma);
        return { { cosBeta, -sinBeta * cosGamma, sinBeta * sinGamma },
                 { sinBeta * cosAlpha, -sinAlpha * sinGamma + cosAlpha * cosBeta * cosGamma, -sinAlpha * cosGamma - sinGamma * cosAlpha * cosBeta },
                 { sinAlpha * sinBeta,
                   sinAlpha * cosBeta * cosGamma + sinGamma * cosAlpha,
                   -sinAlpha * sinGamma * cosBeta + cosAlpha * cosGamma } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> XYX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = math::sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = math::sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = math::sin_cos_pack(gamma);
        return { { cosBeta, sinBeta * sinGamma, sinBeta * cosGamma },
                 { sinAlpha * sinBeta, -sinAlpha * sinGamma * cosBeta + cosAlpha * cosGamma, -sinAlpha * cosBeta * cosGamma - sinGamma * cosAlpha },
                 { -sinBeta * cosAlpha,
                   sinAlpha * cosGamma + sinGamma * cosAlpha * cosBeta,
                   -sinAlpha * sinGamma + cosAlpha * cosBeta * cosGamma } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> YZY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = math::sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = math::sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = math::sin_cos_pack(gamma);
        return { { -sinAlpha * sinGamma + cosAlpha * cosBeta * cosGamma, -sinBeta * cosAlpha, sinAlpha * cosGamma + sinGamma * cosAlpha * cosBeta },
                 { sinBeta * cosGamma, cosBeta, sinBeta * sinGamma },
                 { -sinAlpha * cosBeta * cosGamma - sinGamma * cosAlpha,
                   sinAlpha * sinBeta,
                   -sinAlpha * sinGamma * cosBeta + cosAlpha * cosGamma } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> ZXZ(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = math::sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = math::sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = math::sin_cos_pack(gamma);
        return { { cosAlpha * cosGamma - cosBeta * sinAlpha * sinGamma, -cosAlpha * sinGamma - cosBeta * cosGamma * sinAlpha, sinAlpha * sinBeta },
                 { cosGamma * sinAlpha + cosAlpha * cosBeta * sinGamma, cosAlpha * cosBeta * cosGamma - sinAlpha * sinGamma, -cosAlpha * sinBeta },
                 { sinBeta * sinGamma, cosGamma * sinBeta, cosBeta } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> ZYZ(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = math::sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = math::sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = math::sin_cos_pack(gamma);
        return { { cosAlpha * cosBeta * cosGamma - sinAlpha * sinGamma, -cosGamma * sinAlpha - cosAlpha * cosBeta * sinGamma, cosAlpha * sinBeta },
                 { cosAlpha * sinGamma + cosBeta * cosGamma * sinAlpha, cosAlpha * cosGamma - cosBeta * sinAlpha * sinGamma, sinAlpha * sinBeta },
                 { -cosGamma * sinBeta, sinBeta * sinGamma, cosBeta } };
    }


    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> YXY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = math::sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = math::sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = math::sin_cos_pack(gamma);
        return { { -sinAlpha * sinGamma * cosBeta + cosAlpha * cosGamma, sinAlpha * sinBeta, sinAlpha * cosBeta * cosGamma + sinGamma * cosAlpha },
                 { sinBeta * sinGamma, cosBeta, -sinBeta * cosGamma },
                 { -sinAlpha * cosGamma - sinGamma * cosAlpha * cosBeta,
                   sinBeta * cosAlpha,
                   -sinAlpha * sinGamma + cosAlpha * cosBeta * cosGamma } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> XYZ(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = math::sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = math::sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = math::sin_cos_pack(gamma);
        return {
            { cosBeta * cosGamma, -cosBeta * sinGamma, sinBeta },
            { cosAlpha * sinGamma + cosGamma * sinAlpha * sinBeta, cosAlpha * cosGamma - sinAlpha * sinBeta * sinGamma, -cosBeta * sinAlpha },
            { sinAlpha * sinGamma - cosAlpha * cosGamma * sinBeta, cosGamma * sinAlpha + cosAlpha * sinBeta * sinGamma, cosAlpha * cosBeta }
        };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> YZX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = math::sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = math::sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = math::sin_cos_pack(gamma);
        return { { cosAlpha * cosBeta, sinAlpha * sinGamma - sinBeta * cosAlpha * cosGamma, sinAlpha * cosGamma + sinBeta * sinGamma * cosAlpha },
                 { sinBeta, cosBeta * cosGamma, -sinGamma * cosBeta },
                 { -sinAlpha * cosBeta,
                   sinAlpha * sinBeta * cosGamma + sinGamma * cosAlpha,
                   -sinAlpha * sinBeta * sinGamma + cosAlpha * cosGamma } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> ZXY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = math::sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = math::sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = math::sin_cos_pack(gamma);
        return { { -sinAlpha * sinBeta * sinGamma + cosAlpha * cosGamma, -sinAlpha * cosBeta, sinAlpha * sinBeta * cosGamma + sinGamma * cosAlpha },
                 { sinAlpha * cosGamma + sinBeta * sinGamma * cosAlpha, cosAlpha * cosBeta, sinAlpha * sinGamma - sinBeta * cosAlpha * cosGamma },
                 { -sinGamma * cosBeta, sinBeta, cosBeta * cosGamma } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> XZY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = math::sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = math::sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = math::sin_cos_pack(gamma);
        return { { cosBeta * cosGamma, -sinBeta, sinGamma * cosBeta },
                 { sinAlpha * sinGamma + sinBeta * cosAlpha * cosGamma, cosAlpha * cosBeta, -sinAlpha * cosGamma + sinBeta * sinGamma * cosAlpha },
                 { sinAlpha * sinBeta * cosGamma - sinGamma * cosAlpha, sinAlpha * cosBeta, sinAlpha * sinBeta * sinGamma + cosAlpha * cosGamma } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> ZYX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = math::sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = math::sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = math::sin_cos_pack(gamma);
        return { { cosAlpha * cosBeta, -sinAlpha * cosGamma + sinBeta * sinGamma * cosAlpha, sinAlpha * sinGamma + sinBeta * cosAlpha * cosGamma },
                 { sinAlpha * cosBeta, sinAlpha * sinBeta * sinGamma + cosAlpha * cosGamma, sinAlpha * sinBeta * cosGamma - sinGamma * cosAlpha },
                 { -sinBeta, sinGamma * cosBeta, cosBeta * cosGamma } };
    }

    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> YXZ(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = math::sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = math::sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = math::sin_cos_pack(gamma);
        return { { sinAlpha * sinBeta * sinGamma + cosAlpha * cosGamma, sinAlpha * sinBeta * cosGamma - sinGamma * cosAlpha, sinAlpha * cosBeta },
                 { sinGamma * cosBeta, cosBeta * cosGamma, -sinBeta },
                 { -sinAlpha * cosGamma + sinBeta * sinGamma * cosAlpha,
                   sinAlpha * sinGamma + sinBeta * cosAlpha * cosGamma,
                   cosAlpha * cosBeta } };
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


