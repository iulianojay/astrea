

# File Plotter.hpp

[**File List**](files.md) **>** [**analysis**](dir_46c4498db40ce3dbd9ced60b5dc27dd1.md) **>** [**plots**](dir_6faad7806a2c60f21e03829ae6b33a05.md) **>** [**Plotter.hpp**](Plotter_8hpp.md)

[Go to the documentation of this file](Plotter_8hpp.md)


```C++

#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include <matplot/matplot.h>

#include <astro/astro.fwd.hpp>
#include <astro/systems/celestial_bodies/Earth/Earth.hpp>
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
        const Grid<astro::planets::Earth>& grounds,
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
```


