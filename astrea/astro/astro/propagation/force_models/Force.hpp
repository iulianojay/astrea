/**
 * @file Force.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Force class, which defines the interface for force models in astrodynamics.
 * @version 0.1
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

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/frames.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Abstract base class for force models in astrodynamics.
 *
 * This class defines the interface for computing forces acting on a vehicle in space.
 */
class Force {
  public:
    /**
     * @brief Default constructor for Force.
     */
    Force() = default;

    /**
     * @brief Default destructor for Force.
     */
    virtual ~Force() = default;

    /**
     * @brief Computes the force acting on a vehicle at a given date and state.
     *
     * @param date Date of the computation
     * @param state Cartesian state vector of the vehicle
     * @param vehicle Vehicle object representing the spacecraft
     * @param sys Astrodynamics system containing celestial body data
     * @return AccelerationVector<frames::earth::icrf> The computed acceleration vector due to the force.
     */
    virtual CartesianVector<Acceleration, frames::earth::icrf>
        compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const = 0;
};

} // namespace astro
} // namespace astrea