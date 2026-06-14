

# File trace.fwd.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**trace.fwd.hpp**](trace_8fwd_8hpp.md)

[Go to the documentation of this file](trace_8fwd_8hpp.md)


```C++

#pragma once

#include <astro/systems/system_concepts.hpp>

namespace astrea {
namespace trace {

struct IdPair;
class RiseSetArray;
class AccessArray;

template <astro::IsCelestialBody auto _body_>
class Grid;
template <astro::IsCelestialBody auto _body_>
class GroundPoint;
template <astro::IsCelestialBody auto _body_>
class GroundArchitecture;
template <astro::IsCelestialBody auto _body_>
class GroundStation;

class Sensor;
class Viewer;

struct AccessInfo;

template <class T>
struct Stats;
struct RiseSetStats;
struct AccessStats;

} // namespace trace
} // namespace astrea
```


