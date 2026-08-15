

# File Antenna.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**platforms**](dir_4dbda61db413396ce1d3b920f98dbf93.md) **>** [**sensors**](dir_4c34a36d272c54a3547c6d2c18e9dea2.md) **>** [**Antenna.hpp**](Antenna_8hpp.md)

[Go to the documentation of this file](Antenna_8hpp.md)


```C++

#pragma once

#include <vector>

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions/dynamic_frames/tags.hpp>
#include <astro/types/typedefs.hpp>
#include <math/trig.hpp>
#include <units/units.hpp>

#include <trace/platforms/sensors/Sensor.hpp>
#include <trace/types/typedefs.hpp>

namespace astrea {
namespace trace {

enum class PatternApproximation {
    BESSEL,      
    SINC_SQUARED 
};

class AntennaParameters : public SensorParameters {
  public:
    AntennaParameters(
        const FieldOfView* fov,
        const Length& diameter,
        const Unitless& efficiency,
        const Frequency& frequency,
        const Power& power,
        const astro::CartesianVector<Distance, astro::frames::dynamic::ric>& boresight       = astro::NADIR_RIC,
        const astro::CartesianVector<Distance, astro::frames::dynamic::ric>& attachmentPoint = astro::CENTER,
        const Frequency& noiseBandwidth     = 0.0 * mp_units::si::unit_symbols::GHz,
        const Gain& transmitLoss            = 1.0 * mp_units::one,
        const Gain& receiverLoss            = 1.0 * mp_units::one,
        const PatternApproximation& pattern = PatternApproximation::BESSEL
    ) :
        SensorParameters::SensorParameters(fov, boresight, attachmentPoint),
        _diameter(diameter),
        _efficiency(efficiency),
        _frequency(frequency),
        _power(power),
        _noiseBandwidth(noiseBandwidth),
        _transmitLoss(transmitLoss),
        _receiverLoss(receiverLoss),
        _pattern(pattern),
        _wavelength(speed_of_light_in_vacuum / _frequency),
        _gain(efficiency * mp_units::pow<2>(std::numbers::pi * (_diameter / _wavelength))),
        _eirp(_gain * _power)

    {
    }

    ~AntennaParameters() = default;

    Length get_diameter() const { return _diameter; }

    Unitless get_efficiency() const { return _efficiency; }

    Frequency get_frequency() const { return _frequency; }

    Power get_power() const { return _power; }

    Frequency get_noise_bandwidth() const { return _noiseBandwidth; }

    Gain get_transmit_loss() const { return _transmitLoss; }

    Gain get_receiver_loss() const { return _receiverLoss; }

    PatternApproximation get_pattern() const { return _pattern; }

    Gain get_gain() const { return _gain; }

    Power get_eirp() const { return _eirp; }

    Temperature get_system_noise_temperature() const { return _sysNoiseTemp; }

    Length get_wavelength() const { return _wavelength; }

    void set_diameter(const Length& diameter) { _diameter = diameter; }

    void set_efficiency(const Unitless& efficiency) { _efficiency = efficiency; }

    void set_frequency(const Frequency& frequency) { _frequency = frequency; }

    void set_power(const Power& power) { _power = power; }

    void set_noise_bandwidth(const Frequency& noiseBandwidth) { _noiseBandwidth = noiseBandwidth; }

    void set_transmit_loss(const Gain& transmitLoss) { _transmitLoss = transmitLoss; }

    void set_receiver_loss(const Gain& receiverLoss) { _receiverLoss = receiverLoss; }

    void set_pattern(const PatternApproximation& pattern) { _pattern = pattern; }

  private:
    Length _diameter;              
    Unitless _efficiency;          
    Frequency _frequency;          
    Power _power;                  
    Frequency _noiseBandwidth;     
    Gain _transmitLoss;            
    Gain _receiverLoss;            
    PatternApproximation _pattern; 
    Length _wavelength;            
    Gain _gain;                    
    Power _eirp;                   

    Temperature _sysNoiseTemp = mp_units::point<mp_units::si::unit_symbols::deg_C>(0.0); 
};

class Antenna : public Sensor {
  public:
    template <typename T>
    Antenna(const T& parent, const AntennaParameters& antennaParameters) :
        Sensor::Sensor(parent, antennaParameters),
        _parameters(antennaParameters)
    {
    }

    CNR carrier_to_noise_ratio(const Antenna& receiver, const Distance& range, const Angle& offsetAngle) const;

    CNR carrier_to_noise_density(const Antenna& receiver, const Distance& range, const Angle& offsetAngle) const;

    Power recieved_power(const Antenna& receiver, const Distance& range, const Angle& offsetAngle) const;

    Gain free_space_loss(const Distance& range) const;

    Gain system_loss(const Antenna& receiver, const Angle& offsetAngle) const;

    Gain mispointing_loss(const Antenna& receiver, const Angle& offsetAngle) const;

    Gain polarization_loss(const Antenna& receiver) const;

    Gain atmospheric_loss() const;

    Gain gain() const;

    Temperature system_noise_temperature() const;

    Gain receiver_loss() const;

    Gain transmit_loss() const;

    void set_pattern_approximation(const PatternApproximation& pattern);

  private:
    AntennaParameters _parameters;

    Gain bessel_loss_approximation(const Angle& offsetAngle) const;

    Gain sinc_loss_approximation(const Angle& offsetAngle) const;

    Gain mispointing_loss_approximation_argument(const Angle& offsetAngle) const;
};

} // namespace trace
} // namespace astrea
```


