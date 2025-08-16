#include <access/platforms/sensors/Sensor.hpp>

#include <access/platforms/sensors/SensorPlatform.hpp>

namespace waveguide {
namespace accesslib {

bool Sensor::contains(const astro::RadiusVector<astro::ECI>& sensor2target, const astro::Date& date) const
{
    const astro::RIC frame(_parent);
    const astro::RadiusVector<astro::ECI> boresightEci = frame.convert_from_this_frame(_parameters.get_boresight(), date);
    return _parameters.get_fov()->contains(boresightEci, sensor2target);
}

} // namespace accesslib
} // namespace waveguide