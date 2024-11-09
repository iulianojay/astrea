#pragma once

#ifndef SWIG
    #include <cstdint>
    #include <unordered_map>
    #include <string>
#else

%rename(ElementsSet) ElementSet;

#endif

enum class ElementSet : uint32_t {
    COE,
    CARTESIAN,
    MEE
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
    {ElementSet::COE,       "COE"},
    {ElementSet::CARTESIAN, "CARTESIAN"},
    {ElementSet::MEE,       "MEE"}
};

const std::unordered_map<std::string, ElementSet> StringToElementSet = {
    {"COE",       ElementSet::COE},
    {"CARTESIAN", ElementSet::CARTESIAN},
    {"MEE",       ElementSet::MEE}
};
