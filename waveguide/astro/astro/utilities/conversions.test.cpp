
#include <gtest/gtest.h>
#include <random>
#include <vector>

#include <mp-units/math.h>
#include <mp-units/random.h>

#include <astro/astro.hpp>

using namespace astro;

class ConversionTest : public testing::Test {
  public:
    // Test Options
    const int nConversion  = 1e3;
    const int nElements    = 1e2;
    const Unitless REL_TOL = 1e-6 * mp_units::one;

    ConversionTest() :
        rng(rd()),
        semimajorDist(6380.0 * detail::distance_unit, 40000.0 * detail::distance_unit),
        eccDist(0.0 * detail::unitless, 0.99 * detail::unitless),
        incDist(0.0 * detail::angle_unit, PI),
        raanDist(0.0 * detail::angle_unit, TWO_PI),
        wDist(0.0 * detail::angle_unit, TWO_PI),
        thetaDist(0.0 * detail::angle_unit, TWO_PI)
    {
    }

    void SetUp() override
    {
        const Distance semimajor = 10000.0 * detail::distance_unit;
        const Unitless zero      = 0.0 * detail::unitless;
        const Angle zeroAng      = 0.0 * detail::angle_unit;

        const GravParam mu = sys.get_center()->get_mu();
        const Velocity V   = sqrt(mu / semimajor);

        _keplExp =
            Keplerian(semimajor, 0.0 * detail::unitless, 0.0 * detail::angle_unit, 0.0 * detail::angle_unit, 0.0 * detail::angle_unit, 0.0 * detail::angle_unit);
        _cartExp = Cartesian(
            semimajor,
            0.0 * detail::distance_unit,
            0.0 * detail::distance_unit,
            V,
            0.0 * detail::distance_unit / detail::time_unit,
            0.0 * detail::distance_unit / detail::time_unit
        );
    }

    // Expected values
    OrbitalElements _cartExp;
    OrbitalElements _keplExp;

    // Setup
    AstrodynamicsSystem sys;

    std::random_device rd;
    std::default_random_engine rng;
    mp_units::uniform_real_distribution<Distance> semimajorDist;
    mp_units::uniform_real_distribution<Unitless> eccDist;
    mp_units::uniform_real_distribution<Angle> incDist;
    mp_units::uniform_real_distribution<Angle> raanDist;
    mp_units::uniform_real_distribution<Angle> wDist;
    mp_units::uniform_real_distribution<Angle> thetaDist;

    OrbitalElements random_elements()
    {
        Keplerian elements(semimajorDist(rng), eccDist(rng), incDist(rng), raanDist(rng), wDist(rng), thetaDist(rng));
        return OrbitalElements(elements);
    }

    const bool nearly_equal(const OrbitalElements& first, const OrbitalElements& second)
    {
        if (first.index() != second.index()) { return false; }

        auto firstUnitless  = first.to_vector();
        auto secondUnitless = second.to_vector();
        for (int ii = 0; ii < 6; ii++) {
            if (abs((firstUnitless[ii] - secondUnitless[ii]) / firstUnitless[ii]) > REL_TOL) { return false; }
        }
        return true;
    }

    void assert_nearly_equal(const OrbitalElements& elements, const OrbitalElements& expectedElements)
    {
        ASSERT_TRUE(nearly_equal(elements, expectedElements)) << "Conversion caused issues greater than " << REL_TOL * 100 << "\n"
                                                              << "Converted Set: " << elements << "\n"
                                                              << "Expected Set : " << expectedElements << "\n\n";
    }

    void expect_nearly_equal(const OrbitalElements& elements, const OrbitalElements& expectedElements)
    {
        EXPECT_TRUE(nearly_equal(elements, expectedElements)) << "Conversion caused issues greater than " << REL_TOL * 100 << "\n"
                                                              << "Converted Set: " << elements << "\n"
                                                              << "Expected Set : " << expectedElements << "\n\n";
    }
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(ConversionTest, CartesianKeplerianCycle)
{
    for (int ii = 0; ii < nElements; ii++) {
        const auto originalElements = random_elements();
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