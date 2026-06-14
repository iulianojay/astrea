

# File LambertSolver.hpp

[**File List**](files.md) **>** [**analytic**](dir_0032edd3690e3836975e7dd677ed5fa8.md) **>** [**LambertSolver.hpp**](LambertSolver_8hpp.md)

[Go to the documentation of this file](LambertSolver_8hpp.md)


```C++

#pragma once

#include <math/operations.hpp>
#include <math/trig.hpp>
#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

class LambertSolver {
  public:
    LambertSolver() = delete;

    ~LambertSolver() = delete;

    enum class OrbitDirection : EnumType {
        PROGRADE,  
        RETROGRADE 
    };

    enum class SolutionType : EnumType {
        MINIMUM_ENERGY, 
        MINIMUM_TIME    
    };

    enum class MultiRevBranch : EnumType {
        LEFT, 
        RIGHT 
    };

    template <IsFrame auto _frame_>

    struct Solution {
        Time tof;                   
        VelocityVector<_frame_> v0; 
        VelocityVector<_frame_> vf; 
    };

    template <IsFrame auto _frame_>
    static Cartesian<_frame_> solve(const Cartesian<_frame_>& state0, const Time& dt, const GravParam& mu)
    {

        using namespace mp_units;
        using namespace mp_units::angular;
        using mp_units::angular::unit_symbols::rad;

        // Parse initial state
        const RadiusVector<_frame_> r0   = state0.get_position();
        const VelocityVector<_frame_> v0 = state0.get_velocity();

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
                const RadiusVector<_frame_> rf = f * r0 + g * v0;
                const Distance Rf              = rf.norm();

                // Find v
                const quantity fdot              = sqMU / (Rf * R0) * X * (z * Sz - 1.0 * one);
                const quantity gdot              = 1.0 * one - Xsq / Rf * Cz;
                const VelocityVector<_frame_> vf = fdot * r0 + gdot * v0;

                return Cartesian<_frame_>(rf, vf);
            }
            else if (it >= ITER_MAX) {
                throw std::runtime_error("LambertSolver: Maximum iterations reached");
            }
        }
    }

    template <IsFrame auto _frame_>
    static std::pair<VelocityVector<_frame_>, VelocityVector<_frame_>>
        solve(const RadiusVector<_frame_>& r0, const RadiusVector<_frame_>& rf, const Time& dt, const GravParam& mu, const OrbitDirection& direction)
    {

        using namespace mp_units;
        using namespace mp_units::angular;
        using mp_units::angular::unit_symbols::rad;
        using mp_units::si::unit_symbols::km;

        // Constants
        const Distance R0   = r0.norm();
        const Distance Rf   = rf.norm();
        const quantity sqMU = sqrt(mu);

        static constexpr Angle twoPi = 2.0 * std::numbers::pi * rad;

        // Change in TA
        Angle dtheta = acos((r0.dot(rf) / (R0 * Rf)));
        if (r0[0] * rf[1] - r0[1] * rf[0] >= 0.0 * pow<2>(km)) {
            if (direction == OrbitDirection::RETROGRADE) { dtheta = twoPi - dtheta; }
        }
        else {
            if (direction == OrbitDirection::PROGRADE) { dtheta = twoPi - dtheta; }
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
                const VelocityVector<_frame_> v0 = divG * (rf - f * r0);
                const VelocityVector<_frame_> vf = divG * (gdot * rf - r0);

                return { v0, vf };
            }
            else if (it >= ITER_MAX) {
                throw std::runtime_error("LambertSolver: Maximum iterations reached");
            }
        }
    }

    template <IsFrame auto _frame_>
    static Solution<_frame_>
        solve(const RadiusVector<_frame_>& r0, const RadiusVector<_frame_>& rf, const GravParam& mu, const OrbitDirection& direction, const SolutionType& solutionType)
    {

        using namespace mp_units;
        using namespace mp_units::angular;
        using mp_units::angular::unit_symbols::rad;
        using mp_units::si::unit_symbols::km;

        const Distance R0   = r0.norm();
        const Distance Rf   = rf.norm();
        const quantity sqMU = sqrt(mu);

        static constexpr Angle onePi = std::numbers::pi * rad;
        static constexpr Angle twoPi = 2.0 * std::numbers::pi * rad;

        // Change in TA (same convention as the r & r solver)
        Angle dtheta = acos((r0.dot(rf) / (R0 * Rf)));
        if (r0[0] * rf[1] - r0[1] * rf[0] >= 0.0 * pow<2>(km)) {
            if (direction == OrbitDirection::RETROGRADE) { dtheta = twoPi - dtheta; }
        }
        else {
            if (direction == OrbitDirection::PROGRADE) { dtheta = twoPi - dtheta; }
        }

        const Distance A = sin(dtheta) * sqrt(R0 * Rf / (1.0 * one - cos(dtheta)));

        if (solutionType == SolutionType::MINIMUM_TIME) {
            // Parabolic trajectory (z = 0): C(0) = 1/2, S(0) = 1/6 — minimises time of flight
            const Distance y = R0 + Rf - A * sqrt(2.0 * one);

            if (y <= 0.0 * km) {
                throw std::runtime_error(
                    "LambertSolver: parabolic (minimum-time) trajectory is geometrically "
                    "impossible "
                    "for these endpoints"
                );
            }

            const Time tof      = (pow<3, 2>(y / (0.5 * one)) * (1.0 / 6.0 * one) + A * sqrt(y)) / sqMU;
            const quantity f    = 1.0 * one - y / R0;
            const quantity g    = A * sqrt(y) / sqMU;
            const quantity gdot = 1.0 * one - y / Rf;
            const quantity divG = 1.0 / g;

            const VelocityVector<_frame_> v0Result = divG * (rf - f * r0);
            const VelocityVector<_frame_> vfResult = divG * (gdot * rf - r0);

            return { tof, v0Result, vfResult };
        }

        // MINIMUM_ENERGY: minimum semi-major axis (a = s/2) elliptic transfer
        // Chord and semi-perimeter
        const Distance c = (rf - r0).norm();
        const Distance s = (R0 + Rf + c) * 0.5;

        // β₀ = 2·arcsin(√((s−c)/s))
        const Unitless scRatio = (s - c) / s;
        const Angle beta0      = 2.0 * asin(sqrt(scRatio));

        // Treat angle values as pure scalars (radians) for Lambert's theorem
        const Unitless beta0U   = beta0 / (1.0 * rad);
        const Unitless sinBeta0 = sin(beta0);

        // t_me = √(s³/8μ) · (π ∓ β₀ ± sin(β₀))
        const Time baseTime = sqrt(pow<3>(s) / (8.0 * mu));
        const Time tof = (dtheta <= onePi) ? baseTime * (onePi / isq_angle::cotes_angle - beta0U + sinBeta0) : // short arc
                             baseTime * (onePi / isq_angle::cotes_angle + beta0U - sinBeta0); // long arc

        // Delegate to the existing r & r solver using the computed minimum-energy time
        const auto [v0Result, vfResult] = LambertSolver::solve(r0, rf, tof, mu, direction);

        return { tof, v0Result, vfResult };
    }


    template <IsFrame auto _frame_>
    static std::pair<VelocityVector<_frame_>, VelocityVector<_frame_>> solve(
        const RadiusVector<_frame_>& r0,
        const RadiusVector<_frame_>& rf,
        const Time& dt,
        const GravParam& mu,
        const OrbitDirection& direction,
        unsigned N,
        const MultiRevBranch& branch
    )
    {

        using namespace mp_units;
        using namespace mp_units::angular;
        using mp_units::angular::unit_symbols::rad;
        using mp_units::si::unit_symbols::km;

        if (N == 0) { throw std::invalid_argument("LambertSolver: N must be >= 1 for multi-rev solve"); }

        const Distance R0 = r0.norm();
        const Distance Rf = rf.norm();

        static constexpr Angle twoPi       = 2.0 * std::numbers::pi * rad;
        static constexpr Unitless itTol    = 1e-12 * one;
        static constexpr Unitless clampTol = 1e-10 * one;

        // True-anomaly change (same sign convention as single-rev solvers)
        Angle dtheta = acos((r0.dot(rf) / (R0 * Rf)));
        if (r0[0] * rf[1] - r0[1] * rf[0] >= 0.0 * pow<2>(km)) {
            if (direction == OrbitDirection::RETROGRADE) { dtheta = twoPi - dtheta; }
        }
        else {
            if (direction == OrbitDirection::PROGRADE) { dtheta = twoPi - dtheta; }
        }

        // Gooding geometry parameters (all dimensionless after normalisation)
        const Distance n        = (R0 + Rf) * 0.5;
        const Unitless lambda   = sqrt(R0 * Rf) * cos(dtheta * 0.5) / n;
        const Unitless tau      = sqrt(2.0 * mu / pow<3>(n)) * dt * 0.5;
        const Unitless lambdaSq = lambda * lambda;

        // Normalised TOF and its first two derivatives w.r.t. x (Gooding 1990, Eqs 16–18)
        const Unitless NN = static_cast<double>(N) * one;

        auto T = [&](Unitless x) -> Unitless {
            const Unitless sig = sqrt(1.0 * one - lambdaSq * x * x);
            return (NN * std::numbers::pi + atan2(sig, x) / isq_angle::cotes_angle - lambda * x * sig) / (1.0 - x * x);
        };

        auto dT = [&](Unitless x, Unitless Tx) -> Unitless {
            const Unitless sig  = sqrt(1.0 * one - lambdaSq * x * x);
            const Unitless sig3 = sig * sig * sig;
            return (3.0 * x * Tx - lambda * (lambdaSq * x * x + 2.0 * sig * sig) / sig3) / (1.0 - x * x);
        };

        auto d2T = [&](Unitless x, Unitless Tx, Unitless dTx) -> Unitless {
            const Unitless sig2 = 1.0 * one - lambdaSq * x * x;
            return (5.0 * x * dTx + (3.0 - 4.0 * lambdaSq * x * x / sig2) * Tx) / (1.0 - x * x);
        };

        // Find x* = argmin T(x) via Newton iterations on dT/dx = 0
        Unitless xStar = 0.0;
        for (unsigned k = 0; k < 50; ++k) {
            const Unitless Tv   = T(xStar);
            const Unitless dTv  = dT(xStar, Tv);
            const Unitless d2Tv = d2T(xStar, Tv, dTv);
            if (abs(d2Tv) < 1e-30 * one) { break; }
            const Unitless step = -dTv / d2Tv;
            xStar               = math::clamp(xStar + step, -1.0 * one + clampTol, 1.0 * one - clampTol);
            if (abs(step) < itTol) { break; }
        }

        if (tau < T(xStar)) {
            throw std::runtime_error("LambertSolver: time of flight is below the multi-rev minimum for N=" + std::to_string(N));
        }

        // Initial guess on chosen branch
        const Unitless x0 = (branch == MultiRevBranch::LEFT) ? xStar - 0.5 * (1.0 + xStar) * one // midpoint of (−1, x*)
                                                               :
                                                               xStar + 0.5 * (1.0 - xStar) * one; // midpoint of (x*, 1)

        // Halley iterations on F(x) = T(x) − τ = 0
        Unitless x  = math::clamp(x0, (-1.0 + clampTol) * one, (1.0 - clampTol) * one);
        unsigned it = 0;
        while (true) {
            // Halley: δ = −F / (dT − F·d²T / (2·dT))
            const Unitless Tv   = T(x);
            const Unitless dTv  = dT(x, Tv);
            const Unitless F    = Tv - tau;
            const Unitless step = -F / (dTv - 0.5 * F * d2T(x, Tv, dTv) / dTv);

            x = math::clamp(x + step, (-1.0 + clampTol) * one, (1.0 - clampTol) * one);

            ++it;
            if (abs(step) < itTol) { break; }
            if (it >= ITER_MAX) {
                throw std::runtime_error("LambertSolver: multi-rev solver maximum iterations reached");
            }
        }

        // Recover semi-latus rectum from x
        const Unitless sig2 = 1.0 * one - lambdaSq * x * x;
        const Distance p    = n * (1.0 - lambdaSq) * (1.0 - x * x) / sig2;

        // f-and-g coefficients  (Bate-Mueller-White, Eq. 5.4-4)
        const Unitless f    = 1.0 * one - p / R0;
        const Unitless gdot = 1.0 * one - p / Rf;
        const Time g        = R0 * Rf * sin(dtheta) / sqrt(mu * p);

        const VelocityVector<_frame_> v0Ret = (rf - f * r0) / g;
        const VelocityVector<_frame_> vfRet = (gdot * rf - r0) / g;

        return { v0Ret, vfRet };
    }

  private:
    static constexpr unsigned ITER_MAX = 1e4;                     
    static constexpr Unitless TOL      = 1.0e-12 * mp_units::one; 

    static std::pair<Unitless, Unitless> evaluate_stumpff(const Unitless& z);
};

} // namespace astro
} // namespace astrea
```


