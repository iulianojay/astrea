

# File typedefs.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**types**](dir_99d9bc6205d35ba61d9e386839c646c4.md) **>** [**typedefs.hpp**](typedefs_8hpp.md)

[Go to the documentation of this file](typedefs_8hpp.md)


```C++

#pragma once

#include <cstdint>

#include <astro/astro.fwd.hpp>
#include <astro/frames.hpp>
#include <astro/systems.hpp>

#include <trace/trace.fwd.hpp>

namespace astrea {
namespace trace {

using EnumType = uint32_t;

using LatLon = std::pair<Angle, Angle>;

using LatRange = std::pair<Angle, Angle>;

using LonRange = std::pair<Angle, Angle>;

using EciRadiusVec = astro::CartesianVector<Distance, astro::frames::earth::icrf>;

using EcefRadiusVec = astro::CartesianVector<Distance, astro::frames::earth::earth_fixed>;

using DateVector = std::vector<astro::Date>;

using ViewerConstellation = astro::Constellation<Viewer>;

using ViewerRefVec = std::vector<std::shared_ptr<Viewer>>;

using GroundStationRefVec = std::vector<std::shared_ptr<GroundStation<astro::planets::Earth>>>;

using GroundPointRefVec = std::vector<std::shared_ptr<GroundPoint<astro::planets::Earth>>>;

using PairVec = std::vector<std::pair<std::size_t, std::size_t>>;

using BoresightTable = std::vector<std::vector<EciRadiusVec>>;

} // namespace trace
} // namespace astrea
```


