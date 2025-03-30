#pragma once

#ifndef SWIG
#include <numbers>
#include <unordered_map>
#endif

#include <math/utils.hpp>

#include <astro/types/typedefs.hpp>

class FieldOfView {
  protected:
    FieldOfView()  = default;
    ~FieldOfView() = default;

  public:
    virtual bool contains(const BasisArray& boresight, const BasisArray& target) const { return false; };
};


class CircularFieldOfView : public FieldOfView {
  public:
    CircularFieldOfView(const double& halfConeAngle = std::numbers::pi / 4.0) :
        halfConeAngle(halfConeAngle)
    {
    }
    ~CircularFieldOfView() = default;

    bool contains(const BasisArray& boresight, const BasisArray& target) const;

  private:
    double halfConeAngle;
};


class PolygonalFieldOfView : public FieldOfView {
  public:
    PolygonalFieldOfView(const double& halfConeAngle = std::numbers::pi / 4.0, const int& nPoints = 72);
    PolygonalFieldOfView(const double& halfConeWidth, const double& halfConeHeight, const int& nPoints = 72);
    PolygonalFieldOfView(const std::unordered_map<double, double>& points) :
        points(points)
    {
    }
    ~PolygonalFieldOfView() = default;

    bool contains(const BasisArray& boresight, const BasisArray& target) const { return false; };

  private:
    std::unordered_map<double, double> points;
};