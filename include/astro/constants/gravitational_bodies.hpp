#pragma once

#include <unordered_map>

// Enums for bodies definitions
enum bodyName {
    GC,			// Galactic Center
    Sun,
    Mercury,
    Venus,
    Earth,
    Moon,
    Mars,
    Phobos,
    Deimos,
    Jupiter,
    Ganymede,
    Callisto,
    Io,
    Europa,
    Saturn,
    Titan,
    Rhea,
    Iapetus,
    Uranus,
    Titania,
    Oberon,
    Neptune,
    Triton
};

enum bodyType {
    Star,
    Planet,
    Satellite
};

//-------------------------------------------------- Maps -------------------------------------------------//
static const std::unordered_map<std::string, bodyName> _nameMap = {
    {"Sun",      Sun},
    {"Mercury",  Mercury},
    {"Venus",    Venus},
    {"Earth",    Earth},
    {"Moon",     Moon},
    {"Mars",     Mars},
    {"Phobos",   Phobos},
    {"Deimos",   Deimos},
    {"Jupiter",  Jupiter},
    {"Ganymede", Ganymede},
    {"Callisto", Callisto},
    {"Io",       Io},
    {"Europa",   Europa},
    {"Saturn",   Saturn},
    {"Titan",    Titan},
    {"Rhea",     Rhea},
    {"Iapetus",  Iapetus},
    {"Uranus",   Uranus},
    {"Titania",  Titania},
    {"Oberon",   Oberon},
    {"Neptune",  Neptune},
    {"Triton",   Triton}
};

static const std::unordered_map<bodyName, std::string> _mapName = {
    {Sun,      "Sun"},
    {Mercury,  "Mercury"},
    {Venus,    "Venus"},
    {Earth,    "Earth"},
    {Moon,     "Moon"},
    {Mars,     "Mars"},
    {Phobos,   "Phobos"},
    {Deimos,   "Deimos"},
    {Jupiter,  "Jupiter"},
    {Ganymede, "Ganymede"},
    {Callisto, "Callisto"},
    {Io,       "Io"},
    {Europa,   "Europa"},
    {Saturn,   "Saturn"},
    {Titan,    "Titan"},
    {Rhea,     "Rhea"},
    {Iapetus,  "Iapetus"},
    {Uranus,   "Uranus"},
    {Titania,  "Titania"},
    {Oberon,   "Oberon"},
    {Neptune,  "Neptune"},
    {Triton,   "Triton"}
};

static const std::unordered_map<bodyType, std::string> _mapType = {
    {Star,      "Star"},
    {Planet,    "Planet"},
    {Satellite, "Satellite"},
};

static const std::unordered_map<bodyName, bodyType> _typeMap = {
    {Sun,      Star},
    {Mercury,  Planet},
    {Venus,    Planet},
    {Earth,    Planet},
    {Moon,     Satellite},
    {Mars,     Planet},
    {Phobos,   Satellite},
    {Deimos,   Satellite},
    {Jupiter,  Planet},
    {Ganymede, Satellite},
    {Callisto, Satellite},
    {Io,       Satellite},
    {Europa,   Satellite},
    {Saturn,   Planet},
    {Titan,    Satellite},
    {Rhea,     Satellite},
    {Iapetus,  Satellite},
    {Uranus,   Planet},
    {Titania,  Satellite},
    {Oberon,   Satellite},
    {Neptune,  Planet},
    {Triton,   Satellite}
};

static const std::unordered_map<bodyName, bodyName> _parentMap = {
    {Sun,      GC},
    {Mercury,  Sun},
    {Venus,    Sun},
    {Earth,    Sun},
    {Moon,     Earth},
    {Mars,     Sun},
    {Phobos,   Mars},
    {Deimos,   Mars},
    {Jupiter,  Sun},
    {Ganymede, Jupiter},
    {Callisto, Jupiter},
    {Io,       Jupiter},
    {Europa,   Jupiter},
    {Saturn,   Sun},
    {Titan,    Saturn},
    {Rhea,     Saturn},
    {Iapetus,  Saturn},
    {Uranus,   Sun},
    {Titania,  Uranus},
    {Oberon,   Uranus},
    {Neptune,  Sun},
    {Triton,   Neptune}
};

static const std::unordered_map<bodyName, std::pair<int, int>> _idMap = {
    {Sun,      std::make_pair(0, 0)},
    {Mercury,  std::make_pair(1, 0)},
    {Venus,    std::make_pair(2, 0)},
    {Earth,    std::make_pair(3, 0)},
    {Moon,     std::make_pair(3, 1)},
    {Mars,     std::make_pair(4, 0)},
    {Phobos,   std::make_pair(4, 1)},
    {Deimos,   std::make_pair(4, 2)},
    {Jupiter,  std::make_pair(5, 0)},
    {Ganymede, std::make_pair(5, 1)},
    {Callisto, std::make_pair(5, 2)},
    {Io,       std::make_pair(5, 3)},
    {Europa,   std::make_pair(5, 4)},
    {Saturn,   std::make_pair(6, 0)},
    {Titan,    std::make_pair(6, 1)},
    {Rhea,     std::make_pair(6, 2)},
    {Iapetus,  std::make_pair(6, 3)},
    {Uranus,   std::make_pair(7, 0)},
    {Titania,  std::make_pair(7, 1)},
    {Oberon,   std::make_pair(7, 2)},
    {Neptune,  std::make_pair(8, 0)},
    {Triton,   std::make_pair(8, 1)}
};