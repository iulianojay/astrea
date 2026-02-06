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

#include <matplot/matplot.h>

#include <astro/astro.hpp>
#include <astro/astro.macros.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using namespace matplot;

using astrea::astro::plotting::compare_orbital_elements;
using astrea::astro::plotting::compare_trajectories;
using astrea::astro::plotting::plot_orbital_elements;
using astrea::astro::plotting::plot_trajectory;

using mp_units::angular::unit_symbols::deg;
using mp_units::non_si::day;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

int main()
{
    auto start = std::chrono::steady_clock::now();

    // Setup system
    AstrodynamicsSystem sys;
    Date epoch = Date::now();

    // Build constellation
    Keplerian initialElements = Keplerian::LEO();
    initialElements.set_eccentricity(0.001 * one);
    initialElements.set_inclination(25.0 * deg);

    State state0(initialElements, epoch, sys);
    Spacecraft sat;

    // Force model
    ForceModel forces;
    forces.add<OblatenessForce>(sys, 100, 100);
    forces.add<SolarRadiationPressure>();
    forces.add<AtmosphericForce>();
    forces.add<NBodyForce>();

    // Build EoMs
    CowellsMethod cm(forces);
    KeplerianVop kepVop(forces);
    EquinoctialVop eqVop(forces);
    J2MeanVop j2;

    // Setup integrator
    Integrator integrator;
    integrator.set_abs_tol(1.0e-13);
    integrator.set_rel_tol(1.0e-13);
    integrator.switch_fixed_timestep(true, 30.0 * s);

    // Propagate
    Time propTime = days(1);

    std::cout << "Propagating with Cowell's Method... ";
    const auto trajCm = integrator.propagate(state0, propTime, cm, Vehicle(sat), true);
    std::cout << "Cowell's Method Complete." << std::endl;

    std::cout << "Propagating with Keplerian VOP... ";
    const auto trajKepVop = integrator.propagate(state0, propTime, kepVop, Vehicle(sat), true);
    std::cout << "Keplerian VOP Complete." << std::endl;

    std::cout << "Propagating with Equinoctial VOP... ";
    const auto trajEqVop = integrator.propagate(state0, propTime, eqVop, Vehicle(sat), true);
    std::cout << "Equinoctial VOP Complete." << std::endl;

    std::cout << "Propagating with Mean J2 VOP... ";
    const auto trajJ2 = integrator.propagate(state0, propTime, j2, Vehicle(sat), true);
    std::cout << "Mean J2 VOP Complete." << std::endl;

    auto end  = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<nanoseconds>(end - start);

    std::cout << "Runtime: " << diff.count() / 1e9 << " (s)" << std::endl;

    // plot_orbital_elements(trajCm, "cowells_method_elements.png");
    // plot_orbital_elements(trajKepVop, "keplerian_vop_elements.png");
    // plot_orbital_elements(trajEqVop, "equinoctial_vop_elements.png");
    // plot_orbital_elements(trajJ2, "mean_j2_vop_elements.png");

    // plot_trajectory(trajCm, "cowells_method_trajectory.png");
    // plot_trajectory(trajKepVop, "keplerian_vop_trajectory.png");
    // plot_trajectory(trajEqVop, "equinoctial_vop_trajectory.png");
    // plot_trajectory(trajJ2, "mean_j2_vop_trajectory.png");


    std::filesystem::path outputDir(std::string(_ASTRO_ROOT_));
    outputDir /= "tests/profiling/results";

    std::filesystem::path outfile = outputDir / "orbital_elements_comparison.png";
    compare_orbital_elements({ trajCm, trajKepVop, trajEqVop, trajJ2 }, { "Cowell's Method", "Keplerian VOP", "Equinoctial VOP", "Mean J2 VOP" }, outfile);

    outfile = outputDir / "trajectory_comparison.png";
    compare_trajectories({ trajCm, trajKepVop, trajEqVop, trajJ2 }, { "Cowell's Method", "Keplerian VOP", "Equinoctial VOP", "Mean J2 VOP" }, outfile);
    return 0;
}
