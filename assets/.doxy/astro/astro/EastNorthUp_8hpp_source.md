

# File EastNorthUp.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**definitions**](dir_0fbce91be2e6463cb25c5b2d70c0c29c.md) **>** [**EastNorthUp.hpp**](EastNorthUp_8hpp.md)

[Go to the documentation of this file](EastNorthUp_8hpp.md)


```C++

#pragma once

#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions/transformations.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/frames/framework/DirectionCosineMatrix.hpp>
#include <astro/frames/framework/DynamicFrame.hpp>
#include <astro/frames/framework/Frame.hpp>
#include <astro/state/angular_elements/Geodetic.hpp>
#include <astro/systems/celestial_bodies.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {
namespace frames {

template <IsFrame auto _parent_>
struct EastNorthUpTag : Frame<"East-North-Up", DynamicOrigin{}, DynamicAxis{}, _parent_> {
    EastNorthUp<_parent_> instantaneous(const RadiusVector<_parent_>& r, const VelocityVector<_parent_>& v) const
    {
        return EastNorthUp<_parent_>(r, v);
    }
};

template <IsFrame auto _parent_>
inline constexpr EastNorthUpTag<_parent_> enu_tag{};

template <IsFrame auto _frame_>
struct EastNorthUp : public DynamicFrame<EastNorthUp<_frame_>, _frame_, enu_tag<_frame_>> {

    using tag_type = EastNorthUpTag<_frame_>; 
    static inline constexpr tag_type tag{};   
    static constexpr auto frame = _frame_;    

    EastNorthUp(const RadiusVector<frame>& position, const VelocityVector<frame>& velocity) :
        DynamicFrame<EastNorthUp<_frame_>, frame, enu_tag<_frame_>>(position, velocity)
    {
    }

    EastNorthUp() = delete; 

    DirectionCosineMatrix<frame, tag> get_dcm(const Date& date) const
    {
        // eci -> ecef -> lat/lon -> n/e/u
        const RadiusVector<frame> r            = this->get_position(date);
        static constexpr auto fixed_frame      = get_body_fixed_frame<frame.origin>();
        const RadiusVector<fixed_frame> rFixed = r.template in_frame<fixed_frame>(date);
        const auto [lat, lon, alt]             = convert_body_fixed_to_geodetic(rFixed);

        using mp_units::one;
        using mp_units::angular::cos;
        using mp_units::angular::sin;
        const Unitless sinLat = sin(lat);
        const Unitless cosLat = cos(lat);
        const Unitless sinLon = sin(lon);
        const Unitless cosLon = cos(lon);

        return DirectionCosineMatrix<frame, tag>(
            { -sinLat, cosLat, 0.0 * one }, { -cosLat * sinLon, -sinLat * sinLon, cosLon }, { cosLat * cosLon, sinLat * cosLon, sinLon }
        );
    }
};


} // namespace frames
} // namespace astro
} // namespace astrea
```


