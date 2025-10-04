/**
 * @file DirectionCosineMatrix.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the DirectionCosineMatrix class in the astro namespace
 * @version 0.1
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <array>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>

#include <utilities/string_util.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/frame_concepts.hpp>

namespace astrea {
namespace astro {

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
  public:
    /**
     * @brief Constructor for DirectionCosineMatrix from an array of CartesianVectors.
     *
     * @param matrix An array containing the three rows of the DCM, each represented as a CartesianVector.
     */
    DirectionCosineMatrix(const std::array<std::array<Unitless, 3>, 3>& matrix) :
        _matrix{ matrix }
    {
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis.
     *
     * @param theta The angle of rotation around the X-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static DirectionCosineMatrix<In_Frame_T, Out_Frame_T> X(const Angle& theta)
    {
        using mp_units::one;
        using mp_units::angular::cos;
        using mp_units::angular::sin;
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{ { std::array<Unitless, 3>{ 1.0 * one, 0.0 * one, 0.0 * one },
                                                                 std::array<Unitless, 3>{ 0.0 * one, cos(theta), -sin(theta) },
                                                                 std::array<Unitless, 3>{ 0.0 * one, sin(theta), cos(theta) } } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis.
     *
     * @param theta The angle of rotation around the Y-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static DirectionCosineMatrix<In_Frame_T, Out_Frame_T> Y(const Angle& theta)
    {
        using mp_units::one;
        using mp_units::angular::cos;
        using mp_units::angular::sin;
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{ { std::array<Unitless, 3>{ cos(theta), 0.0 * one, sin(theta) },
                                                                 std::array<Unitless, 3>{ 0.0 * one, 1.0 * one, 0.0 * one },
                                                                 std::array<Unitless, 3>{ -sin(theta), 0.0 * one, cos(theta) } } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis.
     *
     * @param theta The angle of rotation around the Z-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static DirectionCosineMatrix<In_Frame_T, Out_Frame_T> Z(const Angle& theta)
    {
        using mp_units::one;
        using mp_units::angular::cos;
        using mp_units::angular::sin;
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{ { std::array<Unitless, 3>{ cos(theta), -sin(theta), 0.0 * one },
                                                                 std::array<Unitless, 3>{ sin(theta), cos(theta), 0.0 * one },
                                                                 std::array<Unitless, 3>{ 0.0 * one, 0.0 * one, 1.0 * one } } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis followed by a rotation around the Z-axis.
     *
     * @param alpha The angle of rotation around the X-axis.
     * @param beta The angle of rotation around the Y-axis.
     * @param gamma The angle of rotation around the Z-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static DirectionCosineMatrix<In_Frame_T, Out_Frame_T> XZX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        using mp_units::angular::cos;
        using mp_units::angular::sin;
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{
            { std::array<Unitless, 3>{ cos(beta), -cos(gamma) * sin(beta), sin(beta) * sin(gamma) },
              std::array<Unitless, 3>{ cos(alpha) * sin(beta),
                                       cos(alpha) * cos(beta) * cos(gamma) - sin(alpha) * sin(gamma),
                                       -cos(gamma) * sin(alpha) - cos(alpha) * cos(beta) * sin(gamma) },
              std::array<Unitless, 3>{ sin(alpha) * sin(beta),
                                       cos(alpha) * sin(beta) + cos(beta) * cos(gamma) * sin(alpha),
                                       cos(alpha) * cos(gamma) - cos(beta) * sin(gamma) * sin(alpha) } }
        };
    }

    /**
     * @brief Creates a direction cosine matrix from three orthonormal vectors.
     *
     * @param x The unit vector in the X direction.
     * @param y The unit vector in the Y direction.
     * @param z The unit vector in the Z direction.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static DirectionCosineMatrix<In_Frame_T, Out_Frame_T> from_vectors(
        const CartesianVector<Unitless, In_Frame_T>& x,
        const CartesianVector<Unitless, In_Frame_T>& y,
        const CartesianVector<Unitless, In_Frame_T>& z
    )
    {
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{ { std::array<Unitless, 3>{ x[0], y[0], z[0] },
                                                                 std::array<Unitless, 3>{ x[1], y[1], z[1] },
                                                                 std::array<Unitless, 3>{ x[2], y[2], z[2] } } };
    }

    static DirectionCosineMatrix<In_Frame_T, Out_Frame_T> identity()
    {
        using mp_units::one;
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{ { std::array<Unitless, 3>{ 1.0 * one, 0.0 * one, 0.0 * one },
                                                                 std::array<Unitless, 3>{ 0.0 * one, 1.0 * one, 0.0 * one },
                                                                 std::array<Unitless, 3>{ 0.0 * one, 0.0 * one, 1.0 * one } } };
    }

    DirectionCosineMatrix<Out_Frame_T, In_Frame_T> transpose() const
    {
        return DirectionCosineMatrix<Out_Frame_T, In_Frame_T>{
            { std::array<Unitless, 3>{ _matrix[0][0], _matrix[1][0], _matrix[2][0] },
              std::array<Unitless, 3>{ _matrix[0][1], _matrix[1][1], _matrix[2][1] },
              std::array<Unitless, 3>{ _matrix[0][2], _matrix[1][2], _matrix[2][2] } }
        };
    }

    /**
     * @brief Apply the direction cosine matrix to a CartesianVector.
     *
     * @tparam Value_T The type of the vector components.
     * @tparam Frame_T The frame of the CartesianVector.
     * @param vec The CartesianVector to which the DCM will be applied.
     * @return CartesianVector<Value_T, Out_Frame_T> The transformed CartesianVector in the output frame.
     */
    template <typename Value_T>
    CartesianVector<Value_T, Out_Frame_T> operator*(const CartesianVector<Value_T, In_Frame_T>& vec) const
    {
        return CartesianVector<Value_T, Out_Frame_T>(row(0).dot(vec), row(1).dot(vec), row(2).dot(vec));
    }
    /**
     * @brief Get a specific row of the direction cosine matrix.
     *
     * @param idx The index of the row to retrieve (0, 1, or 2).
     * @return const CartesianVector<Value_T, In_Frame_T>& The requested row as a CartesianVector.
     */
    CartesianVector<Unitless, In_Frame_T> row(const std::size_t& idx) const
    {
        return { _matrix[idx][0], _matrix[idx][1], _matrix[idx][2] };
    }

  private:
    std::array<std::array<Unitless, 3>, 3> _matrix; //!< 3x3 matrix to hold the direction cosines.
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

// Defined template function and then delete it so we can enforce lookup restrictions
template <typename Frame_T, typename Frame_U>
inline DCM<Frame_T, Frame_U> get_dcm(const Date& date) = delete;

struct DcmManager {
    DcmManager()                  = delete;
    ~DcmManager()                 = delete;
    DcmManager(const DcmManager&) = delete;
    DcmManager(DcmManager&&)      = delete;

    template <typename Frame_T, typename Frame_U>
    static DCM<Frame_T, Frame_U> get_dcm(const Date& date)
    {
        static_assert(!(HasDcm<Frame_T, Frame_U> && HasDcm<Frame_U, Frame_T>), "DCM defined in both directions, please define only one to avoid symmetry issues.");
        static_assert(IsStaticFrame<Frame_T> && IsStaticFrame<Frame_U>, "Dynamic frame conversions cannot be called statically. Dynamic frames must be created at runtime with a platform to reference.");
        static_assert(HasDcm<Frame_T, Frame_U> || HasDcm<Frame_U, Frame_T> || IsSameFrame<Frame_T, Frame_U>, "No DCM defined between these two frames.");

        if constexpr (IsSameFrame<Frame_T, Frame_U>) {
            return astrea::astro::DCM<Frame_T, Frame_U>::identity(); // TODO: Figure out how to do this earlier to avoid unnecessary matrix math
        }
        else if constexpr (HasDcm<Frame_T, Frame_U> && !HasDcm<Frame_U, Frame_T>) {
            return astrea::astro::get_dcm<Frame_T, Frame_U>(date);
        }
        else if constexpr (!HasDcm<Frame_T, Frame_U> && HasDcm<Frame_U, Frame_T>) {
            return astrea::astro::get_dcm<Frame_U, Frame_T>(date).transpose();
        }
        throw std::logic_error("How did you get here?");
    }
};

} // namespace astro
} // namespace astrea