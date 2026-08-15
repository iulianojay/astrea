

# File BarycentricDynamicalTimeClock.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**time**](dir_0abd23a91674297917c73da93ecec0fe.md) **>** [**clocks**](dir_9416058a812a1f6f42b7c1308c0ab22d.md) **>** [**BarycentricDynamicalTimeClock.hpp**](BarycentricDynamicalTimeClock_8hpp.md)

[Go to the documentation of this file](BarycentricDynamicalTimeClock_8hpp.md)


```C++

#pragma once

#include <chrono>
#include <numbers>
#include <ratio>

#include <astro/time/clocks/JulianDateClock.hpp>
#include <astro/time/clocks/TerrestrialTimeClock.hpp>

namespace astrea {
namespace astro {

struct BarycentricDynamicalTimeClock; // Forward declaration

template <class Duration>
using BarycentricDynamicalTimePoint = std::chrono::time_point<BarycentricDynamicalTimeClock, Duration>;

struct BarycentricDynamicalTimeClock {
    using rep      = double;        
    using period   = std::ratio<1>; 
    using duration = std::chrono::duration<rep, period>; 
    using time_point = std::chrono::time_point<BarycentricDynamicalTimeClock>; 

    static constexpr bool is_steady = false; 
    static constexpr auto jdRef     = JulianDateClock::duration{ 2451545.0 };

    template <class Duration>
    static auto from_sys(std::chrono::sys_time<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        const auto tt     = duration_cast<duration>(TerrestrialTimeClock::from_sys(timePoint).time_since_epoch());
        const auto jd     = JulianDateClock::from_sys(timePoint).time_since_epoch();
        const auto jdDiff = duration_cast<days>(jd - jdRef).count();
        const auto Me = (357.53 + 0.9856003 * jdDiff) * (std::numbers::pi / 180.0); // Mean anomaly of the Earth in rad
        return BarycentricDynamicalTimePoint<duration>{ tt + duration{ 0.001658 * std::sin(Me) + 0.00001385 * std::sin(2 * Me) } };
    }

    template <class Duration>
    static auto to_sys(BarycentricDynamicalTimePoint<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        static const auto sysRef = JulianDateClock::to_sys(JulianDateClock::time_point{ jdRef });
        static const auto tbdRef = BarycentricDynamicalTimeClock::from_sys(sysRef);
        const auto Me = (357.53 + 0.9856003 * duration_cast<days>(timePoint - tbdRef).count()) * (std::numbers::pi / 180.0); // Mean anomaly of the Earth in rad
        const auto tt = timePoint.time_since_epoch() - duration{ 0.001658 * std::sin(Me) + 0.00001385 * std::sin(2 * Me) };
        return TerrestrialTimeClock::to_sys(TerrestrialTimeClock::time_point{ TerrestrialTimeClock::duration{ tt } });
    }

    static time_point now() noexcept
    {
        using namespace std::chrono;
        return from_sys(system_clock::now());
    }
};

using BarycentricDynamicalTime = BarycentricDynamicalTimeClock::time_point;

} // namespace astro
} // namespace astrea
```


