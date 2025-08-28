/**
 * @file OrbitalElementSet.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the OrbitalElementSet enum class and its associated mappings.
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

namespace astrea {
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
enum class OrbitalElementSet : EnumType { CARTESIAN = 0, KEPLERIAN = 1, EQUINOCTIAL = 2 };

//!< @brief Map for OrbitalElementSet enum class to string.
const std::unordered_map<OrbitalElementSet, std::string> OrbitalElementSetToString = {
    { OrbitalElementSet::KEPLERIAN, "KEPLERIAN" },
    { OrbitalElementSet::CARTESIAN, "CARTESIAN" },
    { OrbitalElementSet::EQUINOCTIAL, "EQUINOCTIAL" }
};

//!< @brief Map for string to OrbitalElementSet enum class.
const std::unordered_map<std::string, OrbitalElementSet> StringToOrbitalElementSet = {
    { "KEPLERIAN", OrbitalElementSet::KEPLERIAN },
    { "CARTESIAN", OrbitalElementSet::CARTESIAN },
    { "EQUINOCTIAL", OrbitalElementSet::EQUINOCTIAL }
};

} // namespace astro
} // namespace astrea


/* @brief Specialization of std::hash for OrbitalElementSet enum class.
 *
 * This specialization allows OrbitalElementSet to be used as a key in unordered maps and sets.
 */
template <>
struct std::hash<std::pair<astrea::astro::OrbitalElementSet, astrea::astro::OrbitalElementSet>> {
    /**
     * @brief Hash function for a pair of OrbitalElementSet enum values.
     *
     * This function combines the hash values of two OrbitalElementSet enum values
     * to produce a single hash value suitable for use in unordered containers.
     *
     * @param p The pair of OrbitalElementSet enum values to hash.
     * @return A combined hash value for the pair.
     */
    std::size_t operator()(const std::pair<astrea::astro::OrbitalElementSet, astrea::astro::OrbitalElementSet>& p) const
    {
        auto h1 = std::hash<astrea::astro::OrbitalElementSet>{}(p.first);
        auto h2 = std::hash<astrea::astro::OrbitalElementSet>{}(p.second);
        return h1 ^ h2;
    }
};