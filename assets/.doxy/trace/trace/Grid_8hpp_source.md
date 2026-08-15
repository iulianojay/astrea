

# File Grid.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**platforms**](dir_4dbda61db413396ce1d3b920f98dbf93.md) **>** [**ground**](dir_f1cb7431ef00eaab1d7c5caeb9788760.md) **>** [**Grid.hpp**](Grid_8hpp.md)

[Go to the documentation of this file](Grid_8hpp.md)


```C++

#pragma once

#include <algorithm>
#include <cmath>
#include <ranges>
#include <stdexcept>
#include <vector>

#include <mp-units/math.h>

#include <units/units.hpp>

#include <astro/systems/system_concepts.hpp>

#include <trace/platforms/ground/GroundPoint.hpp>
#include <trace/types/enums.hpp>
#include <trace/types/typedefs.hpp>

namespace astrea {
namespace trace {

template <astro::IsCelestialBody auto _body_>
class Grid {

    using Point = GroundPoint<_body_>;

  public:
    Grid() = default;

    Grid(const std::vector<Point>& groundPoints) :
        _groundPoints(groundPoints),
        _gridType(GridType::MANUAL)
    {
    }

    Grid(
        const LatRange& latRange,
        const LonRange& lonRange,
        const GridType& gridType,
        const Angle& spacing   = 5.0 * mp_units::si::unit_symbols::deg,
        const Unitless& weight = 0.0 * mp_units::one
    ) :
        _groundPoints(build_grid(latRange, lonRange, gridType, spacing, weight)),
        _gridType(gridType)
    {
    }

    virtual ~Grid() = default;

    GridType get_grid_type() const { return _gridType; }

    std::size_t size() const { return _groundPoints.size(); }

    using iterator = typename std::vector<Point>::iterator;

    using const_iterator = typename std::vector<Point>::const_iterator;

    iterator begin() { return _groundPoints.begin(); }

    iterator end() { return _groundPoints.end(); }

    const_iterator begin() const { return _groundPoints.begin(); }

    const_iterator end() const { return _groundPoints.end(); }

    const_iterator cbegin() const { return _groundPoints.begin(); }

    const_iterator cend() const { return _groundPoints.end(); }

    Point& operator[](std::size_t index) { return _groundPoints[index]; }

    const Point& operator[](std::size_t index) const { return _groundPoints[index]; }

    void push_back(const Point& point)
    {
        _gridType = GridType::MANUAL;
        _groundPoints.push_back(point);
    }

    void push_back(Point&& point)
    {
        _gridType = GridType::MANUAL;
        _groundPoints.push_back(std::move(point));
    }

    void emplace_back(const Point& point)
    {
        _gridType = GridType::MANUAL;
        _groundPoints.emplace_back(point);
    }

    void emplace_back(Point&& point)
    {
        _gridType = GridType::MANUAL;
        _groundPoints.emplace_back(std::move(point));
    }

    void clear() { _groundPoints.clear(); }

    void reserve(std::size_t n) { _groundPoints.reserve(n); }

    void resize(std::size_t n) { _groundPoints.resize(n); }

  private:
    std::vector<Point> _groundPoints; 
    GridType _gridType;               

    std::vector<Point>
        build_grid(const LatRange& latRange, const LonRange& lonRange, const GridType& gridType, const Angle& spacing, const Unitless& weight) const
    {
        switch (gridType) {
            case GridType::UNIFORM: return build_uniform_grid(latRange, lonRange, spacing);
            case GridType::EQUAL_AREA: return build_equal_area_grid(latRange, lonRange, spacing);
            case GridType::WEIGHTED_NS:
            case GridType::WEIGHTED_EW: return build_weighted_grid(latRange, lonRange, gridType, spacing, weight);
            case GridType::MANUAL:
                throw std::runtime_error("Manual grids can only be constructed from a vector of GroundPoints.");
            default: throw std::runtime_error("Unrecognized GridType.");
        }
    }

    std::vector<Point> build_uniform_grid(const LatRange& latRange, const LonRange& lonRange, const Angle& spacing) const
    {
        const std::vector<Angle> lats = create_uniformly_spaced_vector(latRange, spacing);
        const std::vector<Angle> lons = create_uniformly_spaced_vector(lonRange, spacing);

        std::vector<Point> grounds;
        for (const auto& [lat, lon] : std::views::cartesian_product(lats, lons)) {
            grounds.emplace_back(lat, lon);
        }
        return grounds;
    }

    std::vector<Point> build_equal_area_grid(const LatRange& latRange, const LonRange& lonRange, const Angle& spacing) const
    {
        throw std::runtime_error("Equal area grids have not been implemented yet.");
    }

    std::vector<Point>
        build_weighted_grid(const LatRange& latRange, const LonRange& lonRange, const GridType& gridType, const Angle& initialSpacing, const Unitless& weight) const
    {
        throw std::runtime_error("Weighted grids have not been implemented yet.");
    }

    std::vector<Angle> create_uniformly_spaced_vector(const std::pair<Angle, Angle>& range, const Angle& spacing) const
    {
        const auto& minAngle = std::min(range.first, range.second);
        const auto& maxAngle = std::max(range.first, range.second);

        const std::size_t nAngles =
            std::ceil((mp_units::abs(maxAngle - minAngle) / spacing).numerical_value_in(mp_units::one)) + 1;
        std::vector<Angle> angles(nAngles);
        std::generate(angles.begin(), angles.end(), [ii = 0, &minAngle, &maxAngle, &spacing]() mutable {
            return std::min(minAngle + (ii++) * spacing, maxAngle);
        });
        return angles;
    }
};

} // namespace trace
} // namespace astrea
```


