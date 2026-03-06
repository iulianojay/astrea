

# File BodyFixedFrame.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**types**](dir_6f58486cdc039e35eca8cf5d1aadadc3.md) **>** [**BodyFixedFrame.hpp**](BodyFixedFrame_8hpp.md)

[Go to the documentation of this file](BodyFixedFrame_8hpp.md)


```C++

#pragma once

#include <string>

#include <astro/frames/Frame.hpp>

namespace astrea {
namespace astro {

template <CelestialBodyId origin>
    requires(origin != CelestialBodyId::UNSET)
struct BodyFixedFrame : public Frame<origin, FrameAxis::BODY_FIXED> {
    virtual ~BodyFixedFrame() = default;

    static constexpr CelestialBodyId get_origin() { return Frame<origin, FrameAxis::BODY_FIXED>::get_origin(); }

    static constexpr FrameAxis get_axis() { return Frame<origin, FrameAxis::BODY_FIXED>::get_axis(); }
};

} // namespace astro
} // namespace astrea
```


