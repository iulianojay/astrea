

# File JulianDateClock.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**time**](dir_0abd23a91674297917c73da93ecec0fe.md) **>** [**clocks**](dir_9416058a812a1f6f42b7c1308c0ab22d.md) **>** [**JulianDateClock.hpp**](JulianDateClock_8hpp.md)

[Go to the documentation of this file](JulianDateClock_8hpp.md)


```C++

#pragma once

#include <chrono>

#include <mp-units/systems/si/chrono.h>

namespace astrea {
namespace astro {

struct JulianDateClock; // Forward declaration

template <class Duration>
using JulianDateTime = std::chrono::time_point<JulianDateClock, Duration>;

struct JulianDateClock {
    using rep    = double; 
    using period = std::chrono::days::period;            
    using duration = std::chrono::duration<rep, period>; 
    using time_point = std::chrono::time_point<JulianDateClock>; 

    static constexpr bool is_steady =
        false; 

    template <class Duration>
    static auto from_sys(std::chrono::sys_time<Duration> const& timePoint) noexcept
    {
        using namespace std;
        using namespace chrono;
        auto constexpr epoch = sys_days{ November / 24 / -4713 } + 12h;
        using ddays          = std::chrono::duration<long double, std::chrono::days::period>;
        if constexpr (sys_time<ddays>{ sys_time<Duration>::min() } < sys_time<ddays>{ epoch }) {
            return JulianDateTime<decltype(timePoint - epoch)>{ timePoint - epoch };
        }
        else {
            // Duration overflows at the epoch.  Sub in new Duration that won't overflow.
            using D = std::chrono::duration<int64_t, ratio<1, 10'000'000>>;
            return JulianDateTime<D>{ round<D>(timePoint) - epoch };
        }
    }

    template <class Duration>
    static auto to_sys(JulianDateTime<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        return sys_time<decltype(timePoint - clock_cast<JulianDateClock>(sys_days{}))>{ timePoint -
                                                                                        clock_cast<JulianDateClock>(sys_days{}) };
    }

    static time_point now() noexcept
    {
        using namespace std::chrono;
        return from_sys(system_clock::now());
    }
};

using JulianDate = JulianDateClock::time_point;

static constexpr JulianDate J2000(JulianDateClock::duration{ 2451545.0 });

static constexpr mp_units::quantity_point J2K = J2000;

static constexpr JulianDate MJD0(JulianDateClock::duration{ 2400000.5 });

static constexpr mp_units::quantity_point MJDStart = MJD0;

} // namespace astro
} // namespace astrea
```


