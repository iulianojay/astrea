

# File DirectionCosineMatrix.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**types**](dir_6f58486cdc039e35eca8cf5d1aadadc3.md) **>** [**DirectionCosineMatrix.hpp**](DirectionCosineMatrix_8hpp.md)

[Go to the documentation of this file](DirectionCosineMatrix_8hpp.md)


```C++

#pragma once

#include <array>
#include <iostream>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>

#include <utilities/string_util.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/frame_concepts.hpp>

namespace astrea {
namespace astro {

// TODO: Probably should use eigen instead of arrays, might not matter for these small matrices used in
//  rotation but worth looking into
template <typename In_Frame_T, typename Out_Frame_T>
class DirectionCosineMatrix {
  public:
    DirectionCosineMatrix(const std::array<std::array<Unitless, 3>, 3>& matrix) :
        _matrix{ matrix }
    {
    }

    static DirectionCosineMatrix<In_Frame_T, Out_Frame_T> X(const Angle& theta)
    {
        using mp_units::one;
        using mp_units::angular::cos;
        using mp_units::angular::sin;
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{ { std::array<Unitless, 3>{ 1.0 * one, 0.0 * one, 0.0 * one },
                                                                 std::array<Unitless, 3>{ 0.0 * one, cos(theta), -sin(theta) },
                                                                 std::array<Unitless, 3>{ 0.0 * one, sin(theta), cos(theta) } } };
    }

    static DirectionCosineMatrix<In_Frame_T, Out_Frame_T> Y(const Angle& theta)
    {
        using mp_units::one;
        using mp_units::angular::cos;
        using mp_units::angular::sin;
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{ { std::array<Unitless, 3>{ cos(theta), 0.0 * one, sin(theta) },
                                                                 std::array<Unitless, 3>{ 0.0 * one, 1.0 * one, 0.0 * one },
                                                                 std::array<Unitless, 3>{ -sin(theta), 0.0 * one, cos(theta) } } };
    }

    static DirectionCosineMatrix<In_Frame_T, Out_Frame_T> Z(const Angle& theta)
    {
        using mp_units::one;
        using mp_units::angular::cos;
        using mp_units::angular::sin;
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{ { std::array<Unitless, 3>{ cos(theta), -sin(theta), 0.0 * one },
                                                                 std::array<Unitless, 3>{ sin(theta), cos(theta), 0.0 * one },
                                                                 std::array<Unitless, 3>{ 0.0 * one, 0.0 * one, 1.0 * one } } };
    }

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

    static DirectionCosineMatrix<In_Frame_T, Out_Frame_T> from_vectors(
        const CartesianVector<Unitless, In_Frame_T>& x,
        const CartesianVector<Unitless, In_Frame_T>& y,
        const CartesianVector<Unitless, In_Frame_T>& z
    )
    {
        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{ { std::array<Unitless, 3>{ x[0], x[1], x[2] },
                                                                 std::array<Unitless, 3>{ y[0], y[1], y[2] },
                                                                 std::array<Unitless, 3>{ z[0], z[1], z[2] } } };
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

    template <typename Value_T>
    CartesianVector<Value_T, Out_Frame_T> operator*(const CartesianVector<Value_T, In_Frame_T>& vec) const
    {
        return CartesianVector<Value_T, Out_Frame_T>(row(0).dot(vec), row(1).dot(vec), row(2).dot(vec));
    }
    CartesianVector<Unitless, In_Frame_T> row(const std::size_t& idx) const
    {
        return { _matrix[idx][0], _matrix[idx][1], _matrix[idx][2] };
    }

  private:
    std::array<std::array<Unitless, 3>, 3> _matrix; 
};

template <typename In_Frame_T, typename Out_Frame_T>
using DCM = DirectionCosineMatrix<In_Frame_T, Out_Frame_T>;

// Defined template function and then delete it so we can enforce lookup restrictions
template <typename Frame_T, typename Frame_U>
inline DCM<Frame_T, Frame_U> get_dcm(const Date& date) = delete;

} // namespace astro
} // namespace astrea
```


