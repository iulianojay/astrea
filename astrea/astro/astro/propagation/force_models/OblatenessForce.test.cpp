/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
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
#include <astro/propagation/force_models/OblatenessForce.hpp>
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

class OblatenessForceTest : public testing::Test {
  public:
    OblatenessForceTest() {}

    void SetUp() override {}

    Spacecraft get_vallado_ex85_satellite()
    {
        Spacecraft sat;
        sat.set_mass(1000.0 * kg);
        sat.set_coefficient_of_drag(2.2 * one);
        sat.set_coefficient_of_lift(0.0 * one);
        sat.set_coefficient_of_reflectivity(1.0 * one);
        sat.set_ram_area(40 * m * m);
        sat.set_solar_area(40 * m * m);
        sat.set_lift_area(1.0 * m * m);
        return sat;
    }

    Spacecraft get_checkcase_satellite()
    {
        Spacecraft sat;
        sat.set_mass(400'000.0 * kg);
        sat.set_inertia_tensor(
            InertiaTensor<frames::dynamic::body>(
                1.02e8 * kg * pow<2>(m),  // xx
                6.96e6 * kg * pow<2>(m),  // xy
                5.48e6 * kg * pow<2>(m),  // xz
                6.96e6 * kg * pow<2>(m),  // yx
                0.91e8 * kg * pow<2>(m),  // yy
                -5.90e5 * kg * pow<2>(m), // yz
                5.48e6 * kg * pow<2>(m),  // zx
                -5.90e5 * kg * pow<2>(m), // zy
                5.48e6 * kg * pow<2>(m)   // zz
            )
        );
        sat.set_ram_area(2.5e3 * m * m);
        sat.set_lift_area(2.5e3 * m * m);
        sat.set_solar_area(2.5e3 * m * m);
        sat.set_coefficient_of_drag(2.2);
        sat.set_coefficient_of_lift(2.2);
        sat.set_coefficient_of_reflectivity(1.1);
        return sat;
    }

    const Unitless REL_TOL = 1.0e-6 * one;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(OblatenessForceTest, DefaultConstructor) { ASSERT_NO_THROW(OblatenessForce<planets::Earth>()); }

// Vallado, Ex. 8.5
TEST_F(OblatenessForceTest, ComputeForceValladoEx85)
{
    Spacecraft sat = get_vallado_ex85_satellite();

    Cartesian<frames::earth::icrf> cart{ -605.790796 * km,   -5870.230422 * km,  3493.051916 * km,
                                         -1.568251 * km / s, -3.702348 * km / s, -6.479485 * km / s };

    Date epoch("2020-02-18 15:08:47.23847");

    State state(cart, epoch);
    const auto [force, torque] = OblatenessForce<planets::Earth, 2, 2>().compute_perturbation(state, Vehicle(sat));
    const AccelerationVector<frames::earth::icrf> accel = force / sat.get_mass(state);

    // Vallado Ex. 8.5 expected results
    const AccelerationVector<frames::earth::earth_fixed> expectedEcef{ -1.151903e-6 * km / (s * s),
                                                                       -2.938330e-6 * km / (s * s),
                                                                       -1.023539e-5 * km / (s * s) };
    const AccelerationVector<frames::earth::icrf> expected =
        frames::rotate_vector_into_frame<frames::earth::icrf>(expectedEcef, epoch);

    // My results - TODO: Figure this out
    // const AccelerationVector<frames::earth::icrf> expected{ -4.33495448e-08 * km / (s * s),
    //                                                         -9.20504000e-07 * km / (s * s),
    //                                                         -6.45221000e-06 * km / (s * s) };

    const Acceleration expectedNorm = expected.norm();
    const Acceleration accelNorm    = accel.norm();

    // These are much much closer than before, to be expected. They show about the same size error as when comparing
    // to the NASA 6DoF checkcases so it's possible that there remains a small calculation error somewhere.
    ASSERT_TRUE(math::nearly_equal(accelNorm, expectedNorm, REL_TOL));
    ASSERT_TRUE(nearly_equal(accel, expected, REL_TOL));
}

// From what I can tell, difference at this level (~1e-8 km or O(10 um)) is due to ecef/icrf rotation differences. The
// checkcases don't explicitly list their rotation method so it's hard to know for sure.
TEST_F(OblatenessForceTest, Orbit03A4x4TotalGravityAtT0)
{
    Spacecraft sat = get_checkcase_satellite();

    const Date epoch("2007/324:00:00:00", "%Y/%j:%H:%M:%S");
    Cartesian<frames::earth::icrf> cart{ -4292653.40999999 * m,    955168.470000001 * m,      5139356.56999999 * m,
                                         109.649662999999 * m / s, -7527.72648999999 * m / s, 1484.521489 * m / s };

    State state(cart, epoch);
    const auto [force, torque] = OblatenessForce<planets::Earth, 4, 4>().compute_perturbation(state, Vehicle(sat));
    const AccelerationVector<frames::earth::icrf> oblatenessAccel = force / sat.get_mass(state);

    const auto rEci                                            = cart.get_position();
    const AccelerationVector<frames::earth::icrf> centralAccel = -get_mu<planets::Earth>() / pow<3>(rEci.norm()) * rEci;
    const AccelerationVector<frames::earth::icrf> totalAccel   = centralAccel + oblatenessAccel;

    const AccelerationVector<frames::earth::icrf> expectedTotalAccel{ 5.51387371235876 * m / (s * s),
                                                                      -1.22700119262805 * m / (s * s),
                                                                      -6.62056474851441 * m / (s * s) };

    ASSERT_TRUE(nearly_equal(totalAccel, expectedTotalAccel, REL_TOL));
}

TEST_F(OblatenessForceTest, Orbit03B8x8TotalGravityAtT0)
{
    Spacecraft sat = get_checkcase_satellite();

    const Date epoch("2007/324:00:00:00", "%Y/%j:%H:%M:%S");
    Cartesian<frames::earth::icrf> cart{ -4292653.40999999 * m,    955168.470000001 * m,      5139356.56999999 * m,
                                         109.649662999999 * m / s, -7527.72648999999 * m / s, 1484.521489 * m / s };

    State state(cart, epoch);
    const auto [force, torque] = OblatenessForce<planets::Earth, 8, 8>().compute_perturbation(state, Vehicle(sat));
    const AccelerationVector<frames::earth::icrf> oblatenessAccel = force / sat.get_mass(state);

    const auto rEci                                            = cart.get_position();
    const AccelerationVector<frames::earth::icrf> centralAccel = -get_mu<planets::Earth>() / pow<3>(rEci.norm()) * rEci;
    const AccelerationVector<frames::earth::icrf> totalAccel   = centralAccel + oblatenessAccel;

    const AccelerationVector<frames::earth::icrf> expectedTotalAccel{ 5.51382727336929 * m / (s * s),
                                                                      -1.22706430181432 * m / (s * s),
                                                                      -6.62051654995019 * m / (s * s) };

    ASSERT_TRUE(nearly_equal(totalAccel, expectedTotalAccel, REL_TOL));
}

TEST_F(OblatenessForceTest, Orbit03A4x4TotalGravityAtT60s)
{
    Spacecraft sat = get_checkcase_satellite();

    const Date epoch0("2007/324:00:00:00", "%Y/%j:%H:%M:%S");
    const Date checkcaseDate = epoch0 + 60.0 * s;

    Cartesian<frames::earth::icrf> cart{ -4276158.38817933 * m,    501645.154952279 * m,      5216446.65330053 * m,
                                         439.972330892332 * m / s, -7583.89133224093 * m / s, 1084.1548444161 * m / s };

    State state(cart, checkcaseDate);
    const auto [force, torque] = OblatenessForce<planets::Earth, 4, 4>().compute_perturbation(state, Vehicle(sat));
    const AccelerationVector<frames::earth::icrf> oblatenessAccel = force / sat.get_mass(state);

    const auto rEci                                            = cart.get_position();
    const AccelerationVector<frames::earth::icrf> centralAccel = -get_mu<planets::Earth>() / pow<3>(rEci.norm()) * rEci;
    const AccelerationVector<frames::earth::icrf> totalAccel   = centralAccel + oblatenessAccel;

    const AccelerationVector<frames::earth::icrf> expectedTotalAccel{ 5.49266875931076 * m / (s * s),
                                                                      -0.644443899684263 * m / (s * s),
                                                                      -6.7198683790639 * m / (s * s) };

    ASSERT_TRUE(nearly_equal(totalAccel, expectedTotalAccel, REL_TOL));
}
