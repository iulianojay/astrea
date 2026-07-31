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

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/equations_of_motion/StateTransitionMatrix.hpp>
#include <astro/propagation/numerical/Integrator.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/time/Date.hpp>
#include <astro/time/Interval.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::s;

class DummyEOM : public EquationsOfMotion {
  public:
    OrbitalElementPartials
        compute_dynamics(const State&, const Vehicle&, const ForceVector<frames::earth::icrf>&, const ForceVector<frames::earth::icrf>&) const override
    {
        return OrbitalElementPartials();
    }

    StateTransitionMatrix compute_stm(const State& state, const Vehicle& vehicle) const override
    {
        return StateTransitionMatrix();
    }

    constexpr std::size_t get_expected_set_id() const override { return 0; }

    std::unique_ptr<EquationsOfMotion> clone() const override { return std::make_unique<DummyEOM>(*this); }
};

struct SimpleTestEvent {
    std::string get_name() const { return "Test Event"; }
    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const
    {
        return 42.0 * mp_units::one;
    }
    bool is_terminal() const { return false; }
    void trigger_action(const Time& time, State& state, Vehicle& vehicle) const {}
};

class IntegratorTest : public ::testing::Test {
  public:
    IntegratorTest() {}

    void SetUp() override {}

    Date epoch;
    Vehicle vehicle;
    State state;
    Time propTime{ days(1) };
    DummyEOM eom;
};

TEST_F(IntegratorTest, DefaultConstructorDestructor) { ASSERT_NO_THROW(Integrator integrator); }

TEST_F(IntegratorTest, SetToleranceAndOptions)
{
    Integrator integrator;
    EXPECT_NO_THROW(integrator.set_abs_tol(1e-10));
    EXPECT_NO_THROW(integrator.set_rel_tol(1e-10));
    EXPECT_NO_THROW(integrator.set_max_iter(1000));
}

TEST_F(IntegratorTest, SetStepMethod)
{
    Integrator integrator;
    EXPECT_NO_THROW(integrator.set_step_method(StepMethod::RK45));
    EXPECT_NO_THROW(integrator.set_step_method(StepMethod::RKF45));
    EXPECT_NO_THROW(integrator.set_step_method(StepMethod::RKF78));
    EXPECT_NO_THROW(integrator.set_step_method(StepMethod::DOP45));
    EXPECT_NO_THROW(integrator.set_step_method(StepMethod::DOP78));
}

TEST_F(IntegratorTest, SetInitialAndFixedTimestep)
{
    Integrator integrator;
    Time dt0 = 60.0 * s;
    EXPECT_NO_THROW(integrator.set_initial_timestep(dt0));
    EXPECT_NO_THROW(integrator.switch_fixed_timestep(true));
    EXPECT_NO_THROW(integrator.switch_fixed_timestep(true, dt0));
    EXPECT_NO_THROW(integrator.set_timestep(dt0));
}

TEST_F(IntegratorTest, PropagateFixedStep)
{
    Integrator integrator;
    integrator.switch_fixed_timestep(true, 60.0 * s);
    integrator.set_equations_of_motion(eom);
    EXPECT_NO_THROW({ auto history = integrator.propagate(state, propTime, vehicle); });
}

TEST_F(IntegratorTest, PropagateVariableStep)
{
    Integrator integrator;
    integrator.switch_fixed_timestep(false);
    integrator.set_equations_of_motion(eom);

    integrator.set_step_method(StepMethod::RK45);
    EXPECT_NO_THROW({ auto history = integrator.propagate(state, propTime, vehicle); });

    integrator.set_step_method(StepMethod::RKF45);
    vehicle = Vehicle();
    EXPECT_NO_THROW({ auto history = integrator.propagate(state, propTime, vehicle); });

    integrator.set_step_method(StepMethod::RKF78);
    vehicle = Vehicle();
    EXPECT_NO_THROW({ auto history = integrator.propagate(state, propTime, vehicle); });

    integrator.set_step_method(StepMethod::DOP45);
    vehicle = Vehicle();
    EXPECT_NO_THROW({ auto history = integrator.propagate(state, propTime, vehicle); });

    integrator.set_step_method(StepMethod::DOP78);
    vehicle = Vehicle();
    EXPECT_NO_THROW({ auto history = integrator.propagate(state, propTime, vehicle); });
}

TEST_F(IntegratorTest, FunctionEvaluations)
{
    Integrator integrator;
    EXPECT_EQ(integrator.n_func_evals(), 0);
}

TEST_F(IntegratorTest, SettingsConstructor)
{
    IntegratorSettings settings;
    settings.absTol       = 1e-10;
    settings.relTol       = 1e-10;
    settings.itMax        = 500;
    settings.stepMethod   = StepMethod::DOP45;
    settings.useFixedStep = false;

    ASSERT_NO_THROW(Integrator integrator(settings));
}

TEST_F(IntegratorTest, SettingsConstructorFixedStep)
{
    IntegratorSettings settings;
    settings.useFixedStep  = true;
    settings.fixedTimeStep = 30.0 * s;

    ASSERT_NO_THROW(Integrator integrator(settings));
}

TEST_F(IntegratorTest, PropagateReturnsNonEmptyHistory)
{
    Integrator integrator;
    integrator.switch_fixed_timestep(true, 60.0 * mp_units::si::unit_symbols::s);
    integrator.set_equations_of_motion(eom);

    auto history = integrator.propagate(state, propTime, vehicle);
    EXPECT_FALSE(history.empty());
    EXPECT_GT(history.size(), 0u);
}

TEST_F(IntegratorTest, PropagateVariableStepReturnsNonEmptyHistory)
{
    Integrator integrator;
    integrator.switch_fixed_timestep(false);
    integrator.set_step_method(StepMethod::RKF78);
    integrator.set_equations_of_motion(eom);

    auto history = integrator.propagate(state, propTime, vehicle);
    EXPECT_FALSE(history.empty());
}

TEST_F(IntegratorTest, PropagateToDateFixed)
{
    Integrator integrator;
    integrator.switch_fixed_timestep(true, 60.0 * s);
    integrator.set_equations_of_motion(eom);

    const Date endEpoch = state.get_epoch() + propTime;
    EXPECT_NO_THROW({ auto history = integrator.propagate(state, endEpoch, vehicle); });
}

TEST_F(IntegratorTest, PropagateToDateVariable)
{
    Integrator integrator;
    integrator.switch_fixed_timestep(false);
    integrator.set_step_method(StepMethod::DOP45);
    integrator.set_equations_of_motion(eom);

    const Date endEpoch = state.get_epoch() + propTime;
    EXPECT_NO_THROW({ auto history = integrator.propagate(state, endEpoch, vehicle); });
}

TEST_F(IntegratorTest, PropagateNoStorageFixed)
{
    Integrator integrator;
    integrator.switch_fixed_timestep(true, 60.0 * s);
    integrator.set_equations_of_motion(eom);

    EXPECT_NO_THROW(integrator.propagate_no_storage(state, propTime, vehicle));
}

TEST_F(IntegratorTest, PropagateNoStorageVariable)
{
    Integrator integrator;
    integrator.switch_fixed_timestep(false);
    integrator.set_step_method(StepMethod::RKF45);
    integrator.set_equations_of_motion(eom);

    EXPECT_NO_THROW(integrator.propagate_no_storage(state, propTime, vehicle));
}

TEST_F(IntegratorTest, PropagateNoStorageToDateFixed)
{
    Integrator integrator;
    integrator.switch_fixed_timestep(true, 60.0 * s);
    integrator.set_equations_of_motion(eom);

    const Date endEpoch = state.get_epoch() + propTime;
    EXPECT_NO_THROW(integrator.propagate_no_storage(state, endEpoch, vehicle));
}

TEST_F(IntegratorTest, PropagateNoStorageToDateVariable)
{
    Integrator integrator;
    integrator.switch_fixed_timestep(false);
    integrator.set_step_method(StepMethod::DOP78);
    integrator.set_equations_of_motion(eom);

    const Date endEpoch = state.get_epoch() + propTime;
    EXPECT_NO_THROW(integrator.propagate_no_storage(state, endEpoch, vehicle));
}

TEST_F(IntegratorTest, FunctionEvaluationsIncrementAfterPropagate)
{
    Integrator integrator;
    integrator.switch_fixed_timestep(true, 60.0 * s);
    integrator.set_equations_of_motion(eom);

    integrator.propagate(state, propTime, vehicle);
    EXPECT_GT(integrator.n_func_evals(), 0);
}

TEST_F(IntegratorTest, AddEventNoThrow)
{
    Integrator integrator;
    Event e(SimpleTestEvent{});
    EXPECT_NO_THROW(integrator.add_event(e));
}

TEST_F(IntegratorTest, AddEventsNoThrow)
{
    Integrator integrator;
    Event e1(SimpleTestEvent{});
    Event e2(SimpleTestEvent{});
    EXPECT_NO_THROW(integrator.add_events({ e1, e2 }));
}

TEST_F(IntegratorTest, ClearEventsNoThrow)
{
    Integrator integrator;
    integrator.add_event(Event(SimpleTestEvent{}));
    EXPECT_NO_THROW(integrator.clear_events());
}

TEST_F(IntegratorTest, PropagateWithEvent)
{
    Integrator integrator;
    integrator.switch_fixed_timestep(true, 60.0 * s);
    integrator.set_equations_of_motion(eom);
    integrator.add_event(Event(SimpleTestEvent{}));

    EXPECT_NO_THROW({ auto history = integrator.propagate(state, propTime, vehicle); });
}

TEST_F(IntegratorTest, SetScheduleNoThrow)
{
    Integrator integrator;
    Schedule schedule;
    EXPECT_NO_THROW(integrator.set_schedule(schedule));
}

TEST_F(IntegratorTest, ClearScheduleNoThrow)
{
    Integrator integrator;
    Schedule schedule;
    integrator.set_schedule(schedule);
    EXPECT_NO_THROW(integrator.clear());
}

TEST_F(IntegratorTest, PropagateWithScheduledEvent)
{
    Integrator integrator;
    integrator.switch_fixed_timestep(true, 60.0 * s);
    integrator.set_equations_of_motion(eom);

    Schedule schedule;
    const Date eventDate = state.get_epoch() + days(0.5);
    schedule.schedule_event(eventDate, Event(SimpleTestEvent{}));
    integrator.set_schedule(schedule);

    EXPECT_NO_THROW({ auto history = integrator.propagate(state, propTime, vehicle); });
}
