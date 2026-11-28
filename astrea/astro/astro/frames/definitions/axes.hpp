/**
 * @file axes.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Definition for axes in astrea.
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

#include <astro/frames/framework/Axis.hpp>

namespace astrea {
namespace astro {

namespace axes {

inline constexpr struct icrf final : Axis<"ICRF"> {
    // x - Measured, meant to coincide with EME2000 X-axis at J2000
    // z - Measured, meant to coincide with EME2000 Z-axis at J2000
} icrf;

inline constexpr struct j2000 final : Axis<"EME2000", icrf> {
    // x - mean equator and equinox of date at J2000
    // z - mean pole of date at J2000
} j2000;

// TODO: This is a bit out of line with the reference axis definitions attached to the celestial bodies
// Both might need a refactor. For now, it's fine.
inline constexpr struct cep : Axis<"Earth Celestial Pole", icrf> {
    // x - mean equator and equinox of date at J2000
    // z - mean pole of date at J2000
} cep;

} // namespace axes

} // namespace astro
} // namespace astrea