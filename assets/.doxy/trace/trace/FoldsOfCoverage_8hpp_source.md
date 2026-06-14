

# File FoldsOfCoverage.hpp

[**File List**](files.md) **>** [**analysis**](dir_46c4498db40ce3dbd9ced60b5dc27dd1.md) **>** [**stats**](dir_d68b2e53ed12ccd9980273f79a385518.md) **>** [**FoldsOfCoverage.hpp**](FoldsOfCoverage_8hpp.md)

[Go to the documentation of this file](FoldsOfCoverage_8hpp.md)


```C++

#pragma once

#include <vector>

#include <gtl/phmap.hpp>

#include <units/units.hpp>

#include <trace/analysis/stats/Stats.hpp>
#include <trace/trace.fwd.hpp>

namespace astrea {
namespace trace {

class FoldsOfCoverage {
  public:
    FoldsOfCoverage() = default;

    FoldsOfCoverage(const AccessArray& access, const Time& resolution, const Time& end);

    using iterator = gtl::flat_hash_map<std::size_t, std::vector<double>>::iterator;

    using const_iterator = gtl::flat_hash_map<std::size_t, std::vector<double>>::const_iterator;

    iterator begin() { return _folds.begin(); }

    iterator end() { return _folds.end(); }

    const_iterator begin() const { return _folds.begin(); }

    const_iterator end() const { return _folds.end(); }

    const_iterator cbegin() const { return _folds.cbegin(); }

    const_iterator cend() const { return _folds.cend(); }

    const Stats<double>& get_stats(const std::size_t& id) const { return _stats.at(id); }

  private:
    gtl::flat_hash_map<std::size_t, std::vector<double>> _folds; 
    gtl::flat_hash_map<std::size_t, Stats<double>> _stats; 
};

} // namespace trace
} // namespace astrea
```


