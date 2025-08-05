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

#include <astro/element_sets/CartesianVector.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief Class representing a direction cosine matrix (DCM) for transforming vectors between frames.
 *
 * This class provides methods to create DCMs for various rotations and to apply them to vectors.
 *
 * @tparam Out_Frame_T The frame type to which the DCM applies.
 */
template <typename Out_Frame_T>
class DirectionCosineMatrix {
  public:
    /**
     * @brief Default constructor for DirectionCosineMatrix.
     *
     * Initializes the DCM with an identity matrix.
     */
    DirectionCosineMatrix() = default;

    /**
     * @brief Constructor for DirectionCosineMatrix from an array of CartesianVectors.
     *
     * @param matrix An array containing the three rows of the DCM, each represented as a CartesianVector.
     */
    DirectionCosineMatrix(const std::array<CartesianVector<Unitless, Out_Frame_T>, 3>& matrix) :
        _matrix(matrix)
    {
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis.
     *
     * @param theta The angle of rotation around the X-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static DirectionCosineMatrix<Out_Frame_T> X(const Angle& theta)
    {
        using mp_units::one;
        using mp_units::angular::cos;
        using mp_units::angular::sin;
        return DirectionCosineMatrix<Out_Frame_T>{ { CartesianVector<Unitless, Out_Frame_T>(1.0 * one, 0.0 * one, 0.0 * one),
                                                     CartesianVector<Unitless, Out_Frame_T>(0.0 * one, cos(theta), -sin(theta)),
                                                     CartesianVector<Unitless, Out_Frame_T>(0.0 * one, sin(theta), cos(theta)) } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Y-axis.
     *
     * @param theta The angle of rotation around the Y-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static DirectionCosineMatrix<Out_Frame_T> Y(const Angle& theta)
    {
        using mp_units::one;
        using mp_units::angular::cos;
        using mp_units::angular::sin;
        return DirectionCosineMatrix<Out_Frame_T>{ { CartesianVector<Unitless, Out_Frame_T>(cos(theta), 0.0 * one, sin(theta)),
                                                     CartesianVector<Unitless, Out_Frame_T>(0.0 * one, 1.0 * one, 0.0 * one),
                                                     CartesianVector<Unitless, Out_Frame_T>(-sin(theta), 0.0 * one, cos(theta)) } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the Z-axis.
     *
     * @param theta The angle of rotation around the Z-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static DirectionCosineMatrix<Out_Frame_T> Z(const Angle& theta)
    {
        using mp_units::one;
        using mp_units::angular::cos;
        using mp_units::angular::sin;
        return DirectionCosineMatrix<Out_Frame_T>{ { CartesianVector<Unitless, Out_Frame_T>(cos(theta), -sin(theta), 0.0 * one),
                                                     CartesianVector<Unitless, Out_Frame_T>(sin(theta), cos(theta), 0.0 * one),
                                                     CartesianVector<Unitless, Out_Frame_T>(0.0 * one, 0.0 * one, 1.0 * one) } };
    }

    /**
     * @brief Creates a direction cosine matrix for a rotation around the X-axis followed by a rotation around the Z-axis.
     *
     * @param alpha The angle of rotation around the X-axis.
     * @param beta The angle of rotation around the Y-axis.
     * @param gamma The angle of rotation around the Z-axis.
     * @return DirectionCosineMatrix<Out_Frame_T> The resulting direction cosine matrix.
     */
    static DirectionCosineMatrix<Out_Frame_T> XZX(const Angle& alpha, const Angle& beta, const Angle& gamma)
    {
        using mp_units::angular::cos;
        using mp_units::angular::sin;
        return DirectionCosineMatrix<Out_Frame_T>{
            { CartesianVector<Unitless, Out_Frame_T>(cos(beta), -cos(gamma) * sin(beta), sin(beta) * sin(gamma)),
              CartesianVector<Unitless, Out_Frame_T>(
                  cos(alpha) * sin(beta),
                  cos(alpha) * cos(beta) * cos(gamma) - sin(alpha) * sin(gamma),
                  -cos(gamma) * sin(alpha) - cos(alpha) * cos(beta) * sin(gamma)
              ),
              CartesianVector<Unitless, Out_Frame_T>(
                  sin(alpha) * sin(beta),
                  cos(alpha) * sin(beta) + cos(beta) * cos(gamma) * sin(alpha),
                  cos(alpha) * cos(gamma) - cos(beta) * sin(gamma) * sin(alpha)
              ) }
        };
    }

    /**
     * @brief Default destructor for DirectionCosineMatrix.
     */
    ~DirectionCosineMatrix() = default;

    /**
     * @brief Apply the direction cosine matrix to a CartesianVector.
     *
     * @tparam Value_T The type of the vector components.
     * @tparam Frame_T The frame of the CartesianVector.
     * @param vec The CartesianVector to which the DCM will be applied.
     * @return CartesianVector<Value_T, Out_Frame_T> The transformed CartesianVector in the output frame.
     */
    template <typename Value_T, typename Frame_T>
    CartesianVector<Value_T, Out_Frame_T> operator*(const CartesianVector<Value_T, Frame_T>& vec) const
    {
        return CartesianVector<Value_T, Out_Frame_T>(
            static_cast<CartesianVector<Unitless, Frame_T>>(_matrix[0]).dot(vec), // Force into the same frame since a DCM is "frameless"
            static_cast<CartesianVector<Unitless, Frame_T>>(_matrix[1]).dot(vec),
            static_cast<CartesianVector<Unitless, Frame_T>>(_matrix[2]).dot(vec)
        );
    }

  private:
    std::array<CartesianVector<Unitless, Out_Frame_T>, 3> _matrix; //<! 3x3 matrix to hold the direction cosines.
};

/**
 * @brief Alias for DirectionCosineMatrix with a specific output frame type.
 *
 * This alias simplifies the usage of DirectionCosineMatrix by allowing the user to specify the output frame type.
 *
 * @tparam Out_Frame_T The frame type to which the DCM applies.
 */
template <typename Out_Frame_T>
using DCM = DirectionCosineMatrix<Out_Frame_T>;


} // namespace astro
} // namespace waveguide