#pragma once

#include <vector>

#include <astro/types/typedefs.hpp>

#include <access/platforms/ground/GroundPoint.hpp>

namespace accesslib {

enum class GridType : astro::EnumType { UNIFORM, EQUAL_AREA, WEIGHTED_NS, WEIGHTED_EW, MANUAL };

using LatLon = std::pair<astro::Angle, astro::Angle>;

class Grid {
  public:
    Grid(const std::vector<GroundPoint>& groundStations) :
        _groundStations(groundStations),
        _gridType(GridType::MANUAL)
    {
    }
    Grid(
        const LatLon& corner1,
        const LatLon& corner4,
        const GridType& gridType,
        const astro::Angle& spacing   = 5.0 * mp_units::angular::unit_symbols::deg,
        const astro::Unitless& weight = 0.0 * mp_units::one
    ) :
        _groundStations(build_grid(corner1, corner4, gridType, spacing, weight)),
        _gridType(gridType)
    {
    }
    virtual ~Grid() = default;

    using iterator       = std::vector<GroundPoint>::iterator;
    using const_iterator = std::vector<GroundPoint>::const_iterator;

    iterator begin() { return _groundStations.begin(); }
    iterator end() { return _groundStations.end(); }
    const_iterator begin() const { return _groundStations.begin(); }
    const_iterator end() const { return _groundStations.end(); }
    const_iterator cbegin() const { return _groundStations.begin(); }
    const_iterator cend() const { return _groundStations.end(); }

  private:
    std::vector<GroundPoint> _groundStations;
    GridType _gridType;

    std::vector<GroundPoint>
        build_grid(const LatLon& corner1, const LatLon& corner4, const GridType& gridType, const astro::Angle& spacing, const astro::Unitless& weight) const;
    std::vector<GroundPoint> build_uniform_grid(const LatLon& corner1, const LatLon& corner4, const astro::Angle& spacing) const;
    std::vector<GroundPoint> build_equal_area_grid(const LatLon& corner1, const LatLon& corner4, const astro::Angle& spacing) const;
    std::vector<GroundPoint> build_weighted_grid(
        const LatLon& corner1,
        const LatLon& corner4,
        const GridType& gridType,
        const astro::Angle& initialSpacing,
        const astro::Unitless& weight
    ) const;

    std::vector<astro::Angle>
        create_uniformly_spaced_vector(const astro::Angle& first, const astro::Angle& second, const astro::Angle& spacing) const;
};

} // namespace accesslib