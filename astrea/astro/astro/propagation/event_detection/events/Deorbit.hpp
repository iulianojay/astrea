/**
 * @file Deorbit.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A class representing a deorbit Event in the astrea astro platform.
 * @date 2026-03-14
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

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

/**
 * @brief A class representing a deorbit Event in the astrea astro platform.
 * This class is used as a placeholder for Events that do not have a defined state or mass.
 */
class Deorbit {

  public:
    /**
     * @brief Constructs a Deorbit Event that triggers at a specific altitude.
     *
     * @param triggerAltitude The altitude at which the deorbit should trigger. Default is 0 km, which means it will
     * trigger when the vehicle reaches the default crash radius of the central body.
     * @return Deorbit A Deorbit Event that triggers at the specified altitude.
     */
    Deorbit(const Distance& triggerAltitude = 0.0 * mp_units::si::unit_symbols::km);

    /**
     * @brief Gets the name of the Event.
     *
     * @return std::string The name of the Event.
     */
    std::string get_name() const;

    /**
     * @brief Detects if the Event is triggered by a Vehicle.
     *
     * @param vehicle The Vehicle to check.
     * @return true If the Event is triggered by the Vehicle.
     * @return false If the Event is not triggered by the Vehicle.
     */
    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const;

    /**
     * @brief Checks if the Event is a terminal Event.
     *
     * @return true If the Event is a terminal Event.
     * @return false If the Event is not a terminal Event.
     */
    bool is_terminal() const;

  private:
    const Distance _triggerAltitude;
};

} // namespace astro
} // namespace astrea