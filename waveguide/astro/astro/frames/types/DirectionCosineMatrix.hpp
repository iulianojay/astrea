#pragma once

#include <array>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>

#include <astro/element_sets/CartesianVector.hpp>

namespace waveguide {
namespace astro {

template <typename Out_Frame_T>
class DirectionCosineMatrix {
  public:
    DirectionCosineMatrix() = default;
    DirectionCosineMatrix(const std::array<CartesianVector<Unitless, Out_Frame_T>, 3>& matrix) :
        _matrix(matrix)
    {
    }

    static DirectionCosineMatrix<Out_Frame_T> X(const Angle& theta)
    {
        using mp_units::one;
        using mp_units::angular::cos;
        using mp_units::angular::sin;
        return DirectionCosineMatrix<Out_Frame_T>{ { CartesianVector<Unitless, Out_Frame_T>(1.0 * one, 0.0 * one, 0.0 * one),
                                                     CartesianVector<Unitless, Out_Frame_T>(0.0 * one, cos(theta), -sin(theta)),
                                                     CartesianVector<Unitless, Out_Frame_T>(0.0 * one, sin(theta), cos(theta)) } };
    }

    static DirectionCosineMatrix<Out_Frame_T> Y(const Angle& theta)
    {
        using mp_units::one;
        using mp_units::angular::cos;
        using mp_units::angular::sin;
        return DirectionCosineMatrix<Out_Frame_T>{ { CartesianVector<Unitless, Out_Frame_T>(cos(theta), 0.0 * one, sin(theta)),
                                                     CartesianVector<Unitless, Out_Frame_T>(0.0 * one, 1.0 * one, 0.0 * one),
                                                     CartesianVector<Unitless, Out_Frame_T>(-sin(theta), 0.0 * one, cos(theta)) } };
    }

    static DirectionCosineMatrix<Out_Frame_T> Z(const Angle& theta)
    {
        using mp_units::one;
        using mp_units::angular::cos;
        using mp_units::angular::sin;
        return DirectionCosineMatrix<Out_Frame_T>{ { CartesianVector<Unitless, Out_Frame_T>(cos(theta), -sin(theta), 0.0 * one),
                                                     CartesianVector<Unitless, Out_Frame_T>(sin(theta), cos(theta), 0.0 * one),
                                                     CartesianVector<Unitless, Out_Frame_T>(0.0 * one, 0.0 * one, 1.0 * one) } };
    }

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

    ~DirectionCosineMatrix() = default;

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

template <typename Out_Frame_T>
using DCM = DirectionCosineMatrix<Out_Frame_T>;


} // namespace astro
} // namespace waveguide