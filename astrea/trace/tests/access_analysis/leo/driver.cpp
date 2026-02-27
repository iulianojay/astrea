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


class LeoToGroundAccessTest : public testing::Test {
  public:
    LeoToGroundAccessTest() :
        mu(sys.get_mu()),
        semimajorLeo(6778.0 * km),
        propTime(hours(2.0)),
        resolution(seconds(5.0))
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
    const Distance semimajorLeo;
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


TEST_F(LeoToGroundAccessTest, LeoThinCone)
{
    // Build constellation
    const Cartesian elem0(Keplerian(semimajorLeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg), mu);
    const State state0(elem0, epoch, sys);

    const auto& centralBody = sys.get_central_body();

    Viewer leo;
    leo.store_state(state0);

    Constellation<Viewer> constel;
    constel.add_spacecraft(leo);

    // Add sensors
    CircularFieldOfView fov(10.0 * deg);
    SensorParameters leoCone(&fov);

    for (auto& shell : constel.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            for (auto& sat : plane.get_all_spacecraft()) {
                sat.attach_payload(leoCone);
            }
        }
    }

    // Propagate
    constel.propagate(propTime, eom, integrator);

    // Build out grounds from points in the satellite's ground track
    CircularFieldOfView groundFov(75.0 * deg);
    SensorParameters groundCone(&groundFov, astro::RADIAL_RIC);

    const auto stateHistory = constel.get_spacecraft(leo.get_id()).get_state_history();
    std::vector<GroundStation> groundsVec;

    // use a coarser resolution for the ground points so the analysis doesn't skip over them
    for (Date date = epoch; date <= epoch + propTime; date += minutes(1.0)) {
        const auto state = stateHistory.get_state_at(date);
        const auto rEcef = state.get_position().in_frame<frames::earth::earth_fixed>(date);
        const auto lla   = astro::Geodetic(rEcef, centralBody.get());
        const auto lat   = lla.get_latitude();
        const auto lon   = lla.get_longitude();

        GroundStation ground(centralBody.get(), lat, lon, 0.0 * km, "Test site", { groundCone });
        groundsVec.push_back(ground);
    }
    GroundArchitecture grounds(groundsVec);

    // Find access
    AccessAnalyzer analyzer(resolution, epoch, epoch + propTime, sys);
    const auto accesses = analyzer.find_accesses(constel, grounds);

    // Should access every ground at least once
    // will have all sat -> grounds and all grounds -> sat
    ASSERT_EQ(accesses.size(), 2 * grounds.size());
}
