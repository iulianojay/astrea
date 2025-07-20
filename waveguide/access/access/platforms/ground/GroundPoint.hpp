#pragma once

#include <vector>

#include <access/platforms/sensors/SensorPlatform.hpp>
#include <access/types/typedefs.hpp>


namespace waveguide {
namespace accesslib {

class GroundPoint {
  public:
    GroundPoint(
        const Angle& latitutde   = 0.0 * mp_units::angular::unit_symbols::deg,
        const Angle& longitude   = 0.0 * mp_units::angular::unit_symbols::deg,
        const Distance& altitude = 0.0 * mp_units::si::unit_symbols::km
    ) :
        _latitude(latitutde),
        _longitude(longitude),
        _altitude(altitude)
    {
    }
    virtual ~GroundPoint() = default;

    Angle get_latitude() const { return _latitude; }
    Angle get_longitude() const { return _longitude; }
    Distance get_altitude() const { return _altitude; }

  protected:
    Angle _latitude;
    Angle _longitude;
    Distance _altitude;
};

} // namespace accesslib
} // namespace waveguide