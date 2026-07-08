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
#include <filesystem>

#include <pagmo/algorithm.hpp>
#include <pagmo/algorithms/nsga2.hpp>
#include <pagmo/problem.hpp>

#include <astro/astro.hpp>
#include <astro/utilities/plotting.hpp>
#include <units/units.hpp>

#include <hermes/hermes.macros.hpp>
#include <hermes/sims-flanagan/SimsFlanaganProblem.hpp>
#include <hermes/sims-flanagan/model.hpp>
#include <hermes/sims-flanagan/settings.hpp>

using namespace astrea;
using namespace astro;
using namespace astro::plotting;
using namespace hermes;

int main()
{
    // Setup
    astro::Integrator integrator;
    astro::J2MeanVop eoms;
    integrator.set_equations_of_motion(eoms);
    integrator.switch_fixed_timestep(true, 1.0 * mp_units::si::minute);
    integrator.set_abs_tol(1e-10);
    integrator.set_rel_tol(1e-10);

    astro::Spacecraft sat;
    astro::Vehicle vehicle{ sat };

    // Problem settings
    astro::Date epoch               = J2000;
    Time initialPropTime            = weeks(1);
    const auto mu                   = astro::get_mu<astro::planets::Earth>();
    const astro::State initialState = { Cartesian<frames::primary>::LEO(mu), epoch };
    const astro::State targetState  = { Cartesian<frames::primary>::GEO(mu), epoch + initialPropTime };
    SimsFlanaganSettings settings{ .epoch                  = epoch,
                                   .nSegments              = 10,
                                   .nSubsegmentsPerSegment = 5,
                                   .maxFlightTime          = 4 * initialPropTime,
                                   .minPosition            = -1000.0 * km,
                                   .maxPosition            = 1000.0 * km,
                                   .minVelocity            = -10.0 * km / s,
                                   .maxVelocity            = 10.0 * km / s,
                                   .maxDeltaV              = 1.0 * km / s,
                                   .integrator             = integrator,
                                   .vehicle                = vehicle,
                                   .initialCartesian       = Cartesian<frames::primary>::LEO(mu),
                                   .targetCartesian        = Cartesian<frames::primary>::GEO(mu) };
    SimsFlanaganProblem problem(settings);

    // Build problem, and algorithm
    pagmo::problem pagmoProblem{ problem };
    pagmo::algorithm algo{ pagmo::nsga2() };

    // Use ballistic case as first guess
    std::cout << "Generating ballistic trajectory for initial guess..." << std::endl;
    // pagmo::population pop{ pagmoProblem, 20 };
    Trajectory ballisticTrajectory =
        Trajectory::ballistic(integrator, vehicle, { initialState }, initialPropTime, settings.nSegments, settings.nSubsegmentsPerSegment);
    const DoubleVector guess = problem.encode_trajectory(ballisticTrajectory);
    // pop.set_x(0, guess);

    // // Evolve the population
    // std::cout << "Evolving population..." << std::endl;
    // const std::size_t nEvolutions = 10;
    // for (std::size_t ii = 0; ii < nEvolutions; ++ii) {
    //     std::cout << "\tEvolution " << ii + 1 << " of " << nEvolutions << "\r";
    //     pop = algo.evolve(pop);
    // }
    // std::cout << std::endl;

    // // Repropagate the best solution and the guess
    // const auto& f      = pop.get_f();
    // const auto& x      = pop.get_x();
    // std::size_t idx    = 0;
    // Velocity minDeltaV = std::numeric_limits<Velocity>::infinity();
    // for (std::size_t ii = 0; ii < x.size(); ++ii) {
    //     std::cout << "Solution " << ii + 1 << ": " << std::endl;
    //     std::cout << "\tContinuity Position Violation = " << f[ii][0] * km << std::endl;
    //     std::cout << "\tContinuity Velocity Violation = " << f[ii][1] * km / s << std::endl;
    //     std::cout << "\tTotal Delta-V = " << f[ii][2] * km / s << std::endl;
    //     std::cout << "\tTotal Time of Flight = " << f[ii][3] * day << std::endl;
    //     if (f[ii][2] * km / s < minDeltaV) {
    //         minDeltaV = f[ii][2] * km / s;
    //         idx       = ii;
    //     }
    // }
    // Trajectory trajectory            = problem.decode_decision_vector(x[idx]);
    // astro::StateHistory stateHistory = trajectory.propagate(integrator, vehicle);

    const auto ballisticStateHistory = ballisticTrajectory.propagate(integrator, vehicle);
    const auto initialOrbitHistory   = integrator.propagate(initialState, initialPropTime, vehicle);
    const auto finalOrbitHistory     = integrator.propagate(targetState, initialPropTime, vehicle);

    // Plot and save
    std::filesystem::path outputDir = std::string(_HERMES_ROOT_) + "/results/sims-flanagan-test";
    std::filesystem::create_directories(outputDir);
    std::filesystem::path guessPath    = outputDir / "guess.png";
    std::filesystem::path solutionPath = outputDir / "result.png";

    std::cout << "Plotting results to " << guessPath << " and " << solutionPath << std::endl;
    compare_trajectories({ initialOrbitHistory, finalOrbitHistory, ballisticStateHistory }, { "Initial Orbit", "Final Orbit", "Ballistic Trajectory" }, guessPath);
    // plot_trajectory(stateHistory, solutionPath);

    return 0;
}