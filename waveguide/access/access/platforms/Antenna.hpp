#pragma once

#include <vector>

#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>

#include <astro/types/typedefs.hpp>
#include <astro/units/units.hpp>

#include <access/platforms/Sensor.hpp>
#include <access/types/typedefs.hpp>
#include <access/units/constants.hpp>
#include <access/units/units.hpp>

#include <math/trig.hpp>

namespace accesslib {


class Antenna : public Sensor {
  public:
    enum class PatternApproximation { BESSEL, SINC_SQUARED };

    Antenna(
        const astro::Length& diameter,
        const astro::Unitless& efficiency,
        const Frequency frequency,
        const Power& power,
        const Gain& transmitLoss           = 1.0 * mp_units::one, // Ideal
        const Gain& receiverLoss           = 1.0 * mp_units::one, // Ideal
        const PatternApproximation pattern = PatternApproximation::BESSEL
    ) :
        Sensor::Sensor(),
        _diameter(diameter),
        _efficiency(efficiency),
        _frequency(frequency),
        _wavelength(speed_of_light_in_vacuum / _frequency),
        _gain(efficiency * mp_units::pow<2>(std::numbers::pi * (_diameter / _wavelength))),
        _power(power),
        _eirp(_gain * _power),
        _transmitLoss(transmitLoss),
        _receiverLoss(receiverLoss),
        _pattern(pattern)
    {
    }

    Power recieved_power(const Antenna& reciever, const astro::Distance& range, const astro::Angle& offsetAngle) const
    {
        return _eirp * reciever.gain() * free_space_loss(range) * system_loss(reciever, offsetAngle);
    }

    Gain free_space_loss(const astro::Distance& range) const
    {
        static const auto fixedLoss = mp_units::pow<2>(1.0 / (4.0 * std::numbers::pi) * mp_units::one);
        return fixedLoss * mp_units::pow<2>(_wavelength / range);
    }

    Gain system_loss(const Antenna& reciever, const astro::Angle& offsetAngle) const
    {
        return transmit_loss() * mispointing_loss(reciever, offsetAngle) * atmospheric_loss() * reciever.receiver_loss();
    }

    virtual Gain mispointing_loss(const Antenna& reciever, const astro::Angle& offsetAngle) const
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

    virtual Gain polarization_loss(const Antenna& reciever) const
    {
        return 1.0; // Ideal, but generally considered true as they are typically small or zero (exactly zero for circular polarization)
    }

    virtual Gain atmospheric_loss() const
    {
        return 1.0; // Ideal, definitely not true
    }

    Gain gain() const { return _gain; }
    Gain receiver_loss() const { return _receiverLoss; }
    virtual Gain transmit_loss() const { return _transmitLoss; }

    void set_pattern_approximation(const PatternApproximation& pattern) { _pattern = pattern; }

  private:
    astro::Length _diameter;     // reflector diameter
    astro::Unitless _efficiency; // apature illumination efficiency
    Frequency _frequency;        // carrier frequency
    astro::Length _wavelength;   // speed of light / frequency
    Power _power;                // transmit power
    Gain _gain;                  // peak isotropic power gain
    Power _eirp;                 // equivalent isotropic radiator power

    Gain _transmitLoss;
    Gain _receiverLoss;
    PatternApproximation _pattern;

    Gain bessel_loss_approximation(const astro::Angle& offsetAngle) const
    {
        const auto u = mispointing_loss_approximation_argument(offsetAngle);
        return 64.0 * mp_units::pow<2>(math::cyl_bessel_j(2.0, u) / mp_units::pow<2>(u));
    }

    Gain sinc_loss_approximation(const astro::Angle& offsetAngle) const
    {
        const auto u     = mispointing_loss_approximation_argument(offsetAngle);
        const auto sincU = math::sinc(0.690 * u * mp_units::isq_angle::cotes_angle);
        return sincU * sincU;
    }

    Gain mispointing_loss_approximation_argument(const astro::Angle& offsetAngle) const
    {
        static const auto ratio = std::numbers::pi * _diameter / _wavelength;
        return ratio * mp_units::angular::sin(offsetAngle);
    }
};

} // namespace accesslib