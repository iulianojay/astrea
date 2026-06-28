/**
 * @file StopWatch.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A simple stopwatch utility for measuring elapsed time.
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

#include <chrono>
#include <cmath>
#include <iostream>
#include <string>

#include <units/units.hpp>

namespace astrea {
namespace utilities {

/**
 * @brief A simple stopwatch utility for measuring elapsed time.
 *
 * The StopWatch class provides a convenient way to measure elapsed time in seconds.
 * It uses the high-resolution clock from the <chrono> library to provide accurate timing.
 */
class StopWatch {
  public:
    /**
     * @brief Constructs a StopWatch and starts timing.
     */
    StopWatch() :
        _start(std::chrono::high_resolution_clock::now())
    {
    }

    /**
     * @brief Resets the stopwatch to the current time.
     */
    void reset() { _start = std::chrono::high_resolution_clock::now(); }

    /**
     * @brief Measures the elapsed time in seconds since the last reset or construction.
     *
     * @return Time The elapsed time.
     */
    Time measure() const
    {
        using namespace std::chrono;
        using mp_units::si::unit_symbols::s;

        auto now = high_resolution_clock::now();
        return duration_cast<nanoseconds>(now - _start).count() / 1.0e9 * s;
    }

  private:
    std::chrono::high_resolution_clock::time_point _start; // The starting time point of the stopwatch.
};

} // namespace utilities
} // namespace astrea