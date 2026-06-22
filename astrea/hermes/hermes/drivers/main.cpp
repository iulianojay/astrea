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
#include <pagmo/algorithms/de.hpp>
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
    integrator.set_abs_tol(1e-10);
    integrator.set_rel_tol(1e-10);

    astro::Spacecraft sat;
    astro::Vehicle vehicle{ sat };

    // Problem settings
    astro::State initialState({ Keplerian<frames::primary>::LEO() }, J2000);
    Time initialPropTime = weeks(1);
    SimsFlanaganSettings settings{ .nSegments              = 10,
                                   .nSubsegmentsPerSegment = 5,
                                   .maxFlightTime          = 4 * initialPropTime,
                                   .minPosition            = -1000.0 * km,
                                   .maxPosition            = 1000.0 * km,
                                   .minVelocity            = -10.0 * km / s,
                                   .maxVelocity            = 10.0 * km / s,
                                   .maxDeltaV              = 1.0 * km / s,
                                   .integrator             = integrator,
                                   .vehicle                = vehicle };
    SimsFlanaganProblem problem(settings);

    // Build problem, and algorithm
    pagmo::problem pagmoProblem{ problem };
    pagmo::algorithm algo{ pagmo::de() };

    // Use ballistic case as first guess
    pagmo::population pop{ pagmoProblem, 20 };
    const Trajectory ballisticTrajectory =
        Trajectory::ballistic(integrator, vehicle, initialState, initialPropTime, settings.nSegments, settings.nSubsegmentsPerSegment);
    const DoubleVector guess = problem.encode_trajectory(ballisticTrajectory);
    pop.set_x(0, guess);

    // Evolve the population
    const std::size_t nEvolutions = 10;
    for (std::size_t ii = 0; ii < nEvolutions; ++ii) {
        pop = algo.evolve(pop);
    }

    // Repropagate the best solution and plot
    Trajectory trajectory            = problem.decode_decision_vector(pop.champion_x());
    astro::StateHistory stateHistory = trajectory.propagate(integrator, vehicle);

    std::filesystem::path guessPath    = std::string(_HERMES_ROOT_) + "/results/guess.png";
    std::filesystem::path solutionPath = std::string(_HERMES_ROOT_) + "/results/result.png";

    plot_trajectory(stateHistory, guessPath);
    plot_trajectory(stateHistory, solutionPath);

    return 0;
}