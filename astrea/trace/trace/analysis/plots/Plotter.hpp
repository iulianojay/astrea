/**
 * @file Plotter.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for plotting utilities in the trace module
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
#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include <matplot/matplot.h>

#include <astro/astro.fwd.hpp>
#include <units/units.hpp>

#include <trace/trace.fwd.hpp>

namespace astrea {
namespace trace {

using ViewerConstellation = astro::Constellation<Viewer>;

namespace plotting {

class Plotter {
  public:
    Plotter() = default;

    void plot_access_metrics(const AccessArray& accesses, const std::filesystem::path& outfile);

    void plot_number_of_folds(
        const ViewerConstellation& satellites,
        const Grid& grounds,
        const AccessArray& accesses,
        const Time& resolution,
        const Time& start,
        const Time& end
    );

    void set_output_directory(const std::filesystem::path& outputDir)
    {
        _outputDir = outputDir;
        std::filesystem::create_directories(_outputDir);
    }

  private:
    std::string _font                = "Arial";
    float _fontSize                  = 25.0;
    std::string _fontWeight          = "bold";
    int _figureWidth                 = 4000;
    int _figureHeight                = 3000;
    std::filesystem::path _outputDir = "./plots";

    auto build_figure(const std::string& title) const
    {
        using namespace matplot;
        auto h = figure(true);
        h->title(title);
        h->number_title(false);
        h->size(_figureWidth, _figureHeight);
        h->font(_font);
        h->font_size(_fontSize);
        return h;
    }
};

} // namespace plotting
} // namespace trace
} // namespace astrea