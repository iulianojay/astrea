/**
 * @file State.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the State module
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

#include <astro/astro.hpp>
#include <units/units.hpp>
#include <utilities/IdProvider.hpp>

namespace astrea {
namespace hermes {

/**
 * @brief A class representing the state of the trajectory at a given point in time
 */
class State {
  public:
    /**
     * @brief Construct a new State object
     *
     * @param state The state of the trajectory at a given point in time
     */
    State(const astro::State& state = {});

    /**
     * @brief Default destructor for the State class
     */
    ~State() = default;

    /**
     * @brief Get the unique identifier for this State instance
     *
     * @return std::size_t The unique identifier for this State instance
     */
    std::size_t get_id() const;

    /**
     * @brief Get the state of the trajectory at a given point in time
     *
     * @return const astro::State& The state of the trajectory at a given point in time
     */
    const astro::State& get_state() const;

  private:
    std::size_t _id;     //!< The unique identifier for this State instance
    astro::State _state; //!< The state of the trajectory at a given point in time
};

} // namespace hermes
} // namespace astrea