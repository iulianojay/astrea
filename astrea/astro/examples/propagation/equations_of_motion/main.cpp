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

    // Equations of motion are the basis for dynamic progagation. This class is meant to provide a partial derivative
    // for some given state and vehicle. Astrea provides several common EoMs, but users can create their own by
    // inheriting from the EquationsOfMotion base class.
    struct MyEquationsOfMotion : public EquationsOfMotion {
        MyEquationsOfMotion(const AstrodynamicsSystem& system) :
            EquationsOfMotion(system) // An astrodynamics system must be provided
        {
        }

        // The expected set id is used to tell the integrator what type of elements to propagate
        constexpr std::size_t get_expected_set_id() const
        {
            // The orbital element class provides a static helper to get the set id for a given element type
            return OrbitalElements::get_set_id<Cartesian>();
        };

        OrbitalElementPartials operator()(const OrbitalElements& state, const Vehicle& vehicle) const override
        {
            // Extracting into the desired set can be convenient
            const AstrodynamicsSystem& system = get_system();
            const auto mu                     = system.get_center()->get_mu();
            const Cartesian cartesian         = state.in_element_set<Cartesian>(system);

            // Pull out the pieces for simple two-body gravity
            const auto r = cartesian.get_position();
            const auto R = r.norm();
            const auto v = cartesian.get_velocity();

            // Compute the partials
            CartesianPartial partials(v, -mu / (R * R * R) * r);

            return partials;
        }
    };
    MyEquationsOfMotion myEoms(sys);

    // Propagation is done using a RKF78 method with a variable step size by default. This can be changed using
    // the integrator setters.
    Integrator integrator;

    bool store = true; // Users can choose to store the state history during propagation, or not
    Interval propInterval{ seconds(0), minutes(1) };

    // Propagation is done with the element representation that the equations of motion expect. This is to avoid
    // unnecessary conversions during the integration process.
    std::cout << "Propagating My Equations of Motion...";
    const StateHistory history = integrator.propagate(epoch, propInterval, myEoms, vehicle, store);
    std::cout << " Propagation Complete." << std::endl;

    std::cout << "Func Evals: " << integrator.n_func_evals() << std::endl;
    std::cout << "Final State: " << history.last() << std::endl;

    return 0;
}