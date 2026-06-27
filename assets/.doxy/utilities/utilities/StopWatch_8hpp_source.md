

# File StopWatch.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**utilities**](dir_bc3eec91113c7b4aa38cf4b314cc4587.md) **>** [**utilities**](dir_e80a6df966dae334846d11eed150d587.md) **>** [**StopWatch.hpp**](StopWatch_8hpp.md)

[Go to the documentation of this file](StopWatch_8hpp.md)


```C++

#pragma once

#include <chrono>
#include <cmath>
#include <iostream>
#include <string>

#include <units/units.hpp>

namespace astrea {
namespace utilities {

class StopWatch {
  public:
    StopWatch() :
        _start(std::chrono::high_resolution_clock::now())
    {
    }

    void reset() { _start = std::chrono::high_resolution_clock::now(); }

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
```


