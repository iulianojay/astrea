/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file defined_rotations_earth.test.cpp
 * @brief Unit tests for the Earth-specific DCM specialisations (defined_rotations_earth.hpp) and
 *        their supporting precession/nutation/polar-motion helper functions.
 *
 * Ground-truth numbers used to validate the implementation are taken from the following published
 * sources:
 *
 *   [1] P.K. Seidelmann, "1980 IAU Theory of Nutation: The Final Report of the IAU Working Group
 *       on Nutation," Celestial Mechanics, 27, 1982, pp. 79-106. Provides the mean obliquity of the
 *       ecliptic at J2000.0, the 106-term nutation series, and the Delaunay fundamental-argument
 *       polynomials that this file's nutation coefficient table and get_anomaly_terms()/
 *       get_nutation_angles() implement.
 *   [2] J.H. Lieske, T. Lederle, W. Fricke, B. Morando, "Expressions for the Precession Quantities
 *       Based upon the IAU (1976) System of Astronomical Constants," Astronomy & Astrophysics, 58,
 *       1977, pp. 1-16. Provides the precession-angle (zeta/z/theta) polynomials that
 *       get_precession_angles() implements.
 *   [3] D. Vallado, "Fundamentals of Astrodynamics and Applications," Algorithm 15 (GMST), which
 *       reproduces the [1]/[2] formulas and reports GMST at the J2000.0 epoch (2000-01-01 12:00:00
 *       TT) as 280.46061837504 deg (= 18h 41m 50.54841s); the same value is given in USNO Circular
 *       179 (2005), Eq. 2.13. This is consistent with (and more precise than) the existing
 *       regression value in astro/time/Date.test.cpp's `GMST` test (4.89496 rad).
 */

#include <gtest/gtest.h>

#include <stdexcept>

#include <mp-units/systems/si.h>

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/frames.hpp>
#include <astro/frames/definitions/defined_rotations_earth.hpp>
#include <astro/time/Date.hpp>

#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astrea::astro;
using namespace mp_units;
using mp_units::si::unit_symbols::arcsec;
using mp_units::si::unit_symbols::deg;

namespace {

const Unitless TIGHT_TOL = 1.0e-9 * one;
const Unitless LOOSE_TOL = 1.0e-6 * one;
const Unitless GMST_TOL  = 1.0e-4 * one; // generous margin around the published GMST reference value

// A date within the bundled Earth Orientation Parameters range (1962 - present) but well away from
// J2000 so that precession, nutation, and polar-motion all contribute nonzero terms.
const Date TEST_DATE = Date(J2000) + 3830.0 * mp_units::non_si::day; // ~2010-06-01

/**
 * @brief Verifies that a DirectionCosineMatrix is a proper rotation: orthogonal (R * R^T = I) and
 *        right-handed (determinant = +1). This is the defining mathematical property of any valid
 *        direction cosine matrix and holds independently of any specific numerical reference.
 */
template <IsFrame auto in_frame, IsFrame auto out_frame>
void expect_proper_rotation(const DCM<in_frame, out_frame>& dcm)
{
    EXPECT_TRUE(nearly_equal(DCM<in_frame, in_frame>(dcm * dcm.transpose()), DCM<in_frame, in_frame>::identity(), LOOSE_TOL, LOOSE_TOL))
        << "DCM is not orthogonal (R * R^T != I):\n"
        << dcm;
    EXPECT_TRUE(math::nearly_equal(dcm.determinant(), 1.0 * one, LOOSE_TOL))
        << "DCM determinant is not +1 (not a proper, right-handed rotation): " << dcm.determinant();
}

} // namespace

// -------------------------------------------------------------------------------------------
// get_precession_angles
// -------------------------------------------------------------------------------------------

TEST(GetPrecessionAngles, AllAnglesAreZeroAtJ2000Epoch)
{
    const auto [z, theta, zeta] = get_precession_angles(0.0 * one);
    EXPECT_TRUE(math::nearly_equal(z, 0.0 * arcsec, TIGHT_TOL));
    EXPECT_TRUE(math::nearly_equal(theta, 0.0 * arcsec, TIGHT_TOL));
    EXPECT_TRUE(math::nearly_equal(zeta, 0.0 * arcsec, TIGHT_TOL));
}

TEST(GetPrecessionAngles, MatchesIAU1976PolynomialOneCenturyAfterJ2000)
{
    // IAU 1976 precession theory (Lieske et al. 1977 [2]):
    //   z     = 2306.2181"T + 1.09468"T^2 + 0.018203"T^3
    //   theta = 2004.3109"T - 0.42665"T^2 - 0.041833"T^3
    //   zeta  = 2306.2181"T + 0.30188"T^2 + 0.017998"T^3
    // Evaluated by hand at T = 1 Julian century after J2000.
    const auto expected_z     = (2306.2181 + 1.09468 + 0.018203) * arcsec;
    const auto expected_theta = (2004.3109 - 0.42665 - 0.041833) * arcsec;
    const auto expected_zeta  = (2306.2181 + 0.30188 + 0.017998) * arcsec;

    const auto [z, theta, zeta] = get_precession_angles(1.0 * one);
    EXPECT_TRUE(math::nearly_equal(z, expected_z, TIGHT_TOL));
    EXPECT_TRUE(math::nearly_equal(theta, expected_theta, TIGHT_TOL));
    EXPECT_TRUE(math::nearly_equal(zeta, expected_zeta, TIGHT_TOL));
}

// -------------------------------------------------------------------------------------------
// get_anomaly_terms (Delaunay fundamental arguments)
// -------------------------------------------------------------------------------------------

TEST(GetAnomalyTerms, ConstantTermsMatchIAU1980FundamentalArguments)
{
    // Seidelmann 1982 [1], Delaunay fundamental-argument constant (T=0) terms, in arcseconds:
    //   l  (lunar mean anomaly)                = 485866.733"
    //   l' (solar mean anomaly)                = 1287099.804"
    //   F  (lunar mean argument of latitude)    = 335778.877"
    //   D  (mean elongation, Moon from Sun)     = 1072261.307"
    //   Om (mean longitude of lunar asc. node)  = 450160.280"
    const auto [l, lp, F, D, Om] = get_anomaly_terms(0.0 * one);
    EXPECT_TRUE(math::nearly_equal(l, 485866.733 * arcsec, TIGHT_TOL));
    EXPECT_TRUE(math::nearly_equal(lp, 1287099.804 * arcsec, TIGHT_TOL));
    EXPECT_TRUE(math::nearly_equal(F, 335778.877 * arcsec, TIGHT_TOL));
    EXPECT_TRUE(math::nearly_equal(D, 1072261.307 * arcsec, TIGHT_TOL));
    EXPECT_TRUE(math::nearly_equal(Om, 450160.280 * arcsec, TIGHT_TOL));
}

// -------------------------------------------------------------------------------------------
// get_nutation_angles
// -------------------------------------------------------------------------------------------

TEST(GetNutationAngles, MeanObliquityAtJ2000MatchesIAU1980Value)
{
    // Seidelmann 1982 [1]: the mean obliquity of the ecliptic at J2000.0 is
    // eps_0 = 23 deg 26' 21.448" = 84381.448" = 23.4392911111 deg.
    const auto [eps, dpsi, deps] = get_nutation_angles(0.0 * one);
    (void)dpsi;
    (void)deps;
    EXPECT_TRUE(math::nearly_equal(wrap_angle(eps), 23.4392911111 * deg, TIGHT_TOL, 1.0e-9 * one))
        << "Mean obliquity at J2000 does not match IAU 1980 value: " << eps;
}

// -------------------------------------------------------------------------------------------
// get_dcm<frames::earth::icrf, frames::earth::cep>
// -------------------------------------------------------------------------------------------

TEST(GetDcmIcrfToCep, IsProperRotationAtJ2000)
{
    expect_proper_rotation(get_dcm<frames::earth::icrf, frames::earth::cep>(Date(J2000)));
}

TEST(GetDcmIcrfToCep, IsProperRotationAwayFromJ2000)
{
    expect_proper_rotation(get_dcm<frames::earth::icrf, frames::earth::cep>(TEST_DATE));
}

TEST(GetDcmIcrfToCep, EqualsNutationOnlyRotationAtJ2000)
{
    // At T=0 the precession angles are all zero (see GetPrecessionAngles.AllAnglesAreZeroAtJ2000Epoch),
    // so the precession matrix is the identity and the full ICRF->CEP DCM at J2000 should reduce to
    // exactly the nutation-only rotation. This is also a regression check for the frame-tagged
    // composition order `P * N` (a previous bug applied nutation before precession).
    const auto [eps, dpsi, deps] = get_nutation_angles(0.0 * one);
    const auto expected          = DCM<frames::earth::icrf, frames::earth::cep>::XZX(-(eps + deps), -dpsi, eps);
    const auto actual            = get_dcm<frames::earth::icrf, frames::earth::cep>(Date(J2000));
    EXPECT_TRUE(nearly_equal(actual, expected, TIGHT_TOL, TIGHT_TOL));
}

// -------------------------------------------------------------------------------------------
// get_dcm<frames::earth::cep, frames::earth::itrf>
// -------------------------------------------------------------------------------------------

TEST(GetDcmCepToItrf, IsProperRotationAtJ2000)
{
    expect_proper_rotation(get_dcm<frames::earth::cep, frames::earth::itrf>(Date(J2000)));
}

TEST(GetDcmCepToItrf, IsProperRotationAwayFromJ2000)
{
    expect_proper_rotation(get_dcm<frames::earth::cep, frames::earth::itrf>(TEST_DATE));
}

TEST(GetDcmCepToItrf, SiderealRotationMatchesPublishedGmstAtJ2000)
{
    // GMST at the J2000.0 epoch (2000-01-01 12:00:00 TT) is 280.46061837504 deg -- see [3] above.
    const Angle gmstJ2000 = 280.46061837504 * deg;

    const auto [xp, yp] = get_polar_motion(Date(J2000));
    const DCM<frames::earth::cep, frames::earth::itrf> expected =
        DCM<frames::earth::cep, frames::earth::itrf>::Z(gmstJ2000) *
        (DCM<frames::earth::itrf, frames::earth::itrf>::Y(-xp) * DCM<frames::earth::itrf, frames::earth::itrf>::X(-yp));
    const auto actual = get_dcm<frames::earth::cep, frames::earth::itrf>(Date(J2000));
    EXPECT_TRUE(nearly_equal(actual, expected, GMST_TOL, GMST_TOL));
}

// -------------------------------------------------------------------------------------------
// get_polar_motion
// -------------------------------------------------------------------------------------------

TEST(GetPolarMotion, MatchesTabulatedEopValueAtExactGridPoint)
{
    // Row for Julian Date 2451544.5 (2000-01-01 00:00 UT) in the bundled IERS Earth Orientation
    // Parameters table (eop::EarthOrientationParameters::DATA) gives PMx = 43.2526 mas,
    // PMy = 377.8662 mas. Interpolating exactly at a tabulated date must reproduce those values
    // exactly (source: IERS Earth Orientation Parameters, as compiled into this repository's
    // generated eop::EarthOrientationParameters::DATA table).
    const Date gridDate(JulianDate(JulianDateClock::duration{ 2451544.5 }));
    const auto [xp, yp] = get_polar_motion(gridDate);
    EXPECT_TRUE(math::nearly_equal(xp, 43.2526 * mp_units::si::milli<mp_units::si::arcsecond>, TIGHT_TOL));
    EXPECT_TRUE(math::nearly_equal(yp, 377.8662 * mp_units::si::milli<mp_units::si::arcsecond>, TIGHT_TOL));
}

TEST(GetPolarMotion, ThrowsForDateOutsideEopRange)
{
    const Date farFuture = Date(J2000) + 100000.0 * mp_units::non_si::day;
    EXPECT_THROW(get_polar_motion(farFuture), std::out_of_range);
}

// -------------------------------------------------------------------------------------------
// Full-chain get_dcm (any Earth ICRF frame -> any Earth body-fixed frame)
// -------------------------------------------------------------------------------------------

TEST(GetDcmIcrfToEarthFixed, IsProperRotation)
{
    expect_proper_rotation(get_dcm<frames::earth::icrf, frames::earth::earth_fixed>(TEST_DATE));
}

TEST(GetDcmIcrfToEarthFixed, EqualsComposedIcrfCepAndCepItrfDcms)
{
    // Regression check for the composition wiring `dcmIcrfToCep * dcmCepToItrf` in the constrained
    // template overload of get_dcm.
    const DCM<frames::earth::icrf, frames::earth::itrf> expected =
        get_dcm<frames::earth::icrf, frames::earth::cep>(TEST_DATE) * get_dcm<frames::earth::cep, frames::earth::itrf>(TEST_DATE);
    const auto actual = get_dcm<frames::earth::icrf, frames::earth::earth_fixed>(TEST_DATE);
    EXPECT_TRUE(nearly_equal(actual, expected, TIGHT_TOL, TIGHT_TOL));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
