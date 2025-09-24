#include <trace/platforms/sensors/Sensor.hpp>

#include <astro/state/CartesianVector.hpp>
#include <astro/state/frames/FrameReference.hpp>
#include <astro/state/frames/frames.hpp>

namespace astrea {
namespace trace {

bool Sensor::contains(const astro::RadiusVector<astro::frames::earth::icrf>& sensor2target, const astro::Date& date) const
{
    if (!_parameters.get_fov()) { return false; }
    const astro::RIC frame(_parent);
    const astro::RadiusVector<astro::frames::earth::icrf> boresightEci =
        frame.convert_from_this_frame(_parameters.get_boresight(), date);
    return _parameters.get_fov()->contains(boresightEci, sensor2target);
}

} // namespace trace
} // namespace astrea