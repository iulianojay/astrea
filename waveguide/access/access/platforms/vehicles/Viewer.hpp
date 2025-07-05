#pragma once

#include <string>
#include <unordered_map>


#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/state/State.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

#include <astro/astro.fwd.hpp>
#include <snapshot/snapshot.hpp>

#include <access/platforms/Sensor.hpp>

namespace accesslib {

class Viewer : public astro::Spacecraft {

  public:
    // Constructor
    Viewer() = default;
    Viewer(const snapshot::SpaceTrackGP& gp) :
        Spacecraft(gp)
    {
    }
    Viewer(astro::OrbitalElements state0, astro::Date epoch = astro::J2000) :
        Spacecraft(state0, epoch){};

    // Destructor
    ~Viewer() = default;

    void attach_sensor(Sensor& sensor) { _sensors.emplace_back(sensor); }
    void attach_sensors(std::vector<Sensor>& _sensors)
    {
        _sensors.insert(std::end(_sensors), std::begin(_sensors), std::end(_sensors));
    }

    std::vector<Sensor>& get_sensors() { return _sensors; }
    const std::vector<Sensor>& get_sensors() const { return _sensors; }

    const AccessArray& get_accesses() const { return _accesses; }

    void add_access(const std::size_t& receiverId, const RiseSetArray& access) { _accesses[_id, receiverId] = access; }

  private:
    AccessArray _accesses;
    std::vector<Sensor> _sensors;
};

} // namespace accesslib