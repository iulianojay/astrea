#include <trace/platforms/sensors/fov/FieldOfView.hpp>

#include <cmath>
#include <stdexcept>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si/math.h>

#include <astro/state/CartesianVector.hpp>
#include <astro/state/frames/frames.hpp>

namespace astrea {
namespace trace {

using namespace mp_units;
using namespace mp_units::angular;
using EciRadiusVec = astro::RadiusVector<astro::frames::earth::icrf>;

Angle calculate_angle_between_vectors(const EciRadiusVec& vector1, const EciRadiusVec& vector2)
{
    const Distance v1Mag = vector1.norm();
    const Distance v2Mag = vector2.norm();
    const auto v1DotV2   = vector1.dot(vector2);
    const auto ratio     = v1DotV2 / (v1Mag * v2Mag);
    if (ratio > 1.0 * one) {
        return 0.0 * astrea::detail::angle_unit;
    } // catch rounding errors - TODO: Make this more intelligent
    return acos(ratio);
}

bool CircularFieldOfView::contains(const EciRadiusVec& boresight, const EciRadiusVec& target) const
{
    return (calculate_angle_between_vectors(boresight, target) <= _halfConeAngle);
}


PolygonalFieldOfView::PolygonalFieldOfView(const Angle& halfConeAngle, const int& nPoints)
{
    for (Angle theta = 0.0 * astrea::detail::angle_unit; theta < TWO_PI; theta += (TWO_PI / nPoints)) {
        _points[theta] = halfConeAngle;
    }
}

PolygonalFieldOfView::PolygonalFieldOfView(const Angle& halfConeWidth, const Angle& halfConeHeight, const int& nPoints)
{

    throw std::logic_error("This function has not been properly updated and is not currently functional.");

    /*
    const Angle sinw = sin(halfConeWidth);
    const Angle sinh = sin(halfConeHeight);

    for (Angle theta = 0.0; theta < TWO_PI; theta += (TWO_PI/nPoints)) {
        points[theta] = 0.0;
    }
    */
}

} // namespace trace
} // namespace astrea