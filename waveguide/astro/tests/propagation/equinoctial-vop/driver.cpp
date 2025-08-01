#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <stdio.h>

#include <gtest/gtest.h>

#include <mp-units/systems/angular.h>
#include <mp-units/systems/international.h>
#include <mp-units/systems/isq.h>
#include <mp-units/systems/si.h>

#include <astro/astro.hpp>

using namespace waveguide;
using namespace astro;

using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::W;


class EquinoctialVopPropagationTest : public testing::Test {
  public:
    EquinoctialVopPropagationTest() :
        start(seconds(0)),
        end(weeks(1)),
        eom(sys, forces),
        propInterval({ start, end }),
        epoch(J2000)
    {
    }

    void SetUp() override {}

    template <auto R, typename Rep>
    const bool nearly_equal(const mp_units::quantity<R, Rep>& first, const mp_units::quantity<R, Rep>& second) const
    {
        const Rep a       = first.numerical_value_ref_in(first.unit);
        const Rep b       = first.numerical_value_ref_in(second.unit);
        const Rep REL_TOL = 1.0e-4;
        if (a != 0.0 && abs((a - b) / a) > REL_TOL) { return false; }
        else if (b != 0.0 && abs((a - b) / b) > REL_TOL) {
            return false;
        }
        return true;
    }

    AstrodynamicsSystem sys;
    EquinoctialVop eom;
    ForceModel forces;
    Integrator integrator;
    Time start;
    Time end;
    Interval propInterval;
    Date epoch;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(EquinoctialVopPropagationTest, GEONoForces)
{
    // Build constellation
    Keplerian state0 = Keplerian::GEO();
    Spacecraft geo({ Equinoctial(state0, sys), epoch, sys });
    Vehicle vehicle{ geo };

    // Propagate
    const auto stateHistory = integrator.propagate(epoch, propInterval, eom, vehicle, true);

    // Validate
    for (const auto& [time, state] : stateHistory) {
        Keplerian kep = state.get_elements().in<Keplerian>(sys);
        nearly_equal(kep.get_semimajor(), state0.get_semimajor());
        nearly_equal(kep.get_eccentricity(), state0.get_eccentricity());
        nearly_equal(kep.get_inclination(), state0.get_inclination());
        nearly_equal(kep.get_right_ascension(), state0.get_right_ascension());
        nearly_equal(kep.get_argument_of_perigee(), state0.get_argument_of_perigee());
    }
}


TEST_F(EquinoctialVopPropagationTest, GPSNoForces)
{
    // Build constellation
    Keplerian state0 = Keplerian::GPS();
    Spacecraft meo({ Equinoctial(state0, sys), epoch, sys });
    Vehicle vehicle{ meo };

    // Propagate
    const auto stateHistory = integrator.propagate(epoch, propInterval, eom, vehicle, true);

    // Validate
    for (const auto& [time, state] : stateHistory) {
        Keplerian kep = state.get_elements().in<Keplerian>(sys);
        nearly_equal(kep.get_semimajor(), state0.get_semimajor());
        nearly_equal(kep.get_eccentricity(), state0.get_eccentricity());
        nearly_equal(kep.get_inclination(), state0.get_inclination());
        nearly_equal(kep.get_right_ascension(), state0.get_right_ascension());
        nearly_equal(kep.get_argument_of_perigee(), state0.get_argument_of_perigee());
    }
}


TEST_F(EquinoctialVopPropagationTest, LEONoForces)
{
    // Build constellation
    Keplerian state0 = Keplerian::LEO();
    Spacecraft leo({ Equinoctial(state0, sys), epoch, sys });
    Vehicle vehicle{ leo };

    // Propagate
    const auto stateHistory = integrator.propagate(epoch, propInterval, eom, vehicle, true);

    // Validate
    for (const auto& [time, state] : stateHistory) {
        Keplerian kep = state.get_elements().in<Keplerian>(sys);
        nearly_equal(kep.get_semimajor(), state0.get_semimajor());
        nearly_equal(kep.get_eccentricity(), state0.get_eccentricity());
        nearly_equal(kep.get_inclination(), state0.get_inclination());
        nearly_equal(kep.get_right_ascension(), state0.get_right_ascension());
        nearly_equal(kep.get_argument_of_perigee(), state0.get_argument_of_perigee());
    }
}