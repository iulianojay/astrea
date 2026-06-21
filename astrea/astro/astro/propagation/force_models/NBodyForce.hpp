/**
 * @file OblatenessForce.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the NBodyForce class, which computes the gravitational force due to multiple celestial bodies.
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
#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/force_models/PerturbingForce.hpp>
#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/system_concepts.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class to compute the gravitational force due to multiple celestial bodies.
 *
 */
template <IsCelestialBody auto... bodies>
class NBodyForce : public PerturbingForce {
  public:
    /**
     * @brief Default constructor for NBodyForce.
     */
    NBodyForce() = default;

    /**
     * @brief Default destructor for NBodyForce.
     */
    ~NBodyForce() = default;

    /**
     * @brief Computes the gravitational force due to multiple celestial bodies.
     *
     * @param state Cartesian<frames::primary> state vector of the vehicle
     * @param vehicle Vehicle object representing the spacecraft
     * @return Perturbation The computed force and torque due to multiple bodies.
     */
    Perturbation compute_perturbation(const State& state, const Vehicle& vehicle) const override
    {
        // Extract
        const Date date                                       = state.get_epoch();
        const RadiusVector<frames::primary>& rCenterToVehicle = state.get_position();

        // Center body properties
        constexpr static auto center = frames::primary.origin;

        // Reset perturbation
        AccelerationVector<frames::primary> accelNBody{ Acceleration::zero() };
        (
            [&]<auto body>() {
                if constexpr (body == center) {
                    return; // Skip central body
                }

                // Find center to nth body and spacecraft to nth body
                // NOTE: The forced frame conversion here is fine since it's just a relative translation, no rotation or velocity
                const RadiusVector<frames::primary> rCenterToNbody =
                    get_relative_position<body, center>(date).template force_frame_conversion<frames::primary>();
                const RadiusVector<frames::primary> rVehicleToNbody = rCenterToNbody - rCenterToVehicle;

                // Normalize
                const Distance rMagVehicleToNbody = rVehicleToNbody.norm();
                const Distance rMagCenterToNbody  = rCenterToNbody.norm();

                // Perturbational force from nth body
                using mp_units::quantity;
                const GravParam mu          = get_mu<body>();
                const quantity directTerm   = mu / pow<3>(rMagVehicleToNbody);
                const quantity indirectTerm = mu / pow<3>(rMagCenterToNbody);

                accelNBody += directTerm * rVehicleToNbody - indirectTerm * rCenterToNbody;
            }.template operator()<bodies>(),
            ...
        );

        return { .force = accelNBody * vehicle.get_mass() };
    }

    /**
     * @brief Creates a deep copy of this NBodyForce object.
     *
     * @return std::unique_ptr<PerturbingForce> A unique pointer to the cloned NBodyForce object.
     */
    std::unique_ptr<PerturbingForce> clone() const override { return std::make_unique<NBodyForce<bodies...>>(*this); }
};

} // namespace astro
} // namespace astrea