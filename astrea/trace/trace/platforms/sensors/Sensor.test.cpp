#include <gtest/gtest.h>

#include <astro/astro.hpp>

#include <trace/trace.hpp>

using namespace astrea;
using namespace astro;
using namespace trace;

class SensorTest : public testing::Test {
  public:
    SensorTest() = default;

    void SetUp() override
    {
        fov        = CircularFieldOfView(std::numbers::pi / 4.0 * mp_units::angular::unit_symbols::rad);
        parameters = SensorParameters(&fov);
        sensor     = new Sensor(viewer, parameters);
    }

    void TearDown() override { delete sensor; }

    CircularFieldOfView fov;
    SensorParameters parameters;
    Viewer viewer;
    Sensor* sensor;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(SensorTest, Constructor) { ASSERT_NO_THROW(Sensor(viewer, parameters)); }

TEST_F(SensorTest, GetId) { ASSERT_NO_THROW(sensor->get_id()); }

// TEST_F(SensorTest, Contains)
// {
//     RadiusVector<frames::earth::icrf> sensor2target(1.0 * mp_units::si::unit_symbols::km, 0.0 * mp_units::si::unit_symbols::km, 0.0 *
//     mp_units::si::unit_symbols::km); ASSERT_TRUE(sensor->contains(sensor2target, Date()));
// }

TEST_F(SensorTest, GetFov) { ASSERT_EQ(parameters.get_fov(), static_cast<const FieldOfView*>(&fov)); }

TEST_F(SensorTest, SetFov)
{
    CircularFieldOfView newFov(0.5 * std::numbers::pi * mp_units::angular::unit_symbols::rad);
    parameters.set_fov(&newFov);
    ASSERT_EQ(parameters.get_fov(), static_cast<const FieldOfView*>(&newFov));
}
