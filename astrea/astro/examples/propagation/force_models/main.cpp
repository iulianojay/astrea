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
using mp_units::si::unit_symbols::N;
using mp_units::si::unit_symbols::s;

int main()
{
    // A ForceModel is a factory for arbitrary PerturbingForce objects. These forces are called during propagation
    // to compute accelerations and torques on the spacecraft. Several forces are provided with Astrea, and users can
    // add more by inheriting from the PerturbingForce class.
    struct ContinuousThrust : public PerturbingForce {
        ContinuousThrust(const std::string& name = "Continuous Thrust Force") :
            _name(name)
        {
        }

        // Currently, forces and torques are expected to return acceleration in the Earth-centered ICRF frame. Future
        // releases will allow perturbating forces to specify the output frame.
        Perturbation compute_perturbation(const State& state, const Vehicle& vehicle) const override
        {
            // Grab the cartesian elements and date
            const Date date                                = state.get_epoch();
            const Cartesian<frames::earth::icrf> cartesian = state.in_element_set<Cartesian<frames::earth::icrf>>();

            // Build out a burn in the RIC frame, pointing in the nadir direction
            const auto frame = frames::dynamic::ric.instantaneous(cartesian.get_position(), cartesian.get_velocity());
            const ForceVector<astro::frames::dynamic::ric> nadirThrust{ -1.0 * N, 0.0 * N, 0.0 * N };

            std::cout << "Applying continuous thrust force: " << _name << " at time " << date << std::endl;
            std::cout << nadirThrust << std::endl;

            // Rotate the acceleration back to the inertial frame for output. Include a torque, if you want to model
            // attitude effects as well.
            const auto thrustForce = frame.rotate_out_of_this_frame(nadirThrust, date);
            std::cout << "Thrust force in inertial frame: " << thrustForce << std::endl;

            const CartesianVector<Length, astro::frames::dynamic::ric> thrusterOffset{ 0.0 * m, 1.0 * m, 0.0 * m };
            const auto thrustTorque = frame.rotate_out_of_this_frame(nadirThrust.cross(thrusterOffset), date);

            return { .force = thrustForce, .torque = thrustTorque };
        }

        std::unique_ptr<PerturbingForce> clone() const override { return std::make_unique<ContinuousThrust>(*this); }

      private:
        std::string _name;
    };

    // Input arguments are forwarded to the constructor of the Force subclass
    ForceModel forceModel;
    forceModel.add<ContinuousThrust>("My Continuous Thrust");

    // During propagation, the force model is queried for the total acceleration
    Cartesian<frames::earth::icrf> cart{ 7000.0 * km, 7000.0 * km, 0.0 * km, 0.0 * km / s, 7.5 * km / s, 1.0 * km / s };
    State state(cart, Date());
    const auto [totalAcceleration, totalTorque] = forceModel.compute_perturbations(state, Vehicle());
    std::cout << "Total Acceleration: " << totalAcceleration << std::endl;
    std::cout << "Total Torque: " << totalTorque << std::endl;

    return 0;
}