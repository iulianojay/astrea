#pragma once

#include <vector>

#include <astro/types/typedefs.hpp>

#include <access/platforms/Sensor.hpp>


namespace accesslib {

class GroundStation {
  public:
    GroundStation(
        const astro::Angle& latitutde,
        const astro::Angle& longitude,
        const astro::Distance& altitude,
        const std::vector<Sensor>& sensors,
        const std::string name = "Unnammed"
    ) :
        _latitutde(latitutde),
        _longitude(longitude),
        _altitude(altitude),
        _sensors(sensors),
        _name(name)
    {
        generate_id_hash();
    };
    ~GroundStation(){};

    void attach(Sensor& sensor) { _sensors.push_back(sensor); }
    void attach(std::vector<Sensor>& sensors)
    {
        _sensors.insert(std::end(_sensors), std::begin(sensors), std::end(sensors));
    }

  private:
    std::size_t _id;
    astro::Angle _latitutde;
    astro::Angle _longitude;
    astro::Distance _altitude;
    std::string _name;

    std::vector<Sensor> _sensors;

    void generate_id_hash();
};

} // namespace accesslib