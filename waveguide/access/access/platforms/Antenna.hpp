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

    Power recieved_power(const Antenna& reciever, const astro::Distance& range, const astro::Angle& offsetAngle) const;
    Gain free_space_loss(const astro::Distance& range) const;
    Gain system_loss(const Antenna& reciever, const astro::Angle& offsetAngle) const;
    Gain mispointing_loss(const Antenna& reciever, const astro::Angle& offsetAngle) const;
    Gain polarization_loss(const Antenna& reciever) const;
    Gain atmospheric_loss() const;

    Gain gain() const;
    Gain receiver_loss() const;
    Gain transmit_loss() const;

    void set_pattern_approximation(const PatternApproximation& pattern);

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

    Gain bessel_loss_approximation(const astro::Angle& offsetAngle) const;
    Gain sinc_loss_approximation(const astro::Angle& offsetAngle) const;
    Gain mispointing_loss_approximation_argument(const astro::Angle& offsetAngle) const;
};

} // namespace accesslib