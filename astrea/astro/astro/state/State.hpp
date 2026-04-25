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

#include <astro/frames/instances/dynamic_body_frame.hpp>
#include <astro/state/attitude/Attitude.hpp>
#include <astro/state/attitude/instances/Quaternion.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing the state of an astronomical object.
 * This class encapsulates the orbital elements, epoch, and the astrodynamics system
 * that the state belongs to. It also optionally includes the attitude of the object as a quaternion.
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
     * @param attitude The attitude of the state, represented as a quaternion.
     */
    State(const OrbitalElements& elements, const Date& epoch, const AstrodynamicsSystem& sys, const std::optional<Attitude>& attitude = std::nullopt) :
        _elements(elements),
        _epoch(epoch),
        _system(&sys),
        _attitude(attitude)
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
    State(const OrbitalElements&, const Date&, AstrodynamicsSystem&&, const std::optional<Attitude>&) = delete;

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
     * @brief Get the attitude of the state.
     *
     * @return std::optional<Attitude> The attitude of the state.
     */
    const std::optional<Attitude>& get_attitude() const { return _attitude; }

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
    RadiusVector<frames::primary> get_position() const
    {
        return in_element_set<Cartesian<frames::primary>>().get_position();
    }

    /**
     * @brief Gets the position vector in a specified frame from the state.
     *
     * @tparam Frame_T The frame to get the position vector in.
     * @return RadiusVector<Frame_T> The position vector of the state in the specified frame.
     */
    template <typename Frame_T>
    RadiusVector<Frame_T> get_position_in_frame(const Date& date) const
    {
        return get_position().template in_frame<Frame_T>(date);
    }

    /**
     * @brief Gets the velocity vector from the state.
     *
     * @return VelocityVector<frames::earth::icrf> The velocity vector of the state.
     */
    VelocityVector<frames::primary> get_velocity() const
    {
        return in_element_set<Cartesian<frames::primary>>().get_velocity();
    }

    /**
     * @brief Gets the velocity vector in a specified frame from the state.
     *
     * @tparam Frame_T The frame to get the velocity vector in.
     * @return VelocityVector<Frame_T> The velocity vector of the state in the specified frame.
     */
    template <typename Frame_T>
    VelocityVector<Frame_T> get_velocity_in_frame(const Date& date) const
    {
        return get_velocity().template in_frame<Frame_T>(date);
    }

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
     * @brief Sets the attitude of the state.
     *
     * @param attitude The new attitude to set.
     */
    void set_attitude(const Attitude& attitude) { _attitude = attitude; }

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
    OrbitalElements _elements; //!< The orbital elements of the state, defining the shape and attitude of the orbit.
    Date _epoch; //!< The epoch of the state, representing the time at which the orbital elements are defined.
    const AstrodynamicsSystem* _system; //!< Pointer to the astrodynamics system associated with the state, providing context for the orbital elements.
    std::optional<Attitude> _attitude; //!< The attitude of the state, represented as a quaternion.

    /**
     * @brief Gets the gravitational parameter (mu) of the central body in the astrodynamics system.
     *
     * @return GravParam The gravitational parameter (mu) of the central body, or zero if no system is associated.
     */
    GravParam get_mu() const
    {
        return _system ? _system->get_mu() : GravParam::zero();
    }

    /**
     * @brief Converts the State to a vector of Unitless values.
     *
     * @return std::vector<Unitless> Vector containing the orbital elements as unitless values.
     */
    std::vector<Unitless> force_to_vector() const
    {
        auto retval = _elements.force_to_vector();
        if (_attitude.has_value()) {
            const auto& attitudeVector = _attitude->force_to_vector();
            retval.insert(retval.end(), attitudeVector.begin(), attitudeVector.end());
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
     * @param epoch The epoch of the state.
     * @param sys The astrodynamics system associated with the state.
     * @param elementPartials The orbital element partials of the state.
     * @param attitudePartial The attitude partial of the state, represented as a quaternion derivative.
     */
    StatePartial(
        const Date& epoch,
        const AstrodynamicsSystem& sys,
        const OrbitalElementPartials& elementPartials,
        const std::optional<AttitudePartials>& attitudePartial = std::nullopt
    ) :
        _epoch(epoch),
        _system(&sys),
        _elementPartials(elementPartials),
        _attitudePartial(attitudePartial)
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

    /**
     * @brief Converts the State to a vector of Unitless values.
     *
     * @return std::vector<Unitless> Vector containing the orbital element partials and attitude partials as unitless values.
     */
    std::vector<Unitless> force_to_vector() const
    {
        auto retval = _elementPartials.force_to_vector();
        if (_attitudePartial.has_value()) {
            const auto& attitudeVector = _attitudePartial->force_to_vector();
            retval.insert(retval.end(), attitudeVector.begin(), attitudeVector.end());
        }
        return retval;
    }

  private:
    Date _epoch; //!< The epoch of the state partial, representing the time at which the orbital elements are defined.
    const AstrodynamicsSystem* _system; //!< Pointer to the astrodynamics system associated with the state, providing context for the orbital elements.
    OrbitalElementPartials _elementPartials; //!< The orbital element partials of the state, defining the shape and attitude of the orbit.
    std::optional<AttitudePartials> _attitudePartial; //!< The attitude partial of the state, represented as a quaternion derivative.
};

} // namespace astro
} // namespace astrea