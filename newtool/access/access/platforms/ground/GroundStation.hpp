#pragma once

#include <vector>

#include <access/platforms/Sensor.hpp>
#include <astro/types/typedefs.hpp>

class GroundStation {
  public:
    GroundStation(const BasisArray& lla, const std::vector<Sensor>& sensors) :
        lla(lla),
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
    BasisArray lla;

    std::vector<Sensor> sensors;

    void generate_id_hash();
};