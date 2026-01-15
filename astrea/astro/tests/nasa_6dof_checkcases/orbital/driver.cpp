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

#include <numbers>

#include <gtest/gtest.h>
#include <matplot/matplot.h>
#include <mp-units/math.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/angular/math.h>

#include <math/operations.hpp>
#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/propagation/equations_of_motion/KeplerianVop.hpp>
#include <astro/propagation/equations_of_motion/TwoBody.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/propagation/numerical/Integrator.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <astro/time/Interval.hpp>
#include <astro/utilities/plotting.hpp>
#include <tests/utilities/comparisons.hpp>

#include <tests/nasa_6dof_checkcases/helpers/AtmosphericCheckcase.hpp>
#include <tests/nasa_6dof_checkcases/helpers/CheckcaseDatabase.hpp>
#include <tests/nasa_6dof_checkcases/helpers/OrbitalCheckcase.hpp>

using namespace astrea;
using namespace astro;
using namespace astro::tests;

using namespace sqlite_orm;
using namespace matplot;
using namespace mp_units;

using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::mm;
using mp_units::si::unit_symbols::s;

template <auto R, typename Rep>
class Stats {
  public:
    Stats()  = default;
    ~Stats() = default;

    Stats(const std::vector<quantity<R, Rep>>& data) :
        _data(data)
    {
    }

    Stats(std::vector<quantity<R, Rep>>&& data) :
        _data(std::move(data))
    {
    }

    quantity<R, Rep> mean() const
    {
        quantity<R, Rep> sum = 0.0 * R;
        for (const auto& val : _data) {
            sum += val;
        }
        return sum / static_cast<Rep>(_data.size());
    }

    quantity<R, Rep> stddev() const
    {
        const quantity<R, Rep> mu = mean();
        quantity<R * R, Rep> sum  = 0.0 * R * R;
        for (const auto& val : _data) {
            sum += (val - mu) * (val - mu);
        }
        return mp_units::sqrt(sum / static_cast<Rep>(_data.size() - 1));
    }

    quantity<R, Rep> max() const
    {
        quantity<R, Rep> maxVal = _data[0];
        for (const auto& val : _data) {
            if (val > maxVal) { maxVal = val; }
        }
        return maxVal;
    }

    quantity<R, Rep> min() const
    {
        quantity<R, Rep> minVal = _data[0];
        for (const auto& val : _data) {
            if (val < minVal) { minVal = val; }
        }
        return minVal;
    }

    template <auto R2>
    void add_value(const quantity<R2, Rep>& value)
    {
        _data.push_back(value);
    }

  private:
    std::vector<quantity<R, Rep>> _data;
};

class Orbital6DofTest : public testing::Test {
  public:
    Orbital6DofTest() :
        sys(),
        mu(sys.get_mu()),
        epoch("2007/324:00:00:00", "%Y/%j:%H:%M:%S"),
        circular(
            RadiusVector<frames::earth::icrf>(-4292.65341 * km, 955.16847 * km, 5139.35657 * km),
            VelocityVector<frames::earth::icrf>(0.109649663 * km / s, -7.527726490 * km / s, 1.484521489 * km / s)
        ),
        elliptic(
            RadiusVector<frames::earth::icrf>(-4315.96774 * km, 960.35620 * km, 5167.26953 * km),
            VelocityVector<frames::earth::icrf>(0.129091037 * km / s, -7.491513855 * km / s, 1.452515654 * km / s)
        ),
        propInterval(0.0 * s, 28800.0 * s)
    {
        integrator.switch_fixed_timestep(true);
        integrator.set_timestep(60.0 * s);
        integrator.set_abs_tol(1.0e-13);
        integrator.set_rel_tol(1.0e-13);

        outputDir = std::getenv("ASTREA_ROOT");
        outputDir /= "astrea/astro/tests/nasa_6dof_checkcases/orbital/results";
    }

    void SetUp() override {}

    const State parse_row_as_state(const OrbitalCheckcaseRow& row) const
    {
        const Time time = std::round(row.time) * s;
        const RadiusVector<frames::earth::icrf> position(row.eiPosition_m_X * m, row.eiPosition_m_Y * m, row.eiPosition_m_Z * m);
        const VelocityVector<frames::earth::icrf> velocity(row.eiVelocity_m_s_X * m / s, row.eiVelocity_m_s_Y * m / s, row.eiVelocity_m_s_Z * m / s);
        return State({ Cartesian(position, velocity) }, epoch + time, sys);
    }

    const Unitless REL_TOL = 1.0e-6;
    const Unitless ABS_TOL = 1.0e-2;

    std::filesystem::path outputDir;

    AstrodynamicsSystem sys;
    GravParam mu;
    Date epoch;
    Cartesian circular;
    Cartesian elliptic;
    Interval propInterval;
    Integrator integrator;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(Orbital6DofTest, Checkcase2Propagation)
{
    // Circular initial conditions
    Spacecraft sat({ Keplerian(circular, mu), epoch, sys });
    Vehicle vehicle{ sat };

    // Setup Propagator
    ForceModel forces;
    TwoBody cartesianTwoBody(sys);
    KeplerianVop keplerianVop(sys, forces, false);

    const auto stateHistory = integrator.propagate(epoch, propInterval, cartesianTwoBody, vehicle, true);
    // const auto stateHistory = integrator.propagate(epoch, propInterval, keplerianVop, vehicle, true);
    auto ccdb = get_checkcase_database();
    ccdb.sync_schema();

    auto checkcases = ccdb.get_all<OrbitalCheckcase>(where(like(&OrbitalCheckcase::name, "Orbit_02%%")));
    std::cout << "Validating Checkcase 2 against " << checkcases.size() << " simulations." << std::endl;

    std::vector<StateHistory> allHistories;
    allHistories.reserve(checkcases.size() + 1);
    allHistories.push_back(stateHistory); // first history is propagated history

    std::vector<std::string> allLabels;
    allLabels.reserve(checkcases.size() + 1);
    allLabels.push_back("Astrea Propagation");

    StateHistory analyticHistory;
    for (const auto& checkcase : checkcases) {
        auto rows = ccdb.get_all<OrbitalCheckcaseRow>(where(
            c(&OrbitalCheckcaseRow::checkcase_num) == checkcase.checkcase_num &&
            c(&OrbitalCheckcaseRow::sim_num) == checkcase.sim_num
        ));
        if (rows.size() == 0) { continue; }

        std::cout << "\tSimulation " << checkcase.sim_num << ":" << std::endl;

        Stats<m, double> rStats;
        Stats<(mm / s), double> vStats;
        StateHistory expectedHistory;
        for (const auto& row : rows) {
            // Pull out propagated state at time
            const State state       = parse_row_as_state(row);
            const Date currentEpoch = state.get_epoch();
            const Cartesian cart    = state.in_element_set<Cartesian>();
            const auto pos          = cart.get_position();
            const auto vel          = cart.get_velocity();

            const State propState    = stateHistory.get_state_at(currentEpoch);
            const Cartesian propCart = propState.in_element_set<Cartesian>();
            const auto propPos       = propCart.get_position();
            const auto propVel       = propCart.get_velocity();

            // Store
            expectedHistory.insert(currentEpoch, state);

            // Compare
            const auto positionError    = propPos - pos;
            const auto positionErrorMag = positionError.norm();

            const auto velocityError    = propVel - vel;
            const auto velocityErrorMag = velocityError.norm();

            // Stats
            rStats.add_value(positionErrorMag);
            vStats.add_value(velocityErrorMag);
        }

        std::cout << "\t\tPosition Error [avg, max]: [" << rStats.mean() << " ± " << rStats.stddev() << ", "
                  << rStats.max() << "]" << std::endl;
        std::cout << "\t\tVelocity Error [avg, max]: [" << vStats.mean() << " ± " << vStats.stddev() << ", "
                  << vStats.max() << "]" << std::endl;

        if (checkcase.sim_num == 0) { analyticHistory = expectedHistory; }
        else {
            allHistories.push_back(expectedHistory);
            allLabels.push_back("Checkcase Sim " + std::to_string(checkcase.sim_num));
        }
    }

    // Plot
    const auto base = outputDir / "checkcase_2";

    plotting::plot_difference_orbital_elements(analyticHistory, allHistories, allLabels, base / "orbital_elements_difference.png");
    plotting::plot_difference_trajectories(analyticHistory, allHistories, allLabels, base / "trajectory_difference.png");

    allHistories.push_back(analyticHistory);
    allLabels.push_back("Analytic Solution");

    plotting::compare_orbital_elements(allHistories, allLabels, base / "orbital_elements_comparison.png");
    plotting::compare_trajectories(allHistories, allLabels, base / "trajectory_comparison.png");
}
