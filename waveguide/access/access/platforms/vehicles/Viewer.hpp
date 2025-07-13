#pragma once

#include <string>


#include <astro/astro.fwd.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/state/State.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

#include <snapshot/snapshot.hpp>

#include <access/platforms/AccessObject.hpp>
#include <access/platforms/sensors/Sensor.hpp>

namespace accesslib {

class Viewer : public astro::Spacecraft, public AccessObject {

  public:
    // Constructor
    Viewer() = default;
    Viewer(const snapshot::SpaceTrackGP& gp, const astro::AstrodynamicsSystem& system) :
        Spacecraft(gp, system),
        AccessObject()
    {
    }
    Viewer(const astro::State& state0) :
        Spacecraft(state0),
        AccessObject()
    {
    }

    // Destructor
    ~Viewer() = default;

    void attach_sensor(Sensor& sensor) { _sensors.emplace_back(sensor); }
    void attach_sensors(std::vector<Sensor>& _sensors)
    {
        _sensors.insert(std::end(_sensors), std::begin(_sensors), std::end(_sensors));
    }

    std::size_t get_id() const { return Spacecraft::get_id(); }

    std::vector<Sensor>& get_sensors() { return _sensors; }
    const std::vector<Sensor>& get_sensors() const { return _sensors; }

  private:
    std::vector<Sensor> _sensors;
};

} // namespace accesslib