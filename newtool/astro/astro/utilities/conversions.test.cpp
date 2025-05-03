
#include <gtest/gtest.h>
#include <random>
#include <vector>

#include <astro/astro.hpp>

using namespace astro;

class ConversionTest : public testing::Test {
  protected:
    // Test Options
    const int nConversion = 1e3;
    const int nElements   = 1e2;
    const double REL_TOL  = 1e-6;

    ConversionTest() :
        rng(rd()),
        semimajorDist(6380.0, 40000.0),
        eccDist(0.0, 0.99),
        incDist(0.0, M_PI),
        raanDist(0.0, 2 * M_PI),
        wDist(0.0, 2 * M_PI),
        thetaDist(0.0, 2 * M_PI)
    {
    }

    // Setup
    AstrodynamicsSystem sys;

    std::random_device rd;
    std::default_random_engine rng;
    std::uniform_real_distribution<double> semimajorDist;
    std::uniform_real_distribution<double> eccDist;
    std::uniform_real_distribution<double> incDist;
    std::uniform_real_distribution<double> raanDist;
    std::uniform_real_distribution<double> wDist;
    std::uniform_real_distribution<double> thetaDist;

    OrbitalElements random_elements()
    {
        ElementArray elements{ semimajorDist(rng), eccDist(rng), incDist(rng), raanDist(rng), wDist(rng), thetaDist(rng) };
        return OrbitalElements(elements, ElementSet::KEPLERIAN);
    }

    const bool nearly_equal(const OrbitalElements& first, const OrbitalElements& second)
    {
        if (first.get_set() != second.get_set()) { return false; }
        for (int ii = 0; ii < 6; ii++) {
            if (fabs((first[ii] - second[ii]) / first[ii]) > REL_TOL) { return false; }
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
            elements.convert(ElementSet::CARTESIAN, sys);

            // Convert back
            elements.convert(ElementSet::KEPLERIAN, sys);

            // Compare
            assert_nearly_equal(elements, originalElements);
        }
    }
    SUCCEED();
}


TEST_F(ConversionTest, KeplerianToCartesian)
{

    const double semimajor = 10000.0;
    OrbitalElements elements({ semimajor, 0.0, 0.0, 0.0, 0.0, 0.0 }, ElementSet::KEPLERIAN);
    elements.convert(ElementSet::CARTESIAN, sys);

    const double mu = sys.get_center()->get_mu();
    const double V  = std::sqrt(mu / elements[0]);
    OrbitalElements expectedElements({ semimajor, 0.0, 0.0, 0.0, V, 0.0 }, ElementSet::CARTESIAN);

    assert_nearly_equal(elements, expectedElements);
}


TEST_F(ConversionTest, CartesianToKeplerian)
{

    const double semimajor = 10000.0;
    const double mu        = sys.get_center()->get_mu();
    const double V         = std::sqrt(mu / semimajor);

    OrbitalElements elements({ semimajor, 0.0, 0.0, 0.0, V, 0.0 }, ElementSet::CARTESIAN);
    elements.convert(ElementSet::KEPLERIAN, sys);

    OrbitalElements expectedElements({ semimajor, 0.0, 0.0, 0.0, 0.0, 0.0 }, ElementSet::KEPLERIAN);

    assert_nearly_equal(elements, expectedElements);
}