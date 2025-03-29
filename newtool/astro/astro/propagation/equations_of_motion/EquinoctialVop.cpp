#include <astro/propagation/equations_of_motion/EquinoctialVop.hpp>

#include <math/utils.hpp>

OrbitalElements EquinoctialVop::operator()(const Time& time, const OrbitalElements& state, const Vehicle& vehicle) const
{

    if (state.get_set() != ElementSet::EQUINOCTIAL) {
        throw std::runtime_error("The Mean Equinoctial dynamics evaluator requires that the incoming Orbital Element "
                                 "set is in EQUINOCTIAL coordinates.");
    }

    // Extract
    const double& p = state[0];
    const double& f = state[1];
    const double& g = state[2];
    const double& h = state[3];
    const double& k = state[4];
    const double& L = state[5];

    // conversions Modified Equinoctial Elements to KEPLERIANs
    const auto coesState = conversions::convert(state, ElementSet::EQUINOCTIAL, ElementSet::KEPLERIAN, system);

    // conversions KEPLERIANs to r and v
    const auto cartesianState = conversions::convert(coesState, ElementSet::KEPLERIAN, ElementSet::CARTESIAN, system);

    const double& x = cartesianState[0];
    const double& y = cartesianState[1];
    const double& z = cartesianState[2];
    const double R  = std::sqrt(x * x + y * y + z * z);

    const double& vx = cartesianState[3];
    const double& vy = cartesianState[4];
    const double& vz = cartesianState[5];

    // Define perturbation vectors relative to the satellites SNC body frame
    /*
       R -> perturbing accel along radius vector outward
       N -> perturbing accel normal to orbital plane in direction of angular momentum vector
       T -> perturbing accel perpendicular to radius in direction of motion
    */
    const double Rhat[3] = { x / R, y / R, z / R };

    const double Nhat[3] = { (y * vz - z * vy) / h, (z * vx - x * vz) / h, (x * vy - y * vx) / h };

    const double Tv[3]  = { Nhat[1] * Rhat[2] - Nhat[2] * Rhat[1],
                            Nhat[2] * Rhat[0] - Nhat[0] * Rhat[2],
                            Nhat[0] * Rhat[1] - Nhat[1] * Rhat[0] };
    const double normTv = std::sqrt(Tv[0] * Tv[0] + Tv[1] * Tv[1] + Tv[2] * Tv[2]);

    const double That[3] = { Tv[0] / normTv, Tv[1] / normTv, Tv[2] / normTv };

    // Function for finding accel caused by perturbations
    auto julianDate       = vehicle.get_epoch().julian_day() + time.count<days>();
    BasisArray accelPerts = forces.compute_forces(julianDate, cartesianState, vehicle, system);

    // Calculate R, N, and T
    const double radialPert     = accelPerts[0] * Rhat[0] + accelPerts[1] * Rhat[1] + accelPerts[2] * Rhat[2];
    const double normalPert     = accelPerts[0] * Nhat[0] + accelPerts[1] * Nhat[1] + accelPerts[2] * Nhat[2];
    const double tangentialPert = accelPerts[0] * That[0] + accelPerts[1] * That[1] + accelPerts[2] * That[2];

    // Variables precalculated for speed
    const double cosL = math::cos(L);
    const double sinL = math::sin(L);

    const double tempA = std::sqrt(p / mu);
    const double tempB = 1.0 + f * math::cos(L) + g * math::sin(L);
    const double s_2   = 1.0 + h * h + k * k;

    const double tempC = (h * sinL - k * cosL) / tempB;
    const double tempD = tempA * s_2 / (2 * tempB);

    // Derivative functions
    const OrbitalElements dsdt(
        {
            2 * p / tempB * tempA * tangentialPert, // dpdt
            tempA * (radialPert * sinL + ((tempB + 1) * cosL + f) / tempB * tangentialPert - g * tempC * normalPert), // dfdt
            tempA * (-radialPert * cosL + ((tempB + 1) * sinL + g) / tempB * tangentialPert + f * tempC * normalPert), // dgdt
            tempD * cosL * normalPert,                                               // dhdt
            tempD * sinL * normalPert,                                               // dkdt
            std::sqrt(mu * p) * tempB * tempB / (p * p) + tempA * tempC * normalPert // dLdt
        },
        ElementSet::EQUINOCTIAL
    );

    return dsdt;
}