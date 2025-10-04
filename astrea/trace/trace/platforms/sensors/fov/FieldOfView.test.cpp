#include <gtest/gtest.h>

#include <astro/astro.hpp>

#include <trace/trace.hpp>

using namespace astrea;
using namespace astro;
using namespace trace;

class FieldOfViewTest : public testing::Test {
  public:
    FieldOfViewTest() = default;
    void SetUp() override
    {
        boresight = RadiusVector<frames::earth::icrf>(
            1.0 * mp_units::si::unit_symbols::km, 0.0 * mp_units::si::unit_symbols::km, 0.0 * mp_units::si::unit_symbols::km
        );
        targetInside = RadiusVector<frames::earth::icrf>(
            0.9 * mp_units::si::unit_symbols::km, 0.1 * mp_units::si::unit_symbols::km, 0.0 * mp_units::si::unit_symbols::km
        );
        targetOutside = RadiusVector<frames::earth::icrf>(
            0.0 * mp_units::si::unit_symbols::km, 1.0 * mp_units::si::unit_symbols::km, 0.0 * mp_units::si::unit_symbols::km
        );

        halfCone = std::numbers::pi / 4.0 * mp_units::angular::unit_symbols::rad;

        circFov = CircularFieldOfView(halfCone);

        for (int ii = 0; ii < 16; ++ii) {
            Angle angle   = ii / 16.0 * TWO_PI;
            points[angle] = halfCone;
        }
        polyFovPoints = PolygonalFieldOfView(points);
    }

    RadiusVector<frames::earth::icrf> boresight;
    RadiusVector<frames::earth::icrf> targetInside;
    RadiusVector<frames::earth::icrf> targetOutside;

    Angle halfCone;
    CircularFieldOfView circFov;
    std::unordered_map<Angle, Angle> points;
    PolygonalFieldOfView polyFovPoints;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(FieldOfViewTest, CircularFieldOfViewConstructor)
{
    CircularFieldOfView fov(halfCone);
    ASSERT_NO_THROW(CircularFieldOfView());
}

TEST_F(FieldOfViewTest, PolygonalFieldOfViewConstructors)
{
    ASSERT_NO_THROW(PolygonalFieldOfView(halfCone, 8));
    ASSERT_ANY_THROW(PolygonalFieldOfView(halfCone, halfCone, 8)); // Not implemented
    ASSERT_NO_THROW(PolygonalFieldOfView(points));
}

TEST_F(FieldOfViewTest, CircularFieldOfViewContains)
{
    ASSERT_TRUE(circFov.contains(boresight, targetInside));
    ASSERT_FALSE(circFov.contains(boresight, targetOutside));
}

TEST_F(FieldOfViewTest, PolygonalFieldOfViewContains)
{
    ASSERT_FALSE(polyFovPoints.contains(boresight, targetInside));
    ASSERT_FALSE(polyFovPoints.contains(boresight, targetOutside));
}
