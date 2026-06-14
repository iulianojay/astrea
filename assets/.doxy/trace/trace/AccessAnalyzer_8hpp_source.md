

# File AccessAnalyzer.hpp

[**File List**](files.md) **>** [**analysis**](dir_46c4498db40ce3dbd9ced60b5dc27dd1.md) **>** [**AccessAnalyzer.hpp**](AccessAnalyzer_8hpp.md)

[Go to the documentation of this file](AccessAnalyzer_8hpp.md)


```C++

#pragma once

#include <memory>
#include <vector>

#include <gtl/phmap.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/systems/celestial_bodies/Earth/Earth.hpp>
#include <astro/time/Date.hpp>
#include <units/units.hpp>
#include <utilities/ProgressBar.hpp>

#include <trace/analysis/PositionCache.hpp>
#include <trace/analysis/SpatialIndex.hpp>
#include <trace/platforms/sensors/Sensor.hpp>
#include <trace/risesets/AccessArray.hpp>
#include <trace/risesets/RiseSetArray.hpp>
#include <trace/trace.fwd.hpp>
#include <trace/types/typedefs.hpp>

namespace astrea {
namespace trace {


template <typename T>
concept HasSize = requires(T t) {
    { t.size() } -> std::convertible_to<std::size_t>;
};

template <typename T>
concept HasSubscriptOperator = requires(T t) {
    { &t[0] } -> std::convertible_to<std::shared_ptr<astro::PayloadPlatform<Sensor>>>;
};


template <typename T>
concept IsPlatformContainer = HasSize<T> && HasSubscriptOperator<T>;

using EciRadiusVec  = astro::RadiusVector<astro::frames::earth::icrf>;
using EcefRadiusVec = astro::RadiusVector<astro::frames::earth::earth_fixed>;

using DateVector = std::vector<astro::Date>;

using ViewerConstellation = astro::Constellation<Viewer>;


using ViewerRefVec = std::vector<std::shared_ptr<Viewer>>;

using GroundStationRefVec = std::vector<std::shared_ptr<GroundStation<astro::planets::Earth>>>;

using GroundPointRefVec = std::vector<std::shared_ptr<GroundPoint<astro::planets::Earth>>>;

using PairVec = std::vector<std::pair<std::size_t, std::size_t>>;


class AccessAnalyzer {

  public:
    AccessAnalyzer(const Time& resolution, const astro::Date& startDate, const astro::Date& endDate, const bool printProgress = false) :
        _resolution(resolution),
        _startDate(startDate),
        _endDate(endDate),
        _printProgress(printProgress)
    {
        create_date_vector();
    }

    ~AccessAnalyzer() = default;

    AccessArray find_internal_accesses(ViewerConstellation& constel, const bool clearPositionCache = true);

    AccessArray find_accesses(ViewerConstellation& constel, GroundArchitecture<astro::planets::Earth>& grounds, const bool includeInternalAccesses = false);

    AccessArray find_accesses(ViewerConstellation& constel, Grid<astro::planets::Earth>& grid, const bool includeInternalAccesses = false);

  private:
    Time _resolution;             
    astro::Date _startDate;       
    astro::Date _endDate;         
    DateVector _dates;            
    PositionCache _positionCache; 
    bool _printProgress;          

    // This isn't doing anything currently, but I'm not convinced it's a terrible idea to speed up the pre-checks by
    // binning the ground points using the spatial index and only checking the corners for very dense grids.
    // SpatialIndex _spatialIndex; //!< Spatial index for ground points

    void create_date_vector();

    bool is_central_body_occulting(const EcefRadiusVec& position1, const EcefRadiusVec& position2, const bool atmosphereBlocks) const;

    RiseSetArray find_platform_to_platform_accesses(
        std::shared_ptr<astro::PayloadPlatform<Sensor>> platform1,
        std::shared_ptr<astro::PayloadPlatform<Sensor>> platform2,
        const bool twoWay = false
    ) const;

    RiseSetArray find_platform_to_ground_point_accesses(
        std::shared_ptr<astro::PayloadPlatform<Sensor>> platform,
        const std::shared_ptr<GroundPoint<astro::planets::Earth>> groundPoint
    ) const;

    RiseSetArray find_sensor_accesses(
        const std::vector<AccessInfo>& accessInfo,
        const Sensor& sensor1,
        const std::optional<Sensor> sensor2 = std::nullopt,
        const bool twoWay                   = false
    ) const;

    bool can_objects_ever_access_each_other(const std::size_t& id1, const std::size_t& id2, const bool atmosphereBlocks) const;

    ViewerRefVec cache_viewers(ViewerConstellation& constel);

    GroundStationRefVec cache_ground_points(GroundArchitecture<astro::planets::Earth>& grounds);

    GroundPointRefVec cache_ground_points(Grid<astro::planets::Earth>& grid);

    std::vector<AccessInfo> build_access_info(const std::size_t& id1, const std::size_t& id2) const;
};

} // namespace trace
} // namespace astrea
```


