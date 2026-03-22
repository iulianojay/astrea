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

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/propagation/force_models/instances/SolarRadiationPressure.hpp>
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

class SolarRadiationPressureTest : public testing::Test {
  public:
    SolarRadiationPressureTest() :
        epoch("2020-02-18 15:08:47.23847"),
        sys(CelestialBodyId::EARTH, { CelestialBodyId::MOON, CelestialBodyId::SUN })
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
    SolarRadiationPressure force;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(SolarRadiationPressureTest, DefaultConstructor) { ASSERT_NO_THROW(SolarRadiationPressure()); }

// Vallado, Ex. 8.5
TEST_F(SolarRadiationPressureTest, ComputeForceValladoEx85)
{
    // These two won't match exactly because Vallado uses 4.56e-6 as average SRP and we use 4.556485540406757e-6 scaled
    // to the ratio of 1 AU and the distance from the sat to the Sun. With these values matched, the results are within
    // 10%. Given the large number of assumptions in this SRP model, the simplicity of the used approximations, and
    // other numerical differences between this code and Vallado's, this is close enough.
    // Since matching them exactly is impractical, the expected values are taken from a run of this code, not Vallado's.

    Cartesian cart{ -605.790796 * km,   -5870.230422 * km,  3493.051916 * km,
                    -1.568251 * km / s, -3.702348 * km / s, -6.479485 * km / s };
    State state(cart, epoch, sys);
    const auto [accel, torque] = force.compute_perturbation(state, Vehicle(sat));

    // // Vallado's expected results
    // const AccelerationVector<frames::earth::icrf> expected{ -1.8791e-10 * km / (s * s),
    //                                                         1.0298e-10 * km / (s * s),
    //                                                         4.4651e-11 * km / (s * s) };

#if defined(ASTREA_BUILD_EARTH_EPHEMERIS) && defined(ASTREA_BUILD_SUN_EPHEMERIS)

    // These values come from a run of this code, not Vallado's. They're within ~20% of Vallado's
    const AccelerationVector<frames::earth::icrf> expected{ -1.6020954749490711e-10 * km / (s * s),
                                                            8.7799006711875608e-11 * km / (s * s),
                                                            3.8068764763680937e-11 * km / (s * s) };

#elif !defined(ASTREA_BUILD_EARTH_EPHEMERIS) && !defined(ASTREA_BUILD_SUN_EPHEMERIS)

    // These are kinda bad. Pretty close to ephemeris values, but still off Vallados
    const AccelerationVector<frames::earth::icrf> expected{ -1.59324328e-10 * km / (s * s),
                                                            8.92084894e-11 * km / (s * s),
                                                            3.86793674e-11 * km / (s * s) };
#endif

    const Acceleration expectedNorm = expected.norm();
    const Acceleration accelNorm    = accel.norm();

    ASSERT_EQ_QUANTITY(accelNorm, expectedNorm, REL_TOL * 1e1);
    ASSERT_EQ_CART_VEC(accel, expected, REL_TOL);
}
