

# File CartesianVector.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**framework**](dir_aa3952657448f7008c08b8ed45c303ac.md) **>** [**CartesianVector.hpp**](CartesianVector_8hpp.md)

[Go to the documentation of this file](CartesianVector_8hpp.md)


```C++

#pragma once

#include <array>
#include <typeinfo>

#include <mp-units/framework.h>
#include <mp-units/systems/angular.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/framework/Frame.hpp>
#include <astro/frames/framework/frame_concepts.hpp>

namespace astrea {
namespace astro {

// TODO: Generalize this class further so it can accept copy/move assignment/construction
// from other vectors in the same frame with a compatible unit (Value Type)

// Dedicated trait for CartesianVector since it has a non-type (IsFrame auto) template parameter
// which is not captured by the general is_specialization helper.
template <class T>
struct is_cartesian_vector : std::false_type {};

template <class Value_T, IsFrame auto frame>
struct is_cartesian_vector<CartesianVector<Value_T, frame>> : std::true_type {};

template <class T>
inline constexpr bool is_cartesian_vector_v = is_cartesian_vector<T>::value;

template <class Value_T, IsFrame auto _frame_>
struct CartesianVector {

    static constexpr auto frame = _frame_; 

    inline constexpr CartesianVector(const Value_T& x = Value_T::zero(), const Value_T& y = Value_T::zero(), const Value_T& z = Value_T::zero()) :
        _vector{ x, y, z }
    {
    }

    inline constexpr CartesianVector(const std::array<Value_T, 3>& vec) :
        _vector{ vec[0], vec[1], vec[2] }
    {
    }

    inline constexpr CartesianVector reverse() const { return { _vector[2], _vector[1], _vector[0] }; }

    inline constexpr ~CartesianVector() = default;

    inline constexpr CartesianVector(const CartesianVector&)            = default;
    inline constexpr CartesianVector(CartesianVector&&)                 = default;
    inline constexpr CartesianVector& operator=(const CartesianVector&) = default;
    inline constexpr CartesianVector& operator=(CartesianVector&&)      = default;

    // Equivalent-frame copy/move constructors. Uses plain `auto` (not `IsFrame auto`) to avoid
    // GCC 15 tsubst ICE with constrained auto NTTPs (deduction failure crashes instead of SFINAE).
    // The `requires(equivalent(...))` clause enforces same-origin/axis/parent at the constraint stage.
    template <typename Value_U, auto frame_u>
        requires((std::is_same_v<Value_T, Value_U> || mp_units::interconvertible(Value_T::unit, Value_U::unit)) && equivalent(frame, frame_u))
    inline constexpr CartesianVector(const CartesianVector<Value_U, frame_u>& other) :
        _vector{ other.get_x(), other.get_y(), other.get_z() }
    {
    }

    template <typename Value_U, auto frame_u>
        requires((std::is_same_v<Value_T, Value_U> || mp_units::interconvertible(Value_T::unit, Value_U::unit)) && equivalent(frame, frame_u))
    inline constexpr CartesianVector(CartesianVector<Value_U, frame_u>&& other) :
        _vector{ std::move(other.get_x()), std::move(other.get_y()), std::move(other.get_z()) }
    {
    }

    template <typename Value_U>
        requires(!is_cartesian_vector_v<Value_U> && std::constructible_from<Value_T, Value_U>)
    inline constexpr CartesianVector operator=(const CartesianVector<Value_U, frame>& other) const
    {
        return CartesianVector(other[0], other[1], other[2]);
    }

    template <IsFrame auto frame_u>
    inline constexpr CartesianVector<Value_T, frame_u> force_frame_conversion() const
    {
        return CartesianVector<Value_T, frame_u>(_vector[0], _vector[1], _vector[2]);
    }

    inline constexpr Value_T& operator[](size_t index) { return _vector[index]; }

    inline constexpr const Value_T& operator[](size_t index) const { return _vector[index]; }

    inline constexpr bool operator==(const CartesianVector& other) const
    {
        return _vector[0] == other._vector[0] && _vector[1] == other._vector[1] && _vector[2] == other._vector[2];
    }

    template <class OtherCart>
        requires(is_cartesian_vector_v<OtherCart> && (OtherCart::frame != frame))
    inline constexpr bool operator==(const OtherCart& other) const
    {
        return false;
    }

    inline constexpr CartesianVector operator+(const CartesianVector& other) const
    {
        return CartesianVector(_vector[0] + other.get_x(), _vector[1] + other.get_y(), _vector[2] + other.get_z());
    }

    inline constexpr CartesianVector& operator+=(const CartesianVector& other)
    {
        _vector[0] += other.get_x();
        _vector[1] += other.get_y();
        _vector[2] += other.get_z();
        return *this;
    }

    inline constexpr CartesianVector operator-(const CartesianVector& other) const
    {
        return CartesianVector(_vector[0] - other.get_x(), _vector[1] - other.get_y(), _vector[2] - other.get_z());
    }

    inline constexpr CartesianVector operator-() const
    {
        return CartesianVector(-_vector[0], -_vector[1], -_vector[2]);
    }

    inline constexpr CartesianVector& operator-=(const CartesianVector& other)
    {
        _vector[0] -= other.get_x();
        _vector[1] -= other.get_y();
        _vector[2] -= other.get_z();
        return *this;
    }

    template <typename Value_U>
        requires(!is_cartesian_vector_v<Value_U>)
    inline constexpr CartesianVector<decltype(Value_T{} * Value_U{}), frame> operator*(const Value_U& scalar) const
    {
        return CartesianVector<decltype(Value_T{} * Value_U{}), frame>(_vector[0] * scalar, _vector[1] * scalar, _vector[2] * scalar);
    }

    inline constexpr CartesianVector& operator*=(const Unitless& scalar)
    {
        _vector[0] *= scalar;
        _vector[1] *= scalar;
        _vector[2] *= scalar;
        return *this;
    }

    template <typename Value_U>
        requires(!is_cartesian_vector_v<Value_U>)
    inline constexpr CartesianVector<decltype(Value_T{} / Value_U{}), frame> operator/(const Value_U& scalar) const
    {
        return CartesianVector<decltype(Value_T{} / Value_U{}), frame>(_vector[0] / scalar, _vector[1] / scalar, _vector[2] / scalar);
    }

    inline constexpr CartesianVector& operator/=(const Unitless& scalar)
    {
        _vector[0] /= scalar;
        _vector[1] /= scalar;
        _vector[2] /= scalar;
        return *this;
    }

    inline constexpr Value_T& get_x() { return _vector[0]; }

    inline constexpr const Value_T& get_x() const { return _vector[0]; }

    inline constexpr Value_T& get_y() { return _vector[1]; }

    inline constexpr const Value_T& get_y() const { return _vector[1]; }

    inline constexpr Value_T& get_z() { return _vector[2]; }

    inline constexpr const Value_T& get_z() const { return _vector[2]; }

    template <typename Value_U>
    inline constexpr decltype(Value_T{} * Value_U{}) dot(const CartesianVector<Value_U, frame>& other) const
    {
        return _vector[0] * other.get_x() + _vector[1] * other.get_y() + _vector[2] * other.get_z();
    }

    template <typename Value_U>
    inline constexpr CartesianVector<decltype(Value_T{} * Value_U{}), frame> cross(const CartesianVector<Value_U, frame>& other) const
    {
        return { _vector[1] * other.get_z() - _vector[2] * other.get_y(),
                 _vector[2] * other.get_x() - _vector[0] * other.get_z(),
                 _vector[0] * other.get_y() - _vector[1] * other.get_x() };
    }

    inline constexpr Value_T norm() const
    {
        return sqrt(_vector[0] * _vector[0] + _vector[1] * _vector[1] + _vector[2] * _vector[2]);
    }

    template <unsigned N = 2>
    inline constexpr Value_T p_norm() const
    {
        using namespace mp_units;
        return pow<1, N>(pow<N>(_vector[0]) + pow<N>(_vector[1]) + pow<N>(_vector[2]));
    }

    inline constexpr CartesianVector<Unitless, frame> direction() const
    {
        using namespace mp_units;

        const Value_T n = norm();
        if (is_eq_zero(n)) {
            // Return zero vector if norm is zero
            return CartesianVector<Unitless, frame>(0.0 * mp_units::one, 0.0 * mp_units::one, 0.0 * mp_units::one);
        }
        return CartesianVector<Unitless, frame>(_vector[0] / n, _vector[1] / n, _vector[2] / n);
    }

    template <typename Value_U>
    inline constexpr Angle offset_angle(const CartesianVector<Value_U, frame>& other) const
    {
        using namespace mp_units;
        using namespace mp_units::angular;

        const Value_T v1Mag = norm();
        const Value_U v2Mag = other.norm();

        if (is_eq_zero(v1Mag) || is_eq_zero(v2Mag)) {
            throw std::runtime_error("Cannot calculate angle with zero-magnitude vector");
        }

        const auto v1DotV2 = dot(other);
        const auto ratio   = v1DotV2 / (v1Mag * v2Mag);

        // magic number is 0.5 ULP for floats near 1.0
        if (abs(ratio - 1.0 * one) < 2.107342e-08 * one) { return 0.0 * astrea::detail::angle_unit; }
        return acos(ratio);
    }

    template <IsFrame auto frame_u>
        requires((frame == frame_u))
    inline constexpr CartesianVector<Value_T, frame_u> in_frame(const Date&) const
    {
        return *this;
    }

    template <IsFrame auto frame_u>
        requires((frame == frame_u))
    inline constexpr CartesianVector<Value_T, frame_u> in_frame(const Date&, const CartesianVector<Distance, _frame_>&) const
    {
        return *this;
    }

    template <IsFrame auto frame_u>
        requires((frame == frame_u))
    inline constexpr CartesianVector<Value_T, frame_u>
        in_frame(const Date&, const CartesianVector<Distance, _frame_>&, const CartesianVector<Velocity, _frame_>&) const
    {
        return *this;
    }

    template <IsFrame auto frame_u>
        requires((std::is_same_v<Value_T, Distance> || std::is_same_v<Value_T, Unitless>) && _frame_ != frame_u && IsStaticFrame<decltype(frame_u)>)
    inline constexpr CartesianVector<Value_T, frame_u> in_frame(const Date& date) const;

    template <IsFrame auto frame_u>
        requires(std::is_same_v<Value_T, Velocity> && _frame_ != frame_u && IsStaticFrame<decltype(frame_u)>)
    inline constexpr CartesianVector<Velocity, frame_u>
        in_frame(const Date& date, const CartesianVector<Distance, _frame_>& position) const;

    template <IsFrame auto frame_u>
        requires(std::is_same_v<Value_T, Acceleration> && _frame_ != frame_u && IsStaticFrame<decltype(frame_u)>)
    inline constexpr CartesianVector<Acceleration, frame_u>
        in_frame(const Date& date, const CartesianVector<Distance, _frame_>& position, const CartesianVector<Velocity, _frame_>& velocity) const;

    template <IsFrame auto frame_u, IsFrame auto frame_v>
        requires(frame != frame_u && frame.axis == frame_u.axis && frame.origin != frame_u.origin)
    inline constexpr CartesianVector<Value_T, frame_v> translate(const CartesianVector<Value_T, frame_u>& other) const
    {
        return CartesianVector<Value_T, frame_v>(
            _vector[0] + other.get_x(), _vector[1] + other.get_y(), _vector[2] + other.get_z()
        );
    }

    // TODO: Remove this function and replace it with an OffsetVector class that explicitly represents the offset between
    // two frames, which can then be applied to any vector in the original frame to get a vector in the target frame. This
    // would make it clearer that the operation is applying an offset rather than a general translation, and would allow
    // for more efficient calculations by precomputing the offset vector once and reusing it for multiple vectors.
    template <IsFrame auto frame_u, IsFrame auto frame_v>
        requires(frame != frame_u && frame.axis == frame_u.axis && frame.origin != frame_u.origin)
    inline constexpr CartesianVector<Value_T, frame_v> offset(const CartesianVector<Value_T, frame_u>& other) const
    {
        return CartesianVector<Value_T, frame_v>(
            _vector[0] - other.get_x(), _vector[1] - other.get_y(), _vector[2] - other.get_z()
        );
    }

    std::array<Value_T, 3> _vector; 
};

template <class Value_T, IsFrame auto frame>
std::ostream& operator<<(std::ostream& os, const CartesianVector<Value_T, frame>& state)
{
    os << "[" << state.get_x() << ", " << state.get_y() << ", " << state.get_z() << "]";
    if constexpr (requires { decltype(frame)::name; }) { os << " (" << decltype(frame)::name.portable() << ")"; }
    return os;
}

template <typename Value_T, typename Value_U, IsFrame auto frame>
    requires(!is_cartesian_vector_v<Value_U>)
inline constexpr CartesianVector<decltype(Value_T{} * Value_U{}), frame>
    operator*(const Value_U& scalar, const CartesianVector<Value_T, frame>& vec)
{
    return vec * scalar;
}

template <typename Value_T, typename Value_U, IsFrame auto frame>
    requires(!is_cartesian_vector_v<Value_U>)
inline constexpr CartesianVector<decltype(Value_T{} * Value_U{}), frame>
    operator/(const Value_U& scalar, const CartesianVector<Value_T, frame>& vec)
{
    return vec / scalar;
}

} // namespace astro
} // namespace astrea
```


