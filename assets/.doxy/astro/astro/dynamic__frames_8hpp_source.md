

# File dynamic\_frames.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**definitions**](dir_0fbce91be2e6463cb25c5b2d70c0c29c.md) **>** [**dynamic\_frames.hpp**](dynamic__frames_8hpp.md)

[Go to the documentation of this file](dynamic__frames_8hpp.md)


```C++

#pragma once

#include <astro/frames/definitions/EastNorthUp.hpp>
#include <astro/frames/definitions/LocalHorizontalLocalVertical.hpp>
#include <astro/frames/definitions/RadialInTrackCrossTrack.hpp>
#include <astro/frames/definitions/VelocityNormalBinormal.hpp>
#include <astro/frames/definitions/frame_registry.hpp>
#include <astro/frames/framework/DynamicFrame.hpp>
#include <astro/frames/framework/Frame.hpp>

namespace astrea {
namespace astro {
namespace frames {
namespace dynamic {

inline constexpr struct body final : Frame<"body", DynamicOrigin{}, DynamicAxis{}> {
} body;

inline constexpr EastNorthUpTag<frames::primary> enu{};

inline constexpr LvlhTag<frames::primary> lvlh{};

inline constexpr RicTag<frames::primary> ric{};

inline constexpr VnbTag<frames::primary> vnb{};

} // namespace dynamic
} // namespace frames
} // namespace astro
} // namespace astrea
```


