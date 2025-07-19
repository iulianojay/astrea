#pragma once

#include <vector>

#include <astro/types/typedefs.hpp>

#include <access/platforms/sensors/Sensor.hpp>


namespace accesslib {

class SensorPlatform {
  public:
    SensorPlatform() = default;
    SensorPlatform(const std::vector<Sensor>& sensors) :
        _sensors(sensors){};
    virtual ~SensorPlatform() = default;

    void attach(const Sensor& sensor) { _sensors.emplace_back(sensor); }
    void attach(const std::vector<Sensor>& sensors)
    {
        _sensors.insert(std::end(_sensors), std::begin(sensors), std::end(sensors));
    }

    std::vector<Sensor>& get_sensors() { return _sensors; }
    const std::vector<Sensor>& get_sensors() const { return _sensors; }

  protected:
    std::vector<Sensor> _sensors;
};

} // namespace accesslib