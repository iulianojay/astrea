/**
 * @file Antenna.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Antenna class for representing antenna properties and behaviors.
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <vector>

#include <astro/state/CartesianVector.hpp>
#include <astro/state/frames/frames.hpp>
#include <astro/types/typedefs.hpp>
#include <math/trig.hpp>
#include <units/units.hpp>

#include <trace/platforms/sensors/Sensor.hpp>
#include <trace/types/typedefs.hpp>

namespace astrea {
namespace trace {

/**
 * @brief Enum class for different antenna pattern approximations.
 */
enum class PatternApproximation {
    BESSEL,      //!< Bessel function approximation
    SINC_SQUARED //!< Sinc-squared approximation
};

/**
 * @brief Class for storing and managing antenna parameters.
 */
class AntennaParameters : public SensorParameters {
  public:
    /**
     * @brief Construct a new Antenna Parameters object
     *
     * @param fov Field of View for the antenna.
     * @param diameter Reflector diameter.
     * @param efficiency Aperture illumination efficiency.
     * @param frequency Carrier frequency.
     * @param power Transmit power.
     * @param boresight Boresight direction in RIC coordinates (default is Nadir).
     * @param attachmentPoint Attachment point in RIC coordinates (default is Center).
     * @param noiseBandwidth Equivalent noise bandwidth (default is 0.0, ideal).
     * @param transmitLoss Transmit loss (default is 1.0, ideal).
     * @param receiverLoss Receiver loss (default is 1.0, ideal).
     * @param pattern Pattern approximation method (default is Bessel).
     */
    AntennaParameters(
        const FieldOfView* fov,
        const Length& diameter,
        const Unitless& efficiency,
        const Frequency& frequency,
        const Power& power,
        const astro::RadiusVector<astro::RIC>& boresight       = { -1.0 * astrea::detail::distance_unit, // Nadir
                                                                   0.0 * astrea::detail::distance_unit,
                                                                   0.0 * astrea::detail::distance_unit },
        const astro::RadiusVector<astro::RIC>& attachmentPoint = { 0.0 * astrea::detail::distance_unit, // Center
                                                                   0.0 * astrea::detail::distance_unit,
                                                                   0.0 * astrea::detail::distance_unit },
        const Frequency& noiseBandwidth                        = 0.0 * mp_units::si::unit_symbols::GHz,
        const Gain& transmitLoss                               = 1.0 * mp_units::one,
        const Gain& receiverLoss                               = 1.0 * mp_units::one,
        const PatternApproximation& pattern                    = PatternApproximation::BESSEL
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

    /**
     * @brief Default constructor for AntennaParameters.
     */
    ~AntennaParameters() = default;

    /**
     * @brief Get the diameter of the antenna.
     *
     * @return Length Diameter of the antenna.
     */
    Length get_diameter() const { return _diameter; }

    /**
     * @brief Get the efficiency of the antenna.
     *
     * @return Unitless Efficiency of the antenna.
     */
    Unitless get_efficiency() const { return _efficiency; }

    /**
     * @brief Get the frequency of the antenna.
     *
     * @return Frequency Frequency of the antenna.
     */
    Frequency get_frequency() const { return _frequency; }

    /**
     * @brief Get the power of the antenna.
     *
     * @return Power Power of the antenna.
     */
    Power get_power() const { return _power; }

    /**
     * @brief Get the noise bandwidth of the antenna.
     *
     * @return Frequency Noise bandwidth of the antenna.
     */
    Frequency get_noise_bandwidth() const { return _noiseBandwidth; }

    /**
     * @brief Get the transmit loss of the antenna.
     *
     * @return Gain Transmit loss of the antenna.
     */
    Gain get_transmit_loss() const { return _transmitLoss; }

    /**
     * @brief Get the receiver loss of the antenna.
     *
     * @return Gain Receiver loss of the antenna.
     */
    Gain get_receiver_loss() const { return _receiverLoss; }

    /**
     * @brief Get the pattern approximation method of the antenna.
     *
     * @return PatternApproximation Pattern approximation method of the antenna.
     */
    PatternApproximation get_pattern() const { return _pattern; }

    /**
     * @brief Get the gain of the antenna.
     *
     * @return Gain Gain of the antenna.
     */
    Gain get_gain() const { return _gain; }

    /**
     * @brief Get the equivalent isotropic radiated power (EIRP) of the antenna.
     *
     * @return Power EIRP of the antenna.
     */
    Power get_eirp() const { return _eirp; }

    /**
     * @brief Get the system noise temperature of the antenna.
     *
     * @return Temperature System noise temperature of the antenna.
     */
    Temperature get_system_noise_temperature() const { return _sysNoiseTemp; }

    /**
     * @brief Get the wavelength of the antenna.
     *
     * @return Length Wavelength of the antenna.
     */
    Length get_wavelength() const { return _wavelength; }

    /**
     * @brief Set the diameter of the antenna.
     *
     * @param diameter Length Diameter of the antenna.
     */
    void set_diameter(const Length& diameter) { _diameter = diameter; }

    /**
     * @brief Set the efficiency of the antenna.
     *
     * @param efficiency Unitless Efficiency of the antenna.
     */
    void set_efficiency(const Unitless& efficiency) { _efficiency = efficiency; }

    /**
     * @brief Set the frequency of the antenna.
     *
     * @param frequency Frequency Frequency of the antenna.
     */
    void set_frequency(const Frequency& frequency) { _frequency = frequency; }

    /**
     * @brief Set the power of the antenna.
     *
     * @param power Power Power of the antenna.
     */
    void set_power(const Power& power) { _power = power; }

    /**
     * @brief Set the noise bandwidth of the antenna.
     *
     * @param noiseBandwidth Frequency Noise bandwidth of the antenna.
     */
    void set_noise_bandwidth(const Frequency& noiseBandwidth) { _noiseBandwidth = noiseBandwidth; }

    /**
     * @brief Set the transmit loss of the antenna.
     *
     * @param transmitLoss Gain Transmit loss of the antenna.
     */
    void set_transmit_loss(const Gain& transmitLoss) { _transmitLoss = transmitLoss; }

    /**
     * @brief Set the receiver loss of the antenna.
     *
     * @param receiverLoss Gain Receiver loss of the antenna.
     */
    void set_receiver_loss(const Gain& receiverLoss) { _receiverLoss = receiverLoss; }

    /**
     * @brief Set the pattern approximation method of the antenna.
     *
     * @param pattern PatternApproximation Pattern approximation method of the antenna.
     */
    void set_pattern(const PatternApproximation& pattern) { _pattern = pattern; }

  private:
    Length _diameter;              //!< Reflector diameter
    Unitless _efficiency;          //!< Aperture illumination efficiency
    Frequency _frequency;          //!< Carrier frequency
    Power _power;                  //!< Transmit power
    Frequency _noiseBandwidth;     //!< Equivalent noise bandwidth
    Gain _transmitLoss;            //!< Transmit loss
    Gain _receiverLoss;            //!< Receiver loss
    PatternApproximation _pattern; //!< Pattern approximation method
    Length _wavelength;            //!< Speed of light / frequency
    Gain _gain;                    //!< Peak isotropic power gain
    Power _eirp;                   //!< Equivalent isotropic radiator power
    Temperature _sysNoiseTemp;     //!< System noise temperature
};

/**
 * @class Antenna
 * @brief Represents an antenna with properties such as diameter, efficiency, frequency, and power.
 *
 * The Antenna class provides methods to calculate signal strength, losses, and other antenna-related properties.
 */
class Antenna : public Sensor {
  public:
    /**
     * @brief Construct a new Antenna object.
     *
     */
    template <typename T>
    Antenna(const T& parent, const AntennaParameters& antennaParameters) :
        Sensor::Sensor(parent, antennaParameters),
        _parameters(antennaParameters)
    {
    }

    /**
     * @brief Calculate the carrier-to-noise ratio (CNR) for the antenna.
     *
     * @param receiver Antenna object representing the receiver.
     * @param range Distance to the receiver.
     * @param offsetAngle Angle offset from the boresight.
     * @return CNR The calculated carrier-to-noise ratio.
     */
    CNR carrier_to_noise_ratio(const Antenna& receiver, const Distance& range, const Angle& offsetAngle) const;

    /**
     * @brief Calculate the carrier-to-noise density (CND) for the antenna.
     *
     * @param receiver Antenna object representing the receiver.
     * @param range Distance to the receiver.
     * @param offsetAngle Angle offset from the boresight.
     * @return CNR The calculated carrier-to-noise density.
     */
    CNR carrier_to_noise_density(const Antenna& receiver, const Distance& range, const Angle& offsetAngle) const;

    /**
     * @brief Calculate the received power at the receiver.
     *
     * @param receiver Antenna object representing the receiver.
     * @param range Distance to the receiver.
     * @param offsetAngle Angle offset from the boresight.
     * @return Power The calculated received power.
     */
    Power recieved_power(const Antenna& receiver, const Distance& range, const Angle& offsetAngle) const;

    /**
     * @brief Calculate the free space loss for the antenna.
     *
     * @param range Distance to the receiver.
     * @return Gain The calculated free space loss.
     */
    Gain free_space_loss(const Distance& range) const;

    /**
     * @brief Calculate the system loss for the antenna.
     *
     * @param receiver Antenna object representing the receiver.
     * @param offsetAngle Angle offset from the boresight.
     * @return Gain The calculated system loss.
     */
    Gain system_loss(const Antenna& receiver, const Angle& offsetAngle) const;

    /**
     * @brief Calculate the mispointing loss for the antenna.
     *
     * @param receiver Antenna object representing the receiver.
     * @param offsetAngle Angle offset from the boresight.
     * @return Gain The calculated mispointing loss.
     */
    Gain mispointing_loss(const Antenna& receiver, const Angle& offsetAngle) const;

    /**
     * @brief Calculate the polarization loss for the antenna.
     *
     * @param receiver Antenna object representing the receiver.
     * @return Gain The calculated polarization loss.
     */
    Gain polarization_loss(const Antenna& receiver) const;

    /**
     * @brief Calculate the atmospheric loss for the antenna.
     *
     * @return Gain The calculated atmospheric loss.
     */
    Gain atmospheric_loss() const;

    /**
     * @brief Get antenna gain.
     *
     * @return Gain The gain of the antenna.
     */
    Gain gain() const;

    /**
     * @brief Get the system noise temperature.
     *
     * @return Temperature The system noise temperature.
     */
    Temperature system_noise_temperature() const;

    /**
     * @brief Get the receiver loss.
     *
     * @return Gain The receiver loss.
     */
    Gain receiver_loss() const;

    /**
     * @brief Get the transmit loss.
     *
     * @return Gain The transmit loss.
     */
    Gain transmit_loss() const;

    /**
     * @brief Set the pattern approximation method.
     *
     * @param pattern Pattern approximation method to set.
     */
    void set_pattern_approximation(const PatternApproximation& pattern);

  private:
    AntennaParameters _parameters;

    /**
     * @brief Calculate the Bessel loss approximation for the antenna.
     *
     * @param offsetAngle Angle offset from the boresight.
     * @return Gain The calculated Bessel loss.
     */
    Gain bessel_loss_approximation(const Angle& offsetAngle) const;

    /**
     * @brief Calculate the Sinc loss approximation for the antenna.
     *
     * @param offsetAngle Angle offset from the boresight.
     * @return Gain The calculated Sinc loss.
     */
    Gain sinc_loss_approximation(const Angle& offsetAngle) const;

    /**
     * @brief Calculate the mispointing loss approximation argument for the antenna.
     *
     * @param offsetAngle Angle offset from the boresight.
     * @return Gain The calculated mispointing loss approximation argument.
     */
    Gain mispointing_loss_approximation_argument(const Angle& offsetAngle) const;
};

} // namespace trace
} // namespace astrea