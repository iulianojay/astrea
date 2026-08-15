

# File Vehicle.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**platforms**](dir_2552b27872b33d254ad75ac21654b66a.md) **>** [**Vehicle.cpp**](Vehicle_8cpp.md)

[Go to the documentation of this file](Vehicle_8cpp.md)


```C++
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
    _ptr(other._ptr->clone()),
    _mass(other._mass),
    _inertiaTensor(other._inertiaTensor),
    _ramArea(other._ramArea),
    _liftArea(other._liftArea),
    _solarArea(other._solarArea),
    _coefficientOfDrag(other._coefficientOfDrag),
    _coefficientOfLift(other._coefficientOfLift),
    _coefficientOfReflectivity(other._coefficientOfReflectivity)
{
}

// Move constructor
Vehicle::Vehicle(Vehicle&& other) noexcept :
    _ptr(std::move(other._ptr)),
    _mass(std::move(other._mass)),
    _inertiaTensor(std::move(other._inertiaTensor)),
    _ramArea(std::move(other._ramArea)),
    _liftArea(std::move(other._liftArea)),
    _solarArea(std::move(other._solarArea)),
    _coefficientOfDrag(std::move(other._coefficientOfDrag)),
    _coefficientOfLift(std::move(other._coefficientOfLift)),
    _coefficientOfReflectivity(std::move(other._coefficientOfReflectivity))
{
}

void Vehicle::generic_ctor_impl()
{
    _mass                      = ptr()->get_mass();
    _inertiaTensor             = ptr()->get_inertia_tensor();
    _ramArea                   = ptr()->get_ram_area();
    _liftArea                  = ptr()->get_lift_area();
    _solarArea                 = ptr()->get_solar_area();
    _coefficientOfDrag         = ptr()->get_coefficient_of_drag();
    _coefficientOfLift         = ptr()->get_coefficient_of_lift();
    _coefficientOfReflectivity = ptr()->get_coefficient_of_reflectivity();
}

// Move assignment operator
Vehicle& Vehicle::operator=(Vehicle&& other) noexcept
{
    if (this != &other) {
        _ptr                       = std::move(other._ptr);
        _mass                      = std::move(other._mass);
        _inertiaTensor             = std::move(other._inertiaTensor);
        _ramArea                   = std::move(other._ramArea);
        _liftArea                  = std::move(other._liftArea);
        _solarArea                 = std::move(other._solarArea);
        _coefficientOfDrag         = std::move(other._coefficientOfDrag);
        _coefficientOfLift         = std::move(other._coefficientOfLift);
        _coefficientOfReflectivity = std::move(other._coefficientOfReflectivity);
    }
    return *this;
}

// Copy assignment operator
Vehicle& Vehicle::operator=(const Vehicle& other) { return *this = Vehicle(other); }

// Pointer to user-defined vehicle
const void* Vehicle::get_ptr() const { return ptr()->get_ptr(); }
void* Vehicle::get_ptr() { return ptr()->get_ptr(); }

} // namespace astro
} // namespace astrea
```


