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

#include <csv-parser/csv.hpp>
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <sqlite_orm/sqlite_orm.h>

#include <mp-units/systems/angular.h>
#include <mp-units/systems/international.h>
#include <mp-units/systems/isq.h>
#include <mp-units/systems/si.h>

#include <astro/astro.hpp>
#include <snapshot/snapshot.hpp>
#include <trace/trace.hpp>

using namespace astrea;
using namespace astro;
using namespace astrea;
using namespace trace;
using namespace snapshot;
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
        start(seconds(0)),
        end(weeks(1)),
        eom(sys),
        accessInterval({ start, end }),
        resolution(minutes(1)),
        epoch(J2000)
    {
        // Setup integrator
        integrator.set_abs_tol(1.0e-10);
        integrator.set_rel_tol(1.0e-10);

        // Build Force Model
        forces.add<OblatenessForce>(sys, 2, 0);
    }

    void SetUp() override {}

    AstrodynamicsSystem sys;
    const Distance semimajorGeo;
    TwoBody eom;
    ForceModel forces;
    Integrator integrator;
    Time start;
    Time end;
    Interval accessInterval;
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
    Viewer geo1({ Cartesian(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg), sys), epoch, sys });
    Viewer geo2({ Cartesian(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 90.0 * deg), sys), epoch, sys });
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
    twoBallGeo.propagate(epoch, eom, integrator, accessInterval);

    // Find access
    const auto accesses = find_internal_accesses(twoBallGeo, resolution, epoch, sys);

    // Assert that there is 100% access
    ASSERT_TRUE(accesses.size() > 0);
    for (const auto& [idPair, risesets] : accesses) {
        ASSERT_EQ(risesets.size(), 2); // Entire interval
        ASSERT_EQ(risesets[0], start);
        ASSERT_EQ(risesets[1], end);
    }
}


TEST_F(SimpleGeoAccessTest, TwoBallGeoNeverConnected)
{
    // Build constellation
    Viewer geo1({ Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg), epoch, sys });
    Viewer geo2({ Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 180.0 * deg), epoch, sys });
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
    twoBallGeo.propagate(epoch, eom, integrator, accessInterval);

    // Find access
    const auto accesses = find_internal_accesses(twoBallGeo, resolution, epoch, sys);

    // Assert that there is never access
    ASSERT_TRUE(accesses.size() == 0);
}


TEST_F(SimpleGeoAccessTest, FourBallGeo)
{
    // Build constellation
    Viewer geo1({ Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg), epoch, sys });
    Viewer geo2({ Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 90.0 * deg), epoch, sys });
    Viewer geo3({ Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 180.0 * deg), epoch, sys });
    Viewer geo4({ Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 270.0 * deg), epoch, sys });

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
    fourBallGeo.propagate(epoch, eom, integrator, accessInterval);

    // Find access
    auto accesses = find_internal_accesses(fourBallGeo, resolution, epoch, sys);

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
    const Time zero    = start;
    const Time simTime = end - start;
    ASSERT_EQ(access12.access_time(Stat::MEAN), simTime);
    ASSERT_EQ(access13.access_time(Stat::MEAN), zero);
    ASSERT_EQ(access14.access_time(Stat::MEAN), simTime);
    ASSERT_EQ(access23.access_time(Stat::MEAN), simTime);
    ASSERT_EQ(access24.access_time(Stat::MEAN), zero);
    ASSERT_EQ(access34.access_time(Stat::MEAN), simTime);
}
