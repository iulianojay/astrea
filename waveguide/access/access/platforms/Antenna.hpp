#pragma once

#include <vector>

#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

#include <astro/types/typedefs.hpp>
#include <astro/units/units.hpp>

#include <access/platforms/Sensor.hpp>
#include <access/types/typedefs.hpp>
#include <access/units/constants.hpp>
#include <access/units/units.hpp>

namespace accesslib {


class Antenna : public Sensor {
  public:
    Antenna(
        const astro::Length& diameter,
        const astro::Unitless& efficiency,
        const Frequency frequency,
        const Power& power,
        const Gain& transmitLoss = 1.0, // Ideal
        const Gain& receiverLoss = 1.0  // Ideal
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
        _receiverLoss(receiverLoss)
    {
    }

    Power recieved_power(const Antenna& reciever, const astro::Distance& range) const
    {
        return _eirp * reciever.gain() * free_space_loss(range) * system_loss(reciever);
    }

    Gain free_space_loss(const astro::Distance& range) const
    {
        return mp_units::pow<2>(0.25 / (std::numbers::pi * (range / _wavelength)));
    }

    Gain system_loss(const Antenna& reciever) const
    {
        return transmit_loss() * mispointing_loss(reciever) * atmospheric_loss() * reciever.receiver_loss();
    }

    virtual Gain mispointing_loss(const Antenna& reciever) const
    {
        // Including polarization losses here
        return 1.0; // Ideal
    }
    virtual Gain atmospheric_loss() const
    {
        return 1.0; // Ideal
    }

    Gain gain() const { return _gain; }
    Gain receiver_loss() const { return _receiverLoss; }
    virtual Gain transmit_loss() const { return _transmitLoss; }

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
};

} // namespace accesslib