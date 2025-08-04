#pragma once

#include <array>

#include <mp-units/math.h>

#include <units/typedefs.hpp>

namespace waveguide {

template <class T>
class CartesianVector {
  public:
    CartesianVector(const T& x = T(), const T& y = T(), const T& z = T()) :
        _vector{ x, y, z }
    {
    }
    CartesianVector(const std::array<T, 3>& vec) :
        _vector(vec)
    {
    }

    T& operator[](size_t index) { return _vector[index]; }
    const T& operator[](size_t index) const { return _vector[index]; }

    CartesianVector<T> operator+(const CartesianVector<T>& other) const
    {
        return CartesianVector(_vector[0] + other.get_x(), _vector[1] + other.get_y(), _vector[2] + other.get_z());
    }

    CartesianVector<T>& operator+=(const CartesianVector<T>& other)
    {
        _vector[0] += other.get_x();
        _vector[1] += other.get_y();
        _vector[2] += other.get_z();
        return *this;
    }

    CartesianVector<T> operator-(const CartesianVector<T>& other) const
    {
        return CartesianVector(_vector[0] - other.get_x(), _vector[1] - other.get_y(), _vector[2] - other.get_z());
    }

    CartesianVector<T>& operator-=(const CartesianVector<T>& other)
    {
        _vector[0] -= other.get_x();
        _vector[1] -= other.get_y();
        _vector[2] -= other.get_z();
        return *this;
    }

    template <typename U>
    CartesianVector<decltype(T{} * U{})> operator*(const U& scalar) const
    {
        return CartesianVector(_vector[0] * scalar, _vector[1] * scalar, _vector[2] * scalar);
    }

    CartesianVector<T>& operator*=(const Unitless& scalar)
    {
        _vector[0] *= scalar;
        _vector[1] *= scalar;
        _vector[2] *= scalar;
        return *this;
    }

    template <typename U>
    CartesianVector<decltype(T{} / U{})> operator/(const U& scalar) const
    {
        return CartesianVector(_vector[0] / scalar, _vector[1] / scalar, _vector[2] / scalar);
    }

    CartesianVector<T>& operator/=(const Unitless& scalar)
    {
        _vector[0] /= scalar;
        _vector[1] /= scalar;
        _vector[2] /= scalar;
        return *this;
    }

    T& get_x() { return _vector[0]; }
    const T& get_x() const { return _vector[0]; }

    T& get_y() { return _vector[1]; }
    const T& get_y() const { return _vector[1]; }

    T& get_z() { return _vector[2]; }
    const T& get_z() const { return _vector[2]; }

    template <typename U>
    decltype(T{} * U{}) dot(const CartesianVector<U>& other) const
    {
        return _vector[0] * other.get_x() + _vector[1] * other.get_y() + _vector[2] * other.get_z();
    }

    template <typename U>
    CartesianVector<decltype(T{} * U{})> cross(const CartesianVector<U>& other) const
    {
        return {
            _vector[1] * other.get_z() - _vector[2] * other.get_y(),
            _vector[2] * other.get_x() - _vector[0] * other.get_z(),
            _vector[0] * other.get_y() - _vector[1] * other.get_x()
        };
    }

    T norm() const { return sqrt(_vector[0] * _vector[0] + _vector[1] * _vector[1] + _vector[2] * _vector[2]); }

    CartesianVector<Unitless> unit() const
    {
        const T n = norm();
        if (n.numerical_value_in(n.unit) == 0) {
            // Return zero vector if norm is zero
            return CartesianVector<Unitless>(0.0 * mp_units::one, 0.0 * mp_units::one, 0.0 * mp_units::one); 
        }
        return CartesianVector<Unitless>(_vector[0] / n, _vector[1] / n, _vector[2] / n);
    }

  private:
    std::array<T, 3> _vector;
};

using RadiusVector       = CartesianVector<Distance>;
using VelocityVector     = CartesianVector<Velocity>;
using AccelerationVector = CartesianVector<Acceleration>;
using UnitVector         = CartesianVector<Unitless>;



template <typename T, typename U>
CartesianVector<decltype(T{} * U{})> operator*(const U& scalar, const CartesianVector<T>& vec)
{
    return CartesianVector(vec.get_x() * scalar, vec.get_y() * scalar, vec.get_z() * scalar);
}

template <typename T, typename U>
CartesianVector<decltype(T{} * U{})> operator/(const U& scalar, const CartesianVector<T>& vec)
{
    return CartesianVector(vec.get_x() / scalar, vec.get_y() / scalar, vec.get_z() / scalar);
}

} // namespace waveguide