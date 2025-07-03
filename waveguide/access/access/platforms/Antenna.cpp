#include <access/platforms/Antenna.hpp>

#include <stdexcept>

#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>

using astro::Angle;
using astro::Distance;

using mp_units::one;
using mp_units::pow;
using mp_units::angular::sin;
using mp_units::isq_angle::cotes_angle;

namespace accesslib {

Antenna::Antenna(
    const astro::Length& diameter,
    const astro::Unitless& efficiency,
    const Frequency frequency,
    const Power& power,
    // const Temperature& sysNoiseTemp,
    const Frequency noiseBandwidth,
    const Gain& transmitLoss,
    const Gain& receiverLoss,
    const PatternApproximation pattern
) :
    Sensor::Sensor(),
    _diameter(diameter),
    _efficiency(efficiency),
    _frequency(frequency),
    _noiseBandwidth(noiseBandwidth),
    // _sysNoiseTemp(sysNoiseTemp),
    _wavelength(speed_of_light_in_vacuum / _frequency),
    _gain(efficiency * mp_units::pow<2>(std::numbers::pi * (_diameter / _wavelength))),
    _power(power),
    _eirp(_gain * _power),
    _transmitLoss(transmitLoss),
    _receiverLoss(receiverLoss),
    _pattern(pattern)
{
}

// CNR Antenna::carrier_to_noise_ratio(const Antenna& receiver, const Distance& range, const Angle& offsetAngle) const
// {
//     return recieved_power(receiver, range, offsetAngle) / receiver.system_noise_temperature() / boltzmann_constant * _noiseBandwidth;
// }

// CNR Antenna::carrier_to_noise_density(const Antenna& receiver, const Distance& range, const Angle& offsetAngle) const
// {
//     return recieved_power(receiver, range, offsetAngle) / receiver.system_noise_temperature() / boltzmann_constant;
// }

Power Antenna::recieved_power(const Antenna& receiver, const Distance& range, const Angle& offsetAngle) const
{
    return _eirp * receiver.gain() * free_space_loss(range) * system_loss(receiver, offsetAngle);
}

Gain Antenna::free_space_loss(const Distance& range) const
{
    static const auto fixedLoss = pow<2>(1.0 / (4.0 * std::numbers::pi) * one);
    return fixedLoss * pow<2>(_wavelength / range);
}

Gain Antenna::system_loss(const Antenna& receiver, const Angle& offsetAngle) const
{
    return transmit_loss() * mispointing_loss(receiver, offsetAngle) * atmospheric_loss() * receiver.receiver_loss();
}

Gain Antenna::mispointing_loss(const Antenna& receiver, const Angle& offsetAngle) const
{
    // Including polarization losses here
    Gain mispointingLoss;
    switch (_pattern) {
        case (PatternApproximation::BESSEL): {
            mispointingLoss = bessel_loss_approximation(offsetAngle);
            break;
        }
        case (PatternApproximation::SINC_SQUARED): {
            mispointingLoss = sinc_loss_approximation(offsetAngle);
            break;
        }
        default: throw std::runtime_error("Unrecognized pattern approximation for mispointing losses.");
    }
    return mispointingLoss * polarization_loss(receiver);
}

Gain Antenna::polarization_loss(const Antenna& receiver) const
{
    return 1.0; // Ideal, but generally considered true as they are typically small or zero (exactly zero for circular polarization)
}

Gain Antenna::atmospheric_loss() const
{
    return 1.0; // Ideal, definitely not true
}

Gain Antenna::gain() const { return _gain; }
Temperature Antenna::system_noise_temperature() const { return _sysNoiseTemp; }
Gain Antenna::receiver_loss() const { return _receiverLoss; }
Gain Antenna::transmit_loss() const { return _transmitLoss; }

void Antenna::set_pattern_approximation(const PatternApproximation& pattern) { _pattern = pattern; }


Gain Antenna::bessel_loss_approximation(const Angle& offsetAngle) const
{
    const auto u = mispointing_loss_approximation_argument(offsetAngle);
    return 64.0 * pow<2>(math::cyl_bessel_j(2.0, u) / pow<2>(u));
}

Gain Antenna::sinc_loss_approximation(const Angle& offsetAngle) const
{
    const auto u     = mispointing_loss_approximation_argument(offsetAngle);
    const auto sincU = math::sinc(0.690 * u * cotes_angle);
    return sincU * sincU;
}

Gain Antenna::mispointing_loss_approximation_argument(const Angle& offsetAngle) const
{
    static const auto ratio = std::numbers::pi * _diameter / _wavelength;
    return ratio * sin(offsetAngle);
}

} // namespace accesslib