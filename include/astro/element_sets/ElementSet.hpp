#pragma once

#ifndef SWIG
    #include <cstdint>
    #include <unordered_map>
    #include <string>
#else

%rename(ElementsSet) ElementSet;

#endif

#include "astro/types/typedefs.hpp"

enum class ElementSet : enum_type {
    KEPLERIAN = 0,
    CARTESIAN = 1,
    EQUINOCTIAL = 2
};

template <>
struct std::hash<std::pair<ElementSet, ElementSet>> {
    std::size_t operator () (const std::pair<ElementSet, ElementSet> &p) const {
        auto h1 = std::hash<ElementSet>{}(p.first);
        auto h2 = std::hash<ElementSet>{}(p.second);
        return h1 ^ h2;
    }
};


const std::unordered_map<ElementSet, std::string> ElementSetToString = {
    {ElementSet::KEPLERIAN,   "KEPLERIAN"},
    {ElementSet::CARTESIAN,   "CARTESIAN"},
    {ElementSet::EQUINOCTIAL, "EQUINOCTIAL"}
};

const std::unordered_map<std::string, ElementSet> StringToElementSet = {
    {"KEPLERIAN",   ElementSet::KEPLERIAN},
    {"CARTESIAN",   ElementSet::CARTESIAN},
    {"EQUINOCTIAL", ElementSet::EQUINOCTIAL}
};
