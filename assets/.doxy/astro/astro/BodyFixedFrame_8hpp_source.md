

# File BodyFixedFrame.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**framework**](dir_aa3952657448f7008c08b8ed45c303ac.md) **>** [**BodyFixedFrame.hpp**](BodyFixedFrame_8hpp.md)

[Go to the documentation of this file](BodyFixedFrame_8hpp.md)


```C++

#pragma once

#include <type_traits>

#include <mp-units/framework/symbol_text.h>

#include <units/units.hpp>

#include <astro/frames/framework/Frame.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/systems/system_concepts.hpp>

namespace astrea {
namespace astro {

namespace detail {

struct BodyFixedFrameBase {};

} // namespace detail

template <mp_units::symbol_text _name_, IsCelestialBody auto _origin_, IsAxis auto _axis_ = _origin_.reference_axes>
struct BodyFixedFrame : Frame<_name_, _origin_, _axis_>, detail::BodyFixedFrameBase {};

} // namespace astro
} // namespace astrea
```


