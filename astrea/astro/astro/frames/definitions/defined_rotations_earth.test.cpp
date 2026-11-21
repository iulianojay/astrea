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
 * @brief Unit tests for the Earth-specific DCM specializations (defined_rotations_earth.hpp) and
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
 *   [4] D. Vallado, "Fundamentals of Astrodynamics and Applications," 4th ed., Example 3-15
 *       (IAU-76/FK5 reduction). On 2004-04-06 07:51:28.386 UTC, r_GCRF = (5102.508958,
 *       6123.011401, 6378.136928) km maps to r_ITRF = (-1033.4793830, 7901.2952754,
 *       6380.3565958) km, with nutation dpsi = -0.0034108 deg and deps = 0.0020316 deg.
 *   [5] G. Petit and B. Luzum (eds.), IERS Conventions (2010), IERS Technical Note No. 36,
 *       Chapter 5, "Transformation between the celestial and terrestrial reference systems."
 *       Its precession-nutation, Earth-rotation, and polar-motion conventions define the ITRF
 *       transformation used by these tests.
 */

#include <gtest/gtest.h>

#include <algorithm>
#include <stdexcept>

#include <mp-units/systems/si.h>

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/frames.hpp>
#include <astro/frames/definitions/defined_rotations_earth.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/systems/celestial_bodies.hpp>
#include <astro/time/Date.hpp>

#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astrea::astro;
using namespace mp_units;
using mp_units::si::unit_symbols::arcsec;
using mp_units::si::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::rad;

namespace {

const Unitless TIGHT_TOL = 1.0e-9 * one;
const Unitless LOOSE_TOL = 1.0e-6 * one;
const Unitless GMST_TOL  = 1.0e-4 * one; // generous margin around the published GMST reference value

// A date within the bundled Earth Orientation Parameters range (1962 - present) but well away from
// J2000 so that precession, nutation, and polar-motion all contribute nonzero terms.
const Date TEST_DATE = Date(J2000) + 3830.0 * mp_units::non_si::day; // ~2010-06-01

// Vallado Example 3-15 [4]
const Date VALLADO_DATE{ "2004-04-06 07:51:28.386", "%Y-%m-%d %H:%M:%S" };

/**
 * @brief Verifies that a DirectionCosineMatrix is a proper rotation: orthogonal (R * R^T = I) and
 *        right-handed (determinant = +1). This is the defining mathematical property of any valid
 *        direction cosine matrix and holds independently of any specific numerical reference.
 */
template <IsFrame auto in_frame, IsFrame auto out_frame>
void expect_proper_rotation(const DCM<in_frame, out_frame>& dcm)
{
    EXPECT_TRUE(nearly_equal(DCM<out_frame, out_frame>(dcm * dcm.transpose()), DCM<out_frame, out_frame>::identity(), LOOSE_TOL, LOOSE_TOL))
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

TEST(GetNutationAngles, MatchesValladoExample)
{
    using astrea::units::unit_symbols::jc;
    const Unitless T             = (VALLADO_DATE - J2000) / jc;
    const auto [eps, dpsi, deps] = get_nutation_angles(T);
    (void)eps;
    // Vallado quotes the angles to 1e-7 deg; the remaining difference is the TT-UTC offset.
    EXPECT_NEAR(dpsi.numerical_value_in(deg), -0.0034108, 2.0e-7);
    EXPECT_NEAR(deps.numerical_value_in(deg), 0.0020316, 2.0e-7);
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
    // so the full ICRF->CEP DCM at J2000 reduces to the mean-of-date -> true-of-date rotation
    // N^T = R1(eps + deps) R3(dpsi) R1(-eps).
    const auto [eps, dpsi, deps] = get_nutation_angles(0.0 * one);
    const auto expected          = DCM<frames::earth::icrf, frames::earth::cep>::XZX(eps + deps, dpsi, -eps);
    const auto actual            = get_dcm<frames::earth::icrf, frames::earth::cep>(Date(J2000));
    EXPECT_TRUE(nearly_equal(actual, expected, TIGHT_TOL, TIGHT_TOL)) << "Expected:\n"
                                                                      << expected << "\nActual:\n"
                                                                      << actual;
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
    // The CEP -> ITRF rotation evaluates sidereal time at UT1, so Earth rotates an extra
    // omega * (UT1 - UTC), then uses apparent sidereal time (GMST + dpsi cos(eps)) followed by
    // polar motion W^T = R2(xp) R1(yp).
    const auto [eps, dpsi, deps] = get_nutation_angles(0.0 * one);
    (void)deps;
    const Time ut1MinusUtc            = UT1Clock::ut1_minus_utc(Date(J2000).sys()).count() * mp_units::si::second;
    const Angle earthRotationOverDut1 = get_rotation_rate<planets::Earth>() * ut1MinusUtc;
    const Angle gastJ2000             = 280.46061837504 * deg + earthRotationOverDut1 + dpsi * math::cos(eps);

    const auto [xp, yp] = get_polar_motion(Date(J2000));
    const DCM<frames::earth::cep, frames::earth::itrf> expected =
        (DCM<frames::earth::itrf, frames::earth::itrf>::Y(xp) * DCM<frames::earth::itrf, frames::earth::itrf>::X(yp)) *
        DCM<frames::earth::cep, frames::earth::itrf>::Z(-gastJ2000);
    const auto actual = get_dcm<frames::earth::cep, frames::earth::itrf>(Date(J2000));
    EXPECT_TRUE(nearly_equal(actual, expected, GMST_TOL, GMST_TOL)) << "Expected:\n"
                                                                    << expected << "\nActual:\n"
                                                                    << actual;
}

// -------------------------------------------------------------------------------------------
// get_polar_motion
// -------------------------------------------------------------------------------------------

TEST(GetPolarMotion, MatchesTabulatedEopValueAtExactGridPoint)
{
    // Interpolating exactly at a tabulated date (2000-01-01 00:00) must reproduce that row of the
    // bundled EOP table. Read the expected values from the table, since every JPL EOP2 release
    // re-smooths the historical values.
    const Date gridDate(JulianDate(JulianDateClock::duration{ 2451544.5 }));
    const auto& data = eop::EarthOrientationParameters::DATA;
    const auto row   = std::ranges::find(data, gridDate, &eop::EarthOrientationParameters::EopRow::MJD);
    ASSERT_NE(row, data.end());
    const auto [xp, yp] = get_polar_motion(gridDate);
    EXPECT_TRUE(math::nearly_equal(xp, row->PMx, TIGHT_TOL));
    EXPECT_TRUE(math::nearly_equal(yp, row->PMy, TIGHT_TOL));
}

TEST(GetPolarMotion, NoThrowForDateOutsideEopRange)
{
    const Date farFuture = Date(J2000) + 100000.0 * mp_units::non_si::day;
    EXPECT_NO_THROW(get_polar_motion(farFuture));
}

// -------------------------------------------------------------------------------------------
// Full-chain get_dcm (any Earth ICRF frame -> any Earth body-fixed frame)
// -------------------------------------------------------------------------------------------

TEST(GetDcmIcrfToEarthFixed, IsProperRotation)
{
    expect_proper_rotation(get_dcm<frames::earth::icrf, frames::earth::earth_fixed>(TEST_DATE));
}

TEST(GetDcmIcrfToEarthFixed, EqualsCepToItrfAppliedAfterIcrfToCep)
{
    // v_itrf = M_cep->itrf * (M_icrf->cep * v_icrf): precession-nutation is applied first.
    const DCM<frames::earth::icrf, frames::earth::itrf> expected =
        get_dcm<frames::earth::cep, frames::earth::itrf>(TEST_DATE) * get_dcm<frames::earth::icrf, frames::earth::cep>(TEST_DATE);
    const auto actual = get_dcm<frames::earth::icrf, frames::earth::earth_fixed>(TEST_DATE);
    EXPECT_TRUE(nearly_equal(actual, expected, TIGHT_TOL, TIGHT_TOL)) << "Expected:\n"
                                                                      << expected << "\nActual:\n"
                                                                      << actual;
}

TEST(GetDcmIcrfToItrf, MatchesValladoExample)
{
    // Vallado Example 3-15 [4]. The reference also evaluates precession-nutation in TT and applies the
    // IERS nutation corrections (ddpsi, ddeps), which this implementation does not model.
    const RadiusVector<frames::earth::icrf> inertialPosition{ 5102.508958 * km, 6123.011401 * km, 6378.136928 * km };
    const auto itrfPosition = inertialPosition.in_frame<frames::earth::itrf>(VALLADO_DATE);

    EXPECT_NEAR(itrfPosition.get_x().numerical_value_in(km), -1033.4793830, 0.002);
    EXPECT_NEAR(itrfPosition.get_y().numerical_value_in(km), 7901.2952754, 0.002);
    EXPECT_NEAR(itrfPosition.get_z().numerical_value_in(km), 6380.3565958, 0.002);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
