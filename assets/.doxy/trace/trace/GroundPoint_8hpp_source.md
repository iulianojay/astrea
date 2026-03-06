

# File GroundPoint.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**platforms**](dir_4dbda61db413396ce1d3b920f98dbf93.md) **>** [**ground**](dir_f1cb7431ef00eaab1d7c5caeb9788760.md) **>** [**GroundPoint.hpp**](GroundPoint_8hpp.md)

[Go to the documentation of this file](GroundPoint_8hpp.md)


```C++

#pragma once

#include <string>

#include <astro/astro.fwd.hpp>
#include <astro/frames/FrameReference.hpp>
#include <astro/state/angular_elements/angular_elements.hpp>
#include <units/units.hpp>

#include <trace/platforms/AccessObject.hpp>
#include <trace/types/typedefs.hpp>


namespace astrea {
namespace trace {

class GroundPoint : virtual public AccessObject, virtual astro::FrameReference {
  public:
    GroundPoint(
        const astro::CelestialBody* parent = nullptr,
        const Angle& latitutde             = 0.0 * mp_units::angular::unit_symbols::deg,
        const Angle& longitude             = 0.0 * mp_units::angular::unit_symbols::deg,
        const Distance& altitude           = 0.0 * mp_units::si::unit_symbols::km
    );

    virtual ~GroundPoint() = default;

    bool operator==(const GroundPoint& other) const;

    const astro::Geodetic& get_lla() const;

    const Angle& get_latitude() const;

    const Angle& get_longitude() const;

    const Distance& get_altitude() const;

    const astro::CelestialBody* get_parent() const;

    std::size_t get_id() const;

    astro::CartesianVector<Distance, astro::frames::earth::earth_fixed> get_position() const;

    astro::CartesianVector<Distance, astro::frames::earth::icrf> get_inertial_position(const astro::Date& date) const;

    astro::CartesianVector<Velocity, astro::frames::earth::icrf> get_inertial_velocity(const astro::Date& date) const;

    std::string get_name() const;

  protected:
    const astro::CelestialBody* _parent; 
    astro::Geodetic _lla;                
    std::size_t _id;                     

    std::size_t generate_id();
};

} // namespace trace
} // namespace astrea
```


