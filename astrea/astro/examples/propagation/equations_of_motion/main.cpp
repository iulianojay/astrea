/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
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

using mp_units::si::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

int main()
{
    // Astrea hosts it's own Integrator. While many numerical integrators exist with far more robust implementations,
    // Astrea's integrator is designed specifically for directly integrating the strongly typed element sets that Astrea
    // uses. This decision was made to avoid hidden numerical errors, rounding issues, or possible implicit unit conversions.
    // As such, the integration process is less complete, and more difficult to develop, but also more transparent, and more
    // extensible. For most users, integration will be no more difficult than that when using a more sophisticated integration library.

    // Setup initial state
    const Date epoch; // Defaults to J2000
    const Keplerian<frames::earth::icrf> elements(10000.0 * km, 0.0 * one, 45.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg);
    const State state0(elements, epoch);

    // Astrea uses a type-erased Vehicle class to propagate states. This keeps the interface more static while allowing
    // for more flexibility and extensibility for users.
    Spacecraft sat;
    Vehicle vehicle(sat);

    // Equations of motion are the basis for dynamic progagation. This class is meant to provide a partial derivative
    // for some given state and vehicle. Astrea provides several common EoMs, but users can create their own by
    // inheriting from the EquationsOfMotion base class.
    struct MyEquationsOfMotion : public EquationsOfMotion {

        // The expected set id is used to tell the integrator what type of elements to propagate
        constexpr std::size_t get_expected_set_id() const
        {
            // The orbital element class provides a static helper to get the set id for a given element type
            return OrbitalElements::get_set_id<Cartesian<frames::earth::icrf>>();
        };

        // Dynamics are computed from the current state. The eom model is also passed the current vehicle, in case
        // checking it's state is required, as well as perturbing and control forces. Perturbing forces are computed
        // from the current force model, and control forces are returned from the vehicle. Both are customizable.
        OrbitalElementPartials compute_dynamics(
            const State& state,
            const Vehicle& vehicle,
            const ForceVector<frames::earth::icrf>& perts,
            const ForceVector<frames::earth::icrf>& control
        ) const override
        {
            // Extracting into the desired set can be convenient
            const GravParam mu                             = get_mu<planets::Earth>();
            const Cartesian<frames::earth::icrf> cartesian = state.in_element_set<Cartesian<frames::earth::icrf>>();

            // Pull out the pieces for simple two-body gravity
            const auto r = cartesian.get_position();
            const auto R = r.norm();
            const auto v = cartesian.get_velocity();

            // Compute the partials
            CartesianPartial<frames::earth::icrf> partials(v, -mu / (R * R * R) * r + control / vehicle.get_mass());

            return partials;
        }

        // Required clone function to help with polymorphic copying of the equations of motion object.
        std::unique_ptr<EquationsOfMotion> clone() const override
        {
            return std::make_unique<MyEquationsOfMotion>(*this);
        }
    };
    MyEquationsOfMotion myEoms;

    // Propagation is done using a RKF78 method with a variable step size by default. This can be changed using
    // the integrator setters.
    Integrator integrator;
    integrator.set_equations_of_motion(myEoms);

    bool store    = true;       // Users can choose to store the state history during propagation, or not
    Time propTime = minutes(1); // Propagation time can also be negative for backwards propagation.

    // Propagation is done with the element representation that the equations of motion expect. This is to avoid
    // unnecessary conversions during the integration process.
    std::cout << "Propagating My Equations of Motion...";
    const StateHistory history = integrator.propagate(state0, propTime, vehicle);

    std::cout << " Propagation Complete." << std::endl;

    std::cout << "Func Evals: " << integrator.n_func_evals() << std::endl;
    std::cout << "Final State: " << history.last() << std::endl;

    return 0;
}