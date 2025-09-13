#include <chrono>
#include <iostream>

#include <mp-units/systems/si.h>

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
    const Date epoch;
    const Keplerian elements(10000.0 * km, 0.0 * one, 45.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg);
    const State state0(elements, epoch, sys);

    // Astrea uses a type-erased Vehicle class to propagate states. This keeps the interface more static while allowing
    // for more flexibility and extensibility for users.
    Spacecraft sat(state0);
    Vehicle vehicle(sat);

    // Build a force model - two-body gravity is included by default, but this may be changed in future releases to give
    // users more flexibility.
    ForceModel forces;
    forces.add<AtmosphericForce>();
    forces.add<OblatenessForce>(sys, 10, 10);

    // Build EoMs - these can be selected from pre-built options, or users can create their own by inheriting from the
    // base EquationsOfMotion class. Note that a force or perturbation model is not required.
    TwoBody twoBodyEom(sys);                       // No forces
    J2MeanVop j2MeanEom(sys);                      // Forces assumed
    CowellsMethod cowellsEom(sys, forces);         // Regular force model
    KeplerianVop keplerianEom(sys, forces, false); // Input options for rounding errors

    // Propagation is done using a RKF78 method with a variable step size by default. This can be changed using
    // the integrator setters.
    Integrator integrator;
    integrator.set_abs_tol(1.0e-10);
    integrator.set_rel_tol(1.0e-10);

    bool store = true; // Users can choose to store the state history during propagation, or not
    Interval propInterval{ seconds(0), minutes(1) };

    // Propagation is done with the element representation that the equations of motion expect. This is to avoid
    // unnecessary conversions during the integration process.
    std::cout << "Propagating...";
    const StateHistory twoBodyHistory = integrator.propagate(epoch, propInterval, twoBodyEom, vehicle, store);
    std::cout << " Two Body Propagation Complete." << std::endl << "Propagating...";
    const StateHistory j2MeanHistory = integrator.propagate(epoch, propInterval, j2MeanEom, vehicle, store);
    std::cout << " J2 Mean Propagation Complete." << std::endl << "Propagating...";
    const StateHistory cowellsHistory = integrator.propagate(epoch, propInterval, cowellsEom, vehicle, store);
    std::cout << " Cowell's Method Propagation Complete." << std::endl << "Propagating...";
    const StateHistory keplerianHistory = integrator.propagate(epoch, propInterval, keplerianEom, vehicle, store);
    std::cout << " Keplerian VoP Propagation Complete." << std::endl << std::endl;

    std::cout << "Func Evals: " << integrator.n_func_evals() << std::endl;
    std::cout << "Two-Body Final State: " << twoBodyHistory.last() << std::endl;
    std::cout << "J2-Mean Final State: " << j2MeanHistory.last() << std::endl;
    std::cout << "Cowell's Method Final State: " << cowellsHistory.last() << std::endl;
    std::cout << "Keplerian VOP Final State: " << keplerianHistory.last() << std::endl << std::endl;

    return 0;
}