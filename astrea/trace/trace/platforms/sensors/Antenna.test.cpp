#include <vector>

#include <gtest/gtest.h>

#include <astro/astro.hpp>

#include <trace/platforms/sensors/Antenna.hpp>
#include <trace/platforms/vehicles/Viewer.hpp>

using namespace astrea;
using namespace astro;
using namespace astrea;
using namespace trace;

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
    Viewer sc;
    CircularFieldOfView fov;
    AntennaParameters parameters(&fov, 3.0 * m, 0.55 * one, 12.0 * GHz, 1.0 * W);

    Antenna antenna(sc, parameters);

    compare_unit_values(to_db(antenna.gain()), 48.93 * dB);
}

// "Satellite Communications" by Dennis Roddy, 5th edition, Example 12.3
TEST(SatCommTest, FreeSpaceLoss)
{
    Viewer sc;
    CircularFieldOfView fov;
    AntennaParameters parameters(&fov, 1.0 * m, 1.0 * one, 6.0 * GHz, 1.0 * W);

    Antenna antenna(sc, parameters);

    compare_unit_values(to_db(antenna.free_space_loss(40400 * km)), -200.14 * dB);
    compare_unit_values(to_db(antenna.free_space_loss(37500 * km)), -199.49 * dB);
}

// "Satellite Communications" by Dennis Roddy, 5th edition, Example 12.4
TEST(SatCommTest, MispointingLossGroundToGEO)
{
    Viewer sc;
    CircularFieldOfView fov;
    AntennaParameters groundParameters(&fov, 3.0 * m, 0.55 * one, 12.0 * GHz, 1.0 * W);
    AntennaParameters geoParameters(&fov, 1.0 * m, 1.0 * one, 12.0 * GHz, 1.0 * W);

    Antenna groundAntenna(sc, groundParameters);
    Antenna geoSatAntenna(sc, geoParameters);

    // Bessel approximation
    compare_unit_values(to_db(groundAntenna.gain()), 48.93 * dB);
    compare_unit_values(to_db(groundAntenna.mispointing_loss(geoSatAntenna, 0.0707 * deg)), -0.16 * dB);

    // Sinc^2 approximation
    groundAntenna.set_pattern_approximation(PatternApproximation::SINC_SQUARED);
    compare_unit_values(to_db(groundAntenna.mispointing_loss(geoSatAntenna, 0.0707 * deg)), -0.15 * dB);
}

// "Satellite Communications" by Dennis Roddy, 5th edition, Example 12.5
TEST(SatCommTest, MispointingLossGroundToSat)
{
    Viewer sc;
    CircularFieldOfView fov;
    AntennaParameters groundParameters(&fov, 10.0 * m, 0.70 * one, 6.0 * GHz, 1.0 * W);
    AntennaParameters satParameters(&fov, 1.0 * m, 1.0 * one, 6.0 * GHz, 1.0 * W);

    Antenna groundAntenna(sc, groundParameters);
    Antenna satAntenna(sc, satParameters);

    // Bessel approximation
    compare_unit_values(to_db(groundAntenna.gain()), 54.42 * dB); // text says 54.41, but is rounds heavily
    compare_unit_values(to_db(groundAntenna.mispointing_loss(satAntenna, 0.1414 * deg)), -1.79 * dB);

    // Sinc^2 approximation
    groundAntenna.set_pattern_approximation(PatternApproximation::SINC_SQUARED);
    compare_unit_values(to_db(groundAntenna.mispointing_loss(satAntenna, 0.1414 * deg)), -1.73 * dB);
}

// TEST(AntennaTest, ConstructorAndGetters)
// {
//     Viewer sc;
//     CircularFieldOfView fov;
//     AntennaParameters paramsIn(&fov, 2.0 * m, 0.5 * one, 10.0 * GHz, 5.0 * W);
//     Antenna antenna(sc, paramsIn);
//     const AntennaParameters params = antenna.get_parameters();

//     ASSERT_EQ(params.get_diameter(), 2.0 * m);
//     ASSERT_EQ(params.get_efficiency(), 0.5 * one);
//     ASSERT_EQ(params.get_frequency(), 10.0 * GHz);
//     ASSERT_EQ(params.get_power(), 5.0 * W);
// }

// TEST(AntennaTest, Setters) // TODO: Antenna can't directly inherit from Sensor since since inherits from Payload
// templated on Sensor. Need SensorBase or similar for each to inherit form
// {
//     Viewer sc;
//     CircularFieldOfView fov;
//     AntennaParameters paramsIn(&fov, 2.0 * m, 0.5 * one, 10.0 * GHz, 5.0 * W);
//     Antenna antenna(sc, paramsIn);
//     const AntennaParameters params = antenna.get_parameters();

//     params.set_diameter(3.0 * m);
//     ASSERT_EQ(params.get_diameter(), 3.0 * m);

//     params.set_efficiency(0.7 * one);
//     ASSERT_EQ(params.get_efficiency(), 0.7 * one);

//     params.set_frequency(12.0 * GHz);
//     ASSERT_EQ(params.get_frequency(), 12.0 * GHz);

//     params.set_power(7.0 * W);
//     ASSERT_EQ(params.get_power(), 7.0 * W);

//     antenna.set_pattern_approximation(PatternApproximation::SINC_SQUARED);
//     ASSERT_EQ(params.get_power(), 7.0 * W);
// }

TEST(AntennaTest, LossAndGainMethods)
{
    Viewer sc;
    CircularFieldOfView fov;
    AntennaParameters params(&fov, 2.0 * m, 0.5 * one, 10.0 * GHz, 5.0 * W);
    Antenna antenna(sc, params);
    Antenna receiver(sc, params);
    Distance range = 1000.0 * km;
    Angle offset   = 0.1 * rad;

    // whatever, just make sure they run
    ASSERT_ANY_THROW(antenna.carrier_to_noise_ratio(receiver, range, offset));
    ASSERT_ANY_THROW(antenna.carrier_to_noise_density(receiver, range, offset));
    ASSERT_NO_THROW(antenna.recieved_power(receiver, range, offset));
    ASSERT_NO_THROW(antenna.free_space_loss(range));
    ASSERT_NO_THROW(antenna.system_loss(receiver, offset));
    ASSERT_NO_THROW(antenna.mispointing_loss(receiver, offset));
    ASSERT_NO_THROW(antenna.polarization_loss(receiver));
    ASSERT_NO_THROW(antenna.atmospheric_loss());
    ASSERT_NO_THROW(antenna.gain());
    ASSERT_NO_THROW(antenna.system_noise_temperature());
    ASSERT_NO_THROW(antenna.receiver_loss());
    ASSERT_NO_THROW(antenna.transmit_loss());
}
