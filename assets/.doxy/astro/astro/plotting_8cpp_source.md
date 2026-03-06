

# File plotting.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**utilities**](dir_68b93ce2887c47fc193a24ece16ebbe5.md) **>** [**plotting.cpp**](plotting_8cpp.md)

[Go to the documentation of this file](plotting_8cpp.md)


```C++
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

#include <astro/utilities/plotting.hpp>

#include <array>

#include <mp-units/math.h>
#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/state/State.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/time/Date.hpp>

using namespace mp_units;
using namespace matplot;

using mp_units::angular::unit_symbols::deg;
using mp_units::non_si::day;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace astro {
namespace plotting {

namespace { // anonymous scoping to hide these functions further

std::vector<double> extract_raw_time_data(const StateHistory& trajectory);

std::array<std::vector<double>, 6> extract_raw_orbital_elements(const StateHistory& trajectory);

std::array<std::vector<double>, 6>
    extract_raw_orbital_elements_at_times(const std::vector<double>& times, const StateHistory& trajectory);

std::array<std::vector<double>, 6> extract_raw_cartesian_elements(const StateHistory& trajectory);

std::array<std::vector<double>, 6>
    extract_raw_cartesian_elements_at_times(const std::vector<double>& times, const StateHistory& trajectory);


std::vector<double> extract_raw_time_data(const StateHistory& trajectory)
{
    std::vector<double> time;
    const Date epoch = trajectory.epoch();
    for (const auto& [date, state] : trajectory) {
        const Time t = date - epoch;
        time.push_back(t.numerical_value_in(day));
    }
    return time;
}


std::array<std::vector<double>, 6> extract_raw_orbital_elements(const StateHistory& trajectory)
{
    std::array<std::vector<double>, 6> data;
    for (const auto& [date, state] : trajectory) {
        const Keplerian kep = state.in_element_set<Keplerian>();

        const auto a  = kep.get_semimajor();
        const auto e  = kep.get_eccentricity();
        const auto i  = wrap_angle(kep.get_inclination());
        const auto r  = wrap_angle(kep.get_right_ascension());
        const auto w  = wrap_angle(kep.get_argument_of_perigee());
        const auto th = wrap_angle(kep.get_true_anomaly());

        data[0].push_back(a.numerical_value_in(km));
        data[1].push_back(e.numerical_value_in(one));
        data[2].push_back(i.numerical_value_in(deg));
        data[3].push_back(r.numerical_value_in(deg));
        data[4].push_back(w.numerical_value_in(deg));
        data[5].push_back(th.numerical_value_in(deg));
    }
    return data;
}


std::array<std::vector<double>, 6> extract_raw_orbital_elements_at_times(const std::vector<double>& times, const StateHistory& trajectory)
{
    std::array<std::vector<double>, 6> data;
    const Date epoch = trajectory.epoch();
    for (const auto& time : times) {
        const Keplerian kep = trajectory.get_state_at(epoch + time * day).in_element_set<Keplerian>();
        const auto a        = kep.get_semimajor();
        const auto e        = kep.get_eccentricity();
        const auto i        = wrap_angle(kep.get_inclination());
        const auto r        = wrap_angle(kep.get_right_ascension());
        const auto w        = wrap_angle(kep.get_argument_of_perigee());
        const auto th       = wrap_angle(kep.get_true_anomaly());

        data[0].push_back(a.numerical_value_in(km));
        data[1].push_back(e.numerical_value_in(one));
        data[2].push_back(i.numerical_value_in(deg));
        data[3].push_back(r.numerical_value_in(deg));
        data[4].push_back(w.numerical_value_in(deg));
        data[5].push_back(th.numerical_value_in(deg));
    }
    return data;
}


std::array<std::vector<double>, 6> extract_raw_cartesian_elements(const StateHistory& trajectory)
{
    std::array<std::vector<double>, 6> data;
    for (const auto& [date, state] : trajectory) {
        const Cartesian cart = state.in_element_set<Cartesian>();

        const auto x  = cart.get_x();
        const auto y  = cart.get_y();
        const auto z  = cart.get_z();
        const auto vx = cart.get_vx();
        const auto vy = cart.get_vy();
        const auto vz = cart.get_vz();

        data[0].push_back(x.numerical_value_in(km));
        data[1].push_back(y.numerical_value_in(km));
        data[2].push_back(z.numerical_value_in(km));
        data[3].push_back(vx.numerical_value_in(km / s));
        data[4].push_back(vy.numerical_value_in(km / s));
        data[5].push_back(vz.numerical_value_in(km / s));
    }
    return data;
}


std::array<std::vector<double>, 6> extract_raw_cartesian_elements_at_times(const std::vector<double>& times, const StateHistory& trajectory)
{
    std::array<std::vector<double>, 6> data;
    const Date epoch = trajectory.epoch();
    for (const auto& time : times) {
        const Cartesian cart = trajectory.get_state_at(epoch + time * day).in_element_set<Cartesian>();

        const auto x  = cart.get_x();
        const auto y  = cart.get_y();
        const auto z  = cart.get_z();
        const auto vx = cart.get_vx();
        const auto vy = cart.get_vy();
        const auto vz = cart.get_vz();

        data[0].push_back(x.numerical_value_in(km));
        data[1].push_back(y.numerical_value_in(km));
        data[2].push_back(z.numerical_value_in(km));
        data[3].push_back(vx.numerical_value_in(km / s));
        data[4].push_back(vy.numerical_value_in(km / s));
        data[5].push_back(vz.numerical_value_in(km / s));
    }
    return data;
}

} // namespace

void plot_orbital_elements(const StateHistory& trajectory, const std::filesystem::path& outfile)
{
    // Plot
    std::vector<double> time                = extract_raw_time_data(trajectory);
    std::array<std::vector<double>, 6> data = extract_raw_orbital_elements(trajectory);
    const Date epoch                        = trajectory.epoch();

    const auto font             = "Arial";
    const float size            = 20.0;
    const bool plotFastVariable = false;
    const std::size_t nPlots    = plotFastVariable ? 6 : 5;

    auto h = figure(true);
    h->title("Orbital Element History");
    h->number_title(false);
    h->size(2000, 1500);
    h->font(font);
    h->font_size(size + 5.0);

    const std::array<std::string, 6> labels      = { "Semimajor Axis",  "Eccentricity",    "Inclination",
                                                     "Right Ascension", "Arg. of Perigee", "True Anomaly" };
    const std::array<std::string, 6> units       = { "km", " ", "deg", "deg", "deg", "deg" };
    const std::array<std::string, 6> tickformats = { "%g", "%0.3f", "%0.3f", "%0.0f", "%0.0f", "%0.0f" };

    tiledlayout(nPlots, 1);
    for (std::size_t iPlot = 0; iPlot < nPlots; ++iPlot) {
        nexttile();
        auto ax = gca();

        auto p = plot(ax, time, data[iPlot]);
        p->line_width(4);

        grid(ax, on);
        if (iPlot >= 3) {
            ylim(ax, { 0.0, 360.0 });
            yticks(ax, { 0.0, 90.0, 180.0, 270.0, 360.0 });
        }
        xlim(ax, { time.front(), time.back() });

        ylabel(ax, labels[iPlot] + " \\n(" + units[iPlot] + ")");
        ytickformat(ax, tickformats[iPlot]);
        if (iPlot == nPlots - 1) {
            xlabel(ax, "Time");
            xtickformat(ax, "%g days");
            ax->x_axis().label_font_size(size);
            ax->x_axis().label_weight("bold");
        }

        ax->font_size(size);
        ax->y_axis().label_font_size(size);
        ax->y_axis().label_weight("bold");
    }
    std::filesystem::create_directories(outfile.parent_path());
    save(outfile);
}


void plot_trajectory(const StateHistory& trajectory, const std::filesystem::path& outfile)
{
    // Plot
    std::array<std::vector<double>, 6> data = extract_raw_cartesian_elements(trajectory);
    std::vector<double> time                = extract_raw_time_data(trajectory);
    const Date epoch                        = trajectory.epoch();

    std::vector<double> R;
    std::vector<double> V;
    for (std::size_t ii = 0; ii < time.size(); ++ii) {

        const auto x  = data[0][ii];
        const auto y  = data[1][ii];
        const auto z  = data[2][ii];
        const auto vx = data[3][ii];
        const auto vy = data[4][ii];
        const auto vz = data[5][ii];

        R.push_back(sqrt(x * x + y * y + z * z));
        V.push_back(sqrt(vx * vx + vy * vy + vz * vz));
    }

    const auto font  = "Arial";
    const float size = 20.0;

    auto h = figure(true);
    h->title("State History");
    h->number_title(false);
    h->size(2000, 1500);
    h->font(font);
    h->font_size(size + 5.0);

    const std::array<std::string, 6> labels = { "X", "Y", "Z", "VX", "VY", "VZ" };
    const std::array<std::string, 6> units  = { "km", "km/s" };

    for (std::size_t iPlot = 0; iPlot < 2; ++iPlot) {
        // 3-D trajectory plots
        auto ax = subplot(2, 2, iPlot);

        auto p = plot3(ax, data[3 * iPlot], data[3 * iPlot + 1], data[3 * iPlot + 2]);
        p->line_width(4);

        grid(ax, on);

        xlabel(ax, labels[3 * iPlot] + " \\n(" + units[iPlot] + ")");
        ylabel(ax, labels[3 * iPlot + 1] + " \\n(" + units[iPlot] + ")");
        zlabel(ax, labels[3 * iPlot + 2] + " \\n(" + units[iPlot] + ")");

        xtickformat(ax, "%g");
        ytickformat(ax, "%g");
        ztickformat(ax, "%g");

        ax->font_size(size);
        ax->x_axis().label_font_size(size);
        ax->x_axis().label_weight("bold");
        ax->y_axis().label_font_size(size);
        ax->y_axis().label_weight("bold");
        ax->z_axis().label_font_size(size);
        ax->z_axis().label_weight("bold");

        // magnitude plots
        ax = subplot(2, 2, iPlot + 2);
        p  = plot(ax, time, iPlot == 0 ? R : V);
        p->line_width(4);

        grid(ax, on);

        xlabel(ax, "Time");
        xtickformat(ax, "%g days");
        ylabel(ax, iPlot == 0 ? "Range \\n(km)" : "Velocity \\n(km/s)");

        xtickformat(ax, "%g");
        ytickformat(ax, "%g");

        ax->font_size(size);
        ax->x_axis().label_font_size(size);
        ax->x_axis().label_weight("bold");
        ax->y_axis().label_font_size(size);
        ax->y_axis().label_weight("bold");
    }
    std::filesystem::create_directories(outfile.parent_path());
    save(outfile);
}


void compare_orbital_elements(const std::vector<StateHistory>& trajectories, const std::vector<std::string>& trajLabels, const std::filesystem::path& outfile)
{
    const auto font             = "Arial";
    const float size            = 20.0;
    const bool plotFastVariable = false;
    const std::size_t nPlots    = plotFastVariable ? 6 : 5;

    auto h = figure(true);
    h->title("Orbital Element History");
    h->number_title(false);
    h->size(4000, 3000);
    h->font(font);
    h->font_size(size + 5.0);

    const std::array<std::string, 6> labels      = { "Semimajor Axis",  "Eccentricity",    "Inclination",
                                                     "Right Ascension", "Arg. of Perigee", "True Anomaly" };
    const std::array<std::string, 6> units       = { "km", " ", "deg", "deg", "deg", "deg" };
    const std::array<std::string, 6> tickformats = { "%0.8f", "%0.8f", "%0.8f", "%0.8f", "%0.4f", "%0.0f" };

    tiledlayout(nPlots, 1);
    for (std::size_t iPlot = 0; iPlot < nPlots; ++iPlot) {

        nexttile();
        auto ax = gca();

        double minTime     = std::numeric_limits<double>::max();
        double maxTime     = std::numeric_limits<double>::lowest();
        unsigned int iTraj = 0;
        for (const auto& trajectory : trajectories) {
            std::vector<double> time                = extract_raw_time_data(trajectory);
            std::array<std::vector<double>, 6> data = extract_raw_orbital_elements(trajectory);

            if (time.front() < minTime) { minTime = time.front(); }
            if (time.back() > maxTime) { maxTime = time.back(); }

            auto p = plot(ax, time, data[iPlot]);
            p->line_width(10.0 - iTraj);
            hold(on);
            ++iTraj;
        }

        legend(ax, trajLabels);
        grid(ax, on);

        xlim(ax, { minTime, maxTime });

        ylabel(ax, labels[iPlot] + " \\n(" + units[iPlot] + ")");
        ytickformat(ax, tickformats[iPlot]);
        if (iPlot == nPlots - 1) {
            xlabel(ax, "Time");
            xtickformat(ax, "%g days");
            ax->x_axis().label_font_size(size);
            ax->x_axis().label_weight("bold");
        }

        ax->font_size(size);
        ax->y_axis().label_font_size(size);
        ax->y_axis().label_weight("bold");
    }
    std::filesystem::create_directories(outfile.parent_path());
    save(outfile);
}


void compare_trajectories(const std::vector<StateHistory>& trajectories, const std::vector<std::string>& trajLabels, const std::filesystem::path& outfile)
{
    const auto font  = "Arial";
    const float size = 20.0;

    auto h = figure(true);
    h->title("State History");
    h->number_title(false);
    h->size(4000, 3000);
    h->font(font);
    h->font_size(size + 5.0);

    const std::array<std::string, 6> labels = { "X", "Y", "Z", "VX", "VY", "VZ" };
    const std::array<std::string, 6> units  = { "km", "km/s" };

    for (std::size_t iPlot = 0; iPlot < 2; ++iPlot) {
        // 3-D trajectory plots
        auto ax = subplot(2, 2, iPlot);

        unsigned int iTraj = 0;
        for (const auto& trajectory : trajectories) {
            std::array<std::vector<double>, 6> data = extract_raw_cartesian_elements(trajectory);

            auto p = plot3(ax, data[3 * iPlot], data[3 * iPlot + 1], data[3 * iPlot + 2]);
            p->line_width(10.0 - iTraj);
            hold(on);
            ++iTraj;
        }

        legend(ax, trajLabels);
        grid(ax, on);

        xlabel(ax, labels[3 * iPlot] + " \\n(" + units[iPlot] + ")");
        ylabel(ax, labels[3 * iPlot + 1] + " \\n(" + units[iPlot] + ")");
        zlabel(ax, labels[3 * iPlot + 2] + " \\n(" + units[iPlot] + ")");

        xtickformat(ax, "%g");
        ytickformat(ax, "%g");
        ztickformat(ax, "%g");

        ax->font_size(size);
        ax->x_axis().label_font_size(size);
        ax->x_axis().label_weight("bold");
        ax->y_axis().label_font_size(size);
        ax->y_axis().label_weight("bold");
        ax->z_axis().label_font_size(size);
        ax->z_axis().label_weight("bold");

        // magnitude plots
        ax    = subplot(2, 2, iPlot + 2);
        iTraj = 0;
        for (const auto& trajectory : trajectories) {
            std::vector<double> time                = extract_raw_time_data(trajectory);
            std::array<std::vector<double>, 6> data = extract_raw_cartesian_elements(trajectory);
            const Date epoch                        = trajectory.epoch();

            std::vector<double> R;
            std::vector<double> V;
            for (std::size_t ii = 0; ii < time.size(); ++ii) {

                const double& x  = data[0][ii];
                const double& y  = data[1][ii];
                const double& z  = data[2][ii];
                const double& vx = data[3][ii];
                const double& vy = data[4][ii];
                const double& vz = data[5][ii];

                R.push_back(sqrt(x * x + y * y + z * z));
                V.push_back(sqrt(vx * vx + vy * vy + vz * vz));
            }
            auto p = plot(ax, time, iPlot == 0 ? R : V);
            p->line_width(10.0 - iTraj);
            hold(on);
            ++iTraj;
        }

        legend(ax, trajLabels);
        grid(ax, on);

        xlabel(ax, "Time");
        xtickformat(ax, "%g days");
        ylabel(ax, iPlot == 0 ? "Range \\n(km)" : "Velocity \\n(km/s)");

        xtickformat(ax, "%g");
        ytickformat(ax, "%g");

        ax->font_size(size);
        ax->x_axis().label_font_size(size);
        ax->x_axis().label_weight("bold");
        ax->y_axis().label_font_size(size);
        ax->y_axis().label_weight("bold");
    }
    std::filesystem::create_directories(outfile.parent_path());
    save(outfile);
}

void plot_difference_orbital_elements(
    const StateHistory expected,
    const std::vector<StateHistory>& trajectories,
    const std::vector<std::string>& trajLabels,
    const std::filesystem::path& outfile
)
{
    const auto font             = "Arial";
    const float size            = 20.0;
    const bool plotFastVariable = false;
    const std::size_t nPlots    = plotFastVariable ? 6 : 5;

    auto h = figure(true);
    h->title("Orbital Element History");
    h->number_title(false);
    h->size(4000, 3000);
    h->font(font);
    h->font_size(size + 5.0);

    const std::array<std::string, 6> labels      = { "Δ Semimajor Axis",  "Δ Eccentricity",    "Δ Inclination",
                                                     "Δ Right Ascension", "Δ Arg. of Perigee", "Δ True Anomaly" };
    const std::array<std::string, 6> units       = { "km", " ", "deg", "deg", "deg", "deg" };
    const std::array<std::string, 6> tickformats = { "%0.2e", "%0.2e", "%0.2e", "%0.2e", "%0.2e", "%0.2e" };

    tiledlayout(nPlots, 1);

    const std::vector<double> time                        = extract_raw_time_data(expected);
    const std::array<std::vector<double>, 6> expectedData = extract_raw_orbital_elements(expected);
    for (std::size_t iPlot = 0; iPlot < nPlots; ++iPlot) {

        nexttile();
        auto ax = gca();

        double minTime     = std::numeric_limits<double>::max();
        double maxTime     = std::numeric_limits<double>::lowest();
        unsigned int iTraj = 0;
        for (const auto& trajectory : trajectories) {
            const std::array<std::vector<double>, 6> data = extract_raw_orbital_elements_at_times(time, trajectory);

            std::array<std::vector<double>, 6> diff;
            for (std::size_t ii = 0; ii < 6; ++ii) {
                for (std::size_t jj = 0; jj < data[ii].size(); ++jj) {
                    diff[ii].push_back(data[ii][jj] - expectedData[ii][jj]);
                }
            }

            if (time.front() < minTime) { minTime = time.front(); }
            if (time.back() > maxTime) { maxTime = time.back(); }

            auto p = plot(ax, time, diff[iPlot]);
            p->line_width(10.0 - iTraj);
            hold(on);
            ++iTraj;
        }

        legend(ax, trajLabels);
        grid(ax, on);

        xlim(ax, { minTime, maxTime });

        ylabel(ax, labels[iPlot] + " \\n(" + units[iPlot] + ")");
        ytickformat(ax, tickformats[iPlot]);
        if (iPlot == nPlots - 1) {
            xlabel(ax, "Time");
            xtickformat(ax, "%g days");
            ax->x_axis().label_font_size(size);
            ax->x_axis().label_weight("bold");
        }

        ax->font_size(size);
        ax->y_axis().label_font_size(size);
        ax->y_axis().label_weight("bold");
    }
    std::filesystem::create_directories(outfile.parent_path());
    save(outfile);
}

void plot_difference_trajectories(
    const StateHistory expected,
    const std::vector<StateHistory>& trajectories,
    const std::vector<std::string>& trajLabels,
    const std::filesystem::path& outfile
)
{
    const auto font  = "Arial";
    const float size = 20.0;

    auto h = figure(true);
    h->title("State History");
    h->number_title(false);
    h->size(4000, 3000);
    h->font(font);
    h->font_size(size + 5.0);

    const std::array<std::string, 6> labels = { "ΔX", "ΔY", "ΔZ", "ΔVX", "ΔVY", "ΔVZ" };
    const std::array<std::string, 6> units  = { "km", "km/s" };

    const std::vector<double> time                        = extract_raw_time_data(expected);
    const std::array<std::vector<double>, 6> expectedData = extract_raw_cartesian_elements(expected);
    for (std::size_t iPlot = 0; iPlot < 2; ++iPlot) {
        // 3-D trajectory plots
        auto ax = subplot(2, 2, iPlot);

        unsigned int iTraj = 0;
        for (const auto& trajectory : trajectories) {
            const std::array<std::vector<double>, 6> data = extract_raw_cartesian_elements_at_times(time, trajectory);

            std::array<std::vector<double>, 6> diff;
            for (std::size_t ii = 0; ii < 6; ++ii) {
                diff[ii].reserve(data[ii].size());
                for (std::size_t jj = 0; jj < data[ii].size(); ++jj) {
                    diff[ii].push_back(data[ii][jj] - expectedData[ii][jj]);
                }
            }

            auto p = plot3(ax, diff[3 * iPlot], diff[3 * iPlot + 1], diff[3 * iPlot + 2]);
            p->line_width(10.0 - iTraj);
            hold(on);
            ++iTraj;
        }

        legend(ax, trajLabels);
        grid(ax, on);

        xlabel(ax, labels[3 * iPlot] + " \\n(" + units[iPlot] + ")");
        ylabel(ax, labels[3 * iPlot + 1] + " \\n(" + units[iPlot] + ")");
        zlabel(ax, labels[3 * iPlot + 2] + " \\n(" + units[iPlot] + ")");

        xtickformat(ax, "%0.2e");
        ytickformat(ax, "%0.2e");
        ztickformat(ax, "%0.2e");

        ax->font_size(size);
        ax->x_axis().label_font_size(size);
        ax->x_axis().label_weight("bold");
        ax->y_axis().label_font_size(size);
        ax->y_axis().label_weight("bold");
        ax->z_axis().label_font_size(size);
        ax->z_axis().label_weight("bold");

        // magnitude plots
        ax    = subplot(2, 2, iPlot + 2);
        iTraj = 0;
        for (const auto& trajectory : trajectories) {
            std::array<std::vector<double>, 6> data = extract_raw_cartesian_elements_at_times(time, trajectory);
            const Date epoch                        = trajectory.epoch();

            std::vector<double> dR;
            std::vector<double> dV;
            for (std::size_t ii = 0; ii < time.size(); ++ii) {
                const double dx  = data[0][ii] - expectedData[0][ii];
                const double dy  = data[1][ii] - expectedData[1][ii];
                const double dz  = data[2][ii] - expectedData[2][ii];
                const double dvx = data[3][ii] - expectedData[3][ii];
                const double dvy = data[4][ii] - expectedData[4][ii];
                const double dvz = data[5][ii] - expectedData[5][ii];
                dR.push_back(sqrt(dx * dx + dy * dy + dz * dz));
                dV.push_back(sqrt(dvx * dvx + dvy * dvy + dvz * dvz));
            }
            auto p = plot(ax, time, iPlot == 0 ? dR : dV);
            p->line_width(10.0 - iTraj);
            hold(on);
            ++iTraj;
        }

        legend(ax, trajLabels);
        grid(ax, on);

        xlabel(ax, "Time");
        xtickformat(ax, "%g days");
        ylabel(ax, iPlot == 0 ? "Δ Range \\n(km)" : "Δ Velocity \\n(km/s)");

        xtickformat(ax, "%g");
        ytickformat(ax, "%0.2e");

        ax->font_size(size);
        ax->x_axis().label_font_size(size);
        ax->x_axis().label_weight("bold");
        ax->y_axis().label_font_size(size);
        ax->y_axis().label_weight("bold");
    }
    std::filesystem::create_directories(outfile.parent_path());
    save(outfile);
}

} // namespace plotting
} // namespace astro
} // namespace astrea
```


