

# File Stats.hpp

[**File List**](files.md) **>** [**analysis**](dir_46c4498db40ce3dbd9ced60b5dc27dd1.md) **>** [**stats**](dir_d68b2e53ed12ccd9980273f79a385518.md) **>** [**Stats.hpp**](Stats_8hpp.md)

[Go to the documentation of this file](Stats_8hpp.md)


```C++

#pragma once

#include <concepts>
#include <string>
#include <vector>

#include <gtl/btree.hpp>
#include <mp-units/concepts.h>
#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <trace/risesets/RiseSetArray.hpp>
#include <trace/types/enums.hpp>

namespace astrea {
namespace trace {

// Default percentiles to calculate for statistics.
static const std::vector<Unitless> DEFAULT_PERCENTILES{ 1, 5, 10, 25, 50, 75, 90, 95, 99 };

template <class T = Time>
struct Stats {

    Stats() = default;

    Stats(const RiseSetArray& risesets, const RiseSetMetric& metric) = delete;

    Stats(std::vector<T> values)
    {
        using mp_units::one;
        using mp_units::si::unit_symbols::s;

        if (values.size() == 0) { throw std::runtime_error("Cannot calculate statistics on an empty vector."); }

        // Sort automatically gives min, max, and sets up for percentile calcs
        std::sort(values.begin(), values.end());

        min = values[0];
        max = values[values.size() - 1];
        avg = T(); // this should be 0?
        for (const auto& time : values) {
            avg += time;
        }
        avg /= static_cast<double>(values.size());

        const std::size_t nTimes = values.size();
        for (const auto& pct : DEFAULT_PERCENTILES) {
            const std::size_t index = static_cast<std::size_t>(std::ceil(pct.numerical_value_in(one) * nTimes / 100)) - 1;
            percentiles.push_back(values[index]);
        }
    }

    std::vector<std::string> to_string_vector() const
    {
        std::vector<std::string> retval;
        retval.reserve(Stats<T>::size());

        // TODO: this order is weakly enforced. Hopefully it doesn't break anything
        retval.push_back(std::to_string(min));
        retval.push_back(std::to_string(avg));
        retval.push_back(std::to_string(max));
        for (const auto& pct : percentiles) {
            retval.push_back(std::to_string(pct));
        }

        return retval;
    }

    static constexpr std::size_t size() { return DEFAULT_PERCENTILES.size() + 3; }

    T min;                      
    T max;                      
    T avg;                      
    std::vector<T> percentiles; 
};

template <>
inline Stats<Time>::Stats(const RiseSetArray& risesets, const RiseSetMetric& metric)
{
    percentiles.reserve(DEFAULT_PERCENTILES.size());
    switch (metric) {
        case (RiseSetMetric::ACCESS_TIME): {
            *this = Stats(risesets.get_access_times());
            break;
        }
        case (RiseSetMetric::GAP): {
            *this = risesets.size() > 2 ? Stats(risesets.get_gap_times()) : Stats();
            break;
        }
        default: throw std::runtime_error("Unrecognized riseset metric.");
    }
}

template <>
inline std::vector<std::string> Stats<Time>::to_string_vector() const
{
    std::vector<std::string> retval;
    retval.reserve(Stats<Time>::size());

    retval.push_back(to_formatted_string(min));
    retval.push_back(to_formatted_string(avg));
    retval.push_back(to_formatted_string(max));
    for (const auto& pct : percentiles) {
        retval.push_back(to_formatted_string(pct));
    }

    return retval;
}

} // namespace trace
} // namespace astrea
```


