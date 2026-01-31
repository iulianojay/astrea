/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>

#include <units/units.hpp>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::non_si::day;
using mp_units::si::unit_symbols::s;

int main()
{
    // The AstrodynamicsSystem is Astrea's attempt to capture definitions and utilities around celestial bodies in a
    // dynamic system. The intention is that users can define a system with either a given body or a barycenter as the
    // center, and then add arbitrarily many or unique celestial bodies. Currently, the system is limited to only using
    // predefined bodies from the CelestialBody class, and it can only use a single body as the system center.

    // Create a system with Earth as the center (and only) body
    AstrodynamicsSystem earthSystem(CelestialBodyId::EARTH);
    const auto& earth = earthSystem.get_central_body();
    std::cout << "Center Body: " << earth->get_name() << std::endl;

    // Systems can also have secondary bodies
    AstrodynamicsSystem earthMoonSystem(CelestialBodyId::EARTH, { CelestialBodyId::MOON });
    std::cout << "Bodies in Earth-Moon System: ";
    for (const auto& [id, body] : earthMoonSystem.get_all_bodies()) {
        std::cout << body->get_name() << " ";
    }
    std::cout << std::endl;

    // Bodies can be accessed directly from the system
    const auto& moon = earthMoonSystem.get_body(CelestialBodyId::MOON);
    std::cout << "Secondary Body: " << moon->get_name() << std::endl;

    return 0;
}