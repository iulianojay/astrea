#pragma once

#include <unordered_map>

#include "typedefs.hpp"

class FieldOfView {
public:
    FieldOfView(const double& halfConeAngle = 45, const int& nPoints = 72);
    FieldOfView(const double& halfConeWidth, const double& halfConeHeight, const int& nPoints = 72);
    FieldOfView(const std::unordered_map<double, double>& points) : points(points) {}
    ~FieldOfView();

    const bool contains(const basis_array& target) const;

private:
    std::unordered_map<double, double> points;
};
