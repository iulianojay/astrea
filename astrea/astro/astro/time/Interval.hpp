/**
 * @file Interval.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Interval class, which represents a time interval with a start and end time.
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
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

#include <units/units.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Represents a time interval with a start and end time.
 *
 * This class is used to define a time interval in the context of astrodynamics.
 * It contains two Time objects: one for the start of the interval and one for the end.
 */
class Interval {
  public:
    /**
     * @brief Default constructor for Interval.
     *
     * Initializes both start and end times to their default values.
     */
    Interval() = default;

    /**
     * @brief Constructs an Interval object with the specified start and end times.
     *
     * @param start The start time of the interval.
     * @param end The end time of the interval.
     */
    Interval(const Time& start, const Time& end) :
        start(start),
        end(end) {};

    /**
     * @brief Default destructor for Interval.
     */
    ~Interval() = default;

    Time start; ///< The start time of the interval.
    Time end;   ///< The end time of the interval.
};

} // namespace astro
} // namespace astrea