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

using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

int main()
{
    // Astrea hosts it's own Integrator. While many numerical integrators exist, with far more robust implementations,
    // Astrea's integrator is designed specifically for directly integrating the strongly typed element sets that Astrea
    // uses. This was to avoid hidden numerical errors, rounding issues, or possible implicit unit conversions. As such,
    // the integration process is less complete, and more difficult to work with, but more transparent, and more extensible.
    // For most users, integration will be no more difficult than that when using a more sophisticated integration library.

    // Setup initial state
    AstrodynamicsSystem sys; // Defaults to Earth-Moon
    const Date epoch;        // Defaults to J2000
    const Keplerian elements(10000.0 * km, 0.0 * one, 45.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg);
    const State state0(elements, epoch, sys);

    // Including attitude will automatically trigger kinematic eoms during propagation. This is meant to be used with a
    // control model to propagate attitude states, but can be used without one if you just want the kinematic effects.
    // If you simple want to model a local orbital frame, you don't need to include attitude dyanmics! You can just
    // model the effects in your custom forces, eoms, or in your vehicle model.
    /*
    const BodyQuaternion attitude{ 1.0, 0.0, 0.0, 0.0 }; // Identity quaternion - no rotation
    const State state0(elements, epoch, sys, attitude);
    */

    // Astrea uses a type-erased Vehicle class to propagate states. This keeps the interface more static while allowing
    // for more flexibility and extensibility for users.
    Spacecraft sat;
    Vehicle vehicle(sat);

    // Build a force model - point mass gravity is always included, but this may be changed in future releases to
    // give users more flexibility.
    ForceModel forces;
    forces.add<AtmosphericForce>();
    forces.add<OblatenessForce>(sys, 10, 10);

    // Build EoMs - these can be selected from pre-built options, or users can create their own by inheriting from the
    // base EquationsOfMotion class. Note that a force or perturbation model is not required.
    TwoBody twoBodyEom;                       // No forces
    J2MeanVop j2MeanEom;                      // Forces assumed
    CowellsMethod cowellsEom(forces);         // Regular force model
    KeplerianVop keplerianEom(forces, false); // Input options for rounding errors

    // Propagation is done using a RKF78 method with a variable step size by default. This can be changed using
    // the integrator setters.
    Integrator integrator;
    integrator.set_abs_tol(1.0e-10);
    integrator.set_rel_tol(1.0e-10);

    bool store    = true;       // Users can choose to store the state history during propagation, or not
    Time propTime = minutes(1); // A propagation interval relative to the epoch. Intervals
                                // can also be negative for backwards propagation.

    // Propagation is done with the element representation that the equations of motion expect. This is to avoid
    // unnecessary conversions during the integration process.
    std::cout << "Propagating...";
    integrator.set_equations_of_motion(twoBodyEom);
    const StateHistory twoBodyHistory = integrator.propagate(state0, propTime, vehicle);
    std::cout << " Two Body Propagation Complete." << std::endl << "Propagating...";
    vehicle = Vehicle(sat); // reset the vehicle in case the propagation updates it

    integrator.set_equations_of_motion(j2MeanEom);
    const StateHistory j2MeanHistory = integrator.propagate(state0, propTime, vehicle);
    std::cout << " J2 Mean Propagation Complete." << std::endl << "Propagating...";
    vehicle = Vehicle(sat);

    integrator.set_equations_of_motion(cowellsEom);
    const StateHistory cowellsHistory = integrator.propagate(state0, propTime, vehicle);
    std::cout << " Cowell's Method Propagation Complete." << std::endl << "Propagating...";
    vehicle = Vehicle(sat);

    integrator.set_equations_of_motion(keplerianEom);
    const StateHistory keplerianHistory = integrator.propagate(state0, propTime, vehicle);
    std::cout << " Keplerian VoP Propagation Complete." << std::endl << std::endl;

    std::cout << "Func Evals: " << integrator.n_func_evals() << std::endl;
    std::cout << "Two-Body Final State: " << twoBodyHistory.last() << std::endl;
    std::cout << "J2-Mean Final State: " << j2MeanHistory.last() << std::endl;
    std::cout << "Cowell's Method Final State: " << cowellsHistory.last() << std::endl;
    std::cout << "Keplerian VOP Final State: " << keplerianHistory.last() << std::endl;

    // And if you want, you can propagate to a specific end epoch instead of for an amount of time
    Date endEpoch = epoch + propTime;
    integrator.set_equations_of_motion(twoBodyEom);
    const StateHistory history = integrator.propagate(state0, endEpoch, vehicle);

    // And if you don't care about storing the history, you can skip that too
    const State statef = integrator.propagate(state0, propTime, vehicle);

    return 0;
}