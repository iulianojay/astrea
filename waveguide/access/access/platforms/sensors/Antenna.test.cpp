#include <vector>

#include <gtest/gtest.h>

#include <astro/astro.hpp>

#include <access/platforms/sensors/Antenna.hpp>

using namespace waveguide;
using namespace astro;
using namespace waveguide;
using namespace accesslib;

using namespace mp_units;
using mp_units::one;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::GHz;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::W;

inline constexpr auto dB = mp_units::one;

Gain from_db(Unitless db) { return std::pow(10.0, db.numerical_value_in(db.unit) / 10.0) * one; }
Unitless to_db(Gain value) { return 10.0 * std::log10(value.numerical_value_in(value.unit)) * dB; }

template <typename T>
void compare_unit_values(const T& first, const T& second, const double& absTol = 1.0e-2)
{
    ASSERT_NEAR(first.numerical_value_in(first.unit), second.numerical_value_in(first.unit), absTol);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// "Satellite Communications" by Dennis Roddy, 5th edition, Example 12.2
TEST(SatCommTest, AntennaGain)
{
    Antenna antenna(3.0 * m, 0.55 * one, 12.0 * GHz, 1.0 * W);
    compare_unit_values(to_db(antenna.gain()), 48.93 * dB);
}

// "Satellite Communications" by Dennis Roddy, 5th edition, Example 12.3
TEST(SatCommTest, FreeSpaceLoss)
{
    Antenna antenna(1.0 * m, 1.0 * one, 6.0 * GHz, 1.0 * W);
    compare_unit_values(to_db(antenna.free_space_loss(40400 * km)), -200.14 * dB);
    compare_unit_values(to_db(antenna.free_space_loss(37500 * km)), -199.49 * dB);
}

// "Satellite Communications" by Dennis Roddy, 5th edition, Example 12.4
TEST(SatCommTest, MispointingLossGroundToGEO)
{
    Antenna groundAntenna(3.0 * m, 0.55 * one, 12.0 * GHz, 1.0 * W);
    Antenna geoSatAntenna(1.0 * m, 1.0 * one, 12.0 * GHz, 1.0 * W);

    // Bessel approximation
    compare_unit_values(to_db(groundAntenna.gain()), 48.93 * dB);
    compare_unit_values(to_db(groundAntenna.mispointing_loss(geoSatAntenna, 0.0707 * deg)), -0.16 * dB);

    // Sinc^2 approximation
    groundAntenna.set_pattern_approximation(Antenna::PatternApproximation::SINC_SQUARED);
    compare_unit_values(to_db(groundAntenna.mispointing_loss(geoSatAntenna, 0.0707 * deg)), -0.15 * dB);
}

// "Satellite Communications" by Dennis Roddy, 5th edition, Example 12.5
TEST(SatCommTest, MispointingLossGroundToSat)
{
    Antenna groundAntenna(10.0 * m, 0.70 * one, 6.0 * GHz, 1.0 * W);
    Antenna satAntenna(1.0 * m, 1.0 * one, 6.0 * GHz, 1.0 * W);

    // Bessel approximation
    compare_unit_values(to_db(groundAntenna.gain()), 54.42 * dB); // text says 54.41, but is rounds heavily
    compare_unit_values(to_db(groundAntenna.mispointing_loss(satAntenna, 0.1414 * deg)), -1.79 * dB);

    // Sinc^2 approximation
    groundAntenna.set_pattern_approximation(Antenna::PatternApproximation::SINC_SQUARED);
    compare_unit_values(to_db(groundAntenna.mispointing_loss(satAntenna, 0.1414 * deg)), -1.73 * dB);
}
