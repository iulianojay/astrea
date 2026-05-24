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

#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sqlite3.h>
#include <stdio.h>

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <sqlite_orm/sqlite_orm.h>

#include <mp-units/systems/angular.h>
#include <mp-units/systems/international.h>
#include <mp-units/systems/isq.h>
#include <mp-units/systems/si.h>

#include <astro/astro.hpp>
#include <trace/trace.hpp>

using namespace astrea;
using namespace astro;
using namespace astrea;
using namespace trace;
using namespace sqlite_orm;

using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::W;


class SimpleGeoAccessTest : public testing::Test {
  public:
    SimpleGeoAccessTest() :
        semimajorGeo(42164.0 * km),
        propTime(weeks(1)),
        resolution(minutes(1)),
        epoch(J2000)
    {
        // Setup integrator
        integrator.set_abs_tol(1.0e-10);
        integrator.set_rel_tol(1.0e-10);

        // Build Force Model
        forces.add<OblatenessForce, 2, 0>();
    }

    void SetUp() override {}

    const Distance semimajorGeo;
    ForceModel forces;
    Integrator integrator;
    Time propTime;
    Time resolution;
    Date epoch;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(SimpleGeoAccessTest, TwoBallGeoAlwaysConnected)
{
    // Build constellation
    State state1(Cartesian(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg), get_mu<planets::Earth>()), epoch);
    Viewer geo1;
    geo1.store_state(state1);

    State state2(Cartesian(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 90.0 * deg), get_mu<planets::Earth>()), epoch);
    Viewer geo2;
    geo2.store_state(state2);

    Constellation<Viewer> twoBallGeo;
    twoBallGeo.add_spacecraft(geo1);
    twoBallGeo.add_spacecraft(geo2);

    // Add sensors
    CircularFieldOfView fov180deg(180.0 * mp_units::angular::unit_symbols::deg);
    SensorParameters geoCone(&fov180deg);

    for (auto& shell : twoBallGeo.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            for (auto& sat : plane.get_all_spacecraft()) {
                sat.attach_payload(geoCone);
            }
        }
    }

    // Propagate
    twoBallGeo.propagate(propTime, integrator);

    // Find access
    AccessAnalyzer analyzer(resolution, epoch, epoch + propTime);
    const auto accesses = analyzer.find_internal_accesses(twoBallGeo);

    // Assert that there is 100% access
    ASSERT_TRUE(accesses.size() > 0);
    for (const auto& [idPair, risesets] : accesses) {
        ASSERT_EQ(risesets.size(), 2); // Entire interval
        ASSERT_EQ(risesets[0], 0.0 * s);
        ASSERT_EQ(risesets[1], propTime);
    }
}


TEST_F(SimpleGeoAccessTest, TwoBallGeoNeverConnected)
{
    // Build constellation
    State state1(Cartesian(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg).get_mu()), epoch);
    Viewer geo1;
    geo1.store_state(state1);

    State state2(Cartesian(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 180.0 * deg).get_mu()), epoch);
    Viewer geo2;
    geo2.store_state(state2);

    Constellation<Viewer> twoBallGeo;
    twoBallGeo.add_spacecraft(geo1);
    twoBallGeo.add_spacecraft(geo2);

    // Add sensors
    CircularFieldOfView fov180deg(180.0 * mp_units::angular::unit_symbols::deg);
    SensorParameters geoCone(&fov180deg);

    for (auto& shell : twoBallGeo.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            for (auto& sat : plane.get_all_spacecraft()) {
                sat.attach_payload(geoCone);
            }
        }
    }

    // Propagate
    twoBallGeo.propagate(propTime, integrator);

    // Find access
    AccessAnalyzer analyzer(resolution, epoch, epoch + propTime);
    const auto accesses = analyzer.find_internal_accesses(twoBallGeo);

    // Assert that there is never access
    ASSERT_TRUE(accesses.size() == 0);
}


TEST_F(SimpleGeoAccessTest, FourBallGeo)
{
    // Build constellation
    State state1({ Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg), epoch });
    State state2({ Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 90.0 * deg), epoch });
    State state3({ Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 180.0 * deg), epoch });
    State state4({ Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 270.0 * deg), epoch });

    Viewer geo1;
    geo1.store_state(state1);
    Viewer geo2;
    geo2.store_state(state2);
    Viewer geo3;
    geo3.store_state(state3);
    Viewer geo4;
    geo4.store_state(state4);

    Constellation<Viewer> fourBallGeo;
    fourBallGeo.add_spacecraft(geo1);
    fourBallGeo.add_spacecraft(geo2);
    fourBallGeo.add_spacecraft(geo3);
    fourBallGeo.add_spacecraft(geo4);

    // Add sensors
    CircularFieldOfView fov180deg(180.0 * mp_units::angular::unit_symbols::deg);
    SensorParameters geoCone(&fov180deg);

    for (auto& shell : fourBallGeo.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            for (auto& sat : plane.get_all_spacecraft()) {
                sat.attach_payload(geoCone);
            }
        }
    }

    // Propagate
    fourBallGeo.propagate(propTime, integrator);

    // Find access
    AccessAnalyzer analyzer(resolution, epoch, epoch + propTime);
    auto accesses = analyzer.find_internal_accesses(fourBallGeo);

    // Assert that there is 100% access for non-apposing sats, 0% for apposing sats
    ASSERT_TRUE(accesses.size() > 0);

    // Access size
    const auto access12 = accesses[geo1.get_id(), geo2.get_id()];
    const auto access13 = accesses[geo1.get_id(), geo3.get_id()];
    const auto access14 = accesses[geo1.get_id(), geo4.get_id()];

    const auto access23 = accesses[geo2.get_id(), geo3.get_id()];
    const auto access24 = accesses[geo2.get_id(), geo4.get_id()];

    const auto access34 = accesses[geo3.get_id(), geo4.get_id()];

    ASSERT_EQ(access12.size(), 2);
    ASSERT_EQ(access13.size(), 0);
    ASSERT_EQ(access14.size(), 2);
    ASSERT_EQ(access23.size(), 2);
    ASSERT_EQ(access24.size(), 0);
    ASSERT_EQ(access34.size(), 2);

    // Access time
    ASSERT_EQ(access12.access_time(StatType::AVG), propTime);
    ASSERT_EQ(access13.access_time(StatType::AVG), 0 * s);
    ASSERT_EQ(access14.access_time(StatType::AVG), propTime);
    ASSERT_EQ(access23.access_time(StatType::AVG), propTime);
    ASSERT_EQ(access24.access_time(StatType::AVG), 0 * s);
    ASSERT_EQ(access34.access_time(StatType::AVG), propTime);
}
