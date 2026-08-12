/**
 * @file DirectionCosineMatrix.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the DirectionCosineMatrix class in the astro namespace
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

#include <math/trig.hpp>
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
    using math::cos;
    using math::sin;
    return std::make_pair(sin(angle), cos(angle));
}

// TODO: Probably should use eigen instead of arrays, might not matter for these small matrices used in
//  rotation but worth looking into
/**
 * @brief Class representing a direction cosine matrix (DCM) for transforming vectors between state/frames.
 *
 * This class provides methods to create DCMs for various rotations and to apply them to vectors.
 *
 * @tparam _out_frame_ The frame type to which the DCM applies.
 */
template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
struct DirectionCosineMatrix : public DcmInterface<Unitless, _in_frame_, _out_frame_> {

    /**
     * @brief Constructor for DirectionCosineMatrix from an array of CartesianVectors.
     *
     * @param matrix An array containing the three rows of the DCM, each represented as a CartesianVector.
     */
    inline constexpr DirectionCosineMatrix(const std::array<Unitless, 9>& matrix) :
        DcmInterface<Unitless, _in_frame_, _out_frame_>{ matrix }
    {
        this->normalize();
    }

    /**
     * @brief Constructor for DirectionCosineMatrix from an array of CartesianVectors.
     *
     * @param row1 An array containing the three elements of the first row of the DCM.
     * @param row2 An array containing the three elements of the second row of the DCM.
     * @param row3 An array containing the three elements of the third row of the DCM.
     */
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

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis.
     *
     * @param theta The angle of rotation around the X-axis.
     * @return DirectionCosineMatrix<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> X(const Angle& theta)
    {
        using mp_units::one;
        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);
        return { { 1.0 * one, 0.0 * one, 0.0 * one }, { 0.0 * one, cosTheta, -sinTheta }, { 0.0 * one, sinTheta, cosTheta } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis.
     *
     * @param theta The angle of rotation around the Y-axis.
     * @return DirectionCosineMatrix<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> Y(const Angle& theta)
    {
        using mp_units::one;
        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);
        return { { cosTheta, 0.0 * one, sinTheta }, { 0.0 * one, 1.0 * one, 0.0 * one }, { -sinTheta, 0.0 * one, cosTheta } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis.
     *
     * @param theta The angle of rotation around the Z-axis.
     * @return DirectionCosineMatrix<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> Z(const Angle& theta)
    {
        using mp_units::one;
        const auto [sinTheta, cosTheta] = sin_cos_pack(theta);
        return { { cosTheta, -sinTheta, 0.0 * one }, { sinTheta, cosTheta, 0.0 * one }, { 0.0 * one, 0.0 * one, 1.0 * one } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis, the Z-axis, and the X-axis again.
     *
     * @param alpha The angle of rotation around the X-axis.
     * @param beta The angle of rotation around the Z-axis.
     * @param gamma The angle of rotation around the X-axis.
     * @return DirectionCosineMatrix<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> XZX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return { { cosBeta, -sinBeta * cosGamma, sinBeta * sinGamma },
                 { sinBeta * cosAlpha, -sinAlpha * sinGamma + cosAlpha * cosBeta * cosGamma, -sinAlpha * cosGamma - sinGamma * cosAlpha * cosBeta },
                 { sinAlpha * sinBeta,
                   sinAlpha * cosBeta * cosGamma + sinGamma * cosAlpha,
                   -sinAlpha * sinGamma * cosBeta + cosAlpha * cosGamma } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis, the Y-axis, and the X-axis again.
     *
     * @param alpha The angle of rotation around the X-axis.
     * @param beta The angle of rotation around the Y-axis.
     * @param gamma The angle of rotation around the X-axis.
     * @return DirectionCosineMatrix<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> XYX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return { { cosBeta, sinBeta * sinGamma, sinBeta * cosGamma },
                 { sinAlpha * sinBeta, -sinAlpha * sinGamma * cosBeta + cosAlpha * cosGamma, -sinAlpha * cosBeta * cosGamma - sinGamma * cosAlpha },
                 { -sinBeta * cosAlpha,
                   sinAlpha * cosGamma + sinGamma * cosAlpha * cosBeta,
                   -sinAlpha * sinGamma + cosAlpha * cosBeta * cosGamma } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis, the Z-axis, and the Y-axis again.
     *
     * @param alpha The angle of rotation around the Y-axis.
     * @param beta The angle of rotation around the Z-axis.
     * @param gamma The angle of rotation around the Y-axis.
     * @return DirectionCosineMatrix<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> YZY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return { { -sinAlpha * sinGamma + cosAlpha * cosBeta * cosGamma, -sinBeta * cosAlpha, sinAlpha * cosGamma + sinGamma * cosAlpha * cosBeta },
                 { sinBeta * cosGamma, cosBeta, sinBeta * sinGamma },
                 { -sinAlpha * cosBeta * cosGamma - sinGamma * cosAlpha,
                   sinAlpha * sinBeta,
                   -sinAlpha * sinGamma * cosBeta + cosAlpha * cosGamma } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis, the X-axis, and the Z-axis again.
     *
     * @param alpha The angle of rotation around the Z-axis.
     * @param beta The angle of rotation around the X-axis.
     * @param gamma The angle of rotation around the Z-axis.
     * @return DirectionCosineMatrix<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> ZXZ(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return { { cosAlpha * cosGamma - cosBeta * sinAlpha * sinGamma, -cosAlpha * sinGamma - cosBeta * cosGamma * sinAlpha, sinAlpha * sinBeta },
                 { cosGamma * sinAlpha + cosAlpha * cosBeta * sinGamma, cosAlpha * cosBeta * cosGamma - sinAlpha * sinGamma, -cosAlpha * sinBeta },
                 { sinBeta * sinGamma, cosGamma * sinBeta, cosBeta } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis, the Y-axis, and the Z-axis again.
     *
     * @param alpha The angle of rotation around the Z-axis.
     * @param beta The angle of rotation around the Y-axis.
     * @param gamma The angle of rotation around the Z-axis.
     * @return DirectionCosineMatrix<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> ZYZ(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return { { cosAlpha * cosBeta * cosGamma - sinAlpha * sinGamma, -cosGamma * sinAlpha - cosAlpha * cosBeta * sinGamma, cosAlpha * sinBeta },
                 { cosAlpha * sinGamma + cosBeta * cosGamma * sinAlpha, cosAlpha * cosGamma - cosBeta * sinAlpha * sinGamma, sinAlpha * sinBeta },
                 { -cosGamma * sinBeta, sinBeta * sinGamma, cosBeta } };
    }


    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis, the X-axis, and the Y-axis again.
     *
     * @param alpha The angle of rotation around the Y-axis.
     * @param beta The angle of rotation around the X-axis.
     * @param gamma The angle of rotation around the Y-axis.
     * @return DirectionCosineMatrix<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> YXY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return { { -sinAlpha * sinGamma * cosBeta + cosAlpha * cosGamma, sinAlpha * sinBeta, sinAlpha * cosBeta * cosGamma + sinGamma * cosAlpha },
                 { sinBeta * sinGamma, cosBeta, -sinBeta * cosGamma },
                 { -sinAlpha * cosGamma - sinGamma * cosAlpha * cosBeta,
                   sinBeta * cosAlpha,
                   -sinAlpha * sinGamma + cosAlpha * cosBeta * cosGamma } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis, then Y-axis, then Z-axis.
     *
     * @param alpha The angle of rotation around the X-axis.
     * @param beta The angle of rotation around the Y-axis.
     * @param gamma The angle of rotation around the Z-axis.
     * @return DirectionCosineMatrix<_out_frame_> The resulting direction cosine matrix.
     */
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

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis, then Z-axis, then X-axis.
     *
     * @param alpha The angle of rotation around the Y-axis.
     * @param beta The angle of rotation around the Z-axis.
     * @param gamma The angle of rotation around the X-axis.
     * @return DirectionCosineMatrix<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> YZX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return { { cosAlpha * cosBeta, sinAlpha * sinGamma - sinBeta * cosAlpha * cosGamma, sinAlpha * cosGamma + sinBeta * sinGamma * cosAlpha },
                 { sinBeta, cosBeta * cosGamma, -sinGamma * cosBeta },
                 { -sinAlpha * cosBeta,
                   sinAlpha * sinBeta * cosGamma + sinGamma * cosAlpha,
                   -sinAlpha * sinBeta * sinGamma + cosAlpha * cosGamma } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis, then X-axis, then Y-axis.
     *
     * @param alpha The angle of rotation around the Z-axis.
     * @param beta The angle of rotation around the X-axis.
     * @param gamma The angle of rotation around the Y-axis.
     * @return DirectionCosineMatrix<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> ZXY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return { { -sinAlpha * sinBeta * sinGamma + cosAlpha * cosGamma, -sinAlpha * cosBeta, sinAlpha * sinBeta * cosGamma + sinGamma * cosAlpha },
                 { sinAlpha * cosGamma + sinBeta * sinGamma * cosAlpha, cosAlpha * cosBeta, sinAlpha * sinGamma - sinBeta * cosAlpha * cosGamma },
                 { -sinGamma * cosBeta, sinBeta, cosBeta * cosGamma } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis, then Z-axis, then Y-axis.
     *
     * @param alpha The angle of rotation around the X-axis.
     * @param beta The angle of rotation around the Z-axis.
     * @param gamma The angle of rotation around the Y-axis.
     * @return DirectionCosineMatrix<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> XZY(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return { { cosBeta * cosGamma, -sinBeta, sinGamma * cosBeta },
                 { sinAlpha * sinGamma + sinBeta * cosAlpha * cosGamma, cosAlpha * cosBeta, -sinAlpha * cosGamma + sinBeta * sinGamma * cosAlpha },
                 { sinAlpha * sinBeta * cosGamma - sinGamma * cosAlpha, sinAlpha * cosBeta, sinAlpha * sinBeta * sinGamma + cosAlpha * cosGamma } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis, then Y-axis, then X-axis.
     *
     * @param alpha The angle of rotation around the Z-axis.
     * @param beta The angle of rotation around the Y-axis.
     * @param gamma The angle of rotation around the X-axis.
     * @return DirectionCosineMatrix<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> ZYX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return { { cosAlpha * cosBeta, -sinAlpha * cosGamma + sinBeta * sinGamma * cosAlpha, sinAlpha * sinGamma + sinBeta * cosAlpha * cosGamma },
                 { sinAlpha * cosBeta, sinAlpha * sinBeta * sinGamma + cosAlpha * cosGamma, sinAlpha * sinBeta * cosGamma - sinGamma * cosAlpha },
                 { -sinBeta, sinGamma * cosBeta, cosBeta * cosGamma } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis, then X-axis, then Z-axis.
     *
     * @param alpha The angle of rotation around the Y-axis.
     * @param beta The angle of rotation around the X-axis.
     * @param gamma The angle of rotation around the Z-axis.
     * @return DirectionCosineMatrix<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> YXZ(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        const auto [sinAlpha, cosAlpha] = sin_cos_pack(alpha);
        const auto [sinBeta, cosBeta]   = sin_cos_pack(beta);
        const auto [sinGamma, cosGamma] = sin_cos_pack(gamma);
        return { { sinAlpha * sinBeta * sinGamma + cosAlpha * cosGamma, sinAlpha * sinBeta * cosGamma - sinGamma * cosAlpha, sinAlpha * cosBeta },
                 { sinGamma * cosBeta, cosBeta * cosGamma, -sinBeta },
                 { -sinAlpha * cosGamma + sinBeta * sinGamma * cosAlpha,
                   sinAlpha * sinGamma + sinBeta * cosAlpha * cosGamma,
                   cosAlpha * cosBeta } };
    }

    /**
     * @brief Creates a direction cosine matrix from three orthonormal vectors.
     *
     * @param x The unit vector in the X direction.
     * @param y The unit vector in the Y direction.
     * @param z The unit vector in the Z direction.
     * @return DirectionCosineMatrix<_out_frame_> The resulting direction cosine matrix.
     */
    static inline constexpr DirectionCosineMatrix<_in_frame_, _out_frame_> from_vectors(
        const CartesianVector<Unitless, _in_frame_>& x,
        const CartesianVector<Unitless, _in_frame_>& y,
        const CartesianVector<Unitless, _in_frame_>& z
    )
    {
        return { { x[0], x[1], x[2] }, { y[0], y[1], y[2] }, { z[0], z[1], z[2] } };
    }

    /**
     * @brief Creates a direction cosine matrix from Euler angles based on a specified rotation sequence.
     *
     * @tparam sequence The rotation sequence to use for the Euler angles (e.g., XYZ, ZYX, etc.).
     * @param alpha The first Euler angle (rotation around the first axis in the sequence).
     * @param beta The second Euler angle (rotation around the second axis in the sequence).
     * @param gamma The third Euler angle (rotation around the third axis in the sequence).
     * @return DirectionCosineMatrix<_out_frame_> The resulting direction cosine matrix.
     */
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

/**
 * @brief Alias for DirectionCosineMatrix with a specific output frame type.
 *
 * This alias simplifies the usage of DirectionCosineMatrix by allowing the user to specify the output frame type.
 *
 * @tparam _out_frame_ The frame type to which the DCM applies.
 */
template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
using DCM = DirectionCosineMatrix<_in_frame_, _out_frame_>;

// Defined template function and then delete it so we can enforce lookup restrictions
template <IsFrame auto frame, IsFrame auto frame_u>
inline constexpr DCM<frame, frame_u> get_dcm(const Date& date) = delete;

} // namespace astro
} // namespace astrea