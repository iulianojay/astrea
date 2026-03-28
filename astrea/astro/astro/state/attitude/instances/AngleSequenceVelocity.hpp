/**
 * @file AngleSequenceVelocity.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Class representing angular sequence velocities for attitude transformations between state/frames.
 * @date 2026-03-22
 *
 * @copyright Copyright (c) 2026 Jay Iuliano
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

#include <mp-units/systems/isq_angle.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frame_concepts.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/state/attitude/instances/AngleSequence.hpp>
#include <astro/types/enums.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing a sequence of angular velocities (either Euler or Tait-Bryan) for attitude transformations between frames.
 *
 * @tparam Sequence_T The type of angle sequence (EulerSequence or TaitBryanSequence).
 * @tparam sequence The specific sequence of rotations (e.g., EulerSequence::ZXZ).
 * @tparam rotationType Whether the sequence is intrinsic or extrinsic.
 * @tparam In_Frame_T The input frame type (e.g., ECI, ECEF).
 * @tparam Out_Frame_T The output frame type (e.g., ECI, ECEF).
 *
 * @note: welcome to templating hell
 */
template <typename Sequence_T, Sequence_T sequence, RotationSequenceType rotationType, typename In_Frame_T, typename Out_Frame_T>
    requires(std::same_as<Sequence_T, EulerSequence> || std::same_as<Sequence_T, TaitBryanSequence>)
class AngleSequenceVelocity {

    friend class AttitudePartial;

  public:
    /**
     * @brief Default constructor for the AngleSequenceVelocity class. Initializes all angles to zero.
     */
    AngleSequenceVelocity() = default;

    /**
     * @brief Constructor for the AngleSequenceVelocity class from three angles.
     *
     * @param angle1 The first angle in the sequence.
     * @param angle2 The second angle in the sequence.
     * @param angle3 The third angle in the sequence.
     */
    AngleSequenceVelocity(const AngularVelocity& angle1, const AngularVelocity& angle2, const AngularVelocity& angle3) :
        _angularVelocity(angle1, angle2, angle3)
    {
    }

    /**
     * @brief Constructor for the AngleSequenceVelocity class from a CartesianVector of angles.
     *
     * @param angles A CartesianVector containing the three angles in the sequence.
     */
    AngleSequenceVelocity(const CartesianVector<AngularVelocity, In_Frame_T>& angles) :
        _angularVelocity(angles)
    {
    }

    // Explicitly deleted copy/move assignment/constructor to prevent implicit frame switches, rotation type conversions, and sequence conversions.
    template <typename Sequence_U, Sequence_U sequence_u, RotationSequenceType rotationType_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsSameAngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T, Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>)
    AngleSequenceVelocity(const AngleSequenceVelocity<Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>& other) = delete;

    template <typename Sequence_U, Sequence_U sequence_u, RotationSequenceType rotationType_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsSameAngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T, Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>)
    AngleSequenceVelocity(AngleSequenceVelocity<Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>&& other) = delete;

    template <typename Sequence_U, Sequence_U sequence_u, RotationSequenceType rotationType_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsSameAngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T, Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>)
    AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>&
        operator=(const AngleSequenceVelocity<Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>& other) = delete;

    template <typename Sequence_U, Sequence_U sequence_u, RotationSequenceType rotationType_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsSameAngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T, Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>)
    AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>&
        operator=(AngleSequenceVelocity<Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>&& other) = delete;

    /**
     * @brief Access operator for vector components.
     *
     * @param index The index of the component to access (0 for x, 1 for y, 2 for z).
     * @return AngularVelocity& Reference to the component at the specified index.
     */
    AngularVelocity& operator[](size_t index) { return _angularVelocity[index]; }

    /**
     * @brief Const access operator for vector components.
     *
     * @param index The index of the component to access (0 for x, 1 for y, 2 for z).
     * @return const AngularVelocity& Reference to the component at the specified index.
     */
    const AngularVelocity& operator[](size_t index) const { return _angularVelocity[index]; }

    /**
     * @brief Equality operator for CartesianVector.
     *
     * @param other The other CartesianVector to compare with.
     * @return true If the two vectors are equal.
     * @return false If the two vectors are not equal.
     *
     * @note Equivalent sequences aren't allowed here because it would imply that their derivatives are the same, which is not true.
     */
    bool operator==(const AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& other) const
    {
        return _angularVelocity == other._angularVelocity;
    }

    /**
     * @brief Inequality operator for CartesianVector in a different frame. Always false.
     *
     * @param other The other CartesianVector to compare with.
     * @return true If the two vectors are not equal.
     * @return false If the two vectors are equal.
     */
    template <typename Sequence_U, Sequence_U sequence_u, RotationSequenceType rotationType_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsSameAngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T, Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>)
    bool operator==(const AngleSequenceVelocity<Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>& other) const
    {
        return false;
    }

    /**
     * @brief Addition operator for CartesianVector.
     *
     * @param other The other AngleSequenceVelocity to add.
     * @return AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> A new
     * AngleSequenceVelocity that is the sum of this sequence and the other.
     */
    AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>
        operator+(const AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& other) const
    {
        return { _angularVelocity + other._angularVelocity };
    }

    /**
     * @brief Addition assignment operator for AngleSequenceVelocity.
     *
     * @param other The other AngleSequenceVelocity to add.
     * @return AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& Reference to the current object after addition.
     */
    AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>&
        operator+=(const AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& other)
    {
        _angularVelocity += other._angularVelocity;
        return *this;
    }

    /**
     * @brief Subtraction operator for AngleSequenceVelocity.
     *
     * @param other The other AngleSequenceVelocity to subtract.
     * @return AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> A new
     * AngleSequenceVelocity that is the difference of this sequence and the other.
     */
    AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>
        operator-(const AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& other) const
    {
        return { _angularVelocity - other._angularVelocity };
    }

    /**
     * @brief Negation operator for AngleSequenceVelocity.
     *
     * @return AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> A new
     * AngleSequenceVelocity that is the negation of this sequence.
     */
    AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> operator-() const
    {
        return { -_angularVelocity };
    }

    /**
     * @brief Subtraction assignment operator for AngleSequenceVelocity.
     *
     * @param other The other AngleSequenceVelocity to subtract.
     * @return AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& Reference to the current object after subtraction.
     */
    AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>&
        operator-=(const AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& other)
    {
        _angularVelocity -= other._angularVelocity;
        return *this;
    }

    /**
     * @brief Scalar multiplication operator for AngleSequenceVelocity.
     *
     * @param scalar The scalar value to multiply with.
     * @return AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> A new
     * AngleSequenceVelocity that is the product of this sequence and the scalar.
     */
    AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> operator*(const Unitless& scalar) const
    {
        return { _angularVelocity * scalar };
    }

    /**
     * @brief Scalar division operator for AngleSequenceVelocity by a Time quantity, resulting in an AngleSequenceAcceleration.
     *
     * @param time The time quantity to divide by.
     * @return AngleSequenceAcceleration<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> A new
     * AngleSequenceAcceleration that is the quotient of this sequence and the time.
     */
    AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> operator*(const Time& time) const
    {
        return { _angularVelocity * time };
    }

    /**
     * @brief Scalar multiplication assignment operator for AngleSequenceVelocity.
     *
     * @param scalar The scalar value to multiply with.
     * @return AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& Reference to the current object after multiplication.
     */
    AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& operator*=(const Unitless& scalar)
    {
        _angularVelocity *= scalar;
        return *this;
    }

    /**
     * @brief Scalar division operator for AngleSequenceVelocity by a Time quantity, resulting in an AngleSequenceAcceleration.
     *
     * @param time The time quantity to divide by.
     * @return AngleSequenceAcceleration<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> A new
     * AngleSequenceAcceleration that is the quotient of this sequence and the time.
     */
    AngleSequenceAcceleration<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> operator/(const Time& time) const
    {
        return { _angularVelocity / time };
    }

    /**
     * @brief Scalar division operator for AngleSequenceVelocity.
     *
     * @param scalar The scalar value to divide by.
     * @return AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> A new
     * AngleSequenceVelocity that is the quotient of this sequence and the scalar.
     */
    AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> operator/(const Unitless& scalar) const
    {
        return { _angularVelocity / scalar };
    }

    /**
     * @brief Scalar division assignment operator for AngleSequenceVelocity.
     *
     * @param scalar The scalar value to divide by.
     * @return AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& Reference to the current object after division.
     */
    AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& operator/=(const Unitless& scalar)
    {
        _angularVelocity /= scalar;
        return *this;
    }

    /**
     * @brief Get the x value of the Cartesian vector.
     *
     * @return AngularVelocity& Reference to the x component of the Cartesian vector.
     */
    AngularVelocity& get_phi_dot() { return _angularVelocity[0]; }

    /**
     * @brief Get the x value of the Cartesian vector.
     *
     * @return const AngularVelocity& Reference to the x component of the Cartesian vector.
     */
    const AngularVelocity& get_phi_dot() const { return _angularVelocity[0]; }

    /**
     * @brief Get the y value of the Cartesian vector.
     *
     * @return AngularVelocity& Reference to the y component of the Cartesian vector.
     */
    AngularVelocity& get_theta_dot() { return _angularVelocity[1]; }

    /**
     * @brief Get the y value of the Cartesian vector.
     *
     * @return const AngularVelocity& Reference to the y component of the Cartesian vector.
     */
    const AngularVelocity& get_theta_dot() const { return _angularVelocity[1]; }

    /**
     * @brief Get the z value of the Cartesian vector.
     *
     * @return AngularVelocity& Reference to the z component of the Cartesian vector.
     */
    AngularVelocity& get_psi_dot() { return _angularVelocity[2]; }

    /**
     * @brief Get the z value of the Cartesian vector.
     *
     * @return const AngularVelocity& Reference to the z component of the Cartesian vector.
     */
    const AngularVelocity& get_psi_dot() const { return _angularVelocity[2]; }

    /**
     * @brief Get the angles as a CartesianVector.
     *
     * @return CartesianVector<AngularVelocity, In_Frame_T>& Reference to the angles as a CartesianVector.
     */
    CartesianVector<AngularVelocity, In_Frame_T>& get_angular_velocity() { return _angularVelocity; }

    /**
     * @brief Get the angles as a CartesianVector.
     *
     * @return const CartesianVector<AngularVelocity, In_Frame_T>& Reference to the angles as a CartesianVector.
     */
    const CartesianVector<AngularVelocity, In_Frame_T>& get_angular_velocity() const { return _angularVelocity; }

    /**
     * @brief Dot product of this angle vector with a CartesianVector.
     *
     * @tparam Value_U The type of the CartesianVector's components.
     * @param vec The CartesianVector to take the dot product with.
     * @return Value_U The resulting scalar from the dot product.
     *
     * @note The result is divided by the coates angle to convert from the angle units to the same units as the other
     * vector's components. This is necessary because the resultant scalar is rarely desired in the base units
     * multiplied by radians. If users want that, they can first extract the angle vector and multiply it directly.
     */
    template <typename Value_U>
    Value_U dot(const CartesianVector<Value_U, In_Frame_T>& vec) const
    {
        using mp_units::isq_angle::cotes_angle;
        return (_angularVelocity.dot(vec)) / cotes_angle;
    }

    /**
     * @brief Dot product of this angle vector with another AngleSequenceVelocity.
     *
     * @param other The other AngleSequenceVelocity to take the dot product with.
     * @return Unitless The resulting scalar from the dot product.
     *
     * @note The result is divided by the coates angle to convert from the angle units to the same units as the other
     * vector's components. This is necessary because the resultant scalar is rarely desired in the base units
     * multiplied by radians. If users want that, they can first extract the angle vector and multiply it directly.
     */
    Unitless dot(const AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& other) const
    {
        using namespace mp_units;
        using mp_units::isq_angle::cotes_angle;
        return (_angularVelocity.dot(other.get_angular_velocity())) / pow<2>(cotes_angle);
    }

    /**
     * @brief Cross product of this angle vector with a CartesianVector.
     *
     * @tparam Value_U The type of the CartesianVector's components.
     * @param vec The CartesianVector to take the cross product with.
     * @return CartesianVector<decltype(Value_U{} * rad), In_Frame_T> The resulting CartesianVector from the cross product.
     */
    template <typename Value_U>
    auto cross(const CartesianVector<Value_U, In_Frame_T>& vec) const
    {
        return _angularVelocity.cross(vec);
    }

    /**
     * @brief Cross product of this angle vector with another AngleSequenceVelocity.
     *
     * @param other The other AngleSequenceVelocity to take the cross product with.
     * @return CartesianVector<decltype(mp_units::pow<2>(mp_units::isq_angle::rad)), In_Frame_T> The resulting AngleSequenceVelocity from the cross product.
     */
    auto cross(const AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& other) const
    {
        return this->cross(other.get_angular_velocity());
    }

    /**
     * @brief Norm of the angle vector.
     *
     * @return AngularVelocity The resulting norm of the angle vector.
     */
    AngularVelocity norm() const { return _angularVelocity.norm(); }

    /**
     * @brief Converts the angle sequence velocity to a vector form for use in numerical integration.
     *
     * @return A std::vector of Unitless quantities representing the components of the angle sequence velocity, in the order [first, second, third].
     */
    std::vector<Unitless> force_to_vector() const
    {
        return { _angularVelocity[0] / _angularVelocity[0].unit,
                 _angularVelocity[1] / _angularVelocity[1].unit,
                 _angularVelocity[2] / _angularVelocity[2].unit };
    }

    /**
     * @brief Interpolates between this angle sequence and another angle sequence at a target time.
     *
     * @param thisTime The time corresponding to this angle sequence.
     * @param otherTime The time corresponding to the other angle sequence.
     * @param other The other angle sequence to interpolate with.
     * @param targetTime The time at which to interpolate the angle sequence.
     * @return AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> A new
     * AngleSequenceVelocity that is the interpolation of this sequence and the other at the target time.
     */
    AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> interpolate(
        const Time& thisTime,
        const Time& otherTime,
        const AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& other,
        const Time& targetTime
    ) const
    {
        // Linear interpolation is fine for angular rates
        const std::array<Time, 2> times = { thisTime, otherTime };
        const AngularVelocity interpPhiDot =
            math::fast_interpolate<Time, AngularVelocity>(times, { _angularVelocity[0], other._angularVelocity[0] }, targetTime);
        const AngularVelocity interpThetaDot =
            math::fast_interpolate<Time, AngularVelocity>(times, { _angularVelocity[1], other._angularVelocity[1] }, targetTime);
        const AngularVelocity interpPsiDot =
            math::fast_interpolate<Time, AngularVelocity>(times, { _angularVelocity[2], other._angularVelocity[2] }, targetTime);

        return { interpPhiDot, interpThetaDot, interpPsiDot };
    }

  private:
    CartesianVector<AngularVelocity, In_Frame_T> _angularVelocity;

    /**
     * @brief Constructs an AngleSequenceVelocity from a vector of Unitless quantities representing the angle components.
     *
     * @param vec A std::vector of Unitless quantities representing the components of the angle sequence, in the order [first, second, third].
     * @return A new AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> constructed from the given vector.
     *
     * @throws std::invalid_argument if the input vector does not have exactly 3 components.
     */
    static AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>
        from_vector(const std::vector<Unitless>& vec)
    {
        using mp_units::angular::unit_symbols::rad;
        using mp_units::si::unit_symbols::s;

        if (vec.size() != 3) {
            throw std::invalid_argument("Input vector must have exactly 3 components to convert to an AngleSequenceVelocity.");
        }
        return { vec[0] * rad / s, vec[1] * rad / s, vec[2] * rad / s };
    }
};

/**
 * @brief Scalar multiplication operator for AngleSequenceVelocitys.
 *
 * @tparam T The type of the vector components.
 * @tparam U The type of the scalar to multiply with.
 * @param scalar The scalar value to multiply with.
 * @param vec The AngleSequenceVelocity to multiply.
 * @return AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> A new
 * AngleSequenceVelocity that is the product of the scalar and the vector.
 */
template <typename Sequence_T, Sequence_T sequence, RotationSequenceType rotationType, typename In_Frame_T, typename Out_Frame_T>
AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>
    operator*(const Unitless& scalar, const AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& vec)
{
    return vec * scalar;
}

/**
 * @brief Scalar division operator for AngleSequenceVelocitys.
 *
 * @tparam T The type of the vector components.
 * @tparam U The type of the scalar to divide by.
 * @param scalar The scalar value to divide by.
 * @param vec The AngleSequenceVelocity to divide.
 * @return AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> A new
 * AngleSequenceVelocity that is the quotient of the scalar and the vector.
 */
template <typename Sequence_T, Sequence_T sequence, RotationSequenceType rotationType, typename In_Frame_T, typename Out_Frame_T>
AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>
    operator/(const Unitless& scalar, const AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& vec)
{
    return vec / scalar;
}

/**
 * @brief Class representing the angular sequence acceleration, which is the time derivative of the angular sequence velocity.
 *
 * @tparam Sequence_T The type of angle sequence (EulerSequence or TaitBryanSequence).
 * @tparam sequence The specific sequence of rotations (e.g., EulerSequence::ZXZ).
 * @tparam rotationType Whether the sequence is intrinsic or extrinsic.
 * @tparam In_Frame_T The input frame type (e.g., ECI, ECEF).
 * @tparam Out_Frame_T The output frame type (e.g., ECI, ECEF).
 *
 * @note: welcome to templating hell pt. 2
 */
template <typename Sequence_T, Sequence_T sequence, RotationSequenceType rotationType, typename In_Frame_T, typename Out_Frame_T>
    requires(std::same_as<Sequence_T, EulerSequence> || std::same_as<Sequence_T, TaitBryanSequence>)
class AngleSequenceAcceleration {

    friend class Attitude;

  public:
    /**
     * @brief Default constructor for the AngleSequenceAcceleration class. Initializes all angular accelerations to zero.
     */
    AngleSequenceAcceleration() = default;

    /**
     * @brief Constructor for the AngleSequenceAcceleration class from three angular accelerations.
     *
     * @param accel1 The first angular acceleration in the sequence.
     * @param accel2 The second angular acceleration in the sequence.
     * @param accel3 The third angular acceleration in the sequence.
     */
    AngleSequenceAcceleration(const AngularAcceleration& accel1, const AngularAcceleration& accel2, const AngularAcceleration& accel3) :
        _angularAcceleration(accel1, accel2, accel3)
    {
    }

    /**
     * @brief Constructor for the AngleSequenceAcceleration class from a CartesianVector of angular accelerations.
     *
     * @param accels A CartesianVector containing the three angular accelerations in the sequence.
     */
    AngleSequenceAcceleration(const CartesianVector<AngularAcceleration, In_Frame_T>& accels) :
        _angularAcceleration(accels)
    {
    }

    /**
     * @brief Access operator for vector components.
     *
     * @param index The index of the component to access (0 for x, 1 for y, 2 for z).
     * @return AngularAcceleration& Reference to the component at the specified index.
     */
    AngularAcceleration& operator[](size_t index) { return _angularAcceleration[index]; }

    /**
     * @brief Const access operator for vector components.
     *
     * @param index The index of the component to access (0 for x, 1 for y, 2 for z).
     * @return const AngularAcceleration& Reference to the component at the specified index.
     */
    const AngularAcceleration& operator[](size_t index) const { return _angularAcceleration[index]; }

    /**
     * @brief Scalar multiplication operator for AngleSequenceAcceleration.
     *
     * @param scalar The scalar value to multiply with.
     * @return AngleSequenceAcceleration<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> A new
     * AngleSequenceAcceleration that is the product of this sequence and the scalar
     */
    AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> operator*(const Time& time) const
    {
        return { _angularAcceleration * time };
    }

    /**
     * @brief Get the x value of the Cartesian vector.
     *
     * @return AngularAcceleration& Reference to the x component of the Cartesian vector.
     */
    AngularAcceleration get_phi_ddot() const { return _angularAcceleration[0]; }

    /**
     * @brief Get the y value of the Cartesian vector.
     *
     * @return AngularAcceleration& Reference to the y component of the Cartesian vector.
     */
    AngularAcceleration get_theta_ddot() const { return _angularAcceleration[1]; }

    /**
     * @brief Get the z value of the Cartesian vector.
     *
     * @return AngularAcceleration& Reference to the z component of the Cartesian vector.
     */
    AngularAcceleration get_psi_ddot() const { return _angularAcceleration[2]; }

    /**
     * @brief Converts the angular sequence acceleration to a vector form for use in numerical integration.
     *
     * @return A std::vector of Unitless quantities representing the components of the angular sequence acceleration, in the order [first, second, third].
     */
    std::vector<Unitless> force_to_vector() const
    {
        return { _angularAcceleration[0] / _angularAcceleration[0].unit,
                 _angularAcceleration[1] / _angularAcceleration[1].unit,
                 _angularAcceleration[2] / _angularAcceleration[2].unit };
    }

  private:
    CartesianVector<AngularAcceleration, In_Frame_T> _angularAcceleration; //!< The angular accelerations of an angle sequence.
};

/**
 * @brief Output stream operator for AngleSequenceVelocity.
 *
 * @tparam Sequence_T The type of angle sequence (EulerSequence or TaitBryanSequence).
 * @tparam sequence The specific sequence of rotations (e.g., EulerSequence::ZXZ).
 * @tparam rotationType Whether the sequence is intrinsic or extrinsic.
 * @tparam In_Frame_T The input frame type (e.g., ECI, ECEF).
 * @tparam Out_Frame_T The output frame type (e.g., ECI, ECEF).
 * @param os The output stream to write to.
 * @param angleSequenceRate The AngleSequenceVelocity to output.
 * @return std::ostream& The output stream after writing the AngleSequenceVelocity.
 */
template <typename Sequence_T, Sequence_T sequence, RotationSequenceType rotationType, typename In_Frame_T, typename Out_Frame_T>
std::ostream&
    operator<<(std::ostream& os, const AngleSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& angleSequenceRate)
{
    os << "[" << angleSequenceRate[0] << " , " << angleSequenceRate[1] << " , " << angleSequenceRate[2] << "]";
    return os;
}

/**
 * @brief Output stream operator for AngleSequenceAcceleration.
 *
 * @tparam Sequence_T The type of angle sequence (EulerSequence or TaitBryanSequence).
 * @tparam sequence The specific sequence of rotations (e.g., EulerSequence::ZXZ).
 * @tparam rotationType Whether the sequence is intrinsic or extrinsic.
 * @tparam In_Frame_T The input frame type (e.g., ECI, ECEF).
 * @tparam Out_Frame_T The output frame type (e.g., ECI, ECEF).
 * @param os The output stream to write to.
 * @param angleSequenceAccel The AngleSequenceAcceleration to output.
 * @return std::ostream& The output stream after writing the AngleSequenceAcceleration.
 */
template <typename Sequence_T, Sequence_T sequence, RotationSequenceType rotationType, typename In_Frame_T, typename Out_Frame_T>
std::ostream&
    operator<<(std::ostream& os, const AngleSequenceAcceleration<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& angleSequenceAccel)
{
    os << "[" << angleSequenceAccel[0] << " , " << angleSequenceAccel[1] << " , " << angleSequenceAccel[2] << "]";
    return os;
}

} // namespace astro
} // namespace astrea