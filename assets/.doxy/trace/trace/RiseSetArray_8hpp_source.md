

# File RiseSetArray.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**risesets**](dir_3852194babc4edab798292ba09c53d6d.md) **>** [**RiseSetArray.hpp**](RiseSetArray_8hpp.md)

[Go to the documentation of this file](RiseSetArray_8hpp.md)


```C++

#pragma once

#include <vector>

#include <units/units.hpp>

#include <trace/risesets/riseset_utils.hpp>
#include <trace/types/enums.hpp>
#include <trace/types/typedefs.hpp>

namespace astrea {
namespace trace {

class RiseSetArray {

    friend std::ostream& operator<<(std::ostream& os, const RiseSetArray& risesets);

  public:
    RiseSetArray() = default;

    ~RiseSetArray() = default;

    RiseSetArray(const std::vector<Time>& risesets);

    RiseSetArray(const RiseSetArray& other);

    RiseSetArray(RiseSetArray&& other) noexcept;

    RiseSetArray& operator=(RiseSetArray&& other) noexcept;

    RiseSetArray& operator=(const RiseSetArray& other);

    void append(const Time& rise, const Time& set);

    void prepend(const Time& rise, const Time& set);

    void insert(const Time& rise, const Time& set);

    std::size_t size() const;

    bool empty() const;

    Time& operator[](const std::size_t& ind); // TODO: Should this be allowed? Makes it possible to generate bad rise/set pairs

    const Time& operator[](const std::size_t& ind) const;

    bool operator==(const RiseSetArray& other) const;

    RiseSetArray operator-(const RiseSetArray& other) const;

    RiseSetArray& operator-=(const RiseSetArray& other);

    RiseSetArray operator|(const RiseSetArray& other) const;

    RiseSetArray& operator|=(const RiseSetArray& other);

    RiseSetArray operator&(const RiseSetArray& other) const;

    RiseSetArray& operator&=(const RiseSetArray& other);

    Time gap(const StatType& stat = StatType::AVG, const Unitless percentile = 0.5) const;

    std::vector<Time> get_gap_times() const;

    Time access_time(const StatType& stat = StatType::AVG, const Unitless percentile = 0.5) const;

    std::vector<Time> get_access_times() const;

    bool has_access(const Time& time) const;

    Time average_daily_vis_time() const;

    Time mean_time_to_access() const;

    using iterator = std::vector<Time>::iterator;

    using const_iterator = std::vector<Time>::const_iterator;

    iterator begin();

    iterator end();

    const_iterator begin() const;

    const_iterator end() const;

    const_iterator cbegin() const;

    const_iterator cend() const;

    std::vector<std::string> to_string_vector() const;

  private:
    std::vector<Time> _risesets; 

    void validate_riseset(const Time& rise, const Time& set) const;

    void validate_risesets(const std::vector<Time>& risesets) const;

    Time calculate_statistic(const StatType& stat, const Unitless& percentile, const RiseSetMetric metric) const;
};

} // namespace trace
} // namespace astrea
```


