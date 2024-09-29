#include "FieldOfView.hpp"

#include <cmath>

FieldOfView::FieldOfView(const double& halfConeAngle, const int& nPoints) {
    for (double theta = 0.0; theta < 360.0; theta += (360.0/nPoints)) {
        points[theta] = halfConeAngle;
    }
}

FieldOfView::FieldOfView(const double& halfConeWidth, const double& halfConeHeight, const int& nPoints) {
    const double sinw = sin(halfConeWidth);
    const double sinh = sin(halfConeHeight);

    for (double theta = 0.0; theta < 360.0; theta += (360.0/nPoints)) {
        points[theta] = 0.0;
    }
}
