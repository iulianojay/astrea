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

#include <astro/propagation/force_models/space_weather/atmosphere.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/time/Date.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::rad;

class AtmosphereTest : public testing::Test {
  public:
    AtmosphereTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

inline constexpr struct DummyBody : CelestialBody<"Dummy", star::Sun> {
} DummyBody;

TEST_F(AtmosphereTest, FindAtmosphericDensityDefaultToZero)
{
    const Date date("2020-02-18 15:08:47.23847");

    // Test Earth (has atmosphere in derived class)
    const State state0(Keplerian<frames::earth::icrf>{ 6378.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad }, date);
    const State state1(Keplerian<frames::earth::icrf>{ 6478.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad }, date);
    const State state2(Keplerian<frames::earth::icrf>{ 6878.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad }, date);
    ASSERT_NO_THROW(find_atmospheric_density<DummyBody>(state0));
    ASSERT_NO_THROW(find_atmospheric_density<DummyBody>(state1));
    ASSERT_NO_THROW(find_atmospheric_density<DummyBody>(state2));

    // Base class returns zero density for most bodies
    const auto densityAtAltitude = find_atmospheric_density<DummyBody>(state0);
    ASSERT_EQ(densityAtAltitude.numerical_value_in(kg / pow<3>(m)), 0.0);
}