

# File AccessAnalyzer.hpp

[**File List**](files.md) **>** [**analysis**](dir_46c4498db40ce3dbd9ced60b5dc27dd1.md) **>** [**AccessAnalyzer.hpp**](AccessAnalyzer_8hpp.md)

[Go to the documentation of this file](AccessAnalyzer_8hpp.md)


```C++

#pragma once

#include <memory>
#include <vector>

#include <gtl/btree.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
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

using GroundStationRefVec = std::vector<std::shared_ptr<GroundStation>>;

using GroundPointRefVec = std::vector<std::shared_ptr<GroundPoint>>;

using PairVec = std::vector<std::pair<std::size_t, std::size_t>>;


class AccessAnalyzer {

  public:
    AccessAnalyzer(const Time& resolution, const astro::Date& startDate, const astro::Date& endDate, const astro::AstrodynamicsSystem& sys, const bool printProgress = false) :
        _resolution(resolution),
        _startDate(startDate),
        _endDate(endDate),
        _sys(&sys),
        _printProgress(printProgress)
    {
        create_date_vector();
    }

    ~AccessAnalyzer() = default;

    AccessArray find_internal_accesses(ViewerConstellation& constel, const bool clearPositionCache = true);

    AccessArray find_accesses(ViewerConstellation& constel, GroundArchitecture& grounds, const bool includeInternalAccesses = false);

    AccessArray find_accesses(ViewerConstellation& constel, Grid& grid, const bool includeInternalAccesses = false);

  private:
    Time _resolution;                       
    astro::Date _startDate;                 
    astro::Date _endDate;                   
    const astro::AstrodynamicsSystem* _sys; 
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

    RiseSetArray
        find_platform_to_ground_point_accesses(std::shared_ptr<astro::PayloadPlatform<Sensor>> platform, const std::shared_ptr<GroundPoint> groundPoint) const;

    RiseSetArray find_sensor_accesses(
        const std::vector<AccessInfo>& accessInfo,
        const Sensor& sensor1,
        const std::optional<Sensor> sensor2 = std::nullopt,
        const bool twoWay                   = false
    ) const;

    bool can_objects_ever_access_each_other(const std::size_t& id1, const std::size_t& id2, const bool atmosphereBlocks) const;

    ViewerRefVec cache_viewers(ViewerConstellation& constel);

    GroundStationRefVec cache_ground_points(GroundArchitecture& grounds);

    GroundPointRefVec cache_ground_points(Grid& grid);

    std::vector<AccessInfo> build_access_info(const std::size_t& id1, const std::size_t& id2) const;

    PairVec filter_impossible_pairs(const ViewerRefVec& viewers) const;

    template <typename T, typename U>
        requires requires(T t) { t.get_id(); } && requires(U u) { u.get_id(); }
    PairVec filter_impossible_pairs(const std::vector<std::shared_ptr<T>>& objects1, const std::vector<std::shared_ptr<U>>& objects2) const
    {
        if (_printProgress) { std::cout << "\tFiltering impossible sat-to-ground pairs..." << std::flush; }

        constexpr bool atmosphereBlocks = !(std::is_base_of_v<GroundPoint, T> || std::is_base_of_v<GroundPoint, U>);
        PairVec validPairs;
        for (std::size_t ii = 0; ii < objects1.size(); ++ii) {
            for (std::size_t jj = 0; jj < objects2.size(); ++jj) {
                if (can_objects_ever_access_each_other(objects1[ii]->get_id(), objects2[jj]->get_id(), atmosphereBlocks)) {
                    validPairs.emplace_back(ii, jj);
                }
            }
        }

        if (_printProgress) {
            std::cout << " kept " << validPairs.size() << " / " << (objects1.size() * objects2.size()) << " pairs ("
                      << (100.0 * validPairs.size() / (objects1.size() * objects2.size())) << "%)" << std::endl;
        }

        return validPairs;
    }
};

} // namespace trace
} // namespace astrea
```


