#pragma once

#include <numbers>
#include <unordered_map>

#include <math/utils.hpp>

#include <astro/constants/constants.hpp>
#include <astro/types/typedefs.hpp>


template <>
struct std::hash<astro::Angle> {
    std::size_t operator()(const astro::Angle& a) const
    {
        return (std::hash<double>()(a.numerical_value_ref_in(a.unit)));
    }
};

namespace accesslib {

class FieldOfView {
  protected:
    FieldOfView()  = default;
    ~FieldOfView() = default;

  public:
    virtual bool contains(const astro::RadiusVector& boresight, const astro::RadiusVector& target) const
    {
        return false;
    };
};


class CircularFieldOfView : public FieldOfView {
  public:
    CircularFieldOfView(const astro::Angle& halfConeAngle = astro::PI / 4.0) :
        halfConeAngle(halfConeAngle)
    {
    }
    ~CircularFieldOfView() = default;

    bool contains(const astro::RadiusVector& boresight, const astro::RadiusVector& target) const;

  private:
    astro::Angle halfConeAngle;
};


class PolygonalFieldOfView : public FieldOfView {
  public:
    PolygonalFieldOfView(const astro::Angle& halfConeAngle = astro::PI / 4.0, const int& nPoints = 72);
    PolygonalFieldOfView(const astro::Angle& halfConeWidth, const astro::Angle& halfConeHeight, const int& nPoints = 72);
    PolygonalFieldOfView(const std::unordered_map<astro::Angle, astro::Angle>& points) :
        points(points)
    {
    }
    ~PolygonalFieldOfView() = default;

    bool contains(const astro::RadiusVector& boresight, const astro::RadiusVector& target) const { return false; };

  private:
    std::unordered_map<astro::Angle, astro::Angle> points;
};

} // namespace accesslib