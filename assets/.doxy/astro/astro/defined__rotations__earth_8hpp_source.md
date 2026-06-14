

# File defined\_rotations\_earth.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**definitions**](dir_0fbce91be2e6463cb25c5b2d70c0c29c.md) **>** [**defined\_rotations\_earth.hpp**](defined__rotations__earth_8hpp.md)

[Go to the documentation of this file](defined__rotations__earth_8hpp.md)


```C++

#pragma once

#include <type_traits>

#include <mp-units/systems/angular/math.h>

#include <astro/frames/definitions/body_centered_inertial_frames.hpp>
#include <astro/frames/definitions/body_fixed_frames.hpp>
#include <astro/frames/definitions/defined_rotations.hpp>
#include <astro/systems/celestial_bodies.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

template <IsFrame auto in_frame, IsFrame auto out_frame>
    requires(in_frame.origin == out_frame.origin && in_frame.origin == planets::Earth && in_frame.axis == axes::icrf && IsBodyFixedFrame<decltype(out_frame)>)
inline constexpr DirectionCosineMatrix<in_frame, out_frame> get_dcm(const Date& date)
{
    const Angle gst = julian_date_to_sidereal_time(date.jd());
    return DirectionCosineMatrix<in_frame, out_frame>::Z(-gst);
}

} // namespace astro
} // namespace astrea
```


