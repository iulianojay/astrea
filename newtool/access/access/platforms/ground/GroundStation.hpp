#pragma once

#include <vector>

#include <astro/types/typedefs.hpp>

#include <access/platforms/Sensor.hpp>


namespace accesslib {

class GroundStation {
  public:
    GroundStation(const astro::Angle& latitutde, const astro::Angle& longitude, const astro::Distance& altitude, const std::vector<Sensor>& sensors) :
        latitutde(latitutde),
        longitude(longitude),
        altitude(altitude),
        sensors(sensors)
    {
        generate_id_hash();
    };
    ~GroundStation(){};

    void attach(Sensor& sensor) { sensors.push_back(sensor); }
    void attach(std::vector<Sensor>& _sensors)
    {
        sensors.insert(std::end(sensors), std::begin(_sensors), std::end(_sensors));
    }

  private:
    size_t id;
    astro::Angle latitutde;
    astro::Angle longitude;
    astro::Distance altitude;

    std::vector<Sensor> sensors;

    void generate_id_hash();
};

} // namespace accesslib