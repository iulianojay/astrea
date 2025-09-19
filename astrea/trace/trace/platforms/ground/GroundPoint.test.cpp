#include <gtest/gtest.h>

#include <astro/astro.hpp>

#include <trace/trace.hpp>

using namespace astrea;
using namespace astro;
using namespace trace;

class GroundPointTest : public testing::Test {
  public:
    GroundPointTest() = default;

    void SetUp() override
    {
        parent    = sys.get(PlanetaryBody::EARTH).get();
        latitude  = 0.5 * mp_units::angular::unit_symbols::rad;
        longitude = 1.0 * mp_units::angular::unit_symbols::rad;
        altitude  = 0.1 * mp_units::si::unit_symbols::km;
        point     = GroundPoint(parent, latitude, longitude, altitude);
    }

    AstrodynamicsSystem sys;
    const CelestialBody* parent;
    Angle latitude;
    Angle longitude;
    Distance altitude;
    GroundPoint point;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(GroundPointTest, DefaultConstructor) { ASSERT_NO_THROW(GroundPoint()); }

TEST_F(GroundPointTest, Constructor)
{
    ASSERT_NO_THROW(GroundPoint(sys.get(PlanetaryBody::EARTH).get(), latitude, longitude, altitude));
}

TEST_F(GroundPointTest, GetLatitude) { ASSERT_EQ(point.get_latitude(), latitude); }

TEST_F(GroundPointTest, GetLongitude) { ASSERT_EQ(point.get_longitude(), longitude); }

TEST_F(GroundPointTest, GetAltitude) { ASSERT_EQ(point.get_altitude(), altitude); }

TEST_F(GroundPointTest, GetParent) { ASSERT_EQ(point.get_parent(), sys.get(PlanetaryBody::EARTH).get()); }

TEST_F(GroundPointTest, GetId)
{
    ASSERT_EQ(point.get_id(), GroundPoint(sys.get(PlanetaryBody::EARTH).get(), latitude, longitude, altitude).get_id());
}
