#include <access/platforms/fov/FieldOfView.hpp>

#include <cmath>
#include <stdexcept>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si/math.h>

#include <math/utils.hpp>

using namespace mp_units;
using namespace mp_units::angular;

using astro::Angle;
using astro::Distance;
using astro::RadiusVector;

namespace accesslib {

Distance norm(const RadiusVector& r) { return sqrt(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]); }

// TODO: Generalize, move
auto dot_product(const RadiusVector& r1, const RadiusVector& r2);

auto dot_product(const RadiusVector& r1, const RadiusVector& r2)
{
    return r1[0] * r2[0] + r1[1] * r2[1] + r1[2] * r2[2];
}

Angle calculate_angle_between_vectors(const RadiusVector& vector1, const RadiusVector& vector2)
{
    const Distance v1Mag = norm(vector1);
    const Distance v2Mag = norm(vector2);
    const auto v1DotV2   = dot_product(vector1, vector2);
    const auto ratio     = v1DotV2 / (v1Mag * v2Mag);
    if (ratio > 1.0 * one) {
        return 0.0 * astro::detail::angle_unit;
    } // catch rounding errors - TODO: Make this more intelligent
    return acos(ratio);
}

bool CircularFieldOfView::contains(const RadiusVector& boresight, const RadiusVector& target) const
{
    return (calculate_angle_between_vectors(boresight, target) <= _halfConeAngle);
}


PolygonalFieldOfView::PolygonalFieldOfView(const astro::Angle& halfConeAngle, const int& nPoints)
{
    for (astro::Angle theta = 0.0 * astro::detail::angle_unit; theta < astro::TWO_PI; theta += (astro::TWO_PI / nPoints)) {
        _points[theta] = halfConeAngle;
    }
}

PolygonalFieldOfView::PolygonalFieldOfView(const astro::Angle& halfConeWidth, const astro::Angle& halfConeHeight, const int& nPoints)
{

    throw std::logic_error("This function has not been properly updated and is not currently functional.");

    /*
    const astro::Angle sinw = sin(halfConeWidth);
    const astro::Angle sinh = sin(halfConeHeight);

    for (astro::Angle theta = 0.0; theta < astro::TWO_PI; theta += (astro::TWO_PI/nPoints)) {
        points[theta] = 0.0;
    }
    */
}

} // namespace accesslib