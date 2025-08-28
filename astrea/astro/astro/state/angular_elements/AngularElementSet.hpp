/**
 * @file AngularElementSet.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the AngularElementSet enum class and its associated mappings.
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
 * @brief Enum class representing different sets of angular elements.
 *
 * This enum class defines the different sets of angular elements used in astrodynamics.
 * It includes:
 * - GEODETIC: Represents geodetic coordinates (latitude, longitude, altitude).
 * - SPHERICAL: Represents spherical coordinates (radius, azimuth angle, elevation angle).
 */
enum class AngularElementSet : EnumType { GEODETIC = 0, SPHERICAL = 1 };

//!< @brief Map for AngularElementSet enum class to string.
const std::unordered_map<AngularElementSet, std::string> AngularElementSetToString = { { AngularElementSet::GEODETIC, "GEODETIC" },
                                                                                       { AngularElementSet::SPHERICAL, "SPHERICAL" } };

//!< @brief Map for string to AngularElementSet enum class.
const std::unordered_map<std::string, AngularElementSet> StringToAngularElementSet = { { "GEODETIC", AngularElementSet::GEODETIC },
                                                                                       { "SPHERICAL", AngularElementSet::SPHERICAL } };

} // namespace astro
} // namespace astrea


/* @brief Specialization of std::hash for AngularElementSet enum class.
 *
 * This specialization allows AngularElementSet to be used as a key in unordered maps and sets.
 */
template <>
struct std::hash<std::pair<astrea::astro::AngularElementSet, astrea::astro::AngularElementSet>> {
    /**
     * @brief Hash function for a pair of AngularElementSet enum values.
     *
     * This function combines the hash values of two AngularElementSet enum values
     * to produce a single hash value suitable for use in unordered containers.
     *
     * @param p The pair of AngularElementSet enum values to hash.
     * @return A combined hash value for the pair.
     */
    std::size_t operator()(const std::pair<astrea::astro::AngularElementSet, astrea::astro::AngularElementSet>& p) const
    {
        auto h1 = std::hash<astrea::astro::AngularElementSet>{}(p.first);
        auto h2 = std::hash<astrea::astro::AngularElementSet>{}(p.second);
        return h1 ^ h2;
    }
};