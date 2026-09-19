/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/platforms/Vehicle.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/si/math.h>

#include <astro/platforms/vehicles/NullVehicle.hpp>


using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::si::unit_symbols;

namespace astrea {
namespace astro {

// Default constructor
Vehicle::Vehicle() :
    Vehicle(NullVehicle{})
{
}

// Copy constructor
Vehicle::Vehicle(const Vehicle& other) :
    _ptr(other._ptr->clone())
{
}

// Move constructor
Vehicle::Vehicle(Vehicle&& other) noexcept :
    _ptr(std::move(other._ptr))
{
}

void Vehicle::generic_ctor_impl() {}

// Move assignment operator
Vehicle& Vehicle::operator=(Vehicle&& other) noexcept
{
    if (this != &other) { _ptr = std::move(other._ptr); }
    return *this;
}

// Copy assignment operator
Vehicle& Vehicle::operator=(const Vehicle& other) { return *this = Vehicle(other); }

// Pointer to user-defined vehicle
const void* Vehicle::get_ptr() const { return ptr()->get_ptr(); }
void* Vehicle::get_ptr() { return ptr()->get_ptr(); }

} // namespace astro
} // namespace astrea