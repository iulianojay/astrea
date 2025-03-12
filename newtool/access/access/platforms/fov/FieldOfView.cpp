#include <access/platforms/fov/FieldOfView.hpp>

#include <cmath>
#include <stdexcept>

#include <math/utils.hpp>


bool CircularFieldOfView::contains(const basis_array& boresight, const basis_array& target) const {
    const double B = math::normalize(boresight, 2);
    const double T = math::normalize(target, 2);
    const double bDotT = boresight[0]*target[0] + boresight[1]*target[1] + boresight[2]*target[2];
    return (acos(bDotT/(B*T)) <= halfConeAngle);
}


PolygonalFieldOfView::PolygonalFieldOfView(const double& halfConeAngle, const int& nPoints) {
    for (double theta = 0.0; theta < std::numbers::pi*2.0; theta += (std::numbers::pi*2.0/nPoints)) {
        points[theta] = halfConeAngle;
    }
}

PolygonalFieldOfView::PolygonalFieldOfView(const double& halfConeWidth, const double& halfConeHeight, const int& nPoints) {

    throw std::logic_error("This function has not been properly updated and is not currently functional.");

    /*
    const double sinw = math::sin(halfConeWidth);
    const double sinh = math::sin(halfConeHeight);

    for (double theta = 0.0; theta < std::numbers::pi*2.0; theta += (std::numbers::pi*2.0/nPoints)) {
        points[theta] = 0.0;
    }
    */
}
