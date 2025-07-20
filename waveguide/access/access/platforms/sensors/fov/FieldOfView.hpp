#pragma once

#include <numbers>
#include <unordered_map>

#include <math/utils.hpp>
#include <units/units.hpp>


namespace waveguide {
namespace accesslib {

// TODO: Move this
Distance norm(const RadiusVector& r);
Angle calculate_angle_between_vectors(const RadiusVector& vector1, const RadiusVector& vector2);

class FieldOfView {
  public:
    FieldOfView()  = default;
    ~FieldOfView() = default;

    virtual bool contains(const RadiusVector& boresight, const RadiusVector& target) const = 0;
};


class CircularFieldOfView : public FieldOfView {
  public:
    CircularFieldOfView(const Angle& halfConeAngle = std::numbers::pi / 4.0 * mp_units::angular::unit_symbols::rad) :
        _halfConeAngle(halfConeAngle)
    {
    }
    ~CircularFieldOfView() = default;

    bool contains(const RadiusVector& boresight, const RadiusVector& target) const;

  private:
    Angle _halfConeAngle;
};


class PolygonalFieldOfView : public FieldOfView {
  public:
    PolygonalFieldOfView(const Angle& halfConeAngle = std::numbers::pi / 4.0 * mp_units::angular::unit_symbols::rad, const int& nPoints = 72);
    PolygonalFieldOfView(const Angle& halfConeWidth, const Angle& halfConeHeight, const int& nPoints = 72);
    PolygonalFieldOfView(const std::unordered_map<Angle, Angle>& points) :
        _points(points)
    {
    }
    ~PolygonalFieldOfView() = default;

    bool contains(const RadiusVector& boresight, const RadiusVector& target) const { return false; };

  private:
    std::unordered_map<Angle, Angle> _points;
};

} // namespace accesslib
} // namespace waveguide