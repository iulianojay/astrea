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

using astro::Distance;
using astro::RadiusVector;

namespace accesslib {

Distance norm(const RadiusVector& r);

Distance norm(const RadiusVector& r) { return sqrt(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]); } // TODO: Move this

bool CircularFieldOfView::contains(const RadiusVector& boresight, const RadiusVector& target) const
{
    const Distance B = norm(boresight);
    const Distance T = norm(target);
    const auto bDotT = boresight[0] * target[0] + boresight[1] * target[1] + boresight[2] * target[2];
    return (acos(bDotT / (B * T)) <= halfConeAngle);
}


PolygonalFieldOfView::PolygonalFieldOfView(const astro::Angle& halfConeAngle, const int& nPoints)
{
    for (astro::Angle theta = 0.0 * astro::detail::angle_unit; theta < astro::TWO_PI; theta += (astro::TWO_PI / nPoints)) {
        points[theta] = halfConeAngle;
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