/**
 * @file State.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Class representing the state of an astronomical object
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <iosfwd>

#include <astro/state/angular_elements/AngularElements.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing the state of an astronomical object.
 * * This class encapsulates the orbital elements, epoch, and the astrodynamics system
 * * that the state belongs to.
 */
class State {

    friend std::ostream& operator<<(std::ostream& os, const State& state);

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
     */
    State(const OrbitalElements& elements, const Date& epoch, const AstrodynamicsSystem& sys);

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
    const OrbitalElements& get_orbit() const { return _orbit; }

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
    void convert_to_orbital_set()
    {
        _orbit.convert_to_orbital_set<T>(get_system());
    }

    /**
     * @brief Converts the state to a different type of orbital elements.
     *
     * @tparam T The type to convert the state to.
     * @return State A new State object with the converted orbital elements.
     */
    template <IsOrbitalElements T>
    State convert_to_orbital_set() const
    {
        return { in_orbital_set<T>(), _epoch, get_system() };
    }

    /**
     * @brief Converts the current orbital elements to a specified type.
     *
     * @param sys The astrodynamics system to use for the conversion.
     * @return The converted orbital elements.
     */
    template <IsOrbitalElements T>
    T in_orbital_set() const
    {
        return _orbit.in_orbital_set<T>(get_system());
    }

    /**
     * @brief Sets the orbital elements of the state.
     *
     * @param orbit The new orbital elements to set.
     */
    template <IsOrbitalElements T>
    void set_elements(const T& orbit, const bool convertToOriginal = false)
    {
        const std::size_t originalIndex = _orbit.index();
        _orbit                          = orbit;
        if (convertToOriginal) { _orbit.convert_to_orbital_set(originalIndex, get_system()); }
    }

  private:
    OrbitalElements _orbit;             //!< Shape and orientation of the orbit.
    AngularElements _orientation;       //!< The orientation and rotation of the object.
    Date _epoch;                        //!< The time at which the elements are defined.
    const AstrodynamicsSystem* _system; //!< Pointer to the astrodynamics system associated with the state
};

} // namespace astro
} // namespace astrea