#pragma once

#include <chrono>

namespace astro {

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

} // namespace astro