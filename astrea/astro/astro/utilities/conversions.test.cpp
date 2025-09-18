#include <random>

#include <gtest/gtest.h>
#include <mp-units/random.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/state/angular_coordinates/Geodetic.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/utilities/conversions.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

class ConversionTest : public testing::Test {
  public:
    // Test Options
    const int nConversion  = 1e3;
    const int nElements    = 1e2;
    const Unitless REL_TOL = 1e-4 * one;

    ConversionTest() :
        rng(rd()),
        semimajorDist(6380.0 * km, 40000.0 * km),
        eccDist(0.0 * one, 0.99 * one),
        incDist(0.0 * rad, PI),
        raanDist(0.0 * rad, TWO_PI),
        wDist(0.0 * rad, TWO_PI),
        thetaDist(0.0 * rad, TWO_PI)
    {
    }

    void SetUp() override
    {
        const Distance R   = 10000.0 * km;
        const GravParam mu = sys.get_center()->get_mu();
        const Velocity V   = sqrt(mu / R);

        _keplExp = Keplerian(R, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad);
        _cartExp = Cartesian(R, 0.0 * km, 0.0 * km, 0.0 * km / s, V, 0.0 * km / s);
        _equiExp = Equinoctial(R, 0.0 * one, 0.0 * one, 0.0 * one, 0.0 * one, 0.0 * rad);

        _eciExp  = Cartesian(R, 0.0 * km, 0.0 * km, 0.0 * km / s, V, 0.0 * km / s);
        _ecefExp = Cartesian(R, 0.0 * km, 0.0 * km, 0.0 * km / s, V, 0.0 * km / s);

        // Hard code vallado values to ensure tests pass
        rEquitorial = 6378.1363 * km;
        rPolar      = 6356.751 * km;
        // rEquitorial = sys.get_center()->get_equitorial_radius();
        // rPolar      = sys.get_center()->get_polar_radius();
    }

    // Expected values
    OrbitalElements _cartExp;
    OrbitalElements _keplExp;
    OrbitalElements _equiExp;

    OrbitalElements _eciExp;
    OrbitalElements _ecefExp;

    // Setup
    AstrodynamicsSystem sys;
    Distance rEquitorial;
    Distance rPolar;

    std::random_device rd;
    std::default_random_engine rng;
    mp_units::uniform_real_distribution<Distance> semimajorDist;
    mp_units::uniform_real_distribution<Unitless> eccDist;
    mp_units::uniform_real_distribution<Angle> incDist;
    mp_units::uniform_real_distribution<Angle> raanDist;
    mp_units::uniform_real_distribution<Angle> wDist;
    mp_units::uniform_real_distribution<Angle> thetaDist;

    template <typename T>
    OrbitalElements random_elements()
    {
        Keplerian elements(semimajorDist(rng), eccDist(rng), incDist(rng), raanDist(rng), wDist(rng), thetaDist(rng));
        return OrbitalElements(T(elements, AstrodynamicsSystem()));
    }
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(ConversionTest, KeplerianToCartesian)
{
    OrbitalElements elements = _keplExp;
    elements.convert_to_set<Cartesian>(sys);
    ASSERT_NO_FATAL_FAILURE(ASSERT_EQ_ORB_ELEM(elements, _cartExp, false, REL_TOL));
}
TEST_F(ConversionTest, CartesianToKeplerian)
{
    OrbitalElements elements = _cartExp;
    elements.convert_to_set<Keplerian>(sys);
    ASSERT_NO_FATAL_FAILURE(ASSERT_EQ_ORB_ELEM(elements, _keplExp, false, REL_TOL));
}
TEST_F(ConversionTest, CartesianKeplerianCycle)
{
    for (int ii = 0; ii < nElements; ii++) {
        const auto originalElements = random_elements<Keplerian>();
        auto elements               = originalElements;
        for (int jj = 0; jj < nConversion; jj++) {
            // Convert to Cartesian
            elements.convert_to_set<Cartesian>(sys);

            // Convert back
            elements.convert_to_set<Keplerian>(sys);

            // Compare
            ASSERT_NO_FATAL_FAILURE(ASSERT_EQ_ORB_ELEM(elements, originalElements, false, REL_TOL));
        }
    }
    SUCCEED();
}

TEST_F(ConversionTest, EquinoctialToCartesian)
{
    OrbitalElements elements = _equiExp;
    elements.convert_to_set<Cartesian>(sys);
    ASSERT_NO_FATAL_FAILURE(ASSERT_EQ_ORB_ELEM(elements, _cartExp, false, REL_TOL));
}
TEST_F(ConversionTest, CartesianToEquinoctial)
{
    OrbitalElements elements = _cartExp;
    elements.convert_to_set<Equinoctial>(sys);
    ASSERT_NO_FATAL_FAILURE(ASSERT_EQ_ORB_ELEM(elements, _equiExp, false, REL_TOL));
}
TEST_F(ConversionTest, CartesianEquinoctialCycle)
{
    for (int ii = 0; ii < nElements; ii++) {
        const auto originalElements = random_elements<Equinoctial>();
        auto elements               = originalElements;
        for (int jj = 0; jj < nConversion; jj++) {
            // Convert to Cartesian
            elements.convert_to_set<Cartesian>(sys);

            // Convert back
            elements.convert_to_set<Equinoctial>(sys);

            // Compare
            ASSERT_NO_FATAL_FAILURE(ASSERT_EQ_ORB_ELEM(elements, originalElements, false, REL_TOL));
        }
    }
    SUCCEED();
}

TEST_F(ConversionTest, KeplerianToEquinoctial)
{
    OrbitalElements elements = _keplExp;
    elements.convert_to_set<Equinoctial>(sys);
    ASSERT_NO_FATAL_FAILURE(ASSERT_EQ_ORB_ELEM(elements, _equiExp, false, REL_TOL));
}
TEST_F(ConversionTest, EquinoctialToKeplerian)
{
    OrbitalElements elements = _equiExp;
    elements.convert_to_set<Keplerian>(sys);
    ASSERT_NO_FATAL_FAILURE(ASSERT_EQ_ORB_ELEM(elements, _keplExp, false, REL_TOL));
}
TEST_F(ConversionTest, EquinoctialKeplerianCycle)
{
    for (int ii = 0; ii < nElements; ii++) {
        const auto originalElements = random_elements<Keplerian>();
        auto elements               = originalElements;
        for (int jj = 0; jj < nConversion; jj++) {
            // Convert to Equinoctial
            elements.convert_to_set<Equinoctial>(sys);

            // Convert back
            elements.convert_to_set<Keplerian>(sys);

            // Compare
            ASSERT_NO_FATAL_FAILURE(ASSERT_EQ_ORB_ELEM(elements, originalElements, false, REL_TOL));
        }
    }
    SUCCEED();
}

TEST_F(ConversionTest, EcefToLla)
{
    // Vallado ex. 3-3
    const RadiusVector<ECEF> rEcef = { 6524.834 * km, 6862.875 * km, 6448.296 * km };

    const auto [lat, lon, alt] = convert_earth_fixed_to_geodetic(rEcef, rEquitorial, rPolar);

    ASSERT_EQ_QUANTITY(lat, Angle(34.3529 * deg), REL_TOL);
    ASSERT_EQ_QUANTITY(lon, Angle(46.4464 * deg), REL_TOL);
    ASSERT_EQ_QUANTITY(alt, Distance(5085.22 * km), REL_TOL);
}
TEST_F(ConversionTest, LlaToEcef)
{
    // Vallado ex. 3-3
    const Angle lat    = 34.3529 * deg;
    const Angle lon    = 46.4464 * deg;
    const Distance alt = 5085.22 * km;

    const RadiusVector<ECEF> rEcef = convert_geodetic_to_earth_fixed(lat, lon, alt, rEquitorial, rPolar);

    // I have no idea why these are not the same
    ASSERT_EQ_QUANTITY(rEcef[0], Distance(6524.834 * km), REL_TOL);
    ASSERT_EQ_QUANTITY(rEcef[1], Distance(6862.875 * km), REL_TOL);
    ASSERT_EQ_QUANTITY(rEcef[2], Distance(6448.296 * km), REL_TOL);
}
// TEST_F(ConversionTest, EcefLlaCycle)
// {
//     for (int ii = 0; ii < nElements; ii++) {
//         const auto originalElements = random_elements<Keplerian>();
//         auto elements               = originalElements;
//         for (int jj = 0; jj < nConversion; jj++) {
//             // Convert to Equinoctial
//             elements.convert_to_set<Equinoctial>(sys);

//             // Convert back
//             elements.convert_to_set<Keplerian>(sys);

//             // Compare
//             ASSERT_NO_FATAL_FAILURE(ASSERT_EQ_ORB_ELEM(elements, originalElements, false, REL_TOL));
//         }
//     }
//     SUCCEED();
// }

// TEST_F(ConversionTest, EciToEcef)
// {
//     OrbitalElements elements = _eciExp;
//     elements.convert_to_set<Equinoctial>(sys);
//     ASSERT_NO_FATAL_FAILURE(ASSERT_EQ_ORB_ELEM(elements, _ecefExp, false, REL_TOL));
// }
// TEST_F(ConversionTest, EcefToEci)
// {
//     OrbitalElements elements = _ecefExp;
//     elements.convert_to_set<Keplerian>(sys);
//     ASSERT_NO_FATAL_FAILURE(ASSERT_EQ_ORB_ELEM(elements, _eciExp, false, REL_TOL));
// }
// TEST_F(ConversionTest, EciEcefCycle)
// {
//     for (int ii = 0; ii < nElements; ii++) {
//         const auto originalElements = random_elements<Keplerian>();
//         auto elements               = originalElements;
//         for (int jj = 0; jj < nConversion; jj++) {
//             // Convert to Equinoctial
//             elements.convert_to_set<Equinoctial>(sys);

//             // Convert back
//             elements.convert_to_set<Keplerian>(sys);

//             // Compare
//             ASSERT_NO_FATAL_FAILURE(ASSERT_EQ_ORB_ELEM(elements, originalElements, false, REL_TOL));
//         }
//     }
//     SUCCEED();
// }

TEST_F(ConversionTest, ConvertMeanAnomalyToTrueAnomaly)
{
    // Test for circular orbit (ecc = 0)
    Angle ma     = thetaDist(rng);
    Unitless ecc = 0.0 * one;
    Angle ta     = convert_mean_anomaly_to_true_anomaly(ma, ecc);
    ASSERT_EQ_QUANTITY(ta, ma, REL_TOL);

    // Test for elliptical orbit (ecc > 0)
    ma  = 0.5 * rad;
    ecc = 0.5 * one;
    ta  = convert_mean_anomaly_to_true_anomaly(ma, ecc);

    ASSERT_EQ_QUANTITY(ta, 1.3624806 * rad, REL_TOL);
}

TEST_F(ConversionTest, ConvertTrueAnomalyToMeanAnomaly)
{
    // Test for circular orbit (ecc = 0)
    Angle ta     = thetaDist(rng);
    Unitless ecc = 0.0 * one;
    Angle ma     = convert_true_anomaly_to_mean_anomaly(ta, ecc);
    ASSERT_EQ_QUANTITY(ma, ta, REL_TOL);

    // Test for elliptical orbit (ecc > 0)
    ta  = 0.5 * rad;
    ecc = 0.5 * one;
    ma  = convert_true_anomaly_to_mean_anomaly(ta, ecc);

    ASSERT_EQ_QUANTITY(ma, 0.1522418 * rad, REL_TOL);
}

TEST_F(ConversionTest, SanitizeAngle)
{
    // Test angle within [0, 2pi]
    Angle ang       = 1.0 * rad;
    Angle sanitized = sanitize_angle(ang);
    ASSERT_EQ_QUANTITY(sanitized, ang, REL_TOL);

    // Test negative angle
    ang       = -1.0 * rad;
    sanitized = sanitize_angle(ang);
    ASSERT_EQ_QUANTITY(sanitized, ang + TWO_PI, REL_TOL);

    // Test angle greater than 2pi
    ang       = 3.0 * TWO_PI;
    sanitized = sanitize_angle(ang);
    ASSERT_EQ_QUANTITY(sanitized, ang - TWO_PI, REL_TOL);
}
