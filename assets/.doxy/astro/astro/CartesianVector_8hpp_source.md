

# File CartesianVector.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**CartesianVector.hpp**](CartesianVector_8hpp.md)

[Go to the documentation of this file](CartesianVector_8hpp.md)


```C++

#pragma once

#include <array>
#include <typeinfo>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>

#include <units/typedefs.hpp>
#include <utilities/string_util.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/Frame.hpp>
#include <astro/frames/frame_concepts.hpp>
#include <astro/frames/transformations.hpp>

namespace astrea {
namespace astro {

// TODO: Generalize this class further so it can accept copy/move assignment/construction
// from other vectors in the same frame with a compatible unit (Value Type)


template <class T, template <class...> class Template>
struct is_specialization : std::false_type {};

template <template <class...> class Template, class... Args>
struct is_specialization<Template<Args...>, Template> : std::true_type {};

template <class Value_T, class Frame_T>
class CartesianVector {

  public:
    CartesianVector(const Value_T& x = Value_T(), const Value_T& y = Value_T(), const Value_T& z = Value_T()) :
        _vector{ x, y, z }
    {
    }

    // Explicitly deleted copy/move assignment/constructor to prevent implicit frame switches.
    template <typename Frame_U>
    CartesianVector(const CartesianVector<Value_T, Frame_U>& other) = delete;
    template <typename Frame_U>
    CartesianVector(CartesianVector<Value_T, Frame_U>&& other) = delete;
    template <typename Frame_U>
    CartesianVector<Value_T, Frame_T> operator=(const CartesianVector<Value_T, Frame_U>& other) = delete;
    template <typename Frame_U>
    CartesianVector<Value_T, Frame_T> operator=(CartesianVector<Value_T, Frame_U>&& other) = delete;

    template <typename Frame_U>
    CartesianVector<Value_T, Frame_U> force_frame_conversion() const
    {
        return CartesianVector<Value_T, Frame_U>(_vector[0], _vector[1], _vector[2]);
    }

    Value_T& operator[](size_t index) { return _vector[index]; }

    const Value_T& operator[](size_t index) const { return _vector[index]; }

    template <typename Value_U>
    bool operator==(const CartesianVector<Value_U, Frame_T>& other) const
    {
        return _vector[0] == other._vector[0] && _vector[1] == other._vector[1] && _vector[2] == other._vector[2];
    }

    template <typename Frame_U>
        requires(!std::is_same<Frame_T, Frame_U>::value)
    bool operator==(const CartesianVector<Value_T, Frame_U>& other) const
    {
        return false;
    }

    CartesianVector<Value_T, Frame_T> operator+(const CartesianVector<Value_T, Frame_T>& other) const
    {
        return CartesianVector<Value_T, Frame_T>(
            _vector[0] + other.get_x(), _vector[1] + other.get_y(), _vector[2] + other.get_z()
        );
    }

    CartesianVector<Value_T, Frame_T>& operator+=(const CartesianVector<Value_T, Frame_T>& other)
    {
        _vector[0] += other.get_x();
        _vector[1] += other.get_y();
        _vector[2] += other.get_z();
        return *this;
    }

    CartesianVector<Value_T, Frame_T> operator-(const CartesianVector<Value_T, Frame_T>& other) const
    {
        return CartesianVector<Value_T, Frame_T>(
            _vector[0] - other.get_x(), _vector[1] - other.get_y(), _vector[2] - other.get_z()
        );
    }

    CartesianVector<Value_T, Frame_T> operator-() const
    {
        return CartesianVector<Value_T, Frame_T>(-_vector[0], -_vector[1], -_vector[2]);
    }

    CartesianVector<Value_T, Frame_T>& operator-=(const CartesianVector<Value_T, Frame_T>& other)
    {
        _vector[0] -= other.get_x();
        _vector[1] -= other.get_y();
        _vector[2] -= other.get_z();
        return *this;
    }

    template <typename Value_U>
        requires(!is_specialization<Value_U, CartesianVector>::value)
    CartesianVector<decltype(Value_T{} * Value_U{}), Frame_T> operator*(const Value_U& scalar) const
    {
        return CartesianVector<decltype(Value_T{} * Value_U{}), Frame_T>(_vector[0] * scalar, _vector[1] * scalar, _vector[2] * scalar);
    }

    CartesianVector<Value_T, Frame_T>& operator*=(const Unitless& scalar)
    {
        _vector[0] *= scalar;
        _vector[1] *= scalar;
        _vector[2] *= scalar;
        return *this;
    }

    template <typename Value_U>
        requires(!is_specialization<Value_U, CartesianVector>::value)
    CartesianVector<decltype(Value_T{} / Value_U{}), Frame_T> operator/(const Value_U& scalar) const
    {
        return CartesianVector<decltype(Value_T{} / Value_U{}), Frame_T>(_vector[0] / scalar, _vector[1] / scalar, _vector[2] / scalar);
    }

    CartesianVector<Value_T, Frame_T>& operator/=(const Unitless& scalar)
    {
        _vector[0] /= scalar;
        _vector[1] /= scalar;
        _vector[2] /= scalar;
        return *this;
    }

    Value_T& get_x() { return _vector[0]; }

    const Value_T& get_x() const { return _vector[0]; }

    Value_T& get_y() { return _vector[1]; }

    const Value_T& get_y() const { return _vector[1]; }

    Value_T& get_z() { return _vector[2]; }

    const Value_T& get_z() const { return _vector[2]; }

    template <typename Value_U>
    decltype(Value_T{} * Value_U{}) dot(const CartesianVector<Value_U, Frame_T>& other) const
    {
        return _vector[0] * other.get_x() + _vector[1] * other.get_y() + _vector[2] * other.get_z();
    }

    template <typename Value_U>
    CartesianVector<decltype(Value_T{} * Value_U{}), Frame_T> cross(const CartesianVector<Value_U, Frame_T>& other) const
    {
        return { _vector[1] * other.get_z() - _vector[2] * other.get_y(),
                 _vector[2] * other.get_x() - _vector[0] * other.get_z(),
                 _vector[0] * other.get_y() - _vector[1] * other.get_x() };
    }

    Value_T norm() const { return sqrt(_vector[0] * _vector[0] + _vector[1] * _vector[1] + _vector[2] * _vector[2]); }

    CartesianVector<Unitless, Frame_T> unit() const
    {
        const Value_T n = norm();
        if (n.numerical_value_in(n.unit) == 0) {
            // Return zero vector if norm is zero
            return CartesianVector<Unitless, Frame_T>(0.0 * mp_units::one, 0.0 * mp_units::one, 0.0 * mp_units::one);
        }
        return CartesianVector<Unitless, Frame_T>(_vector[0] / n, _vector[1] / n, _vector[2] / n);
    }

    Angle offset_angle(const CartesianVector<Value_T, Frame_T>& other) const
    {
        const Value_T v1Mag = norm();
        const Value_T v2Mag = other.norm();

        if (v1Mag.numerical_value_in(v1Mag.unit) == 0 || v2Mag.numerical_value_in(v2Mag.unit) == 0) {
            throw std::runtime_error("Cannot calculate angle with zero-magnitude vector");
        }

        const auto v1DotV2 = dot(other);
        const auto ratio   = v1DotV2 / (v1Mag * v2Mag);
        if (mp_units::abs(ratio) > 1.0 * mp_units::one) {
            return 0.0 * astrea::detail::angle_unit;
        } // catch rounding errors - TODO: Make this more intelligent
        return mp_units::angular::acos(ratio);
    }

    template <IsStaticFrame Frame_U>
    CartesianVector<Value_T, Frame_U> in_frame(const Date& date) const
    {
        return frames::rotate_vector_into_frame<Value_T, Frame_T, Frame_U>(*this, date);
    }

    // /**
    //  * @brief Transform this vector into another frame at a given date, accounting for both rotation and translation.
    //  *
    //  * @tparam Frame_U The target frame type to transform into.
    //  * @param date The date at which to perform the transformation.
    //  * @return CartesianVector<Value_T, Frame_U> A new CartesianVector in the target frame.
    //  * @throws std::runtime_error If the frames do not have a known transformation or if the DCM cannot be obtained.
    //  */
    // template <typename Frame_U>
    //     requires(IsStaticFrame<Frame_U>)
    // CartesianVector<Value_T, Frame_U> with_respect_to_frame(const Date& date) const
    // {
    //     return frames::transform_vector_into_frame<Value_T, Frame_T, Frame_U>(*this, date);
    // }

    template <typename Frame_U, typename Frame_V>
        requires(!IsSameFrame<Frame_T, Frame_U> && HasSameAxis<Frame_T, Frame_U> && !HasSameOrigin<Frame_T, Frame_U>)
    CartesianVector<Value_T, Frame_V> translate(const CartesianVector<Value_T, Frame_U>& other) const
    {
        return CartesianVector<Value_T, Frame_V>(
            _vector[0] + other.get_x(), _vector[1] + other.get_y(), _vector[2] + other.get_z()
        );
    }

    template <typename Frame_U, typename Frame_V>
        requires(!IsSameFrame<Frame_T, Frame_U> && HasSameAxis<Frame_T, Frame_U> && !HasSameOrigin<Frame_T, Frame_U>)
    CartesianVector<Value_T, Frame_V> offset(const CartesianVector<Value_T, Frame_U>& other) const
    {
        return CartesianVector<Value_T, Frame_V>(
            _vector[0] - other.get_x(), _vector[1] - other.get_y(), _vector[2] - other.get_z()
        );
    }

  private:
    std::array<Value_T, 3> _vector; 
};

template <class Value_T, class Frame_T>
    requires(std::is_constructible<Frame_T>::value)
std::ostream& operator<<(std::ostream& os, const CartesianVector<Value_T, Frame_T>& state)
{
    // static const Frame_T frame;
    os << "[" << state.get_x() << ", " << state.get_y() << ", " << state.get_z() << "]";
    return os;
}

template <class Value_T, class Frame_T>
    requires(!std::is_constructible<Frame_T>::value)
std::ostream& operator<<(std::ostream& os, const CartesianVector<Value_T, Frame_T>& state)
{
    // static const std::string name = utilities::get_type_name<Frame_T>(); // Make this utilities function constexpr
    os << "[" << state.get_x() << ", " << state.get_y() << ", " << state.get_z() << "]";
    return os;
}

template <typename Value_T, typename Value_U, typename Frame_T>
    requires(!is_specialization<Value_U, CartesianVector>::value)
CartesianVector<decltype(Value_T{} * Value_U{}), Frame_T>
    operator*(const Value_U& scalar, const CartesianVector<Value_T, Frame_T>& vec)
{
    return vec * scalar;
}

template <typename Value_T, typename Value_U, typename Frame_T>
    requires(!is_specialization<Value_U, CartesianVector>::value)
CartesianVector<decltype(Value_T{} * Value_U{}), Frame_T>
    operator/(const Value_U& scalar, const CartesianVector<Value_T, Frame_T>& vec)
{
    return vec / scalar;
}

} // namespace astro
} // namespace astrea
```


