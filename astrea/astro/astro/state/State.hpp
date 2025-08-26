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

#include <iostream>

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
    State(const OrbitalElements& elements, const Date& epoch, const AstrodynamicsSystem& sys) :
        _elements(elements),
        _epoch(epoch),
        _system(&sys)
    {
    }

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
    void convert()
    {
        _elements.convert<T>(get_system());
    }

    /**
     * @brief Converts the state to a different type of orbital elements.
     *
     * @tparam T The type to convert the state to.
     * @return State A new State object with the converted orbital elements.
     */
    template <IsOrbitalElements T>
    State convert() const
    {
        return { _elements.in<T>(get_system()), _epoch, get_system() };
    }

  private:
    Date _epoch; //!< The epoch of the state, representing the time at which the orbital elements are defined.
    OrbitalElements _elements; //!< The orbital elements of the state, defining the shape and orientation of the orbit.
    const AstrodynamicsSystem* _system; //!< Pointer to the astrodynamics system associated with the state, providing context for the orbital elements.
    // Frame frame; // TODO: state/frames
};

} // namespace astro
} // namespace astrea