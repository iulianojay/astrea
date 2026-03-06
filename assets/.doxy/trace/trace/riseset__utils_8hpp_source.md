

# File riseset\_utils.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**risesets**](dir_3852194babc4edab798292ba09c53d6d.md) **>** [**riseset\_utils.hpp**](riseset__utils_8hpp.md)

[Go to the documentation of this file](riseset__utils_8hpp.md)


```C++

#pragma once

#include <string>

#include <units/units.hpp>

#include <trace/trace.fwd.hpp>

namespace astrea {
namespace trace {

std::string to_formatted_string(Time t);

RiseSetArray riseset_union(const RiseSetArray& a, const RiseSetArray& b);

RiseSetArray riseset_intersection(const RiseSetArray& a, const RiseSetArray& b);

RiseSetArray riseset_difference(const RiseSetArray& a, const RiseSetArray& b);

} // namespace trace
} // namespace astrea
```


