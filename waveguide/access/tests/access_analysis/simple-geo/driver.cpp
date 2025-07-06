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

#include <access/access.hpp>
#include <astro/astro.hpp>
#include <snapshot/snapshot.hpp>

using namespace astro;
using namespace accesslib;
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
    const Distance semimajorGeo;
    TwoBody eom;
    ForceModel forces;
    Integrator integrator;
    Time start;
    Time end;
    Interval accessInterval;
    Time resolution;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(SimpleGeoAccessTest, TwoBallGeoAlwaysConnected)
{
    // Build constellation
    Viewer geo1(Cartesian(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg), sys));
    Viewer geo2(Cartesian(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 90.0 * deg), sys));
    Constellation<Viewer> twoBallGeo;
    twoBallGeo.add_spacecraft(geo1);
    twoBallGeo.add_spacecraft(geo2);

    // Add sensors
    CircularFieldOfView fov180deg(180.0 * mp_units::angular::unit_symbols::deg);
    Sensor geoCone(fov180deg);

    for (auto& shell : twoBallGeo) {
        for (auto& plane : shell) {
            for (auto& sat : plane) {
                sat.attach_sensor(geoCone);
            }
        }
    }

    // Propagate
    twoBallGeo.propagate(eom, integrator, accessInterval);

    // Find access
    const auto accesses = find_accesses(twoBallGeo, resolution, sys);

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
    Viewer geo1(Cartesian(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg), sys));
    Viewer geo2(Cartesian(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 180.0 * deg), sys));
    Constellation<Viewer> twoBallGeo;
    twoBallGeo.add_spacecraft(geo1);
    twoBallGeo.add_spacecraft(geo2);

    // Add sensors
    CircularFieldOfView fov180deg(180.0 * mp_units::angular::unit_symbols::deg);
    Sensor geoCone(fov180deg);

    for (auto& shell : twoBallGeo) {
        for (auto& plane : shell) {
            for (auto& sat : plane) {
                sat.attach_sensor(geoCone);
            }
        }
    }

    // Propagate
    twoBallGeo.propagate(eom, integrator, accessInterval);

    // Find access
    const auto accesses = find_accesses(twoBallGeo, resolution, sys);

    // Assert that there is never access
    ASSERT_TRUE(accesses.size() == 0);
}
