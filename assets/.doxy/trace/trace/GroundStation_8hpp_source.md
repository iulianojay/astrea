

# File GroundStation.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**platforms**](dir_4dbda61db413396ce1d3b920f98dbf93.md) **>** [**ground**](dir_f1cb7431ef00eaab1d7c5caeb9788760.md) **>** [**GroundStation.hpp**](GroundStation_8hpp.md)

[Go to the documentation of this file](GroundStation_8hpp.md)


```C++

#pragma once

#include <string>
#include <vector>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/time/Date.hpp>
#include <units/units.hpp>

#include <trace/platforms/ground/GroundPoint.hpp>
#include <trace/platforms/sensors/Sensor.hpp>

namespace astrea {
namespace trace {

class GroundStation : public GroundPoint, public SensorPlatform {
  public:
    GroundStation(
        const astro::CelestialBody* parent,
        const Angle& latitude,
        const Angle& longitude,
        const Distance& altitude                     = 0.0 * mp_units::si::unit_symbols::km,
        const std::string name                       = "Unnammed",
        const std::vector<SensorParameters>& sensors = {}
    );

    ~GroundStation() = default;

    std::size_t get_id() const;

    std::string get_name() const;

    astro::CartesianVector<Distance, astro::frames::earth::icrf> get_inertial_position(const astro::Date& date) const;

    astro::CartesianVector<Velocity, astro::frames::earth::icrf> get_inertial_velocity(const astro::Date& date) const;

  private:
    std::string _name; 
};

} // namespace trace
} // namespace astrea
```


