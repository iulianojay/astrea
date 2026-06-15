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
#include <astro/propagation/force_models/AtmosphericForce.hpp>
#include <astro/state/orbital_elements/Cartesian.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/time/Date.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

class AtmosphericForceTest : public testing::Test {
  public:
    AtmosphericForceTest() :
        epoch("2020-02-18 15:08:47.23847"),
        atmoForce()
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
    AtmosphericForce atmoForce;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(AtmosphericForceTest, DefaultConstructor) { ASSERT_NO_THROW(AtmosphericForce()); }

// Vallado, Ex. 8.5
TEST_F(AtmosphericForceTest, ComputeForceValladoEx85)
{
    const Cartesian<frames::earth::icrf> cart{ -605.790796 * km,   -5870.230422 * km,  3493.051916 * km,
                                               -1.568251 * km / s, -3.702348 * km / s, -6.479485 * km / s };
    const State state(cart, epoch);
    const auto [force, torque]                          = atmoForce.compute_perturbation(state, Vehicle(sat));
    const AccelerationVector<frames::earth::icrf> accel = force / sat.get_mass();

    const AccelerationVector<frames::earth::earth_fixed> expectedEcef{ 1.4553e-9 * km / (s * s),
                                                                       1.5354e-9 * km / (s * s),
                                                                       3.2957e-9 * km / (s * s) };
    const AccelerationVector<frames::earth::icrf> expected =
        frames::rotate_vector_into_frame<frames::earth::icrf>(expectedEcef, epoch);

    const Acceleration expectedNorm = expected.norm();
    const Acceleration accelNorm    = accel.norm();

    // ASSERT_TRUE(math::nearly_equal(accelNorm, expectedNorm, REL_TOL));
    // ASSERT_TRUE(nearly_equal(accel, expected, REL_TOL));
}

TEST_F(AtmosphericForceTest, MartianAtmosphere)
{
    AtmosphericForce martianAtmosphere;
    State state(Cartesian<frames::mars::icrf>::LEO(get_mu<planets::Mars>()), epoch);
    ASSERT_NO_THROW(martianAtmosphere.compute_perturbation(state, Vehicle(sat)));
}

TEST_F(AtmosphericForceTest, VenutianAtmosphere)
{
    AtmosphericForce venutianAtmosphere;
    State state(Cartesian<frames::venus::icrf>::LEO(get_mu<planets::Venus>()), epoch);
    ASSERT_NO_THROW(venutianAtmosphere.compute_perturbation(state, Vehicle(sat)));
}

TEST_F(AtmosphericForceTest, TitanAtmosphere)
{
    AtmosphericForce titanAtmosphere;
    State state(Cartesian<frames::titan::icrf>::LEO(get_mu<moons::Titan>()), epoch);
    ASSERT_NO_THROW(titanAtmosphere.compute_perturbation(state, Vehicle(sat)));
}