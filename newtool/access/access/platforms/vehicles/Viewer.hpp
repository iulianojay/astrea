#pragma once

#ifndef SWIG
#include <string>
#include <unordered_map>
#endif

#include <astro/constants/astronomical_constants.h>
#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/state/State.hpp>
#include <astro/time/Date.hpp>
#include <astro/time/Time.hpp>
#include <astro/types/typedefs.hpp>

#include <astro/astro.fwd.hpp>

#include <access/platforms/Sensor.hpp>

class Viewer : public Spacecraft {

  public:
    // Constructor
    Viewer() = default;
    Viewer(OrbitalElements state0, Date epoch = J2000) :
        Spacecraft(state0, epoch){};

    // Destructor
    ~Viewer() = default;

    void attach(Sensor& sensor) { _sensors.emplace_back(sensor); }
    void attach(std::vector<Sensor>& _sensors)
    {
        _sensors.insert(std::end(_sensors), std::begin(_sensors), std::end(_sensors));
    }

    std::vector<Sensor>& get_sensors() { return _sensors; }
    const std::vector<Sensor>& get_sensors() const { return _sensors; }

    void add_access(const size_t& receiverId, const RiseSetArray& access) { _accesses[_id, receiverId] = access; }

  private:
    AccessArray _accesses;
    std::vector<Sensor> _sensors;
};


#ifdef SWIG

%template(ViewerVector) std::vector<Viewer>;
%template(ViewerVectorVector) std::vector<std::vector<Viewer>>;

#endif