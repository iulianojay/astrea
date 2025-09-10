#include <astro/astro.hpp>
#include <astro/propagation/force_models/Force.hpp>
#include <gtest/gtest.h>

using namespace astrea;
using namespace astro;

class DummyForce : public Force {
  public:
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

class ForceModelTest : public testing::Test {
  public:
    ForceModelTest() = default;
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


TEST(ForceModelStandaloneTest, DefaultConstructor) { ASSERT_NO_THROW(ForceModel()); }

TEST(ForceModelStandaloneTest, AddForce)
{
    ForceModel model;
    auto& ptr = model.add<DummyForce>();
    EXPECT_NE(ptr.get(), nullptr);
}

TEST(ForceModelStandaloneTest, ComputeForces)
{
    ForceModel model;
    model.add<DummyForce>();
    Date date;
    Cartesian state;
    Vehicle vehicle;
    AstrodynamicsSystem sys;
    auto accel = model.compute_forces(date, state, vehicle, sys);
    EXPECT_EQ(accel.get_x(), 0.0 * mp_units::si::unit_symbols::km / (mp_units::si::unit_symbols::s * mp_units::si::unit_symbols::s));
    EXPECT_EQ(accel.get_y(), 0.0 * mp_units::si::unit_symbols::km / (mp_units::si::unit_symbols::s * mp_units::si::unit_symbols::s));
    EXPECT_EQ(accel.get_z(), 0.0 * mp_units::si::unit_symbols::km / (mp_units::si::unit_symbols::s * mp_units::si::unit_symbols::s));
}

TEST(ForceModelStandaloneTest, AtByName)
{
    ForceModel model;
    model.add<DummyForce>();
    std::string name = typeid(DummyForce).name();
    auto& ptr        = model.at(name);
    EXPECT_NE(ptr.get(), nullptr);
}

TEST(ForceModelStandaloneTest, GetByType)
{
    ForceModel model;
    model.add<DummyForce>();
    auto& ptr = model.get<DummyForce>();
    EXPECT_NE(ptr.get(), nullptr);
}
