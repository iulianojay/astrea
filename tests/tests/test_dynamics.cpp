
#include <vector>
#include <random>
#include <gtest/gtest.h>

#include "astro.hpp"


class DynamicsTest : public testing::Test {
protected:

    // Test Options
    const int nConversion = 1e3;
    const int nElements = 1000;
    const double REL_TOL = 1e-6;

    DynamicsTest() :
        eom(sys),
        rng(rd()),
        semimajor_dist(6380.0, 40000.0),
        ecc_dist(0.0, 0.99),
        inc_dist(0.0, 180.0),
        raan_dist(0.0, 360.0),
        w_dist(0.0, 360.0),
        theta_dist(0.0, 360.0)
    {
        integrator.set_abs_tol(1.0e-13);
        integrator.set_rel_tol(1.0e-13);
    }

    // Setup
    AstrodynamicsSystem sys;
    EquationsOfMotion eom;
    Integrator integrator;
    std::string epoch = "Jan-01-2030 00:00:00.0";

    Interval oneDay{seconds(0), days(1)};
    Interval oneWeek{seconds(0), weeks(1)};
    Interval oneMonth{seconds(0), months(1)};
    Interval oneYear{seconds(0), years(1)};

    std::random_device rd;
    std::default_random_engine rng;
    std::uniform_real_distribution<double> semimajor_dist;
    std::uniform_real_distribution<double> ecc_dist;
    std::uniform_real_distribution<double> inc_dist;
    std::uniform_real_distribution<double> raan_dist;
    std::uniform_real_distribution<double> w_dist;
    std::uniform_real_distribution<double> theta_dist;

    OrbitalElements random_elements() {
        element_array elements{
            semimajor_dist(rng),
            ecc_dist(rng),
            inc_dist(rng),
            raan_dist(rng),
            w_dist(rng),
            theta_dist(rng)
        };
        return OrbitalElements(elements, ElementSet::KEPLERIAN);
    }

    const bool nearly_equal(const OrbitalElements& first, const OrbitalElements& second, const bool& ignoreAnomaly = true) {
        if (first.get_set() != second.get_set()) {
            return false;
        }
        const int endInd = ignoreAnomaly ? 5 : 6;
        for (int ii = 0; ii < endInd; ii++) {
            if (fabs((first[ii] - second[ii])/first[ii]) > REL_TOL) {
                return false;
            }
        }
        return true;
    }

    void assert_nearly_equal(const OrbitalElements& elements, const OrbitalElements& expectedElements, const bool& ignoreAnomaly = false) {
        ASSERT_TRUE( nearly_equal(elements, expectedElements, ignoreAnomaly) ) <<
                    "Conversion caused issues greater than " << REL_TOL*100 << "\n" <<
                    "Converted Set: " << elements << "\n" <<
                    "Expected Set : " << expectedElements << "\n\n";
    }

    void expect_nearly_equal(const OrbitalElements& elements, const OrbitalElements& expectedElements, const bool& ignoreAnomaly = false) {
        EXPECT_TRUE( nearly_equal(elements, expectedElements, ignoreAnomaly) ) <<
                    "Conversion caused issues greater than " << REL_TOL*100 << "\n" <<
                    "Converted Set: " << elements << "\n" <<
                    "Expected Set : " << expectedElements << "\n\n";
    }
};


TEST_F(DynamicsTest, TwoBody) {
    // Build spacecraft
    OrbitalElements elements0 = random_elements();
    Spacecraft vehicle(elements0, epoch);

    // Build EoMs
    eom.switch_dynamics(EquationsOfMotion::TWO_BODY);

    // Propagate
    integrator.propagate(oneMonth, vehicle, eom);

    // Compare
    for (const auto& state : vehicle.get_states()) {
        assert_nearly_equal(state.elements, elements0, true);
    }
}

TEST_F(DynamicsTest, CowellsNoPert) {
    // Build spacecraft
    OrbitalElements elements0 = random_elements();
    Spacecraft vehicle(elements0, epoch);

    // Build EoMs
    eom.switch_dynamics(EquationsOfMotion::COWELLS);

    // Propagate
    integrator.propagate(oneMonth, vehicle, eom);

    // Compare
    for (const auto& state : vehicle.get_states()) {
        assert_nearly_equal(state.elements, elements0, true);
    }
}