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
#include <astro/propagation/force_models/instances/OblatenessForce.hpp>
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

class OblatenessForceTest : public testing::Test {
  public:
    OblatenessForceTest() :
        epoch("2020-02-18 15:08:47.23847"),
        sys(CelestialBodyId::EARTH, { CelestialBodyId::MOON, CelestialBodyId::SUN }),
        oblatenessForce(sys, 2, 2)
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

    const Unitless REL_TOL = 1.0e-1 * one;

    Spacecraft sat;
    Date epoch;
    OblatenessForce oblatenessForce;
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
    Cartesian<frames::earth::icrf> cart{ -605.790796 * km,   -5870.230422 * km,  3493.051916 * km,
                                         -1.568251 * km / s, -3.702348 * km / s, -6.479485 * km / s };
    State state(cart, epoch);
    const auto [force, torque]                          = oblatenessForce.compute_perturbation(state, Vehicle(sat));
    const AccelerationVector<frames::earth::icrf> accel = force / sat.get_mass();

    // Vallado Ex. 8.5 expected results
    const AccelerationVector<frames::earth::earth_fixed> expectedEcef{ -1.151903e-6 * km / (s * s),
                                                                       -2.938330e-6 * km / (s * s),
                                                                       -1.023539e-5 * km / (s * s) };
    const AccelerationVector<frames::earth::icrf> expected = expectedEcef.in_frame<frames::earth::icrf>(epoch);

    // My results - TODO: Figure this out
    // const AccelerationVector<frames::earth::icrf> expected{ -4.33495448e-08 * km / (s * s),
    //                                                         -9.20504000e-07 * km / (s * s),
    //                                                         -6.45221000e-06 * km / (s * s) };

    const Acceleration expectedNorm = expected.norm();
    const Acceleration accelNorm    = accel.norm();

    // These are much much closer than before, to be expected. They show abou the same size error as when comparing
    // to the NASA 6DoF checkcases so it's possible that there remains a small calculation error somewhere.
    ASSERT_TRUE(math::nearly_equal(accelNorm, expectedNorm, REL_TOL));
    ASSERT_TRUE(nearly_equal(accel, expected, REL_TOL));
}
