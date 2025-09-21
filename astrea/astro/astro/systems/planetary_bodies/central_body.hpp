/**
 * @file jpl_ephemeris/celestial_bodies/central_body.hpp
 * @brief Defines enum class for specifying the central body used when computing the position/velocity of a Celestial Body
 *
 * @note Adapted from https://github.com/mschmit6/jpl_ephemeris.git
 */

#pragma once

namespace astrea {
namespace astro {
namespace jpl_ephemeris {

//! Specifies the central body used when computing the position/velocity of a Celestial Body
enum class CentralBody : int {
    SSB   = 0, //!< Use the Solar System Barycenter (SSB) as the central body
    Sun   = 1, //!< Use the Sun as the central body
    Earth = 2, //!< Use Earth as the central body
    Moon  = 3, //!< Use the Moon as the central body
};

} // namespace jpl_ephemeris
} // namespace astro
} // namespace astrea