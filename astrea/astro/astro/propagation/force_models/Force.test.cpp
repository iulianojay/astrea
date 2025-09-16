#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/force_models/Force.hpp>
#include <astro/state/CartesianVector.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

class DummyForce : public Force {
  public:
    DummyForce() = default;
    AccelerationVector<ECI>
        compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const override
    {
        return AccelerationVector<ECI>(0.0 * km / (s * s), 0.0 * km / (s * s), 0.0 * km / (s * s));
    }
};

class ForceTest : public testing::Test {
  public:
    ForceTest() = default;
    void SetUp() override {}

    DummyForce force;
    Date date;
    Cartesian state;
    Vehicle vehicle;
    AstrodynamicsSystem sys;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(ForceTest, DefaultConstructor) { ASSERT_NO_THROW(DummyForce()); }

TEST_F(ForceTest, ComputeForce)
{
    auto accel = force.compute_force(date, state, vehicle, sys);
    ASSERT_EQ(accel.get_x(), 0.0 * km / (s * s));
    ASSERT_EQ(accel.get_y(), 0.0 * km / (s * s));
    ASSERT_EQ(accel.get_z(), 0.0 * km / (s * s));
}
