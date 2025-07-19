#pragma once

#include <vector>

#include <astro/types/typedefs.hpp>

#include <access/platforms/ground/GroundPoint.hpp>
#include <access/platforms/sensors/SensorPlatform.hpp>


namespace accesslib {

class GroundStation : public GroundPoint, public AccessObject, public SensorPlatform {
  public:
    GroundStation(
        const astro::Angle& latitude,
        const astro::Angle& longitude,
        const astro::Distance& altitude    = 0.0 * mp_units::si::unit_symbols::km,
        const std::vector<Sensor>& sensors = {},
        const std::string name             = "Unnammed"
    ) :
        GroundPoint(latitude, longitude, altitude),
        AccessObject(),
        SensorPlatform(sensors),
        _name(name)
    {
        generate_id_hash();
    };
    ~GroundStation() = default;

    std::size_t get_id() const { return _id; }
    std::string get_name() const { return _name; }

  private:
    std::size_t _id;
    std::string _name;

    void generate_id_hash();
};

} // namespace accesslib