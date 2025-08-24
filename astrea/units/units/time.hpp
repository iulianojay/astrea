/**
 * @file time.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines various time units using the C++ chrono library.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
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