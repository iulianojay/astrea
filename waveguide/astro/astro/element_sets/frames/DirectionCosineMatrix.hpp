#pragma once

#include <astro/element_sets/CartesianVector.hpp>
#include <astro/element_sets/Frame.hpp>

namespace waveguide {
namespace astro {


class DirectionCosineMatrix {
  public:
    DirectionCosineMatrix()          = default;
    virtual ~DirectionCosineMatrix() = default;

    virtual RadiusVector operator*(const RadiusVector& vec) const             = 0;
    virtual VelocityVector operator*(const VelocityVector& vec) const         = 0;
    virtual AccelerationVector operator*(const AccelerationVector& vec) const = 0;
};

using DCM = DirectionCosineMatrix;


} // namespace astro
} // namespace waveguide