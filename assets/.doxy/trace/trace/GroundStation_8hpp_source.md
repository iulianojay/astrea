

# File GroundStation.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**platforms**](dir_4dbda61db413396ce1d3b920f98dbf93.md) **>** [**ground**](dir_f1cb7431ef00eaab1d7c5caeb9788760.md) **>** [**GroundStation.hpp**](GroundStation_8hpp.md)

[Go to the documentation of this file](GroundStation_8hpp.md)


```C++

#pragma once

#include <string>
#include <vector>

#include <astro/systems/system_concepts.hpp>
#include <astro/time/Date.hpp>
#include <units/units.hpp>

#include <trace/platforms/ground/GroundPoint.hpp>
#include <trace/platforms/sensors/Sensor.hpp>

namespace astrea {
namespace trace {

template <astro::IsCelestialBody auto _body_>
class GroundStation : public GroundPoint<_body_>, public SensorPlatform {
    using Base = GroundPoint<_body_>;

  public:
    GroundStation(
        const Angle& latitude,
        const Angle& longitude,
        const Distance& altitude                     = 0.0 * mp_units::si::unit_symbols::km,
        const std::string name                       = "Unnamed",
        const std::vector<SensorParameters>& sensors = {}
    ) :
        Base(latitude, longitude, altitude),
        SensorPlatform(),
        _name(name)
    {
        for (const auto& sp : sensors) {
            attach_payload(sp);
        }
    }

    ~GroundStation() = default;

    std::size_t get_id() const override { return Base::_id; }

    std::string get_name() const { return _name; }

    auto get_position() const { return Base::get_position(); }

    astro::RadiusVector<astro::frames::primary> get_position(const astro::Date& date) const
    {
        return Base::get_position(date);
    }

    astro::VelocityVector<astro::frames::primary> get_velocity(const astro::Date& date) const
    {
        return Base::get_velocity(date);
    }

  private:
    std::string _name; 
};

} // namespace trace
} // namespace astrea
```


