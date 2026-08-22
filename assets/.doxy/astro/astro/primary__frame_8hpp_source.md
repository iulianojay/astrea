

# File primary\_frame.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**definitions**](dir_0fbce91be2e6463cb25c5b2d70c0c29c.md) **>** [**primary\_frame.hpp**](primary__frame_8hpp.md)

[Go to the documentation of this file](primary__frame_8hpp.md)


```C++

#pragma once

#include <astro/frames/definitions/body_centered_inertial_frames.hpp>
#include <astro/frames/definitions/body_fixed_frames.hpp>

namespace astrea {
namespace astro {

namespace frames {

inline constexpr auto primary       = frames::earth::icrf;
inline constexpr auto primary_fixed = frames::earth::earth_fixed;

} // namespace frames

static_assert(IsInertialFrame<std::decay_t<decltype(frames::primary)>>, "The primary frame must be inertial.");

} // namespace astro
} // namespace astrea
```


