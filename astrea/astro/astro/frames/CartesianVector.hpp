/**
 * @file CartesianVector.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the CartesianVector class, which represents a 3D vector in Cartesian coordinates.
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <array>
#include <typeinfo>

#include <mp-units/math.h>
#include <mp-units/ostream.h>
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

/**
 * @brief Class representing a 3D vector in Cartesian coordinates.
 *
 * This class encapsulates a vector with three components (x, y, z) and provides various operations
 * such as addition, subtraction, scalar multiplication, and dot/cross products.
 *
 * @tparam T The type of the vector components (e.g., Distance, Velocity).
 */
template <class Value_T, class Frame_T>
class CartesianVector {

    template <class Value_U, class Frame_U>
    friend std::ostream& operator<<(std::ostream& os, const CartesianVector<Value_U, Frame_U>& state);

  public:
    /**
     * @brief Default constructor for CartesianVector.
     *
     * Initializes the vector components to zero.
     * @param x The x component of the vector (default is 0).
     * @param y The y component of the vector (default is 0).
     * @param z The z component of the vector (default is 0).
     */
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

    /**
     * @brief Copy constructor for CartesianVector that implicitly converts the frame.
     *
     * @param other The other CartesianVector to copy from.
     */
    template <typename Frame_U>
    CartesianVector<Value_T, Frame_U> force_frame_conversion() const
    {
        return CartesianVector<Value_T, Frame_U>(_vector[0], _vector[1], _vector[2]);
    }

    /**
     * @brief Access operator for vector components.
     *
     * @param index The index of the component to access (0 for x, 1 for y, 2 for z).
     * @return Value_T& Reference to the component at the specified index.
     */
    Value_T& operator[](size_t index) { return _vector[index]; }

    /**
     * @brief Const access operator for vector components.
     *
     * @param index The index of the component to access (0 for x, 1 for y, 2 for z).
     * @return const Value_T& Reference to the component at the specified index.
     */
    const Value_T& operator[](size_t index) const { return _vector[index]; }

    /**
     * @brief Equality operator for CartesianVector.
     *
     * @param other The other CartesianVector to compare with.
     * @return true If the two vectors are equal.
     * @return false If the two vectors are not equal.
     */
    template <typename Value_U>
    bool operator==(const CartesianVector<Value_U, Frame_T>& other) const
    {
        return _vector[0] == other._vector[0] && _vector[1] == other._vector[1] && _vector[2] == other._vector[2];
    }

    /**
     * @brief Inequality operator for CartesianVector in a different frame. Always false.
     *
     * @param other The other CartesianVector to compare with.
     * @return true If the two vectors are not equal.
     * @return false If the two vectors are equal.
     */
    template <typename Frame_U>
        requires(!std::is_same<Frame_T, Frame_U>::value)
    bool operator==(const CartesianVector<Value_T, Frame_U>& other) const
    {
        return false;
    }

    /**
     * @brief Addition operator for CartesianVector.
     *
     * @param other The other CartesianVector to add.
     * @return CartesianVector<Value_T, Frame_T> A new CartesianVector that is the sum of this vector and the other.
     */
    CartesianVector<Value_T, Frame_T> operator+(const CartesianVector<Value_T, Frame_T>& other) const
    {
        return CartesianVector<Value_T, Frame_T>(
            _vector[0] + other.get_x(), _vector[1] + other.get_y(), _vector[2] + other.get_z()
        );
    }

    /**
     * @brief Addition assignment operator for CartesianVector.
     *
     * @param other The other CartesianVector to add.
     * @return CartesianVector<Value_T, Frame_T>& Reference to the current object after addition.
     */
    CartesianVector<Value_T, Frame_T>& operator+=(const CartesianVector<Value_T, Frame_T>& other)
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
     * @return CartesianVector<Value_T, Frame_T> A new CartesianVector that is the difference of this vector and the other.
     */
    CartesianVector<Value_T, Frame_T> operator-(const CartesianVector<Value_T, Frame_T>& other) const
    {
        return CartesianVector<Value_T, Frame_T>(
            _vector[0] - other.get_x(), _vector[1] - other.get_y(), _vector[2] - other.get_z()
        );
    }

    /**
     * @brief Negation operator for CartesianVector.
     *
     * @return CartesianVector<T> A new CartesianVector that is the negation of this vector.
     */
    CartesianVector<Value_T, Frame_T> operator-() const
    {
        return CartesianVector<Value_T, Frame_T>(-_vector[0], -_vector[1], -_vector[2]);
    }

    /**
     * @brief Subtraction assignment operator for CartesianVector.
     *
     * @param other The other CartesianVector to subtract.
     * @return CartesianVector<Value_T, Frame_T>& Reference to the current object after subtraction.
     */
    CartesianVector<Value_T, Frame_T>& operator-=(const CartesianVector<Value_T, Frame_T>& other)
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
     * @return CartesianVector<Value_T * Value_U, Frame_T> A new CartesianVector that is the product of this vector and the scalar.
     */
    template <typename Value_U>
    CartesianVector<decltype(Value_T{} * Value_U{}), Frame_T> operator*(const Value_U& scalar) const
    {
        return CartesianVector<decltype(Value_T{} * Value_U{}), Frame_T>(_vector[0] * scalar, _vector[1] * scalar, _vector[2] * scalar);
    }

    /**
     * @brief Scalar multiplication assignment operator for CartesianVector.
     *
     * @param scalar The scalar value to multiply with.
     * @return CartesianVector<Value_T, Frame_T>& Reference to the current object after multiplication.
     */
    CartesianVector<Value_T, Frame_T>& operator*=(const Unitless& scalar)
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
    CartesianVector<decltype(Value_T{} / Value_U{}), Frame_T> operator/(const Value_U& scalar) const
    {
        return CartesianVector<decltype(Value_T{} / Value_U{}), Frame_T>(_vector[0] / scalar, _vector[1] / scalar, _vector[2] / scalar);
    }

    /**
     * @brief Scalar division assignment operator for CartesianVector.
     *
     * @param scalar The scalar value to divide by.
     * @return CartesianVector<Value_T, Frame_T>& Reference to the current object after division.
     */
    CartesianVector<Value_T, Frame_T>& operator/=(const Unitless& scalar)
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
    Value_T& get_x() { return _vector[0]; }

    /**
     * @brief Get the x value of the Cartesian vector.
     *
     * @return const Value_T& Reference to the x component of the Cartesian vector.
     */
    const Value_T& get_x() const { return _vector[0]; }

    /**
     * @brief Get the y value of the Cartesian vector.
     *
     * @return Value_T& Reference to the y component of the Cartesian vector.
     */
    Value_T& get_y() { return _vector[1]; }

    /**
     * @brief Get the y value of the Cartesian vector.
     *
     * @return const Value_T& Reference to the y component of the Cartesian vector.
     */
    const Value_T& get_y() const { return _vector[1]; }

    /**
     * @brief Get the z value of the Cartesian vector.
     *
     * @return Value_T& Reference to the z component of the Cartesian vector.
     */
    Value_T& get_z() { return _vector[2]; }

    /**
     * @brief Get the z value of the Cartesian vector.
     *
     * @return const Value_T& Reference to the z component of the Cartesian vector.
     */
    const Value_T& get_z() const { return _vector[2]; }

    /**
     * @brief Dot product of this vector with another CartesianVector.
     *
     * @tparam U The type of the other CartesianVector.
     * @param other The other CartesianVector to compute the dot product with.
     * @return decltype(Value_T{} * Value_U{}) The result of the dot product.
     */
    template <typename Value_U>
    decltype(Value_T{} * Value_U{}) dot(const CartesianVector<Value_U, Frame_T>& other) const
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
    CartesianVector<decltype(Value_T{} * Value_U{}), Frame_T> cross(const CartesianVector<Value_U, Frame_T>& other) const
    {
        return { _vector[1] * other.get_z() - _vector[2] * other.get_y(),
                 _vector[2] * other.get_x() - _vector[0] * other.get_z(),
                 _vector[0] * other.get_y() - _vector[1] * other.get_x() };
    }

    /**
     * @brief Calculate the norm (magnitude) of the vector.
     *
     * @return T The norm of the vector.
     */
    Value_T norm() const { return sqrt(_vector[0] * _vector[0] + _vector[1] * _vector[1] + _vector[2] * _vector[2]); }

    /**
     * @brief Normalize the vector to create a unit vector.
     *
     * @return CartesianVector<Unitless> A unit vector in the same direction as this vector.
     * @note If the norm is zero, returns a zero vector.
     */
    CartesianVector<Unitless, Frame_T> unit() const
    {
        const Value_T n = norm();
        if (n.numerical_value_in(n.unit) == 0) {
            // Return zero vector if norm is zero
            return CartesianVector<Unitless, Frame_T>(0.0 * mp_units::one, 0.0 * mp_units::one, 0.0 * mp_units::one);
        }
        return CartesianVector<Unitless, Frame_T>(_vector[0] / n, _vector[1] / n, _vector[2] / n);
    }

    /**
     * @brief Calculate the angle between this vector and another CartesianVector.
     *
     * @param other The other CartesianVector to calculate the angle with.
     * @return Angle The angle between the two vectors.
     * @throws std::runtime_error If either vector has zero magnitude.
     */
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
            return 0.0 * mp_units::angular::unit_symbols::rad;
        } // catch rounding errors - TODO: Make this more intelligent
        return mp_units::angular::acos(ratio);
    }

    /**
     * @brief Rotate this vector into another frame at a given date.
     *
     * @tparam Frame_U The target frame type to rotate into.
     * @param date The date at which to perform the rotation.
     * @return CartesianVector<Value_T, Frame_U> A new CartesianVector in the target frame.
     * @throws std::runtime_error If the frames do not share the same origin or if the DCM cannot be obtained.
     */
    template <IsStaticFrame Frame_U>
    CartesianVector<Value_T, Frame_U> in_frame(const Date& date) const
    {
        return frames::rotate_vector_into_frame<Value_T, Frame_T, Frame_U>(*this, date);
    }

    /**
     * @brief Transform this vector into another frame at a given date, accounting for both rotation and translation.
     *
     * @tparam Frame_U The target frame type to transform into.
     * @param date The date at which to perform the transformation.
     * @return CartesianVector<Value_T, Frame_U> A new CartesianVector in the target frame.
     * @throws std::runtime_error If the frames do not have a known transformation or if the DCM cannot be obtained.
     */
    template <IsStaticFrame Frame_U>
    CartesianVector<Value_T, Frame_U> with_respect_to_frame(const Date& date) const
    {
        return frames::transform_vector_into_frame<Value_T, Frame_T, Frame_U>(*this, date);
    }

    /**
     * @brief Translate this vector by another vector in a different frame, resulting in a vector in a third frame.
     *
     * This operation is valid when the two frames share the same axis but have different origins.
     * For example, translating a position vector of the Moon relative to the Earth by the position vector
     * of the Earth relative to the Solar System Barycenter results in the position vector of the Moon
     * relative to the Solar System Barycenter.
     *
     * @tparam Frame_U The frame type of the vector to translate by.
     * @tparam Frame_V The frame type of the resulting vector.
     * @param other The CartesianVector to translate by.
     * @return CartesianVector<Value_T, Frame_V> A new CartesianVector in the resulting frame.
     * @note It is the user's responsibility to ensure that this operation makes sense in the context of the frames involved.
     *      r<Frame_T> + r<Frame_U> = r<Frame_V>
     *           rEarth<ssb::icrf> + rMoon<earth::icrf> = rMoon<ssb::icrf>
     *           rEarth<ssb::icrf> + rMoon<ssb::icrf> = (rEarth + rMoon)<ssb::icrf>
     *           rEarth<ssb::icrf> + rMoon<jupiter::icrf> = (???)<???>
     *      there's no way to enforce this makes sense at compile time without explicitly knowing where the vectors start
     *      and end, so it has to be left to the user to use it correctly
     */
    template <typename Frame_U, typename Frame_V>
        requires(!IsSameFrame<Frame_T, Frame_U> && HasSameAxis<Frame_T, Frame_U> && !HasSameOrigin<Frame_T, Frame_U>)
    CartesianVector<Value_T, Frame_V> translate(const CartesianVector<Value_T, Frame_U>& other) const
    {
        return CartesianVector<Value_T, Frame_V>(
            _vector[0] + other.get_x(), _vector[1] + other.get_y(), _vector[2] + other.get_z()
        );
    }

    /**
     * @brief Calculate the offset vector from another vector in a different frame, resulting in a vector in a third frame.
     *
     * @tparam Frame_U The frame type of the vector to calculate the offset from.
     * @tparam Frame_V The frame type of the resulting vector.
     * @param other The CartesianVector to calculate the offset from.
     * @return CartesianVector<Value_T, Frame_V> A new CartesianVector in the resulting frame.
     * @note It is the user's responsibility to ensure that this operation makes sense in the context of the frames involved.
     */
    template <typename Frame_U, typename Frame_V>
        requires(!IsSameFrame<Frame_T, Frame_U> && HasSameAxis<Frame_T, Frame_U> && !HasSameOrigin<Frame_T, Frame_U>)
    CartesianVector<Value_T, Frame_V> offset(const CartesianVector<Value_T, Frame_U>& other) const
    {
        return CartesianVector<Value_T, Frame_V>(
            _vector[0] - other.get_x(), _vector[1] - other.get_y(), _vector[2] - other.get_z()
        );
    }

  private:
    std::array<Value_T, 3> _vector; //!< Array to hold the x, y, and z components of the vector.
};

/**
 * @brief Overload the output stream operator for CartesianVector.
 *
 * @tparam Value_T The type of the vector components.
 * @tparam Frame_T The type of the frame.
 * @param os The output stream.
 * @param state The CartesianVector to output.
 * @return The output stream.
 */
template <class Value_T, class Frame_T>
    requires(std::is_constructible<Frame_T>::value)
std::ostream& operator<<(std::ostream& os, const CartesianVector<Value_T, Frame_T>& state)
{
    // static const Frame_T frame;
    os << "[" << state.get_x() << ", " << state.get_y() << ", " << state.get_z() << "]";
    return os;
}

/**
 * @brief Overload the output stream operator for CartesianVector.
 *
 * @tparam Value_T The type of the vector components.
 * @tparam Frame_T The type of the frame.
 * @param os The output stream.
 * @param state The CartesianVector to output.
 * @return The output stream.
 */
template <class Value_T, class Frame_T>
    requires(!std::is_constructible<Frame_T>::value)
std::ostream& operator<<(std::ostream& os, const CartesianVector<Value_T, Frame_T>& state)
{
    // static const std::string name = utilities::get_type_name<Frame_T>(); // Make this utilities function constexpr
    os << "[" << state.get_x() << ", " << state.get_y() << ", " << state.get_z() << "]";
    return os;
}

/**
 * @brief Scalar multiplication operator for CartesianVector.
 *
 * @tparam T The type of the vector components.
 * @tparam U The type of the scalar to multiply with.
 * @param scalar The scalar value to multiply with.
 * @param vec The CartesianVector to multiply.
 * @return CartesianVector<decltype(Value_T{} * Value_U{}), Frame_T> A new CartesianVector that is the product of the scalar and the vector.
 */
template <typename Value_T, typename Value_U, typename Frame_T>
CartesianVector<decltype(Value_T{} * Value_U{}), Frame_T>
    operator*(const Value_U& scalar, const CartesianVector<Value_T, Frame_T>& vec)
{
    return CartesianVector<decltype(Value_T{} * Value_U{}), Frame_T>(vec.get_x() * scalar, vec.get_y() * scalar, vec.get_z() * scalar);
}

/**
 * @brief Scalar division operator for CartesianVector.
 *
 * @tparam T The type of the vector components.
 * @tparam U The type of the scalar to divide by.
 * @param scalar The scalar value to divide by.
 * @param vec The CartesianVector to divide.
 * @return CartesianVector<decltype(Value_T{} * Value_U{}), Frame_T> A new CartesianVector that is the quotient of the scalar and the vector.
 */
template <typename Value_T, typename Value_U, typename Frame_T>
CartesianVector<decltype(Value_T{} * Value_U{}), Frame_T>
    operator/(const Value_U& scalar, const CartesianVector<Value_T, Frame_T>& vec)
{
    return CartesianVector<decltype(Value_T{} * Value_U{}), Frame_T>(vec.get_x() / scalar, vec.get_y() / scalar, vec.get_z() / scalar);
}

/**
 * @brief Type alias for a vector representing a radius in 3D space.
 */
template <typename Frame_T>
using RadiusVector = CartesianVector<Distance, Frame_T>;

/**
 * @brief Type alias for a vector representing velocity in 3D space.
 */
template <typename Frame_T>
using VelocityVector = CartesianVector<Velocity, Frame_T>;

/**
 * @brief Type alias for a vector representing acceleration in 3D space.
 */
template <typename Frame_T>
using AccelerationVector = CartesianVector<Acceleration, Frame_T>;

/**
 * @brief Type alias for a vector representing unit vectors in 3D space.
 *
 * This is used for direction vectors that do not have units of distance, velocity, or acceleration.
 */
template <typename Frame_T>
using UnitVector = CartesianVector<Unitless, Frame_T>;

} // namespace astro
} // namespace astrea
