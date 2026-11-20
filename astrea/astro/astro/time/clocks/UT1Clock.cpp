/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/time/clocks/UT1Clock.hpp>

#include <astro/eop/EarthOrientationParameters.hpp>
#include <astro/systems/eop_interpolation.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

UT1Clock::duration UT1Clock::ut1_minus_utc(const std::chrono::sys_time<duration>& utc)
{
    using namespace std::chrono;
    using EopRow = eop::EarthOrientationParameters::EopRow;

    const Date date{ clock_cast<JulianDateClock>(utc) };
    const auto taiMinusUt1 = eop::get_eop_interpolant(date).interpolate(&EopRow::TAI_UT1);

    // TAI - UTC was 10 s when integer leap seconds began in 1972, plus every leap second since
    const auto leapSeconds = get_leap_second_info(utc_clock::from_sys(floor<seconds>(utc))).elapsed;
    const duration taiMinusUtc{ 10.0 + static_cast<double>(leapSeconds.count()) };

    return taiMinusUtc - duration{ taiMinusUt1.numerical_value_in(mp_units::si::second) };
}

} // namespace astro
} // namespace astrea
