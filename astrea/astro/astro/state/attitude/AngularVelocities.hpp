/**
 * @file AngularVelocities.hpp
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

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions/dynamic_frames.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/frames/framework/DirectionCosineMatrix.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/platforms/InertiaTensor.hpp>
#include <astro/state/attitude/EulerAngles.hpp>
#include <astro/state/framework/ElementMatrix.hpp>
#include <astro/types/enums.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing a sequence of angular velocities (either Euler or Tait-Bryan) for attitude transformations between frames.
 *
 * @tparam in_frame The input frame type (e.g., ECI, ECEF), defaulting to dynamic body frame.
 * @tparam ref_frame The reference frame type (e.g., ECI, ECEF), defaulting to Earth ICRF frame.
 */
template <IsFrame auto _in_frame_, IsFrame auto _ref_frame_>
class AngularVelocities {

    friend class AttitudePartial;
    friend std::ostream& operator<<(std::ostream& os, const AngularVelocities& angularVelocities)
    {
        os << angularVelocities._angularVelocities;
        return os;
    }

  public:
    static constexpr auto in_frame  = _in_frame_;
    static constexpr auto ref_frame = _ref_frame_;

    /**
     * @brief Default constructor for the AngularVelocities class. Initializes all angles to zero.
     */
    AngularVelocities() = default;

    /**
     * @brief Constructor for the AngularVelocities class from three angles.
     *
     * @param angle1 The first angle in the sequence.
     * @param angle2 The second angle in the sequence.
     * @param angle3 The third angle in the sequence.
     */
    AngularVelocities(const AngularVelocity& angle1, const AngularVelocity& angle2, const AngularVelocity& angle3) :
        _angularVelocities(angle1, angle2, angle3)
    {
    }

    /**
     * @brief Constructor for the AngularVelocities class from a CartesianVector of angles.
     *
     * @param angles A CartesianVector containing the three angles in the sequence.
     */
    AngularVelocities(const CartesianVector<AngularVelocity, in_frame>& angles) :
        _angularVelocities(angles)
    {
    }

    explicit AngularVelocities(const AngularVelocities& other)   = default;
    explicit AngularVelocities(AngularVelocities&& other)        = default;
    AngularVelocities& operator=(const AngularVelocities& other) = default;
    AngularVelocities& operator=(AngularVelocities&& other)      = default;

    /**
     * @brief Array access operator for accessing individual angular velocity components.
     *
     * @param index The index of the angular velocity component (0, 1, or 2).
     * @return AngularVelocity& Reference to the angular velocity component.
     */
    AngularVelocity& operator[](std::size_t index) { return _angularVelocities[index]; }

    /**
     * @brief Const array access operator for accessing individual angular velocity components.
     *
     * @param index The index of the angular velocity component (0, 1, or 2).
     * @return const AngularVelocity& Const reference to the angular velocity component.
     */
    const AngularVelocity& operator[](std::size_t index) const { return _angularVelocities[index]; }

    /**
     * @brief Get access to the underlying CartesianVector.
     *
     * @return CartesianVector<AngularVelocity, in_frame>& Reference to the internal CartesianVector.
     */
    CartesianVector<AngularVelocity, in_frame>& get_angular_velocities() { return _angularVelocities; }

    /**
     * @brief Get const access to the underlying CartesianVector.
     *
     * @return const CartesianVector<AngularVelocity, in_frame>& Const reference to the internal CartesianVector.
     */
    const CartesianVector<AngularVelocity, in_frame>& get_angular_velocities() const { return _angularVelocities; }

    bool operator==(const AngularVelocities& other) const { return _angularVelocities == other._angularVelocities; }

    template <auto in_frame_u, auto ref_frame_u>
    bool operator==(const AngularVelocities<in_frame_u, ref_frame_u>&) const
    {
        return false;
    }

    /**
     * @brief Addition operator for CartesianVector.
     *
     * @param other The other CartesianVector to add.
     * @return CartesianVector<AngularVelocity, in_frame> A new
     * CartesianVector that is the sum of this sequence and the other.
     */
    CartesianVector<AngularVelocity, in_frame> operator+(const CartesianVector<AngularVelocity, in_frame>& other) const
    {
        return { _angularVelocities + other };
    }

    /**
     * @brief Addition operator for CartesianVector.
     *
     * @param other The other AngularVelocities to add.
     * @return AngularVelocities A new
     * AngularVelocities that is the sum of this sequence and the other.
     */
    AngularVelocities operator+(const AngularVelocities& other) const
    {
        return { _angularVelocities + other._angularVelocities };
    }

    /**
     * @brief Addition assignment operator for AngularVelocities.
     *
     * @param other The other AngularVelocities to add.
     * @return AngularVelocities& Reference to the current object after addition.
     */
    AngularVelocities& operator+=(const AngularVelocities& other)
    {
        _angularVelocities += other._angularVelocities;
        return *this;
    }

    /**
     * @brief Unary negation operator for AngularVelocities.
     *
     * @return AngularVelocities A new
     * AngularVelocities that is the negation of this sequence.
     */
    AngularVelocities operator-() const { return { -_angularVelocities }; }

    /**
     * @brief Subtraction operator for CartesianVector.
     *
     * @param other The other CartesianVector to subtract.
     * @return CartesianVector<AngularVelocity, in_frame> CartesianVector result of subtraction.
     */
    CartesianVector<AngularVelocity, in_frame> operator-(const CartesianVector<AngularVelocity, in_frame>& other) const
    {
        return _angularVelocities - other;
    }

    /**
     * @brief Subtraction operator for AngularVelocities.
     *
     * @param other The other AngularVelocities to subtract.
     * @return AngularVelocities A new
     * AngularVelocities that is the difference of this sequence and the other.
     */
    AngularVelocities operator-(const AngularVelocities& other) const
    {
        return { _angularVelocities - other._angularVelocities };
    }

    /**
     * @brief Subtraction assignment operator for AngularVelocities.
     *
     * @param other The other AngularVelocities to subtract.
     * @return AngularVelocities& Reference to the current object after subtraction.
     */
    AngularVelocities& operator-=(const AngularVelocities& other)
    {
        _angularVelocities -= other._angularVelocities;
        return *this;
    }

    /**
     * @brief Scalar multiplication operator for AngularVelocities by a quantity, resulting in an CartesianVector.
     *
     * @param scalar The quantity to multiply by.
     * @return CartesianVector<decltype(AngularVelocity{} * Value_U{}), in_frame> A new
     * CartesianVector that is the product of this sequence and the quantity.
     */
    template <typename Value_U>
    CartesianVector<decltype(AngularVelocity{} * Value_U{}), in_frame> operator*(const Value_U& scalar) const
    {
        return _angularVelocities * scalar;
    }

    /**
     * @brief Scalar multiplication operator for AngularVelocities by a Time quantity, resulting in an EulerAngles.
     *
     * @param time The time quantity to multiply by.
     * @return EulerAngles<sequence, rotation_type, in_frame, ref_frame> A new
     * EulerAngles that is the product of this sequence and the time.
     */
    template <RotationSequence sequence, RotationType rotation_type>
    EulerAngles<sequence, rotation_type, in_frame, ref_frame> operator*(const Time& time) const
    {
        return { _angularVelocities * time };
    }

    /**
     * @brief Scalar multiplication operator for AngularVelocities by a quantity, resulting in an AngularVelocities.
     *
     * @param scale The quantity to multiply by.
     * @return AngularVelocities A new
     * AngularVelocities that is the product of this sequence and the quantity.
     */
    AngularVelocities operator*(const Unitless& scale) const { return { _angularVelocities * scale }; }

    /**
     * @brief Scalar multiplication assignment operator for AngularVelocities by a quantity.
     *
     * @param scale The quantity to multiply by.
     * @return AngularVelocities& Reference to the current object after multiplication.
     */
    AngularVelocities& operator*=(const Unitless& scale)
    {
        _angularVelocities *= scale;
        return *this;
    }

    /**
     * @brief Scalar division operator for AngularVelocities by a quantity, resulting in a CartesianVector.
     *
     * @param scalar The quantity to divide by.
     * @return CartesianVector<decltype(AngularVelocity{} / Value_U{}), in_frame> A new
     * CartesianVector that is the quotient of this sequence and the quantity.
     */
    template <typename Value_U>
    CartesianVector<decltype(AngularVelocity{} / Value_U{}), in_frame> operator/(const Value_U& scalar) const
    {
        return _angularVelocities / scalar;
    }

    /**
     * @brief Scalar division operator for AngularVelocities by a Time quantity, resulting in an AngularAccelerations.
     *
     * @param time The time quantity to divide by.
     * @return AngularAccelerations<in_frame, ref_frame> A new
     * AngularAccelerations that is the quotient of this sequence and the time.
     */
    AngularAccelerations<in_frame, ref_frame> operator/(const Time& time) const
    {
        return { _angularVelocities / time };
    }

    /**
     * @brief Scalar division operator for AngularVelocities by a quantity, resulting in an AngularVelocities.
     *
     * @param scale The quantity to divide by.
     * @return AngularVelocities A new
     * AngularVelocities that is the quotient of this sequence and the quantity.
     */
    AngularVelocities operator/(const Unitless& scale) const { return { _angularVelocities / scale }; }

    /**
     * @brief Scalar division assignment operator for AngularVelocities by a quantity.
     *
     * @param scale The quantity to divide by.
     * @return AngularVelocities& Reference to the current object after division.
     */
    AngularVelocities& operator/=(const Unitless& scale)
    {
        _angularVelocities /= scale;
        return *this;
    }

    /**
     * @brief Dot product of this angular velocity vector with a CartesianVector.
     *
     * @tparam Value_U The type of the CartesianVector's components.
     * @param other The CartesianVector to take the dot product with.
     * @return auto The resulting scalar from the dot product.
     */
    template <typename Value_U>
    auto dot(const CartesianVector<Value_U, in_frame>& other) const
    {
        return _angularVelocities.dot(other);
    }

    /**
     * @brief Dot product of this angle vector with another AngularVelocities.
     *
     * @param other The other AngularVelocities to take the dot product with.
     * @return auto The resulting scalar from the dot product.
     */
    auto dot(const AngularVelocities& other) const { return _angularVelocities.dot(other._angularVelocities); }

    /**
     * @brief Cross product of this angular velocity vector with a CartesianVector.
     *
     * @tparam Value_U The type of the CartesianVector's components.
     * @param other The CartesianVector to take the cross product with.
     * @return CartesianVector<decltype(AngularVelocity{} * Value_U{}), in_frame> The resulting CartesianVector from the cross product.
     */
    template <typename Value_U>
    CartesianVector<decltype(AngularVelocity{} * Value_U{}), in_frame> cross(const CartesianVector<Value_U, in_frame>& other) const
    {
        return _angularVelocities.cross(other);
    }

    /**
     * @brief Cross product of this angle vector with another AngularVelocities.
     *
     * @param other The other AngularVelocities to take the cross product with.
     * @return CartesianVector<decltype(AngularVelocity{} * AngularVelocity{}), in_frame> The resulting CartesianVector from the cross product.
     */
    CartesianVector<decltype(AngularVelocity{} * AngularVelocity{}), in_frame> cross(const AngularVelocities& other) const
    {
        return _angularVelocities.cross(other._angularVelocities);
    }

    /**
     * @brief Converts the angle sequence velocity to a vector form for use in numerical integration.
     *
     * @return A std::vector of Unitless quantities representing the components of the angle sequence velocity, in the order [first, second, third].
     */
    UniformElementArray<3, AngularVelocity> force_to_element_array() const
    {
        return { _angularVelocities[0], _angularVelocities[1], _angularVelocities[2] };
    }

    /**
     * @brief Interpolates between this angle sequence and another angle sequence at a target time.
     *
     * @param thisTime The time corresponding to this angle sequence.
     * @param otherTime The time corresponding to the other angle sequence.
     * @param other The other angle sequence to interpolate with.
     * @param targetTime The time at which to interpolate the angle sequence.
     * @return AngularVelocities A new
     * AngularVelocities that is the interpolation of this sequence and the other at the target time.
     */
    AngularVelocities interpolate(const Time& thisTime, const Time& otherTime, const AngularVelocities& other, const Time& targetTime) const
    {
        // Linear interpolation is fine for angular rates
        const std::array<Time, 2> times = { thisTime, otherTime };
        const AngularVelocity interpPhiDot =
            math::fast_interpolate<Time, AngularVelocity>(times, { _angularVelocities[0], other._angularVelocities[0] }, targetTime);
        const AngularVelocity interpThetaDot =
            math::fast_interpolate<Time, AngularVelocity>(times, { _angularVelocities[1], other._angularVelocities[1] }, targetTime);
        const AngularVelocity interpPsiDot =
            math::fast_interpolate<Time, AngularVelocity>(times, { _angularVelocities[2], other._angularVelocities[2] }, targetTime);

        return { interpPhiDot, interpThetaDot, interpPsiDot };
    }

  private:
    CartesianVector<AngularVelocity, in_frame> _angularVelocities;
};

/**
 * @brief Scalar multiplication operator for AngularVelocities with an InertiaTensor.
 *
 * @tparam sequence The specific sequence of rotations (e.g., RotationSequence::ZXZ).
 * @tparam type Whether the sequence is intrinsic or extrinsic.
 * @tparam in_frame The input frame type (e.g., ECI, ECEF).
 * @tparam ref_frame The output frame type (e.g., ECI, ECEF).
 * @param inertiaTensor The InertiaTensor to multiply with.
 * @param vec The AngularVelocities to multiply.
 * @return CartesianVector<decltype(MomentOfInertia{} * AngularVelocity{}), in_frame> A new
 * CartesianVector that is the product of the inertia tensor and the angle sequence velocity.
 */
template <IsFrame auto in_frame, IsFrame auto ref_frame>
CartesianVector<decltype(MomentOfInertia{} * AngularVelocity{}), in_frame>
    operator*(const InertiaTensor<in_frame>& inertiaTensor, const AngularVelocities<in_frame, ref_frame>& vec)
{

    return { inertiaTensor[0, 0] * vec[0] + inertiaTensor[0, 1] * vec[1] + inertiaTensor[0, 2] * vec[2],
             inertiaTensor[1, 0] * vec[0] + inertiaTensor[1, 1] * vec[1] + inertiaTensor[1, 2] * vec[2],
             inertiaTensor[2, 0] * vec[0] + inertiaTensor[2, 1] * vec[1] + inertiaTensor[2, 2] * vec[2] };
}

/**
 * @brief Class representing the angular sequence acceleration, which is the time derivative of the angular sequence velocity.
 *
 * @tparam in_frame The input frame type (e.g., ECI, ECEF).
 * @tparam ref_frame The output frame type (e.g., ECI, ECEF).
 */
template <IsFrame auto _in_frame_, IsFrame auto _ref_frame_>
class AngularAccelerations {

    friend class Attitude;

  public:
    static constexpr auto in_frame  = _in_frame_;
    static constexpr auto ref_frame = _ref_frame_;

    /**
     * @brief Default constructor for the AngularAccelerations class. Initializes all angular accelerations to zero.
     */
    AngularAccelerations() = default;

    /**
     * @brief Constructor for the AngularAccelerations class from three angular accelerations.
     *
     * @param accel1 The first angular acceleration in the sequence.
     * @param accel2 The second angular acceleration in the sequence.
     * @param accel3 The third angular acceleration in the sequence.
     */
    AngularAccelerations(const AngularAcceleration& accel1, const AngularAcceleration& accel2, const AngularAcceleration& accel3) :
        _angularAccels(accel1, accel2, accel3)
    {
    }

    /**
     * @brief Constructor for the AngularAccelerations class from a CartesianVector of angular accelerations.
     *
     * @param accels A CartesianVector containing the three angular accelerations in the sequence.
     */
    AngularAccelerations(const CartesianVector<AngularAcceleration, in_frame>& accels) :
        _angularAccels(accels)
    {
    }

    /**
     * @brief Array access operator for accessing individual angular acceleration components.
     *
     * @param index The index of the angular acceleration component (0, 1, or 2).
     * @return AngularAcceleration& Reference to the angular acceleration component.
     */
    AngularAcceleration& operator[](std::size_t index) { return _angularAccels[index]; }

    /**
     * @brief Const array access operator for accessing individual angular acceleration components.
     *
     * @param index The index of the angular acceleration component (0, 1, or 2).
     * @return const AngularAcceleration& Const reference to the angular acceleration component.
     */
    const AngularAcceleration& operator[](std::size_t index) const { return _angularAccels[index]; }

    /**
     * @brief Get access to the underlying CartesianVector.
     *
     * @return CartesianVector<AngularAcceleration, in_frame>& Reference to the internal CartesianVector.
     */
    CartesianVector<AngularAcceleration, in_frame>& get_angularAccels() { return _angularAccels; }

    /**
     * @brief Get const access to the underlying CartesianVector.
     *
     * @return const CartesianVector<AngularAcceleration, in_frame>& Const reference to the internal CartesianVector.
     */
    const CartesianVector<AngularAcceleration, in_frame>& get_angularAccels() const { return _angularAccels; }

    /**
     * @brief Addition operator for AngularAccelerations.
     *
     * @param other The other AngularAccelerations to add.
     * @return AngularAccelerations<in_frame, ref_frame> A new
     * AngularAccelerations that is the sum of this and other.
     */
    AngularAccelerations<in_frame, ref_frame> operator+(const AngularAccelerations<in_frame, ref_frame>& other) const
    {
        return { _angularAccels + other._angularAccels };
    }

    /**
     * @brief Addition assignment operator for AngularAccelerations.
     *
     * @param other The other AngularAccelerations to add.
     * @return AngularAccelerations<in_frame, ref_frame>& Reference to the current object after addition.
     */
    AngularAccelerations<in_frame, ref_frame>& operator+=(const AngularAccelerations<in_frame, ref_frame>& other)
    {
        _angularAccels += other._angularAccels;
        return *this;
    }

    /**
     * @brief Subtraction operator for AngularAccelerations.
     *
     * @param other The other AngularAccelerations to subtract.
     * @return AngularAccelerations<in_frame, ref_frame> A new
     * AngularAccelerations that is the difference of this and other.
     */
    AngularAccelerations<in_frame, ref_frame> operator-(const AngularAccelerations<in_frame, ref_frame>& other) const
    {
        return { _angularAccels - other._angularAccels };
    }

    /**
     * @brief Subtraction assignment operator for AngularAccelerations.
     *
     * @param other The other AngularAccelerations to subtract.
     * @return AngularAccelerations<in_frame, ref_frame>& Reference to the current object after subtraction.
     */
    AngularAccelerations<in_frame, ref_frame>& operator-=(const AngularAccelerations<in_frame, ref_frame>& other)
    {
        _angularAccels -= other._angularAccels;
        return *this;
    }

    /**
     * @brief Scalar multiplication operator for AngularAccelerations by a quantity, resulting in a CartesianVector.
     *
     * @param scalar The quantity to multiply by.
     * @return CartesianVector<decltype(AngularAcceleration{} * Value_U{}), in_frame> A new
     * CartesianVector that is the product of this sequence and the quantity.
     */
    template <typename Value_U>
    CartesianVector<decltype(AngularAcceleration{} * Value_U{}), in_frame> operator*(const Value_U& scalar) const
    {
        return { _angularAccels * scalar };
    }

    /**
     * @brief Scalar multiplication operator for AngularAccelerations.
     *
     * @param time The time value to multiply with.
     * @return AngularVelocities<in_frame, ref_frame> A new AngularVelocities that is the product of this sequence and the time
     */
    AngularVelocities<in_frame, ref_frame> operator*(const Time& time) const { return { _angularAccels * time }; }

    /**
     * @brief Scalar division operator for AngularAccelerations by a quantity, resulting in a CartesianVector.
     *
     * @param scalar The quantity to divide by.
     * @return CartesianVector<decltype(AngularAcceleration{} / Value_U{}), in_frame> A new
     * CartesianVector that is the quotient of this sequence and the quantity.
     */
    template <typename Value_U>
    CartesianVector<decltype(AngularAcceleration{} / Value_U{}), in_frame> operator/(const Value_U& scalar) const
    {
        return { _angularAccels / scalar };
    }

    /**
     * @brief Dot product of this angular acceleration vector with a CartesianVector.
     *
     * @tparam Value_U The type of the CartesianVector's components.
     * @param other The CartesianVector to take the dot product with.
     * @return auto The resulting scalar from the dot product.
     */
    template <typename Value_U>
    auto dot(const CartesianVector<Value_U, in_frame>& other) const
    {
        return _angularAccels.dot(other);
    }

    /**
     * @brief Dot product of this angle vector with another AngularAccelerations.
     *
     * @param other The other AngularAccelerations to take the dot product with.
     * @return auto The resulting scalar from the dot product.
     */
    auto dot(const AngularAccelerations<in_frame, ref_frame>& other) const
    {
        return _angularAccels.dot(other._angularAccels);
    }

    /**
     * @brief Cross product of this angular acceleration vector with a CartesianVector.
     *
     * @tparam Value_U The type of the CartesianVector's components.
     * @param other The CartesianVector to take the cross product with.
     * @return CartesianVector<decltype(AngularAcceleration{} * Value_U{}), in_frame> The resulting CartesianVector from the cross product.
     */
    template <typename Value_U>
    CartesianVector<decltype(AngularAcceleration{} * Value_U{}), in_frame> cross(const CartesianVector<Value_U, in_frame>& other) const
    {
        return _angularAccels.cross(other);
    }

    /**
     * @brief Cross product of this angle vector with another AngularAccelerations.
     *
     * @param other The other AngularAccelerations to take the cross product with.
     * @return CartesianVector<decltype(AngularAcceleration{} * AngularAcceleration{}), in_frame> The resulting CartesianVector from the cross product.
     */
    CartesianVector<decltype(AngularAcceleration{} * AngularAcceleration{}), in_frame>
        cross(const AngularAccelerations<in_frame, ref_frame>& other) const
    {
        return _angularAccels.cross(other._angularAccels);
    }

    /**
     * @brief Converts the angular sequence acceleration to an element array for use in numerical integration.

     * @return A std::vector of Unitless quantities representing the components of the angular sequence acceleration, in the order [first, second, third].
     */
    UniformElementArray<3, AngularAcceleration> force_to_element_array() const
    {
        return { _angularAccels[0].numerical_value_in(_angularAccels[0].unit),
                 _angularAccels[1].numerical_value_in(_angularAccels[1].unit),
                 _angularAccels[2].numerical_value_in(_angularAccels[2].unit) };
    }

  private:
    CartesianVector<AngularAcceleration, in_frame> _angularAccels;
};

/**
 * @brief Scalar multiplication operator for a quantity multiplied by AngularAccelerations, resulting in a CartesianVector.
 *
 * @tparam Value_U The type of the scalar quantity.
 * @tparam sequence The specific sequence of rotations.
 * @tparam type Whether the sequence is intrinsic or extrinsic.
 * @tparam in_frame The input frame type.
 * @tparam ref_frame The output frame type.
 * @param scalar The quantity to multiply with.
 * @param accel The AngularAccelerations to multiply.
 * @return CartesianVector<decltype(Value_U{} * AngularAcceleration{}), in_frame> The resulting CartesianVector.
 */
template <typename Value_U, IsFrame auto in_frame, IsFrame auto ref_frame>
CartesianVector<decltype(Value_U{} * AngularAcceleration{}), in_frame>
    operator*(const Value_U& scalar, const AngularAccelerations<in_frame, ref_frame>& accel)
{
    return { scalar * accel.get_angularAccels() };
}

/**
 * @brief Scalar multiplication operator for Time multiplied by AngularAccelerations, resulting in an AngularVelocities.
 *
 * @tparam sequence The specific sequence of rotations.
 * @tparam type Whether the sequence is intrinsic or extrinsic.
 * @tparam in_frame The input frame type.
 * @tparam ref_frame The output frame type.
 * @param time The time value to multiply with.
 * @param accel The AngularAccelerations to multiply.
 * @return AngularVelocities The resulting AngularVelocities.
 */
template <IsFrame auto in_frame, IsFrame auto ref_frame>
AngularVelocities<in_frame, ref_frame> operator*(const Time& time, const AngularAccelerations<in_frame, ref_frame>& accel)
{
    return { time * accel.get_angularAccels() };
}

/**
 * @brief Output stream operator for AngularVelocities.
 *
 * @tparam sequence The specific sequence of rotations (e.g., RotationSequence::ZXZ).
 * @tparam type Whether the sequence is intrinsic or extrinsic.
 * @tparam in_frame The input frame type (e.g., ECI, ECEF).
 * @tparam ref_frame The output frame type (e.g., ECI, ECEF).
 * @param os The output stream to write to.
 * @param angleSequenceRate The AngularVelocities to output.
 * @return std::ostream& The output stream after writing the AngularVelocities.
 */
template <IsFrame auto in_frame, IsFrame auto ref_frame>
std::ostream& operator<<(std::ostream& os, const AngularVelocities<in_frame, ref_frame>& angleSequenceRate)
{
    os << "[" << angleSequenceRate[0] << " , " << angleSequenceRate[1] << " , " << angleSequenceRate[2] << "]";
    return os;
}

/**
 * @brief Output stream operator for AngularAccelerations.
 *
 * @tparam sequence The specific sequence of rotations (e.g., RotationSequence::ZXZ).
 * @tparam type Whether the sequence is intrinsic or extrinsic.
 * @tparam in_frame The input frame type (e.g., ECI, ECEF).
 * @tparam ref_frame The output frame type (e.g., ECI, ECEF).
 * @param os The output stream to write to.
 * @param angleSequenceAccel The AngularAccelerations to output.
 * @return std::ostream& The output stream after writing the AngularAccelerations.
 */
template <IsFrame auto in_frame, IsFrame auto ref_frame>
std::ostream& operator<<(std::ostream& os, const AngularAccelerations<in_frame, ref_frame>& angleSequenceAccel)
{
    os << "[" << angleSequenceAccel[0] << " , " << angleSequenceAccel[1] << " , " << angleSequenceAccel[2] << "]";
    return os;
}

} // namespace astro
} // namespace astrea