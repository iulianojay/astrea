#include <astro/propagation/equations_of_motion/CowellsMethod.hpp>

OrbitalElements CowellsMethod::operator()(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const
{

    if (state.get_set() != ElementSet::CARTESIAN) {
        throw std::runtime_error("The Cowell's Method dynamics evaluator requires that the incoming Orbital Element "
                                 "set is in Cartesian coordinates.");
    }

    // Extract
    const double& x  = state[0];
    const double& y  = state[1];
    const double& z  = state[2];
    const double& vx = state[3];
    const double& vy = state[4];
    const double& vz = state[5];

    // Calculate required values for force model
    const double R = std::sqrt(x * x + y * y + z * z); // radius magnitude

    // mu/R^3
    const double muOverRadiusCubed = mu / (R * R * R);

    // Run find functions for force model
    auto julianDate        = vehicle.get_epoch().julian_day() + time.count<days>();
    basis_array accelPerts = forces.compute_forces(julianDate, state, vehicle, system);

    // Derivative
    const OrbitalElements dsdt(
        { vx, vy, vz, -muOverRadiusCubed * x + accelPerts[0], -muOverRadiusCubed * y + accelPerts[1], -muOverRadiusCubed * z + accelPerts[2] },
        ElementSet::CARTESIAN);

    return dsdt;
}