/**
 * @file output.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Contains utilities for outputting access analysis info.
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <numbers>
#include <optional>
#include <sstream>

#include <mp-units/systems/si/units.h>
#include <sqlite_orm/sqlite_orm.h>

#include <astro/frames/definitions.hpp>
#include <astro/platforms/space/Constellation.hpp>
#include <astro/time/Date.hpp>

#include <trace/analysis/stats/AccessStats.hpp>
#include <trace/analysis/stats/FoldsOfCoverage.hpp>
#include <trace/analysis/stats/RiseSetStats.hpp>
#include <trace/platforms/ground/GroundArchitecture.hpp>
#include <trace/risesets/AccessArray.hpp>
#include <trace/risesets/RiseSetArray.hpp>
#include <trace/risesets/riseset_utils.hpp>

using mp_units::si::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace trace {

// Database schema structures
struct RiseSetRecord {
    int id;
    std::string sender;
    std::string receiver;
    std::string riseSetTimes;
};

struct RiseSetMetricsRecord {
    int id;
    std::string sender;
    std::string receiver;
    std::string metricType;
    double minTime;
    double avgTime;
    double maxTime;
    std::string percentiles; // JSON string of percentile values
};

struct ReceiverRiseSetMetricsRecord {
    int id;
    std::string object;
    std::string metricType;
    std::string statType;
    double minTime;
    double avgTime;
    double maxTime;
    std::string percentiles;
};

struct AccessMetricsRecord {
    int id;
    std::string object;
    std::string metricType;
    double timeValue;
};

struct FoldsRecord {
    int id;
    std::string object;
    double minFolds;
    double avgFolds;
    double maxFolds;
    std::string percentiles;
};

struct GroundLocationRecord {
    int id;
    std::string name;
    double latitude;
    double longitude;
    double altitude;
};

struct GroundTrackRecord {
    int id;
    std::string satellite;
    double timeSec;
    double latitude;
    double longitude;
};

// Create database storage with schema
inline auto make_database_storage(const std::filesystem::path& dbPath)
{
    using namespace sqlite_orm;
    return make_storage(
        dbPath.string(),
        make_table(
            "rise_sets",
            make_column("id", &RiseSetRecord::id, primary_key().autoincrement()),
            make_column("sender", &RiseSetRecord::sender),
            make_column("receiver", &RiseSetRecord::receiver),
            make_column("rise_set_times", &RiseSetRecord::riseSetTimes)
        ),

        make_table(
            "rise_set_metrics",
            make_column("id", &RiseSetMetricsRecord::id, primary_key().autoincrement()),
            make_column("sender", &RiseSetMetricsRecord::sender),
            make_column("receiver", &RiseSetMetricsRecord::receiver),
            make_column("metric_type", &RiseSetMetricsRecord::metricType),
            make_column("min_time", &RiseSetMetricsRecord::minTime),
            make_column("avg_time", &RiseSetMetricsRecord::avgTime),
            make_column("max_time", &RiseSetMetricsRecord::maxTime),
            make_column("percentiles", &RiseSetMetricsRecord::percentiles)
        ),

        make_table(
            "receiver_rise_set_metrics",
            make_column("id", &ReceiverRiseSetMetricsRecord::id, primary_key().autoincrement()),
            make_column("object", &ReceiverRiseSetMetricsRecord::object),
            make_column("metric_type", &ReceiverRiseSetMetricsRecord::metricType),
            make_column("stat_type", &ReceiverRiseSetMetricsRecord::statType),
            make_column("min_time", &ReceiverRiseSetMetricsRecord::minTime),
            make_column("avg_time", &ReceiverRiseSetMetricsRecord::avgTime),
            make_column("max_time", &ReceiverRiseSetMetricsRecord::maxTime),
            make_column("percentiles", &ReceiverRiseSetMetricsRecord::percentiles)
        ),

        make_table(
            "access_metrics",
            make_column("id", &AccessMetricsRecord::id, primary_key().autoincrement()),
            make_column("object", &AccessMetricsRecord::object),
            make_column("metric_type", &AccessMetricsRecord::metricType),
            make_column("time_value", &AccessMetricsRecord::timeValue)
        ),

        make_table(
            "folds",
            make_column("id", &FoldsRecord::id, primary_key().autoincrement()),
            make_column("object", &FoldsRecord::object),
            make_column("min_folds", &FoldsRecord::minFolds),
            make_column("avg_folds", &FoldsRecord::avgFolds),
            make_column("max_folds", &FoldsRecord::maxFolds),
            make_column("percentiles", &FoldsRecord::percentiles)
        ),

        make_table(
            "ground_locations",
            make_column("id", &GroundLocationRecord::id, primary_key().autoincrement()),
            make_column("name", &GroundLocationRecord::name),
            make_column("latitude", &GroundLocationRecord::latitude),
            make_column("longitude", &GroundLocationRecord::longitude),
            make_column("altitude", &GroundLocationRecord::altitude)
        ),

        make_table(
            "ground_track",
            make_column("id", &GroundTrackRecord::id, primary_key().autoincrement()),
            make_column("satellite", &GroundTrackRecord::satellite),
            make_column("time_sec", &GroundTrackRecord::timeSec),
            make_column("latitude", &GroundTrackRecord::latitude),
            make_column("longitude", &GroundTrackRecord::longitude)
        )
    );
}

template <typename T, typename U>
std::string get_object_name_from_id(std::size_t id, const astro::Constellation<T>& satellites, const U& grounds = U())
{
    std::string name = "Not Found :(";
    for (const auto& shell : satellites.get_shells()) {
        for (const auto& plane : shell.get_planes()) {
            for (const auto& viewer : plane.get_all_spacecraft()) {
                if (viewer.get_id() == id) { name = viewer.get_name(); }
            }
        }
    }
    if (grounds.size() != 0) {
        for (const auto& ground : grounds) {
            if (ground.get_id() == id) { name = ground.get_name(); }
        }
    }
    return name;
}


/**
 * @brief A class for managing database output operations with a single database instance.
 *
 * This class creates or loads a database on construction and provides methods to save
 * various types of analysis data using the same database connection.
 */
class DatabaseOutputManager {
  public:
    using DatabaseStorage = decltype(make_database_storage(std::filesystem::path{}));

  private:
    DatabaseStorage _storage;

  public:
    /**
     * @brief Constructs a DatabaseOutputManager with the specified database path.
     *
     * @param dbPath The path to the database file. Will be created if it doesn't exist.
     * @param overwrite If true, the existing database will be overwritten. Default is false.
     */
    explicit DatabaseOutputManager(const std::filesystem::path& dbPath, const bool overwrite = false) :
        _storage([&dbPath, overwrite]() {
            if (overwrite) { std::filesystem::remove(dbPath); }
            return make_database_storage(dbPath);
        }())
    {
        _storage.sync_schema();
        optimize_database_performance();
    }

  private:
    /**
     * @brief Optimizes SQLite database performance for bulk operations.
     */
    void optimize_database_performance()
    {
        // Use basic optimizations supported by sqlite_orm
        try {
            _storage.pragma.journal_mode(sqlite_orm::journal_mode::WAL);
        }
        catch (...) {
            // If WAL mode fails, continue with default
        }
    }

  public:
    /**
     * @brief Saves all results to the database in a structured format.
     *
     * @tparam T The type of Spacecraft used in the Constellation.
     * @tparam U The type of the ground container.
     * @param folds The FoldsOfCoverage containing the fold statistics to be saved.
     * @param stats The AccessStats containing the access statistics to be saved.
     * @param accesses The AccessArray containing the access times to be saved.
     * @param satellites The Constellation containing the Spacecraft for which access times are being saved.
     * @param grounds The GroundArchitecture containing the ground stations for which access times are being saved
     */
    template <typename T, typename U>
    void save_results(
        const FoldsOfCoverage& folds,
        const AccessStats& stats,
        const AccessArray& accesses,
        const astro::Constellation<T>& satellites,
        const U& grounds = U()
    )
    {
        save_ground_locations(grounds);
        save_risesets(accesses, satellites, grounds);
        save_riseset_metrics(accesses, satellites, grounds);
        save_receiver_riseset_metrics(stats, satellites, grounds);
        save_access_metrics(stats, satellites, grounds);
        save_number_of_folds(folds, satellites, grounds);
    }

    /**
     * @brief Saves the AccessArray to the database in a structured format.
     *
     * @tparam T The type of Spacecraft used in the Constellation.
     * @tparam U The type of the ground container.
     * @param accesses The AccessArray containing the access times to be saved.
     * @param satellites The Constellation containing the Spacecraft for which access times are being saved.
     * @param grounds The GroundArchitecture containing the ground stations for which access times are being saved
     */
    template <typename T, typename U>
    void save_risesets(const AccessArray& accesses, const astro::Constellation<T>& satellites, const U& grounds = U())
    {
        // Clear existing data first
        _storage.remove_all<RiseSetRecord>();

        // Use transaction for bulk inserts
        _storage.transaction([&] {
            for (const auto& [idPair, risesets] : accesses) {
                if (risesets.size() > 0) {
                    const std::string sender   = get_object_name_from_id(idPair.sender, satellites, grounds);
                    const std::string receiver = get_object_name_from_id(idPair.receiver, satellites, grounds);

                    // Convert rise-set times to a single string
                    std::stringstream riseSetStream;
                    auto riseSetStrings = risesets.to_string_vector();
                    for (size_t i = 0; i < riseSetStrings.size(); ++i) {
                        if (i > 0) riseSetStream << ";";
                        riseSetStream << riseSetStrings[i];
                    }

                    RiseSetRecord record{ -1, sender, receiver, riseSetStream.str() };
                    _storage.insert(record);
                }
            }
            return true; // Commit transaction
        });
    }

    /**
     * @brief Saves the RiseSet metrics to the database in a structured format.
     *
     * @tparam T The type of Spacecraft used in the Constellation.
     * @tparam U The type of the ground container.
     * @param accesses The AccessArray containing the access times to be saved.
     * @param satellites The Constellation containing the Spacecraft for which access times are being saved.
     * @param grounds The GroundArchitecture containing the ground stations for which access times are being saved
     */
    template <typename T, typename U>
    void save_riseset_metrics(const AccessArray& accesses, const astro::Constellation<T>& satellites, const U& grounds = U())
    {
        // Clear existing data first
        _storage.remove_all<RiseSetMetricsRecord>();

        // Use transaction for bulk inserts
        _storage.transaction([&] {
            for (const auto& [idPair, risesets] : accesses) {
                if (risesets.size() > 0) {
                    const std::string sender   = get_object_name_from_id(idPair.sender, satellites, grounds);
                    const std::string receiver = get_object_name_from_id(idPair.receiver, satellites, grounds);

                    RiseSetStats stats(risesets);
                    auto statsVector = stats.to_string_vector();

                    // Parse stats vector based on expected structure
                    size_t idx = 0;
                    for (const auto& metric : ALL_RISE_SET_METRICS) {
                        const std::string metricStr = RISE_SET_METRIC_STRINGS.at(metric);

                        if (idx + 2 < statsVector.size()) {
                            double minTime = std::stod(statsVector[idx]);
                            double avgTime = std::stod(statsVector[idx + 1]);
                            double maxTime = std::stod(statsVector[idx + 2]);
                            idx += 3;

                            // Collect percentile values
                            std::stringstream percentilesStream;
                            for (size_t i = 0; i < DEFAULT_PERCENTILES.size() && idx < statsVector.size(); ++i, ++idx) {
                                if (i > 0) percentilesStream << ",";
                                percentilesStream << statsVector[idx];
                            }

                            RiseSetMetricsRecord record{ -1,      sender,  receiver, metricStr,
                                                         minTime, avgTime, maxTime,  percentilesStream.str() };
                            _storage.insert(record);
                        }
                    }
                }
            }
            return true; // Commit transaction
        });
    }

    /**
     * @brief Saves the receiver RiseSet metrics to the database in a structured format.
     *
     * @tparam T The type of Spacecraft used in the Constellation.
     * @tparam U The type of the ground container.
     * @param stats The AccessStats containing the statistics to be saved.
     * @param satellites The Constellation containing the Spacecraft for which access times are being saved.
     * @param grounds The GroundArchitecture containing the ground stations for which access times are being saved
     */
    template <typename T, typename U>
    void save_receiver_riseset_metrics(const AccessStats& stats, const astro::Constellation<T>& satellites, const U& grounds = U())
    {
        // Clear existing data first
        _storage.remove_all<ReceiverRiseSetMetricsRecord>();

        // Use transaction for bulk inserts
        _storage.transaction([&] {
            std::vector<std::string> statStrings = { "MIN", "AVG", "MAX" };
            for (const auto& pct : DEFAULT_PERCENTILES) {
                int pctVal = pct.numerical_value_ref_in(pct.unit);
                statStrings.push_back(std::to_string(pctVal) + "th PCT");
            }

            for (const auto& metric : ALL_RISE_SET_METRICS) {
                const std::string metricStr = RISE_SET_METRIC_STRINGS.at(metric);

                for (const auto& [id, statsMap] : stats.get_riseset_statistics()) {
                    const std::string object = get_object_name_from_id(id, satellites, grounds);

                    // Get stats vector for this metric
                    auto statsVector = statsMap.at(metric).to_string_vector();

                    // Parse and store min/avg/max and percentiles
                    if (statsVector.size() >= 3) {
                        double minTime = std::stod(statsVector[0]);
                        double avgTime = std::stod(statsVector[1]);
                        double maxTime = std::stod(statsVector[2]);

                        // Collect percentiles
                        std::stringstream percentilesStream;
                        for (size_t i = 3; i < statsVector.size(); ++i) {
                            if (i > 3) percentilesStream << ",";
                            percentilesStream << statsVector[i];
                        }

                        ReceiverRiseSetMetricsRecord record{ -1,      object,  metricStr, "BASIC",
                                                             minTime, avgTime, maxTime,   percentilesStream.str() };
                        _storage.insert(record);
                    }

                    // Get hyper statistics
                    const auto hyperStats = stats.get_hyper_statistics(metric);
                    auto hyperStatsVector = hyperStats.to_string_vector();

                    if (hyperStatsVector.size() >= 3) {
                        double hyperMin = std::stod(hyperStatsVector[0]);
                        double hyperAvg = std::stod(hyperStatsVector[1]);
                        double hyperMax = std::stod(hyperStatsVector[2]);

                        // Collect hyper percentiles
                        std::stringstream hyperPercentilesStream;
                        for (size_t i = 3; i < hyperStatsVector.size(); ++i) {
                            if (i > 3) hyperPercentilesStream << ",";
                            hyperPercentilesStream << hyperStatsVector[i];
                        }

                        ReceiverRiseSetMetricsRecord hyperRecord{
                            -1, object, metricStr, "HYPER", hyperMin, hyperAvg, hyperMax, hyperPercentilesStream.str()
                        };
                        _storage.insert(hyperRecord);
                    }
                }
            }
            return true; // Commit transaction
        });
    }


    /**
     * @brief Saves the access metrics to the database in a structured format.
     *
     * @tparam T The type of Spacecraft used in the Constellation.
     * @tparam U The type of the ground container.
     * @param stats The AccessStats containing the metrics to be saved.
     * @param satellites The Constellation containing the Spacecraft for which access times are being saved.
     * @param grounds The GroundArchitecture containing the ground stations for which access times are being saved
     */
    template <typename T, typename U>
    void save_access_metrics(const AccessStats& stats, const astro::Constellation<T>& satellites, const U& grounds = U())
    {
        // Clear existing data first
        _storage.remove_all<AccessMetricsRecord>();

        // Use transaction for bulk inserts
        _storage.transaction([&] {
            for (const auto& [id, statsMap] : stats.get_access_metrics()) {
                const std::string object = get_object_name_from_id(id, satellites, grounds);

                for (const auto& metric : ALL_ACCESS_METRICS) {
                    const std::string metricStr = ACCESS_METRIC_STRINGS.at(metric);
                    double timeValue            = statsMap.at(metric).numerical_value_ref_in(s);

                    AccessMetricsRecord record{ -1, object, metricStr, timeValue };
                    _storage.insert(record);
                }
            }
            return true; // Commit transaction
        });
    }

    /**
     * @brief Saves the number of folds coverage data to the database in a structured format.
     *
     * @tparam T The type of Spacecraft used in the Constellation.
     * @tparam U The type of the ground container.
     * @param folds The FoldsOfCoverage containing the folds data to be saved.
     * @param satellites The Constellation containing the Spacecraft for which access times are being saved.
     * @param grounds The GroundArchitecture containing the ground stations for which access times are being saved
     */
    template <typename T, typename U>
    void save_number_of_folds(const FoldsOfCoverage& folds, const astro::Constellation<T>& satellites, const U& grounds)
    {
        // Clear existing data first
        _storage.remove_all<FoldsRecord>();

        // Use transaction for bulk inserts
        _storage.transaction([&] {
            for (const auto& [id, foldsVector] : folds) {
                const std::string object = get_object_name_from_id(id, satellites, grounds);

                auto statsVector = folds.get_stats(id).to_string_vector();

                if (statsVector.size() >= 3) {
                    double minFolds = std::stod(statsVector[0]);
                    double avgFolds = std::stod(statsVector[1]);
                    double maxFolds = std::stod(statsVector[2]);

                    // Collect percentiles
                    std::stringstream percentilesStream;
                    for (size_t i = 3; i < statsVector.size(); ++i) {
                        if (i > 3) percentilesStream << ",";
                        percentilesStream << statsVector[i];
                    }

                    FoldsRecord record{ -1, object, minFolds, avgFolds, maxFolds, percentilesStream.str() };
                    _storage.insert(record);
                }
            }
            return true; // Commit transaction
        });
    }

    /**
     * @brief Saves ground location coordinates to the database.
     *
     * @tparam U The type of the ground container (e.g., Grid, GroundArchitecture).
     * @param grounds The container of ground objects to save.
     */
    template <typename U>
    void save_ground_locations(const U& grounds)
    {
        // Clear existing data first
        _storage.remove_all<GroundLocationRecord>();

        // Use transaction for bulk inserts
        _storage.transaction([&] {
            for (const auto& ground : grounds) {
                if constexpr (requires {
                                  ground.get_latitude();
                                  ground.get_longitude();
                                  ground.get_altitude();
                              }) {
                    GroundLocationRecord record{ -1,
                                                 ground.get_name(),
                                                 ground.get_latitude().numerical_value_in(deg),
                                                 ground.get_longitude().numerical_value_in(deg),
                                                 ground.get_altitude().numerical_value_in(km) };
                    _storage.insert(record);
                }
            }
            return true; // Commit transaction
        });
    }

    /**
     * @brief Saves satellite ground track positions (latitude/longitude over time) to the database.
     *
     * @tparam T The spacecraft type used in the Constellation.
     * @param satellites The constellation whose satellites' ground tracks are to be saved.
     * @param startDate The start of the simulation epoch.
     * @param endDate The end of the simulation epoch.
     * @param resolution The time step between saved ground track points.
     */
    template <typename T>
    void save_ground_track(const astro::Constellation<T>& satellites, const astro::Date& startDate, const astro::Date& endDate, const Time& resolution)
    {
        using namespace mp_units::si::unit_symbols;

        _storage.remove_all<GroundTrackRecord>();

        // Build date vector matching AccessAnalyzer::create_date_vector()
        std::vector<astro::Date> dates;
        Time elapsed = 0.0 * s;
        dates.push_back(startDate);
        while (startDate + elapsed < endDate) {
            if (startDate + elapsed + resolution >= endDate) { elapsed = endDate - startDate; }
            else {
                elapsed += resolution;
            }
            dates.push_back(startDate + elapsed);
        }

        _storage.transaction([&] {
            for (const auto& shell : satellites.get_shells()) {
                for (const auto& plane : shell.get_planes()) {
                    for (const auto& sat : plane.get_all_spacecraft()) {
                        const std::string& rawName = sat.get_name();
                        const std::string satName  = rawName.empty() ? "SAT-" + std::to_string(sat.get_id()) : rawName;
                        for (const auto& date : dates) {
                            const auto posEci  = sat.get_position(date);
                            const auto posEcef = posEci.template in_frame<astro::frames::earth::earth_fixed>(date);
                            const double r     = posEcef.norm().numerical_value_in(km);
                            const double z     = posEcef.get_z().numerical_value_in(km);
                            const double y     = posEcef.get_y().numerical_value_in(km);
                            const double x     = posEcef.get_x().numerical_value_in(km);
                            constexpr double rad_to_deg = 180.0 / std::numbers::pi;
                            const double latDeg         = std::asin(z / r) * rad_to_deg;
                            const double lonDeg         = std::atan2(y, x) * rad_to_deg;
                            const double timeSec        = (date - startDate).numerical_value_in(s);
                            _storage.insert(GroundTrackRecord{ -1, satName, timeSec, latDeg, lonDeg });
                        }
                    }
                }
            }
            return true;
        });
    }

    /**
     * @brief Clears all data from all tables in the database.
     *
     * This is useful when you want to completely reset the database
     * before saving new analysis results.
     */
    void clear_all_tables()
    {
        _storage.remove_all<RiseSetRecord>();
        _storage.remove_all<RiseSetMetricsRecord>();
        _storage.remove_all<ReceiverRiseSetMetricsRecord>();
        _storage.remove_all<AccessMetricsRecord>();
        _storage.remove_all<FoldsRecord>();
        _storage.remove_all<GroundLocationRecord>();
        _storage.remove_all<GroundTrackRecord>();
    }

    /**
     * @brief Gets a reference to the underlying database storage.
     *
     * @return DatabaseStorage& Reference to the database storage instance.
     */
    DatabaseStorage& get_storage() { return _storage; }

    /**
     * @brief Gets a const reference to the underlying database storage.
     *
     * @return const DatabaseStorage& Const reference to the database storage instance.
     */
    const DatabaseStorage& get_storage() const { return _storage; }
};

} // namespace trace
} // namespace astrea