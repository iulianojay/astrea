/**
 * @file NullVehicle.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A class representing a null vehicle in the astrea astro platform.
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

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

/**
 * @brief A class representing a null vehicle in the astrea astro platform.
 * This class is used as a placeholder for vehicles that do not have a defined state or mass.
 */
class NullVehicle {

  public:
    /**
     * @brief Constructs a NullVehicle with an initial state and mass.
     *
     * @param mass The mass of the vehicle, defaulting to one kilogram.
     */
    NullVehicle(const Mass& mass = 1.0 * mp_units::si::unit_symbols::kg);

    /**
     * @brief Clone the NullVehicle object.
     *
     * @return NullVehicle* A pointer to a new NullVehicle object that is a copy of this one.
     */
    NullVehicle* clone() const;

    /**
     * @brief Gets the mass of the vehicle.
     *
     * @return Mass The mass of the vehicle.
     */
    Mass get_mass(const State& state) const;

    /**
     * @brief Gets the name of the vehicle.
     *
     * @return std::string The name of the vehicle.
     */
    std::string get_name() const;

  private:
    Mass _mass; // Mass of the vehicle
};

} // namespace astro
} // namespace astrea