
#include <gtest/gtest.h>
#include <random>
#include <vector>

#include <astro/astro.hpp>


class ConversionTest : public testing::Test {
  protected:
    // Test Options
    const int nConversion = 1e3;
    const int nElements   = 1000;
    const double REL_TOL  = 1e-6;

    ConversionTest() :
        rng(rd()),
        semimajor_dist(6380.0, 40000.0),
        ecc_dist(0.0, 0.99),
        inc_dist(0.0, 180.0),
        raan_dist(0.0, 360.0),
        w_dist(0.0, 360.0),
        theta_dist(0.0, 360.0)
    {
    }

    // Setup
    AstrodynamicsSystem sys;

    std::random_device rd;
    std::default_random_engine rng;
    std::uniform_real_distribution<double> semimajor_dist;
    std::uniform_real_distribution<double> ecc_dist;
    std::uniform_real_distribution<double> inc_dist;
    std::uniform_real_distribution<double> raan_dist;
    std::uniform_real_distribution<double> w_dist;
    std::uniform_real_distribution<double> theta_dist;

    OrbitalElements random_elements()
    {
        ElementArray elements{ semimajor_dist(rng), ecc_dist(rng), inc_dist(rng),
                               raan_dist(rng),      w_dist(rng),   theta_dist(rng) };
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