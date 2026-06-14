

# File GeocentricCoordinateTimeClock.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**time**](dir_0abd23a91674297917c73da93ecec0fe.md) **>** [**clocks**](dir_9416058a812a1f6f42b7c1308c0ab22d.md) **>** [**GeocentricCoordinateTimeClock.hpp**](GeocentricCoordinateTimeClock_8hpp.md)

[Go to the documentation of this file](GeocentricCoordinateTimeClock_8hpp.md)


```C++

#pragma once

#include <chrono>
#include <ratio>

#include <astro/time/clocks/JulianDateClock.hpp>
#include <astro/time/clocks/TerrestrialTimeClock.hpp>

namespace astrea {
namespace astro {

struct GeocentricCoordinateTimeClock; // Forward declaration

template <class Duration>
using GeocentricCoordinateDateTime = std::chrono::time_point<GeocentricCoordinateTimeClock, Duration>;

struct GeocentricCoordinateTimeClock {
    using rep      = double;        
    using period   = std::ratio<1>; 
    using duration = std::chrono::duration<rep, period>; 
    using time_point = std::chrono::time_point<GeocentricCoordinateTimeClock>; 

    static constexpr bool is_steady = false; 
    static constexpr rep Lg{ 6.969290134e-10 }; 
    static constexpr JulianDateClock::duration jdRef{ 2443144.5 };

    template <class Duration>
    static auto from_sys(std::chrono::sys_time<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        const auto tt = TerrestrialTimeClock::from_sys(timePoint).time_since_epoch();
        const auto jd = JulianDateClock::from_sys(timePoint).time_since_epoch();
        return GeocentricCoordinateDateTime{ tt + Lg / (1.0 - Lg) * (jd - jdRef) };
    }

    template <class Duration>
    static auto to_sys(GeocentricCoordinateDateTime<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        static const auto sysRef = JulianDateClock::to_sys(JulianDateClock::time_point{ jdRef });
        static const auto tgcRef = GeocentricCoordinateTimeClock::from_sys(sysRef);
        const auto tt = timePoint.time_since_epoch() - Lg / (1.0 - Lg) * duration_cast<days>(timePoint - tgcRef);
        return TerrestrialTimeClock::to_sys(TerrestrialTimeClock::time_point{ TerrestrialTimeClock::duration{ tt } });
    }

    static time_point now() noexcept
    {
        using namespace std::chrono;
        return from_sys(system_clock::now());
    }
};

using GeocentricCoordinateTime = GeocentricCoordinateTimeClock::time_point;

} // namespace astro
} // namespace astrea
```


