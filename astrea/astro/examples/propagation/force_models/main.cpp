/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>

#include <units/units.hpp>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

int main()
{
    // A ForceModel is a factory for arbitrary Force objects. These forces are called during propagation
    // to compute accelerations on the spacecraft. Several forces are provided with Astrea, and users can add
    // more by inheriting from the Force class.
    struct ContinuousThrust : public PerturbingForce {
        ContinuousThrust(const std::string& name = "Continuous Thrust Force") :
            _name(name)
        {
        }

        // Currently, forces are expected to return acceleration in the Earth-centered ICRF frame. Future releases will
        // allow forces to specify the output frame.
        Perturbation compute_perturbation(const State& state, const Vehicle& vehicle) const override
        {
            // Grab the cartesian elements and date
            const Date date           = state.get_epoch();
            const Cartesian cartesian = state.in_element_set<Cartesian>();

            // Build out a burn in the RIC frame, pointing in the nadir direction
            using RIC       = astro::frames::dynamic::ric;
            const RIC frame = frames::dynamic::ric::instantaneous(cartesian.get_position(), cartesian.get_velocity());
            const ForceVector<RIC> nadirThrust{ -1.0 * N, 0.0 * N, 0.0 * N };

            std::cout << "Applying continuous thrust force: " << _name << " at time " << date << std::endl;
            std::cout << nadirThrust << std::endl;

            // Rotate the acceleration back to the inertial frame for output
            return { .force = frame.rotate_out_of_this_frame(nadirThrust, date) };
        }

      private:
        std::string _name;
    };

    // Input arguments are forwarded to the constructor of the Force subclass
    AstrodynamicsSystem sys;
    ForceModel forceModel;
    forceModel.add<ContinuousThrust>("My Continuous Thrust");

    // During propagation, the force model is queried for the total acceleration
    Cartesian cart{ 7000.0 * km, 7000.0 * km, 0.0 * km, 0.0 * km / s, 7.5 * km / s, 1.0 * km / s };
    State state(cart, Date(), sys);
    const auto [totalAcceleration, totalTorque] = forceModel.compute_perturbations(state, Vehicle());
    std::cout << "Total Acceleration: " << totalAcceleration << std::endl;

    return 0;
}