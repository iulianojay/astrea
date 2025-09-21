/**
 * @file jpl_ephemeris/celestial_bodies/JplEphemerisTable.hpp
 * @brief Base class for any JPL Celestial-Body (CB) table
 *
 * @note Resource: https://www.celestialprogramming.com/jpl-ephemeris-format/jpl-ephemeris-format.html
 *
 * @note Adapted from https://github.com/mschmit6/jpl_ephemeris.git
 */

#pragma once

namespace astrea {
namespace astro {
namespace jpl_ephemeris {

//! Base class for any JPL Celestial-Body (CB) table
class JplEphemerisTable {

  protected:
    JplEphemerisTable() :
        _startDate("1/1/2000 12:00:00"),
        _stopDate("1/1/2100 12:00:00") {};

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
    static const Date _startDate;

    //! Upper bound on MJD J2K in the TDB time system
    static const Date _stopDate;
};

} // namespace jpl_ephemeris
} // namespace astro
} // namespace astrea
