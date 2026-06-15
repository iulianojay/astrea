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
    // The Astrea State is a fully-defined state representation that can hold any supported
    // orbital element set, an epoch, and the system the set is defined in. Currently, it does not
    // support angular (kinematic) states, but this will be added in a future release.
    Cartesian<frames::earth::icrf> cartesian{
        7000.0 * km, 0.0 * km, 0.0 * km, 0.0 * km / s, 7.5 * km / s, 1.0 * km / s,
    };
    Date epoch = Date::now();
    State state(cartesian, epoch);
    std::cout << "State: " << state << std::endl;

    // The state can currently support conversions between any supported element set
    // without needing to directly reference the astrodynamics system. This is a nice convenience
    // for users who don't want to lug around a system object.
    std::cout << "State in Keplerian: " << state.in_element_set<Keplerian<frames::earth::icrf>>() << std::endl;
    std::cout << "State in Equinoctial: " << state.in_element_set<Equinoctial<frames::earth::icrf>>() << std::endl;
    std::cout << "State in Cartesian: " << state.in_element_set<Cartesian<frames::earth::icrf>>() << std::endl
              << std::endl;

    // A state also can hold an optional attitude.
    const BodyQuaternion orientation{ 1.0, 0.0, 0.0, 0.0 }; // Identity quaternion - no rotation
    const BodyAngleVelocities angularVelocity{ 0.0 * deg / s, 0.0 * deg / s, 0.0 * deg / s };
    const Attitude attitude(orientation, angularVelocity);
    State stateWithAttitude(cartesian, epoch, attitude);
    std::cout << "State with Attitude: " << stateWithAttitude << std::endl;
    std::cout << "State Attitude: " << stateWithAttitude.get_attitude().value() << std::endl << std::endl;

    // States can be stored in a StateHistory for easy access and containerization.
    // Note: A StateHistory may be updated to "Trajectory" in future releases.
    StateHistory history;
    std::cout << "StateHistory Size: " << history.size() << std::endl;
    history.insert(state);
    std::cout << "StateHistory Size: " << history.size() << std::endl;
    std::cout << "history(epoch): " << history.get_state_at(epoch) << std::endl;

    return 0;
}