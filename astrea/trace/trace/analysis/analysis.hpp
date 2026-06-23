/**
 * @file analysis.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for trace analysis functions in the astrea trace library.
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

#include <trace/analysis/TraceConfig.hpp>
#include <trace/analysis/stats/AccessStats.hpp>
#include <trace/analysis/stats/FoldsOfCoverage.hpp>
#include <trace/risesets/AccessArray.hpp>

namespace astrea {
namespace trace {

/**
 * @brief Aggregated results returned by run_trace_analysis.
 */
struct analysisResult {
    AccessArray accesses;
    AccessStats stats;
    FoldsOfCoverage folds;
};

/**
 * @brief Run a full trace analysis (propagation + access + statistics) from a TraceConfig.
 *
 * Builds the constellation, attaches sensors, builds the coverage grid, propagates
 * with J2 mean-element dynamics, runs the access analyzer, and returns the aggregated
 * statistics.  Output (DB write, Python plotting) is the responsibility of the caller.
 */
analysisResult run_trace_analysis(const TraceConfig& config);

} // namespace trace
} // namespace astrea
