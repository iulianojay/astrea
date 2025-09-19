#include <iostream>

#include <units/units.hpp>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::min;
using mp_units::si::unit_symbols::s;

int main()
{
    // Astrea offers a few simple utilities to compute the Lambert solutions
    // through the static LambertSolver class. Future releases will include
    // more advanced Lambert solvers, including multi-revolution solutions,
    // distinctions between minimum energy and minimum time solutions, etc.

    AstrodynamicsSystem sys;
    RadiusVector<ECI> r0{ 15945.34 * km, 0.0 * km, 0.0 * km }, rf{ 12214.83899 * km, 10249.46731 * km, 0.0 * km };
    VelocityVector<ECI> v0{ 2.058913 * km / s, 2.915964 * km / s }, vf{ -3.451565 * km / s, 0.910314 * km / s };
    Time dt = 76.0 * min;

    // Known solution from Vallado, 5th Ed., Ex. 7-5
    std::cout << "Known initial state" << std::endl;
    std::cout << "  Position: " << r0 << std::endl;
    std::cout << "  Velocity: " << v0 << std::endl << std::endl;

    std::cout << "Known final state" << std::endl;
    std::cout << "  Position: " << rf << std::endl;
    std::cout << "  Velocity: " << vf << std::endl << std::endl;

    // Solve from position and velocity
    const Cartesian result = LambertSolver::solve({ r0, v0 }, dt, sys.get_mu());
    std::cout << "Final state from r0, v0" << std::endl;
    std::cout << "  Position: " << result.get_position() << std::endl;
    std::cout << "  Velocity: " << result.get_velocity() << std::endl << std::endl;

    // Solve from position and position
    const auto [res0, resf] = LambertSolver::solve(r0, rf, dt, sys.get_mu(), LambertSolver::OrbitDirection::PROGRADE);
    std::cout << "Initial and final velocity from r0, rf" << std::endl;
    std::cout << "  Initial Velocity: " << res0 << std::endl;
    std::cout << "  Final Velocity: " << resf << std::endl;

    return 0;
}