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
#include <unordered_map>

#include <mp-units/math.h>

#include <units/typedefs.hpp>

#include <astro/element_sets/Frame.hpp>
#include <astro/utilities/conversions.hpp>

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
template <class T>
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
    CartesianVector(const T& x = T(), const T& y = T(), const T& z = T(), const FRAME& frame = FRAME::ECI) :
        _vector{ x, y, z },
        _frame(frame)
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
    CartesianVector(T&& x, T&& y, T&& z, FRAME&& frame) :
        _vector{ std::forward<T>(x), std::forward<T>(y), std::forward<T>(z) },
        _frame(std::forward<FRAME>(frame))
    {
    }

    /**
     * @brief Constructor for CartesianVector from an array.
     *
     * @param vec An array containing the x, y, and z components of the vector.
     */
    CartesianVector(const std::array<T, 3>& vec) :
        _vector(vec)
    {
    }

    /**
     * @brief Constructor for CartesianVector from an rvalue array.
     *
     * @param vec An rvalue array containing the x, y, and z components of the vector.
     */
    CartesianVector(std::array<T, 3>&& vec) :
        _vector(std::move(vec))
    {
    }

    /**
     * @brief Access operator for vector components.
     *
     * @param index The index of the component to access (0 for x, 1 for y, 2 for z).
     * @return T& Reference to the component at the specified index.
     */
    T& operator[](size_t index) { return _vector[index]; }

    /**
     * @brief Const access operator for vector components.
     *
     * @param index The index of the component to access (0 for x, 1 for y, 2 for z).
     * @return const T& Reference to the component at the specified index.
     */
    const T& operator[](size_t index) const { return _vector[index]; }

    /**
     * @brief Equality operator for CartesianVector.
     *
     * @param other The other CartesianVector to compare with.
     * @return true If the two vectors are equal.
     * @return false If the two vectors are not equal.
     */
    bool operator==(const CartesianVector<T>& other) const
    {
        return _vector[0] == other._vector[0] && _vector[1] == other._vector[1] && _vector[2] == other._vector[2];
    }

    /**
     * @brief Addition operator for CartesianVector.
     *
     * @param other The other CartesianVector to add.
     * @return CartesianVector<T> A new CartesianVector that is the sum of this vector and the other.
     */
    CartesianVector<T> operator+(const CartesianVector<T>& other) const
    {
        return CartesianVector(_vector[0] + other.get_x(), _vector[1] + other.get_y(), _vector[2] + other.get_z(), _frame);
    }

    /**
     * @brief Addition assignment operator for CartesianVector.
     *
     * @param other The other CartesianVector to add.
     * @return CartesianVector<T>& Reference to the current object after addition.
     */
    CartesianVector<T>& operator+=(const CartesianVector<T>& other)
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
     * @return CartesianVector<T> A new CartesianVector that is the difference of this vector and the other.
     */
    CartesianVector<T> operator-(const CartesianVector<T>& other) const
    {
        return CartesianVector(_vector[0] - other.get_x(), _vector[1] - other.get_y(), _vector[2] - other.get_z(), _frame);
    }

    /**
     * @brief Negation operator for CartesianVector.
     *
     * @return CartesianVector<T> A new CartesianVector that is the negation of this vector.
     */
    CartesianVector<T> operator-() const { return CartesianVector<T>(-_vector[0], -_vector[1], -_vector[2]); }

    /**
     * @brief Subtraction assignment operator for CartesianVector.
     *
     * @param other The other CartesianVector to subtract.
     * @return CartesianVector<T>& Reference to the current object after subtraction.
     */
    CartesianVector<T>& operator-=(const CartesianVector<T>& other)
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
     * @return CartesianVector<T> A new CartesianVector that is the product of this vector and the scalar.
     */
    template <typename U>
    CartesianVector<decltype(T{} * U{})> operator*(const U& scalar) const
    {
        return CartesianVector<decltype(T{} * U{})>(_vector[0] * scalar, _vector[1] * scalar, _vector[2] * scalar, _frame);
    }

    /**
     * @brief Scalar multiplication assignment operator for CartesianVector.
     *
     * @param scalar The scalar value to multiply with.
     * @return CartesianVector<T>& Reference to the current object after multiplication.
     */
    CartesianVector<T>& operator*=(const Unitless& scalar)
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
     * @return CartesianVector<decltype(T{} / U{})> A new CartesianVector that is the quotient of this vector and the scalar.
     */
    template <typename U>
    CartesianVector<decltype(T{} / U{})> operator/(const U& scalar) const
    {
        return CartesianVector<decltype(T{} / U{})>(_vector[0] / scalar, _vector[1] / scalar, _vector[2] / scalar, _frame);
    }

    /**
     * @brief Scalar division assignment operator for CartesianVector.
     *
     * @param scalar The scalar value to divide by.
     * @return CartesianVector<T>& Reference to the current object after division.
     */
    CartesianVector<T>& operator/=(const Unitless& scalar)
    {
        _vector[0] /= scalar;
        _vector[1] /= scalar;
        _vector[2] /= scalar;
        return *this;
    }

    /**
     * @brief Get the x value of the Cartesian vector.
     *
     * @return T& Reference to the x component of the Cartesian vector.
     */
    T& get_x() { return _vector[0]; }

    /**
     * @brief Get the x value of the Cartesian vector.
     *
     * @return const T& Reference to the x component of the Cartesian vector.
     */
    const T& get_x() const { return _vector[0]; }

    /**
     * @brief Get the y value of the Cartesian vector.
     *
     * @return T& Reference to the y component of the Cartesian vector.
     */
    T& get_y() { return _vector[1]; }

    /**
     * @brief Get the y value of the Cartesian vector.
     *
     * @return const T& Reference to the y component of the Cartesian vector.
     */
    const T& get_y() const { return _vector[1]; }

    /**
     * @brief Get the z value of the Cartesian vector.
     *
     * @return T& Reference to the z component of the Cartesian vector.
     */
    T& get_z() { return _vector[2]; }

    /**
     * @brief Get the z value of the Cartesian vector.
     *
     * @return const T& Reference to the z component of the Cartesian vector.
     */
    const T& get_z() const { return _vector[2]; }

    /**
     * @brief Dot product of this vector with another CartesianVector.
     *
     * @tparam U The type of the other CartesianVector.
     * @param other The other CartesianVector to compute the dot product with.
     * @return decltype(T{} * U{}) The result of the dot product.
     */
    template <typename U>
    decltype(T{} * U{}) dot(const CartesianVector<U>& other) const
    {
        return _vector[0] * other.get_x() + _vector[1] * other.get_y() + _vector[2] * other.get_z();
    }

    /**
     * @brief Cross product of this vector with another CartesianVector.
     *
     * @tparam U The type of the other CartesianVector.
     * @param other The other CartesianVector to compute the cross product with.
     * @return CartesianVector<decltype(T{} * U{})> The result of the cross product.
     */
    template <typename U>
    CartesianVector<decltype(T{} * U{})> cross(const CartesianVector<U>& other) const
    {
        return { _vector[1] * other.get_z() - _vector[2] * other.get_y(),
                 _vector[2] * other.get_x() - _vector[0] * other.get_z(),
                 _vector[0] * other.get_y() - _vector[1] * other.get_x(),
                 _frame };
    }

    /**
     * @brief Calculate the norm (magnitude) of the vector.
     *
     * @return T The norm of the vector.
     */
    T norm() const { return sqrt(_vector[0] * _vector[0] + _vector[1] * _vector[1] + _vector[2] * _vector[2]); }

    /**
     * @brief Normalize the vector to create a unit vector.
     *
     * @return CartesianVector<Unitless> A unit vector in the same direction as this vector.
     * @note If the norm is zero, returns a zero vector.
     */
    CartesianVector<Unitless> unit() const
    {
        const T n = norm();
        if (n.numerical_value_in(n.unit) == 0) {
            // Return zero vector if norm is zero
            return CartesianVector<Unitless>(0.0 * mp_units::one, 0.0 * mp_units::one, 0.0 * mp_units::one, _frame);
        }
        return CartesianVector<Unitless>(_vector[0] / n, _vector[1] / n, _vector[2] / n, _frame);
    }

    /**
     * @brief Get the frame of reference for this vector.
     *
     * @return FRAME The frame of reference for the vector.
     */
    FRAME get_frame() const { return _frame; }

    /**
     * @brief Convert the CartesianVector to a CartesianVector in a specified frame of reference.
     *
     * @param frame The frame of reference to convert to.
     * @return CartesianVector<T> A new CartesianVector in the specified frame.
     */
    template <FRAME frame>
    CartesianVector<T> in(const Date& date) const
    {
        if (frame == _frame) {
            return *this; // No conversion needed
        }

        // God this is dumb
        switch (_frame) {
            case FRAME::ECEF:
                switch (frame) {
                    case FRAME::ECI: return ecef_to_eci(*this, date);
                    default: throw std::runtime_error("Conversion between specified frames is not implemented.");
                }
            case FRAME::ECI:
                switch (frame) {
                    case FRAME::ECEF: return eci_to_ecef(*this, date);
                    default: throw std::runtime_error("Conversion between specified frames is not implemented.");
                }
            default: throw std::runtime_error("Conversion from unknown frame to specified frame is not implemented.");
        }
    }

  private:
    std::array<T, 3> _vector; //<! Array to hold the x, y, and z components of the vector.
    FRAME _frame;             //<! Frame of reference for the vector.
};

/**
 * @brief Scalar multiplication operator for CartesianVector.
 *
 * @tparam T The type of the vector components.
 * @tparam U The type of the scalar to multiply with.
 * @param scalar The scalar value to multiply with.
 * @param vec The CartesianVector to multiply.
 * @return CartesianVector<decltype(T{} * U{})> A new CartesianVector that is the product of the scalar and the vector.
 */
template <typename T, typename U>
CartesianVector<decltype(T{} * U{})> operator*(const U& scalar, const CartesianVector<T>& vec)
{
    return CartesianVector(vec.get_x() * scalar, vec.get_y() * scalar, vec.get_z() * scalar, vec.get_frame());
}

/**
 * @brief Scalar division operator for CartesianVector.
 *
 * @tparam T The type of the vector components.
 * @tparam U The type of the scalar to divide by.
 * @param scalar The scalar value to divide by.
 * @param vec The CartesianVector to divide.
 * @return CartesianVector<decltype(T{} / U{})> A new CartesianVector that is the quotient of the scalar and the vector.
 */
template <typename T, typename U>
CartesianVector<decltype(T{} * U{})> operator/(const U& scalar, const CartesianVector<T>& vec)
{
    return CartesianVector(vec.get_x() / scalar, vec.get_y() / scalar, vec.get_z() / scalar, vec.get_frame());
}

/**
 * @brief Type alias for a vector representing a radius in 3D space.
 */
using RadiusVector = CartesianVector<Distance>;

/**
 * @brief Type alias for a vector representing velocity in 3D space.
 */
using VelocityVector = CartesianVector<Velocity>;

/**
 * @brief Type alias for a vector representing acceleration in 3D space.
 */
using AccelerationVector = CartesianVector<Acceleration>;

/**
 * @brief Type alias for a vector representing unit vectors in 3D space.
 *
 * This is used for direction vectors that do not have units of distance, velocity, or acceleration.
 */
using UnitVector = CartesianVector<Unitless>;

} // namespace astro
} // namespace waveguide
