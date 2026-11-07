/**
 * @file celestial_bodies.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file that includes all planetary bodies.
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

#include <astro/systems/celestial_bodies_impl.hpp>

// Keplerian-approximation fallback for get_position_at / get_velocity_at.
// Included AFTER all planet specializations so the fallback primary-template
// definition does not shadow any explicit specialization.
#include <astro/systems/default_celestial_body_orbits.hpp>