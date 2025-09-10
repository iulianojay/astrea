#include <trace/platforms/sensors/Antenna.hpp>

#include <stdexcept>

#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>

using mp_units::one;
using mp_units::pow;
using mp_units::angular::sin;
using mp_units::isq_angle::cotes_angle;

namespace astrea {
namespace trace {

CNR Antenna::carrier_to_noise_ratio(const Antenna& receiver, const Distance& range, const Angle& offsetAngle) const
{
    throw std::runtime_error("CNR calculation not yet implemented.");
    // return recieved_power(receiver, range, offsetAngle) / receiver.system_noise_temperature() / boltzmann_constant * _noiseBandwidth;
}

CNR Antenna::carrier_to_noise_density(const Antenna& receiver, const Distance& range, const Angle& offsetAngle) const
{
    throw std::runtime_error("CND calculation not yet implemented.");
    // return recieved_power(receiver, range, offsetAngle) / receiver.system_noise_temperature() / boltzmann_constant;
}

Power Antenna::recieved_power(const Antenna& receiver, const Distance& range, const Angle& offsetAngle) const
{
    return _parameters.get_eirp() * receiver.gain() * free_space_loss(range) * system_loss(receiver, offsetAngle);
}

Gain Antenna::free_space_loss(const Distance& range) const
{
    static const auto fixedLoss = pow<2>(1.0 / (4.0 * std::numbers::pi) * one);
    return fixedLoss * pow<2>(_parameters.get_wavelength() / range);
}

Gain Antenna::system_loss(const Antenna& receiver, const Angle& offsetAngle) const
{
    return _parameters.get_transmit_loss() * mispointing_loss(receiver, offsetAngle) * atmospheric_loss() * receiver.receiver_loss();
}

Gain Antenna::mispointing_loss(const Antenna& receiver, const Angle& offsetAngle) const
{
    // Including polarization losses here
    Gain mispointingLoss;
    switch (_parameters.get_pattern()) {
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

Gain Antenna::gain() const { return _parameters.get_gain(); }
Temperature Antenna::system_noise_temperature() const { return _parameters.get_system_noise_temperature(); }
Gain Antenna::receiver_loss() const { return _parameters.get_receiver_loss(); }
Gain Antenna::transmit_loss() const { return _parameters.get_transmit_loss(); }

void Antenna::set_pattern_approximation(const PatternApproximation& pattern) { _parameters.set_pattern(pattern); }


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
    static const auto ratio = std::numbers::pi * _parameters.get_diameter() / _parameters.get_wavelength();
    return ratio * sin(offsetAngle);
}

} // namespace trace
} // namespace astrea