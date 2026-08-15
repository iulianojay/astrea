

# File InertiaTensor.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**platforms**](dir_2552b27872b33d254ad75ac21654b66a.md) **>** [**InertiaTensor.hpp**](InertiaTensor_8hpp.md)

[Go to the documentation of this file](InertiaTensor_8hpp.md)


```C++

#pragma once

#include <mp-units/framework.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions/dynamic_frames/tags.hpp>
#include <astro/frames/framework/CartesianVector.hpp>

namespace astrea {
namespace astro {

template <IsFrame auto _frame_ = frames::dynamic::body>
class InertiaTensor {

    static constexpr MomentOfInertia zero =
        0.0 * mp_units::si::unit_symbols::kg * mp_units::pow<2>(mp_units::si::unit_symbols::m);
    static constexpr MomentOfInertia one =
        1.0 * mp_units::si::unit_symbols::kg * mp_units::pow<2>(mp_units::si::unit_symbols::m);

  public:
    constexpr InertiaTensor() :
        _tensor{ { { one, zero, zero }, { zero, one, zero }, { zero, zero, one } } }
    {
    }

    ~InertiaTensor() = default;

    InertiaTensor(
        const MomentOfInertia& Ixx,
        const MomentOfInertia& Ixy,
        const MomentOfInertia& Ixz,
        const MomentOfInertia& Iyx,
        const MomentOfInertia& Iyy,
        const MomentOfInertia& Iyz,
        const MomentOfInertia& Izx,
        const MomentOfInertia& Izy,
        const MomentOfInertia& Izz
    ) :
        _tensor{ { { Ixx, -Ixy, -Ixz }, { -Iyx, Iyy, -Iyz }, { -Izx, -Izy, Izz } } }
    {
    }

    InertiaTensor(const MomentOfInertia& Ixx, const MomentOfInertia& Iyy, const MomentOfInertia& Izz) :
        _tensor{ { { Ixx, zero, zero }, { zero, Iyy, zero }, { zero, zero, Izz } } }
    {
    }

    InertiaTensor(const MomentOfInertia& Iii) :
        _tensor{ { { Iii, zero, zero }, { zero, Iii, zero }, { zero, zero, Iii } } }
    {
    }

    MomentOfInertia& operator[](size_t i, size_t j) { return _tensor[i][j]; }

    const MomentOfInertia& operator[](size_t i, size_t j) const { return _tensor[i][j]; }

    auto determinant() const
    {
        return _tensor[0][0] * (_tensor[1][1] * _tensor[2][2] - _tensor[1][2] * _tensor[2][1]) -
               _tensor[0][1] * (_tensor[1][0] * _tensor[2][2] - _tensor[1][2] * _tensor[2][0]) +
               _tensor[0][2] * (_tensor[1][0] * _tensor[2][1] - _tensor[1][1] * _tensor[2][0]);
    }

    template <typename Value_U>
    CartesianVector<decltype(Value_U{} / MomentOfInertia{}), _frame_>
        inverse_multiply(const CartesianVector<Value_U, _frame_>& vec) const
    {
        // Compute the determinant
        // TODO: Generalize a 3x3 matrix class and use it with the DCM as well
        const auto det = determinant();

        if (is_eq_zero(det)) { throw std::runtime_error("Inertia tensor is singular and cannot be inverted."); }

        // Compute the inverse using the formula for the inverse of a 3x3 matrix
        const auto invDet = 1.0 / det;
        const auto xx     = invDet * (_tensor[1][1] * _tensor[2][2] - _tensor[1][2] * _tensor[2][1]);
        const auto xy     = invDet * (_tensor[0][2] * _tensor[2][1] - _tensor[0][1] * _tensor[2][2]);
        const auto xz     = invDet * (_tensor[0][1] * _tensor[1][2] - _tensor[0][2] * _tensor[1][1]);
        const auto yx     = invDet * (_tensor[1][0] * _tensor[2][2] - _tensor[1][2] * _tensor[2][0]);
        const auto yy     = invDet * (_tensor[0][2] * _tensor[2][0] - _tensor[0][0] * _tensor[2][2]);
        const auto yz     = invDet * (_tensor[0][0] * _tensor[1][1] - _tensor[0][1] * _tensor[1][0]);
        const auto zx     = invDet * (_tensor[1][0] * _tensor[2][1] - _tensor[1][1] * _tensor[2][0]);
        const auto zy     = invDet * (_tensor[0][1] * _tensor[2][0] - _tensor[0][0] * _tensor[2][1]);
        const auto zz     = invDet * (_tensor[0][0] * _tensor[1][1] - _tensor[0][1] * _tensor[1][0]);

        return { xx * vec[0] + xy * vec[1] + xz * vec[2],
                 yx * vec[0] + yy * vec[1] + yz * vec[2],
                 zx * vec[0] + zy * vec[1] + zz * vec[2] };
    }

  private:
    std::array<std::array<MomentOfInertia, 3>, 3> _tensor; 
};

} // namespace astro
} // namespace astrea
```


