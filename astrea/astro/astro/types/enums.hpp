#pragma once

#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

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
    EARTH_BARYCENTER,
    MARS_BARYCENTER,
    JUPITER_BARYCENTER,
    SATURN_BARYCENTER,
    URANUS_BARYCENTER,
    NEPTUNE_BARYCENTER,

    // Other
    CUSTOM
};

enum class CelestialBodyType : EnumType { UNSET, STAR, PLANET, MOON };

enum class SystemCenter : EnumType { CENTRAL_BODY, BARYCENTER };

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
