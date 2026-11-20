/**
 * @file eop_interpolation.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Linear interpolation of the tabulated Earth Orientation Parameters.
 * @date 2026-11-20
 *
 * @copyright Copyright (c) 2026 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 */
#pragma once

#include <cstddef>

#include <units/units.hpp>

#include <astro/eop/EarthOrientationParameters.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {
namespace eop {

/**
 * @brief Pair of bracketing Earth Orientation Parameters rows and the linear interpolation fraction between them.
 */
struct EopInterpolant {
    const EarthOrientationParameters::EopRow& lower; //!< Row at or before the requested date
    const EarthOrientationParameters::EopRow& upper; //!< Row at or after the requested date
    Unitless fraction;                               //!< Interpolation fraction from lower to upper

    /**
     * @brief Linearly interpolate an EOP field at the requested date.
     *
     * @param field Pointer to the EOP row member to interpolate.
     * @return The interpolated value of the field.
     */
    template <typename Value_T>
    constexpr Value_T interpolate(Value_T EarthOrientationParameters::EopRow::* field) const noexcept
    {
        return lower.*field + fraction * (upper.*field - lower.*field);
    }
};

/**
 * @brief Find the Earth Orientation Parameters rows bracketing a given date.
 *
 * Dates outside the tabulated range are clamped to the first or last row.
 *
 * @param date The date (UTC) for which to find the bracketing rows.
 * @return EopInterpolant The bracketing rows and interpolation fraction.
 */
inline EopInterpolant get_eop_interpolant(const Date& date) noexcept
{
    using mp_units::one;

    static const auto& DATA = EarthOrientationParameters::DATA;
    static const auto MJD0  = DATA.front().MJD;
    static const auto MJDN  = DATA.back().MJD;
    static const auto STEP  = DATA[1].MJD - DATA[0].MJD;

    if (date <= MJD0) { return { DATA.front(), DATA.front(), 0.0 * one }; }
    else if (date >= MJDN) {
        return { DATA.back(), DATA.back(), 0.0 * one };
    }

    // Assume the step is consistent (which it seems to be) and that the data is sorted by MJD (which it seems to be)
    // TODO: Add introspective properties to the EOP data to allow for more robust searching (e.g., binary search, etc.)
    const auto guessIdx = static_cast<std::size_t>((date - MJD0) / STEP);
    const auto& row     = DATA[guessIdx];

    if (row.MJD == date) { return { row, row, 0.0 * one }; }
    else if (row.MJD > date) {
        const auto& prevRow = DATA[guessIdx - 1];
        return { prevRow, row, (date - prevRow.MJD) / (row.MJD - prevRow.MJD) };
    }

    const auto& nextRow = DATA[guessIdx + 1];
    return { row, nextRow, (date - row.MJD) / (nextRow.MJD - row.MJD) };
}

} // namespace eop
} // namespace astro
} // namespace astrea
