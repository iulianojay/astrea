/**
 * @file Segment.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Segment module
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

#include <utilities/IdProvider.hpp>

#include <hermes/sims-flanagan/model/DeltaV.hpp>
#include <hermes/sims-flanagan/model/State.hpp>
#include <hermes/sims-flanagan/model/Subsegment.hpp>
#include <hermes/sims-flanagan/settings.hpp>
#include <hermes/types/typedefs.hpp>

namespace astrea {
namespace hermes {

/**
 * @brief A class representing a segment of a Sims-Flanagan trajectory, consisting of multiple subsegments
 */
class Segment {
  public:
    /**
     * @brief Construct a new Segment object
     *
     * @param subsegments The subsegments that make up the segment
     * @param burns The delta-v burns that occur during the segment
     * @param duration The total duration of the segment
     * @param isForward Whether the segment is forward-propagating (true) or backward
     */
    Segment(const std::vector<Subsegment>& subsegments = {}, const std::vector<DeltaV>& burns = {}, const Time& duration = Time::zero(), bool isForward = true);

    /**
     * @brief Construct a new Segment object from the given settings
     *
     * @param settings The settings for the segment
     */
    Segment(const SegmentSettings& settings);

    /**
     * @brief Default destructor for the Segment class
     */
    ~Segment() = default;

    /**
     * @brief Create a new Segment object representing a ballistic trajectory
     *
     * @param integrator The integrator to use for propagating the trajectory
     * @param vehicle The vehicle to use for propagating the trajectory
     * @param initialState The initial state of the trajectory
     * @param segmentTime The total time of flight for the segment
     * @param nSubsegments The number of subsegments to divide the segment into
     * @return Segment A new Segment object representing the ballistic trajectory
     */
    static Segment
        ballistic(astro::Integrator& integrator, astro::Vehicle& vehicle, const State& initialState, const Time& segmentTime, std::size_t nSubsegments);

    /**
     * @brief Propagate the segment without storing the state history
     *
     * @param integrator The integrator to use for propagating the trajectory
     * @param vehicle The vehicle to use for propagating the trajectory
     */
    void propagate_no_storage(astro::Integrator& integrator, astro::Vehicle& vehicle);

    /**
     * @brief Propagate the segment and return the state history
     *
     * @param integrator The integrator to use for propagating the trajectory
     * @param vehicle The vehicle to use for propagating the trajectory
     * @return astro::StateHistory The state history of the propagated segment
     */
    astro::StateHistory propagate(astro::Integrator& integrator, astro::Vehicle& vehicle);

    /**
     * @brief Get the unique identifier for this Segment instance
     *
     * @return std::size_t The unique identifier for this Segment instance
     */
    std::size_t get_id() const;

    /**
     * @brief Get the subsegments that make up this segment
     *
     * @return const std::vector<Subsegment>& The subsegments that make up this segment
     */
    const std::vector<Subsegment>& get_subsegments() const;

    /**
     * @brief Get the duration of the segment
     *
     * @return const Time& The duration of the segment
     */
    const Time& get_duration() const;

    /**
     * @brief Get the state of the trajectory at the beginning of the segment
     *
     * @return const State& The state of the trajectory at the beginning of the segment
     */
    const State& get_initial_state() const;

    /**
     * @brief Get the state of the trajectory at the end of the segment
     *
     * @return const State& The state of the trajectory at the end of the segment
     */
    const State& get_final_state() const;

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

    /**
     * @brief Get the burns that occur during this segment
     *
     * @return const std::vector<DeltaV>& The burns that occur during this segment
     */
    const std::vector<DeltaV>& get_burns() const;

    /**
     * @brief Check if the segment is forward-propagating
     *
     * @return true If the segment is forward-propagating
     * @return false If the segment is backward-propagating
     */
    bool is_forward() const;

  private:
    std::size_t _id;
    std::vector<Subsegment> _subsegments;
    std::vector<DeltaV> _burns;
    bool _isForward;
    Time _duration;
};

} // namespace hermes
} // namespace astrea