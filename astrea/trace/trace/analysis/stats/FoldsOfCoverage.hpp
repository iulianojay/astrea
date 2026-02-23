/**
 * @file FoldsOfCoverage.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Contains the FoldsOfCoverage class.
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

#include <vector>

#include <gtl/btree.hpp>

#include <units/units.hpp>

#include <trace/analysis/stats/Stats.hpp>
#include <trace/trace.fwd.hpp>

namespace astrea {
namespace trace {

/**
 * @brief The FoldsOfCoverage class represents the folds of coverage (simultaneous accesses) for each receiver ID over time.
 *
 * It calculates the number of accesses (folds) for each receiver ID at each time point based on the provided
 * AccessArray and time parameters. It also computes statistics for the folds of coverage for each receiver ID.
 */
class FoldsOfCoverage {
  public:
    /**
     * @brief Default constructor for FoldsOfCoverage.
     */
    FoldsOfCoverage() = default;

    /**
     * @brief Constructs a FoldsOfCoverage object from an AccessArray and time parameters.
     *
     * @param access The AccessArray containing the rise sets for each sender-receiver pair.
     * @param resolution The time resolution for calculating folds of coverage.
     * @param start The start time for calculating folds of coverage.
     * @param end The end time for calculating folds of coverage.
     */
    FoldsOfCoverage(const AccessArray& access, const Time& resolution, const Time& start, const Time& end);

    /**
     * @brief Iterator type for the FoldsOfCoverage.
     */
    using iterator = gtl::btree_map<std::size_t, std::vector<std::size_t>>::iterator;

    /**
     * @brief Constant iterator type for the FoldsOfCoverage.
     */
    using const_iterator = gtl::btree_map<std::size_t, std::vector<std::size_t>>::const_iterator;

    /**
     * @brief Returns an iterator to the beginning of the FoldsOfCoverage.
     *
     * @return iterator An iterator to the beginning of the FoldsOfCoverage.
     */
    iterator begin() { return _folds.begin(); }

    /**
     * @brief Returns an iterator to the end of the FoldsOfCoverage.
     *
     * @return iterator An iterator to the end of the FoldsOfCoverage.
     */
    iterator end() { return _folds.end(); }

    /**
     * @brief Returns a constant iterator to the beginning of the FoldsOfCoverage.
     *
     * @return const_iterator A constant iterator to the beginning of the FoldsOfCoverage.
     */
    const_iterator begin() const { return _folds.begin(); }

    /**
     * @brief Returns a constant iterator to the end of the FoldsOfCoverage.
     *
     * @return const_iterator A constant iterator to the end of the FoldsOfCoverage.
     */
    const_iterator end() const { return _folds.end(); }

    /**
     * @brief Returns a constant iterator to the beginning of the FoldsOfCoverage.
     *
     * @return const_iterator A constant iterator to the beginning of the FoldsOfCoverage.
     */
    const_iterator cbegin() const { return _folds.cbegin(); }

    /**
     * @brief Returns a constant iterator to the end of the FoldsOfCoverage.
     *
     * @return const_iterator A constant iterator to the end of the FoldsOfCoverage.
     */
    const_iterator cend() const { return _folds.cend(); }

    /**
     * @brief Returns the statistics for a given ID.
     *
     * @param id The ID to get the statistics for.
     * @return Stats<std::size_t> The statistics for the given ID.
     */
    const Stats<std::size_t>& get_stats(const std::size_t& id) const { return _stats.at(id); }

  private:
    gtl::btree_map<std::size_t, std::vector<std::size_t>> _folds; //!< Map of receiver ID to vector of folds of coverage over time.
    gtl::btree_map<std::size_t, Stats<std::size_t>> _stats; //!< Map of receiver ID to statistics for the folds of coverage.
};

} // namespace trace
} // namespace astrea