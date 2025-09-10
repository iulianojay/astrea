#include <astro/astro.hpp>
#include <astro/propagation/force_models/Force.hpp>
#include <gtest/gtest.h>

using namespace astrea;
using namespace astro;

class DummyForce : public Force {
  public:
    DummyForce() = default;
    AccelerationVector<ECI>
        compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const override
    {
        return AccelerationVector<ECI>(
            0.0 * mp_units::si::unit_symbols::km / (mp_units::si::unit_symbols::s * mp_units::si::unit_symbols::s),
            0.0 * mp_units::si::unit_symbols::km / (mp_units::si::unit_symbols::s * mp_units::si::unit_symbols::s),
            0.0 * mp_units::si::unit_symbols::km / (mp_units::si::unit_symbols::s * mp_units::si::unit_symbols::s)
        );
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
    ASSERT_EQ(accel.get_x(), 0.0 * mp_units::si::unit_symbols::km / (mp_units::si::unit_symbols::s * mp_units::si::unit_symbols::s));
    ASSERT_EQ(accel.get_y(), 0.0 * mp_units::si::unit_symbols::km / (mp_units::si::unit_symbols::s * mp_units::si::unit_symbols::s));
    ASSERT_EQ(accel.get_z(), 0.0 * mp_units::si::unit_symbols::km / (mp_units::si::unit_symbols::s * mp_units::si::unit_symbols::s));
}
