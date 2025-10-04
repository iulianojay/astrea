#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/force_models/Force.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
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
    AccelerationVector<frames::earth::icrf>
        compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const override
    {
        return AccelerationVector<frames::earth::icrf>(0.0 * km / (s * s), 0.0 * km / (s * s), 0.0 * km / (s * s));
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
    EXPECT_EQ(accel.get_x(), 0.0 * km / (s * s));
    EXPECT_EQ(accel.get_y(), 0.0 * km / (s * s));
    EXPECT_EQ(accel.get_z(), 0.0 * km / (s * s));
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
