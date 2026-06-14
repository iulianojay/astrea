

# File AccessStats.hpp

[**File List**](files.md) **>** [**analysis**](dir_46c4498db40ce3dbd9ced60b5dc27dd1.md) **>** [**stats**](dir_d68b2e53ed12ccd9980273f79a385518.md) **>** [**AccessStats.hpp**](AccessStats_8hpp.md)

[Go to the documentation of this file](AccessStats_8hpp.md)


```C++

#pragma once

#include <string>
#include <vector>

#include <gtl/phmap.hpp>

#include <units/units.hpp>

#include <trace/analysis/stats/HyperStats.hpp>
#include <trace/analysis/stats/RiseSetStats.hpp>
#include <trace/analysis/stats/Stats.hpp>
#include <trace/risesets/RiseSetArray.hpp>
#include <trace/trace.fwd.hpp>
#include <trace/types/IdPair.hpp>
#include <trace/types/enums.hpp>

namespace astrea {
namespace trace {

struct AccessStats {
    AccessStats() = default;

    AccessStats(const AccessArray& accesses);

    std::vector<std::string> to_string_vector() const;

    const auto& get_riseset_statistics() const { return _stats; }

    const auto& get_riseset_statistics(std::size_t receiverId) const { return _stats.at(receiverId); }

    const auto& get_access_metric(std::size_t receiverId, const AccessMetric& metric) const
    {
        return _accessMetrics.at(receiverId).at(metric);
    }

    const auto& get_access_metrics() const { return _accessMetrics; }

    const auto& get_access_statistics(const AccessMetric& metric) const { return _accessStats.at(metric); }

    const auto& get_hyper_statistics(const RiseSetMetric& metric) const { return _hyperStats.at(metric); }

    auto& get_hyper_statistics(const RiseSetMetric& metric) { return _hyperStats[metric]; }

  private:
    gtl::flat_hash_map<std::size_t, RiseSetArray> _risesets;         
    gtl::flat_hash_map<std::size_t, RiseSetStats> _stats;            
    gtl::flat_hash_map<RiseSetMetric, HyperStats<Time>> _hyperStats; 

    gtl::flat_hash_map<std::size_t, gtl::flat_hash_map<AccessMetric, Time>> _accessMetrics; 
    gtl::flat_hash_map<AccessMetric, Stats<Time>> _accessStats;                             
};

} // namespace trace
} // namespace astrea
```


