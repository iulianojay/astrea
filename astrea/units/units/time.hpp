/**
 * @file time.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines various time units using the C++ chrono library.
 * @version 0.1
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

namespace astrea {

// nanoseconds
using nanoseconds = std::chrono::duration<double, std::nano>;

// microseconds
using microseconds = std::chrono::duration<double, std::micro>;

// milliseconds
using milliseconds = std::chrono::duration<double, std::milli>;

// seconds
using seconds = std::chrono::duration<double>;

// minutes
using minutes = std::chrono::duration<double, std::ratio<60>>;

// hours
using hours = std::chrono::duration<double, std::ratio<3600>>;

// days
using days = std::chrono::duration<double, std::ratio<86400>>;

// weeks
using weeks = std::chrono::duration<double, std::ratio<604800>>;

// months
using months = std::chrono::duration<double, std::ratio<2629746>>;

// years
using years = std::chrono::duration<double, std::ratio<31556952>>;

} // namespace astrea