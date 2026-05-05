/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2026 Jay Iuliano
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

using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;

int main()
{
    // Astrea comes with a few simple containers for Vehicles. These are meant for quick organization and could be
    // quickly replaced with custom alternatives for more specific use cases.

    // Build a Spacecraft Constellation with Walker parameters
    AstrodynamicsSystem sys;
    Date epoch("2024-01-01T00:00:00Z");
    const Distance sma  = 7000.0 * km;
    const Angle inc     = 45.0 * deg;
    const std::size_t T = 20;  // Total number of spacecraft
    const std::size_t P = 5;   // Number of planes
    const double F      = 1.0; // Phasing parameters
    Constellation<Spacecraft> constellation(sys, epoch, sma, inc, T, P, F);

    // Iterate over the constellation and print the initial state of each spacecraft
    for (const auto& shell : constellation.get_shells()) {
        std::cout << "Shell ID: " << shell.get_id() << std::endl;
        for (const auto& plane : shell.get_planes()) {
            std::cout << "\tPlane ID: " << plane.get_id() << std::endl;
            for (const auto& satellite : plane.get_all_spacecraft()) {
                std::cout << "\t\tSatellite ID: " << satellite.get_id() << std::endl;
                std::cout << "\t\tInitial State: " << satellite.get_initial_state() << std::endl;
            }
        }
    }
    return 0;
}