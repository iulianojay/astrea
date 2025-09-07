#include <chrono>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include <astro/astro.hpp>

using mp_units::one;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

using namespace astrea;
using namespace astro;

class AtmosphericForceTest : public testing::Test {
  public:
    AtmosphericForceTest() :
        epoch("2020-02-18 15:08:47.23847"),
        sys("Earth", { "Earth", "Moon", "Sun" }, epoch),
        force()
    {
    }

    void SetUp() override
    {
        // Vallado Ex. 8.5
        sat.set_mass(100.0 * kg);
        sat.set_coefficient_of_drag(2.2 * one);
        sat.set_coefficient_of_lift(0.0 * one);
        sat.set_coefficient_of_reflectivity(1.0 * one);
        sat.set_ram_area(40 * m * m);
        sat.set_solar_area(40 * m * m);
        sat.set_lift_area(1.0 * m * m);
    }

    const Unitless REL_TOL = 1.0e-6 * one;

    Spacecraft sat;
    Date epoch;
    AstrodynamicsSystem sys;
    AtmosphericForce force;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(AtmosphericForceTest, DefaultConstructor) { ASSERT_NO_THROW(AtmosphericForce()); }

// // Vallado, Ex. 8.5
// TEST_F(AtmosphericForceTest, ComputeForceValladoEx85)
// {
//     Cartesian state{ -605.790796 * km,   -5870.230422 * km,  3493.051916 * km,
//                      -1.568251 * km / s, -3.702348 * km / s, -6.479485 * km / s };
//     const AccelerationVector accel = force.compute_force(epoch, state, Vehicle(sat), sys);

//     const AccelerationVector expectedEcef{ 1.4553e-9 * km / (s * s), 1.5354e-9 * km / (s * s), 3.2957e-9 * km / (s *
//     s) }; const AccelerationVector expected = ecef_to_eci(expectedEcef, epoch);

//     const Acceleration expectedNorm = sqrt(expected[0] * expected[0] + expected[1] * expected[1] + expected[2] * expected[2]);
//     const Acceleration accelNorm = sqrt(accel[0] * accel[0] + accel[1] * accel[1] + accel[2] * accel[2]);

//     ASSERT_EQ_CART_VEC(accel, expected, REL_TOL);
// }
