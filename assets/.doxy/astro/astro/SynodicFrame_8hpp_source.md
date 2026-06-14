

# File SynodicFrame.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**framework**](dir_aa3952657448f7008c08b8ed45c303ac.md) **>** [**SynodicFrame.hpp**](SynodicFrame_8hpp.md)

[Go to the documentation of this file](SynodicFrame_8hpp.md)


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

struct SynodicFrameBase {};

} // namespace detail

template <IsCelestialBody auto _primary_, IsCelestialBody auto _secondary_>
struct SynodicAxis
    : Axis<_primary_.name + mp_units::symbol_text{ "-" } + _secondary_.name + mp_units::symbol_text{ " synodic axis" }> {
    static constexpr auto primary   = _primary_;
    static constexpr auto secondary = _secondary_;
};


template <mp_units::symbol_text _name_, IsBarycenter auto _origin_, IsCelestialBody auto _primary_, IsCelestialBody auto _secondary_>
struct SynodicFrame : Frame<_name_, _origin_, SynodicAxis<_primary_, _secondary_>{}>, detail::SynodicFrameBase {};

} // namespace astro
} // namespace astrea
```


