#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

#include <astro/types/typedefs.hpp>

namespace astro {

enum class ElementSet : EnumType { KEPLERIAN, CARTESIAN, EQUINOCTIAL };


const std::unordered_map<ElementSet, std::string> ElementSetToString = { { ElementSet::KEPLERIAN, "KEPLERIAN" },
                                                                         { ElementSet::CARTESIAN, "CARTESIAN" },
                                                                         { ElementSet::EQUINOCTIAL, "EQUINOCTIAL" } };

const std::unordered_map<std::string, ElementSet> StringToElementSet = { { "KEPLERIAN", ElementSet::KEPLERIAN },
                                                                         { "CARTESIAN", ElementSet::CARTESIAN },
                                                                         { "EQUINOCTIAL", ElementSet::EQUINOCTIAL } };

} // namespace astro

template <>
struct std::hash<std::pair<astro::ElementSet, astro::ElementSet>> {
    std::size_t operator()(const std::pair<astro::ElementSet, astro::ElementSet>& p) const
    {
        auto h1 = std::hash<astro::ElementSet>{}(p.first);
        auto h2 = std::hash<astro::ElementSet>{}(p.second);
        return h1 ^ h2;
    }
};