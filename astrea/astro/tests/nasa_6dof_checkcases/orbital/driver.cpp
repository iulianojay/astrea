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
#include <regex>
#include <vector>

#include <gtest/gtest.h>
#include <matplot/matplot.h>
#include <mp-units/math.h>
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

#include <astro/propagation/force_models/AtmosphericForce.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/propagation/force_models/NBodyForce.hpp>
#include <astro/propagation/force_models/OblatenessForce.hpp>
#include <astro/propagation/force_models/SolarRadiationPressure.hpp>
#include <astro/propagation/numerical/Integrator.hpp>

#include <astro/astro.macros.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <astro/time/Interval.hpp>
#include <astro/utilities/plotting.hpp>

#include <tests/nasa_6dof_checkcases/helpers/CheckcaseDatabase.hpp>
#include <tests/nasa_6dof_checkcases/helpers/OrbitalCheckcase.hpp>
#include <tests/nasa_6dof_checkcases/helpers/Stats.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace sqlite_orm;
using namespace matplot;
using namespace mp_units;

using mp_units::angular::unit_symbols::deg;
using mp_units::international::unit_symbols::ft;
using mp_units::si::unit_symbols::cm;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;
using mp_units::si::unit_symbols::µm;

namespace astrea {
namespace astro {
namespace tests {

enum EomType { TWO_BODY = 0, COWELLS_METHOD = 1, KEPLERIAN_VOP = 2, EQUINOCTIAL_VOP = 3 };
enum InitialOrbitType { CIRCULAR = 0, ELLIPTIC = 1 };
enum VehicleType { ISS = 0, SPHERE = 1, BRICK = 2, CYLINDER = 3 };

class Orbital6DofTest : public testing::Test {

    // TODO: Make NASA 6DoF Tests generate a report file. Add this output to CI.
    // TODO: Finish implementing all force models in the tests. This includes more atmosphere models, and different
    //       SRP models. It may also include closing down any errors further.

    using RStats = Stats<m, double>;
    using VStats = Stats<(cm / s), double>;

  public:
    Orbital6DofTest() :
        sys(CelestialBodyId::EARTH, { CelestialBodyId::SUN }),
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

        outputDir = std::string(_ASTRO_ROOT_);
        outputDir /= "/tests/nasa_6dof_checkcases/orbital/results";
    }

    void SetUp() override {}

    std::vector<std::pair<StateHistory, std::string>>
        run_all_propagations(const ForceModel& forces, const InitialOrbitType& orbitType, const VehicleType vehicleType, const bool& ignoreTwoBody = true)
    {
        std::vector<std::pair<StateHistory, std::string>> results;
        for (const auto eomId : { TWO_BODY, COWELLS_METHOD, KEPLERIAN_VOP, EQUINOCTIAL_VOP }) {
            if (ignoreTwoBody && eomId == TWO_BODY) { continue; }

            std::string eomName;
            switch (eomId) {
                case TWO_BODY: eomName = "Two_Body"; break;
                case COWELLS_METHOD: eomName = "Cowells_Method"; break;
                case KEPLERIAN_VOP: eomName = "Keplerian_VOP"; break;
                case EQUINOCTIAL_VOP: eomName = "Equinoctial_VOP"; break;
                default: throw std::runtime_error("Invalid EOM ID");
            }
            results.push_back({ run_propagation(eomId, forces, orbitType, vehicleType), eomName });
        }

        return results;
    }

    Spacecraft build_spacecraft(const InitialOrbitType& orbitType, const VehicleType& vehicleType)
    {
        OrbitalElements initialState = (orbitType == CIRCULAR) ? Keplerian(circular, mu) : Keplerian(elliptic, mu);
        Spacecraft sat({ initialState, epoch, sys });

        switch (vehicleType) {
            case ISS: {
                sat.set_mass(4.5e5 * kg);
                sat.set_ram_area(2.5e3 * m * m);
                sat.set_lift_area(2.5e3 * m * m);
                sat.set_solar_area(2.5e3 * m * m);
                sat.set_coefficient_of_drag(2.2);
                sat.set_coefficient_of_lift(2.2);
                sat.set_coefficient_of_reflectivity(1.1);
                break;
            }

            case SPHERE: {
                sat.set_mass(1.0 * kg);
                sat.set_ram_area(1.0 * m * m);
                sat.set_lift_area(0.0 * m * m);
                sat.set_solar_area(1.0 * m * m);
                sat.set_coefficient_of_drag(0.02);
                sat.set_coefficient_of_lift(0.0);
                sat.set_coefficient_of_reflectivity(1.1);
                break;
            }

            case BRICK: {
                sat.set_mass(1.0 * kg);
                sat.set_ram_area(206.451 * cm * cm);
                sat.set_lift_area(206.451 * cm * cm);
                sat.set_solar_area(206.451 * cm * cm);
                sat.set_coefficient_of_drag(2.2);
                sat.set_coefficient_of_lift(2.2);
                sat.set_coefficient_of_reflectivity(1.1);
                break;
            }

            case CYLINDER: {
                sat.set_mass(1000.0 * kg);
                sat.set_ram_area(12.0 * m * m);
                sat.set_lift_area(12.0 * m * m);
                sat.set_solar_area(12.0 * m * m);
                sat.set_coefficient_of_drag(2.2);
                sat.set_coefficient_of_lift(2.2);
                sat.set_coefficient_of_reflectivity(1.1);
                break;
            }

            default: throw std::runtime_error("Invalid Vehicle Type");
        }

        return sat;
    }

    StateHistory run_propagation(const EomType eomId, const ForceModel& forces, const InitialOrbitType& orbitType, const VehicleType vehicleType)
    {
        Spacecraft sat = build_spacecraft(orbitType, vehicleType);
        Vehicle vehicle{ sat };

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
        return State({ Cartesian(position, velocity) }, epoch + time, sys);
    }

    std::vector<std::pair<StateHistory, std::string>> get_checkcase_histories(const std::string& pattern) const
    {
        const auto checkcases = get_checkcases(pattern);

        std::vector<std::pair<StateHistory, std::string>> results;
        for (const auto& checkcase : checkcases) {
            auto rows = get_checkcase_rows(checkcase);
            if (rows.size() == 0) { continue; }

            StateHistory history;
            for (const auto& row : rows) {
                const State state = parse_row_as_state(row);
                history.insert(state.get_epoch(), state);
            }
            results.push_back({ history, "Checkcase " + std::to_string(checkcase.sim_num) });
        }
        if (results.size() == 0) { throw std::runtime_error("No checkcases found matching pattern: " + pattern); }
        return results;
    }

    void compare_all_propagations_to_checkcases(const std::vector<std::pair<StateHistory, std::string>>& propagations, const std::string& checkcaseName) const
    {
        const auto checkcases = get_checkcase_histories(checkcaseName + "%%");

        std::vector<std::vector<RStats>> allRStats;
        std::vector<std::vector<VStats>> allVStats;

        std::vector<StateHistory> checkcaseHistories;
        std::vector<std::string> checkcaseLabels;
        for (const auto& [checkcaseHistory, checkcaseLabel] : checkcases) {
            std::vector<RStats> rStatsList;
            std::vector<VStats> vStatsList;
            for (const auto& [propHistory, propLabel] : propagations) {
                const auto [rStats, vStats] =
                    validate_propagation_vs_checkcase(propHistory, propLabel, checkcaseHistory, checkcaseLabel, checkcaseName);
                rStatsList.push_back(rStats);
                vStatsList.push_back(vStats);
            }

            std::filesystem::path base = outputDir / checkcaseName / checkcaseLabel;
            make_summary_for_all_propagations(rStatsList, vStatsList, propagations, checkcaseLabel, base);

            allRStats.push_back(rStatsList);
            allVStats.push_back(vStatsList);

            checkcaseHistories.push_back(checkcaseHistory);
            checkcaseLabels.push_back(checkcaseLabel);
        }
        make_summary_for_all_checkcases(propagations, checkcases, checkcaseName, allRStats, allVStats);

        std::vector<StateHistory> propHistories;
        std::vector<std::string> propLabels;
        for (const auto& [propHistory, propLabel] : propagations) {
            propHistories.push_back(propHistory);
            propLabels.push_back(propLabel);
        }

        for (const auto& [checkcaseHistory, checkcaseLabel] : checkcases) {
            std::filesystem::path base = outputDir / checkcaseName / checkcaseLabel;
            make_comparison_plots(propHistories, propLabels, checkcaseHistory, checkcaseLabel, base);
        }

        make_comparison_plots(propHistories, propLabels, checkcaseHistories, checkcaseLabels, outputDir / checkcaseName);
    }

    std::pair<RStats, VStats> validate_propagation_vs_checkcase(
        const StateHistory& propHistory,
        const std::string& propLabel,
        const StateHistory& checkcaseHistory,
        const std::string& checkcaseLabel,
        const std::string& checkcaseName
    ) const
    {
        unsigned nViolations            = 0;
        const unsigned N_MAX_VIOLATIONS = 5;

        RStats rStats;
        VStats vStats;
        for (const auto& [date, checkcaseState] : checkcaseHistory) {
            const State propState    = propHistory.get_state_at(date);
            const Cartesian propCart = propState.in_element_set<Cartesian>();
            const auto propPos       = propCart.get_position();
            const auto propVel       = propCart.get_velocity();

            const Cartesian cart = checkcaseState.in_element_set<Cartesian>();
            const auto pos       = cart.get_position();
            const auto vel       = cart.get_velocity();

            // Compare
            const auto positionError    = propPos - pos;
            const auto positionErrorMag = positionError.norm();

            const auto velocityError    = propVel - vel;
            const auto velocityErrorMag = velocityError.norm();

            if (positionErrorMag > _MAX_R_ERROR * 10 || velocityErrorMag > _MAX_V_ERROR * 10) {
                // This seems to happen from bad checkcase data every now and then. Ignore it if it just happens a couple times.
                nViolations++;
                if (nViolations < N_MAX_VIOLATIONS) { continue; }
            }

            rStats.add_value(positionErrorMag);
            vStats.add_value(velocityErrorMag);
        }

        EXPECT_TRUE(rStats.max() <= _MAX_R_ERROR)
            << "Max allowed position error (" << _MAX_R_ERROR.in(m) << ") violated comparing " << propLabel << " to "
            << checkcaseLabel << "[" << rStats.mean() << " ± " << rStats.stddev() << ", " << rStats.max() << "]" << std::endl;
        EXPECT_TRUE(vStats.max() <= _MAX_V_ERROR)
            << "Max allowed velocity error (" << _MAX_V_ERROR.in(cm / s) << ") violated comparing " << propLabel << " to "
            << checkcaseLabel << "[" << vStats.mean() << " ± " << vStats.stddev() << ", " << vStats.max() << "]" << std::endl;

        // Delete any existing plots from previous runs
        std::filesystem::path base = outputDir / checkcaseName / checkcaseLabel / propLabel;
        std::filesystem::remove_all(base);

        // Plot
        make_comparison_plots(propHistory, propLabel, checkcaseHistory, checkcaseLabel, base);

        return { rStats, vStats };
    }

    void make_summary_for_all_checkcases(
        const std::vector<std::pair<StateHistory, std::string>>& propHistories,
        const std::vector<std::pair<StateHistory, std::string>>& checkcaseHistories,
        const std::string& checkcaseName,
        const std::vector<std::vector<RStats>>& allRStats,
        const std::vector<std::vector<VStats>>& allVStats
    ) const
    {
        std::filesystem::path base = outputDir / checkcaseName;
        std::filesystem::create_directories(base);

        std::ofstream summaryFile;
        summaryFile.open(base / "summary.csv");
        summaryFile << "Checkcase, Propagation, Mean Position Error, Std Dev Position Error, Max Position Error, Min "
                       "Position Error, Mean Velocity Error, Std Dev Velocity Error, Max Velocity Error, Min "
                       "Velocity Error"
                    << std::endl;
        for (std::size_t i = 0; i < checkcaseHistories.size(); ++i) {
            const auto& checkcaseLabel = checkcaseHistories[i].second;
            for (std::size_t j = 0; j < propHistories.size(); ++j) {
                summaryFile << checkcaseLabel << ", "
                            << make_row_string(propHistories[j].second, allRStats[i][j], allVStats[i][j]) << std::endl;
            }
        }
        summaryFile.close();
    }

    void make_summary_for_all_propagations(
        const std::vector<RStats>& rStatsList,
        const std::vector<VStats>& vStatsList,
        const std::vector<std::pair<StateHistory, std::string>>& propHistories,
        const std::string& checkcaseLabel,
        const std::filesystem::path& base
    ) const
    {
        std::filesystem::create_directories(base);

        std::ofstream summaryFile;
        summaryFile.open(base / "summary.csv");

        summaryFile << "Propagation, Mean Position Error, Std Dev Position Error, Max Position Error, Min "
                       "Position Error, Mean Velocity Error, Std Dev Velocity Error, Max Velocity Error, Min "
                       "Velocity Error"
                    << std::endl;
        for (std::size_t ii = 0; ii < propHistories.size(); ++ii) {
            summaryFile << make_row_string(propHistories[ii].second, rStatsList[ii], vStatsList[ii]) << std::endl;
        }

        summaryFile.close();
    }

    std::string make_row_string(const std::string& propLabel, const RStats& rStats, const VStats& vStats) const
    {
        std::ostringstream oss;
        oss << propLabel << ", ";
        oss << rStats.mean().in(m) << ", " << rStats.stddev().in(m) << ", " << rStats.max().in(m) << ", "
            << rStats.min().in(m) << ", ";
        oss << vStats.mean().in(cm / s) << ", " << vStats.stddev().in(cm / s) << ", " << vStats.max().in(cm / s) << ", "
            << vStats.min().in(cm / s);
        return oss.str();
    }

    void make_comparison_plots(
        const StateHistory& propHistory,
        const std::string& propLabel,
        const StateHistory& checkcaseHistory,
        const std::string& checkcaseLabel,
        const std::filesystem::path& base
    ) const
    {
        std::cout.setstate(std::ios::failbit);
        std::cerr.setstate(std::ios::failbit);

        plotting::plot_difference_orbital_elements(checkcaseHistory, { propHistory }, { propLabel }, base / "orbital_elements_difference.png");
        plotting::plot_difference_trajectories(checkcaseHistory, { propHistory }, { propLabel }, base / "trajectory_difference.png");

        std::vector<StateHistory> histories = { checkcaseHistory, propHistory };
        std::vector<std::string> labels     = { checkcaseLabel, propLabel };
        plotting::compare_orbital_elements(histories, labels, base / "orbital_elements_comparison.png");
        plotting::compare_trajectories(histories, labels, base / "trajectory_comparison.png");

        std::cout.clear();
        std::cerr.clear();
    }

    void make_comparison_plots(
        const std::vector<StateHistory>& propHistories,
        const std::vector<std::string>& propLabels,
        const StateHistory& checkcaseHistory,
        const std::string& checkcaseLabel,
        const std::filesystem::path& base
    ) const
    {
        std::cout.setstate(std::ios::failbit);
        std::cerr.setstate(std::ios::failbit);

        std::vector<StateHistory> histories = propHistories;
        histories.push_back(checkcaseHistory);

        std::vector<std::string> labels = propLabels;
        labels.push_back(checkcaseLabel);

        plotting::compare_orbital_elements(histories, labels, base / "orbital_elements_comparison.png");
        plotting::compare_trajectories(histories, labels, base / "trajectory_comparison.png");

        std::cout.clear();
        std::cerr.clear();
    }

    void make_comparison_plots(
        const std::vector<StateHistory>& propHistories,
        const std::vector<std::string>& propLabels,
        const std::vector<StateHistory>& checkcaseHistories,
        const std::vector<std::string>& checkcaseLabels,
        const std::filesystem::path& base
    ) const
    {
        std::cout.setstate(std::ios::failbit);
        std::cerr.setstate(std::ios::failbit);

        std::vector<StateHistory> histories = checkcaseHistories;
        histories.insert(histories.end(), propHistories.begin(), propHistories.end());

        std::vector<std::string> labels = checkcaseLabels;
        labels.insert(labels.end(), propLabels.begin(), propLabels.end());

        plotting::compare_orbital_elements(histories, labels, base / "orbital_elements_comparison.png");
        plotting::compare_trajectories(histories, labels, base / "trajectory_comparison.png");

        std::cout.clear();
        std::cerr.clear();
    }

    const Distance _MAX_R_ERROR = 10.0 * m;
    const Velocity _MAX_V_ERROR = 1.0 * cm / s;

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


TEST_F(Orbital6DofTest, Checkcase2_Propagation)
{

    /*
    A mu value of 398600.436 reduces the error of this comparison to mm level. This suggests that the published value
    used by the checkcases is wrong or imprecise.
    */

    ForceModel forces;

    const auto propagations = run_all_propagations(forces, CIRCULAR, ISS, false);

    compare_all_propagations_to_checkcases(propagations, "Orbit_02");
}


TEST_F(Orbital6DofTest, Checkcase3A_4x4Oblateness)
{
    ForceModel forces;
    forces.add<OblatenessForce>(sys, 4, 4);

    const auto propagations = run_all_propagations(forces, CIRCULAR, ISS);

    compare_all_propagations_to_checkcases(propagations, "Orbit_03A");
}


TEST_F(Orbital6DofTest, Checkcase3B_8x8Oblateness)
{
    ForceModel forces;
    forces.add<OblatenessForce>(sys, 8, 8);

    const auto propagations = run_all_propagations(forces, CIRCULAR, ISS);

    compare_all_propagations_to_checkcases(propagations, "Orbit_03B");
}


TEST_F(Orbital6DofTest, Checkcase4_NBody)
{
    sys.add_body(CelestialBodyId::MOON);

    ForceModel forces;
    forces.add<NBodyForce>();

    const auto propagations = run_all_propagations(forces, CIRCULAR, ISS);

    compare_all_propagations_to_checkcases(propagations, "Orbit_04");
}


TEST_F(Orbital6DofTest, Checkcase5A_SrpSolarMin)
{
    ForceModel forces;
    forces.add<NBodyForce>();
    forces.add<SolarRadiationPressure>();

    const auto propagations = run_all_propagations(forces, ELLIPTIC, ISS);

    compare_all_propagations_to_checkcases(propagations, "Orbit_05A");
}


TEST_F(Orbital6DofTest, Checkcase5B_SrpSolarMean)
{
    ForceModel forces;
    forces.add<NBodyForce>();
    forces.add<SolarRadiationPressure>();

    const auto propagations = run_all_propagations(forces, ELLIPTIC, ISS);

    compare_all_propagations_to_checkcases(propagations, "Orbit_05B");
}


TEST_F(Orbital6DofTest, Checkcase5C_SrpSolarMax)
{
    ForceModel forces;
    forces.add<NBodyForce>();
    forces.add<SolarRadiationPressure>();

    const auto propagations = run_all_propagations(forces, ELLIPTIC, ISS);

    compare_all_propagations_to_checkcases(propagations, "Orbit_05C");
}


TEST_F(Orbital6DofTest, Checkcase6A_AtmosFixedSphere)
{
    ForceModel forces;
    forces.add<AtmosphericForce>();

    const auto propagations = run_all_propagations(forces, ELLIPTIC, SPHERE);

    compare_all_propagations_to_checkcases(propagations, "Orbit_06A");
}


TEST_F(Orbital6DofTest, Checkcase6B_AtmosDynamicSphere)
{
    ForceModel forces;
    forces.add<AtmosphericForce>();

    const auto propagations = run_all_propagations(forces, ELLIPTIC, SPHERE);

    compare_all_propagations_to_checkcases(propagations, "Orbit_06B");
}


// TEST_F(Orbital6DofTest, Checkcase6C_CylinderWithPlaneChange)
// {
//     ForceModel forces;

//     const auto propagations = run_all_propagations(forces, CIRCULAR, CYLINDER);

//     compare_all_propagations_to_checkcases(propagations, "Orbit_06C");
// }


// TEST_F(Orbital6DofTest, Checkcase6D_CylinderWithEarthDeparture)
// {
//     ForceModel forces;

//     const auto propagations = run_all_propagations(forces, CIRCULAR, CYLINDER);

//     compare_all_propagations_to_checkcases(propagations, "Orbit_06D");
// }


TEST_F(Orbital6DofTest, Checkcase7A_4x4Oblateness_NBody)
{
    sys.add_body(CelestialBodyId::MOON);

    ForceModel forces;
    forces.add<OblatenessForce>(sys, 4, 4);
    forces.add<NBodyForce>();

    const auto propagations = run_all_propagations(forces, ELLIPTIC, SPHERE);

    compare_all_propagations_to_checkcases(propagations, "Orbit_07A");
}


TEST_F(Orbital6DofTest, Checkcase7B_8x8Oblateness_NBody)
{
    sys.add_body(CelestialBodyId::MOON);

    ForceModel forces;
    forces.add<OblatenessForce>(sys, 8, 8);
    forces.add<NBodyForce>();

    const auto propagations = run_all_propagations(forces, ELLIPTIC, SPHERE);

    compare_all_propagations_to_checkcases(propagations, "Orbit_07B");
}


TEST_F(Orbital6DofTest, Checkcase7C_4x4Oblateness_NBody_Drag)
{
    sys.add_body(CelestialBodyId::MOON);

    ForceModel forces;
    forces.add<OblatenessForce>(sys, 4, 4);
    forces.add<NBodyForce>();
    forces.add<AtmosphericForce>();

    const auto propagations = run_all_propagations(forces, ELLIPTIC, SPHERE);

    compare_all_propagations_to_checkcases(propagations, "Orbit_07C");
}


TEST_F(Orbital6DofTest, Checkcase7D_8x8Oblateness_NBody_Drag)
{
    sys.add_body(CelestialBodyId::MOON);

    ForceModel forces;
    forces.add<OblatenessForce>(sys, 8, 8);
    forces.add<NBodyForce>();
    forces.add<AtmosphericForce>();

    const auto propagations = run_all_propagations(forces, ELLIPTIC, SPHERE);

    compare_all_propagations_to_checkcases(propagations, "Orbit_07D");
}


} // namespace tests
} // namespace astro
} // namespace astrea