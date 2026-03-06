

# File EastNorthUp.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**instances**](dir_a85615e9ad779999123e94bfb15c8545.md) **>** [**EastNorthUp.hpp**](EastNorthUp_8hpp.md)

[Go to the documentation of this file](EastNorthUp_8hpp.md)


```C++

#pragma once

#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/frames/transformations.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/frames/types/DynamicFrame.hpp>
#include <astro/state/angular_elements/instances/Geodetic.hpp>
#include <astro/systems/planetary_bodies/planetary_bodies.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {
namespace frames {

class EastNorthUp : public DynamicFrame<EastNorthUp, FrameAxis::ENU> {

    friend DynamicFrame<EastNorthUp, FrameAxis::ENU>;

  public:
    EastNorthUp(const FrameReference* parent) :
        DynamicFrame<EastNorthUp, FrameAxis::ENU>(parent)
    {
    }

    ~EastNorthUp() = default;

    DirectionCosineMatrix<frames::earth::icrf, EastNorthUp> get_dcm(const Date& date) const
    {
        // TODO: This assumes we're using "default" Earth. REALLY don't want to pass a system
        // to this object
        static const planetary_bodies::Earth earth;
        static const Distance& rEquitorial = earth.get_equitorial_radius();
        static const Distance& rPolar      = earth.get_polar_radius();

        // eci -> ecef -> lat/lon -> n/e/u
        const RadiusVector<frames::earth::icrf> r            = get_inertial_position(date);
        const RadiusVector<frames::earth::earth_fixed> rEcef = r.in_frame<frames::earth::earth_fixed>(date);
        const auto [lat, lon, alt] = convert_earth_fixed_to_geodetic(rEcef, rEquitorial, rPolar);

        using mp_units::one;
        using mp_units::angular::cos;
        using mp_units::angular::sin;
        const Unitless sinLat = sin(lat);
        const Unitless cosLat = cos(lat);
        const Unitless sinLon = sin(lon);
        const Unitless cosLon = cos(lon);

        return DirectionCosineMatrix<frames::earth::icrf, EastNorthUp>(
            { std::array<Unitless, 3>{ -sinLat, cosLat, 0.0 * one },
              std::array<Unitless, 3>{ -cosLat * sinLon, -sinLat * sinLon, cosLon },
              std::array<Unitless, 3>{ cosLat * cosLon, sinLat * cosLon, sinLon } }
        );
    }

  private:
    EastNorthUp(const RadiusVector<frames::earth::icrf>& position, const VelocityVector<frames::earth::icrf>& velocity) :
        DynamicFrame<EastNorthUp, FrameAxis::ENU>(position, velocity)
    {
    }
};

namespace dynamic {
using enu = EastNorthUp;
} // namespace dynamic

} // namespace frames
} // namespace astro
} // namespace astrea
```


