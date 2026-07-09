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

#include <hermes/sims-flanagan/SimsFlanaganProblem.hpp>

#include <mp-units/core.h>
#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <hermes/sims-flanagan/calculations.hpp>

namespace astrea {
namespace hermes {

using namespace mp_units;
using mp_units::non_si::day;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

std::string SimsFlanaganProblem::get_name() const { return "Sims-Flanagan Problem"; }

std::size_t SimsFlanaganProblem::get_nx() const { return _nDecisions; }

std::size_t SimsFlanaganProblem::get_nic() const { return 0; }

std::size_t SimsFlanaganProblem::get_nobj() const { return 4; }

std::pair<DoubleVector, DoubleVector> SimsFlanaganProblem::get_bounds() const
{
    const DoubleVector lb(_nDecisions, 0.0);
    const DoubleVector ub(_nDecisions, 1.0);
    return { lb, ub };
}

template <typename T>
T convert_decision_value_to_quantity(double value, T min, T max)
{
    return min + value * (max - min);
}

Trajectory SimsFlanaganProblem::decode_decision_vector(const DoubleVector& x) const
{
    // Build out settings blocks from the decision vector
    TrajectorySettings settings;
    settings.nSegments = _nSegments;
    settings.segmentSettings.reserve(_nSegments);
    for (std::size_t ii = 0; ii < _nSegments; ++ii) {
        std::size_t idx = _nDecisionsPerSegment * ii;

        SegmentSettings segSettings;
        segSettings.nSubsegments = _nSubsegmentsPerSegment;
        segSettings.isForward    = _segmentDirections[ii];
        segSettings.duration     = convert_decision_value_to_quantity(x[idx + 0], Time::zero(), _maxFlightTime);

        // Build the state
        segSettings.initialState =
            State(astro::State{ astro::Cartesian<astro::frames::primary>{
                                    convert_decision_value_to_quantity(x[idx + 1], _minPosition, _maxPosition),
                                    convert_decision_value_to_quantity(x[idx + 2], _minPosition, _maxPosition),
                                    convert_decision_value_to_quantity(x[idx + 3], _minPosition, _maxPosition),
                                    convert_decision_value_to_quantity(x[idx + 4], _minVelocity, _maxVelocity),
                                    convert_decision_value_to_quantity(x[idx + 5], _minVelocity, _maxVelocity),
                                    convert_decision_value_to_quantity(x[idx + 6], _minVelocity, _maxVelocity) },
                                _epoch });

        // Build out the burns
        segSettings.subsegBurns.reserve(_nBurnsPerSegment);
        for (std::size_t jj = 0; jj < _nBurnsPerSegment; ++jj) {
            segSettings.subsegBurns.push_back(DeltaV{
                convert_decision_value_to_quantity(x[idx + 7 + 3 * jj], Velocity::zero(), _maxDeltaV),
                convert_decision_value_to_quantity(x[idx + 8 + 3 * jj], Velocity::zero(), _maxDeltaV),
                convert_decision_value_to_quantity(x[idx + 9 + 3 * jj], Velocity::zero(), _maxDeltaV) });
        }

        // Store
        settings.segmentSettings.emplace_back(segSettings);
    }
    std::size_t idx      = _nDecisionsPerSegment * _nSegments;
    settings.initialBurn = DeltaV{ convert_decision_value_to_quantity(x[idx], Velocity::zero(), _maxDeltaV),
                                   convert_decision_value_to_quantity(x[idx + 1], Velocity::zero(), _maxDeltaV),
                                   convert_decision_value_to_quantity(x[idx + 2], Velocity::zero(), _maxDeltaV) };
    settings.finalBurn   = DeltaV{ convert_decision_value_to_quantity(x[idx + 3], Velocity::zero(), _maxDeltaV),
                                 convert_decision_value_to_quantity(x[idx + 4], Velocity::zero(), _maxDeltaV),
                                 convert_decision_value_to_quantity(x[idx + 5], Velocity::zero(), _maxDeltaV) };
    return Trajectory(settings);
}

DoubleVector SimsFlanaganProblem::encode_trajectory(const Trajectory& trajectory) const
{
    DoubleVector x(_nDecisions, 0.0);
    const auto& segments = trajectory.get_segments();
    for (std::size_t ii = 0; ii < _nSegments; ++ii) {
        const auto& segment = segments[ii];
        std::size_t idx     = _nDecisionsPerSegment * ii;

        x[idx + 0] = segment.get_duration().numerical_value_in(s);

        const auto initialState = segment.get_initial_state().get_cartesian();
        x[idx + 1] = ((initialState.get_x() - _minPosition) / (_maxPosition - _minPosition)).numerical_value_in(one);
        x[idx + 2] = ((initialState.get_y() - _minPosition) / (_maxPosition - _minPosition)).numerical_value_in(one);
        x[idx + 3] = ((initialState.get_z() - _minPosition) / (_maxPosition - _minPosition)).numerical_value_in(one);
        x[idx + 4] = ((initialState.get_vx() - _minVelocity) / (_maxVelocity - _minVelocity)).numerical_value_in(one);
        x[idx + 5] = ((initialState.get_vy() - _minVelocity) / (_maxVelocity - _minVelocity)).numerical_value_in(one);
        x[idx + 6] = ((initialState.get_vz() - _minVelocity) / (_maxVelocity - _minVelocity)).numerical_value_in(one);

        const auto& burns = segment.get_burns();
        for (std::size_t jj = 0; jj < burns.size(); ++jj) {
            const auto& burn    = burns[jj];
            x[idx + 7 + 3 * jj] = (burn.get_dx() / _maxDeltaV).numerical_value_in(one);
            x[idx + 8 + 3 * jj] = (burn.get_dy() / _maxDeltaV).numerical_value_in(one);
            x[idx + 9 + 3 * jj] = (burn.get_dz() / _maxDeltaV).numerical_value_in(one);
        }
    }
    const std::size_t idx   = _nDecisionsPerSegment * _nSegments;
    const auto& initialBurn = trajectory.get_initial_burn();
    x[idx]                  = (initialBurn.get_dx() / _maxDeltaV).numerical_value_in(one);
    x[idx + 1]              = (initialBurn.get_dy() / _maxDeltaV).numerical_value_in(one);
    x[idx + 2]              = (initialBurn.get_dz() / _maxDeltaV).numerical_value_in(one);
    const auto& finalBurn   = trajectory.get_final_burn();
    x[idx + 3]              = (finalBurn.get_dx() / _maxDeltaV).numerical_value_in(one);
    x[idx + 4]              = (finalBurn.get_dy() / _maxDeltaV).numerical_value_in(one);
    x[idx + 5]              = (finalBurn.get_dz() / _maxDeltaV).numerical_value_in(one);

    return x;
}

DoubleVector SimsFlanaganProblem::fitness(const DoubleVector& x) const
{
    // Build the trajectory and propagate
    Trajectory trajectory = decode_decision_vector(x);

    try {
        trajectory.propagate(_integrator, _vehicle);
    }
    catch (...) {
        return { std::numeric_limits<double>::infinity(),
                 std::numeric_limits<double>::infinity(),
                 std::numeric_limits<double>::infinity(),
                 std::numeric_limits<double>::infinity() };
    }

    // Compute objectives
    const auto continuityViolations = compute_continuity_violations(trajectory);
    const auto deltaVCosts          = compute_total_delta_v(trajectory);
    const Time totalTimeOfFlight    = compute_total_time_of_flight(trajectory);

    return { continuityViolations.positionViolation.numerical_value_in(km),
             continuityViolations.velocityViolation.numerical_value_in(km / s),
             deltaVCosts.totalDeltaV.numerical_value_in(km / s),
             totalTimeOfFlight.numerical_value_in(day) };
}

} // namespace hermes
} // namespace astrea