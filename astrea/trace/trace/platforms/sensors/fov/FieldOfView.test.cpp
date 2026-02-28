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
#include <gtl/btree.hpp>

#include <astro/astro.hpp>

#include <trace/trace.hpp>

using namespace astrea;
using namespace astro;
using namespace trace;

using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::m;

class FieldOfViewTest : public testing::Test {
  public:
    FieldOfViewTest() = default;

    void SetUp() override
    {
        boresight     = RadiusVector<frames::earth::icrf>(1.0 * m, 0.0 * m, 0.0 * m);
        targetInside  = RadiusVector<frames::earth::icrf>(0.9 * m, 0.1 * m, 0.0 * m);
        targetOutside = RadiusVector<frames::earth::icrf>(0.0 * m, 1.0 * m, 0.0 * m);

        halfCone = std::numbers::pi / 4.0 * rad;

        circFov = CircularFieldOfView(halfCone);

        for (int ii = 0; ii < 16; ++ii) {
            Angle angle   = ii / 16.0 * 2.0 * std::numbers::pi * rad;
            points[angle] = halfCone;
        }
        polyFov = PolygonalFieldOfView(points);
    }

    RadiusVector<frames::earth::icrf> boresight;
    RadiusVector<frames::earth::icrf> targetInside;
    RadiusVector<frames::earth::icrf> targetOutside;

    Angle halfCone;
    CircularFieldOfView circFov;
    gtl::btree_map<Angle, Angle> points;
    PolygonalFieldOfView polyFov;
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
    ASSERT_TRUE(polyFov.contains(boresight, targetInside));
    ASSERT_FALSE(polyFov.contains(boresight, targetOutside));
}
