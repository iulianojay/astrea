

# File HyperStats.hpp

[**File List**](files.md) **>** [**analysis**](dir_46c4498db40ce3dbd9ced60b5dc27dd1.md) **>** [**stats**](dir_d68b2e53ed12ccd9980273f79a385518.md) **>** [**HyperStats.hpp**](HyperStats_8hpp.md)

[Go to the documentation of this file](HyperStats_8hpp.md)


```C++

#pragma once

#include <string>
#include <vector>

#include <gtl/btree.hpp>

#include <units/units.hpp>

#include <trace/analysis/stats/RiseSetStats.hpp>
#include <trace/analysis/stats/Stats.hpp>
#include <trace/risesets/RiseSetArray.hpp>
#include <trace/trace.fwd.hpp>
#include <trace/types/IdPair.hpp>
#include <trace/types/enums.hpp>

namespace astrea {
namespace trace {

template <class T = Time>
struct HyperStats {

    HyperStats() = default;

    HyperStats(const std::vector<Stats<T>>& statsVec)
    {
        std::vector<T> minVals;
        std::vector<T> maxVals;
        std::vector<T> avgVals;
        std::vector<std::vector<T>> pctVals;

        const std::size_t statsSize = statsVec.size();
        minVals.reserve(statsSize);
        maxVals.reserve(statsSize);
        avgVals.reserve(statsSize);

        const std::size_t nPercentiles = DEFAULT_PERCENTILES.size();
        pctVals.resize(nPercentiles);
        for (std::size_t ii = 0; ii < nPercentiles; ++ii) {
            pctVals[ii].reserve(statsSize);
        }

        // stats of stats. oh joy
        for (const auto& stats : statsVec) {
            // assume this marks the Stats as empty
            if (stats.percentiles.size() == 0) { continue; }

            minVals.push_back(stats.min);
            maxVals.push_back(stats.max);
            avgVals.push_back(stats.avg);

            for (std::size_t ii = 0; ii < nPercentiles; ++ii) {
                pctVals[ii].push_back(stats.percentiles[ii]);
            }
        }

        min = Stats<T>(minVals);
        max = Stats<T>(maxVals);
        avg = Stats<T>(avgVals);
        for (std::size_t ii = 0; ii < nPercentiles; ++ii) {
            percentiles.push_back(Stats<T>(pctVals[ii]));
        }
    }

    std::vector<std::string> to_string_vector() const
    {
        std::vector<std::string> retval;
        retval.reserve(HyperStats<T>::size());

        const auto minStrVec = min.to_string_vector();
        const auto avgStrVec = avg.to_string_vector();
        const auto maxStrVec = max.to_string_vector();

        retval.insert(retval.end(), minStrVec.begin(), minStrVec.end());
        retval.insert(retval.end(), avgStrVec.begin(), avgStrVec.end());
        retval.insert(retval.end(), maxStrVec.begin(), maxStrVec.end());

        for (const auto& pct : percentiles) {
            const auto pctStrVec = pct.to_string_vector();
            retval.insert(retval.end(), pctStrVec.begin(), pctStrVec.end());
        }

        return retval;
    }

    static constexpr std::size_t size() { return Stats<T>::size() * (3 + DEFAULT_PERCENTILES.size()); }

    Stats<T> min;                      
    Stats<T> max;                      
    Stats<T> avg;                      
    std::vector<Stats<T>> percentiles; 
};

} // namespace trace
} // namespace astrea
```


