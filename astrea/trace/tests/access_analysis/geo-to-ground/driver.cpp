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
#include <stdio.h>

// #include <arrow/api.h>
// #include <arrow/csv/api.h>
// #include <arrow/io/api.h>
// #include <arrow/ipc/api.h>
// #include <parquet/arrow/reader.h>
// #include <parquet/arrow/writer.h>

#include <sqlite3.h>

#include <csv.hpp>
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
using namespace trace;
using namespace sqlite_orm;

using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::W;


class GeoToGroundAccessTest : public testing::Test {
  public:
    GeoToGroundAccessTest() :
        mu(sys.get_mu()),
        semimajorGeo(42164.0 * km),
        propTime(weeks(1)),
        resolution(minutes(1))
    {
        // Setup integrator
        integrator.set_abs_tol(1.0e-10);
        integrator.set_rel_tol(1.0e-10);

        // Build Force Model
        forces.add<OblatenessForce>(sys, 2, 0);
    }

    void SetUp() override {}

    AstrodynamicsSystem sys;
    GravParam mu;
    const Distance semimajorGeo;
    TwoBody eom;
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


TEST_F(GeoToGroundAccessTest, GeoAlwaysConnected)
{
    // Build constellation
    const Cartesian elem0(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg), mu);
    const State state0(elem0, epoch, sys);

    const auto rEcef           = elem0.get_position().in_frame<frames::earth::earth_fixed>(epoch);
    const auto& centralBody    = sys.get_central_body();
    const auto rEq             = centralBody->get_equitorial_radius();
    const auto rPolar          = centralBody->get_polar_radius();
    const auto [lat, lon, alt] = astro::convert_earth_fixed_to_geodetic(rEcef, rEq, rPolar);

    Viewer geo;
    geo.store_state(state0);

    Constellation<Viewer> constel;
    constel.add_spacecraft(geo);

    // Add sensors
    CircularFieldOfView fov180deg(180.0 * mp_units::angular::unit_symbols::deg);
    SensorParameters geoCone(&fov180deg);

    for (auto& shell : constel.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            for (auto& sat : plane.get_all_spacecraft()) {
                sat.attach_payload(geoCone);
            }
        }
    }

    // Build out grounds
    SensorParameters groundCone(&fov180deg, { 1.0 * m, 0.0 * m, 0.0 * m });
    GroundStation ground(centralBody.get(), lat, lon, 0.0 * km, "Test site", { groundCone });
    GroundArchitecture grounds({ ground });

    // Propagate
    constel.propagate(propTime, eom, integrator);

    // Find access
    const auto accesses = find_accesses(constel, grounds, resolution, epoch, sys);

    // Assert that there is access
    ASSERT_TRUE(accesses.size() > 0);
}


TEST_F(GeoToGroundAccessTest, TwoBallGeoNeverConnected)
{
    // Build constellation
    State state1({ Cartesian(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg), mu), epoch, sys });
    Viewer geo1;
    geo1.store_state(state1);

    State state2({ Cartesian(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 180.0 * deg), mu), epoch, sys });
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
    twoBallGeo.propagate(propTime, eom, integrator);

    // Find access
    const auto accesses = find_internal_accesses(twoBallGeo, resolution, epoch, sys);

    // Assert that there is never access
    ASSERT_TRUE(accesses.size() == 0);
}


TEST_F(GeoToGroundAccessTest, FourBallGeo)
{
    // Build constellation
    State state1({ Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg), epoch, sys });
    State state2({ Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 90.0 * deg), epoch, sys });
    State state3({ Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 180.0 * deg), epoch, sys });
    State state4({ Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 270.0 * deg), epoch, sys });

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
    fourBallGeo.propagate(propTime, eom, integrator);

    // Find access
    auto accesses = find_internal_accesses(fourBallGeo, resolution, epoch, sys);

    // Assert that there is 100% access for non-apposing sats, 0% for apposing sats
    ASSERT_TRUE(accesses.size() > 0);

    ASSERT_EQ((accesses[geo1.get_id(), geo2.get_id()]).size(), 2);
    ASSERT_EQ((accesses[geo1.get_id(), geo3.get_id()]).size(), 0);
    ASSERT_EQ((accesses[geo1.get_id(), geo4.get_id()]).size(), 2);

    ASSERT_EQ((accesses[geo2.get_id(), geo3.get_id()]).size(), 2);
    ASSERT_EQ((accesses[geo2.get_id(), geo4.get_id()]).size(), 0);

    ASSERT_EQ((accesses[geo3.get_id(), geo4.get_id()]).size(), 2);
}
