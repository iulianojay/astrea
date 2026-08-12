/**
 * @file system_concepts.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Definitions for system concepts and other compile-time utilities.
 * @date 2025-10-02
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <concepts>

namespace astrea {
namespace astro {

namespace detail {

// Forward declarations of base types
struct CelestialBodyBase;
struct BarycenterBase;

} // namespace detail

/**
 * @brief Concept to determine if a type is a celestial body.
 */
template <typename T>
concept IsCelestialBody = std::derived_from<T, detail::CelestialBodyBase> && !std::derived_from<T, detail::BarycenterBase>;

/**
 * @brief Concept to determine if a type is a barycenter.
 */
template <typename T>
concept IsBarycenter = std::derived_from<T, detail::BarycenterBase> && !std::derived_from<T, detail::CelestialBodyBase>;

/**
 * @brief Concept to determine if a type is a celestial reference, which can be either a celestial body or a barycenter.
 */
template <typename T>
concept IsCelestialReference = IsCelestialBody<T> || IsBarycenter<T>;

} // namespace astro
} // namespace astrea