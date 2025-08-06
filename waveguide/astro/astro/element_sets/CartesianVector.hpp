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

#include <units/typedefs.hpp>

#include <astro/astro.fwd.hpp>

namespace waveguide {
namespace astro {

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

    /**
     * @brief Constructor for CartesianVector with rvalue references.
     *
     * Initializes the vector components with rvalue references for efficiency.
     * @param x The x component of the vector.
     * @param y The y component of the vector.
     * @param z The z component of the vector.
     * @param frame The frame of reference for the vector.
     */
    CartesianVector(Value_T&& x, Value_T&& y, Value_T&& z) :
        _vector{ std::forward<Value_T>(x), std::forward<Value_T>(y), std::forward<Value_T>(z) }
    {
    }

    /**
     * @brief Constructor for CartesianVector from an array.
     *
     * @param vec An array containing the x, y, and z components of the vector.
     */
    CartesianVector(const std::array<Value_T, 3>& vec) :
        _vector(vec)
    {
    }

    /**
     * @brief Constructor for CartesianVector from an rvalue array.
     *
     * @param vec An rvalue array containing the x, y, and z components of the vector.
     */
    CartesianVector(std::array<Value_T, 3>&& vec) :
        _vector(std::move(vec))
    {
    }

    /**
     * @brief Explicitly deleted copy constructor to prevent implicit frame switches.
     *
     * @tparam Frame_U The frame type of the other CartesianVector.
     * @param other The other CartesianVector to copy from.
     * @return CartesianVector <Value_T, Frame_T> A new CartesianVector that is a copy of the other.
     */
    template <typename Frame_U>
    CartesianVector(const CartesianVector<Value_T, Frame_U>& other) = delete;

    /**
     * @brief Explicitly deleted copy assignment constructor to prevent implicit frame switches.
     *
     * @tparam Frame_U The frame type of the other CartesianVector.
     * @param other The other CartesianVector to copy from.
     * @return CartesianVector <Value_T, Frame_T> A new CartesianVector that is a copy of the other.
     */
    template <typename Frame_U>
    CartesianVector<Value_T, Frame_U> operator=(const CartesianVector<Value_T, Frame_T>& other) = delete;

    /**
     * @brief Explicitly deleted copy assignment constructor to prevent implicit frame switches.
     *
     * @tparam Frame_U The frame type of the other CartesianVector.
     * @param other The other CartesianVector to copy from.
     * @return CartesianVector <Value_T, Frame_T> A new CartesianVector that is a copy of the other.
     */
    template <typename Frame_U>
    CartesianVector<Value_T, Frame_T> operator=(const CartesianVector<Value_T, Frame_U>& other) = delete;

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
    bool operator==(const CartesianVector<Value_T, Frame_T>& other) const
    {
        return _vector[0] == other._vector[0] && _vector[1] == other._vector[1] && _vector[2] == other._vector[2];
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
     * @brief Convert the CartesianVector to a CartesianVector in a specified frame of reference.
     *
     * @param frame The frame of reference to convert to.
     * @return CartesianVector<T> A new CartesianVector in the specified frame.
     */
    template <typename Frame_U>
    CartesianVector<Value_T, Frame_U> in(const Date& date) const
    {
        return Frame_U::convert_to(*this, date);
    }

  private:
    std::array<Value_T, 3> _vector; //<! Array to hold the x, y, and z components of the vector.
};

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
using RadiusVector = CartesianVector<Distance, EarthCenteredInertial>;

/**
 * @brief Type alias for a vector representing velocity in 3D space.
 */
using VelocityVector = CartesianVector<Velocity, EarthCenteredInertial>;

/**
 * @brief Type alias for a vector representing acceleration in 3D space.
 */
using AccelerationVector = CartesianVector<Acceleration, EarthCenteredInertial>;

/**
 * @brief Type alias for a vector representing unit vectors in 3D space.
 *
 * This is used for direction vectors that do not have units of distance, velocity, or acceleration.
 */
using UnitVector = CartesianVector<Unitless, EarthCenteredInertial>;

} // namespace astro
} // namespace waveguide
