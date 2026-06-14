

# File system\_concepts.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**system\_concepts.hpp**](system__concepts_8hpp.md)

[Go to the documentation of this file](system__concepts_8hpp.md)


```C++

#pragma once

#include <concepts>

namespace astrea {
namespace astro {

namespace detail {

// Forward declarations of base types
struct CelestialBodyBase;
struct BarycenterBase;

} // namespace detail

template <typename T>
concept IsCelestialBody = std::derived_from<T, detail::CelestialBodyBase> && !std::derived_from<T, detail::BarycenterBase>;

template <typename T>
concept IsBarycenter = std::derived_from<T, detail::BarycenterBase> && !std::derived_from<T, detail::CelestialBodyBase>;

template <typename T>
concept IsCelestialReference = IsCelestialBody<T> || IsBarycenter<T>;

} // namespace astro
} // namespace astrea
```


