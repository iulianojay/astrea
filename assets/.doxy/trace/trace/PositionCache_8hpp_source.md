

# File PositionCache.hpp

[**File List**](files.md) **>** [**analysis**](dir_46c4498db40ce3dbd9ced60b5dc27dd1.md) **>** [**PositionCache.hpp**](PositionCache_8hpp.md)

[Go to the documentation of this file](PositionCache_8hpp.md)


```C++

#pragma once

#include <vector>

#include <gtl/phmap.hpp>

#include <astro/frames/definitions.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/state/angular_elements.hpp>

#include <trace/types/typedefs.hpp>

namespace astrea {
namespace trace {

using EcefRadiusVec = astro::RadiusVector<astro::frames::earth::earth_fixed>;

class PositionCache {
  public:
    PositionCache()  = default;
    ~PositionCache() = default;

    void reserve(std::size_t nPlatforms);

    std::size_t add_platform(std::size_t platformId, std::size_t nTimesteps);

    void set_position(std::size_t platformIdx, std::size_t timeIdx, const EcefRadiusVec& position);

    const EcefRadiusVec& get_position_by_id(std::size_t platformId, std::size_t timeIdx) const;

    const EcefRadiusVec& get_position_by_index(std::size_t platformIdx, std::size_t timeIdx) const;

    std::size_t get_index(std::size_t platformId) const;

    std::size_t get_platform_id(std::size_t platformIdx) const;

    std::size_t n_platforms() const;

    std::size_t n_timesteps() const;

    void clear();

  private:
    std::vector<std::size_t> _platformIds;                   
    std::vector<std::vector<EcefRadiusVec>> _positions;      
    gtl::flat_hash_map<std::size_t, std::size_t> _idToIndex; 
};

} // namespace trace
} // namespace astrea
```


