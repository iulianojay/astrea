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

#include <numbers>

#include <mp-units/systems/angular.h>

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/frames/transformations.hpp>
#include <astro/time/Date.hpp>

#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astrea::astro;
using namespace mp_units;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;

static const Unitless REL_TOL = 1.0e-10 * one;
static const Unitless ABS_TOL = 1.0e-12 * one;

static_assert(frames::HasValidFrameTransformation<frames::earth::icrf, frames::earth::icrf>);
static_assert(frames::HasValidFrameTransformation<frames::earth::icrf, frames::earth::j2000>);
static_assert(frames::HasValidFrameTransformation<frames::earth::icrf, frames::earth::earth_fixed>);
static_assert(frames::HasDcm<frames::earth::j2000, frames::earth::icrf>);

TEST(GetCenterOffset, SameOriginICRFReturnsZeroVector)
{
    const auto offset = frames::get_center_offset<frames::earth::icrf, frames::earth::j2000>(J2000);
    EXPECT_NEAR(offset.get_x().numerical_value_in(km), 0.0, 1e-12);
    EXPECT_NEAR(offset.get_y().numerical_value_in(km), 0.0, 1e-12);
    EXPECT_NEAR(offset.get_z().numerical_value_in(km), 0.0, 1e-12);
}

TEST(GetCenterOffset, SameOriginECEFReturnsZeroVector)
{
    const auto offset = frames::get_center_offset<frames::earth::icrf, frames::earth::earth_fixed>(J2000);
    EXPECT_NEAR(offset.get_x().numerical_value_in(km), 0.0, 1e-12);
    EXPECT_NEAR(offset.get_y().numerical_value_in(km), 0.0, 1e-12);
    EXPECT_NEAR(offset.get_z().numerical_value_in(km), 0.0, 1e-12);
}

TEST(RotateVectorIntoFrame, SameFrameReturnsIdenticalVector)
{
    constexpr auto F = frames::earth::icrf;
    const CartesianVector<Unitless, F> vec{ 1.0 * one, 2.0 * one, 3.0 * one };
    const auto result = frames::rotate_vector_into_frame<Unitless, F, F>(vec, J2000);
    EXPECT_TRUE(nearly_equal(result, vec, REL_TOL, ABS_TOL));
}

TEST(RotateVectorIntoFrame, SameFrameZeroVectorRemainsZero)
{
    constexpr auto F = frames::earth::icrf;
    const CartesianVector<Unitless, F> zero{};
    const auto result = frames::rotate_vector_into_frame<Unitless, F, F>(zero, J2000);
    EXPECT_TRUE(nearly_equal(result, zero, REL_TOL, ABS_TOL));
}

TEST(RotateVectorIntoFrame, EarthIcrfToJ2000IsIdentityAtJ2000)
{
    const CartesianVector<Unitless, frames::earth::icrf> vec{ 1.0 * one, 0.0 * one, 0.0 * one };
    const auto result = frames::rotate_vector_into_frame<Unitless, frames::earth::icrf, frames::earth::j2000>(vec, J2000);
    EXPECT_TRUE(nearly_equal(result, CartesianVector<Unitless, frames::earth::j2000>{ 1.0 * one, 0.0 * one, 0.0 * one }, REL_TOL, ABS_TOL));
}

TEST(RotateVectorIntoFrame, EarthJ2000ToIcrfIsIdentityAtJ2000)
{
    const CartesianVector<Unitless, frames::earth::j2000> vec{ 0.0 * one, 1.0 * one, 0.0 * one };
    const auto result = frames::rotate_vector_into_frame<Unitless, frames::earth::j2000, frames::earth::icrf>(vec, J2000);
    EXPECT_TRUE(nearly_equal(result, CartesianVector<Unitless, frames::earth::icrf>{ 0.0 * one, 1.0 * one, 0.0 * one }, REL_TOL, ABS_TOL));
}

TEST(RotateVectorIntoFrame, IcrfToEcefToIcrfRoundTripRecoverOriginal)
{
    // Rotate into ECEF then back; regardless of the GST angle, the round-trip
    // should recover the original vector within floating-point tolerance.
    const CartesianVector<Unitless, frames::earth::icrf> original{ 1.0 * one, 2.0 * one, 3.0 * one };
    const auto ecef = frames::rotate_vector_into_frame<Unitless, frames::earth::icrf, frames::earth::earth_fixed>(original, J2000);
    const auto roundtrip =
        frames::rotate_vector_into_frame<Unitless, frames::earth::earth_fixed, frames::earth::icrf>(ecef, J2000);
    EXPECT_TRUE(nearly_equal(roundtrip, original, REL_TOL, ABS_TOL));
}

TEST(RotateVectorIntoFrame, IcrfToEcefPreservesVectorMagnitude)
{
    constexpr auto InFrame  = frames::earth::icrf;
    constexpr auto OutFrame = frames::earth::earth_fixed;

    const CartesianVector<Unitless, InFrame> original{ 3.0 * one, 4.0 * one, 0.0 * one };
    const auto ecef = frames::rotate_vector_into_frame<Unitless, InFrame, OutFrame>(original, J2000);

    const auto mag_in  = original.norm();
    const auto mag_out = ecef.norm();
    EXPECT_NEAR(mag_out.numerical_value_in(one), mag_in.numerical_value_in(one), 1e-10);
}

TEST(RotateVectorIntoFrame, IcrfToEcefZAxisIsInvariant)
{
    // The z-axis is the rotation axis for ECEF, so z_hat should be unchanged.
    const CartesianVector<Unitless, frames::earth::icrf> z_hat{ 0.0 * one, 0.0 * one, 1.0 * one };
    const auto ecef = frames::rotate_vector_into_frame<Unitless, frames::earth::icrf, frames::earth::earth_fixed>(z_hat, J2000);
    EXPECT_NEAR(ecef.get_x().numerical_value_in(one), 0.0, 1e-10);
    EXPECT_NEAR(ecef.get_y().numerical_value_in(one), 0.0, 1e-10);
    EXPECT_NEAR(ecef.get_z().numerical_value_in(one), 1.0, 1e-10);
}

TEST(CartesianVectorInFrame, SameFrameReturnsSelf)
{
    constexpr auto F = frames::earth::icrf;
    const CartesianVector<Unitless, F> vec{ 5.0 * one, 6.0 * one, 7.0 * one };
    const auto result = vec.in_frame<F>(J2000);
    EXPECT_TRUE(nearly_equal(result, vec, REL_TOL, ABS_TOL));
}

TEST(CartesianVectorInFrame, IcrfToEcefToIcrfRoundTrip)
{
    const CartesianVector<Unitless, frames::earth::icrf> original{ 2.0 * one, -3.0 * one, 1.0 * one };
    const auto ecef      = original.in_frame<frames::earth::earth_fixed>(J2000);
    const auto recovered = ecef.in_frame<frames::earth::icrf>(J2000);
    EXPECT_TRUE(nearly_equal(recovered, original, REL_TOL, ABS_TOL));
}

TEST(CartesianVectorInFrame, IcrfToEcefProducesCorrectFrameType)
{
    const CartesianVector<Unitless, frames::earth::icrf> vec{ 1.0 * one, 0.0 * one, 0.0 * one };
    const auto ecef = vec.in_frame<frames::earth::earth_fixed>(J2000);
    static_assert(std::is_same_v<std::remove_const_t<decltype(ecef)>, CartesianVector<Unitless, frames::earth::earth_fixed>>);
    SUCCEED();
}

TEST(TransformVectorIntoFrame, SameOriginDelegatesToRotate)
{
    const CartesianVector<Unitless, frames::earth::icrf> vec{ 1.0 * one, 0.0 * one, 0.0 * one };
    const auto via_transform =
        frames::transform_vector_into_frame<Unitless, frames::earth::icrf, frames::earth::earth_fixed>(vec, J2000);
    const auto via_rotate =
        frames::rotate_vector_into_frame<Unitless, frames::earth::icrf, frames::earth::earth_fixed>(vec, J2000);
    EXPECT_TRUE(nearly_equal(via_transform, via_rotate, REL_TOL, ABS_TOL));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
