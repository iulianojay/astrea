/**
 * @file NullEvent.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A class representing a null Event in the astrea astro platform.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <mp-units/core.h>

#include <astro/platforms/Vehicle.hpp>

namespace astrea {
namespace astro {

/**
 * @brief A class representing a null Event in the astrea astro platform.
 * This class is used as a placeholder for Events that do not have a defined state or mass.
 */
class NullEvent {

  public:
    /**
     * @brief Gets the name of the Event.
     *
     * @return std::string The name of the Event.
     */
    std::string get_name() const { return "NullEvent"; }

    /**
     * @brief Detects if the Event is triggered by a Vehicle.
     *
     * @param vehicle The Vehicle to check.
     * @return true If the Event is triggered by the Vehicle.
     * @return false If the Event is not triggered by the Vehicle.
     */
    Unitless measure_event(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const
    {
        return 1.0 * mp_units::one;
    }

    /**
     * @brief Checks if the Event is a terminal Event.
     *
     * @return true If the Event is a terminal Event.
     * @return false If the Event is not a terminal Event.
     */
    bool is_terminal() const { return false; }
};

} // namespace astro
} // namespace astrea