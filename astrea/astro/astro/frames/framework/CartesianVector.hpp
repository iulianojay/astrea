/**
 * @file CartesianVector.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the CartesianVector class, which represents a 3D vector in Cartesian coordinates.
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <array>
#include <typeinfo>

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

/**
 * @brief Class representing a 3D vector in Cartesian coordinates.
 *
 * This class encapsulates a vector with three components (x, y, z) and provides various operations
 * such as addition, subtraction, scalar multiplication, and dot/cross products.
 *
 * @tparam T The type of the vector components (e.g., Distance, Velocity).
 */
template <class Value_T, IsFrame auto _frame_>
struct CartesianVector {

    static constexpr auto frame = _frame_; //!< The reference frame of the vector.

    /**
     * @brief Default constructor for CartesianVector.
     *
     * Initializes the vector components to zero.
     * @param x The x component of the vector (default is 0).
     * @param y The y component of the vector (default is 0).
     * @param z The z component of the vector (default is 0).
     */
    inline constexpr CartesianVector(const Value_T& x = Value_T::zero(), const Value_T& y = Value_T::zero(), const Value_T& z = Value_T::zero()) :
        _vector{ x, y, z }
    {
    }

    /**
     * @brief Return the reverse of the vector, which switches the x and z components. This is useful for converting between different rotation sequences.
     */
    inline constexpr CartesianVector reverse() const { return { _vector[2], _vector[1], _vector[0] }; }

    /**
     * @brief Destructor for CartesianVector.
     */
    inline constexpr ~CartesianVector() = default;

    inline constexpr CartesianVector(const CartesianVector&)            = default;
    inline constexpr CartesianVector(CartesianVector&&)                 = default;
    inline constexpr CartesianVector& operator=(const CartesianVector&) = default;
    inline constexpr CartesianVector& operator=(CartesianVector&&)      = default;

    // Equivalent-frame copy/move constructors. Uses plain `auto` (not `IsFrame auto`) to avoid
    // GCC 15 tsubst ICE with constrained auto NTTPs (deduction failure crashes instead of SFINAE).
    // The `requires(equivalent(...))` clause enforces same-origin/axis/parent at the constraint stage.
    template <auto frame_u>
        requires(equivalent(frame, frame_u))
    inline constexpr CartesianVector(const CartesianVector<Value_T, frame_u>& other) :
        _vector{ other.get_x(), other.get_y(), other.get_z() }
    {
    }

    template <auto frame_u>
        requires(equivalent(frame, frame_u))
    inline constexpr CartesianVector(CartesianVector<Value_T, frame_u>&& other) :
        _vector{ std::move(other.get_x()), std::move(other.get_y()), std::move(other.get_z()) }
    {
    }

    /**
     * @brief Copy constructor for CartesianVector that implicitly converts the unit.
     *
     * @return CartesianVector A new CartesianVector with the same components but potentially different unit.
     */
    template <typename Value_U>
        requires(!is_cartesian_vector_v<Value_U> && std::constructible_from<Value_T, Value_U>)
    inline constexpr CartesianVector operator=(const CartesianVector<Value_U, frame>& other) const
    {
        return CartesianVector(other[0], other[1], other[2]);
    }

    /**
     * @brief Copy constructor for CartesianVector that implicitly converts the frame.
     *
     * @param other The other CartesianVector to copy from.
     */
    template <IsFrame auto frame_u>
    inline constexpr CartesianVector<Value_T, frame_u> force_frame_conversion() const
    {
        return CartesianVector<Value_T, frame_u>(_vector[0], _vector[1], _vector[2]);
    }

    /**
     * @brief Access operator for vector components.
     *
     * @param index The index of the component to access (0 for x, 1 for y, 2 for z).
     * @return Value_T& Reference to the component at the specified index.
     */
    inline constexpr Value_T& operator[](size_t index) { return _vector[index]; }

    /**
     * @brief Const access operator for vector components.
     *
     * @param index The index of the component to access (0 for x, 1 for y, 2 for z).
     * @return const Value_T& Reference to the component at the specified index.
     */
    inline constexpr const Value_T& operator[](size_t index) const { return _vector[index]; }

    /**
     * @brief Equality operator for CartesianVector (same type and frame).
     *
     * @param other The other CartesianVector to compare with.
     * @return true If the two vectors are equal.
     * @return false If the two vectors are not equal.
     */
    inline constexpr bool operator==(const CartesianVector& other) const
    {
        return _vector[0] == other._vector[0] && _vector[1] == other._vector[1] && _vector[2] == other._vector[2];
    }

    /**
     * @brief Equality operator for CartesianVector in a different frame or with an incompatible value type. Always returns false.
     *
     * Uses a type-parameter approach to avoid GCC 15's constrained auto NTTP deduction bug
     * (which incorrectly deduces `frame_u = Value_U` for `IsFrame auto frame_u` in both
     * direct and reversed lookup).
     *
     * @param other The other CartesianVector to compare with.
     * @return false Always, since vectors in different frames or with incompatible types cannot be equal.
     */
    template <class OtherCart>
        requires(is_cartesian_vector_v<OtherCart> && (OtherCart::frame != frame))
    inline constexpr bool operator==(const OtherCart& other) const
    {
        return false;
    }

    /**
     * @brief Addition operator for CartesianVector.
     *
     * @param other The other CartesianVector to add.
     * @return CartesianVector A new CartesianVector that is the sum of this vector and the other.
     */
    inline constexpr CartesianVector operator+(const CartesianVector& other) const
    {
        return CartesianVector(_vector[0] + other.get_x(), _vector[1] + other.get_y(), _vector[2] + other.get_z());
    }

    /**
     * @brief Addition assignment operator for CartesianVector.
     *
     * @param other The other CartesianVector to add.
     * @return CartesianVector& Reference to the current object after addition.
     */
    inline constexpr CartesianVector& operator+=(const CartesianVector& other)
    {
        _vector[0] += other.get_x();
        _vector[1] += other.get_y();
        _vector[2] += other.get_z();
        return *this;
    }

    /**
     * @brief Subtraction operator for CartesianVector.
     *
     * @param other The other CartesianVector to subtract.
     * @return CartesianVector A new CartesianVector that is the difference of this vector and the other.
     */
    inline constexpr CartesianVector operator-(const CartesianVector& other) const
    {
        return CartesianVector(_vector[0] - other.get_x(), _vector[1] - other.get_y(), _vector[2] - other.get_z());
    }

    /**
     * @brief Negation operator for CartesianVector.
     *
     * @return CartesianVector<T> A new CartesianVector that is the negation of this vector.
     */
    inline constexpr CartesianVector operator-() const
    {
        return CartesianVector(-_vector[0], -_vector[1], -_vector[2]);
    }

    /**
     * @brief Subtraction assignment operator for CartesianVector.
     *
     * @param other The other CartesianVector to subtract.
     * @return CartesianVector& Reference to the current object after subtraction.
     */
    inline constexpr CartesianVector& operator-=(const CartesianVector& other)
    {
        _vector[0] -= other.get_x();
        _vector[1] -= other.get_y();
        _vector[2] -= other.get_z();
        return *this;
    }

    /**
     * @brief Scalar multiplication operator for CartesianVector.
     *
     * @tparam U The type of the scalar to multiply with.
     * @param scalar The scalar value to multiply with.
     * @return CartesianVector<Value_T * Value_U, frame> A new CartesianVector that is the product of this vector and the scalar.
     */
    template <typename Value_U>
        requires(!is_cartesian_vector_v<Value_U>)
    inline constexpr CartesianVector<decltype(Value_T{} * Value_U{}), frame> operator*(const Value_U& scalar) const
    {
        return CartesianVector<decltype(Value_T{} * Value_U{}), frame>(_vector[0] * scalar, _vector[1] * scalar, _vector[2] * scalar);
    }

    /**
     * @brief Scalar multiplication assignment operator for CartesianVector.
     *
     * @param scalar The scalar value to multiply with.
     * @return CartesianVector& Reference to the current object after multiplication.
     */
    inline constexpr CartesianVector& operator*=(const Unitless& scalar)
    {
        _vector[0] *= scalar;
        _vector[1] *= scalar;
        _vector[2] *= scalar;
        return *this;
    }

    /**
     * @brief Scalar division operator for CartesianVector.
     *
     * @tparam U The type of the scalar to divide by.
     * @param scalar The scalar value to divide by.
     * @return CartesianVector<decltype(Value_T{} / U{})> A new CartesianVector that is the quotient of this vector and the scalar.
     */
    template <typename Value_U>
        requires(!is_cartesian_vector_v<Value_U>)
    inline constexpr CartesianVector<decltype(Value_T{} / Value_U{}), frame> operator/(const Value_U& scalar) const
    {
        return CartesianVector<decltype(Value_T{} / Value_U{}), frame>(_vector[0] / scalar, _vector[1] / scalar, _vector[2] / scalar);
    }

    /**
     * @brief Scalar division assignment operator for CartesianVector.
     *
     * @param scalar The scalar value to divide by.
     * @return CartesianVector& Reference to the current object after division.
     */
    inline constexpr CartesianVector& operator/=(const Unitless& scalar)
    {
        _vector[0] /= scalar;
        _vector[1] /= scalar;
        _vector[2] /= scalar;
        return *this;
    }

    /**
     * @brief Get the x value of the Cartesian vector.
     *
     * @return Value_T& Reference to the x component of the Cartesian vector.
     */
    inline constexpr Value_T& get_x() { return _vector[0]; }

    /**
     * @brief Get the x value of the Cartesian vector.
     *
     * @return const Value_T& Reference to the x component of the Cartesian vector.
     */
    inline constexpr const Value_T& get_x() const { return _vector[0]; }

    /**
     * @brief Get the y value of the Cartesian vector.
     *
     * @return Value_T& Reference to the y component of the Cartesian vector.
     */
    inline constexpr Value_T& get_y() { return _vector[1]; }

    /**
     * @brief Get the y value of the Cartesian vector.
     *
     * @return const Value_T& Reference to the y component of the Cartesian vector.
     */
    inline constexpr const Value_T& get_y() const { return _vector[1]; }

    /**
     * @brief Get the z value of the Cartesian vector.
     *
     * @return Value_T& Reference to the z component of the Cartesian vector.
     */
    inline constexpr Value_T& get_z() { return _vector[2]; }

    /**
     * @brief Get the z value of the Cartesian vector.
     *
     * @return const Value_T& Reference to the z component of the Cartesian vector.
     */
    inline constexpr const Value_T& get_z() const { return _vector[2]; }

    /**
     * @brief Dot product of this vector with another CartesianVector.
     *
     * @tparam U The type of the other CartesianVector.
     * @param other The other CartesianVector to compute the dot product with.
     * @return decltype(Value_T{} * Value_U{}) The result of the dot product.
     */
    template <typename Value_U>
    inline constexpr decltype(Value_T{} * Value_U{}) dot(const CartesianVector<Value_U, frame>& other) const
    {
        return _vector[0] * other.get_x() + _vector[1] * other.get_y() + _vector[2] * other.get_z();
    }

    /**
     * @brief Cross product of this vector with another CartesianVector.
     *
     * @tparam U The type of the other CartesianVector.
     * @param other The other CartesianVector to compute the cross product with.
     * @return CartesianVector<decltype(Value_T{} * Value_U{})> The result of the cross product.
     */
    template <typename Value_U>
    inline constexpr CartesianVector<decltype(Value_T{} * Value_U{}), frame> cross(const CartesianVector<Value_U, frame>& other) const
    {
        return { _vector[1] * other.get_z() - _vector[2] * other.get_y(),
                 _vector[2] * other.get_x() - _vector[0] * other.get_z(),
                 _vector[0] * other.get_y() - _vector[1] * other.get_x() };
    }

    /**
     * @brief Calculate the norm (magnitude) of the vector.
     *
     * @return T The norm of the vector.
     *
     * @note: This can't be called "magnitude" due to an mp-units type resolution bug
     */
    inline constexpr Value_T norm() const
    {
        return sqrt(_vector[0] * _vector[0] + _vector[1] * _vector[1] + _vector[2] * _vector[2]);
    }

    /**
     * @brief Calculate the p-norm of the vector.
     *
     * @tparam N The order of the norm to calculate (default is 2 for Euclidean norm).
     * @return T The p-norm of the vector.
     */
    template <unsigned N = 2>
    inline constexpr Value_T p_norm() const
    {
        using namespace mp_units;
        return pow<1, N>(pow<N>(_vector[0]) + pow<N>(_vector[1]) + pow<N>(_vector[2]));
    }

    /**
     * @brief Normalize the vector to create a unit vector.
     *
     * @return CartesianVector<Unitless> A unit vector in the same direction as this vector.
     * @note If the norm is zero, returns a zero vector.
     */
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

    /**
     * @brief Calculate the angle between this vector and another CartesianVector.
     *
     * @tparam U The type of the other CartesianVector.
     * @param other The other CartesianVector to calculate the angle with.
     * @return Angle The angle between the two vectors.
     * @throws std::runtime_error If either vector has zero magnitude.
     */
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

    /**
     * @brief No-op overload when calling in_frame with the same frame.
     *
     * @tparam frame_u The target frame type to get the vector in.
     * @return CartesianVector<Value_T, frame_u> A new CartesianVector in the target frame.
     * @throws std::runtime_error If the frames do not share the same origin or if the DCM cannot be obtained.
     */
    template <IsFrame auto frame_u>
        requires((frame == frame_u))
    inline constexpr CartesianVector<Value_T, frame_u> in_frame(const Date&) const
    {
        return *this;
    }

    /**
     * @brief Rotate this vector into another frame at a given date.
     *
     * @tparam frame_u The target frame type to rotate into.
     * @param date The date at which to perform the rotation.
     * @return CartesianVector<Value_T, frame_u> A new CartesianVector in the target frame.
     * @throws std::runtime_error If the frames do not share the same origin or if the DCM cannot be obtained.
     */
    template <IsFrame auto frame_u>
        requires(_frame_ != frame_u && IsStaticFrame<decltype(frame_u)>)
    inline constexpr CartesianVector<Value_T, frame_u> in_frame(const Date& date) const;

    /**
     * @brief Translate this vector by another vector in a different frame, resulting in a vector in a third frame.
     *
     * This operation is valid when the two frames share the same axis but have different origins.
     * For example, translating a position vector of the Moon relative to the Earth by the position vector
     * of the Earth relative to the Solar System Barycenter results in the position vector of the Moon
     * relative to the Solar System Barycenter.
     *
     * @tparam frame_u The frame type of the vector to translate by.
     * @tparam frame_v The frame type of the resulting vector.
     * @param other The CartesianVector to translate by.
     * @return CartesianVector<Value_T, frame_v> A new CartesianVector in the resulting frame.
     * @note It is the user's responsibility to ensure that this operation makes sense in the context of the frames involved.
     *      r<frame> + r<frame_u> = r<frame_v>
     *           rEarth<ssb::icrf> + rMoon<earth::icrf> = rMoon<ssb::icrf>
     *           rEarth<ssb::icrf> + rMoon<ssb::icrf> = (rEarth + rMoon)<ssb::icrf>
     *           rEarth<ssb::icrf> + rMoon<jupiter::icrf> = (???)<???>
     *      there's no way to enforce this makes sense at compile time without explicitly knowing where the vectors start
     *      and end, so it has to be left to the user to use it correctly
     */
    template <IsFrame auto frame_u, IsFrame auto frame_v>
        requires(frame != frame_u && frame.axis == frame_u.axis && frame.origin != frame_u.origin)
    inline constexpr CartesianVector<Value_T, frame_v> translate(const CartesianVector<Value_T, frame_u>& other) const
    {
        return CartesianVector<Value_T, frame_v>(
            _vector[0] + other.get_x(), _vector[1] + other.get_y(), _vector[2] + other.get_z()
        );
    }

    /**
     * @brief Calculate the offset vector from another vector in a different frame, resulting in a vector in a third frame.
     *
     * @tparam frame_u The frame type of the vector to calculate the offset from.
     * @tparam frame_v The frame type of the resulting vector.
     * @param other The CartesianVector to calculate the offset from.
     * @return CartesianVector<Value_T, frame_v> A new CartesianVector in the resulting frame.
     * @note It is the user's responsibility to ensure that this operation makes sense in the context of the frames involved.
     */
    template <IsFrame auto frame_u, IsFrame auto frame_v>
        requires(frame != frame_u && frame.axis == frame_u.axis && frame.origin != frame_u.origin)
    inline constexpr CartesianVector<Value_T, frame_v> offset(const CartesianVector<Value_T, frame_u>& other) const
    {
        return CartesianVector<Value_T, frame_v>(
            _vector[0] - other.get_x(), _vector[1] - other.get_y(), _vector[2] - other.get_z()
        );
    }

    std::array<Value_T, 3> _vector; //!< Array to hold the x, y, and z components of the vector.
};

/**
 * @brief Overload the output stream operator for CartesianVector.
 *
 * @tparam Value_T The type of the vector components.
 * @tparam frame The type of the frame.
 * @param os The output stream.
 * @param state The CartesianVector to output.
 * @return The output stream.
 */
template <class Value_T, IsFrame auto frame>
std::ostream& operator<<(std::ostream& os, const CartesianVector<Value_T, frame>& state)
{
    os << "[" << state.get_x() << ", " << state.get_y() << ", " << state.get_z() << "]";
    if constexpr (requires { decltype(frame)::name; }) { os << " (" << decltype(frame)::name.portable() << ")"; }
    return os;
}

/**
 * @brief Scalar multiplication operator for CartesianVector.
 *
 * @tparam T The type of the vector components.
 * @tparam U The type of the scalar to multiply with.
 * @param scalar The scalar value to multiply with.
 * @param vec The CartesianVector to multiply.
 * @return CartesianVector<decltype(Value_T{} * Value_U{}), frame> A new CartesianVector that is the product of the scalar and the vector.
 */
template <typename Value_T, typename Value_U, IsFrame auto frame>
    requires(!is_cartesian_vector_v<Value_U>)
inline constexpr CartesianVector<decltype(Value_T{} * Value_U{}), frame>
    operator*(const Value_U& scalar, const CartesianVector<Value_T, frame>& vec)
{
    return vec * scalar;
}

/**
 * @brief Scalar division operator for CartesianVector.
 *
 * @tparam T The type of the vector components.
 * @tparam U The type of the scalar to divide by.
 * @param scalar The scalar value to divide by.
 * @param vec The CartesianVector to divide.
 * @return CartesianVector<decltype(Value_T{} * Value_U{}), frame> A new CartesianVector that is the quotient of the scalar and the vector.
 */
template <typename Value_T, typename Value_U, IsFrame auto frame>
    requires(!is_cartesian_vector_v<Value_U>)
inline constexpr CartesianVector<decltype(Value_T{} * Value_U{}), frame>
    operator/(const Value_U& scalar, const CartesianVector<Value_T, frame>& vec)
{
    return vec / scalar;
}

} // namespace astro
} // namespace astrea