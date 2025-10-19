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

#include <astro/astro.hpp>
#include <matplot/matplot.h>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using namespace matplot;
using mp_units::angular::unit_symbols::deg;
using mp_units::non_si::day;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

void plot_trajectory(const StateHistory& trajectory, const std::string& filename);

int main()
{
    auto start = std::chrono::steady_clock::now();

    // Setup system
    AstrodynamicsSystem sys;
    Date epoch = Date::now();

    // Build constellation
    Keplerian initialElements = Keplerian::GPS();
    initialElements.set_eccentricity(0.1 * one);
    initialElements.set_inclination(25.0 * deg);

    State state0(initialElements, epoch, sys);
    Spacecraft sat(state0);

    // Force model
    ForceModel forces;
    forces.add<OblatenessForce>(sys, 2, 0);

    // Build EoMs
    CowellsMethod cm(sys, forces);
    KeplerianVop kepVop(sys, forces);
    EquinoctialVop eqVop(sys, forces);
    J2MeanVop j2(sys);

    // Setup integrator
    Integrator integrator;
    integrator.set_abs_tol(1.0e-10);
    integrator.set_rel_tol(1.0e-10);

    // Propagate
    Interval propInterval{ seconds(0), months(1) };
    std::cout << "Propagating with Cowell's Method... ";
    const auto trajCm = integrator.propagate(epoch, propInterval, cm, Vehicle(sat), true);
    std::cout << "Cowell's Method Complete." << std::endl;

    std::cout << "Propagating with Keplerian VOP... ";
    const auto trajKepVop = integrator.propagate(epoch, propInterval, kepVop, Vehicle(sat), true);
    std::cout << "Keplerian VOP Complete." << std::endl;

    std::cout << "Propagating with Equinoctial VOP... ";
    const auto trajEqVop = integrator.propagate(epoch, propInterval, eqVop, Vehicle(sat), true);
    std::cout << "Equinoctial VOP Complete." << std::endl;

    std::cout << "Propagating with Mean J2 VOP... ";
    const auto trajJ2 = integrator.propagate(epoch, propInterval, j2, Vehicle(sat), true);
    std::cout << "Mean J2 VOP Complete." << std::endl;

    auto end  = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<nanoseconds>(end - start);

    std::cout << "Runtime: " << diff.count() / 1e9 << " (s)" << std::endl;

    plot_trajectory(trajCm, "cowells_method.png");
    plot_trajectory(trajKepVop, "keplerian_vop.png");
    plot_trajectory(trajEqVop, "equinoctial_vop.png");
    plot_trajectory(trajJ2, "mean_j2_vop.png");

    return 0;
}

void plot_trajectory(const StateHistory& trajectory, const std::string& filename)
{
    // Plot
    std::vector<double> time;
    std::array<std::vector<double>, 6> data;
    const Date epoch = trajectory.epoch();
    for (const auto& [date, state] : trajectory) {
        const Keplerian kep = state.in_element_set<Keplerian>();
        const Time t        = date - epoch;

        const auto a  = kep.get_semimajor();
        const auto e  = kep.get_eccentricity();
        const auto i  = wrap_angle(kep.get_inclination());
        const auto r  = wrap_angle(kep.get_right_ascension());
        const auto w  = wrap_angle(kep.get_argument_of_perigee());
        const auto th = wrap_angle(kep.get_true_anomaly());

        time.push_back(t.numerical_value_in(day));
        data[0].push_back(a.numerical_value_in(km));
        data[1].push_back(e.numerical_value_in(one));
        data[2].push_back(i.numerical_value_in(deg));
        data[3].push_back(r.numerical_value_in(deg));
        data[4].push_back(w.numerical_value_in(deg));
        data[5].push_back(th.numerical_value_in(deg));
    }

    const auto font             = "Arial";
    const float size            = 20.0;
    const bool plotFastVariable = false;
    const std::size_t nPlots    = plotFastVariable ? 6 : 5;

    auto h = figure(true);
    h->title("Orbital Element History");
    h->number_title(false);
    h->size(1500, 1500);
    h->font(font);
    h->font_size(size + 5.0);

    const std::array<std::string, 6> labels = { "Semimajor Axis\\n(km)",   "Eccentricity",
                                                "Inclination\\n(deg)",     "Right Ascension\\n(deg)",
                                                "Arg. of Perigee\\n(deg)", "True Anomaly\\n(deg)" };

    tiledlayout(nPlots, 1);
    for (std::size_t iPlot = 0; iPlot < nPlots; ++iPlot) {
        nexttile();
        auto ax = gca();
        // auto ax = subplot(nPlots, 1, iPlot);

        auto p = plot(ax, time, data[iPlot]);
        p->line_width(2);

        grid(ax, on);
        ylabel(ax, labels[iPlot]);
        if (iPlot == nPlots - 1) {
            xlabel(ax, "Time (days)");
            ax->x_axis().label_font_size(size);
            ax->x_axis().label_weight("bold");
        }

        ax->font_size(size);
        ax->y_axis().label_font_size(size);
        ax->y_axis().label_weight("bold");
    }

    const std::filesystem::path outputDir = std::getenv("ASTREA_ROOT");
    save(outputDir / filename);
}