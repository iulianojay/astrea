

# File TerrestrialTimeClock.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**time**](dir_0abd23a91674297917c73da93ecec0fe.md) **>** [**clocks**](dir_9416058a812a1f6f42b7c1308c0ab22d.md) **>** [**TerrestrialTimeClock.hpp**](TerrestrialTimeClock_8hpp.md)

[Go to the documentation of this file](TerrestrialTimeClock_8hpp.md)


```C++

#pragma once

#include <chrono>
#include <ratio>

namespace astrea {
namespace astro {

struct TerrestrialTimeClock; // Forward declaration

template <class Duration>
using TerrestrialDateTime = std::chrono::time_point<TerrestrialTimeClock, Duration>;

struct TerrestrialTimeClock {
    using rep      = double;        
    using period   = std::ratio<1>; 
    using duration = std::chrono::duration<rep, period>; 
    using time_point = std::chrono::time_point<TerrestrialTimeClock>; 

    static constexpr bool is_steady = false; 

    static constexpr duration tt_tai_offset{ 32.184 };

    template <class Duration>
    static auto from_sys(std::chrono::sys_time<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        auto const tai = clock_cast<tai_clock>(timePoint);
        return TerrestrialDateTime<TerrestrialTimeClock::duration>{
            duration_cast<TerrestrialTimeClock::duration>(tai.time_since_epoch()) + tt_tai_offset
        };
    }

    template <class Duration>
    static auto to_sys(TerrestrialDateTime<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        auto const tai_dur = duration_cast<tai_clock::duration>(timePoint.time_since_epoch()) -
                             duration_cast<tai_clock::duration>(tt_tai_offset);
        return clock_cast<system_clock>(std::chrono::time_point<tai_clock>{ tai_dur });
    }

    static time_point now() noexcept
    {
        using namespace std::chrono;
        return from_sys(system_clock::now());
    }
};

using TerrestrialTime = TerrestrialTimeClock::time_point;

} // namespace astro
} // namespace astrea
```


