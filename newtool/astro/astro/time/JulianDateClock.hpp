#pragma once

#include <chrono>

#include <mp-units/systems/si/chrono.h>

namespace astro {

// Adapted from https://stackoverflow.com/questions/33964461/handling-julian-days-in-c11-14
struct JulianDateClock;

template <class Duration>
using JulianDateTime = std::chrono::time_point<JulianDateClock, Duration>;

struct JulianDateClock {
    using rep        = double;
    using period     = std::chrono::days::period;
    using duration   = std::chrono::duration<rep, period>;
    using time_point = std::chrono::time_point<JulianDateClock>;

    static constexpr bool is_steady = false;

    template <class Duration>
    static auto from_sys(std::chrono::sys_time<Duration> const& timePoint) noexcept
    {
        using namespace std;
        using namespace chrono;
        auto constexpr epoch = sys_days{ November / 24 / -4713 } + 12h;
        using ddays          = std::chrono::duration<long double, std::chrono::days::period>;
        if constexpr (sys_time<ddays>{ sys_time<Duration>::min() } < sys_time<ddays>{ epoch }) {
            return JulianDateTime{ timePoint - epoch };
        }
        else {
            // Duration overflows at the epoch.  Sub in new Duration that won't overflow.
            using D = std::chrono::duration<int64_t, ratio<1, 10'000'000>>;
            return JulianDateTime{ round<D>(timePoint) - epoch };
        }
    }

    template <class Duration>
    static auto to_sys(JulianDateTime<Duration> const& timePoint) noexcept
    {
        using namespace std::chrono;
        return sys_time{ timePoint - clock_cast<JulianDateClock>(sys_days{}) };
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

} // namespace astro