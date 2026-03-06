

# File SpatialIndex.hpp

[**File List**](files.md) **>** [**analysis**](dir_46c4498db40ce3dbd9ced60b5dc27dd1.md) **>** [**SpatialIndex.hpp**](SpatialIndex_8hpp.md)

[Go to the documentation of this file](SpatialIndex_8hpp.md)


```C++

#pragma once

#include <unordered_set>
#include <vector>

#include <units/units.hpp>

namespace astrea {
namespace trace {

struct GeographicBin {
    Angle latMin, latMax;
    Angle lonMin, lonMax;
    std::vector<std::size_t> groundPointIndices;

    bool contains(const Angle& lat, const Angle& lon) const
    {
        return lat >= latMin && lat <= latMax && lon >= lonMin && lon <= lonMax;
    }
};

class SpatialIndex {
  public:
    SpatialIndex(const Angle& binSize = 10.0 * mp_units::angular::unit_symbols::deg);

    void add_ground_point(std::size_t groundPointIdx, const Angle& lat, const Angle& lon);

    std::unordered_set<std::size_t> get_nearby_ground_points(const Angle& lat, const Angle& lon, const Angle& radius) const;

    std::vector<std::size_t> get_all_ground_points() const;

    void clear();

  private:
    Angle _binSize;
    std::size_t _nLatBins;
    std::size_t _nLonBins;
    std::vector<GeographicBin> _bins;

    std::size_t get_lat_bin_index(const Angle& lat) const;

    std::size_t get_lon_bin_index(const Angle& lon) const;

    std::size_t get_bin_index(const Angle& lat, const Angle& lon) const;
};

} // namespace trace
} // namespace astrea
```


