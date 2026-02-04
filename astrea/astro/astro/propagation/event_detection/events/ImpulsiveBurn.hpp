/**
 * @file ImpulsiveBurn.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A class representing a null Event in the astrea astro platform.
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

#include <string>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

/**
 * @brief A class representing an impulsive burn Event. It triggers when the true anomaly wraps around (i.e. at
 * perigee), and applies the total impulsive delta-v from all thrusters to the vehicle in the velocity direction.
 * TODO: Generalize to a scheduler of some sort and other burn triggers.
 * TODO: Generalize burn direction.
 * TODO: Generalize which thrusters burn.
 */
class ImpulsiveBurn {

  public:
    /**
     * @brief Gets the name of the Event.
     *
     * @return std::string The name of the Event.
     */
    std::string get_name() const;

    /**
     * @brief Measures the anomaly as a trigger.
     *
     * @param vehicle The Vehicle to check.
     * @return true If the Event is triggered by the Vehicle.
     * @return false If the Event is not triggered by the Vehicle.
     */
    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const;

    /**
     * @brief Triggers an impulsive burn.
     *
     * @param vehicle The Vehicle to trigger the action on.
     */
    void trigger_action(Vehicle& vehicle) const;

    /**
     * @brief Checks if the Event is a terminal Event.
     *
     * @return true If the Event is a terminal Event.
     * @return false If the Event is not a terminal Event.
     */
    bool is_terminal() const;

  private:
    mutable Angle previousAnomaly = 0.0 * astrea::detail::angle_unit;
};

} // namespace astro
} // namespace astrea