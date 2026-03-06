

# File Frame.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**Frame.hpp**](Frame_8hpp.md)

[Go to the documentation of this file](Frame_8hpp.md)


```C++

#pragma once

#include <string>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/frame_concepts.hpp>

namespace astrea {
namespace astro {

template <CelestialBodyId origin, FrameAxis axis>
struct Frame {

  protected:
    virtual ~Frame() = default;

  public:
    static constexpr CelestialBodyId get_origin() { return _origin; }

    static constexpr FrameAxis get_axis() { return _axis; }

  protected:
    static constexpr CelestialBodyId _origin = origin; 
    static constexpr FrameAxis _axis         = axis;   
};


} // namespace astro
} // namespace astrea
```


