# Time Systems

Astrea provides a comprehensive time handling system built on top of modern C++ chrono facilities. The time module provides date handling, interval management, and Julian date conversions for astronomical applications.

## Core Components

### Date Class

The `Date` class provides functionality for handling dates with astronomical precision:

- Conversion between string representations and Julian dates
- Support for various date formats using standard strftime/strptime patterns  
- Sidereal time calculations
- Clock conversions

```cpp
#include <astro/time/Date.hpp>

// Convert string epoch to Julian date
JulianDate jd = epoch_to_julian_date("2024-01-01 12:00:00", "%Y-%m-%d %H:%M:%S");

// Convert Julian date back to string
std::string dateStr = julian_date_to_epoch(jd, "%Y-%m-%d %H:%M:%S");
```

### Julian Date Clock

Astrea features a custom `JulianDateClock` implementation that provides:

- Native Julian date arithmetic
- Conversion to/from system clocks
- High-precision time point representation using double precision for fractional days
- C++20 chrono compatibility

```cpp
#include <astro/time/JulianDateClock.hpp>

// Julian date time points
JulianDateTime<std::chrono::milliseconds> jdTime;

// Clock conversions
auto systemTime = JulianDateClock::to_system_clock(jdTime);
auto julianTime = JulianDateClock::from_system_clock(systemTime);
```

### Time Intervals

The `Interval` class represents time spans for propagation analysis:

- Start and end time management
- Duration calculations
- Propagation time tracking

```cpp
#include <astro/time/Interval.hpp>

Time startTime = epoch_to_julian_date("2024-01-01 00:00:00");
Time endTime = epoch_to_julian_date("2024-01-01 01:30:00");

Interval propagationInterval(startTime, endTime);
Time duration = propagationInterval.propTime - propagationInterval.start;
```

## Integration with mp-units

All time quantities in Astrea are strongly typed using mp-units, providing compile-time dimensional analysis and preventing unit conversion errors. Time durations automatically work with the physical quantity system.