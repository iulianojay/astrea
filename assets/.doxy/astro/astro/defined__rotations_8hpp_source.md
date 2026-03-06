

# File defined\_rotations.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**instances**](dir_a85615e9ad779999123e94bfb15c8545.md) **>** [**defined\_rotations.hpp**](defined__rotations_8hpp.md)

[Go to the documentation of this file](defined__rotations_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/frames/frames.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

template <typename Frame_T, typename Frame_U>
    requires(Frame_T::get_axis() == FrameAxis::J2000 && Frame_U::get_axis() == FrameAxis::ICRF && HasSameOrigin<Frame_T, Frame_U>)
inline DCM<Frame_T, Frame_U> get_dcm(const Date& date)
{
    // using mp_units::angular::unit_symbols::deg;
    // static const Angle obliquity = Angle(23.43928 * deg); // obliquity at J2000
    // return DCM<Frame_T, Frame_U>::X(obliquity);

    // boy was this wrong
    // TODO: Implement precession/nutation model for more accurate transformation. Add transformations for other
    //  "ECI" frames
    return DCM<Frame_T, Frame_U>::identity();
}

template <>
inline DirectionCosineMatrix<frames::earth::icrf, frames::earth::earth_fixed>
    get_dcm<frames::earth::icrf, frames::earth::earth_fixed>(const Date& date)
{
    const Angle gst = julian_date_to_sidereal_time(date.jd());
    return DirectionCosineMatrix<frames::earth::icrf, frames::earth::earth_fixed>::Z(-gst);
}

} // namespace astro
} // namespace astrea
```


