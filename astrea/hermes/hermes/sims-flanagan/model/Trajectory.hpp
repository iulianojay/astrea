/**
 * @file Trajectory.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Trajectory module
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

#include <astro/astro.hpp>
#include <utilities/IdProvider.hpp>

#include <hermes/sims-flanagan/model/DeltaV.hpp>
#include <hermes/sims-flanagan/model/Segment.hpp>
#include <hermes/sims-flanagan/model/State.hpp>
#include <hermes/sims-flanagan/settings.hpp>
#include <hermes/types/typedefs.hpp>

namespace astrea {
namespace hermes {

/**
 * @brief A class representing a trajectory consisting of multiple segments, each with its own initial and final states and burns
 */
class Trajectory {
  public:
    /**
     * @brief Construct a new Trajectory object
     *
     * @param segments The segments that make up the trajectory
     */
    Trajectory(const std::vector<Segment>& segments = {});

    /**
     * @brief Construct a new Trajectory object from the given settings
     *
     * @param settings The settings for the trajectory
     */
    Trajectory(const TrajectorySettings& settings);

    /**
     * @brief Default destructor for the Trajectory class
     */
    ~Trajectory() = default;

    /**
     * @brief Create a new Trajectory object representing a ballistic trajectory
     *
     * @param integrator The integrator to use for propagating the trajectory
     * @param vehicle The vehicle to use for propagating the trajectory
     * @param initialState The initial state of the trajectory
     * @param propTime The total propagation time for the trajectory
     * @param nSegments The number of segments in the trajectory
     * @param nSubsegmentsPerSegment The number of subsegments per segment in the trajectory
     * @return Trajectory A new Trajectory object representing a ballistic trajectory with the given parameters
     */
    static Trajectory
        ballistic(astro::Integrator& integrator, astro::Vehicle& vehicle, const State& initialState, const Time& propTime, std::size_t nSegments, std::size_t nSubsegmentsPerSegment);

    /**
     * @brief Propagate the trajectory without storing the state history
     *
     * @param integrator The integrator to use for propagating the trajectory
     * @param vehicle The vehicle to use for propagating the trajectory
     */
    void propagate_no_storage(astro::Integrator& integrator, astro::Vehicle& vehicle);

    /**
     * @brief Propagate the trajectory and return the state history
     *
     * @param integrator The integrator to use for propagating the trajectory
     * @param vehicle The vehicle to use for propagating the trajectory
     * @return astro::StateHistory The state history of the propagated trajectory
     */
    astro::StateHistory propagate(astro::Integrator& integrator, astro::Vehicle& vehicle);

    /**
     * @brief Get the unique identifier for this Trajectory instance
     *
     * @return std::size_t The unique identifier for this Trajectory instance
     */
    std::size_t get_id() const;

    /**
     * @brief Get the segments that make up this trajectory
     *
     * @return const std::vector<Segment>& The segments that make up this trajectory
     */
    const std::vector<Segment>& get_segments() const;

    /**
     * @brief Get the state of the trajectory at the beginning of the trajectory
     *
     * @return const State& The state of the trajectory at the beginning of the trajectory
     */
    const State& get_initial_state() const;

    /**
     * @brief Get the state of the trajectory at the end of the trajectory
     *
     * @return const State& The state of the trajectory at the end of the trajectory
     */
    const State& get_final_state() const;

    /**
     * @brief Get the segment with the given ID
     *
     * @param id The unique identifier of the segment to retrieve
     * @return OptionalRef<const Segment> An optional reference to the segment with the given ID, or std::nullopt if no such segment exists
     */
    OptionalRef<const Segment> get_segment(std::size_t id) const;

    /**
     * @brief Get the segment with the given ID
     *
     * @param id The unique identifier of the segment to retrieve
     * @return OptionalRef<Segment> An optional reference to the segment with the given ID, or std::nullopt if no such segment exists
     */
    OptionalRef<Segment> get_segment(std::size_t id);

    /**
     * @brief Get the subsegment with the given ID
     *
     * @param id The unique identifier of the subsegment to retrieve
     * @return OptionalRef<const Subsegment> An optional reference to the subsegment with the given ID, or std::nullopt if no such subsegment exists
     */
    OptionalRef<const Subsegment> get_subsegment(std::size_t id) const;

    /**
     * @brief Get the subsegment with the given ID
     *
     * @param id The unique identifier of the subsegment to retrieve
     * @return OptionalRef<Subsegment> An optional reference to the subsegment with the given ID, or std::nullopt if no such subsegment exists
     */
    OptionalRef<Subsegment> get_subsegment(std::size_t id);

    /**
     * @brief Get the node with the given ID
     *
     * @param id The unique identifier of the node to retrieve
     * @return OptionalRef<const Node> An optional reference to the node with the given ID, or std::nullopt if no such node exists
     */
    OptionalRef<const Node> get_node(std::size_t id) const;

    /**
     * @brief Get the node with the given ID
     *
     * @param id The unique identifier of the node to retrieve
     * @return OptionalRef<Node> An optional reference to the node with the given ID, or std::nullopt if no such node exists
     */
    OptionalRef<Node> get_node(std::size_t id);

    /**
     * @brief Get the state with the given ID
     *
     * @param id The unique identifier of the state to retrieve
     * @return OptionalRef<const State> An optional reference to the state with the given ID, or std::nullopt if no such state exists
     */
    OptionalRef<const State> get_state(std::size_t id) const;

    /**
     * @brief Get the state with the given ID
     *
     * @param id The unique identifier of the state to retrieve
     * @return OptionalRef<State> An optional reference to the state with the given ID, or std::nullopt if no such state exists
     */
    OptionalRef<State> get_state(std::size_t id);

  private:
    std::size_t _id;                //!< Unique identifier for this Trajectory instance
    std::vector<Segment> _segments; //!< The segments that make up this trajectory
    DeltaV _initialBurn;            //!< The initial burn of the trajectory
    DeltaV _finalBurn;              //!< The final burn of the trajectory
    std::vector<DeltaV> _burns;     //!< The burns for each segment in the trajectory
    astro::Date _epoch;             //!< The epoch of the trajectory
};

} // namespace hermes
} // namespace astrea