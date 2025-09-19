#pragma once

#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

enum class PlanetaryBody : EnumType {
    UNSET,
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
    CUSTOM
};

enum class CelestialBodyType : EnumType { UNSET, STAR, PLANET, MOON };

enum class SystemCenter : EnumType { CENTRAL_BODY, BARYCENTER };

} // namespace astro
} // namespace astrea
