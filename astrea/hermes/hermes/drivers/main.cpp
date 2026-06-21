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

#include <pagmo

#include <pagmo/algorithm.hpp>
#include <pagmo/algorithms.hpp>
#include <pagmo/problem.hpp>

#include <astro/astro.hpp>

#include <hermes/sims-flanagan/SimsFlanaganProblem.hpp>

using namespace astrea;
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

    SimsFlanaganSettings settings{ .nSegments              = 10,
                                   .nSubsegmentsPerSegment = 5,
                                   .minPosition            = -1000.0 * km,
                                   .maxPosition            = 1000.0 * km,
                                   .minVelocity            = -10.0 * km / s,
                                   .maxVelocity            = 10.0 * km / s,
                                   .maxDeltaV              = 1.0 * km / s,
                                   .integrator             = integrator,
                                   .vehicle                = vehicle };
    SimsFlanaganProblem problem(settings);

    // Build problem, algorithm, and population
    pagmo::problem pagmoProblem{ problem };
    pagmo::algorithm algo{ pagmo::de() };
    pagmo::population pop{ pagmoProblem, 20 };

    // Evolve the population
    pop = algo.evolve(pop);

    // Output the best solution
    std::cout << "Best solution found: " << pop.champion_x() << std::endl;
    std::cout << "Best fitness: " << pop.champion_f() << std::endl;

    Trajectory trajectory = problem.decode_decision_vector(pop.champion_x());
    astro::StateHistory   = trajectory.propagate(integrator, vehicle);

    return 0;
}