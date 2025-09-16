#include <chrono>
#include <iostream>

#include <mp-units/systems/si.h>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

int main()
{
    // The Astrea State is a fully-defined state representation that can hold any supported
    // orbital element set, an epoch, and the system the set is defined in. Currently, it does not
    // support angular (kinematic) states, but this will be added in a future release.
    AstrodynamicsSystem sys; // Default system is Earth
    Cartesian cartesian{
        7000.0 * km, 0.0 * km, 0.0 * km, 0.0 * km / s, 7.5 * km / s, 1.0 * km / s,
    };
    Date epoch = Date::now();
    State state(cartesian, epoch, sys);
    std::cout << "State: " << state << std::endl;

    // The state can currently support conversions between any supported element set
    // without needing to directly reference the astrodynamics system. This is a nice conveinience
    // for users who don't want to lug around a system object.
    std::cout << "State in Keplerian: " << state.in_element_set<Keplerian>() << std::endl;
    std::cout << "State in Equinoctial: " << state.in_element_set<Equinoctial>() << std::endl;
    std::cout << "State in Cartesian: " << state.in_element_set<Cartesian>() << std::endl << std::endl;

    // In future release, the state will be used directly for propagation in place of OrbitalElements.

    // States can be stored in a StateHistory for easy access and containerization.
    // Note: A StateHistory may be updated to "Trajectory" in future releases.
    StateHistory history;
    std::cout << "StateHistory Size: " << history.size() << std::endl;
    history[epoch] = state;
    std::cout << "StateHistory Size: " << history.size() << std::endl;
    std::cout << "history(epoch): " << history.at(epoch) << std::endl;

    return 0;
}