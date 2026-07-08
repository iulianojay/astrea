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

#include <units/units.hpp>

#include <hermes/sims-flanagan/model.hpp>
#include <hermes/sims-flanagan/settings.hpp>
#include <hermes/types/typedefs.hpp>

namespace astrea {
namespace hermes {

/**
 * @brief A class representing the Sims-Flanagan trajectory optimization problem, which can be used with pagmo for optimization
 */
class SimsFlanaganProblem {
  public:
    /**
     * @brief Default constructor for the SimsFlanaganProblem class
     */
    SimsFlanaganProblem() = default;

    /**
     * @brief Construct a new SimsFlanaganProblem object from the given settings
     *
     * @param settings The settings for the Sims-Flanagan problem
     */
    SimsFlanaganProblem(const SimsFlanaganSettings& settings) :
        _epoch(settings.epoch),
        _nSegments(settings.nSegments),
        _nSubsegmentsPerSegment(settings.nSubsegmentsPerSegment),
        _maxFlightTime(settings.maxFlightTime),
        _minPosition(settings.minPosition),
        _maxPosition(settings.maxPosition),
        _minVelocity(settings.minVelocity),
        _maxVelocity(settings.maxVelocity),
        _maxDeltaV(settings.maxDeltaV),
        _initialCartesian(settings.initialCartesian),
        _targetCartesian(settings.targetCartesian),
        _integrator(settings.integrator),
        _vehicle(settings.vehicle),
        _nBurnsPerSegment(_nSubsegmentsPerSegment - 1),
        _nDecisionsPerSegment(8 + 3 * _nBurnsPerSegment),
        _nDecisions(_nDecisionsPerSegment * _nSegments)
    {
    }

    /**
     * @brief Default destructor for the SimsFlanaganProblem class
     */
    ~SimsFlanaganProblem() = default;

    SimsFlanaganProblem(const SimsFlanaganProblem&)            = default;
    SimsFlanaganProblem(SimsFlanaganProblem&&)                 = default;
    SimsFlanaganProblem& operator=(const SimsFlanaganProblem&) = default;
    SimsFlanaganProblem& operator=(SimsFlanaganProblem&&)      = default;

    /**
     * @brief Get the number of decision variables for this problem
     *
     * @return std::size_t The number of decision variables for this problem
     */
    std::size_t get_nx() const;

    /**
     * @brief Get the number of objectives for this problem
     *
     * @return std::size_t The number of objectives for this problem
     */
    std::size_t get_nic() const;

    /**
     * @brief Get the number of constraints for this problem
     *
     * @return std::size_t The number of constraints for this problem
     */
    std::size_t get_nobj() const;

    /**
     * @brief Get the bounds for the decision variables of this problem
     *
     * @return std::pair<vector_double, vector_double> A pair of vectors representing the lower and upper bounds for the decision variables of this problem
     */
    std::pair<DoubleVector, DoubleVector> get_bounds() const;

    /**
     * @brief Evaluate the fitness of a given decision vector
     *
     * @param x The decision vector to evaluate
     * @return vector_double The fitness values for the given decision vector
     */
    DoubleVector fitness(const DoubleVector& x) const;

    /**
     * @brief Get the name of this problem
     *
     * @return std::string The name of this problem
     */
    std::string get_name() const;

    /**
     * @brief Decode a decision vector into a Trajectory object
     *
     * @param x The decision vector to decode
     * @return Trajectory The Trajectory object decoded from the given decision vector
     */
    Trajectory decode_decision_vector(const DoubleVector& x) const;

    /**
     * @brief Encode a Trajectory object into a decision vector
     *
     * @param trajectory The Trajectory object to encode
     * @return DoubleVector The decision vector encoded from the given Trajectory object
     */
    DoubleVector encode_trajectory(const Trajectory& trajectory) const;

  private:
    astro::Date _epoch;                  //!< The epoch for the trajectory
    std::size_t _nSegments;              //!< The number of segments in the trajectory
    std::size_t _nSubsegmentsPerSegment; //!< The number of subsegments per segment in the trajectory
    Time _maxFlightTime;                 //!< The maximum flight time for the entire trajectory
    Distance _minPosition;               //!< The minimum position value for the decision variables
    Distance _maxPosition;               //!< The maximum position value for the decision variables
    Velocity _minVelocity;               //!< The minimum velocity value for the decision variables
    Velocity _maxVelocity;               //!< The maximum velocity value for the decision variables
    Velocity _maxDeltaV;                 //!< The maximum delta-v value for the decision variables

    astro::Cartesian<astro::frames::primary> _initialCartesian; //!< The initial state of the first segment
    astro::Cartesian<astro::frames::primary> _targetCartesian;  //!< The final state of the last segment

    mutable astro::Integrator _integrator; //!< The integrator to use for propagating the trajectory
    mutable astro::Vehicle _vehicle;       //!< The vehicle to use for propagating the trajectory

    std::size_t _nBurnsPerSegment; //!< The number of burns per segment in the trajectory (equal to nSubsegmentsPerSegment - 1)
    std::size_t _nDecisionsPerSegment; //!< The number of decision variables per segment in the trajectory (equal to 8 + 3 * nBurnsPerSegment)
    std::size_t _nDecisions; //!< The total number of decision variables for the trajectory (equal to nDecisionsPerSegment * nSegments)
};

} // namespace hermes
} // namespace astrea