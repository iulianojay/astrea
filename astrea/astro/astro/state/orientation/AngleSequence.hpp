/**
 * @file EulerAngles.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Class representing Euler angles for orientation transformations between state/frames.
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
#include <astro/types/enums.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Concept to check if two AngleSequences can be added/subtracted safely
 */
template <typename Sequence_T, Sequence_T sequence_t, RotationSequenceType rotation_t, typename In_Frame_T, typename Out_Frame_T, typename Sequence_U, Sequence_U sequence_u, RotationSequenceType rotation_u, typename In_Frame_U, typename Out_Frame_U>
concept IsCompatibleAngleSequence =
    std::is_same_v<Sequence_T, Sequence_U> && // Must both be the same sequence type (Euler or Tait-Bryan)
    (sequence_t == sequence_u) &&             // Must both be the same specific sequence (e.g., ZXZ)
    (rotation_t == rotation_u) &&             // Must both be the same rotation type (intrinsic or extrinsic)
    IsSameFrame<In_Frame_T, In_Frame_U> &&    // Must have the same input frame
    IsSameFrame<Out_Frame_T, Out_Frame_U>;    // Must have the same output frame

/**
 * @brief Class representing a sequence of angles (either Euler or Tait-Bryan) for orientation transformations between frames.
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
    requires(std::same_as<Sequence_T, EulerSequence> || std::same_as<Sequence_T, TaitBryanSequence> && !IsSameFrame<In_Frame_T, Out_Frame_T>)
class AngleSequence {

    friend State;

  public:
    /**
     * @brief Default constructor for the AngleSequence class. Initializes all angles to zero.
     */
    AngleSequence() = default;

    /**
     * @brief Constructor for the AngleSequence class from three angles.
     *
     * @param angle1 The first angle in the sequence.
     * @param angle2 The second angle in the sequence.
     * @param angle3 The third angle in the sequence.
     */
    AngleSequence(const Angle& angle1, const Angle& angle2, const Angle& angle3) :
        _angles(angle1, angle2, angle3)
    {
        wrap_angles();
    }

    /**
     * @brief Constructor for the AngleSequence class from a CartesianVector of angles.
     *
     * @param angles A CartesianVector containing the three angles in the sequence.
     */
    AngleSequence(const CartesianVector<Angle, In_Frame_T>& angles) :
        _angles(angles)
    {
        wrap_angles();
    }

    /**
     * @brief Converts the angle sequence to a direction cosine matrix (DCM) for transforming vectors between frames.
     *
     * @return DirectionCosineMatrix<In_Frame_T, Out_Frame_T> The resulting direction cosine matrix.
     */
    DirectionCosineMatrix<In_Frame_T, Out_Frame_T> to_dcm() const
    {
        // Extrinsic sequences are applied in the order they are specified, while intrinsic sequences are applied in reverse order
        const Angle& first  = ([&] {
            if constexpr (rotationType == RotationSequenceType::INTRINSIC) { return _angles[0]; }
            else {
                return _angles[2];
            }
        }());
        const Angle& second = _angles[1];
        const Angle& third  = ([&] {
            if constexpr (rotationType == RotationSequenceType::INTRINSIC) { return _angles[2]; }
            else {
                return _angles[0];
            }
        }());

        return to_dcm_impl<Sequence_T>(first, second, third);
    }

    // Explicitly deleted copy/move assignment/constructor to prevent implicit frame switches, rotation type conversions, and sequence conversions.
    template <typename Sequence_U, Sequence_U sequence_u, RotationSequenceType rotationType_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsCompatibleAngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T, Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>)
    AngleSequence(const AngleSequence<Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>& other) = delete;

    template <typename Sequence_U, Sequence_U sequence_u, RotationSequenceType rotationType_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsCompatibleAngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T, Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>)
    AngleSequence(AngleSequence<Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>&& other) = delete;

    template <typename Sequence_U, Sequence_U sequence_u, RotationSequenceType rotationType_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsCompatibleAngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T, Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>)
    AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>&
        operator=(const AngleSequence<Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>& other) = delete;

    template <typename Sequence_U, Sequence_U sequence_u, RotationSequenceType rotationType_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsCompatibleAngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T, Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>)
    AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>&
        operator=(AngleSequence<Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>&& other) = delete;

    /**
     * @brief Access operator for vector components.
     *
     * @param index The index of the component to access (0 for x, 1 for y, 2 for z).
     * @return Angle& Reference to the component at the specified index.
     */
    Angle& operator[](size_t index) { return _angles[index]; }

    /**
     * @brief Const access operator for vector components.
     *
     * @param index The index of the component to access (0 for x, 1 for y, 2 for z).
     * @return const Angle& Reference to the component at the specified index.
     */
    const Angle& operator[](size_t index) const { return _angles[index]; }

    /**
     * @brief Equality operator for CartesianVector.
     *
     * @param other The other CartesianVector to compare with.
     * @return true If the two vectors are equal.
     * @return false If the two vectors are not equal.
     */
    bool operator==(const AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& other) const
    {
        return _angles == other._angles;
    }

    /**
     * @brief Inequality operator for CartesianVector in a different frame. Always false.
     *
     * @param other The other CartesianVector to compare with.
     * @return true If the two vectors are not equal.
     * @return false If the two vectors are equal.
     */
    template <typename Sequence_U, Sequence_U sequence_u, RotationSequenceType rotationType_u, typename In_Frame_U, typename Out_Frame_U>
        requires(!IsCompatibleAngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T, Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>)
    bool operator==(const AngleSequence<Sequence_U, sequence_u, rotationType_u, In_Frame_U, Out_Frame_U>& other) const
    {
        return false;
    }

    /**
     * @brief Addition operator for CartesianVector.
     *
     * @param other The other AngleSequence to add.
     * @return AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> A new AngleSequence that is the sum of this sequence and the other.
     */
    AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>
        operator+(const AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& other) const
    {
        return { _angles + other._angles };
    }

    /**
     * @brief Addition assignment operator for AngleSequence.
     *
     * @param other The other AngleSequence to add.
     * @return AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& Reference to the current object after addition.
     */
    AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>&
        operator+=(const AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& other)
    {
        _angles += other._angles;
        wrap_angles();
        return *this;
    }

    /**
     * @brief Subtraction operator for AngleSequence.
     *
     * @param other The other AngleSequence to subtract.
     * @return AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> A new AngleSequence that is the difference of this sequence and the other.
     */
    AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>
        operator-(const AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& other) const
    {
        return { _angles - other._angles };
    }

    /**
     * @brief Negation operator for AngleSequence.
     *
     * @return AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> A new AngleSequence that is the negation of this sequence.
     */
    AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> operator-() const
    {
        return { -_angles };
    }

    /**
     * @brief Subtraction assignment operator for AngleSequence.
     *
     * @param other The other AngleSequence to subtract.
     * @return AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& Reference to the current object after subtraction.
     */
    AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>&
        operator-=(const AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& other)
    {
        _angles -= other._angles;
        wrap_angles();
        return *this;
    }

    /**
     * @brief Scalar multiplication operator for AngleSequence.
     *
     * @param scalar The scalar value to multiply with.
     * @return AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> A new AngleSequence that is the product of this sequence and the scalar.
     */
    AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> operator*(const Unitless& scalar) const
    {
        return { _angles * scalar };
    }

    /**
     * @brief Scalar multiplication assignment operator for AngleSequence.
     *
     * @param scalar The scalar value to multiply with.
     * @return AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& Reference to the current object after multiplication.
     */
    AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& operator*=(const Unitless& scalar)
    {
        _angles *= scalar;
        wrap_angles();
        return *this;
    }

    /**
     * @brief Scalar division operator for AngleSequence by a Time quantity, resulting in an AngularSequenceRate.
     *
     * @param time The time quantity to divide by.
     * @return AngularSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> A new
     * AngularSequenceVelocity that is the quotient of this sequence and the time.
     */
    AngularSequenceVelocity<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> operator/(const Time& time) const
    {
        return { _angles / time };
    }

    /**
     * @brief Scalar division operator for AngleSequence.
     *
     * @param scalar The scalar value to divide by.
     * @return AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> A new AngleSequence that is the quotient of this sequence and the scalar.
     */
    AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> operator/(const Unitless& scalar) const
    {
        return { _angles / scalar };
    }

    /**
     * @brief Scalar division assignment operator for AngleSequence.
     *
     * @param scalar The scalar value to divide by.
     * @return AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& Reference to the current object after division.
     */
    AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& operator/=(const Unitless& scalar)
    {
        _angles /= scalar;
        wrap_angles();
        return *this;
    }

    /**
     * @brief Get the x value of the Cartesian vector.
     *
     * @return Angle& Reference to the x component of the Cartesian vector.
     */
    Angle& get_phi() { return _angles[0]; }

    /**
     * @brief Get the x value of the Cartesian vector.
     *
     * @return const Angle& Reference to the x component of the Cartesian vector.
     */
    const Angle& get_phi() const { return _angles[0]; }

    /**
     * @brief Get the y value of the Cartesian vector.
     *
     * @return Angle& Reference to the y component of the Cartesian vector.
     */
    Angle& get_theta() { return _angles[1]; }

    /**
     * @brief Get the y value of the Cartesian vector.
     *
     * @return const Angle& Reference to the y component of the Cartesian vector.
     */
    const Angle& get_theta() const { return _angles[1]; }

    /**
     * @brief Get the z value of the Cartesian vector.
     *
     * @return Angle& Reference to the z component of the Cartesian vector.
     */
    Angle& get_psi() { return _angles[2]; }

    /**
     * @brief Get the z value of the Cartesian vector.
     *
     * @return const Angle& Reference to the z component of the Cartesian vector.
     */
    const Angle& get_psi() const { return _angles[2]; }

    /**
     * @brief Get the angles as a CartesianVector.
     *
     * @return CartesianVector<Angle, In_Frame_T>& Reference to the angles as a CartesianVector.
     */
    CartesianVector<Angle, In_Frame_T>& get_angles() { return _angles; }

    /**
     * @brief Get the angles as a CartesianVector.
     *
     * @return const CartesianVector<Angle, In_Frame_T>& Reference to the angles as a CartesianVector.
     */
    const CartesianVector<Angle, In_Frame_T>& get_angles() const { return _angles; }

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
        return (_angles.dot(vec)) / cotes_angle;
    }

    /**
     * @brief Dot product of this angle vector with another AngleSequence.
     *
     * @param other The other AngleSequence to take the dot product with.
     * @return Unitless The resulting scalar from the dot product.
     *
     * @note The result is divided by the coates angle to convert from the angle units to the same units as the other
     * vector's components. This is necessary because the resultant scalar is rarely desired in the base units
     * multiplied by radians. If users want that, they can first extract the angle vector and multiply it directly.
     */
    Unitless dot(const AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& other) const
    {
        using namespace mp_units;
        using mp_units::isq_angle::cotes_angle;
        return (_angles.dot(other.get_angles())) / pow<2>(cotes_angle);
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
        return _angles.cross(vec);
    }

    /**
     * @brief Cross product of this angle vector with another AngleSequence.
     *
     * @param other The other AngleSequence to take the cross product with.
     * @return CartesianVector<decltype(mp_units::pow<2>(mp_units::isq_angle::rad)), In_Frame_T> The resulting AngleSequence from the cross product.
     */
    auto cross(const AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& other) const
    {
        return this->cross(other.get_angles());
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
     * @brief Cursed template indirection to resolved the correct DCM construction method based on the sequence type and specific sequence.
     *
     * @tparam Sequence_U The type of angle sequence (EulerSequence).
     * @param first The first angle in the sequence.
     * @param second The second angle in the sequence.
     * @param third The third angle in the sequence.
     * @return DirectionCosineMatrix<In_Frame_T, Out_Frame_T> The resulting direction cosine matrix.
     */
    template <typename Sequence_U>
        requires(std::is_same_v<Sequence_U, EulerSequence>)
    static DirectionCosineMatrix<In_Frame_T, Out_Frame_T> to_dcm_impl(const Angle& first, const Angle& second, const Angle& third)
    {
        // weeeeee
        if constexpr (sequence == EulerSequence::ZXZ) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::ZXZ(first, second, third);
        }
        else if constexpr (sequence == EulerSequence::XYX) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::XYX(first, second, third);
        }
        else if constexpr (sequence == EulerSequence::YZY) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::YZY(first, second, third);
        }
        else if constexpr (sequence == EulerSequence::ZYZ) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::ZYZ(first, second, third);
        }
        else if constexpr (sequence == EulerSequence::XZX) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::XZX(first, second, third);
        }
        else if constexpr (sequence == EulerSequence::YXY) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::YXY(first, second, third);
        }
    }

    /**
     * @brief Cursed template indirection to resolved the correct DCM construction method based on the sequence type and specific sequence.
     *
     * @tparam Sequence_U The type of angle sequence (TaitBryanSequence).
     * @param first The first angle in the sequence.
     * @param second The second angle in the sequence.
     * @param third The third angle in the sequence.
     * @return DirectionCosineMatrix<In_Frame_T, Out_Frame_T> The resulting direction cosine matrix.
     */
    template <typename Sequence_U>
        requires(std::is_same_v<Sequence_U, TaitBryanSequence>)
    static DirectionCosineMatrix<In_Frame_T, Out_Frame_T> to_dcm_impl(const Angle& first, const Angle& second, const Angle& third)
    {
        if constexpr (sequence == TaitBryanSequence::XYZ) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::XYZ(first, second, third);
        }
        else if constexpr (sequence == TaitBryanSequence::YZX) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::YZX(first, second, third);
        }
        else if constexpr (sequence == TaitBryanSequence::ZXY) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::ZXY(first, second, third);
        }
        else if constexpr (sequence == TaitBryanSequence::XZY) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::XZY(first, second, third);
        }
        else if constexpr (sequence == TaitBryanSequence::ZYX) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::ZYX(first, second, third);
        }
        else if constexpr (sequence == TaitBryanSequence::YXZ) {
            return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>::YXZ(first, second, third);
        }
    }

    /**
     * @brief Constructs an AngleSequence from a vector of Unitless quantities representing the angle components.
     *
     * @param vec A std::vector of Unitless quantities representing the components of the angle sequence, in the order [first, second, third].
     * @return A new AngleSequence constructed from the given vector.
     *
     * @throws std::invalid_argument if the input vector does not have exactly 3 components.
     */
    static AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> from_vector(const std::vector<Unitless>& vec)
    {
        using mp_units::angular::unit_symbols::rad;

        if (vec.size() != 3) {
            throw std::invalid_argument("Input vector must have exactly 3 components to convert to an AngleSequence.");
        }
        return { vec[0] * rad, vec[1] * rad, vec[2] * rad };
    }
};

/**
 * @brief Scalar multiplication operator for AngleSequences.
 *
 * @tparam T The type of the vector components.
 * @tparam U The type of the scalar to multiply with.
 * @param scalar The scalar value to multiply with.
 * @param vec The AngleSequence to multiply.
 * @return AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> A new AngleSequence that is the product of the scalar and the vector.
 */
template <typename Sequence_T, Sequence_T sequence, RotationSequenceType rotationType, typename In_Frame_T, typename Out_Frame_T>
AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>
    operator*(const Unitless& scalar, const AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& vec)
{
    return vec * scalar;
}

/**
 * @brief Scalar division operator for AngleSequences.
 *
 * @tparam T The type of the vector components.
 * @tparam U The type of the scalar to divide by.
 * @param scalar The scalar value to divide by.
 * @param vec The AngleSequence to divide.
 * @return AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T> A new AngleSequence that is the quotient of the scalar and the vector.
 */
template <typename Sequence_T, Sequence_T sequence, RotationSequenceType rotationType, typename In_Frame_T, typename Out_Frame_T>
AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>
    operator/(const Unitless& scalar, const AngleSequence<Sequence_T, sequence, rotationType, In_Frame_T, Out_Frame_T>& vec)
{
    return vec / scalar;
}

// Typdefs to make life not as terrible
template <EulerSequence sequence, RotationSequenceType rotationType, typename In_Frame_T, typename Out_Frame_T>
using EulerAngles = AngleSequence<EulerSequence, sequence, rotationType, In_Frame_T, Out_Frame_T>;

template <EulerSequence sequence, typename In_Frame_T, typename Out_Frame_T>
using IntrinsicEulerAngles = EulerAngles<sequence, RotationSequenceType::INTRINSIC, In_Frame_T, Out_Frame_T>;

template <EulerSequence sequence, typename In_Frame_T, typename Out_Frame_T>
using ExtrinsicEulerAngles = EulerAngles<sequence, RotationSequenceType::EXTRINSIC, In_Frame_T, Out_Frame_T>;


template <TaitBryanSequence sequence, RotationSequenceType rotationType, typename In_Frame_T, typename Out_Frame_T>
using TaitBryanAngles = AngleSequence<TaitBryanSequence, sequence, rotationType, In_Frame_T, Out_Frame_T>;

template <TaitBryanSequence sequence, typename In_Frame_T, typename Out_Frame_T>
using IntrinsicTaitBryanAngles = TaitBryanAngles<sequence, RotationSequenceType::INTRINSIC, In_Frame_T, Out_Frame_T>;

template <TaitBryanSequence sequence, typename In_Frame_T, typename Out_Frame_T>
using ExtrinsicTaitBryanAngles = TaitBryanAngles<sequence, RotationSequenceType::EXTRINSIC, In_Frame_T, Out_Frame_T>;

} // namespace astro
} // namespace astrea