/**
 * @file HarrisPriester.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the HarrisPriester class.
 * @date 2026-05-01
 *
 * @copyright Copyright (c) 2026 Jay Iuliano
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

namespace astrea {
namespace astro {
namespace planetary_bodies {

class HarrisPriesterAtmosphere {
  public:
    HarrisPriesterAtmosphere() = delete;

    static Density find_atmospheric_density(const State& state);
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea