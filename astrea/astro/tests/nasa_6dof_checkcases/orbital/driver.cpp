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
using mp_units::si::unit_symbols::cm;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;


class Orbital6DofTest : public testing::Test {
  public:
    Orbital6DofTest() :
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
        integrator.set_timestep(30.0 * s);
        integrator.set_abs_tol(1.0e-13);
        integrator.set_rel_tol(1.0e-13);

        outputDir = std::getenv("ASTREA_ROOT");
        outputDir /= "astrea/astro/tests/nasa_6dof_checkcases/orbital/results";
    }

    void SetUp() override {}

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
    Spacecraft sat({ Cartesian(circular, mu), epoch, sys });
    Vehicle vehicle{ sat };

    // Setup Propagator
    ForceModel forces;
    TwoBody eom(sys);
    KeplerianVop keplerianVop(sys, forces, false);

    std::cout << "Propagating Checkcase 2...";
    const auto stateHistory = integrator.propagate(epoch, propInterval, keplerianVop, vehicle, true);
    std::cout << " Propagation Complete." << std::endl << std::endl;

    // Grab history from database
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

    for (const auto& checkcase : checkcases) {
        auto rows = ccdb.get_all<OrbitalCheckcaseRow>(where(
            c(&OrbitalCheckcaseRow::checkcase_num) == checkcase.checkcase_num &&
            c(&OrbitalCheckcaseRow::sim_num) == checkcase.sim_num
        ));
        if (rows.size() == 0) { continue; }

        std::cout << "\tValidating against " << rows.size() << " points in Simulation " << checkcase.sim_num << std::endl;
        Distance avgPositionError = 0.0 * km;
        Distance maxPositionError = 0.0 * km;
        Velocity avgVelocityError = 0.0 * km / s;
        Velocity maxVelocityError = 0.0 * km / s;

        StateHistory expectedHistory;
        for (const auto& row : rows) {

            // Pull out propagated state at time
            const Time time             = std::round(row.time) * s;
            const State propagatedState = stateHistory.get_state_at(epoch + time);
            const Cartesian cart        = propagatedState.in_element_set<Cartesian>();

            const RadiusVector<frames::earth::icrf> pos(row.eiPosition_m_X * m, row.eiPosition_m_Y * m, row.eiPosition_m_Z * m);
            const auto positionError    = cart.get_position() - pos;
            const auto positionErrorMag = positionError.norm();

            const VelocityVector<frames::earth::icrf> vel(row.eiVelocity_m_s_X * m / s, row.eiVelocity_m_s_Y * m / s, row.eiVelocity_m_s_Z * m / s);
            const auto velocityError    = cart.get_velocity() - vel;
            const auto velocityErrorMag = velocityError.norm();

            // Store
            expectedHistory.insert(epoch + time, State({ Cartesian(pos, vel) }, epoch + time, sys));

            // Stats
            maxPositionError = math::max(maxPositionError, positionErrorMag);
            maxVelocityError = math::max(maxVelocityError, velocityErrorMag);
            avgPositionError += positionErrorMag;
            avgVelocityError += velocityErrorMag;
        }
        avgPositionError /= static_cast<double>(rows.size());
        avgVelocityError /= static_cast<double>(rows.size());

        std::cout << "\t\tAverage Position Error: " << avgPositionError.in(m) << std::endl;
        std::cout << "\t\tMaximum Position Error: " << maxPositionError.in(m) << std::endl;
        std::cout << "\t\tAverage Velocity Error: " << avgVelocityError.in(cm / s) << std::endl;
        std::cout << "\t\tMaximum Velocity Error: " << maxVelocityError.in(cm / s) << std::endl;

        allHistories.push_back(expectedHistory);
        allLabels.push_back("Checkcase Sim " + std::to_string(checkcase.sim_num));
    }

    // Build out exact results to compare
    StateHistory analyticHistory;
    const Keplerian elements0(circular, mu);
    for (const auto& [date, state] : stateHistory) {
        // this ignores anomaly changes but whatever
        analyticHistory.insert(date, State({ elements0 }, date, sys));
    }
    allHistories.push_back(analyticHistory);
    allLabels.push_back("Analytic Solution");

    plotting::compare_trajectories(allHistories, allLabels, outputDir / "checkcase_2" / "trajectory_comparison.png");
    plotting::compare_orbital_elements(allHistories, allLabels, outputDir / "checkcase_2" / "orbital_elements_comparison.png");
}
