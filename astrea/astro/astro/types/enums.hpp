/**
 * @file enums.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Enumeration types for astrodynamics.
 * @date 2025-10-09
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include <stdint.h>

namespace astrea {
namespace astro {

/**
 * @brief Type definition for enumeration types.
 */
using EnumType = uint32_t;

/**
 * @brief Celestial body identifiers.
 */
enum class CelestialBodyId : EnumType {
    UNSET,

    // Solar System Bodies
    SUN,
    MERCURY,
    VENUS,
    EARTH,
    MOON,
    MARS,
    PHOBOS,
    DEIMOS,
    JUPITER,
    GANYMEDE,
    CALLISTO,
    IO,
    EUROPA,
    SATURN,
    TITAN,
    RHEA,
    IAPETUS,
    URANUS,
    TITANIA,
    OBERON,
    NEPTUNE,
    TRITON,

    // Barycenters
    SOLAR_SYSTEM_BARYCENTER,
    MERCURY_BARYCENTER,
    VENUS_BARYCENTER,
    EARTH_BARYCENTER,
    MARS_BARYCENTER,
    JUPITER_BARYCENTER,
    SATURN_BARYCENTER,
    URANUS_BARYCENTER,
    NEPTUNE_BARYCENTER,

    // Other
    CUSTOM
};

/**
 * @brief Celestial body types.
 */
enum class CelestialBodyType : EnumType { UNSET, STAR, PLANET, MOON };

/**
 * @brief System center types.
 */
enum class SystemCenter : EnumType { CENTRAL_BODY, BARYCENTER };

/**
 * @brief Reference frames axes.
 */
enum class FrameAxis : EnumType {
    /** International Celestial Reference Frame */
    ICRF,
    /** Mean equinox of standard epoch J2000 */
    J2000,
    /** Body-fixed frame */
    BODY_FIXED,
    /** Local vertical/local horizontal frame */
    LVLH,
    /** Radial/Along-track/Cross-track frame */
    RIC,
    /** Velocity/Normal/Body frame */
    VNB
};

} // namespace astro
} // namespace astrea
