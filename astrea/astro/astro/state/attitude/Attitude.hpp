/**
 * @file Attitude.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Attitude class and its associated methods.
 * @date 2025-08-02
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

#include <iosfwd>
#include <variant>

#include <units/units.hpp>

// Astro
#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions.hpp>
#include <astro/frames/definitions/dynamic_frames.hpp>
#include <astro/state/attitude/AngularVelocities.hpp>
#include <astro/state/attitude/EulerAngles.hpp>
#include <astro/state/attitude/Quaternion.hpp>
#include <astro/types/type_traits.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/types/variant_util.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Type alias for a ICRF->body quaternion
 */
using BodyQuaternion = Quaternion<frames::dynamic::body, frames::earth::icrf>;

/**
 * @brief Type alias for a ICRF->body quaternion derivative
 */
using BodyQuaternionRate = QuaternionPartial<frames::dynamic::body, frames::earth::icrf>;

/**
 * @brief Type alias for a ICRF->body angle sequence
 */
using BodyAngles = EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, frames::dynamic::body, frames::earth::icrf>;

/**
 * @brief Type alias for a ICRF->body angle sequence velocity
 */
using BodyAngleVelocities = AngularVelocities<frames::dynamic::body, frames::earth::icrf>;

/**
 * @brief Type alias for a ICRF->body angle sequence acceleration
 */
using BodyAngularAcceleration = AngularAccelerations<frames::dynamic::body, frames::earth::icrf>;

/**
 * @brief Concept to check if a type is an attitude type.
 *
 * This concept checks if a type is a valid attitude type, ensuring it meets
 * the requirements for being default constructible, copyable, movable, destructible,
 * and convertible to Quaternion orientation.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept IsAttitude = requires(T) {
    std::is_same<T, remove_cv_ref<T>>::value;
    std::is_default_constructible<T>::value;
    std::is_copy_constructible<T>::value;
    std::is_move_constructible<T>::value;
    std::is_destructible<T>::value;
    requires !std::is_same<T, Attitude>::value;
};

class AttitudePartials; // Forward declaration

/**
 * @brief Class representing a set of orientation.
 *
 * This class encapsulates different types of orientation (EulerAngles, EulerAngles, Quaternion)
 * and provides methods for conversion, interpolation, and mathematical operations.
 */
class Attitude {

    friend std::ostream& operator<<(std::ostream& os, const Attitude& state);
    friend class StateTransitionMatrix;
    friend class State;

  public:
    /**
     * @brief Default constructor initializing to Cartesian<frames::earth::icrf> orientation.
     */
    Attitude() = default;

    /**
     * @brief Constructor initializing with Quaternion orientation.
     *
     * @param orientation The orientation to initialize with.
     */
    Attitude(const BodyQuaternion& orientation, const BodyAngleVelocities& angularVelocity);

    /**
     * @brief Constructor initializing with EulerAngles orientation.
     *
     * @param orientation The orientation to initialize with.
     */
    template <RotationSequence sequence, RotationType rotationType>
    Attitude(const EulerAngles<sequence, rotationType, frames::dynamic::body, frames::earth::icrf>& angleSequence, const BodyAngleVelocities& angleSequenceVelocity) :
        _orientation(angleSequence),
        _angularVelocity(angleSequenceVelocity)
    {
    }

    /**
     * @brief Gets the orientation as a BodyQuaternion.
     *
     * @return const BodyQuaternion& The orientation as a BodyQuaternion.
     */
    const BodyQuaternion& get_orientation() const { return _orientation; }

    /**
     * @brief Gets the angular velocity as a BodyAngleVelocities.
     *
     * @return const BodyAngleVelocities& The angular velocity as a BodyAngleVelocities.
     */
    const BodyAngleVelocities& get_angular_velocity() const { return _angularVelocity; }

    /**
     * @brief Compares two Attitude objects for equality.
     *
     * @param other Another Attitude object to compare with.
     * @return true if the two Attitude objects are equal
     * @return false if the two Attitude objects are not equal
     */
    bool operator==(const Attitude& other) const;

    /**
     * @brief Adds two Attitude objects.
     *
     * @param other Another Attitude object
     * @return Resultant Attitude sum.
     */
    Attitude operator+(const Attitude& other) const;

    /**
     * @brief Adds another Attitude object to the current one.
     *
     * @param other Another Attitude object
     * @return Reference to the current Attitude object after addition.
     */
    Attitude& operator+=(const Attitude& other);

    /**
     * @brief Subtracts another Attitude object from the current one.
     *
     * @param other Another Attitude object
     * @return Resultant Attitude difference.
     */
    Attitude operator-(const Attitude& other) const;

    /**
     * @brief Subtracts another Attitude object from the current one.
     *
     * @param other Another Attitude object
     * @return Reference to the current Attitude object after subtraction.
     */
    Attitude& operator-=(const Attitude& other);

    /**
     * @brief Multiplies the Attitude by a scalar.
     *
     * @param multiplier Scalar value to multiply with
     * @return Resultant Attitude after multiplication.
     */
    Attitude operator*(const Unitless& multiplier) const;

    /**
     * @brief Multiplies the Attitude by a scalar.
     *
     * @param multiplier Scalar value to multiply with
     * @return Reference to the current Attitude object after multiplication.
     */
    Attitude& operator*=(const Unitless& multiplier);

    /**
     * @brief Divides the Attitude by a time.
     *
     * @param divisor Time value to divide by
     * @return Resultant AttitudePartials after division.
     */
    AttitudePartials operator/(const Time& divisor) const;

    /**
     * @brief Converts the Attitude to a vector of Unitless values.
     *
     * @return std::vector<Unitless> Vector containing the orientation as unitless values.
     */
    std::vector<double> force_to_double_vector() const;

    /**
     * @brief Divides the Attitude by a scalar.
     *
     * @param divisor Scalar value to divide with
     * @return Resultant Attitude after division.
     */
    Attitude operator/(const Unitless& divisor) const;

    /**
     * @brief Divides the Attitude by a scalar.
     *
     * @param divisor Scalar value to divide with
     * @return Reference to the current Attitude object after division.
     */
    Attitude& operator/=(const Unitless& divisor);

    /**
     * @brief Interpolates between two Attitude at a given time.
     *
     * @param thisTime Time of the current state
     * @param otherTime Time of the other state
     * @param other Another Attitude object to interpolate with
     * @param targetTime The target time for interpolation
     * @return Interpolated Attitude at the target time.
     */
    Attitude interpolate(const Time& thisTime, const Time& otherTime, const Attitude& other, const Time& targetTime) const;

  private:
    BodyQuaternion _orientation;          //!< Variant holding the orientation
    BodyAngleVelocities _angularVelocity; //!< Variant holding the orientation partials

    /**
     * @brief Creates an Attitude object from a vector of Unitless values.
     *
     * @param vec The vector of Unitless values.
     * @return Attitude The created Attitude object.
     */
    static Attitude from_double_vector(const std::vector<double>& vec);
};

/**
 * @brief Class representing partial derivatives of orientation.
 *
 * This class encapsulates the partial derivatives of orientation, allowing for
 * operations such as multiplication by time to obtain Cartesian<frames::earth::icrf> state vectors.
 */
class AttitudePartials {

    friend std::ostream& operator<<(std::ostream& os, const AttitudePartials& state);

    friend class StatePartial;

  public:
    /**
     * @brief Default constructor initializing to CartesianPartial orientation.
     */
    AttitudePartials() = default;

    /**
     * @brief Constructor initializing with CartesianPartial orientation.
     *
     * @param orientationRate The orbital element partials to initialize with.
     * @param angularAcceleration The angular acceleration to initialize with.
     */
    AttitudePartials(const BodyQuaternionRate& orientationRate, const BodyAngularAcceleration& angularAcceleration);

    /**
     * @brief Multiplies the AttitudePartials by a time to get an Attitude.
     *
     * @param time The time to multiply the partials with.
     * @return A reference to the current attitude partials after conversion.
     */
    Attitude operator*(const Time& time) const;

    /**
     * @brief Converts the AttitudePartials to a vector of Unitless values.
     *
     * @return std::vector<Unitless> Vector containing the orientation as unitless values.
     */
    std::vector<double> force_to_double_vector() const;

  private:
    BodyQuaternionRate _orientationRate; //!< Partial derivatives of the orientation, represented as a quaternion rate
    BodyAngularAcceleration _angularAcceleration; //!< Partial derivatives of the angular velocity, represented as an angular acceleration
};

} // namespace astro
} // namespace astrea