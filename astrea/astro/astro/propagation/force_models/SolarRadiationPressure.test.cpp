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

class SolarRadiationPressureTest : public testing::Test {
  public:
    SolarRadiationPressureTest() :
        epoch("2020-02-18 15:08:47.23847"),
        sys("Earth", { "Earth", "Moon", "Sun" }, epoch)
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
    SolarRadiationPressure force;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(SolarRadiationPressureTest, DefaultConstructor) { ASSERT_NO_THROW(SolarRadiationPressure()); }

// // Vallado, Ex. 8.5
// TEST_F(SolarRadiationPressureTest, ComputeForceValladoEx85)
// {
//     Cartesian state{ -605.790796 * km,   -5870.230422 * km,  3493.051916 * km,
//                      -1.568251 * km / s, -3.702348 * km / s, -6.479485 * km / s };
//     const AccelerationVector accel = force.compute_force(epoch, state, Vehicle(sat), sys);

//     const AccelerationVector expected{ -1.8791e-10 * km / (s * s), 1.0298e-10 * km / (s * s), 4.4651e-11 * km / (s * s) };

//     // These two won't match exactly cause Vallado uses 4.56e-6 as average SRP and we use 4.556485540406757e-6 scaled to
//     // the ratio of 1 AU and the distance from the sat to the Sun
//     ASSERT_EQ_CART_VEC(accel, expected, REL_TOL);
// }
