

# File DcmInterface.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**framework**](dir_aa3952657448f7008c08b8ed45c303ac.md) **>** [**DcmInterface.hpp**](DcmInterface_8hpp.md)

[Go to the documentation of this file](DcmInterface_8hpp.md)


```C++

#pragma once

#include <array>
#include <cmath>
#include <iostream>

#include <mp-units/math.h>
#include <mp-units/systems/si/math.h>

#include <utilities/string_util.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

// TODO: Make this CRTP to avoid weird casting issues

template <typename Value_T, IsFrame auto _in_frame_, IsFrame auto _out_frame_>
struct DcmInterface {

    template <typename Value_U, IsFrame auto in_frame_u, IsFrame auto out_frame_u>
    friend struct DcmInterface;

    static constexpr auto in_frame  = _in_frame_;  
    static constexpr auto out_frame = _out_frame_; 

    friend std::ostream& operator<<(std::ostream& os, const DcmInterface& matrix)
    {
        for (std::size_t i = 0; i < 3; ++i) {
            os << "| ";
            for (std::size_t j = 0; j < 3; ++j) {
                os << matrix[i, j] << " ";
            }
            os << "|\n";
        }
        return os;
    }

    inline constexpr DcmInterface(const std::array<Value_T, 9>& matrix) :
        _data{ matrix }
    {
    }

    inline constexpr DcmInterface(const std::array<Value_T, 3>& row1, const std::array<Value_T, 3>& row2, const std::array<Value_T, 3>& row3) :
        _data{ row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2] }
    {
    }

    template <typename Value_U, auto in_frame_u, auto out_frame_u>
        requires(requires { Value_T{ Value_U{} }; } && equivalent(in_frame, in_frame_u) && equivalent(out_frame, out_frame_u))
    inline constexpr DcmInterface(const DcmInterface<Value_U, in_frame_u, out_frame_u>& matrix) :
        _data{ matrix._data }
    {
    }

    template <typename Value_U, auto in_frame_u, auto out_frame_u>
        requires(requires { Value_T{ Value_U{} }; } && equivalent(in_frame, in_frame_u) && equivalent(out_frame, out_frame_u))
    inline constexpr DcmInterface(DcmInterface<Value_U, in_frame_u, out_frame_u>&& matrix) :
        _data{ std::move(matrix._data) }
    {
    }

    inline constexpr Value_T& operator[](std::size_t row, std::size_t col) { return _data[row * 3 + col]; }

    inline constexpr const Value_T& operator[](std::size_t row, std::size_t col) const { return _data[row * 3 + col]; }

    template <typename Value_U, auto in_frame_u, auto out_frame_u>
        requires(equivalent(in_frame, in_frame_u) && equivalent(out_frame, out_frame_u))
    inline constexpr DcmInterface operator+(const DcmInterface<Value_U, in_frame_u, out_frame_u>& other) const
    {
        return { { _data[0] + other._data[0],
                   _data[1] + other._data[1],
                   _data[2] + other._data[2],
                   _data[3] + other._data[3],
                   _data[4] + other._data[4],
                   _data[5] + other._data[5],
                   _data[6] + other._data[6],
                   _data[7] + other._data[7],
                   _data[8] + other._data[8] } };
    }

    inline constexpr DcmInterface operator-() const
    {
        return { { -_data[0], -_data[1], -_data[2], -_data[3], -_data[4], -_data[5], -_data[6], -_data[7], -_data[8] } };
    }

    template <typename Value_U, auto in_frame_u, auto out_frame_u>
        requires(equivalent(in_frame, in_frame_u) && equivalent(out_frame, out_frame_u))
    inline constexpr DcmInterface operator-(const DcmInterface<Value_U, in_frame_u, out_frame_u>& other) const
    {
        return *this + (-other);
    }

    template <typename Value_U, auto in_frame_u, auto out_frame_u>
        requires(equivalent(in_frame, in_frame_u) && equivalent(out_frame, out_frame_u))
    inline constexpr DcmInterface<decltype(Value_T{} * Value_U{}), in_frame, out_frame>
        operator*(const DcmInterface<Value_U, in_frame_u, out_frame_u>& other) const
    {
        return _multiply(other.data());
    }

    template <typename Value_U, auto in_frame_u, auto out_frame_u>
        requires(!(equivalent(in_frame, in_frame_u) && equivalent(out_frame, out_frame_u)) && equivalent(out_frame, in_frame_u))
    inline constexpr DcmInterface<decltype(Value_T{} * Value_U{}), in_frame, out_frame_u>
        operator*(const DcmInterface<Value_U, in_frame_u, out_frame_u>& other) const
    {
        return _multiply(other.data());
    }

    template <typename Value_U, auto in_frame_u>
        requires(equivalent(in_frame, in_frame_u))
    inline constexpr CartesianVector<decltype(Value_T{} * Value_U{}), out_frame>
        operator*(const CartesianVector<Value_U, in_frame_u>& vec) const
    {
        return { row(0).dot(vec), row(1).dot(vec), row(2).dot(vec) };
    }

    template <typename Value_U>
        requires(std::is_arithmetic_v<Value_U> || mp_units::Quantity<Value_U>)
    inline constexpr DcmInterface<decltype(Value_T{} * Value_U{}), in_frame, out_frame> operator*(const Value_U& scalar) const
    {
        return { { _data[0] * scalar, _data[1] * scalar, _data[2] * scalar },
                 { _data[3] * scalar, _data[4] * scalar, _data[5] * scalar },
                 { _data[6] * scalar, _data[7] * scalar, _data[8] * scalar } };
    }

    inline constexpr CartesianVector<Value_T, _in_frame_> row(const std::size_t& idx) const
    {
        return { _data[idx * 3 + 0], _data[idx * 3 + 1], _data[idx * 3 + 2] };
    }

    inline constexpr DcmInterface<Value_T, _out_frame_, _in_frame_> transpose() const
    {
        return { { _data[0], _data[3], _data[6] }, { _data[1], _data[4], _data[7] }, { _data[2], _data[5], _data[8] } };
    }

    inline constexpr Value_T trace() const { return _data[0] + _data[4] + _data[8]; }

    inline constexpr Value_T determinant() const
    {
        return _data[0] * (_data[4] * _data[8] - _data[5] * _data[7]) -
               _data[1] * (_data[3] * _data[8] - _data[5] * _data[6]) + _data[2] * (_data[3] * _data[7] - _data[4] * _data[6]);
    }

    inline constexpr void normalize()
    {
        using namespace mp_units;

        const Unitless det = determinant().in(one);
        if (det == 0.0) {
            throw std::runtime_error("Cannot normalize a zero-value determinant matrix. The matrix is likely singular.");
        }

        // For 3x3 matrices, determinant scales as k^3 where k is the scaling factor
        // Use linear approximation when determinant is close to 1: k ≈ 1 - (det-1)/3
        // https://stackoverflow.com/questions/11667783/quaternion-and-normalization
        if (abs(1.0 * one - det) < 2.107342e-08 * one) { _normalize(1.0 * one - (det - 1.0 * one) / 3.0); }
        else {
            // Exact formula: k = (1/det)^(1/3) to make k^3 * det = 1
            _normalize(1.0 * one / cbrt(det));
        }
    }

    inline constexpr std::array<Value_T, 9> data() const { return _data; }

  protected:
    std::array<Value_T, 9> _data; 

    inline constexpr void _normalize(const Unitless& scale)
    {
        using namespace mp_units;

        for (auto& element : _data) {
            element *= scale;
            // Avoid very small values that should be zero
            if (mp_units::abs(element) < 1.0e-15 * one) { element = 0.0 * one; }
        }
    }

    // Helper function for matrix multiplication
    template <typename Value_U>
    std::array<decltype(Value_T{} * Value_U{}), 9> _multiply(const std::array<Value_U, 9>& other) const
    {
        // lmao whatever
        return { _data[0] * other[0] + _data[1] * other[3] + _data[2] * other[6],
                 _data[0] * other[1] + _data[1] * other[4] + _data[2] * other[7],
                 _data[0] * other[2] + _data[1] * other[5] + _data[2] * other[8],
                 _data[3] * other[0] + _data[4] * other[3] + _data[5] * other[6],
                 _data[3] * other[1] + _data[4] * other[4] + _data[5] * other[7],
                 _data[3] * other[2] + _data[4] * other[5] + _data[5] * other[8],
                 _data[6] * other[0] + _data[7] * other[3] + _data[8] * other[6],
                 _data[6] * other[1] + _data[7] * other[4] + _data[8] * other[7],
                 _data[6] * other[2] + _data[7] * other[5] + _data[8] * other[8] };
    }

    static inline constexpr DcmInterface identity()
    {
        static constexpr auto one = 1.0 * Value_T::unit;
        return { { one, Value_T::zero(), Value_T::zero() },
                 { Value_T::zero(), one, Value_T::zero() },
                 { Value_T::zero(), Value_T::zero(), one } };
    }

    static inline constexpr DcmInterface zero()
    {
        return { { Value_T::zero(), Value_T::zero(), Value_T::zero() },
                 { Value_T::zero(), Value_T::zero(), Value_T::zero() },
                 { Value_T::zero(), Value_T::zero(), Value_T::zero() } };
    }
};


template <typename Value_T, typename Value_U, IsFrame auto in_frame, IsFrame auto out_frame>
    requires(std::is_arithmetic_v<Value_U> || mp_units::Quantity<Value_U>)
inline constexpr DcmInterface<decltype(Value_T{} * Value_U{}), in_frame, out_frame>
    operator*(const Value_T& scalar, const DcmInterface<Value_U, in_frame, out_frame>& matrix)
{
    return matrix * scalar;
}


} // namespace astro
} // namespace astrea
```


