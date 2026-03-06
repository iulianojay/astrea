

# File frame\_concepts.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**frame\_concepts.hpp**](frame__concepts_8hpp.md)

[Go to the documentation of this file](frame__concepts_8hpp.md)


```C++

#pragma once

#include <concepts>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

template <typename Frame_T>
concept IsInertialFrame = (Frame_T::get_axis() == FrameAxis::ICRF || Frame_T::get_axis() == FrameAxis::J2000);

template <typename Frame_T>
concept IsBodyFixedFrame = (Frame_T::get_axis() == FrameAxis::BODY_FIXED);

template <typename Frame_T>
concept IsStaticFrame =
    (Frame_T::get_axis() == FrameAxis::ICRF || Frame_T::get_axis() == FrameAxis::J2000 || Frame_T::get_axis() == FrameAxis::BODY_FIXED);

template <typename Frame_T>
concept IsDynamicFrame =
    (Frame_T::get_axis() == FrameAxis::LVLH || Frame_T::get_axis() == FrameAxis::RIC || Frame_T::get_axis() == FrameAxis::VNB);

template <typename Frame_T, typename Frame_U>
concept HasSameOrigin = (Frame_T::get_origin() == Frame_U::get_origin());

template <typename Frame_T, typename Frame_U>
concept HasSameAxis = (Frame_T::get_axis() == Frame_U::get_axis());

template <typename Frame_T, typename Frame_U>
concept IsSameFrame = HasSameOrigin<Frame_T, Frame_U> && HasSameAxis<Frame_T, Frame_U>;

template <typename Frame_T, typename Frame_U>
concept HasDcm = requires(const Date& date) { get_dcm<Frame_T, Frame_U>(date); };

template <typename Frame_T, typename Frame_U>
concept HasDcmMethod =
    requires(const Frame_T& frame, const Date& date) { frame.template get_dcm<Frame_T, Frame_U>(date); };

} // namespace astro
} // namespace astrea
```


