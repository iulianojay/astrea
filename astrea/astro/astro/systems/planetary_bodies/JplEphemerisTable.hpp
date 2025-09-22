/**
 * @file jpl_ephemeris/celestial_bodies/JplEphemerisTable.hpp
 * @brief Base class for any JPL Celestial-Body (CB) table
 *
 * @note Resource: https://www.celestialprogramming.com/jpl-ephemeris-format/jpl-ephemeris-format.html
 *
 * @note Adapted from https://github.com/mschmit6/jpl_ephemeris.git
 */

#pragma once

#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

//! Base class for any JPL Celestial-Body (CB) table
class JplEphemerisTable {

  protected:
    /**
     * @brief Get the index corresponding to the Chebyshev polynomial coefficients
     *
     * @param date Date for which the index is to be computed
     * @param timePerPoly Amount of time each set of polynomial coefficients covers
     *
     * @return Table lookup index
     */
    std::size_t get_index(const Date& date, const Time& timePerPoly);

    //! Lower bound on MJD J2K in the TDB time system
    static const Date START_DATE;

    //! Upper bound on MJD J2K in the TDB time system
    static const Date STOP_DATE;
};

} // namespace astro
} // namespace astrea
