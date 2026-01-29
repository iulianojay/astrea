/**
 * @file CowellsMethod.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Cowell's Method equations of motion class.
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
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class implementing Cowell's method for equations of motion.
 */
class CowellsMethod : public EquationsOfMotion {

  public:
    /**
     * @brief Constructor for Cowell's Method.
     *
     * @param system The astrodynamics system containing the central body and its properties.
     * @param forces The force model to be used in the equations of motion.
     */
    CowellsMethod(const AstrodynamicsSystem& system, const ForceModel& forces);

    /**
     * @brief Destructor for Cowell's Method.
     */
    ~CowellsMethod() = default;

    /**
     * @brief Computes the partial derivatives of the orbital elements using Cowell's method.
     *
     * @param date The current date for which the equations of motion are being computed.
     * @param state The current orbital elements of the vehicle.
     * @param vehicle The vehicle for which the equations of motion are being computed.
     * @return OrbitalElementPartials The computed partial derivatives of the orbital elements.
     */
    OrbitalElementPartials operator()(const Date& date, const OrbitalElements& state, const Vehicle& vehicle) const override;

    /**
     * @brief Returns the expected set of orbital elements for this method.
     *
     * @return std::size_t The expected set id of orbital elements.
     */
    constexpr std::size_t get_expected_set_id() const override { return OrbitalElements::get_set_id<Cartesian>(); };

  private:
    const ForceModel* forces; //!< The force model used in the equations of motion.
    GravParam mu;             //!< Gravitational parameter of the central body.
};

} // namespace astro
} // namespace astrea