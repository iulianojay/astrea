#pragma once

#include <string>


#include <astro/astro.fwd.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/state/State.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

#include <snapshot/http-queries/spacetrack/SpaceTrackGP.hpp>

#include <access/platforms/AccessObject.hpp>
#include <access/platforms/sensors/Sensor.hpp>

namespace waveguide {
namespace accesslib {

class Viewer : public astro::Spacecraft, public AccessObject, public SensorPlatform {

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

    std::size_t get_id() const { return Spacecraft::get_id(); }

  private:
    std::vector<Sensor> _sensors;
};

} // namespace accesslib
} // namespace waveguide