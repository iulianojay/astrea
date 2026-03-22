/**
 * @file State.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Class representing the state of an astronomical object
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
#include <optional>

#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/state/orientation/Quaternion.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

// Declare a body frame without defining it
namespace frames {
namespace dynamic {

struct body;

} // namespace dynamic
} // namespace frames

namespace {

using BodyQuaternion        = Quaternion<frames::earth::icrf, frames::dynamic::body>;
using BodyQuaternionPartial = QuaternionPartial<frames::earth::icrf, frames::dynamic::body>;

} // namespace

/**
 * @brief Class representing the state of an astronomical object.
 * * This class encapsulates the orbital elements, epoch, and the astrodynamics system
 * * that the state belongs to.
 */
class State {

    friend std::ostream& operator<<(std::ostream& os, const State& state);
    friend class Integrator;
    friend class StateTransitionMatrix;

  public:
    /**
     * @brief Default constructor for State.
     */
    State() = default;

    /**
     * @brief Constructs a State with given orbital elements, epoch, and astrodynamics system.
     *
     * @param elements The orbital elements of the state.
     * @param epoch The epoch of the state.
     * @param sys The astrodynamics system associated with the state.
     * @param orientation The orientation of the state, represented as a quaternion.
     */
    State(const OrbitalElements& elements, const Date& epoch, const AstrodynamicsSystem& sys, const std::optional<BodyQuaternion>& orientation = std::nullopt) :
        _elements(elements),
        _epoch(epoch),
        _system(&sys),
        _orientation(orientation)
    {
    }

    /**
     * @brief Constructs a State from a StateHistory object.
     *
     * @param history The StateHistory object to construct the State from.
     *
     * @note This only works if the StateHistory contains exactly one state.
     */
    State(const StateHistory& history);

    /**
     * @brief Deleted constructor for State to prevent constructing a reference to an AstrodynamicsSystem rvalue
     */
    State(const OrbitalElements&, const Date&, AstrodynamicsSystem&&, const std::optional<BodyQuaternion>&) = delete;

    /**
     * @brief Checks if two State objects are equal.
     *
     * @param other The other State object to compare with.
     * @return true if the two states are equal (same elements and epoch),
     * @return false otherwise.
     */
    bool operator==(const State& other) const;

    /**
     * @brief Gets the orbital elements of the state.
     *
     * @return const OrbitalElements& Reference to the orbital elements of the state.
     */
    const OrbitalElements& get_elements() const { return _elements; }

    /**
     * @brief Gets the epoch of the state.
     *
     * @return const Date& Reference to the epoch of the state.
     */
    const Date& get_epoch() const { return _epoch; }

    /**
     * @brief Gets the astrodynamics system associated with the state.
     *
     * @return const AstrodynamicsSystem& Reference to the astrodynamics system.
     */
    const AstrodynamicsSystem& get_system() const { return *_system; }

    /**
     * @brief Converts the orbital elements to a different type.
     *
     * @tparam T The type to convert the orbital elements to.
     */
    template <IsOrbitalElements T>
    void convert_to_set()
    {
        _elements.convert_to_set<T>(get_mu());
    }

    /**
     * @brief Converts the orbital elements to a different type based on index.
     *
     * @param idx The index of the orbital element type to convert to.
     */
    State& convert_to_set(const std::size_t idx)
    {
        _elements.convert_to_set(idx, get_mu());
        return *this;
    }

    /**
     * @brief Converts the state to a different type of orbital elements based on index.
     *
     * @param idx The index of the orbital element type to convert to.
     * @return State A new State object with the converted orbital elements.
     */
    State convert_to_set(const std::size_t idx) const
    {
        State newState = *this;
        newState._elements.convert_to_set(idx, get_mu());
        return newState;
    }

    /**
     * @brief Converts the state to a different type of orbital elements.
     *
     * @tparam T The type to convert the state to.
     * @return State A new State object with the converted orbital elements.
     */
    template <IsOrbitalElements T>
    State convert_to_set() const
    {
        return { in_element_set<T>(), _epoch, get_system() };
    }

    /**
     * @brief Converts the current orbital elements to a specified type.
     *
     * @param sys The astrodynamics system to use for the conversion.
     * @return The converted orbital elements.
     */
    template <IsOrbitalElements T>
    T in_element_set() const
    {
        return _elements.in_element_set<T>(get_mu());
    }

    /**
     * @brief Gets the position vector from the state.
     *
     * @return RadiusVector<frames::earth::icrf> The position vector of the state.
     */
    RadiusVector<frames::earth::icrf> get_position() const { return in_element_set<Cartesian>().get_position(); }

    /**
     * @brief Gets the velocity vector from the state.
     *
     * @return VelocityVector<frames::earth::icrf> The velocity vector of the state.
     */
    VelocityVector<frames::earth::icrf> get_velocity() const { return in_element_set<Cartesian>().get_velocity(); }

    /**
     * @brief Gets the position vector in a specified frame.
     *
     * @tparam Frame_T The frame type to get the position in.
     * @return RadiusVector<Frame_T> The position vector in the specified frame.
     */
    template <typename Frame_T>
    RadiusVector<Frame_T> get_position_in_frame() const
    {
        return get_position().template in_frame<Frame_T>(_epoch);
    }

    /**
     * @brief Get the orientation of the state as a quaternion.
     *
     * @return std::optional<BodyQuaternion> The orientation of the state,
     * represented as a quaternion. If no orientation is provided, returns an identity quaternion (no rotation).
     */
    const std::optional<BodyQuaternion>& get_orientation() const { return _orientation; }

    /**
     * @brief Sets the orbital elements of the state.
     *
     * @param elements The new orbital elements to set.
     */
    template <IsOrbitalElements T>
    void set_elements(const T& elements, const bool convertToOriginal = false)
    {
        std::size_t originalIndex = _elements.index();
        _elements                 = elements;
        if (convertToOriginal) { _elements.convert_to_set(originalIndex, get_mu()); }
    }

    /**
     * @brief Sets the orientation of the state.
     *
     * @param orientation The new orientation to set.
     */
    void set_orientation(const BodyQuaternion& orientation) { _orientation = orientation; }

    /**
     * @brief Sets the epoch of the state.
     *
     * @param epoch The new epoch to set.
     */
    void set_epoch(const Date& epoch) { _epoch = epoch; }

    /**
     * @brief Sets the astrodynamics system associated with the state.
     *
     * @param sys The new astrodynamics system to set.
     */
    void set_system(const AstrodynamicsSystem& sys) { _system = &sys; }

  private:
    OrbitalElements _elements; //!< The orbital elements of the state, defining the shape and orientation of the orbit.
    Date _epoch; //!< The epoch of the state, representing the time at which the orbital elements are defined.
    const AstrodynamicsSystem* _system; //!< Pointer to the astrodynamics system associated with the state, providing context for the orbital elements.
    std::optional<BodyQuaternion> _orientation; //!< The orientation of the state, represented as a quaternion.

    /**
     * @brief Gets the gravitational parameter (mu) of the central body in the astrodynamics system.
     *
     * @return GravParam The gravitational parameter (mu) of the central body, or zero if no system is associated.
     */
    GravParam get_mu() const
    {
        using namespace mp_units;
        return _system ? _system->get_mu() : 0.0 * pow<3>(astrea::detail::distance_unit) / pow<2>(astrea::detail::time_unit);
    }

    /**
     * @brief Converts the State to a vector of Unitless values.
     *
     * @return std::vector<Unitless> Vector containing the orbital elements as unitless values.
     */
    std::vector<Unitless> force_to_vector() const
    {
        auto retval = _elements.force_to_vector();
        if (_orientation.has_value()) {
            const auto& orientationVector = _orientation->force_to_vector();
            retval.insert(retval.end(), orientationVector.begin(), orientationVector.end());
        }
        return retval;
    }

    /**
     * @brief Creates an State object from a vector of Unitless values.
     *
     * @param vec The vector of Unitless values.
     * @param idx The index of the orbital element type to create.
     * @param sys The astrodynamics system associated with the state.
     * @return State The created State object.
     */
    static State from_vector(const std::vector<Unitless>& vec, const std::size_t idx, const AstrodynamicsSystem& sys);

    /**
     * @brief Adds two State objects together.
     *
     * @param other The other State object to add.
     * @return State The resulting State after addition.
     */
    State operator+(const State& other) const;

    /**
     * @brief Adds another State object to this State object in place.
     *
     * @param other The other State object to add.
     * @return Reference to the current State object after addition.
     */
    State& operator+=(const State& other);

    /**
     * @brief Subtracts another State object from this State object.
     *
     * @param other The other State object to subtract.
     * @return State The resulting State after subtraction.
     */
    State operator-(const State& other) const;

    /**
     * @brief Subtracts another State object from this State object in place.
     *
     * @param other The other State object to subtract.
     * @return Reference to the current State object after subtraction.
     */
    State& operator-=(const State& other);

    /**
     * @brief Multiplies the State by a scalar.
     *
     * @param scalar The scalar to multiply with.
     * @return State The resulting State after multiplication.
     */
    State operator*(const Unitless& scalar) const;

    /**
     * @brief Multiplies the State by a scalar in place.
     *
     * @param scalar The scalar to multiply with.
     * @return Reference to the current State object after multiplication.
     */
    State& operator*=(const Unitless& scalar);

    /**
     * @brief Divides the State by a scalar.
     *
     * @param scalar The scalar to divide by.
     * @return State The resulting State after division.
     */
    State operator/(const Unitless& scalar) const;

    /**
     * @brief Divides the State by a scalar in place.
     *
     * @param scalar The scalar to divide by.
     * @return Reference to the current State object after division.
     */
    State& operator/=(const Unitless& scalar);

    /**
     * @brief Divides the State by a Time to get a StatePartial.
     *
     * @param divisor The Time to divide by.
     * @return StatePartial The resulting StatePartial after division.
     */
    StatePartial operator/(const Time& divisor) const;

    /**
     * @brief Validates that another State object belongs to the same astrodynamics system.
     *
     * @param other The other State object to validate against.
     */
    void validate_system(const State& other) const;
};

class StatePartial {

  public:
    /**
     * @brief Default constructor for StatePartial.
     */
    StatePartial() = default;

    /**
     * @brief Constructs a StatePartial with given orbital element partials and astrodynamics system.
     *
     * @param elementPartials The orbital element partials of the state.
     * @param epoch The epoch of the state.
     * @param sys The astrodynamics system associated with the state.
     * @param orientationPartial The orientation partial of the state, represented as a quaternion derivative.
     */
    StatePartial(
        const OrbitalElementPartials& elementPartials,
        const Date& epoch,
        const AstrodynamicsSystem& sys,
        const std::optional<BodyQuaternionPartial>& orientationPartial = std::nullopt
    ) :
        _elementPartials(elementPartials),
        _epoch(epoch),
        _system(&sys),
        _orientationPartial(orientationPartial)
    {
    }

    /**
     * @brief Multiplies the StatePartial by a time to get a State.
     *
     * @param time The time to multiply with.
     * @return State The resulting State after multiplication.
     */
    State operator*(const Time& time) const;

    /**
     * @brief Gets the astrodynamics system associated with the state.
     *
     * @return const AstrodynamicsSystem& Reference to the astrodynamics system.
     */
    const AstrodynamicsSystem& get_system() const;

    /**
     * @brief Gets the epoch of the state partial.
     *
     * @return const Date& Reference to the epoch of the state partial.
     */
    const Date& get_epoch() const;

  private:
    OrbitalElementPartials _elementPartials; //!< The orbital element partials of the state, defining the shape and orientation of the orbit.
    Date _epoch; //!< The epoch of the state partial, representing the time at which the orbital elements are defined.
    const AstrodynamicsSystem* _system; //!< Pointer to the astrodynamics system associated with the state, providing context for the orbital elements.
    std::optional<BodyQuaternionPartial> _orientationPartial; //!< The orientation partial of the state, represented as a quaternion derivative.
};

} // namespace astro
} // namespace astrea