#include <trace/platforms/ground/GroundStation.hpp>

#include <mp-units/systems/angular.h>

#include <astro/state/CartesianVector.hpp>
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
    return _lla.get_position(date, _parent);
}

astro::VelocityVector<astro::frames::earth::icrf> GroundStation::get_inertial_velocity(const astro::Date& date) const
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

} // namespace trace
} // namespace astrea