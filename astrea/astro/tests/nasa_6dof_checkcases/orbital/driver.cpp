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
#include <mp-units/systems/international.h>

#include <math/operations.hpp>
#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/propagation/equations_of_motion/CowellsMethod.hpp>
#include <astro/propagation/equations_of_motion/EquinoctialVop.hpp>
#include <astro/propagation/equations_of_motion/J2MeanVop.hpp>
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

#include <regex>
#include <tests/nasa_6dof_checkcases/helpers/AtmosphericCheckcase.hpp>
#include <tests/nasa_6dof_checkcases/helpers/CheckcaseDatabase.hpp>
#include <tests/nasa_6dof_checkcases/helpers/OrbitalCheckcase.hpp>

using namespace sqlite_orm;
using namespace matplot;
using namespace mp_units;

using mp_units::angular::unit_symbols::deg;
using mp_units::international::unit_symbols::ft;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::mm;
using mp_units::si::unit_symbols::s;
using mp_units::si::unit_symbols::µm;

namespace astrea {
namespace astro {
namespace tests {

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

enum EomType { TWO_BODY = 0, COWELLS_METHOD = 1, KEPLERIAN_VOP = 2, EQUINOCTIAL_VOP = 3 };

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
        integrator.set_timestep(1.0 * s);
        integrator.set_abs_tol(1.0e-13);
        integrator.set_rel_tol(1.0e-13);

        outputDir = std::getenv("ASTREA_ROOT");
        outputDir /= "astrea/astro/tests/nasa_6dof_checkcases/orbital/results";
    }

    void SetUp() override {}

    std::pair<std::vector<StateHistory>, std::vector<std::string>> run_all_propagations()
    {
        std::vector<StateHistory> histories;
        std::vector<std::string> labels;
        for (const auto eomId : { TWO_BODY, COWELLS_METHOD, KEPLERIAN_VOP, EQUINOCTIAL_VOP }) {
            histories.push_back(run_propagation(eomId));

            std::string eomName;
            switch (eomId) {
                case TWO_BODY: eomName = "Two Body"; break;
                case COWELLS_METHOD: eomName = "Cowell's Method"; break;
                case KEPLERIAN_VOP: eomName = "Keplerian VOP"; break;
                case EQUINOCTIAL_VOP: eomName = "Equinoctial VOP"; break;
                default: eomName = "Unknown EOM"; break;
            }
            labels.push_back("Astrea Propagation - " + eomName);
        }

        return { histories, labels };
    }

    StateHistory run_propagation(const EomType eomId)
    {
        Spacecraft sat({ Keplerian(circular, mu), epoch, sys });
        Vehicle vehicle{ sat };

        // Setup Propagator
        ForceModel forces;

        switch (eomId) {
            case TWO_BODY: {
                TwoBody twoBody(sys);
                return integrator.propagate(epoch, propInterval, twoBody, vehicle, true);
            }

            case COWELLS_METHOD: {
                CowellsMethod cowells(sys, forces);
                return integrator.propagate(epoch, propInterval, cowells, vehicle, true);
            }

            case KEPLERIAN_VOP: {
                KeplerianVop keplerianVop(sys, forces, false);
                return integrator.propagate(epoch, propInterval, keplerianVop, vehicle, true);
            }

            case EQUINOCTIAL_VOP: {
                EquinoctialVop equinoctialVop(sys, forces);
                return integrator.propagate(epoch, propInterval, equinoctialVop, vehicle, true);
            }

            default: throw std::runtime_error("Invalid EOM ID");
        }
    }

    std::vector<OrbitalCheckcase> get_checkcases(const std::string& pattern) const
    {
        auto ccdb = get_checkcase_database();
        ccdb.sync_schema();
        return ccdb.get_all<OrbitalCheckcase>(where(like(&OrbitalCheckcase::name, pattern)));
    }

    std::vector<OrbitalCheckcaseRow> get_checkcase_rows(const OrbitalCheckcase& checkcase) const
    {
        auto ccdb = get_checkcase_database();
        ccdb.sync_schema();
        return ccdb.get_all<OrbitalCheckcaseRow>(where(
            c(&OrbitalCheckcaseRow::checkcase_num) == checkcase.checkcase_num &&
            c(&OrbitalCheckcaseRow::sim_num) == checkcase.sim_num
        ));
    }

    State parse_row_as_state(const OrbitalCheckcaseRow& row) const
    {
        const Time time = std::round(row.time) * s;
        const RadiusVector<frames::earth::icrf> position(row.eiPosition_m_X * m, row.eiPosition_m_Y * m, row.eiPosition_m_Z * m);
        const VelocityVector<frames::earth::icrf> velocity(row.eiVelocity_m_s_X * m / s, row.eiVelocity_m_s_Y * m / s, row.eiVelocity_m_s_Z * m / s);
        const AccelerationVector<frames::earth::icrf> acceleration(
            row.eiAccel_m_s2_X * m / (s * s), row.eiAccel_m_s2_Y * m / (s * s), row.eiAccel_m_s2_Z * m / (s * s)
        );
        return State({ Cartesian(position, velocity) }, CartesianPartial(velocity, acceleration), epoch + time, sys);
    }

    std::vector<StateHistory> get_checkcase_histories(const std::vector<OrbitalCheckcase>& checkcases) const
    {
        std::vector<StateHistory> histories;
        for (const auto& checkcase : checkcases) {
            auto rows = get_checkcase_rows(checkcase);
            if (rows.size() == 0) { continue; }

            StateHistory history;
            for (const auto& row : rows) {
                const State state = parse_row_as_state(row);
                history.insert(state.get_epoch(), state);
            }
            histories.push_back(history);
        }
        return histories;
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

/*
A mu value of 398600.436 reduces the error of this comparison to mm level. This suggests that the published value
used by the checkcases is wrong or imprecise.
*/


TEST_F(Orbital6DofTest, Checkcase2Propagation)
{
    std::cout << "mu: " << mu.in(mp_units::pow<3>(km) / mp_units::pow<2>(s)) << std::endl;
    std::cout << "mu: " << mu.in(mp_units::pow<3>(ft) / mp_units::pow<2>(s)) << std::endl;

    auto [histories, labels] = run_all_propagations();

    const auto checkcases = get_checkcases("Orbit_02%%");

    std::vector<StateHistory> checkcaseHistories = get_checkcase_histories(checkcases);

    std::cout << "Validating Checkcase 2 against " << checkcases.size() << " simulations." << std::endl;

    std::size_t propNum = 0;
    for (const auto& propHistory : histories) {

        std::cout << "\nPropagation " << labels[propNum] << std::endl;
        std::size_t checkcaseNum = 0;

        StateHistory analyticHistory;

        auto tempHistories = histories;
        auto tempLabels    = labels;
        for (const auto& checkcaseHistory : checkcaseHistories) {

            Stats<mm, double> rStats;
            Stats<(mm / s), double> vStats;
            // Stats<(µm / (s * s)), double> aStats;
            std::cout << "\t Checking checkcase " << checkcases[checkcaseNum].sim_num << "..." << std::endl;

            if (checkcases[checkcaseNum].sim_num == 0) { analyticHistory = propHistory; }
            else {
                tempHistories.push_back(checkcaseHistory);
                tempLabels.push_back("Checkcase " + std::to_string(checkcases[checkcaseNum].sim_num));
            }

            for (const auto& [date, state] : checkcaseHistory) {
                const State stateProp    = propHistory.get_state_at(date);
                const Cartesian propCart = stateProp.in_element_set<Cartesian>();
                const auto propPos       = propCart.get_position();
                const auto propVel       = propCart.get_velocity();
                // const auto propPartial   = stateProp.get_partials().value().extract();
                // const auto propAcc       = std::get<CartesianPartial>(propPartial).get_acceleration();

                const Cartesian cart = state.in_element_set<Cartesian>();
                const auto pos       = cart.get_position();
                const auto vel       = cart.get_velocity();
                // const auto partial      = state.get_partials().value().extract();
                //  const auto acc          = std::get<CartesianPartial>(partial).get_acceleration();

                // Compare
                const auto positionError    = propPos - pos;
                const auto positionErrorMag = positionError.norm();

                const auto velocityError    = propVel - vel;
                const auto velocityErrorMag = velocityError.norm();

                // const auto accelerationError    = propAcc - acc;
                // const auto accelerationErrorMag = accelerationError.norm();

                if (positionErrorMag > 100.0 * m) { continue; }

                rStats.add_value(positionErrorMag);
                vStats.add_value(velocityErrorMag);
                // aStats.add_value(accelerationErrorMag);
            }

            std::cout << "\t\tPosition Error [avg, max]: [" << rStats.mean() << " ± " << rStats.stddev() << ", "
                      << rStats.max() << "]" << std::endl;
            std::cout << "\t\tVelocity Error [avg, max]: [" << vStats.mean() << " ± " << vStats.stddev() << ", "
                      << vStats.max() << "]" << std::endl;
            // std::cout << "\t\tAcceleration Error [avg, max]: [" << aStats.mean() << " ± " << aStats.stddev() << ", "
            //           << aStats.max() << "]" << std::endl;

            checkcaseNum++;
        }

        // // Plot
        // std::string name = std::regex_replace(labels[propNum], std::regex(" "), "_");
        // name             = std::regex_replace(name, std::regex("-"), "");
        // name             = std::regex_replace(name, std::regex("__"), "_");
        // name             = std::regex_replace(name, std::regex("Astrea_Propagation_"), "");
        // const auto base  = outputDir / "checkcase_2" / name;

        // plotting::plot_difference_orbital_elements(analyticHistory, tempHistories, tempLabels, base / "orbital_elements_difference.png");
        // plotting::plot_difference_trajectories(analyticHistory, tempHistories, tempLabels, base / "trajectory_difference.png");

        // histories.push_back(analyticHistory);
        // labels.push_back("Analytic Solution");

        // plotting::compare_orbital_elements(histories, labels, base / "orbital_elements_comparison.png");
        // plotting::compare_trajectories(histories, labels, base / "trajectory_comparison.png");

        propNum++;
    }
}

} // namespace tests
} // namespace astro
} // namespace astrea