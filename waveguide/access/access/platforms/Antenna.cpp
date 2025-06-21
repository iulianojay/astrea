#include <access/platforms/Antenna.hpp>

namespace accesslib {

Power Antenna::recieved_power(const Antenna& reciever, const astro::Distance& range, const astro::Angle& offsetAngle) const
{
    return _eirp * reciever.gain() * free_space_loss(range) * system_loss(reciever, offsetAngle);
}

Gain Antenna::free_space_loss(const astro::Distance& range) const
{
    static const auto fixedLoss = mp_units::pow<2>(1.0 / (4.0 * std::numbers::pi) * mp_units::one);
    return fixedLoss * mp_units::pow<2>(_wavelength / range);
}

Gain Antenna::system_loss(const Antenna& reciever, const astro::Angle& offsetAngle) const
{
    return transmit_loss() * mispointing_loss(reciever, offsetAngle) * atmospheric_loss() * reciever.receiver_loss();
}

Gain Antenna::mispointing_loss(const Antenna& reciever, const astro::Angle& offsetAngle) const
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
    return mispointingLoss * polarization_loss(reciever);
}

Gain Antenna::polarization_loss(const Antenna& reciever) const
{
    return 1.0; // Ideal, but generally considered true as they are typically small or zero (exactly zero for circular polarization)
}

Gain Antenna::atmospheric_loss() const
{
    return 1.0; // Ideal, definitely not true
}

Gain Antenna::gain() const { return _gain; }
Gain Antenna::receiver_loss() const { return _receiverLoss; }
Gain Antenna::transmit_loss() const { return _transmitLoss; }

void Antenna::set_pattern_approximation(const PatternApproximation& pattern) { _pattern = pattern; }


Gain Antenna::bessel_loss_approximation(const astro::Angle& offsetAngle) const
{
    const auto u = mispointing_loss_approximation_argument(offsetAngle);
    return 64.0 * mp_units::pow<2>(math::cyl_bessel_j(2.0, u) / mp_units::pow<2>(u));
}

Gain Antenna::sinc_loss_approximation(const astro::Angle& offsetAngle) const
{
    const auto u     = mispointing_loss_approximation_argument(offsetAngle);
    const auto sincU = math::sinc(0.690 * u * mp_units::isq_angle::cotes_angle);
    return sincU * sincU;
}

Gain Antenna::mispointing_loss_approximation_argument(const astro::Angle& offsetAngle) const
{
    static const auto ratio = std::numbers::pi * _diameter / _wavelength;
    return ratio * mp_units::angular::sin(offsetAngle);
}

} // namespace accesslib