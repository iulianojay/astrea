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

#include <trace/analysis/plots/Plotter.hpp>

#include <vector>

#include <mp-units/math.h>
#include <mp-units/systems/si.h>

#include <trace/analysis/stats/FoldsOfCoverage.hpp>
#include <trace/platforms/ground/Grid.hpp>
#include <trace/risesets/AccessArray.hpp>

using namespace mp_units;
using namespace matplot;

using mp_units::angular::unit_symbols::deg;
using mp_units::non_si::day;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace trace {
namespace plotting {

namespace { // anonymous scoping to hide these functions further


std::pair<std::vector<double>, std::vector<double>> extract_lats_lons(const Grid& grounds);

std::pair<std::vector<double>, std::vector<double>> extract_lats_lons(const Grid& grounds)
{
    std::vector<double> lats;
    std::vector<double> lons;
    for (const auto& point : grounds) {
        lats.push_back(point.get_latitude().numerical_value_in(deg));
        lons.push_back(point.get_longitude().numerical_value_in(deg));
    }
    return { lats, lons };
}

} // namespace


void Plotter::plot_access_metrics(const AccessArray& accesses, const std::filesystem::path& outfile) {}

void Plotter::plot_number_of_folds(
    const ViewerConstellation& satellites,
    const Grid& grounds,
    const AccessArray& accesses,
    const Time& resolution,
    const Time& start,
    const Time& end
)
{
    // Setup
    auto h = build_figure("Number of Folds");

    // Get data
    FoldsOfCoverage folds(accesses, resolution, end);

    const auto [lats, lons] = extract_lats_lons(grounds);

    // Plot
    const std::size_t nPlots = 1;
    for (std::size_t iPlot = 0; iPlot < nPlots; ++iPlot) {
        nexttile();
        auto ax = gca();

        auto p = geoplot(ax, lats, lons, "o");
        geolimits(ax, { -90.0, 90.0 }, { -180.0, 180.0 });

        std::vector<double> x              = linspace(-2 * 3.14, 2 * 3.14);
        std::vector<double> y              = linspace(0, 4 * 3.14);
        auto [X, Y]                        = meshgrid(x, y);
        std::vector<std::vector<double>> Z = transform(X, Y, [](double x, double y) { return sin(x) + cos(y); });
        contour(ax, X, Y, Z);

        ax->font_size(_fontSize);
        ax->y_axis().label_font_size(_fontSize);
        ax->y_axis().label_weight(_fontWeight);
        ax->x_axis().label_font_size(_fontSize);
        ax->x_axis().label_weight(_fontWeight);
    }

    // Save
    save(_outputDir / "number_of_folds.png");
}

} // namespace plotting
} // namespace trace
} // namespace astrea