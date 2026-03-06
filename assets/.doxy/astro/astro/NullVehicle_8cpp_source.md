

# File NullVehicle.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**platforms**](dir_2552b27872b33d254ad75ac21654b66a.md) **>** [**vehicles**](dir_6209fec1d31cfd277683fcd634983a45.md) **>** [**NullVehicle.cpp**](NullVehicle_8cpp.md)

[Go to the documentation of this file](NullVehicle_8cpp.md)


```C++
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

#include <astro/platforms/vehicles/NullVehicle.hpp>

#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/FrameReference.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

NullVehicle::NullVehicle(const Mass& mass) :
    _mass(mass)
{
}

NullVehicle* NullVehicle::clone() const { return new NullVehicle(*this); }

Mass NullVehicle::get_mass() const { return _mass; }

std::string NullVehicle::get_name() const { return "NullVehicle"; }

RadiusVector<frames::earth::icrf> NullVehicle::get_inertial_position(const Date& date) const
{
    return { 0.0 * km, 0.0 * km, 0.0 * km };
}

VelocityVector<frames::earth::icrf> NullVehicle::get_inertial_velocity(const Date& date) const
{
    return { 0.0 * km / s, 0.0 * km / s, 0.0 * km / s };
}

AccelerationVector<frames::earth::icrf> NullVehicle::get_inertial_acceleration(const Date& date) const
{
    return { 0.0 * km / (s * s), 0.0 * km / (s * s), 0.0 * km / (s * s) };
}

} // namespace astro
} // namespace astrea
```


