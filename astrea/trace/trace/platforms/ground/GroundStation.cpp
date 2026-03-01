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

#include <mp-units/systems/angular.h>

#include <astro/frames/CartesianVector.hpp>
#include <astro/time/Date.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {

using namespace astro;

namespace trace {

using namespace mp_units;
using namespace mp_units::angular;
using mp_units::isq_angle::cotes_angle;
using mp_units::si::unit_symbols::km;

GroundStation::GroundStation(
    const astro::CelestialBody* parent,
    const Angle& latitude,
    const Angle& longitude,
    const Distance& altitude,
    const std::string name,
    const std::vector<SensorParameters>& sensorParams
) :
    GroundPoint(parent, latitude, longitude, altitude),
    SensorPlatform(),
    _name(name)
{
    for (const auto& sensorParam : sensorParams) {
        attach_payload(sensorParam);
    }
}


std::size_t GroundStation::get_id() const { return _id; }

std::string GroundStation::get_name() const { return _name; }

astro::RadiusVector<astro::frames::earth::icrf> GroundStation::get_inertial_position(const astro::Date& date) const
{
    return GroundPoint::get_inertial_position(date);
}

astro::VelocityVector<astro::frames::earth::icrf> GroundStation::get_inertial_velocity(const astro::Date& date) const
{
    return GroundPoint::get_inertial_velocity(date);
}

} // namespace trace
} // namespace astrea