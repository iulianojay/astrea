

# File Viewer.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**platforms**](dir_4dbda61db413396ce1d3b920f98dbf93.md) **>** [**vehicles**](dir_9708b761f2d3397b5afefec8b7ac12b4.md) **>** [**Viewer.hpp**](Viewer_8hpp.md)

[Go to the documentation of this file](Viewer_8hpp.md)


```C++

#pragma once

#include <string>

#include <astro/astro.fwd.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/state/State.hpp>
#include <astro/state/orbital_data_formats/instances/GeneralPerturbations.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

#include <trace/platforms/AccessObject.hpp>
#include <trace/platforms/sensors/Sensor.hpp>

namespace astrea {
namespace trace {

class Viewer : public astro::Spacecraft, public AccessObject, public SensorPlatform {

  public:
    Viewer() = default;

    Viewer(const astro::GeneralPerturbations& gp, const astro::AstrodynamicsSystem& system) :
        Spacecraft(gp, system),
        AccessObject()
    {
    }

    ~Viewer() = default;

    std::size_t get_id() const { return Spacecraft::get_id(); }

    std::string get_name() const { return Spacecraft::get_name(); }

    Mass get_mass() const override { return Spacecraft::get_mass(); }

    astro::RadiusVector<astro::frames::earth::icrf> get_inertial_position(const astro::Date& date) const
    {
        return Spacecraft::get_inertial_position(date);
    }

    astro::VelocityVector<astro::frames::earth::icrf> get_inertial_velocity(const astro::Date& date) const
    {
        return Spacecraft::get_inertial_velocity(date);
    }

    // This is so stupid. Why C++ standards committee
    using SensorPlatform::attach_payload;
    using SensorPlatform::get_payloads;
    using Spacecraft::attach_payload;
    using Spacecraft::get_payloads;
};

} // namespace trace
} // namespace astrea
```


