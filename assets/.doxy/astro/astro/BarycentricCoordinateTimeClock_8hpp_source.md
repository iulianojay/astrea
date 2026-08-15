

# File BarycentricCoordinateTimeClock.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**time**](dir_0abd23a91674297917c73da93ecec0fe.md) **>** [**clocks**](dir_9416058a812a1f6f42b7c1308c0ab22d.md) **>** [**BarycentricCoordinateTimeClock.hpp**](BarycentricCoordinateTimeClock_8hpp.md)

[Go to the documentation of this file](BarycentricCoordinateTimeClock_8hpp.md)


```C++

#pragma once

#include <chrono>
#include <numbers>
#include <ratio>

#include <astro/time/clocks/BarycentricDynamicalTimeClock.hpp>
#include <astro/time/clocks/JulianDateClock.hpp>

namespace astrea {
namespace astro {

struct BarycentricCoordinateTimeClock; // Forward declaration

template <class Duration>
using BarycentricCoordinateTimePoint = std::chrono::time_point<BarycentricCoordinateTimeClock, Duration>;

struct BarycentricCoordinateTimeClock {
    using rep      = double;        
    using period   = std::ratio<1>; 
    using duration = std::chrono::duration<rep, period>; 
    using time_point = std::chrono::time_point<BarycentricCoordinateTimeClock>; 

    static constexpr bool is_steady = false;          
    static constexpr rep Lb         = 1.550519768e-8; 
    static constexpr auto P0        = duration{ 6.55e-5 };
    static constexpr auto jdRef     = JulianDateClock::duration{ 2443144.5 };

    template <class Duration>
    static auto from_sys(std::chrono::sys_time<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        const auto tdb = duration_cast<duration>(BarycentricDynamicalTimeClock::from_sys(timePoint).time_since_epoch());
        const auto jd  = JulianDateClock::from_sys(timePoint).time_since_epoch();
        const auto jdDiff = duration_cast<days>(jd - jdRef).count();
        return BarycentricCoordinateTimePoint<duration>{ tdb + duration{ Lb * jdDiff + P0.count() } };
    }

    template <class Duration>
    static auto to_sys(BarycentricCoordinateTimePoint<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        static const auto sysRef = JulianDateClock::to_sys(JulianDateClock::time_point{ jdRef });
        static const auto tcbRef = BarycentricCoordinateTimeClock::from_sys(sysRef);
        const auto jdDiff        = duration_cast<days>(timePoint - tcbRef).count();
        const auto tdb           = timePoint.time_since_epoch() - duration{ Lb * jdDiff + P0.count() };
        return BarycentricDynamicalTimeClock::to_sys(
            BarycentricDynamicalTimeClock::time_point{ BarycentricDynamicalTimeClock::duration{ tdb } }
        );
    }

    static time_point now() noexcept
    {
        using namespace std::chrono;
        return from_sys(system_clock::now());
    }
};

using BarycentricCoordinateTime = BarycentricCoordinateTimeClock::time_point;

} // namespace astro
} // namespace astrea
```


