

# File RiseSetStats.hpp

[**File List**](files.md) **>** [**analysis**](dir_46c4498db40ce3dbd9ced60b5dc27dd1.md) **>** [**stats**](dir_d68b2e53ed12ccd9980273f79a385518.md) **>** [**RiseSetStats.hpp**](RiseSetStats_8hpp.md)

[Go to the documentation of this file](RiseSetStats_8hpp.md)


```C++

#pragma once

#include <string>
#include <vector>

#include <gtl/phmap.hpp>

#include <units/units.hpp>

#include <trace/analysis/stats/Stats.hpp>
#include <trace/trace.fwd.hpp>
#include <trace/types/enums.hpp>

namespace astrea {
namespace trace {

struct RiseSetStats {

    RiseSetStats() = default;

    RiseSetStats(const RiseSetArray& risesets);

    std::vector<std::string> to_string_vector() const;

    const auto& at(const RiseSetMetric& metric) const { return _stats.at(metric); }

    auto& operator[](const RiseSetMetric& metric) { return _stats[metric]; }

  private:
    gtl::flat_hash_map<RiseSetMetric, Stats<Time>> _stats; 
};

} // namespace trace
} // namespace astrea
```


