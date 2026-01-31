/**
 * @file astro.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for plotting utilities in the astro module
 * @date 2026-01-13
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
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
#include <string>
#include <vector>

#include <matplot/matplot.h>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {
namespace plotting {

/**
 * @brief Plots the orbital elements of a trajectory.
 *
 * @param trajectory The state history representing the trajectory.
 * @param outfile The path to the file to save the plot.
 */
void plot_orbital_elements(const StateHistory& trajectory, const std::filesystem::path& outfile);

/**
 * @brief Plots the Cartesian trajectory.
 *
 * @param trajectory The state history representing the trajectory.
 * @param outfile The path to the file to save the plot.
 */
void plot_trajectory(const StateHistory& trajectory, const std::filesystem::path& outfile);

/**
 * @brief Compares multiple trajectories by plotting their orbital elements.
 *
 * @param trajectories A vector of state histories representing the trajectories.
 * @param labels A vector of labels for each trajectory.
 * @param outfile The path to the file to save the comparison plot.
 */
void compare_orbital_elements(const std::vector<StateHistory>& trajectories, const std::vector<std::string>& labels, const std::filesystem::path& outfile);
/**
 * @brief Compares multiple trajectories by plotting their Cartesian components.
 *
 * @param trajectories A vector of state histories representing the trajectories.
 * @param labels A vector of labels for each trajectory.
 * @param outfile The path to the file to save the comparison plot.
 */
void compare_trajectories(const std::vector<StateHistory>& trajectories, const std::vector<std::string>& labels, const std::filesystem::path& outfile);

/**
 * @brief Compares multiple trajectories by plotting their orbital elements.
 *
 * @param trajectories A vector of state histories representing the trajectories.
 * @param labels A vector of labels for each trajectory.
 * @param outfile The path to the file to save the comparison plot.
 */
void plot_difference_orbital_elements(
    const StateHistory expected,
    const std::vector<StateHistory>& trajectories,
    const std::vector<std::string>& labels,
    const std::filesystem::path& outfile
);
/**
 * @brief Compares multiple trajectories by plotting their Cartesian components.
 *
 * @param trajectories A vector of state histories representing the trajectories.
 * @param labels A vector of labels for each trajectory.
 * @param outfile The path to the file to save the comparison plot.
 */
void plot_difference_trajectories(
    const StateHistory expected,
    const std::vector<StateHistory>& trajectories,
    const std::vector<std::string>& labels,
    const std::filesystem::path& outfile
);

} // namespace plotting
} // namespace astro
} // namespace astrea