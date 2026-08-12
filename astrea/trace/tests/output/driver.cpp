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
#include <sqlite3.h>

#include <gtest/gtest.h>
#include <sqlite_orm/sqlite_orm.h>

#include <mp-units/systems/si.h>

#include <astro/astro.hpp>
#include <trace/io/output.hpp>
#include <trace/trace.hpp>

using namespace astrea;
using namespace astro;
using namespace trace;
using namespace sqlite_orm;

using mp_units::si::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;


class OutputRegressionTest : public testing::Test {
  public:
    // 600 km LEO, 45° inclination — designed so the satellite passes over
    // the ground stations at least once in two hours.
    const Distance sma    = 6971.0 * km; // ~593 km altitude
    const Angle inc       = 45.0 * deg;
    const Time propTime   = hours(2.0);
    const Time resolution = seconds(30.0);
    const Date epoch;

    const std::filesystem::path dbPath = std::filesystem::temp_directory_path() / "output_regression_test.db";

    // FOV objects must outlive any Constellation that holds a SensorParameters
    // pointing at them — they are declared here to ensure test-lifetime duration.
    CircularFieldOfView fov_30deg{ 30.0 * deg };

    Integrator integrator;

    void SetUp() override
    {
        std::filesystem::remove(dbPath);
        integrator.set_abs_tol(1.0e-10);
        integrator.set_rel_tol(1.0e-10);
    }

    void TearDown() override { std::filesystem::remove(dbPath); }

    // Single-satellite constellation with a wide nadir-pointing cone.
    Constellation<Viewer> make_constellation()
    {
        State s0(
            Cartesian<frames::earth::icrf>(
                Keplerian<frames::earth::icrf>(sma, 0.0 * mp_units::one, inc, 0.0 * deg, 0.0 * deg, 0.0 * deg), get_mu<planets::Earth>()
            ),
            epoch
        );
        Viewer sat;
        sat.set_name("SAT-0");
        sat.store_state(s0);

        Constellation<Viewer> constel;
        constel.add_spacecraft(sat);

        SensorParameters cone(&fov_30deg);
        for (auto& shell : constel.get_shells())
            for (auto& plane : shell.get_planes())
                for (auto& v : plane.get_all_spacecraft())
                    v.attach_payload(cone);

        constel.propagate(propTime, integrator);
        return constel;
    }

    // Small grid of ground stations spread around the equatorial band.
    GroundArchitecture<planets::Earth> make_grounds()
    {
        std::vector<GroundStation<planets::Earth>> stations;
        for (double lon = -135.0; lon <= 135.0; lon += 45.0)
            stations.emplace_back(0.0 * deg, lon * deg, 0.0 * km, "GS_lon" + std::to_string(static_cast<int>(lon)));
        return GroundArchitecture<planets::Earth>(stations);
    }
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(OutputRegressionTest, SaveResultsPopulatesGroundLocationsTable)
{
    auto constel = make_constellation();
    auto grounds = make_grounds();

    AccessAnalyzer analyzer(resolution, epoch, epoch + propTime);
    const auto accesses = analyzer.find_accesses(constel, grounds);
    const AccessStats stats(accesses);
    const FoldsOfCoverage folds(accesses, resolution, propTime);

    DatabaseOutputManager mgr(dbPath, true);
    mgr.save_results(folds, stats, accesses, constel, grounds);

    const auto locs = mgr.get_storage().get_all<GroundLocationRecord>();
    ASSERT_EQ(locs.size(), grounds.size()) << "Every ground station must have a location record";

    for (const auto& loc : locs) {
        EXPECT_GE(loc.latitude, -90.0);
        EXPECT_LE(loc.latitude, 90.0);
        EXPECT_GE(loc.longitude, -180.0);
        EXPECT_LE(loc.longitude, 180.0);
        EXPECT_FALSE(loc.name.empty());
    }
}

TEST_F(OutputRegressionTest, SaveResultsPopulatesRiseSetsTable)
{
    auto constel = make_constellation();
    auto grounds = make_grounds();

    AccessAnalyzer analyzer(resolution, epoch, epoch + propTime);
    const auto accesses = analyzer.find_accesses(constel, grounds);
    const AccessStats stats(accesses);
    const FoldsOfCoverage folds(accesses, resolution, propTime);

    DatabaseOutputManager mgr(dbPath, true);
    mgr.save_results(folds, stats, accesses, constel, grounds);

    // With a 30° half-angle cone and equatorial ground stations a 45° LEO
    // satellite should have at least one access in 2 hours.
    const auto riseSets = mgr.get_storage().get_all<RiseSetRecord>();
    ASSERT_GT(riseSets.size(), 0) << "At least one rise/set record expected for this geometry";

    for (const auto& rs : riseSets) {
        EXPECT_FALSE(rs.sender.empty());
        EXPECT_FALSE(rs.receiver.empty());
        EXPECT_FALSE(rs.riseSetTimes.empty());
    }
}

TEST_F(OutputRegressionTest, SaveResultsPopulatesRiseSetMetricsTable)
{
    auto constel = make_constellation();
    auto grounds = make_grounds();

    AccessAnalyzer analyzer(resolution, epoch, epoch + propTime);
    const auto accesses = analyzer.find_accesses(constel, grounds);
    const AccessStats stats(accesses);
    const FoldsOfCoverage folds(accesses, resolution, propTime);

    DatabaseOutputManager mgr(dbPath, true);
    mgr.save_results(folds, stats, accesses, constel, grounds);

    const auto metrics = mgr.get_storage().get_all<RiseSetMetricsRecord>();
    ASSERT_GT(metrics.size(), 0);

    for (const auto& m : metrics) {
        EXPECT_LE(m.minTime, m.avgTime);
        EXPECT_LE(m.avgTime, m.maxTime);
    }
}

TEST_F(OutputRegressionTest, SaveResultsPopulatesAccessMetricsTable)
{
    auto constel = make_constellation();
    auto grounds = make_grounds();

    AccessAnalyzer analyzer(resolution, epoch, epoch + propTime);
    const auto accesses = analyzer.find_accesses(constel, grounds);
    const AccessStats stats(accesses);
    const FoldsOfCoverage folds(accesses, resolution, propTime);

    DatabaseOutputManager mgr(dbPath, true);
    mgr.save_results(folds, stats, accesses, constel, grounds);

    const auto accessMetrics = mgr.get_storage().get_all<AccessMetricsRecord>();
    ASSERT_GT(accessMetrics.size(), 0);
    for (const auto& m : accessMetrics) {
        EXPECT_FALSE(m.object.empty());
        EXPECT_FALSE(m.metricType.empty());
        EXPECT_GE(m.timeValue, 0.0);
    }
}

TEST_F(OutputRegressionTest, SaveGroundTrackRecordCountMatchesSatelliteTimesteps)
{
    auto constel = make_constellation();

    // Determine expected count the same way the implementation does.
    std::size_t nDates = 1;
    Time elapsed       = 0.0 * s;
    while (epoch + elapsed < epoch + propTime) {
        if (epoch + elapsed + resolution >= epoch + propTime)
            elapsed = propTime;
        else
            elapsed += resolution;
        ++nDates;
    }
    const std::size_t nSats = constel.size();

    DatabaseOutputManager mgr(dbPath, true);
    mgr.save_ground_track(constel, epoch, epoch + propTime, resolution);

    const auto records = mgr.get_storage().get_all<GroundTrackRecord>();
    ASSERT_EQ(records.size(), nSats * nDates);
}

TEST_F(OutputRegressionTest, SaveGroundTrackCoordinatesPhysicallyValid)
{
    auto constel = make_constellation();

    DatabaseOutputManager mgr(dbPath, true);
    mgr.save_ground_track(constel, epoch, epoch + propTime, resolution);

    for (const auto& rec : mgr.get_storage().get_all<GroundTrackRecord>()) {
        EXPECT_GE(rec.latitude, -90.0) << "lat < -90 for " << rec.satellite;
        EXPECT_LE(rec.latitude, 90.0) << "lat > +90 for " << rec.satellite;
        EXPECT_GE(rec.longitude, -180.0) << "lon < -180 for " << rec.satellite;
        EXPECT_LE(rec.longitude, 180.0) << "lon > +180 for " << rec.satellite;
        EXPECT_GE(rec.timeSec, 0.0) << "negative time for " << rec.satellite;
    }
}

TEST_F(OutputRegressionTest, DatabasePersistsAcrossManagerInstances)
{
    auto constel = make_constellation();
    auto grounds = make_grounds();

    AccessAnalyzer analyzer(resolution, epoch, epoch + propTime);
    const auto accesses = analyzer.find_accesses(constel, grounds);
    const AccessStats stats(accesses);
    const FoldsOfCoverage folds(accesses, resolution, propTime);

    // Write with first manager instance.
    {
        DatabaseOutputManager writer(dbPath, true);
        writer.save_results(folds, stats, accesses, constel, grounds);
        writer.save_ground_track(constel, epoch, epoch + propTime, resolution);
    }

    // Re-open without overwrite and verify data still present.
    DatabaseOutputManager reader(dbPath, false);
    EXPECT_GT(reader.get_storage().get_all<GroundLocationRecord>().size(), 0);
    EXPECT_GT(reader.get_storage().get_all<RiseSetRecord>().size(), 0);
    EXPECT_GT(reader.get_storage().get_all<GroundTrackRecord>().size(), 0);
}

TEST_F(OutputRegressionTest, ClearAllTablesEmptiesEveryTable)
{
    auto constel = make_constellation();
    auto grounds = make_grounds();

    AccessAnalyzer analyzer(resolution, epoch, epoch + propTime);
    const auto accesses = analyzer.find_accesses(constel, grounds);
    const AccessStats stats(accesses);
    const FoldsOfCoverage folds(accesses, resolution, propTime);

    DatabaseOutputManager mgr(dbPath, true);
    mgr.save_results(folds, stats, accesses, constel, grounds);
    mgr.save_ground_track(constel, epoch, epoch + propTime, resolution);

    mgr.clear_all_tables();

    EXPECT_EQ(mgr.get_storage().get_all<GroundLocationRecord>().size(), 0);
    EXPECT_EQ(mgr.get_storage().get_all<RiseSetRecord>().size(), 0);
    EXPECT_EQ(mgr.get_storage().get_all<RiseSetMetricsRecord>().size(), 0);
    EXPECT_EQ(mgr.get_storage().get_all<ReceiverRiseSetMetricsRecord>().size(), 0);
    EXPECT_EQ(mgr.get_storage().get_all<AccessMetricsRecord>().size(), 0);
    EXPECT_EQ(mgr.get_storage().get_all<FoldsRecord>().size(), 0);
    EXPECT_EQ(mgr.get_storage().get_all<GroundTrackRecord>().size(), 0);
}

// Every access window must have its rise time strictly before its set time.
TEST_F(OutputRegressionTest, RiseTimesAreLessThanCorrespondingSetTimes)
{
    auto constel = make_constellation();
    auto grounds = make_grounds();

    AccessAnalyzer analyzer(resolution, epoch, epoch + propTime);
    const auto accesses = analyzer.find_accesses(constel, grounds);

    for (const auto& [idPair, risesets] : accesses) {
        ASSERT_EQ(risesets.size() % 2, 0u)
            << "Odd number of entries in rise/set array for pair " << idPair.sender << "->" << idPair.receiver;
        for (std::size_t i = 0; i + 1 < risesets.size(); i += 2) {
            EXPECT_LT(risesets[i], risesets[i + 1])
                << "Rise not before set at window " << i / 2 << " for pair " << idPair.sender << "->" << idPair.receiver;
        }
    }
}

// Consecutive access windows for the same pair must not overlap:
// the set time of window i must be <= the rise time of window i+1.
TEST_F(OutputRegressionTest, AccessWindowsDoNotOverlap)
{
    auto constel = make_constellation();
    auto grounds = make_grounds();

    AccessAnalyzer analyzer(resolution, epoch, epoch + propTime);
    const auto accesses = analyzer.find_accesses(constel, grounds);

    for (const auto& [idPair, risesets] : accesses) {
        // risesets: [rise0, set0, rise1, set1, ...]; need set[i] <= rise[i+1]
        for (std::size_t i = 1; i + 1 < risesets.size(); i += 2) {
            EXPECT_LE(risesets[i], risesets[i + 1]) << "Window " << i / 2 << " set overlaps window " << (i / 2 + 1)
                                                    << " rise for pair " << idPair.sender << "->" << idPair.receiver;
        }
    }
}

// Folds of coverage must be non-negative and never exceed the number of
// satellites (a single time step cannot have more simultaneous viewers than
// there are satellites in the constellation).
TEST_F(OutputRegressionTest, FoldsAreNonNegativeAndBoundedByConstellationSize)
{
    auto constel = make_constellation();
    auto grounds = make_grounds();

    AccessAnalyzer analyzer(resolution, epoch, epoch + propTime);
    const auto accesses = analyzer.find_accesses(constel, grounds);
    const FoldsOfCoverage folds(accesses, resolution, propTime);

    const double nSats = static_cast<double>(constel.size());
    for (const auto& [id, foldVec] : folds) {
        for (double f : foldVec) {
            EXPECT_GE(f, 0.0) << "Negative fold count at receiver " << id;
            EXPECT_LE(f, nSats) << "Fold count exceeds constellation size at receiver " << id;
        }
    }
}

// AccessStats must satisfy min <= avg <= max for every receiver and every
// rise/set metric (ACCESS_TIME and GAP).
TEST_F(OutputRegressionTest, AccessStatsOrderingInvariant)
{
    auto constel = make_constellation();
    auto grounds = make_grounds();

    AccessAnalyzer analyzer(resolution, epoch, epoch + propTime);
    const auto accesses = analyzer.find_accesses(constel, grounds);
    const AccessStats stats(accesses);

    for (const auto& [id, rsStats] : stats.get_riseset_statistics()) {
        for (const auto& metric : ALL_RISE_SET_METRICS) {
            const auto& s = rsStats.at(metric);
            if (s.percentiles.empty()) continue; // receiver has no data for this metric
            EXPECT_LE(s.min, s.avg) << "min > avg for receiver " << id << " metric " << static_cast<int>(metric);
            EXPECT_LE(s.avg, s.max) << "avg > max for receiver " << id << " metric " << static_cast<int>(metric);
        }
    }
}

// A 60° half-angle cone must produce at least as many non-empty access pairs
// as a 5° half-angle cone for the same orbit and ground architecture.
TEST_F(OutputRegressionTest, WiderFoVProducesAtLeastAsManyNonEmptyAccessPairs)
{
    // FOV objects must live until after find_accesses() completes.
    CircularFieldOfView fovNarrow(5.0 * deg);
    CircularFieldOfView fovWide(60.0 * deg);

    auto build_constel = [&](CircularFieldOfView& fov) {
        State s0(
            Cartesian<frames::earth::icrf>(
                Keplerian<frames::earth::icrf>(sma, 0.0 * mp_units::one, inc, 0.0 * deg, 0.0 * deg, 0.0 * deg), get_mu<planets::Earth>()
            ),
            epoch
        );
        Viewer sat;
        sat.store_state(s0);
        Constellation<Viewer> constel;
        constel.add_spacecraft(sat);
        SensorParameters cone(&fov);
        for (auto& shell : constel.get_shells())
            for (auto& plane : shell.get_planes())
                for (auto& v : plane.get_all_spacecraft())
                    v.attach_payload(cone);
        constel.propagate(propTime, integrator);
        return constel;
    };

    auto grounds       = make_grounds();
    auto constelNarrow = build_constel(fovNarrow);
    auto constelWide   = build_constel(fovWide);

    AccessAnalyzer analyzer(resolution, epoch, epoch + propTime);
    const auto accessesNarrow = analyzer.find_accesses(constelNarrow, grounds);
    const auto accessesWide   = analyzer.find_accesses(constelWide, grounds);

    auto count_nonempty = [](const AccessArray& arr) {
        std::size_t n = 0;
        for (const auto& [idPair, risesets] : arr)
            if (risesets.size() > 0) ++n;
        return n;
    };

    EXPECT_GE(count_nonempty(accessesWide), count_nonempty(accessesNarrow))
        << "Wider FoV must not yield fewer non-empty access pairs than a narrow FoV";
}

// The number of RiseSetRecord rows saved to the database must equal the number
// of non-empty sender-receiver pairs in the AccessArray.
TEST_F(OutputRegressionTest, RiseSetRecordCountMatchesNonEmptyAccessPairs)
{
    auto constel = make_constellation();
    auto grounds = make_grounds();

    AccessAnalyzer analyzer(resolution, epoch, epoch + propTime);
    const auto accesses = analyzer.find_accesses(constel, grounds);
    const AccessStats stats(accesses);
    const FoldsOfCoverage folds(accesses, resolution, propTime);

    std::size_t nonEmptyPairs = 0;
    for (const auto& [idPair, risesets] : accesses)
        if (risesets.size() > 0) ++nonEmptyPairs;

    DatabaseOutputManager mgr(dbPath, true);
    mgr.save_results(folds, stats, accesses, constel, grounds);

    EXPECT_EQ(mgr.get_storage().get_all<RiseSetRecord>().size(), nonEmptyPairs)
        << "DB RiseSetRecord count must equal the number of non-empty access pairs";
}

// Extending the analysis window should produce at least as many total access
// windows as a shorter window for the same orbit and ground architecture.
TEST_F(OutputRegressionTest, LongerWindowProducesAtLeastAsManyAccessWindows)
{
    const Time shortProp = hours(1.0);
    const Time longProp  = hours(4.0);

    // FOV object must live until after both find_accesses() calls complete.
    CircularFieldOfView fov30(30.0 * deg);

    auto build_constel = [&](Time t) {
        State s0(
            Cartesian<frames::earth::icrf>(
                Keplerian<frames::earth::icrf>(sma, 0.0 * mp_units::one, inc, 0.0 * deg, 0.0 * deg, 0.0 * deg), get_mu<planets::Earth>()
            ),
            epoch
        );
        Viewer sat;
        sat.store_state(s0);
        Constellation<Viewer> constel;
        constel.add_spacecraft(sat);
        SensorParameters cone(&fov30);
        for (auto& shell : constel.get_shells())
            for (auto& plane : shell.get_planes())
                for (auto& v : plane.get_all_spacecraft())
                    v.attach_payload(cone);
        constel.propagate(t, integrator);
        return constel;
    };

    auto grounds      = make_grounds();
    auto constelShort = build_constel(shortProp);
    auto constelLong  = build_constel(longProp);

    AccessAnalyzer analyzerShort(resolution, epoch, epoch + shortProp);
    AccessAnalyzer analyzerLong(resolution, epoch, epoch + longProp);

    const auto accessesShort = analyzerShort.find_accesses(constelShort, grounds);
    const auto accessesLong  = analyzerLong.find_accesses(constelLong, grounds);

    auto total_windows = [](const AccessArray& arr) {
        std::size_t n = 0;
        for (const auto& [idPair, risesets] : arr)
            n += risesets.size() / 2;
        return n;
    };

    EXPECT_GE(total_windows(accessesLong), total_windows(accessesShort))
        << "Longer propagation window must not yield fewer access windows";
}
