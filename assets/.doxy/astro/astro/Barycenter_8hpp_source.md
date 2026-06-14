

# File Barycenter.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**Barycenter.hpp**](Barycenter_8hpp.md)

[Go to the documentation of this file](Barycenter_8hpp.md)


```C++

#pragma once

#include <mp-units/framework/symbol_text.h>

#include <units/units.hpp>

#include <astro/frames/framework/Axis.hpp>
#include <astro/frames/framework/Frame.hpp>
#include <astro/frames/framework/Origin.hpp>
#include <astro/systems/system_concepts.hpp>

namespace astrea {
namespace astro {

namespace detail {

struct BarycenterBase {};

} // namespace detail

template <typename...>
struct CelestialBodyTypePack {};

template <mp_units::symbol_text, auto...>
struct Barycenter;

template <mp_units::symbol_text _name_>
struct Barycenter<_name_> : Origin<_name_>, detail::BarycenterBase {};

template <mp_units::symbol_text _name_, IsOrigin auto _parent_>
struct Barycenter<_name_, _parent_> : Origin<_name_, _parent_>, detail::BarycenterBase {};

} // namespace astro
} // namespace astrea
```


