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

#include <astro/types/typedefs.hpp>
#include <math/trig.hpp>
#include <units/units.hpp>

#include <access/platforms/sensors/Sensor.hpp>
#include <access/types/typedefs.hpp>

namespace waveguide {
namespace accesslib {

/**
 * @class Antenna
 * @brief Represents an antenna with properties such as diameter, efficiency, frequency, and power.
 *
 * The Antenna class provides methods to calculate signal strength, losses, and other antenna-related properties.
 */
class Antenna : public Sensor {
  public:
    /**
     * @brief Enum class for different antenna pattern approximations.
     */
    enum class PatternApproximation {
        BESSEL,      //<! Bessel function approximation
        SINC_SQUARED //<! Sinc-squared approximation
    };

    /**
     * @brief Construct a new Antenna object.
     *
     * @param diameter Reflector diameter.
     * @param efficiency Aperture illumination efficiency.
     * @param frequency Carrier frequency.
     * @param power Transmit power.
     * @param noiseBandwidth Equivalent noise bandwidth (default is 0.0, ideal).
     * @param transmitLoss Transmit loss (default is 1.0, ideal).
     * @param receiverLoss Receiver loss (default is 1.0, ideal).
     * @param pattern Pattern approximation method (default is Bessel).
     */
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
    Length _diameter;              //<! Reflector diameter
    Unitless _efficiency;          //<! Apature illumination efficiency
    Frequency _frequency;          //<! Carrier frequency
    Frequency _noiseBandwidth;     //<! Equivalent noise bandwidth
    Length _wavelength;            //<! Speed of light / frequency
    Power _power;                  //<! Transmit power
    Gain _gain;                    //<! Peak isotropic power gain
    Power _eirp;                   //<! Equivalent isotropic radiator power
    Gain _transmitLoss;            //<! Transmit loss
    Gain _receiverLoss;            //<! Receiver loss
    PatternApproximation _pattern; //<! Pattern approximation method
    Temperature _sysNoiseTemp;     //<! System noise temperature

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

} // namespace accesslib
} // namespace waveguide