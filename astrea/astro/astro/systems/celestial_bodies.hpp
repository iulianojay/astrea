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

#include <astro/systems/celestial_bodies/Earth/Earth.hpp>
#include <astro/systems/celestial_bodies/Earth/Moon.hpp>
#include <astro/systems/celestial_bodies/Jupiter/Callisto.hpp>
#include <astro/systems/celestial_bodies/Jupiter/Europa.hpp>
#include <astro/systems/celestial_bodies/Jupiter/Ganymede.hpp>
#include <astro/systems/celestial_bodies/Jupiter/Io.hpp>
#include <astro/systems/celestial_bodies/Jupiter/Jupiter.hpp>
#include <astro/systems/celestial_bodies/Mars/Deimos.hpp>
#include <astro/systems/celestial_bodies/Mars/Mars.hpp>
#include <astro/systems/celestial_bodies/Mars/Phobos.hpp>
#include <astro/systems/celestial_bodies/Mercury/Mercury.hpp>
#include <astro/systems/celestial_bodies/Neptune/Neptune.hpp>
#include <astro/systems/celestial_bodies/Neptune/Triton.hpp>
#include <astro/systems/celestial_bodies/Saturn/Iapetus.hpp>
#include <astro/systems/celestial_bodies/Saturn/Rhea.hpp>
#include <astro/systems/celestial_bodies/Saturn/Saturn.hpp>
#include <astro/systems/celestial_bodies/Saturn/Titan.hpp>
#include <astro/systems/celestial_bodies/Sun/Sun.hpp>
#include <astro/systems/celestial_bodies/Uranus/Oberon.hpp>
#include <astro/systems/celestial_bodies/Uranus/Titania.hpp>
#include <astro/systems/celestial_bodies/Uranus/Uranus.hpp>
#include <astro/systems/celestial_bodies/Venus/Venus.hpp>

// Keplerian-approximation fallback for get_position_at / get_velocity_at.
// Included AFTER all planet specialisations so the fallback primary-template
// definition does not shadow any explicit specialisation.
#include <astro/systems/default_property_getters.hpp>