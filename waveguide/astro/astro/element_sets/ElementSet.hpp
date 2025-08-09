/**
 * @file ElementSet.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the ElementSet enum class and its associated mappings.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

#include <astro/types/typedefs.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief Enum class representing different sets of orbital elements.
 *
 * This enum class defines the different sets of orbital elements used in astrodynamics.
 * It includes:
 * - CARTESIAN: Represents Cartesian coordinates (position and velocity).
 * - KEPLERIAN: Represents Keplerian elements (semi-major axis, eccentricity, inclination, etc.).
 * - EQUINOCTIAL: Represents equinoctial elements (a combination of position and velocity in a different form).
 */
enum class ElementSet : EnumType { CARTESIAN = 0, KEPLERIAN = 1, EQUINOCTIAL = 2 };

//!< @brief Map for ElementSet enum class to string.
const std::unordered_map<ElementSet, std::string> ElementSetToString = { { ElementSet::KEPLERIAN, "KEPLERIAN" },
                                                                         { ElementSet::CARTESIAN, "CARTESIAN" },
                                                                         { ElementSet::EQUINOCTIAL, "EQUINOCTIAL" } };

//!< @brief Map for string to ElementSet enum class.
const std::unordered_map<std::string, ElementSet> StringToElementSet = { { "KEPLERIAN", ElementSet::KEPLERIAN },
                                                                         { "CARTESIAN", ElementSet::CARTESIAN },
                                                                         { "EQUINOCTIAL", ElementSet::EQUINOCTIAL } };

} // namespace astro
} // namespace waveguide


/* @brief Specialization of std::hash for ElementSet enum class.
 *
 * This specialization allows ElementSet to be used as a key in unordered maps and sets.
 */
template <>
struct std::hash<std::pair<waveguide::astro::ElementSet, waveguide::astro::ElementSet>> {
    /**
     * @brief Hash function for a pair of ElementSet enum values.
     *
     * This function combines the hash values of two ElementSet enum values
     * to produce a single hash value suitable for use in unordered containers.
     *
     * @param p The pair of ElementSet enum values to hash.
     * @return A combined hash value for the pair.
     */
    std::size_t operator()(const std::pair<waveguide::astro::ElementSet, waveguide::astro::ElementSet>& p) const
    {
        auto h1 = std::hash<waveguide::astro::ElementSet>{}(p.first);
        auto h2 = std::hash<waveguide::astro::ElementSet>{}(p.second);
        return h1 ^ h2;
    }
};