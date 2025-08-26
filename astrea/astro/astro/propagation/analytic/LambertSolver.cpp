#include <astro/propagation/analytic/LambertSolver.hpp>

#include <numbers>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>

#include <math/trig.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;
using namespace mp_units::angular;
using mp_units::angular::unit_symbols::rad;

// r and v Lambert solver
Cartesian LambertSolver::solve(const Cartesian& state0, const Time& dt, const GravParam& mu)
{
    // Parse initial state
    const RadiusVector<ECI> r0   = state0.get_position();
    const VelocityVector<ECI> v0 = state0.get_velocity();

    // Constants
    const Distance R0 = r0.norm();
    const Velocity V0 = v0.norm();

    const quantity sqMU  = sqrt(mu);                // km^1.5/s
    const quantity termA = r0.dot(v0) / sqMU;       // km^0.5
    const quantity alpha = 2.0 / R0 - V0 * V0 / mu; // 1/km

    // Find X
    quantity Xn = sqMU * dt * abs(alpha); // km^0.5
    quantity X  = Xn;

    // Universal Variable loop
    unsigned it  = 0;
    Unitless err = 1.0 * one;
    while (true) {
        // Reset
        X = Xn;

        // Precalculate
        const Distance Xsq = X * X;
        const Unitless z   = Xsq * alpha;

        // Evaluate Stumpff Functions
        const auto [Cz, Sz] = evaluate_stumpff(z);

        // Newton Functions
        const quantity F  = termA * Xsq * Cz + (1.0 * one - alpha * R0) * X * Xsq * Sz + R0 * X - sqMU * dt;
        const quantity dF = termA * X * (1.0 * one - alpha * Xsq * Sz) + (1.0 * one - alpha * R0) * Xsq * Cz + R0;

        // Step
        Xn = X - F / dF;

        err = abs((Xn - X) / X);
        ++it;

        if (err <= TOL) {
            const quantity f = 1.0 * one - Xsq / R0 * Cz;
            const quantity g = dt - 1.0 * one / sqMU * Xsq * X * Sz;

            // Find r
            const RadiusVector<ECI> rf = f * r0 + g * v0;
            const Distance Rf          = rf.norm();

            // Find v
            const quantity fdot          = sqMU / (Rf * R0) * X * (z * Sz - 1.0 * one);
            const quantity gdot          = 1.0 * one - Xsq / Rf * Cz;
            const VelocityVector<ECI> vf = fdot * r0 + gdot * v0;

            return Cartesian(rf, vf);
        }
        else if (it >= ITER_MAX) {
            throw std::runtime_error("LambertSolver: Maximum iterations reached");
        }
    }
}

// r and r Lambert solver
std::pair<VelocityVector<ECI>, VelocityVector<ECI>>
    LambertSolver::solve(const RadiusVector<ECI>& r0, const RadiusVector<ECI>& rf, const Time& dt, const GravParam& mu, const LambertSolver::OrbitDirection& direction)
{
    // Constants
    const Distance R0   = r0.norm();
    const Distance Rf   = rf.norm();
    const quantity sqMU = sqrt(mu);

    // Change in TA
    Angle dtheta = acos((r0.dot(rf) / (R0 * Rf)));
    if (r0[0] * rf[1] - r0[1] * rf[0] >= 0.0 * pow<2>(astrea::detail::distance_unit)) {
        if (direction == OrbitDirection::RETROGRADE) { dtheta = 2.0 * std::numbers::pi * rad - dtheta; }
    }
    else {
        if (direction == OrbitDirection::PROGRADE) { dtheta = 2.0 * std::numbers::pi * rad - dtheta; }
    }

    const Distance A = sin(dtheta) * sqrt(R0 * Rf / (1.0 * one - cos(dtheta)));

    // Find z
    Unitless zn  = 0.0 * one;
    unsigned it  = 0;
    Unitless err = 1.0 * one;
    while (true) {
        // Reset
        const Unitless z = zn;

        // Evaluate Stumpff Functions
        const auto [Cz, Sz] = evaluate_stumpff(z);
        const quantity y    = R0 + Rf + A * (z * Sz - 1.0 * one) / sqrt(Cz);

        // Newton Functions
        const quantity F = pow<3, 2>(y / Cz) * Sz + A * sqrt(y) - sqMU * dt;
        const quantity dF =
            (z == 0.0 * one) ?
                sqrt(2.0 * one) / 40.0 * pow<3, 2>(y) + A / 8 * (sqrt(y) + A * sqrt(1.0 / (2.0 * y))) :
                (pow<3, 2>(y / Cz) * (1.0 / (2.0 * z) * (Cz - 3.0 * Sz / (2.0 * Cz)) + 3.0 * Sz * Sz / (4.0 * Cz)) +
                 A / 8.0 * (3.0 * Sz / Cz * sqrt(y) + A * sqrt(Cz / y)));

        // Step
        zn = z - F / dF;

        err = (z == 0.0 * one) ? abs(zn - z) : abs((zn - z) / z);
        ++it;

        if (err <= TOL) {
            // f and g functions
            const quantity f    = 1.0 * one - y / R0;
            const quantity g    = A * sqrt(y) / sqMU;
            const quantity gdot = 1.0 * one - y / Rf;
            const quantity divG = 1.0 / g;

            // v1 and v2
            const VelocityVector<ECI> v0 = divG * (rf - f * r0);
            const VelocityVector<ECI> vf = divG * (gdot * rf - r0);

            return { v0, vf };
        }
        else if (it >= ITER_MAX) {
            throw std::runtime_error("LambertSolver: Maximum iterations reached");
        }
    }
}

std::pair<Unitless, Unitless> LambertSolver::evaluate_stumpff(const Unitless& z)
{
    using namespace math;
    if (z > 0.0 * one) {
        const Unitless sqz = sqrt(z);
        const Unitless Cz  = (1.0 - cos(sqz * isq_angle::cotes_angle)) / z;
        const Unitless Sz  = (sqz - sin(sqz * isq_angle::cotes_angle)) / (sqz * sqz * sqz);
        return { Cz, Sz };
    }
    else if (z < 0.0 * one) {
        const Unitless sqnz = sqrt(-z);
        const Unitless Cz   = (1.0 - cosh(sqnz * isq_angle::cotes_angle)) / z;
        const Unitless Sz   = (sinh(sqnz * isq_angle::cotes_angle) - sqnz) / (sqnz * sqnz * sqnz);
        return { Cz, Sz };
    }

    const Unitless Cz = 0.5 * one;
    const Unitless Sz = 1.0 / 6.0 * one;
    return { Cz, Sz };
}

} // namespace astro
} // namespace astrea