/**
 * @file EulerAngles.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Class representing a sequence of angles (either Euler or Tait-Bryan) for attitude transformations between state/frames.
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

#include <math/interpolation.hpp>
#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frame_concepts.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/types/enums.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Get the reverse of a Tait-Bryan sequence (e.g., XYZ -> ZYX).
 */
constexpr RotationSequence get_reverse_sequence(RotationSequence sequence)
{
    switch (sequence) {
        case RotationSequence::XYZ: return RotationSequence::ZYX;
        case RotationSequence::YZX: return RotationSequence::XZY;
        case RotationSequence::ZXY: return RotationSequence::YXZ;
        case RotationSequence::XZY: return RotationSequence::YZX;
        case RotationSequence::ZYX: return RotationSequence::XYZ;
        case RotationSequence::YXZ: return RotationSequence::ZXY;
        default:
            // For Euler sequences, the reverse is the same sequence with reversed angles, so we can just return the same sequence type
            return sequence;
    }
}

constexpr bool is_proper_euler_sequence(RotationSequence sequence)
{
    switch (sequence) {
        case RotationSequence::ZXZ:
        case RotationSequence::XYX:
        case RotationSequence::YZY:
        case RotationSequence::ZYZ:
        case RotationSequence::XZX:
        case RotationSequence::YXY: return true;
        default: return false;
    }
}

constexpr std::array<int, 3> get_sequence_numbers(RotationSequence sequence)
{
    switch (sequence) {
        case RotationSequence::ZXZ: return std::array{ 3, 1, 3 };
        case RotationSequence::XZX: return std::array{ 1, 3, 1 };
        case RotationSequence::YXY: return std::array{ 2, 1, 2 };
        case RotationSequence::XYX: return std::array{ 1, 2, 1 };
        case RotationSequence::YZY: return std::array{ 2, 3, 2 };
        case RotationSequence::ZYZ: return std::array{ 3, 2, 3 };
        case RotationSequence::XYZ: return std::array{ 1, 2, 3 };
        case RotationSequence::XZY: return std::array{ 1, 3, 2 };
        case RotationSequence::YZX: return std::array{ 2, 3, 1 };
        case RotationSequence::YXZ: return std::array{ 2, 1, 3 };
        case RotationSequence::ZXY: return std::array{ 3, 1, 2 };
        case RotationSequence::ZYX: return std::array{ 3, 2, 1 };
    }
}

/**
 * @brief Concept to check if two EulerAngless are the same (same sequence type, same specific sequence, same rotation type, and same frames).
 */
template <RotationSequence sequence_t, RotationType rotation_t, typename In_Frame_T, typename Out_Frame_T, RotationSequence sequence_u, RotationType rotation_u, typename In_Frame_U, typename Out_Frame_U>
concept IsSameEulerAngles = (sequence_t == sequence_u) && // Must both be the same specific sequence (e.g., ZXZ)
                            (rotation_t == rotation_u) && // Must both be the same rotation type (intrinsic or extrinsic)
                            IsSameFrame<In_Frame_T, In_Frame_U> && // Must have the same input frame
                            IsSameFrame<Out_Frame_T, Out_Frame_U>; // Must have the same output frame

/**
 * @brief Concept to check if two EulerAngless are equivalent (same sequence type, reverse specific sequence, opposite rotation type, and same frames).
 */
template <RotationSequence sequence_t, RotationType rotation_t, typename In_Frame_T, typename Out_Frame_T, RotationSequence sequence_u, RotationType rotation_u, typename In_Frame_U, typename Out_Frame_U>
concept IsEquivalentEulerAngles =
    (get_reverse_sequence(sequence_t) == sequence_u) && // Must be the reverse sequence (e.g., ZXZ vs ZXZ with reversed angles)
    (rotation_t != rotation_u) &&                       // Must be opposite rotation types (intrinsic vs extrinsic)
    IsSameFrame<In_Frame_T, In_Frame_U> &&              // Must have the same input frame
    IsSameFrame<Out_Frame_T, Out_Frame_U>;              // Must have the same output frame

/**
 * @brief Concept to check if two EulerAngless are compatible (either the same or equivalent).
 *
 * @note Technically, all angle sequences can be represented as all others with the exception of singularities, but we
 * want to prevent implicit conversions between sequences that would lead to very non-obvious bugs. If users want to convert
 * between different sequences, they can do so explicitly through the DCM or by converting to the same rotation type and then using the reverse sequence if desired.
 */
template <RotationSequence sequence_t, RotationType rotation_t, typename In_Frame_T, typename Out_Frame_T, RotationSequence sequence_u, RotationType rotation_u, typename In_Frame_U, typename Out_Frame_U>
concept IsCompatibleEulerAngles =
    IsSameEulerAngles<sequence_t, rotation_t, In_Frame_T, Out_Frame_T, sequence_u, rotation_u, In_Frame_U, Out_Frame_U> ||
    IsEquivalentEulerAngles<sequence_t, rotation_t, In_Frame_T, Out_Frame_T, sequence_u, rotation_u, In_Frame_U, Out_Frame_U>;

/**
 * @brief Class representing a sequence of angles (either Euler or Tait-Bryan) for attitude transformations between frames.
 *
 * @tparam sequence The specific sequence of rotations (e.g., RotationSequence::ZXZ).
 * @tparam type Whether the sequence is intrinsic or extrinsic.
 * @tparam In_Frame_T The input frame type (e.g., ECI, ECEF).
 * @tparam Out_Frame_T The output frame type (e.g., ECI, ECEF).
 *
 * @note: welcome to templating hell
 */
template <RotationSequence sequence, RotationType rotation_type, typename In_Frame_T, typename Out_Frame_T>
class EulerAngles {

    friend class Attitude;

  public:
    using in_frame  = In_Frame_T;
    using out_frame = Out_Frame_T;

    /**
     * @brief Default constructor for the EulerAngles class. Initializes all angles to zero.
     */
    EulerAngles() = default;

    /**
     * @brief Constructor for the EulerAngles class from three angles.
     *
     * @param angle1 The first angle in the sequence.
     * @param angle2 The second angle in the sequence.
     * @param angle3 The third angle in the sequence.
     */
    EulerAngles(const Angle& angle1, const Angle& angle2, const Angle& angle3) :
        _angles(angle1, angle2, angle3)
    {
        wrap_angles();
    }

    /**
     * @brief Constructor for the EulerAngles class from a CartesianVector of angles.
     *
     * @param angles A CartesianVector containing the three angles in the sequence.
     */
    EulerAngles(const CartesianVector<Angle, In_Frame_T>& angles) :
        _angles(angles)
    {
        wrap_angles();
    }

    /**
     * Default copy and move constructors and assignment operators for the same sequence, rotation type, and frames.
     */
    EulerAngles(const EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other)            = default;
    EulerAngles(EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>&& other)                 = default;
    EulerAngles& operator=(const EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other) = default;
    EulerAngles& operator=(EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>&& other)      = default;

    /**
     * Copy and move constructors and assignment operators for equivalent sequences (reverse sequence and opposite rotation type).
     * These allow for implicit conversions between equivalent sequences (e.g., ZXZ extrinsic with angles [x, y, z] to ZXZ intrinsic with angles [z, y, x]).
     */
    template <RotationSequence sequence_u, RotationType rotation_type_u, typename In_Frame_U, typename Out_Frame_U>
        requires IsEquivalentEulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T, sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>
    EulerAngles(const EulerAngles<sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>& other) :
        _angles(other._angles.reverse())
    {
    }

    template <RotationSequence sequence_u, RotationType rotation_type_u, typename In_Frame_U, typename Out_Frame_U>
        requires IsEquivalentEulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T, sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>
    EulerAngles(EulerAngles<sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>&& other) :
        _angles(other._angles.reverse())
    {
    }

    template <RotationSequence sequence_u, RotationType rotation_type_u, typename In_Frame_U, typename Out_Frame_U>
        requires IsEquivalentEulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T, sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>
    EulerAngles& operator=(const EulerAngles<sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>& other)
    {
        _angles = other._angles.reverse();
        return *this;
    }

    template <RotationSequence sequence_u, RotationType rotation_type_u, typename In_Frame_U, typename Out_Frame_U>
        requires IsEquivalentEulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T, sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>
    EulerAngles& operator=(EulerAngles<sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>&& other)
    {
        _angles = other._angles.reverse();
        return *this;
    }

    /**
     * @brief Explicit copy constructor for incompatible sequences (different specific sequence, different rotation type,
     * or different frames). Converts through the DCM to ensure correct transformations between frames and proper handling of singularities.
     *
     * @param other The other EulerAngles to copy from, which must be incompatible with this sequence.
     * @return EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new EulerAngles object that is the result of converting the other sequence to this sequence.
     */
    template <RotationSequence sequence_u, RotationType rotation_type_u>
        requires(!IsCompatibleEulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T, sequence_u, rotation_type_u, In_Frame_T, Out_Frame_T>)
    EulerAngles(const EulerAngles<sequence_u, rotation_type_u, In_Frame_T, Out_Frame_T>& other)
    {
        *this = Quaternion<In_Frame_T, Out_Frame_T>(other).template to_euler_angles<sequence, rotation_type, In_Frame_T, Out_Frame_T>();
    }

    /**
     * @brief Constructs the inverse sequence with the same rotation type.
     *
     * @return EulerAngles<get_reverse_sequence(sequence), rotation_type, Out_Frame_T, In_Frame_T> A new EulerAngles
     *object that is the inverse sequence with the same rotation type and reversed angles. object that is the inverse
     *sequence with the same rotation type and reversed angles.
     **/
    EulerAngles<get_reverse_sequence(sequence), rotation_type, Out_Frame_T, In_Frame_T> get_inverse_sequence() const
    {
        return { -_angles.reverse() };
    }


    /**
     * @brief Array access operator for accessing individual angle components.
     *
     * @param index The index of the angle component (0, 1, or 2).
     * @return Angle& Reference to the angle component.
     */
    Angle& operator[](std::size_t index) { return _angles[index]; }

    /**
     * @brief Const array access operator for accessing individual angle components.
     *
     * @param index The index of the angle component (0, 1, or 2).
     * @return const Angle& Const reference to the angle component.
     */
    const Angle& operator[](std::size_t index) const { return _angles[index]; }

    /**
     * @brief Get access to the underlying CartesianVector.
     *
     * @return CartesianVector<Angle, In_Frame_T>& Reference to the internal CartesianVector.
     */
    CartesianVector<Angle, In_Frame_T>& get_angles() { return _angles; }

    /**
     * @brief Get const access to the underlying CartesianVector.
     *
     * @return const CartesianVector<Angle, In_Frame_T>& Const reference to the internal CartesianVector.
     */
    const CartesianVector<Angle, In_Frame_T>& get_angles() const { return _angles; }

    /**
     * @brief Converts the angle sequence to a direction cosine matrix (DCM) for transforming vectors between frames.
     *
     * @return DirectionCosineMatrix<In_Frame_T, Out_Frame_T> The resulting direction cosine matrix.
     */
    DirectionCosineMatrix<In_Frame_T, Out_Frame_T> to_dcm() const
    {
        // Extrinsic sequences are applied in the order they are specified, while intrinsic sequences are applied in reverse order
        static constexpr bool isIntrinsic = (rotation_type == RotationType::INTRINSIC);

        const Angle& first  = _angles[isIntrinsic ? 2 : 0];
        const Angle& second = _angles[1];
        const Angle& third  = _angles[isIntrinsic ? 0 : 2];

        return to_dcm_impl(first, second, third);
    }

    /**
     * @brief Converts the angle sequence to the opposite rotation type (intrinsic to extrinsic or vice versa) by reversing the order of the angles.
     */
    template <RotationType rotation_u>
        requires(rotation_type != rotation_u)
    EulerAngles<get_reverse_sequence(sequence), rotation_u, In_Frame_T, Out_Frame_T> to_rotation_type() const
    {
        return { _angles };
    }

    /**
     * @brief Converts the angle sequence to the same rotation type (intrinsic to intrinsic or extrinsic to extrinsic).
     * This is a no-op but allows for explicit conversions between different sequences of the same rotation type.
     */
    template <RotationType rotation_u>
        requires(rotation_type == rotation_u)
    auto to_rotation_type() const
    {
        return *this;
    }

    // Explicitly deleted copy/move assignment/constructor to prevent implicit frame switches, rotation type conversions, and sequence conversions.
    template <RotationSequence sequence_u, RotationType rotation_type_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsCompatibleEulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T, sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>)
    EulerAngles(const EulerAngles<sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>& other) = delete;

    template <RotationSequence sequence_u, RotationType rotation_type_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsCompatibleEulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T, sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>)
    EulerAngles(EulerAngles<sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>&& other) = delete;

    template <RotationSequence sequence_u, RotationType rotation_type_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsCompatibleEulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T, sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>)
    EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>&
        operator=(const EulerAngles<sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>& other) = delete;

    template <RotationSequence sequence_u, RotationType rotation_type_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsCompatibleEulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T, sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>)
    EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>&
        operator=(EulerAngles<sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>&& other) = delete;

    /**
     * @brief Equality operator for CartesianVector.
     *
     * @param other The other CartesianVector to compare with.
     * @return true If the two vectors are equal.
     * @return false If the two vectors are not equal.
     */
    bool operator==(const EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other) const
    {
        return _angles == other._angles;
    }

    template <RotationSequence sequence_u, RotationType rotation_type_u, typename In_Frame_U, typename Out_Frame_U>
        requires(IsEquivalentEulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T, sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>)
    bool operator==(const EulerAngles<sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>& other) const
    {
        return _angles == other.get_angles().reverse();
    }

    /**
     * @brief Inequality operator for CartesianVector in a different frame. Always false.
     *
     * @param other The other CartesianVector to compare with.
     * @return true If the two vectors are not equal.
     * @return false If the two vectors are equal.
     */
    template <RotationSequence sequence_u, RotationType rotation_type_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsCompatibleEulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T, sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>)
    bool operator==(const EulerAngles<sequence_u, rotation_type_u, In_Frame_U, Out_Frame_U>& other) const
    {
        return false;
    }

    /**
     * @brief Addition operator for CartesianVector.
     *
     * @param other The other EulerAngles to add.
     * @return EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new EulerAngles that is the sum of this sequence and the other.
     */
    EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>
        operator+(const EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other) const
    {
        return { _angles + other._angles };
    }

    /**
     * @brief Addition assignment operator for EulerAngles.
     *
     * @param other The other EulerAngles to add.
     * @return EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& Reference to the current object after addition.
     */
    EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>&
        operator+=(const EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other)
    {
        _angles += other._angles;
        wrap_angles();
        return *this;
    }

    /**
     * @brief Subtraction operator for EulerAngles.
     *
     * @param other The other EulerAngles to subtract.
     * @return EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new EulerAngles that
     * is the difference of this sequence and the other.
     */
    EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>
        operator-(const EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other) const
    {
        return { _angles - other._angles };
    }

    /**
     * @brief Negation operator for EulerAngles.
     *
     * @return EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new EulerAngles that is the negation of this sequence.
     */
    EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T> operator-() const { return { -_angles }; }

    /**
     * @brief Subtraction assignment operator for EulerAngles.
     *
     * @param other The other EulerAngles to subtract.
     * @return EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& Reference to the current object after subtraction.
     */
    EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>&
        operator-=(const EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other)
    {
        _angles -= other._angles;
        wrap_angles();
        return *this;
    }

    /**
     * @brief Scalar multiplication operator for EulerAngles.
     *
     * @param scalar The scalar value to multiply with.
     * @return EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new EulerAngles that is the product of this sequence and the scalar.
     */
    EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T> operator*(const Unitless& scalar) const
    {
        return { _angles * scalar };
    }

    /**
     * @brief Scalar multiplication assignment operator for EulerAngles.
     *
     * @param scalar The scalar value to multiply with.
     * @return EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& Reference to the current object after multiplication.
     */
    EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& operator*=(const Unitless& scalar)
    {
        _angles *= scalar;
        wrap_angles();
        return *this;
    }

    /**
     * @brief Scalar division operator for EulerAngles by a Time quantity, resulting in an EulerAnglesRate.
     *
     * @param time The time quantity to divide by.
     * @return AngularVelocities<In_Frame_T, Out_Frame_T> A new
     * AngularVelocities that is the quotient of this sequence and the time.
     */
    AngularVelocities<In_Frame_T, Out_Frame_T> operator/(const Time& time) const { return { _angles / time }; }

    /**
     * @brief Scalar division operator for EulerAngles.
     *
     * @param scalar The scalar value to divide by.
     * @return EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new EulerAngles that is the quotient of this sequence and the scalar.
     */
    EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T> operator/(const Unitless& scalar) const
    {
        return { _angles / scalar };
    }

    /**
     * @brief Scalar division assignment operator for EulerAngles.
     *
     * @param scalar The scalar value to divide by.
     * @return EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& Reference to the current object after division.
     */
    EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& operator/=(const Unitless& scalar)
    {
        _angles /= scalar;
        wrap_angles();
        return *this;
    }

    /**
     * @brief Dot product of this angle vector with another EulerAngles.
     *
     * @param other The other EulerAngles to take the dot product with.
     * @return auto The resulting scalar from the dot product.
     */
    auto dot(const EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other) const
    {
        return _angles.dot(other._angles);
    }

    /**
     * @brief Dot product of this angle vector with a generic CartesianVector.
     *
     * @tparam Value_U The value type of the CartesianVector.
     * @param other The CartesianVector to take the dot product with.
     * @return auto The resulting scalar from the dot product.
     */
    template <typename Value_U>
    auto dot(const CartesianVector<Value_U, In_Frame_T>& other) const
    {
        return _angles.dot(other);
    }

    /**
     * @brief Cross product of this angle vector with another EulerAngles.
     *
     * @param other The other EulerAngles to take the cross product with.
     * @return auto The resulting CartesianVector from the cross product.
     */
    auto cross(const EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other) const
    {
        return _angles.cross(other._angles);
    }

    /**
     * @brief Cross product of this angle vector with a generic CartesianVector.
     *
     * @tparam Value_U The value type of the CartesianVector.
     * @param other The CartesianVector to take the cross product with.
     * @return auto The resulting CartesianVector from the cross product.
     */
    template <typename Value_U>
    auto cross(const CartesianVector<Value_U, In_Frame_T>& other) const
    {
        return _angles.cross(other);
    }

    /**
     * @brief Norm of the angle vector.
     *
     * @return Angle The resulting norm of the angle vector.
     */
    Angle norm() const { return _angles.norm(); }

    /**
     * @brief Converts the angle sequence to a vector form for use in numerical integration.
     *
     * @return A std::vector of Unitless quantities representing the components of the angle sequence, in the order [first, second, third].
     */
    std::vector<Unitless> force_to_vector() const
    {
        return { _angles[0] / _angles[0].unit, _angles[1] / _angles[1].unit, _angles[2] / _angles[2].unit };
    }

    /**
     * @brief Interpolates between this angle sequence and another angle sequence at a target time.
     *
     * @param thisTime The time corresponding to this angle sequence.
     * @param otherTime The time corresponding to the other angle sequence.
     * @param other The other angle sequence to interpolate with.
     * @param targetTime The time at which to interpolate the angle sequence.
     * @return EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new EulerAngles that
     * is the interpolation of this sequence and the other at the target time.
     */
    EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T> interpolate(
        const Time& thisTime,
        const Time& otherTime,
        const EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& other,
        const Time& targetTime
    ) const
    {
        static_assert(false, "Don't do this. Just use the Quaternion.");
    }

  private:
    CartesianVector<Angle, In_Frame_T> _angles;

    /**
     * @brief Wraps the angles in the sequence to their appropriate ranges.
     *
     * @note This function uses an assumed convention. I don't really know the limitations of it. Might have to modify
     * it later.
     *  φ - [0, 2π)
     *  θ - [0, π)
     *  ψ - [0, 2π)
     */
    void wrap_angles()
    {
        _angles[0] = wrap_angle(_angles[0]);       // φ - [0, 2π)
        _angles[1] = wrap_angle_to_pi(_angles[1]); // θ - [0, π)
        _angles[2] = wrap_angle(_angles[2]);       // ψ - [0, 2π)
    }

    /**
     * @brief Implementation of the to_dcm function that constructs the direction cosine matrix based on the specific sequence and rotation type.
     *
     * @param first The first angle in the sequence.
     * @param second The second angle in the sequence.
     * @param third The third angle in the sequence.
     * @return DirectionCosineMatrix<In_Frame_T, Out_Frame_T> The resulting direction cosine matrix.
     */
    static constexpr DirectionCosineMatrix<In_Frame_T, Out_Frame_T>
        to_dcm_impl(const Angle& first, const Angle& second, const Angle& third)
    {
        // weeeeee
        if constexpr (sequence == RotationSequence::ZXZ) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::ZXZ(first, second, third);
        }
        else if constexpr (sequence == RotationSequence::XYX) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::XYX(first, second, third);
        }
        else if constexpr (sequence == RotationSequence::YZY) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::YZY(first, second, third);
        }
        else if constexpr (sequence == RotationSequence::ZYZ) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::ZYZ(first, second, third);
        }
        else if constexpr (sequence == RotationSequence::XZX) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::XZX(first, second, third);
        }
        else if constexpr (sequence == RotationSequence::YXY) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::YXY(first, second, third);
        }
        else if constexpr (sequence == RotationSequence::XYZ) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::XYZ(first, second, third);
        }
        else if constexpr (sequence == RotationSequence::YZX) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::YZX(first, second, third);
        }
        else if constexpr (sequence == RotationSequence::ZXY) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::ZXY(first, second, third);
        }
        else if constexpr (sequence == RotationSequence::XZY) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::XZY(first, second, third);
        }
        else if constexpr (sequence == RotationSequence::ZYX) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::ZYX(first, second, third);
        }
        else if constexpr (sequence == RotationSequence::YXZ) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::YXZ(first, second, third);
        }
    }

    /**
     * @brief Constructs an EulerAngles from a vector of Unitless quantities representing the angle components.
     *
     * @param vec A std::vector of Unitless quantities representing the components of the angle sequence, in the order [first, second, third].
     * @return A new EulerAngles constructed from the given vector.
     *
     * @throws std::invalid_argument if the input vector does not have exactly 3 components.
     */
    static EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T> from_vector(const std::vector<Unitless>& vec)
    {
        using mp_units::angular::unit_symbols::rad;

        if (vec.size() != 3) {
            throw std::invalid_argument("Input vector must have exactly 3 components to convert to an EulerAngles.");
        }
        return { vec[0] * rad, vec[1] * rad, vec[2] * rad };
    }
};

/**
 * @brief Scalar multiplication operator for EulerAngless.
 *
 * @tparam T The type of the vector components.
 * @tparam U The type of the scalar to multiply with.
 * @param scalar The scalar value to multiply with.
 * @param vec The EulerAngles to multiply.
 * @return EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new EulerAngles that is the product of the scalar and the vector.
 */
template <RotationSequence sequence, RotationType rotation_type, typename In_Frame_T, typename Out_Frame_T>
EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>
    operator*(const Unitless& scalar, const EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& vec)
{
    return vec * scalar;
}

/**
 * @brief Scalar division operator for EulerAngless.
 *
 * @tparam T The type of the vector components.
 * @tparam U The type of the scalar to divide by.
 * @param scalar The scalar value to divide by.
 * @param vec The EulerAngles to divide.
 * @return EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T> A new EulerAngles that is the quotient of the scalar and the vector.
 */
template <RotationSequence sequence, RotationType rotation_type, typename In_Frame_T, typename Out_Frame_T>
EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>
    operator/(const Unitless& scalar, const EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& vec)
{
    return vec / scalar;
}

/**
 * @brief Output stream operator for EulerAngles
 *
 * @tparam sequence The specific sequence of rotations (e.g., RotationSequence::ZXZ).
 * @tparam type Whether the sequence is intrinsic or extrinsic.
 * @tparam In_Frame_T The input frame type (e.g., ECI, ECEF).
 * @tparam Out_Frame_T The output frame type (e.g., ECI, ECEF).
 * @param os The output stream to write to.
 * @param angleSequence The EulerAngles to output.
 * @return std::ostream& The output stream after writing the EulerAngles.
 */
template <RotationSequence sequence, RotationType rotation_type, typename In_Frame_T, typename Out_Frame_T>
std::ostream& operator<<(std::ostream& os, const EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& angleSequence)
{
    os << "[" << angleSequence[0] << " , " << angleSequence[1] << " , " << angleSequence[2] << "]";
    return os;
}

} // namespace astro
} // namespace astrea