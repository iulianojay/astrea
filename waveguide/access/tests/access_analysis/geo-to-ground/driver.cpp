// #include <filesystem>
// #include <fstream>
// #include <iostream>
// #include <ranges>
// #include <stdio.h>

// // #include <arrow/api.h>
// // #include <arrow/csv/api.h>
// // #include <arrow/io/api.h>
// // #include <arrow/ipc/api.h>
// // #include <parquet/arrow/reader.h>
// // #include <parquet/arrow/writer.h>

// #include <sqlite3.h>

// #include <csv-parser/csv.hpp>
// #include <gtest/gtest.h>
// #include <nlohmann/json.hpp>
// #include <sqlite_orm/sqlite_orm.h>

// #include <mp-units/systems/angular.h>
// #include <mp-units/systems/international.h>
// #include <mp-units/systems/isq.h>
// #include <mp-units/systems/si.h>

// #include <access/access.hpp>
// #include <astro/astro.hpp>
// #include <snapshot/snapshot.hpp>

// using namespace waveguide;
// using namespace astro;
// using namespace accesslib;
// using namespace snapshot;
// using namespace sqlite_orm;

// using namespace mp_units;
// using mp_units::angular::unit_symbols::deg;
// using mp_units::si::unit_symbols::km;
// using mp_units::si::unit_symbols::s;

// using mp_units::si::unit_symbols::m;
// using mp_units::si::unit_symbols::W;


// class GeoToGroundAccessTest : public testing::Test {
//   public:
//     GeoToGroundAccessTest() :
//         semimajorGeo(42164.0 * km),
//         start(seconds(0)),
//         end(weeks(1)),
//         eom(sys),
//         accessInterval({ start, end }),
//         resolution(minutes(1))
//     {
//         // Setup integrator
//         integrator.set_abs_tol(1.0e-10);
//         integrator.set_rel_tol(1.0e-10);

//         // Build Force Model
//         forces.add<OblatenessForce>(sys, 2, 0);
//     }

//     void SetUp() override {}

//     AstrodynamicsSystem sys;
//     const Distance semimajorGeo;
//     TwoBody eom;
//     ForceModel forces;
//     Integrator integrator;
//     Time start;
//     Time end;
//     Interval accessInterval;
//     Time resolution;
//     Date epoch;
// };


// int main(int argc, char** argv)
// {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }


// TEST_F(GeoToGroundAccessTest, TwoBallGeoAlwaysConnected)
// {
//     // Build constellation
//     Viewer geo({ Cartesian(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg), sys), epoch, sys });

//     Constellation<Viewer> twoBallGeo;
//     twoBallGeo.add_spacecraft(geo);

//     // Add sensors
//     CircularFieldOfView fov180deg(180.0 * mp_units::angular::unit_symbols::deg);
//     Sensor geoCone(fov180deg);

//     for (auto& shell : twoBallGeo) {
//         for (auto& plane : shell) {
//             for (auto& sat : plane) {
//                 sat.attach(geoCone);
//             }
//         }
//     }

//     // Build out grounds
//     GroundStation ground(38.895 * deg, -77.0366 * deg, 0.0 * km, { fov180deg }, "Test site");
//     GroundArchitecture grounds({ ground });

//     // Propagate
//     twoBallGeo.propagate(epoch, eom, integrator, accessInterval);

//     // Find access
//     const auto accesses = find_accesses(allSats, grounds, resolution, epoch, sys);

//     // Assert that there is access
//     ASSERT_TRUE(accesses.size() > 0);
// }


// TEST_F(GeoToGroundAccessTest, TwoBallGeoNeverConnected)
// {
//     // Build constellation
//     Viewer geo1({ Cartesian(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg), sys),
//     epoch, sys }); Viewer geo2({ Cartesian(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 180.0
//     * deg), sys), epoch, sys }); Constellation<Viewer> twoBallGeo; twoBallGeo.add_spacecraft(geo1);
//     twoBallGeo.add_spacecraft(geo2);

//     // Add sensors
//     CircularFieldOfView fov180deg(180.0 * mp_units::angular::unit_symbols::deg);
//     Sensor geoCone(fov180deg);

//     for (auto& shell : twoBallGeo) {
//         for (auto& plane : shell) {
//             for (auto& sat : plane) {
//                 sat.attach(geoCone);
//             }
//         }
//     }

//     // Propagate
//     twoBallGeo.propagate(epoch, eom, integrator, accessInterval);

//     // Find access
//     const auto accesses = find_accesses(twoBallGeo, resolution, sys);

//     // Assert that there is never access
//     ASSERT_TRUE(accesses.size() == 0);
// }


// TEST_F(GeoToGroundAccessTest, FourBallGeo)
// {
//     // Build constellation
//     Viewer geo1({ Cartesian(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg), sys), epoch, sys });
//     Viewer geo2({ Cartesian(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 90.0 * deg), sys), epoch, sys });
//     Viewer geo3({ Cartesian(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 180.0 * deg), sys), epoch, sys });
//     Viewer geo4({ Cartesian(Keplerian(semimajorGeo, 0.0 * one, 0.0 * deg, 0.0 * deg, 0.0 * deg, 270.0 * deg), sys), epoch, sys });

//     Constellation<Viewer> fourBallGeo;
//     fourBallGeo.add_spacecraft(geo1);
//     fourBallGeo.add_spacecraft(geo2);
//     fourBallGeo.add_spacecraft(geo3);
//     fourBallGeo.add_spacecraft(geo4);

//     // Add sensors
//     CircularFieldOfView fov180deg(180.0 * mp_units::angular::unit_symbols::deg);
//     Sensor geoCone(fov180deg);

//     for (auto& shell : fourBallGeo) {
//         for (auto& plane : shell) {
//             for (auto& sat : plane) {
//                 sat.attach(geoCone);
//             }
//         }
//     }

//     // Propagate
//     fourBallGeo.propagate(epoch, eom, integrator, accessInterval);

//     // Find access
//     auto accesses = find_accesses(fourBallGeo, resolution, sys);

//     // Assert that there is 100% access for non-apposing sats, 0% for apposing sats
//     ASSERT_TRUE(accesses.size() > 0);

//     ASSERT_EQ((accesses[geo1.get_id(), geo2.get_id()]).size(), 2);
//     ASSERT_EQ((accesses[geo1.get_id(), geo3.get_id()]).size(), 0);
//     ASSERT_EQ((accesses[geo1.get_id(), geo4.get_id()]).size(), 2);

//     ASSERT_EQ((accesses[geo2.get_id(), geo3.get_id()]).size(), 2);
//     ASSERT_EQ((accesses[geo2.get_id(), geo4.get_id()]).size(), 0);

//     ASSERT_EQ((accesses[geo3.get_id(), geo4.get_id()]).size(), 2);
// }
