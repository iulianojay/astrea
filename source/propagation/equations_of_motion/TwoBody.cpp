#include "TwoBody.hpp"


OrbitalElements TwoBody::operator()(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft) const {

    if (state.get_set() != ElementSet::CARTESIAN) {
        throw std::runtime_error("The two-body dynamics evaluator requires that the incoming Orbital Element set is in Cartesian coordinates.");
    }

    // Extract
    const double& x = state[0];
    const double& y = state[1];
    const double& z = state[2];
    const double& vx = state[3];
    const double& vy = state[4];
    const double& vz = state[5];

    // Calculate required values for force model
    const double R = std::sqrt(x*x + y*y + z*z);

    // mu/R^3
    const double muOverRadiusCubed = mu/(R*R*R);

    // Derivative
    const OrbitalElements dsdt ({
        vx,
        vy,
        vz,
        (-muOverRadiusCubed*x),
        (-muOverRadiusCubed*y),
        (-muOverRadiusCubed*z)
    },
    ElementSet::CARTESIAN);

    return dsdt;
}