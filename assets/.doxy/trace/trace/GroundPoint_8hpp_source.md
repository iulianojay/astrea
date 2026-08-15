

# File GroundPoint.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**platforms**](dir_4dbda61db413396ce1d3b920f98dbf93.md) **>** [**ground**](dir_f1cb7431ef00eaab1d7c5caeb9788760.md) **>** [**GroundPoint.hpp**](GroundPoint_8hpp.md)

[Go to the documentation of this file](GroundPoint_8hpp.md)


```C++

#pragma once

#include <sstream>
#include <string>

#include <mp-units/systems/si.h>

#include <astro/astro.fwd.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/state/angular_elements.hpp>
#include <astro/systems/property_getters.hpp>
#include <astro/systems/system_concepts.hpp>
#include <astro/time/Date.hpp>
#include <units/units.hpp>

#include <utilities/IdProvider.hpp>

#include <trace/platforms/AccessObject.hpp>
#include <trace/types/typedefs.hpp>


namespace astrea {
namespace trace {

template <astro::IsCelestialBody auto _body_>
class GroundPoint : virtual public AccessObject {
  public:
    static constexpr auto body = _body_; 

    GroundPoint(
        const Angle& latitude    = 0.0 * mp_units::si::unit_symbols::deg,
        const Angle& longitude   = 0.0 * mp_units::si::unit_symbols::deg,
        const Distance& altitude = 0.0 * mp_units::si::unit_symbols::km
    ) :
        AccessObject(),
        _lla(latitude, longitude, altitude),
        _id(utilities::IdProvider::get_next_id<"Platform">())
    {
    }

    virtual ~GroundPoint() = default;

    bool operator==(const GroundPoint& other) const { return _lla == other._lla; }

    const astro::Geodetic<_body_>& get_lla() const { return _lla; }

    const Angle& get_latitude() const { return _lla.get_latitude(); }

    const Angle& get_longitude() const { return _lla.get_longitude(); }

    const Distance& get_altitude() const { return _lla.get_altitude(); }

    std::size_t get_id() const override { return _id; }

    auto get_position() const { return _lla.get_position(); }

    auto get_position(const astro::Date& date) const { return _lla.get_position(date); }

    auto get_velocity(const astro::Date& date) const
    {
        using namespace mp_units::si::unit_symbols;
        constexpr auto fixed_frame = astro::Geodetic<_body_>::_fixed_frame_;
        constexpr auto icrf_frame  = astro::Geodetic<_body_>::_icrf_frame_;

        const auto rEcef = _lla.get_position();
        const auto rEcefPlanar = astro::CartesianVector<Distance, fixed_frame>{ rEcef.get_x(), rEcef.get_y(), 0.0 * km };

        const Distance rEcefPlanarNorm = rEcefPlanar.norm();
        const Velocity vEcefMag        = rEcefPlanarNorm * astro::get_rotation_rate<_body_>() / rad;

        const astro::CartesianVector<Distance, fixed_frame> z{ 0.0 * km, 0.0 * km, 1.0 * km };
        const auto vEcef = z.cross(rEcefPlanar).direction() * vEcefMag;

        return vEcef.template in_frame<icrf_frame>(date, rEcef);
    }

    std::string get_name() const
    {
        using mp_units::si::unit_symbols::deg;
        using mp_units::si::unit_symbols::km;

        std::ostringstream oss;
        oss << "[" << _lla.get_latitude().in(deg) << ", " << _lla.get_longitude().in(deg);
        if (_lla.get_altitude() != 0.0 * km) { oss << ", " << _lla.get_altitude(); }
        oss << "]";
        oss << " (" << decltype(_body_)::name.portable() << ")";

        return oss.str();
    }

  protected:
    astro::Geodetic<_body_> _lla; 
    std::size_t _id;              
};

} // namespace trace
} // namespace astrea
```


