#pragma once

#include <vector>

#include <astro/types/typedefs.hpp>
#include <math/trig.hpp>
#include <units/units.hpp>

#include <access/platforms/sensors/Sensor.hpp>
#include <access/types/typedefs.hpp>

namespace waveguide {
namespace accesslib {

class Antenna : public Sensor {
  public:
    enum class PatternApproximation { BESSEL, SINC_SQUARED };

    Antenna(
        const Length& diameter,
        const Unitless& efficiency,
        const Frequency frequency,
        const Power& power,
        // const Temperature& sysNoiseTemp    = 0.0 * mp_units::si::unit_symbols::K,   // Nonsense
        const Frequency noiseBandwidth     = 0.0 * mp_units::si::unit_symbols::GHz, // Ideal
        const Gain& transmitLoss           = 1.0 * mp_units::one,                   // Ideal
        const Gain& receiverLoss           = 1.0 * mp_units::one,                   // Ideal
        const PatternApproximation pattern = PatternApproximation::BESSEL
    );

    // Signal strength
    CNR carrier_to_noise_ratio(const Antenna& receiver, const Distance& range, const Angle& offsetAngle) const;
    CNR carrier_to_noise_density(const Antenna& receiver, const Distance& range, const Angle& offsetAngle) const;

    // Losses
    Power recieved_power(const Antenna& receiver, const Distance& range, const Angle& offsetAngle) const;
    Gain free_space_loss(const Distance& range) const;
    Gain system_loss(const Antenna& receiver, const Angle& offsetAngle) const;
    Gain mispointing_loss(const Antenna& receiver, const Angle& offsetAngle) const;
    Gain polarization_loss(const Antenna& receiver) const;
    Gain atmospheric_loss() const;

    // Getters
    Gain gain() const;
    Temperature system_noise_temperature() const;
    Gain receiver_loss() const;
    Gain transmit_loss() const;

    // Setters
    void set_pattern_approximation(const PatternApproximation& pattern);

  private:
    Length _diameter;          // reflector diameter
    Unitless _efficiency;      // apature illumination efficiency
    Frequency _frequency;      // carrier frequency
    Frequency _noiseBandwidth; // equivalent noise bandwidth
    Length _wavelength;        // speed of light / frequency
    Power _power;              // transmit power
    Gain _gain;                // peak isotropic power gain
    Power _eirp;               // equivalent isotropic radiator power
    Gain _transmitLoss;
    Gain _receiverLoss;
    PatternApproximation _pattern;
    Temperature _sysNoiseTemp;

    Gain bessel_loss_approximation(const Angle& offsetAngle) const;
    Gain sinc_loss_approximation(const Angle& offsetAngle) const;
    Gain mispointing_loss_approximation_argument(const Angle& offsetAngle) const;
};

} // namespace accesslib
} // namespace waveguide