#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/numerical/Integrator.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <astro/time/Interval.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;

class DummyEOM : public EquationsOfMotion {
  public:
    DummyEOM(const AstrodynamicsSystem& system) :
        EquationsOfMotion(system)
    {
    }

    OrbitalElementPartials operator()(const OrbitalElements&, const Vehicle&) const override
    {
        return OrbitalElementPartials();
    }

    constexpr std::size_t get_expected_set_id() const override { return 0; }
};

class IntegratorTest : public ::testing::Test {
  public:
    IntegratorTest() :
        eom(sys)
    {
    }

    void SetUp() override {}

    AstrodynamicsSystem sys;
    Date epoch;
    Interval interval{ seconds(0), days(1) };
    Vehicle vehicle;
    DummyEOM eom;
};

TEST_F(IntegratorTest, DefaultConstructorDestructor) { ASSERT_NO_THROW(Integrator integrator); }

TEST_F(IntegratorTest, SetToleranceAndOptions)
{
    Integrator integrator;
    EXPECT_NO_THROW(integrator.set_abs_tol(1e-10));
    EXPECT_NO_THROW(integrator.set_rel_tol(1e-10));
    EXPECT_NO_THROW(integrator.set_max_iter(1000));
    EXPECT_NO_THROW(integrator.switch_print(true));
    EXPECT_NO_THROW(integrator.switch_timer(true));
}

TEST_F(IntegratorTest, SetStepMethod)
{
    Integrator integrator;
    EXPECT_NO_THROW(integrator.set_step_method(Integrator::StepMethod::RK45));
    EXPECT_NO_THROW(integrator.set_step_method(Integrator::StepMethod::RKF45));
    EXPECT_NO_THROW(integrator.set_step_method(Integrator::StepMethod::RKF78));
    EXPECT_NO_THROW(integrator.set_step_method(Integrator::StepMethod::DOP45));
    EXPECT_NO_THROW(integrator.set_step_method(Integrator::StepMethod::DOP78));
}

TEST_F(IntegratorTest, SetInitialAndFixedTimestep)
{
    Integrator integrator;
    Time dt0 = 60.0 * mp_units::si::unit_symbols::s;
    EXPECT_NO_THROW(integrator.set_initial_timestep(dt0));
    EXPECT_NO_THROW(integrator.switch_fixed_timestep(true));
    EXPECT_NO_THROW(integrator.switch_fixed_timestep(true, dt0));
    EXPECT_NO_THROW(integrator.set_timestep(dt0));
}

TEST_F(IntegratorTest, PropagateFixedStep)
{
    Integrator integrator;
    integrator.switch_fixed_timestep(true, 60.0 * mp_units::si::unit_symbols::s);
    EXPECT_NO_THROW({ auto history = integrator.propagate(epoch, interval, eom, vehicle); });
}

TEST_F(IntegratorTest, PropagateVariableStep)
{
    Integrator integrator;
    integrator.switch_fixed_timestep(false);

    integrator.set_step_method(Integrator::StepMethod::RK45);
    EXPECT_NO_THROW({ auto history = integrator.propagate(epoch, interval, eom, vehicle); });

    integrator.set_step_method(Integrator::StepMethod::RKF45);
    vehicle = Vehicle();
    EXPECT_NO_THROW({ auto history = integrator.propagate(epoch, interval, eom, vehicle); });

    integrator.set_step_method(Integrator::StepMethod::RKF78);
    vehicle = Vehicle();
    EXPECT_NO_THROW({ auto history = integrator.propagate(epoch, interval, eom, vehicle); });

    integrator.set_step_method(Integrator::StepMethod::DOP45);
    vehicle = Vehicle();
    EXPECT_NO_THROW({ auto history = integrator.propagate(epoch, interval, eom, vehicle); });

    integrator.switch_print(true);
    integrator.set_step_method(Integrator::StepMethod::DOP78);
    vehicle = Vehicle();
    EXPECT_NO_THROW({ auto history = integrator.propagate(epoch, interval, eom, vehicle); });
}

TEST_F(IntegratorTest, FunctionEvaluations)
{
    Integrator integrator;
    EXPECT_EQ(integrator.n_func_evals(), 0);
}
