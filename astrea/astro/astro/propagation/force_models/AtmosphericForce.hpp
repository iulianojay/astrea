/**
 * @file AtmosphericForce.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the AtmosphericForce class, which computes the atmospheric force on a vehicle.
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

#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/force_models/PerturbingForce.hpp>
#include <astro/systems/system_concepts.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class to compute the atmospheric force on a vehicle.
 *
 * This class computes the atmospheric force on a vehicle based on its state and the celestial body's atmosphere.
 */
template <IsCelestialBody auto _body_, planets::EarthAtmosphereModel _model_ = planets::EarthAtmosphereModel::HARRIS_PRIESTER>
class AtmosphericForce : public PerturbingForce {

  public:
    static constexpr auto center = _body_;

    /**
     * @brief Default constructor for AtmosphericForce.
     */
    AtmosphericForce() = default;

    /**
     * @brief Default destructor for AtmosphericForce.
     */
    ~AtmosphericForce() = default;

    /**
     * @brief Computes the atmospheric force on a vehicle.
     *
     * @param state State of the vehicle
     * @param vehicle Vehicle object representing the spacecraft
     * @return Perturbation The computed force and torque due to atmospheric force.
     */
    Perturbation compute_perturbation(const State& state, const Vehicle& vehicle) const override
    {
        using namespace mp_units;
        using mp_units::pow;
        using mp_units::si::atan2;
        using mp_units::si::sin;
        using mp_units::si::unit_symbols::rad;
        using mp_units::si::unit_symbols::s;

        // Extract
        const AngularVelocity& bodyRotationRate = get_rotation_rate<center>();

        const RadiusVector<frames::primary>& r   = state.get_position();
        const VelocityVector<frames::primary>& v = state.get_velocity();

        const Distance& x = r.get_x();
        const Distance& y = r.get_y();
        const Distance R  = r.norm();

        const Velocity& vx = v.get_x();
        const Velocity& vy = v.get_y();
        const Velocity& vz = v.get_z();

        // Find velocity relative to atmosphere
        const VelocityVector<frames::primary> relVelocity = { vx + y * bodyRotationRate.in(rad / s) / rad,
                                                              vy - x * bodyRotationRate.in(rad / s) / rad,
                                                              vz };

        // Exponential Drag Model
        Density atmosphericDensity;
        if constexpr (center == planets::Earth) {
            atmosphericDensity = find_atmospheric_density<center, _model_>(state);
        }
        else {
            atmosphericDensity = find_atmospheric_density<center>(state);
        }

        // Accel due to drag
        const Velocity relVelMag         = relVelocity.norm();
        const Unitless coefficientOfDrag = vehicle.get_coefficient_of_drag();
        const SurfaceArea areaRam        = vehicle.get_ram_area();
        const Force dragForceMag         = -0.5 * coefficientOfDrag * areaRam * atmosphericDensity * pow<2>(relVelMag);

        const ForceVector<frames::primary> forceDrag = dragForceMag * (relVelocity / relVelMag);

        // accel due to lift
        const Angle angleOfAttack        = atan2(relVelocity.get_z(), relVelocity.get_x());
        const Unitless coefficientOfLift = vehicle.get_coefficient_of_lift();
        const SurfaceArea areaLift       = vehicle.get_lift_area();
        const Force liftForceMag = 0.5 * coefficientOfLift * areaLift * atmosphericDensity * pow<2>(relVelMag) * sin(angleOfAttack);
        const ForceVector<frames::primary> forceLift = liftForceMag * (r / R); // just assume radial lift for now

        return { .force = forceDrag + forceLift };
    }

    /**
     * @brief Creates a clone of the current AtmosphericForce object.
     *
     * @return std::unique_ptr<PerturbingForce> A unique pointer to the cloned AtmosphericForce object.
     */
    std::unique_ptr<PerturbingForce> clone() const override { return std::make_unique<AtmosphericForce>(*this); }
};

} // namespace astro
} // namespace astrea