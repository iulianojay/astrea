

# File Grid.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**platforms**](dir_4dbda61db413396ce1d3b920f98dbf93.md) **>** [**ground**](dir_f1cb7431ef00eaab1d7c5caeb9788760.md) **>** [**Grid.hpp**](Grid_8hpp.md)

[Go to the documentation of this file](Grid_8hpp.md)


```C++

#pragma once

#include <vector>

#include <units/units.hpp>

#include <astro/systems/CelestialBody.hpp>

#include <trace/platforms/ground/GroundPoint.hpp>
#include <trace/types/enums.hpp>
#include <trace/types/typedefs.hpp>

namespace astrea {
namespace trace {

class Grid {
  public:
    Grid() = default;

    Grid(const std::vector<GroundPoint>& groundPoints) :
        _groundPoints(groundPoints),
        _gridType(GridType::MANUAL)
    {
    }

    Grid(
        const astro::CelestialBody* parent,
        const LatLon& corner1,
        const LatLon& corner4,
        const GridType& gridType,
        const Angle& spacing   = 5.0 * mp_units::angular::unit_symbols::deg,
        const Unitless& weight = 0.0 * mp_units::one
    ) :
        _parent(parent),
        _groundPoints(build_grid(corner1, corner4, gridType, spacing, weight)),
        _gridType(gridType)
    {
    }

    virtual ~Grid() = default;

    GridType get_grid_type() const { return _gridType; }

    const astro::CelestialBody* get_parent() const { return _parent; }

    std::size_t size() const { return _groundPoints.size(); }

    using iterator = std::vector<GroundPoint>::iterator;

    using const_iterator = std::vector<GroundPoint>::const_iterator;

    iterator begin() { return _groundPoints.begin(); }

    iterator end() { return _groundPoints.end(); }

    const_iterator begin() const { return _groundPoints.begin(); }

    const_iterator end() const { return _groundPoints.end(); }

    const_iterator cbegin() const { return _groundPoints.begin(); }

    const_iterator cend() const { return _groundPoints.end(); }

    GroundPoint& operator[](const std::size_t index) { return _groundPoints[index]; }

    const GroundPoint& operator[](const std::size_t index) const { return _groundPoints[index]; }

  private:
    const astro::CelestialBody* _parent;    
    std::vector<GroundPoint> _groundPoints; 
    GridType _gridType;                     

    std::vector<GroundPoint>
        build_grid(const LatLon& corner1, const LatLon& corner4, const GridType& gridType, const Angle& spacing, const Unitless& weight) const;

    std::vector<GroundPoint> build_uniform_grid(const LatLon& corner1, const LatLon& corner4, const Angle& spacing) const;

    std::vector<GroundPoint> build_equal_area_grid(const LatLon& corner1, const LatLon& corner4, const Angle& spacing) const;

    std::vector<GroundPoint>
        build_weighted_grid(const LatLon& corner1, const LatLon& corner4, const GridType& gridType, const Angle& initialSpacing, const Unitless& weight) const;

    std::vector<Angle> create_uniformly_spaced_vector(const Angle& first, const Angle& second, const Angle& spacing) const;
};

} // namespace trace
} // namespace astrea
```


