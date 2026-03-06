

# File time.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**units**](dir_69ee7df8d286dff8402d348058eb58eb.md) **>** [**units**](dir_8ace873b55bc88b2d1a73a241bbdd96b.md) **>** [**time.hpp**](time_8hpp.md)

[Go to the documentation of this file](time_8hpp.md)


```C++

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
```


