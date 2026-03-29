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

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frame_concepts.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/platforms/InertiaTensor.hpp>
#include <astro/state/attitude/instances/AngleSequence.hpp>
#include <astro/types/enums.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing a sequence of angular velocities (either Euler or Tait-Bryan) for attitude transformations between frames.
 *
 * @tparam sequence The specific sequence of rotations (e.g., RotationSequence::ZXZ).
 * @tparam type Whether the sequence is intrinsic or extrinsic.
 * @tparam In_Frame_T The input frame type (e.g., ECI, ECEF).
 * @tparam Out_Frame_T The output frame type (e.g., ECI, ECEF).
 */
template <RotationSequence sequence, RotationType rotation_type, typename In_Frame_T, typename Out_Frame_T>
class AngleSequenceVelocity {

    friend class AttitudePartial;

  public:
    using in_frame  = In_Frame_T;
    using out_frame = Out_Frame_T;

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
        _angularVelocities(angle1, angle2, angle3)
    {
    }

    /**
     * @brief Constructor for the AngleSequenceVelocity class from a CartesianVector of angles.
     *
     * @param angles A CartesianVector containing the three angles in the sequence.
     */
    AngleSequenceVelocity(const CartesianVector<AngularVelocity, In_Frame_T>& angles) :
        _angularVelocities(angles)
    {
    }

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
     * @return CartesianVector<AngularVelocity, In_Frame_T>& Reference to the internal CartesianVector.
     */
    CartesianVector<AngularVelocity, In_Frame_T>& get_angularVelocities() { return _angularVelocities; }

    /**
     * @brief Get const access to the underlying CartesianVector.
     *
     * @return const CartesianVector<AngularVelocity, In_Frame_T>& Const reference to the internal CartesianVector.
     */
    const CartesianVector<AngularVelocity, In_Frame_T>& get_angularVelocities() const { return _angularVelocities; }

    // Explicitly deleted copy/move assignment/constructor to prevent implicit frame switches, rotation type conversions, and sequence conversions.
    template <RotationSequence sequence_u, RotationType rotation_type_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsSameAngleSequence<sequence, rotation_type, In_Frame_T, Out_Frame_T, sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>)
    AngleSequenceVelocity(const AngleSequenceVelocity<sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>& other) = delete;

    template <RotationSequence sequence_u, RotationType rotation_type_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsSameAngleSequence<sequence, rotation_type, In_Frame_T, Out_Frame_T, sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>)
    AngleSequenceVelocity(AngleSequenceVelocity<sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>&& other) = delete;

    template <RotationSequence sequence_u, RotationType rotation_type_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsSameAngleSequence<sequence, rotation_type, In_Frame_T, Out_Frame_T, sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>)
    AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>&
        operator=(const AngleSequenceVelocity<sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>& other) = delete;

    template <RotationSequence sequence_u, RotationType rotation_type_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsSameAngleSequence<sequence, rotation_type, In_Frame_T, Out_Frame_T, sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>)
    AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>&
        operator=(AngleSequenceVelocity<sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>&& other) = delete;

    /**
     * @brief Equality operator for CartesianVector.
     *
     * @param other The other CartesianVector to compare with.
     * @return true If the two vectors are equal.
     * @return false If the two vectors are not equal.
     *
     * @note Equivalent sequences aren't allowed here because it would imply that their derivatives are the same, which is not true.
     */
    bool operator==(const AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other) const
    {
        return _angularVelocities == other._angularVelocities;
    }

    /**
     * @brief Inequality operator for CartesianVector in a different frame. Always false.
     *
     * @param other The other CartesianVector to compare with.
     * @return true If the two vectors are not equal.
     * @return false If the two vectors are equal.
     */
    template <RotationSequence sequence_u, RotationType rotation_type_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsSameAngleSequence<sequence, rotation_type, In_Frame_T, Out_Frame_T, sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>)
    bool operator==(const AngleSequenceVelocity<sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>& other) const
    {
        return false;
    }

    /**
     * @brief Addition operator for CartesianVector.
     *
     * @param other The other CartesianVector to add.
     * @return CartesianVector<AngularVelocity, In_Frame_T> A new
     * CartesianVector that is the sum of this sequence and the other.
     */
    CartesianVector<AngularVelocity, In_Frame_T> operator+(const CartesianVector<AngularVelocity, In_Frame_T>& other) const
    {
        return { _angularVelocities + other };
    }

    /**
     * @brief Addition operator for CartesianVector.
     *
     * @param other The other AngleSequenceVelocity to add.
     * @return AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new
     * AngleSequenceVelocity that is the sum of this sequence and the other.
     */
    AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>
        operator+(const AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other) const
    {
        return { _angularVelocities + other._angularVelocities };
    }

    /**
     * @brief Addition assignment operator for AngleSequenceVelocity.
     *
     * @param other The other AngleSequenceVelocity to add.
     * @return AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>& Reference to the current object after addition.
     */
    AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>&
        operator+=(const AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other)
    {
        _angularVelocities += other._angularVelocities;
        return *this;
    }

    /**
     * @brief Unary negation operator for AngleSequenceVelocity.
     *
     * @return AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new
     * AngleSequenceVelocity that is the negation of this sequence.
     */
    AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T> operator-() const
    {
        return { -_angularVelocities };
    }

    /**
     * @brief Subtraction operator for CartesianVector.
     *
     * @param other The other CartesianVector to subtract.
     * @return CartesianVector<AngularVelocity, In_Frame_T> CartesianVector result of subtraction.
     */
    CartesianVector<AngularVelocity, In_Frame_T> operator-(const CartesianVector<AngularVelocity, In_Frame_T>& other) const
    {
        return _angularVelocities - other;
    }

    /**
     * @brief Subtraction operator for AngleSequenceVelocity.
     *
     * @param other The other AngleSequenceVelocity to subtract.
     * @return AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new
     * AngleSequenceVelocity that is the difference of this sequence and the other.
     */
    AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>
        operator-(const AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other) const
    {
        return { _angularVelocities - other._angularVelocities };
    }

    /**
     * @brief Subtraction assignment operator for AngleSequenceVelocity.
     *
     * @param other The other AngleSequenceVelocity to subtract.
     * @return AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>& Reference to the current object after subtraction.
     */
    AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>&
        operator-=(const AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other)
    {
        _angularVelocities -= other._angularVelocities;
        return *this;
    }

    /**
     * @brief Scalar multiplication operator for AngleSequenceVelocity by a quantity, resulting in an CartesianVector.
     *
     * @param scalar The quantity to multiply by.
     * @return CartesianVector<decltype(AngularVelocity{} * Value_U{}), In_Frame_T> A new
     * CartesianVector that is the product of this sequence and the quantity.
     */
    template <typename Value_U>
    CartesianVector<decltype(AngularVelocity{} * Value_U{}), In_Frame_T> operator*(const Value_U& scalar) const
    {
        return _angularVelocities * scalar;
    }

    /**
     * @brief Scalar multiplication operator for AngleSequenceVelocity by a Time quantity, resulting in an AngleSequence.
     *
     * @param time The time quantity to multiply by.
     * @return AngleSequence<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new
     * AngleSequence that is the product of this sequence and the time.
     */
    AngleSequence<sequence, rotation_type, In_Frame_T, Out_Frame_T> operator*(const Time& time) const
    {
        return { _angularVelocities * time };
    }

    /**
     * @brief Scalar multiplication operator for AngleSequenceVelocity by a quantity, resulting in an AngleSequenceVelocity.
     *
     * @param scale The quantity to multiply by.
     * @return AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new
     * AngleSequenceVelocity that is the product of this sequence and the quantity.
     */
    AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T> operator*(const Unitless& scale) const
    {
        return { _angularVelocities * scale };
    }

    /**
     * @brief Scalar multiplication assignment operator for AngleSequenceVelocity by a quantity.
     *
     * @param scale The quantity to multiply by.
     * @return AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>& Reference to the current object after multiplication.
     */
    AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>& operator*=(const Unitless& scale)
    {
        _angularVelocities *= scale;
        return *this;
    }

    /**
     * @brief Scalar division operator for AngleSequenceVelocity by a quantity, resulting in a CartesianVector.
     *
     * @param scalar The quantity to divide by.
     * @return CartesianVector<decltype(AngularVelocity{} / Value_U{}), In_Frame_T> A new
     * CartesianVector that is the quotient of this sequence and the quantity.
     */
    template <typename Value_U>
    CartesianVector<decltype(AngularVelocity{} / Value_U{}), In_Frame_T> operator/(const Value_U& scalar) const
    {
        return _angularVelocities / scalar;
    }

    /**
     * @brief Scalar division operator for AngleSequenceVelocity by a Time quantity, resulting in an AngleSequenceAcceleration.
     *
     * @param time The time quantity to divide by.
     * @return AngleSequenceAcceleration<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new
     * AngleSequenceAcceleration that is the quotient of this sequence and the time.
     */
    AngleSequenceAcceleration<sequence, rotation_type, In_Frame_T, Out_Frame_T> operator/(const Time& time) const
    {
        return { _angularVelocities / time };
    }

    /**
     * @brief Scalar division operator for AngleSequenceVelocity by a quantity, resulting in an AngleSequenceVelocity.
     *
     * @param scale The quantity to divide by.
     * @return AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new
     * AngleSequenceVelocity that is the quotient of this sequence and the quantity.
     */
    AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T> operator/(const Unitless& scale) const
    {
        return { _angularVelocities / scale };
    }

    /**
     * @brief Scalar division assignment operator for AngleSequenceVelocity by a quantity.
     *
     * @param scale The quantity to divide by.
     * @return AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>& Reference to the current object after division.
     */
    AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>& operator/=(const Unitless& scale)
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
    auto dot(const CartesianVector<Value_U, In_Frame_T>& other) const
    {
        return _angularVelocities.dot(other);
    }

    /**
     * @brief Dot product of this angle vector with another AngleSequenceVelocity.
     *
     * @param other The other AngleSequenceVelocity to take the dot product with.
     * @return auto The resulting scalar from the dot product.
     */
    auto dot(const AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other) const
    {
        return _angularVelocities.dot(other._angularVelocities);
    }

    /**
     * @brief Cross product of this angular velocity vector with a CartesianVector.
     *
     * @tparam Value_U The type of the CartesianVector's components.
     * @param other The CartesianVector to take the cross product with.
     * @return CartesianVector<decltype(AngularVelocity{} * Value_U{}), In_Frame_T> The resulting CartesianVector from the cross product.
     */
    template <typename Value_U>
    CartesianVector<decltype(AngularVelocity{} * Value_U{}), In_Frame_T> cross(const CartesianVector<Value_U, In_Frame_T>& other) const
    {
        return _angularVelocities.cross(other);
    }

    /**
     * @brief Cross product of this angle vector with another AngleSequenceVelocity.
     *
     * @param other The other AngleSequenceVelocity to take the cross product with.
     * @return CartesianVector<decltype(AngularVelocity{} * AngularVelocity{}), In_Frame_T> The resulting CartesianVector from the cross product.
     */
    CartesianVector<decltype(AngularVelocity{} * AngularVelocity{}), In_Frame_T>
        cross(const AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other) const
    {
        return _angularVelocities.cross(other._angularVelocities);
    }

    /**
     * @brief Converts the angle sequence velocity to a vector form for use in numerical integration.
     *
     * @return A std::vector of Unitless quantities representing the components of the angle sequence velocity, in the order [first, second, third].
     */
    std::vector<Unitless> force_to_vector() const
    {
        return { _angularVelocities[0] / _angularVelocities[0].unit,
                 _angularVelocities[1] / _angularVelocities[1].unit,
                 _angularVelocities[2] / _angularVelocities[2].unit };
    }

    /**
     * @brief Interpolates between this angle sequence and another angle sequence at a target time.
     *
     * @param thisTime The time corresponding to this angle sequence.
     * @param otherTime The time corresponding to the other angle sequence.
     * @param other The other angle sequence to interpolate with.
     * @param targetTime The time at which to interpolate the angle sequence.
     * @return AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new
     * AngleSequenceVelocity that is the interpolation of this sequence and the other at the target time.
     */
    AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T> interpolate(
        const Time& thisTime,
        const Time& otherTime,
        const AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other,
        const Time& targetTime
    ) const
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
    CartesianVector<AngularVelocity, In_Frame_T> _angularVelocities;

    /**
     * @brief Constructs an AngleSequenceVelocity from a vector of Unitless quantities representing the angle components.
     *
     * @param vec A std::vector of Unitless quantities representing the components of the angle sequence, in the order [first, second, third].
     * @return A new AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T> constructed from the given vector.
     *
     * @throws std::invalid_argument if the input vector does not have exactly 3 components.
     */
    static AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T> from_vector(const std::vector<Unitless>& vec)
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
 * @brief Scalar multiplication operator for AngleSequenceVelocity with an InertiaTensor.
 *
 * @tparam sequence The specific sequence of rotations (e.g., RotationSequence::ZXZ).
 * @tparam type Whether the sequence is intrinsic or extrinsic.
 * @tparam In_Frame_T The input frame type (e.g., ECI, ECEF).
 * @tparam Out_Frame_T The output frame type (e.g., ECI, ECEF).
 * @param inertiaTensor The InertiaTensor to multiply with.
 * @param vec The AngleSequenceVelocity to multiply.
 * @return CartesianVector<decltype(MomentOfInertia{} * AngularVelocity{}), In_Frame_T> A new
 * CartesianVector that is the product of the inertia tensor and the angle sequence velocity.
 */
template <RotationSequence sequence, RotationType rotation_type, typename In_Frame_T, typename Out_Frame_T>
CartesianVector<decltype(MomentOfInertia{} * AngularVelocity{}), In_Frame_T>
    operator*(const InertiaTensor<In_Frame_T>& inertiaTensor, const AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>& vec)
{

    return { inertiaTensor[0, 0] * vec[0] + inertiaTensor[0, 1] * vec[1] + inertiaTensor[0, 2] * vec[2],
             inertiaTensor[1, 0] * vec[0] + inertiaTensor[1, 1] * vec[1] + inertiaTensor[1, 2] * vec[2],
             inertiaTensor[2, 0] * vec[0] + inertiaTensor[2, 1] * vec[1] + inertiaTensor[2, 2] * vec[2] };
}

/**
 * @brief Class representing the angular sequence acceleration, which is the time derivative of the angular sequence velocity.
 *
 * @tparam sequence The specific sequence of rotations (e.g., RotationSequence::ZXZ).
 * @tparam type Whether the sequence is intrinsic or extrinsic.
 * @tparam In_Frame_T The input frame type (e.g., ECI, ECEF).
 * @tparam Out_Frame_T The output frame type (e.g., ECI, ECEF).
 */
template <RotationSequence sequence, RotationType rotation_type, typename In_Frame_T, typename Out_Frame_T>
class AngleSequenceAcceleration {

    friend class Attitude;

  public:
    using in_frame  = In_Frame_T;
    using out_frame = Out_Frame_T;

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
        _angularAccels(accel1, accel2, accel3)
    {
    }

    /**
     * @brief Constructor for the AngleSequenceAcceleration class from a CartesianVector of angular accelerations.
     *
     * @param accels A CartesianVector containing the three angular accelerations in the sequence.
     */
    AngleSequenceAcceleration(const CartesianVector<AngularAcceleration, In_Frame_T>& accels) :
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
     * @return CartesianVector<AngularAcceleration, In_Frame_T>& Reference to the internal CartesianVector.
     */
    CartesianVector<AngularAcceleration, In_Frame_T>& get_angularAccels() { return _angularAccels; }

    /**
     * @brief Get const access to the underlying CartesianVector.
     *
     * @return const CartesianVector<AngularAcceleration, In_Frame_T>& Const reference to the internal CartesianVector.
     */
    const CartesianVector<AngularAcceleration, In_Frame_T>& get_angularAccels() const { return _angularAccels; }

    /**
     * @brief Addition operator for AngleSequenceAcceleration.
     *
     * @param other The other AngleSequenceAcceleration to add.
     * @return AngleSequenceAcceleration<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new
     * AngleSequenceAcceleration that is the sum of this and other.
     */
    AngleSequenceAcceleration<sequence, rotation_type, In_Frame_T, Out_Frame_T>
        operator+(const AngleSequenceAcceleration<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other) const
    {
        return { _angularAccels + other._angularAccels };
    }

    /**
     * @brief Addition assignment operator for AngleSequenceAcceleration.
     *
     * @param other The other AngleSequenceAcceleration to add.
     * @return AngleSequenceAcceleration<sequence, rotation_type, In_Frame_T, Out_Frame_T>& Reference to the current object after addition.
     */
    AngleSequenceAcceleration<sequence, rotation_type, In_Frame_T, Out_Frame_T>&
        operator+=(const AngleSequenceAcceleration<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other)
    {
        _angularAccels += other._angularAccels;
        return *this;
    }

    /**
     * @brief Subtraction operator for AngleSequenceAcceleration.
     *
     * @param other The other AngleSequenceAcceleration to subtract.
     * @return AngleSequenceAcceleration<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new
     * AngleSequenceAcceleration that is the difference of this and other.
     */
    AngleSequenceAcceleration<sequence, rotation_type, In_Frame_T, Out_Frame_T>
        operator-(const AngleSequenceAcceleration<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other) const
    {
        return { _angularAccels - other._angularAccels };
    }

    /**
     * @brief Subtraction assignment operator for AngleSequenceAcceleration.
     *
     * @param other The other AngleSequenceAcceleration to subtract.
     * @return AngleSequenceAcceleration<sequence, rotation_type, In_Frame_T, Out_Frame_T>& Reference to the current object after subtraction.
     */
    AngleSequenceAcceleration<sequence, rotation_type, In_Frame_T, Out_Frame_T>&
        operator-=(const AngleSequenceAcceleration<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other)
    {
        _angularAccels -= other._angularAccels;
        return *this;
    }

    /**
     * @brief Scalar multiplication operator for AngleSequenceAcceleration by a quantity, resulting in a CartesianVector.
     *
     * @param scalar The quantity to multiply by.
     * @return CartesianVector<decltype(AngularAcceleration{} * Value_U{}), In_Frame_T> A new
     * CartesianVector that is the product of this sequence and the quantity.
     */
    template <typename Value_U>
    CartesianVector<decltype(AngularAcceleration{} * Value_U{}), In_Frame_T> operator*(const Value_U& scalar) const
    {
        return { _angularAccels * scalar };
    }

    /**
     * @brief Scalar multiplication operator for AngleSequenceAcceleration.
     *
     * @param time The time value to multiply with.
     * @return AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new
     * AngleSequenceVelocity that is the product of this sequence and the time
     */
    AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T> operator*(const Time& time) const
    {
        return { _angularAccels * time };
    }

    /**
     * @brief Scalar division operator for AngleSequenceAcceleration by a quantity, resulting in a CartesianVector.
     *
     * @param scalar The quantity to divide by.
     * @return CartesianVector<decltype(AngularAcceleration{} / Value_U{}), In_Frame_T> A new
     * CartesianVector that is the quotient of this sequence and the quantity.
     */
    template <typename Value_U>
    CartesianVector<decltype(AngularAcceleration{} / Value_U{}), In_Frame_T> operator/(const Value_U& scalar) const
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
    auto dot(const CartesianVector<Value_U, In_Frame_T>& other) const
    {
        return _angularAccels.dot(other);
    }

    /**
     * @brief Dot product of this angle vector with another AngleSequenceAcceleration.
     *
     * @param other The other AngleSequenceAcceleration to take the dot product with.
     * @return auto The resulting scalar from the dot product.
     */
    auto dot(const AngleSequenceAcceleration<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other) const
    {
        return _angularAccels.dot(other._angularAccels);
    }

    /**
     * @brief Cross product of this angular acceleration vector with a CartesianVector.
     *
     * @tparam Value_U The type of the CartesianVector's components.
     * @param other The CartesianVector to take the cross product with.
     * @return CartesianVector<decltype(AngularAcceleration{} * Value_U{}), In_Frame_T> The resulting CartesianVector from the cross product.
     */
    template <typename Value_U>
    CartesianVector<decltype(AngularAcceleration{} * Value_U{}), In_Frame_T>
        cross(const CartesianVector<Value_U, In_Frame_T>& other) const
    {
        return _angularAccels.cross(other);
    }

    /**
     * @brief Cross product of this angle vector with another AngleSequenceAcceleration.
     *
     * @param other The other AngleSequenceAcceleration to take the cross product with.
     * @return CartesianVector<decltype(AngularAcceleration{} * AngularAcceleration{}), In_Frame_T> The resulting CartesianVector from the cross product.
     */
    CartesianVector<decltype(AngularAcceleration{} * AngularAcceleration{}), In_Frame_T>
        cross(const AngleSequenceAcceleration<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other) const
    {
        return _angularAccels.cross(other._angularAccels);
    }

    /**
     * @brief Converts the angular sequence acceleration to a vector form for use in numerical integration.
     *
     * @return A std::vector of Unitless quantities representing the components of the angular sequence acceleration, in the order [first, second, third].
     */
    std::vector<Unitless> force_to_vector() const
    {
        return { _angularAccels[0] / _angularAccels[0].unit,
                 _angularAccels[1] / _angularAccels[1].unit,
                 _angularAccels[2] / _angularAccels[2].unit };
    }

  private:
    CartesianVector<AngularAcceleration, In_Frame_T> _angularAccels;
};

/**
 * @brief Scalar multiplication operator for a quantity multiplied by AngleSequenceAcceleration, resulting in a CartesianVector.
 *
 * @tparam Value_U The type of the scalar quantity.
 * @tparam sequence The specific sequence of rotations.
 * @tparam type Whether the sequence is intrinsic or extrinsic.
 * @tparam In_Frame_T The input frame type.
 * @tparam Out_Frame_T The output frame type.
 * @param scalar The quantity to multiply with.
 * @param accel The AngleSequenceAcceleration to multiply.
 * @return CartesianVector<decltype(Value_U{} * AngularAcceleration{}), In_Frame_T> The resulting CartesianVector.
 */
template <typename Value_U, RotationSequence sequence, RotationType rotation_type, typename In_Frame_T, typename Out_Frame_T>
CartesianVector<decltype(Value_U{} * AngularAcceleration{}), In_Frame_T>
    operator*(const Value_U& scalar, const AngleSequenceAcceleration<sequence, rotation_type, In_Frame_T, Out_Frame_T>& accel)
{
    return { scalar * accel.get_angularAccels() };
}

/**
 * @brief Scalar multiplication operator for Time multiplied by AngleSequenceAcceleration, resulting in an AngleSequenceVelocity.
 *
 * @tparam sequence The specific sequence of rotations.
 * @tparam type Whether the sequence is intrinsic or extrinsic.
 * @tparam In_Frame_T The input frame type.
 * @tparam Out_Frame_T The output frame type.
 * @param time The time value to multiply with.
 * @param accel The AngleSequenceAcceleration to multiply.
 * @return AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T> The resulting AngleSequenceVelocity.
 */
template <RotationSequence sequence, RotationType rotation_type, typename In_Frame_T, typename Out_Frame_T>
AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>
    operator*(const Time& time, const AngleSequenceAcceleration<sequence, rotation_type, In_Frame_T, Out_Frame_T>& accel)
{
    return { time * accel.get_angularAccels() };
}

/**
 * @brief Output stream operator for AngleSequenceVelocity.
 *
 * @tparam sequence The specific sequence of rotations (e.g., RotationSequence::ZXZ).
 * @tparam type Whether the sequence is intrinsic or extrinsic.
 * @tparam In_Frame_T The input frame type (e.g., ECI, ECEF).
 * @tparam Out_Frame_T The output frame type (e.g., ECI, ECEF).
 * @param os The output stream to write to.
 * @param angleSequenceRate The AngleSequenceVelocity to output.
 * @return std::ostream& The output stream after writing the AngleSequenceVelocity.
 */
template <RotationSequence sequence, RotationType rotation_type, typename In_Frame_T, typename Out_Frame_T>
std::ostream& operator<<(std::ostream& os, const AngleSequenceVelocity<sequence, rotation_type, In_Frame_T, Out_Frame_T>& angleSequenceRate)
{
    os << "[" << angleSequenceRate[0] << " , " << angleSequenceRate[1] << " , " << angleSequenceRate[2] << "]";
    return os;
}

/**
 * @brief Output stream operator for AngleSequenceAcceleration.
 *
 * @tparam sequence The specific sequence of rotations (e.g., RotationSequence::ZXZ).
 * @tparam type Whether the sequence is intrinsic or extrinsic.
 * @tparam In_Frame_T The input frame type (e.g., ECI, ECEF).
 * @tparam Out_Frame_T The output frame type (e.g., ECI, ECEF).
 * @param os The output stream to write to.
 * @param angleSequenceAccel The AngleSequenceAcceleration to output.
 * @return std::ostream& The output stream after writing the AngleSequenceAcceleration.
 */
template <RotationSequence sequence, RotationType rotation_type, typename In_Frame_T, typename Out_Frame_T>
std::ostream& operator<<(std::ostream& os, const AngleSequenceAcceleration<sequence, rotation_type, In_Frame_T, Out_Frame_T>& angleSequenceAccel)
{
    os << "[" << angleSequenceAccel[0] << " , " << angleSequenceAccel[1] << " , " << angleSequenceAccel[2] << "]";
    return os;
}

} // namespace astro
} // namespace astrea