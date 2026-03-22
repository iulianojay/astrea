/**
 * @file Force.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Force class, which defines the interface for force models in astrodynamics.
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

#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

namespace {

using namespace mp_units;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::N;
using mp_units::si::unit_symbols::s;

} // namespace

/**
 * @brief Struct to hold the results of a perturbation force computation, including both acceleration and torque.
 */
struct Perturbation {
    ForceVector<frames::earth::icrf> force = { 0.0 * N }; //!< The computed force vector due to the perturbing force.
    MomentVector<frames::earth::icrf> torque = { 0.0 * N * m }; //!< The computed torque vector due to the perturbing force.
};

/**
 * @brief Abstract base class for force models in astrodynamics.
 *
 * This class defines the interface for computing forces acting on a vehicle in space.
 */
class PerturbingForce {
  public:
    /**
     * @brief Default constructor for PerturbingForce.
     */
    PerturbingForce() = default;

    /**
     * @brief Default destructor for PerturbingForce.
     */
    virtual ~PerturbingForce() = default;

    /**
     * @brief Computes the force acting on a vehicle at a given date and state.
     *
     * @param state State of the vehicle
     * @param vehicle Vehicle object representing the spacecraft
     * @return Perturbation The computed acceleration and torque vectors due to the force.
     */
    virtual Perturbation compute_perturbation(const State& state, const Vehicle& vehicle) const = 0;
};

} // namespace astro
} // namespace astrea