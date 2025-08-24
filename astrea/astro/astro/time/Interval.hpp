/**
 * @file Interval.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Interval class, which represents a time interval with a start and end time.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <astro/types/typedefs.hpp>

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