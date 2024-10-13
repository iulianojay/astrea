#pragma once

#ifndef SWIG
    #include <vector>
#endif

#include "solar_system.hpp"
#include "GravitationalBody.hpp"
#include "Barycenter.hpp"

#include "SolarObjectFactory.fwd.hpp"

class SolarObjectBuilder {

    friend class SolarObjectFactory;
    friend class BarycenterFactory;

public:

    SolarObjectBuilder() {}
    ~SolarObjectBuilder() {}

    GravitationalBody build(SolarObject name);
    //Barycenter build(std::vector<SolarObject> names); // TODO: implement

private:

    void assign_properties(GravitationalBody& body, SolarObject name);

    //-------------------------------------------------- Maps -------------------------------------------------//
    const std::unordered_map<std::string, SolarObject> _nameMap = {
        {"Sun",      SUN},
        {"Mercury",  MERCURY},
        {"Venus",    VENUS},
        {"Earth",    EARTH},
        {"Moon",     MOON},
        {"Mars",     MARS},
        {"Phobos",   PHOBOS},
        {"Deimos",   DEIMOS},
        {"Jupiter",  JUPITER},
        {"Ganymede", GANYMEDE},
        {"Callisto", CALLISTO},
        {"Io",       IO},
        {"Europa",   EUROPA},
        {"Saturn",   SATURN},
        {"Titan",    TITAN},
        {"Rhea",     RHEA},
        {"Iapetus",  IAPETUS},
        {"Uranus",   URANUS},
        {"Titania",  TITANIA},
        {"Oberon",   OBERON},
        {"Neptune",  NEPTUNE},
        {"Triton",   TRITON}
    };

    const std::unordered_map<SolarObject, std::string> _mapName = {
        {SUN,      "Sun"},
        {MERCURY,  "Mercury"},
        {VENUS,    "Venus"},
        {EARTH,    "Earth"},
        {MOON,     "Moon"},
        {MARS,     "Mars"},
        {PHOBOS,   "Phobos"},
        {DEIMOS,   "Deimos"},
        {JUPITER,  "Jupiter"},
        {GANYMEDE, "Ganymede"},
        {CALLISTO, "Callisto"},
        {IO,       "Io"},
        {EUROPA,   "Europa"},
        {SATURN,   "Saturn"},
        {TITAN,    "Titan"},
        {RHEA,     "Rhea"},
        {IAPETUS,  "Iapetus"},
        {URANUS,   "Uranus"},
        {TITANIA,  "Titania"},
        {OBERON,   "Oberon"},
        {NEPTUNE,  "Neptune"},
        {TRITON,   "Triton"}
    };

    const std::unordered_map<SolarObjectType, std::string> _mapType = {
        {STAR,      "Star"},
        {PLANET,    "Planet"},
        {SATELLITE, "Satellite"},
    };

    const std::unordered_map<SolarObject, SolarObjectType> _typeMap = {
        {SUN,      STAR},
        {MERCURY,  PLANET},
        {VENUS,    PLANET},
        {EARTH,    PLANET},
        {MOON,     SATELLITE},
        {MARS,     PLANET},
        {PHOBOS,   SATELLITE},
        {DEIMOS,   SATELLITE},
        {JUPITER,  PLANET},
        {GANYMEDE, SATELLITE},
        {CALLISTO, SATELLITE},
        {IO,       SATELLITE},
        {EUROPA,   SATELLITE},
        {SATURN,   PLANET},
        {TITAN,    SATELLITE},
        {RHEA,     SATELLITE},
        {IAPETUS,  SATELLITE},
        {URANUS,   PLANET},
        {TITANIA,  SATELLITE},
        {OBERON,   SATELLITE},
        {NEPTUNE,  PLANET},
        {TRITON,   SATELLITE}
    };

    const std::unordered_map<SolarObject, SolarObject> _parentMap = {
        {SUN,      GC},
        {MERCURY,  SUN},
        {VENUS,    SUN},
        {EARTH,    SUN},
        {MOON,     EARTH},
        {MARS,     SUN},
        {PHOBOS,   MARS},
        {DEIMOS,   MARS},
        {JUPITER,  SUN},
        {GANYMEDE, JUPITER},
        {CALLISTO, JUPITER},
        {IO,       JUPITER},
        {EUROPA,   JUPITER},
        {SATURN,   SUN},
        {TITAN,    SATURN},
        {RHEA,     SATURN},
        {IAPETUS,  SATURN},
        {URANUS,   SUN},
        {TITANIA,  URANUS},
        {OBERON,   URANUS},
        {NEPTUNE,  SUN},
        {TRITON,   NEPTUNE}
    };

    const std::unordered_map<SolarObject, std::pair<int, int>> _idMap = {
        {SUN,      std::make_pair(0, 0)},
        {MERCURY,  std::make_pair(1, 0)},
        {VENUS,    std::make_pair(2, 0)},
        {EARTH,    std::make_pair(3, 0)},
        {MOON,     std::make_pair(3, 1)},
        {MARS,     std::make_pair(4, 0)},
        {PHOBOS,   std::make_pair(4, 1)},
        {DEIMOS,   std::make_pair(4, 2)},
        {JUPITER,  std::make_pair(5, 0)},
        {GANYMEDE, std::make_pair(5, 1)},
        {CALLISTO, std::make_pair(5, 2)},
        {IO,       std::make_pair(5, 3)},
        {EUROPA,   std::make_pair(5, 4)},
        {SATURN,   std::make_pair(6, 0)},
        {TITAN,    std::make_pair(6, 1)},
        {RHEA,     std::make_pair(6, 2)},
        {IAPETUS,  std::make_pair(6, 3)},
        {URANUS,   std::make_pair(7, 0)},
        {TITANIA,  std::make_pair(7, 1)},
        {OBERON,   std::make_pair(7, 2)},
        {NEPTUNE,  std::make_pair(8, 0)},
        {TRITON,   std::make_pair(8, 1)}
    };
};
