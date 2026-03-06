

# File GroundPoint.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**platforms**](dir_4dbda61db413396ce1d3b920f98dbf93.md) **>** [**ground**](dir_f1cb7431ef00eaab1d7c5caeb9788760.md) **>** [**GroundPoint.cpp**](GroundPoint_8cpp.md)

[Go to the documentation of this file](GroundPoint_8cpp.md)


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

#include <trace/platforms/ground/GroundStation.hpp>

#include <ostream>

#include <mp-units/systems/angular.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>

#include <astro/frames/CartesianVector.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/time/Date.hpp>

using namespace mp_units;
using namespace mp_units::angular;
using mp_units::angular::unit_symbols::deg;
using mp_units::isq_angle::cotes_angle;
using mp_units::si::unit_symbols::km;

namespace astrea {

using namespace astro;

namespace trace {

GroundPoint::GroundPoint(const CelestialBody* parent, const Angle& latitutde, const Angle& longitude, const Distance& altitude) :
    AccessObject(),
    _parent(parent),
    _lla(latitutde, longitude, altitude),
    _id(generate_id())
{
}

bool GroundPoint::operator==(const GroundPoint& other) const { return _lla == other._lla; }

const Geodetic& GroundPoint::get_lla() const { return _lla; }

const Angle& GroundPoint::get_latitude() const { return _lla.get_latitude(); }

const Angle& GroundPoint::get_longitude() const { return _lla.get_longitude(); }

const Distance& GroundPoint::get_altitude() const { return _lla.get_altitude(); }

const CelestialBody* GroundPoint::get_parent() const { return _parent; }

std::size_t GroundPoint::get_id() const { return _id; }

astro::CartesianVector<Distance, astro::frames::earth::earth_fixed> GroundPoint::get_position() const
{
    return _lla.get_position(_parent);
}

RadiusVector<frames::earth::icrf> GroundPoint::get_inertial_position(const Date& date) const
{
    return _lla.get_position(date, _parent);
}

VelocityVector<frames::earth::icrf> GroundPoint::get_inertial_velocity(const Date& date) const
{
    const RadiusVector<frames::earth::earth_fixed> rEcef = _lla.get_position(_parent);

    const RadiusVector<frames::earth::earth_fixed> rEcefPlanar = { rEcef.get_x(), rEcef.get_y(), 0.0 * km };
    const Distance rEcefPlanarNorm                             = rEcefPlanar.norm();
    const Velocity vEcefMag                          = rEcefPlanarNorm * _parent->get_rotation_rate() / cotes_angle;
    const RadiusVector<frames::earth::earth_fixed> z = { 0.0 * km, 0.0 * km, 1.0 * km };
    const VelocityVector<frames::earth::earth_fixed> vEcef =
        (z.cross(rEcefPlanar).unit()) * vEcefMag; // z cross (x,y,0) give perpendicular direction vector
    return vEcef.in_frame<frames::earth::icrf>(date);
}

std::string GroundPoint::get_name() const
{
    std::ostringstream oss;
    oss << "[" << _lla.get_latitude().in(deg) << ", " << _lla.get_longitude().in(deg);
    if (_lla.get_altitude() != 0.0 * km) { oss << ", " << _lla.get_altitude(); }
    oss << "]";
    oss << " (" << _parent->get_name() << ")";
    return oss.str();
}

std::size_t GroundPoint::generate_id()
{
    static std::size_t idCounter = -1; // UNDERFLOW DEPENDENT BEHAVIOR LETS GOOOOOOO
    return idCounter--; // TODO: not this (but have to for now cause otherwise viewer ids can conflict with ground IDs)
}

} // namespace trace
} // namespace astrea
```


