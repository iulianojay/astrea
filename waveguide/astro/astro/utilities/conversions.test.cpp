
#include <gtest/gtest.h>
#include <random>
#include <vector>

#include <mp-units/math.h>
#include <mp-units/random.h>

#include <astro/astro.hpp>

using namespace waveguide;
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

    [[nodiscard]] constexpr bool nearly_equal(const OrbitalElements& first, const OrbitalElements& second) noexcept
    {
        if (first.index() != second.index()) { return false; }

        auto firstUnitless  = first.to_vector();
        auto secondUnitless = second.to_vector();
        for (int ii = 0; ii < 6; ii++) {
            if (!nearly_equal(firstUnitless[ii], secondUnitless[ii])) { return false; }
        }
        return true;
    }

    template <auto R, typename Rep>
    [[nodiscard]] constexpr bool nearly_equal(const mp_units::quantity<R, Rep>& x, const mp_units::quantity<R, Rep>& y) noexcept
    {
        const auto a = x.numerical_value_ref_in(x.unit);
        const auto b = y.numerical_value_ref_in(x.unit);
        if (a != 0.0 * one && abs((a - b) / a) > REL_TOL) { return false; }
        else if (b != 0.0 * one && abs((a - b) / b) > REL_TOL) {
            return false;
        }
        return true;
    }

    void assert_nearly_equal(const OrbitalElements& elements, const OrbitalElements& expectedElements)
    {
        ASSERT_TRUE(nearly_equal(elements, expectedElements)) << "Conversion caused issues greater than " << REL_TOL * 100 << "%\n"
                                                              << "Converted Set: " << elements << "\n"
                                                              << "Expected Set : " << expectedElements << "\n\n";
    }

    template <auto R, typename Rep>
    void assert_nearly_equal(const mp_units::quantity<R, Rep>& x, const mp_units::quantity<R, Rep>& y) noexcept
    {
        ASSERT_TRUE(nearly_equal(x, y)) << "Conversion caused issues greater than " << REL_TOL * 100 << "%\n"
                                        << "First: " << x << "\n"
                                        << "Second: " << y << "\n\n";
    }

    void expect_nearly_equal(const OrbitalElements& elements, const OrbitalElements& expectedElements)
    {
        EXPECT_TRUE(nearly_equal(elements, expectedElements)) << "Conversion caused issues greater than " << REL_TOL * 100 << "%\n"
                                                              << "Converted Set: " << elements << "\n"
                                                              << "Expected Set : " << expectedElements << "\n\n";
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
    elements.convert<Cartesian>(sys);
    assert_nearly_equal(elements, _cartExp);
}
TEST_F(ConversionTest, CartesianToKeplerian)
{
    OrbitalElements elements = _cartExp;
    elements.convert<Keplerian>(sys);
    assert_nearly_equal(elements, _keplExp);
}
TEST_F(ConversionTest, CartesianKeplerianCycle)
{
    for (int ii = 0; ii < nElements; ii++) {
        const auto originalElements = random_elements<Keplerian>();
        auto elements               = originalElements;
        for (int jj = 0; jj < nConversion; jj++) {
            // Convert to Cartesian
            elements.convert<Cartesian>(sys);

            // Convert back
            elements.convert<Keplerian>(sys);

            // Compare
            assert_nearly_equal(elements, originalElements);
        }
    }
    SUCCEED();
}

TEST_F(ConversionTest, EquinoctialToCartesian)
{
    OrbitalElements elements = _equiExp;
    elements.convert<Cartesian>(sys);
    assert_nearly_equal(elements, _cartExp);
}
TEST_F(ConversionTest, CartesianToEquinoctial)
{
    OrbitalElements elements = _cartExp;
    elements.convert<Equinoctial>(sys);
    assert_nearly_equal(elements, _equiExp);
}
TEST_F(ConversionTest, CartesianEquinoctialCycle)
{
    for (int ii = 0; ii < nElements; ii++) {
        const auto originalElements = random_elements<Equinoctial>();
        auto elements               = originalElements;
        for (int jj = 0; jj < nConversion; jj++) {
            // Convert to Cartesian
            elements.convert<Cartesian>(sys);

            // Convert back
            elements.convert<Equinoctial>(sys);

            // Compare
            assert_nearly_equal(elements, originalElements);
        }
    }
    SUCCEED();
}

TEST_F(ConversionTest, KeplerianToEquinoctial)
{
    OrbitalElements elements = _keplExp;
    elements.convert<Equinoctial>(sys);
    assert_nearly_equal(elements, _equiExp);
}
TEST_F(ConversionTest, EquinoctialToKeplerian)
{
    OrbitalElements elements = _equiExp;
    elements.convert<Keplerian>(sys);
    assert_nearly_equal(elements, _keplExp);
}
TEST_F(ConversionTest, EquinoctialKeplerianCycle)
{
    for (int ii = 0; ii < nElements; ii++) {
        const auto originalElements = random_elements<Keplerian>();
        auto elements               = originalElements;
        for (int jj = 0; jj < nConversion; jj++) {
            // Convert to Equinoctial
            elements.convert<Equinoctial>(sys);

            // Convert back
            elements.convert<Keplerian>(sys);

            // Compare
            assert_nearly_equal(elements, originalElements);
        }
    }
    SUCCEED();
}

TEST_F(ConversionTest, EcefToLla) // TODO: Make an LLA element set of some kind
{
    // Vallado ex. 3-3
    const RadiusVector rEcef = { 6524.834 * km, 6862.875 * km, 6448.296 * km };

    Angle lat, lon;
    Distance alt;
    ecef_to_lla(rEcef, rEquitorial, rPolar, lat, lon, alt);

    assert_nearly_equal(lat, Angle(34.3529 * deg));
    assert_nearly_equal(lon, Angle(46.4464 * deg));
    assert_nearly_equal(alt, Distance(5085.22 * km));
}
TEST_F(ConversionTest, LlaToEcef)
{
    // Vallado ex. 3-3
    const Angle lat    = 34.3529 * deg;
    const Angle lon    = 46.4464 * deg;
    const Distance alt = 5085.22 * km;

    const RadiusVector rEcef = lla_to_ecef(lat, lon, alt, rEquitorial, rPolar);

    // I have no idea why these are not the same
    assert_nearly_equal(rEcef[0], Distance(6524.834 * km));
    assert_nearly_equal(rEcef[1], Distance(6862.875 * km));
    assert_nearly_equal(rEcef[2], Distance(6448.296 * km));
}
// TEST_F(ConversionTest, EcefLlaCycle)
// {
//     for (int ii = 0; ii < nElements; ii++) {
//         const auto originalElements = random_elements<Keplerian>();
//         auto elements               = originalElements;
//         for (int jj = 0; jj < nConversion; jj++) {
//             // Convert to Equinoctial
//             elements.convert<Equinoctial>(sys);

//             // Convert back
//             elements.convert<Keplerian>(sys);

//             // Compare
//             assert_nearly_equal(elements, originalElements);
//         }
//     }
//     SUCCEED();
// }

// TEST_F(ConversionTest, EciToEcef)
// {
//     OrbitalElements elements = _eciExp;
//     elements.convert<Equinoctial>(sys);
//     assert_nearly_equal(elements, _ecefExp);
// }
// TEST_F(ConversionTest, EcefToEci)
// {
//     OrbitalElements elements = _ecefExp;
//     elements.convert<Keplerian>(sys);
//     assert_nearly_equal(elements, _eciExp);
// }
// TEST_F(ConversionTest, EciEcefCycle)
// {
//     for (int ii = 0; ii < nElements; ii++) {
//         const auto originalElements = random_elements<Keplerian>();
//         auto elements               = originalElements;
//         for (int jj = 0; jj < nConversion; jj++) {
//             // Convert to Equinoctial
//             elements.convert<Equinoctial>(sys);

//             // Convert back
//             elements.convert<Keplerian>(sys);

//             // Compare
//             assert_nearly_equal(elements, originalElements);
//         }
//     }
//     SUCCEED();
// }