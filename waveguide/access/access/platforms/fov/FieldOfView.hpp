#pragma once

#include <numbers>
#include <unordered_map>

#include <math/utils.hpp>

#include <astro/types/typedefs.hpp>
#include <astro/units/constants.hpp>


template <>
struct std::hash<astro::Angle> {
    std::size_t operator()(const astro::Angle& a) const
    {
        return (std::hash<double>()(a.numerical_value_ref_in(a.unit)));
    }
};

namespace accesslib {

class FieldOfView {
  public:
    FieldOfView()  = default;
    ~FieldOfView() = default;

    virtual bool contains(const astro::RadiusVector& boresight, const astro::RadiusVector& target) const = 0;
};


class CircularFieldOfView : public FieldOfView {
  public:
    CircularFieldOfView(const astro::Angle& halfConeAngle = std::numbers::pi / 4.0 * mp_units::angular::unit_symbols::rad) :
        _halfConeAngle(halfConeAngle)
    {
    }
    ~CircularFieldOfView() = default;

    bool contains(const astro::RadiusVector& boresight, const astro::RadiusVector& target) const;

  private:
    astro::Angle _halfConeAngle;
};


class PolygonalFieldOfView : public FieldOfView {
  public:
    PolygonalFieldOfView(const astro::Angle& halfConeAngle = std::numbers::pi / 4.0 * mp_units::angular::unit_symbols::rad, const int& nPoints = 72);
    PolygonalFieldOfView(const astro::Angle& halfConeWidth, const astro::Angle& halfConeHeight, const int& nPoints = 72);
    PolygonalFieldOfView(const std::unordered_map<astro::Angle, astro::Angle>& points) :
        _points(points)
    {
    }
    ~PolygonalFieldOfView() = default;

    bool contains(const astro::RadiusVector& boresight, const astro::RadiusVector& target) const { return false; };

  private:
    std::unordered_map<astro::Angle, astro::Angle> _points;
};

} // namespace accesslib