#pragma once

#include <vector>

#include <astro/types/typedefs.hpp>

#include <access/platforms/sensors/SensorPlatform.hpp>


namespace accesslib {

class GroundPoint {
  public:
    GroundPoint(
        const astro::Angle& latitutde   = 0.0 * mp_units::angular::unit_symbols::deg,
        const astro::Angle& longitude   = 0.0 * mp_units::angular::unit_symbols::deg,
        const astro::Distance& altitude = 0.0 * mp_units::si::unit_symbols::km
    ) :
        _latitude(latitutde),
        _longitude(longitude),
        _altitude(altitude)
    {
    }
    virtual ~GroundPoint() = default;

    astro::Angle get_latitude() const { return _latitude; }
    astro::Angle get_longitude() const { return _longitude; }
    astro::Distance get_altitude() const { return _altitude; }

  protected:
    astro::Angle _latitude;
    astro::Angle _longitude;
    astro::Distance _altitude;
};

} // namespace accesslib