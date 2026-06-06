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
    // First we get the basic setup for a propagation
    const Date epoch;
    const Keplerian<frames::earth::icrf> elements(10000.0 * km, 0.0 * one, 45.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg);
    const State state0(elements, epoch);

    Spacecraft sat;
    Vehicle vehicle(sat);
    Integrator integrator;

    // Integrators can also accept callable objects to watch each step. These can be used for logging, plotting,
    // or any other side effect.
    integrator.add_step_watcher([](const State& state) {
        std::cout << "\tCurrent epoch: " << state.get_epoch() << std::endl;
    });

    // Each watcher will be stored in an std::function and called after each successful step
    std::cout << "Propagating..." << std::endl;
    integrator.propagate_no_storage(state0, minutes(1), vehicle);

    // These watchers can be built out of any decayed set of arguments from the full function signature
    // (void foo(const Time&, const State&, const Vehicle&)), including no arguments at all.
    // They can be constructed from any callable object, including lambdas, function pointers, std::function, or functor objects.
    integrator.clear_watchers();

    int counter = 0;
    integrator.add_step_watcher([&counter]() {
        std::cout << "\rStep: " << counter << std::flush;
        counter++;
    });
    std::cout << "Propagating again..." << std::endl;
    integrator.propagate_no_storage(state0, days(1), vehicle);
    std::cout << std::endl << "Number of steps taken: " << counter << std::endl;

    return 0;
}