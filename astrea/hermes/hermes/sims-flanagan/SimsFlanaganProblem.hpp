/**
 * @file SimsFlanaganProblem.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Sims-Flanagan problem module
 * @date 2026-04-24
 *
 * @copyright Copyright (c) 2026 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <vector>

#include <pagmo/problem.hpp>

#include <hermes/sims-flanagan/model/DeltaV.hpp>
#include <hermes/sims-flanagan/model/Segment.hpp>
#include <hermes/sims-flanagan/model/State.hpp>
#include <hermes/types/typedefs.hpp>

namespace astrea {
namespace hermes {

struct SimsFlanaganSettings {
    std::size_t nSegments;
    std::size_t nSubsegmentsPerSegment;
    Distance minPosition;
    Distance maxPosition;
    Velocity minVelocity;
    Velocity maxVelocity;
    Velocity maxDeltaV;
    astro::Integrator integrator;
    astro::Vehicle vehicle;
};

class SimsFlanaganProblem {
  public:
    SimsFlanaganProblem() = default;

    SimsFlanaganProblem(const SimsFlanaganSettings& settings) :
        _nSegments(settings.nSegments),
        _nSubsegmentsPerSegment(settings.nSubsegmentsPerSegment),
        _maxDeltaV(settings.maxDeltaV),
        _integrator(settings.integrator),
        _vehicle(settings.vehicle),
        _nBurnsPerSegment(_nSubsegmentsPerSegment - 1),
        _nDecisionsPerSegment(8 + 3 * _nBurnsPerSegment),
        _nDecisions(_nDecisionsPerSegment * _nSegments)
    {
    }

    ~SimsFlanaganProblem() = default;

    std::size_t get_nx() const;

    std::size_t get_nic() const;

    std::size_t get_nobj() const;

    std::pair<DoubleVector, DoubleVector> get_bounds() const;

    DoubleVector fitness(const DoubleVector& x) const;

    std::string get_name() const;

    Trajectory decode_decision_vector(const DoubleVector& x) const;

  private:
    std::size_t _nSegments;
    std::size_t _nSubsegmentsPerSegment;
    Distance _minPosition;
    Distance _maxPosition;
    Velocity _minVelocity;
    Velocity _maxVelocity;
    Velocity _maxDeltaV;
    astro::Integrator _integrator;
    astro::Vehicle _vehicle;

    const std::size_t _nBurnsPerSegment;
    const std::size_t _nDecisionsPerSegment;
    const std::size_t _nDecisions;
};

} // namespace hermes
} // namespace astrea