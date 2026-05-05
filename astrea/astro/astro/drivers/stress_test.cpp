/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <chrono>
#include <iostream>
#include <map>
#include <string>

#include <units/units.hpp>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

struct Stopwatch {

    using timer    = std::chrono::high_resolution_clock::time_point;
    using duration = std::chrono::duration<double, std::milli>;

    std::map<std::string, timer> starts;
    std::map<std::string, duration> durations;

    void start(std::string id) { starts[id] = std::chrono::high_resolution_clock::now(); }

    void stop(std::string id) { durations[id] = std::chrono::high_resolution_clock::now() - starts[id]; }

    void print_results() const
    {
        std::cout << "Timing Results:\n";
        for (const auto& [id, dur] : durations) {
            std::cout << "  " << id << ": " << dur.count() << " ms\n";
        }
    }
};

int main()
{
    Stopwatch stopwatch;

    // Setup initial state
    AstrodynamicsSystem sys; // Defaults to Earth-Moon
    const Date epoch;        // Defaults to J2000
    const Keplerian elements(7000.0 * km, 0.0 * one, 45.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg);
    const State state0(elements, epoch, sys);

    Spacecraft sat;
    Vehicle vehicle(sat);

    // Build a force model
    ForceModel forces;
    // forces.add<AtmosphericForce>();
    stopwatch.start("Build OblatenessForce");
    forces.add<OblatenessForce>(sys, 100, 100);
    stopwatch.stop("Build OblatenessForce");

    Integrator integrator;
    integrator.set_abs_tol(1.0e-10);
    integrator.set_rel_tol(1.0e-10);

    Time propTime = weeks(1);

    // Build EoMs
    TwoBody twoBodyEom;
    J2MeanVop j2MeanEom;
    CowellsMethod cowellsEom(forces);
    KeplerianVop keplerianEom(forces, false);

    integrator.set_equations_of_motion(keplerianEom);
    stopwatch.start("Run Keplerian Propagation");
    integrator.propagate_no_storage(state0, propTime, vehicle);
    stopwatch.stop("Run Keplerian Propagation");

    stopwatch.print_results();

    return 0;
}