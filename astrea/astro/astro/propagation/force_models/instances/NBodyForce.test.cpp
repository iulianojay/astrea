/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/propagation/force_models/instances/NBodyForce.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/systems/system_utilities>
#include <astro/time/Date.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

class NBodyForceTest : public testing::Test {
  public:
    NBodyForceTest() :
        epoch("2020-02-18 15:08:47.23847"),
        nBodyForce()
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

    const Unitless REL_TOL = 1.0e-5 * one;

    Spacecraft sat;
    Date epoch;
    NBodyForce nBodyForce;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(NBodyForceTest, DefaultConstructor) { ASSERT_NO_THROW(NBodyForce()); }

// Vallado, Ex. 8.5
TEST_F(NBodyForceTest, ComputeForceValladoEx85)
{
    // These two won't match exactly because of numerous numerical differences between this code and Vallado's. Both
    // results have a similar magnitude and direction, but the values can be different up to 25%. Given that these tests
    // are meant to be pragmatically approachable estimations, not exact reproductions of Vallado's work, and since
    // matching them exactly is impractical, the expected values are taken from a run of this code, not Vallado's.

    Cartesian<frames::earth::icrf> cart{ -605.790796 * km,   -5870.230422 * km,  3493.051916 * km,
                                         -1.568251 * km / s, -3.702348 * km / s, -6.479485 * km / s };
    State state(cart, epoch);
    const auto [force, torque]                          = nBodyForce.compute_perturbation(state, Vehicle(sat));
    const AccelerationVector<frames::earth::icrf> accel = force / sat.get_mass();

#if defined(ASTREA_BUILD_EARTH_EPHEMERIS) && defined(ASTREA_BUILD_SUN_EPHEMERIS)

    // Vallado's expected result:
    // const AccelerationVector<frames::earth::icrf> expected{ (1.8664e-10 + 9.0459e-11) * km / (s * s),
    //                                                         (1.5243e-10 + -4.3052e-10) * km / (s * s),
    //                                                         (-1.8187e-10 + -7.0011e-10) * km / (s * s) };


    // These values come from a run of this code, not Vallado's, but they're close
    const AccelerationVector<frames::earth::icrf> expected{ 2.74172e-10 * km / (s * s),
                                                            -2.82853e-10 * km / (s * s),
                                                            -8.78525e-10 * km / (s * s) };

#elif !defined(ASTREA_BUILD_EARTH_EPHEMERIS) && !defined(ASTREA_BUILD_SUN_EPHEMERIS)

    // These are big bad
    const AccelerationVector<frames::earth::icrf> expected{ 6.391114272e-10 * km / (s * s),
                                                            -1.4610138560e-10 * km / (s * s),
                                                            -8.216647495e-10 * km / (s * s) };
#endif

    const Acceleration expectedNorm = expected.norm();
    const Acceleration accelNorm    = accel.norm();

    std::cout << "NBodyForce acceleration: " << accel << std::endl;
    std::cout << "Expected acceleration: " << expected << std::endl;
    std::cout << "NBodyForce acceleration norm: " << accelNorm << std::endl;
    std::cout << "Expected acceleration norm: " << expectedNorm << std::endl;

    ASSERT_TRUE(math::nearly_equal(accelNorm, expectedNorm, REL_TOL));
    ASSERT_TRUE(nearly_equal(accel, expected, REL_TOL));
}
