/**
 * @file State.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Class representing the state of an astronomical object
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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

#include <astro/frames/definitions/dynamic_frames/tags.hpp>
#include <astro/state/attitude/Quaternion.hpp>
#include <astro/state/framework/element_matrix_concepts.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing the state of an astronomical object.
 * This class encapsulates the orbital elements, epoch, and the astrodynamics system
 * that the state belongs to. It also optionally includes the attitude of the object as a quaternion.
 */
template <typename OrbitalElements_T, typename Attitude_T>
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
     * @param attitude The attitude of the state, represented as a quaternion.
     */
    State(const OrbitalElements_T& elements, const Date& epoch, const std::optional<Attitude_T>& attitude = std::nullopt) :
        _elements(elements),
        _epoch(epoch),
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
     * @return const OrbitalElements_T& Reference to the orbital elements of the state.
     */
    const OrbitalElements_T& get_elements() const { return _elements; }

    /**
     * @brief Get the attitude of the state.
     *
     * @return std::optional<Attitude_T> The attitude of the state.
     */
    const std::optional<Attitude_T>& get_attitude() const { return _attitude; }

    /**
     * @brief Gets the epoch of the state.
     *
     * @return const Date& Reference to the epoch of the state.
     */
    const Date& get_epoch() const { return _epoch; }

    /**
     * @brief Gets the gravitational parameter (mu) derived from the origin of the current elements' frame.
     *
     * @return GravParam The gravitational parameter of the central body.
     */
    GravParam get_mu() const
    {
        return std::visit(
            []<typename ElemT>(const ElemT&) -> GravParam {
                return astrea::astro::get_mu<decltype(ElemT::frame)::origin>();
            },
            _elements.extract()
        );
    }

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
     * @brief Converts the state to a different type of orbital elements.
     *
     * @tparam T The type to convert the state to.
     * @return State A new State object with the converted orbital elements.
     */
    template <IsOrbitalElements T>
    State<T, Attitude_T> convert_to_set() const
    {
        return { in_element_set<T>(), _epoch, _attitude };
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
        // TODO: How do we do this?
        // if constexpr (std::is_specialization_v<_elements, Cartesian>) {
        //     // cartesian<a> -> cartesian<b> -> set2<b>
        //     return _elements.template in_frame<T::frame>(_epoch, get_mu()).in_element_set<T>(get_mu());
        // }

        // set1<a> -> set2<a> -> cartesian<a> -> cartesian<b> -> set2<b>
        return _elements.in_element_set<T>(get_mu()).template in_frame<T::frame>(_epoch, get_mu());
    }

    /**
     * @brief Gets the position vector from the state.
     *
     * @return RadiusVector<frames::earth::icrf> The position vector of the state.
     */
    RadiusVector<frames::earth::icrf> get_position() const
    {
        return in_element_set<Cartesian<frames::earth::icrf>>().get_position();
    }

    /**
     * @brief Converts the state to a specified frame.
     *
     * @tparam _frame_ The frame to convert the state to.
     * @return State A new State object with the converted orbital elements.
     */
    template <IsFrame auto _frame_>
    State& in_frame()
    {
        _elements = _elements.in_frame<_frame_>(get_epoch(), get_mu());
        return *this;
    }

    /**
     * @brief Gets the position vector in a specified frame from the state.
     *
     * @tparam _frame_ The frame to get the position vector in.
     * @return RadiusVector<_frame_> The position vector of the state in the specified frame.
     */
    template <IsFrame auto _frame_>
    RadiusVector<_frame_> get_position_in_frame() const
    {
        return get_position().template in_frame<_frame_>(get_epoch());
    }

    /**
     * @brief Gets the velocity vector from the state.
     *
     * @return VelocityVector<frames::earth::icrf> The velocity vector of the state.
     */
    VelocityVector<frames::earth::icrf> get_velocity() const
    {
        return in_element_set<Cartesian<frames::earth::icrf>>().get_velocity();
    }

    /**
     * @brief Gets the velocity vector in a specified frame from the state.
     *
     * @tparam _frame_ The frame to get the velocity vector in.
     * @return VelocityVector<_frame_> The velocity vector of the state in the specified frame.
     */
    template <IsFrame auto _frame_>
    VelocityVector<_frame_> get_velocity_in_frame(const Date& date) const
    {
        return get_velocity().template in_frame<_frame_>(date);
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
    void set_attitude(const Attitude_T& attitude) { _attitude = attitude; }

    /**
     * @brief Sets the epoch of the state.
     *
     * @param epoch The new epoch to set.
     */
    void set_epoch(const Date& epoch) { _epoch = epoch; }

  private:
    OrbitalElements_T _elements; //!< The orbital elements of the state, defining the shape and attitude of the orbit.
    Date _epoch; //!< The epoch of the state, representing the time at which the orbital elements are defined.
    std::optional<Attitude_T> _attitude; //!< The attitude of the state, represented as a quaternion.

    /**
     * @brief Converts the State to a vector of Unitless values.
     *
     * @return auto Vector containing the orbital elements as element array values.
     */
    auto force_to_element_array() const
    {
        auto retval = _elements.force_to_element_array();
        if (_attitude.has_value()) { retval.combine_rows(_attitude->force_to_element_array()); }
        return retval;
    }

    /**
     * @brief Creates an State object from a vector of Unitless values.
     *
     * @param vec The vector of Unitless values.
     * @param idx The index of the orbital element type to create.
     * @return State The created State object.
     */
    template <std::size_t size, typename... Elements_T>
    void update_from_element_array(const ElementMatrix<size, 1, Elements_T...>& array)
    {
        template for (constexpr auto idx : std::make_index_sequence<size>)
        {
            static_assert(std::is_same_v<decltype(array.get<idx>()), decltype(_elements.get<idx>())>, "All elements in the array must be the same type");
            if constexpr (idx < _elements.size()) { _elements.get<idx>() = array.get<idx>(); }
            else { // Assumed that a larger input array means that the attitude is being updated as well
                _attitude->get<idx - _elements.size()>() = array.get<idx>();
            }
        }
    }

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
    StatePartial<OrbitalElements_T, Attitude_T> operator/(const Time& divisor) const;
};

template <typename OrbitalElements_T, typename Attitude_T>
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
    StatePartial(const Date& epoch, const OrbitalElementPartials& elementPartials, const std::optional<AttitudePartials>& attitudePartial = std::nullopt) :
        _epoch(epoch),
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
    State<OrbitalElements_T, Attitude_T> operator*(const Time& time) const;

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
    std::vector<Unitless> force_to_element_array() const
    {
        auto retval = _elementPartials.force_to_element_array();
        if (_attitudePartial.has_value()) { retval.combine_rows(_attitudePartial->force_to_element_array()); }
        return retval;
    }

  private:
    Date _epoch; //!< The epoch of the state partial, representing the time at which the orbital elements are defined.
    OrbitalElementPartials _elementPartials; //!< The orbital element partials of the state, defining the shape and attitude of the orbit.
    std::optional<AttitudePartials> _attitudePartial; //!< The attitude partial of the state, represented as a quaternion derivative.
};

} // namespace astro
} // namespace astrea

#include <astro/state/State.ipp>