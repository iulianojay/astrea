#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

#include <astro/types/typedefs.hpp>

namespace waveguide {
namespace astro {

enum class ElementSet : EnumType { CARTESIAN = 0, KEPLERIAN = 1, EQUINOCTIAL = 2 };


const std::unordered_map<ElementSet, std::string> ElementSetToString = { { ElementSet::KEPLERIAN, "KEPLERIAN" },
                                                                         { ElementSet::CARTESIAN, "CARTESIAN" },
                                                                         { ElementSet::EQUINOCTIAL, "EQUINOCTIAL" } };

const std::unordered_map<std::string, ElementSet> StringToElementSet = { { "KEPLERIAN", ElementSet::KEPLERIAN },
                                                                         { "CARTESIAN", ElementSet::CARTESIAN },
                                                                         { "EQUINOCTIAL", ElementSet::EQUINOCTIAL } };

} // namespace astro
} // namespace waveguide

template <>
struct std::hash<std::pair<waveguide::astro::ElementSet, waveguide::astro::ElementSet>> {
    std::size_t operator()(const std::pair<waveguide::astro::ElementSet, waveguide::astro::ElementSet>& p) const
    {
        auto h1 = std::hash<waveguide::astro::ElementSet>{}(p.first);
        auto h2 = std::hash<waveguide::astro::ElementSet>{}(p.second);
        return h1 ^ h2;
    }
};