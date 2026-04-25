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

using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::m;

int main()
{
    // Propagation is centered around a State and a Vehicle. The general idea being that the State represents the 6
    // location and the 6 orientation elements of the spacecraft, and the AstrodynamicsSystem in which they're defined,
    // while the Vehicle represents the physical object existing at that State.
    //
    // The Vehicle class is designed as a type-erased container to keep this relationship as generic and flexible as
    // possible without making it diificult for developers to understand it's behavior. Type-erasure also keeps
    // interfaces clean, and can hand out work to default functions and implementations. This lessens the burden on
    // users and allows arbitrarily complex systems of vehicles to be built without needing to worry about the
    // underlying implementation of the Vehicle class itself. The Vehicle class only requires users to develop a class
    // with a single function, get_mass(), and all other implementation details are optional. If users want to develop
    // their own custom Vehicles, they can also have functions for defining numerous spacecraft properties such as
    // inertia, areas, and dynamic coefficients. Users can also define functions for implementing control authority for
    // the vehicle.
    struct MyVehicle {
        Mass get_mass() const { return 1000.0 * kg; }
    };
    MyVehicle myVehicle;
    Vehicle vehicle(myVehicle);

    struct MyComplicatedVehicle {
        Mass get_mass() const { return 1000.0 * kg; }
        InertiaTensor<frames::dynamic::body> get_inertia_tensor() const
        {
            return InertiaTensor<frames::dynamic::body>{ 100.0 * kg * pow<2>(m), 20.0 * kg * pow<2>(m), 120.0 * kg * pow<2>(m) };
        }
        SurfaceArea get_ram_area() const { return 10.0 * pow<2>(m); }
        Unitless get_drag_coefficient() const { return 2.0; }
    };
    MyComplicatedVehicle myComplicatedVehicle;
    Vehicle complicatedVehicle(myComplicatedVehicle);

    // Astrea comes with two built-in Vehicle types: The NullVehicle, a do-nothing class used to satisfy Vehicle constructors, and
    // the Spacecraft class. The latter is a reasonably complete implementation of many of the features that a user may want.
    Spacecraft sat;
    Vehicle spacecraft(sat);

    // All of these can be safely propagated
    AstrodynamicsSystem sys;
    Date epoch = Date::now();
    State state0(Keplerian::LEO(), epoch, sys);
    Time propTime = hours(1.0);

    Integrator integrator; // default to two-body

    integrator.propagate(state0, propTime, vehicle);
    integrator.propagate(state0, propTime, complicatedVehicle);
    integrator.propagate(state0, propTime, spacecraft);

    return 0;
}