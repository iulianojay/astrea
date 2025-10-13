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

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

int main()
{
    // Setup system
    AstrodynamicsSystem sys;
    Date epoch = Date::now();

    // Build constellation
    State state0(Keplerian::GEO(), epoch, sys);
    Vehicle geo{ Spacecraft(state0) };

    // Force model
    ForceModel forces;
    forces.add<OblatenessForce>(sys, 100, 100);

    // Build EoMs
    CowellsMethod eom(sys, forces);

    // Setup integrator
    Integrator integrator;
    integrator.set_abs_tol(1.0e-10);
    integrator.set_rel_tol(1.0e-10);

    // Propagate
    Interval propInterval{ seconds(0), weeks(1) };
    integrator.propagate(epoch, propInterval, eom, geo);

    return 0;
}