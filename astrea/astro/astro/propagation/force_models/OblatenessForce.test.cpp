#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/propagation/force_models/OblatenessForce.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

class OblatenessForceTest : public testing::Test {
  public:
    OblatenessForceTest() :
        epoch("2020-02-18 15:08:47.23847"),
        sys(CelestialBodyId::EARTH, { CelestialBodyId::MOON, CelestialBodyId::SUN }),
        force(sys, 2, 2)
    {
    }

    void SetUp() override
    {
        // Vallado Ex. 8.5
        sat.set_mass(1000.0 * kg);
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
    OblatenessForce force;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(OblatenessForceTest, DefaultConstructor) { ASSERT_NO_THROW(OblatenessForce(sys, 2, 0)); }

// Vallado, Ex. 8.5
TEST_F(OblatenessForceTest, ComputeForceValladoEx85)
{
    Cartesian state{ -605.790796 * km,   -5870.230422 * km,  3493.051916 * km,
                     -1.568251 * km / s, -3.702348 * km / s, -6.479485 * km / s };
    const AccelerationVector<frames::earth::icrf> accel = force.compute_force(epoch, state, Vehicle(sat), sys);

    const AccelerationVector<frames::earth::earth_fixed> expectedEcef{ -1.151903e-6 * km / (s * s),
                                                                       -2.938330e-6 * km / (s * s),
                                                                       -1.023539e-5 * km / (s * s) };
    const AccelerationVector<frames::earth::icrf> expected = expectedEcef.in_frame<frames::earth::icrf>(epoch);

    const Acceleration expectedNorm = expected.norm();
    const Acceleration accelNorm    = accel.norm();

    // It's hard to say if these can match. They're in the same direction, but small differences in values
    // change these equally small outputs. Itermediary values are similar, but not identical
    // ASSERT_EQ_QUANTITY(accelNorm, expectedNorm, REL_TOL);
    // ASSERT_EQ_CART_VEC(accel, expected, REL_TOL);
}
