/**
 * @file TwoLineElements.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the TwoLineElements class
 * @version 0.1
 * @date 2025-08-27
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <array>
#include <iomanip>
#include <iostream>
#include <variant>

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing the two-line element (TLE) format for orbital data.
 */
class TwoLineElements {

  /**
   * @brief Overloaded output stream operator for TwoLineElements.
   */
    friend std::ostream& operator<<(std::ostream&, TwoLineElements const&);

    friend TwoLineElementsPartial;

  public:
    /**
     * @brief Default constructor.
     */
    TwoLineElements() = default;

    /**
     * @brief Construct a new Two Line Elements object from modern TLEs
     *
     * @param rawTle The raw TLE data.
     * @param sys The astrodynamics system.
     */
    TwoLineElements(const std::array<std::string, 3> rawTle, const AstrodynamicsSystem& sys);

    /**
     * @brief Construct a new Two Line Elements object from classic TLEs
     *
     * @param rawTle The raw TLE data.
     * @param sys The astrodynamics system.
     */
    TwoLineElements(const std::array<std::string, 2> rawTle, const AstrodynamicsSystem& sys);

    /**
     * @brief Copy constructor.
     * 
     * @param other The other TwoLineElements object to copy from.
     */
    TwoLineElements(const TwoLineElements&);

    /**
     * @brief Move constructor.
     * 
     * @param other The other TwoLineElements object to move from.
     */
    TwoLineElements(TwoLineElements&&) noexcept;

    /**
     * @brief Move assignment operator.
     * 
     * @param other The other TwoLineElements object to move from.
     * 
     * @return TwoLineElements& Reference to this object after assignment.
     */
    TwoLineElements& operator=(TwoLineElements&&) noexcept;

    /**
     * @brief Copy assignment operator.
     * 
     * @param other The other TwoLineElements object to copy from.
     * 
     * @return TwoLineElements& Reference to this object after assignment.
     */
    TwoLineElements& operator=(const TwoLineElements&);

    /**
     * @brief Default destructor.
     */
    ~TwoLineElements() = default;

    /**
     * @brief Equality operator.
     * 
     * @param other The other TwoLineElements object to compare with.
     * @return true if the objects are equal, false otherwise.
     */
    bool operator==(const TwoLineElements& other) const;

    /**
     * @brief Inequality operator.
     * 
     * @param other The other TwoLineElements object to compare with.
     * @return true if the objects are not equal, false otherwise.
     */
    bool operator!=(const TwoLineElements& other) const;

    /**
     * @brief Get the raw TLE data.
     * 
     * @return std::array<std::string, 2> The raw TLE data.
     */
    std::array<std::string, 2> get_raw_tle() const { return _rawTLE; }

    /**
     * @brief Get the 1st line of the TLE.
     * 
     * @return std::string The 1st line of the TLE.
     */
    std::string get_1st_line() const { return _rawTLE[0]; }

    /**
     * @brief Get the 2nd line of the TLE.
     * 
     * @return std::string The 2nd line of the TLE.
     */
    std::string get_2nd_line() const { return _rawTLE[1]; }

    /**
     * @brief Get the name of the satellite.
     * 
     * @return std::string The name of the satellite.
     */
    std::string get_name() const { return _name; }

    /**
     * @brief Get the catalogue number of the satellite.
     * 
     * @return unsigned The catalogue number of the satellite.
     */
    unsigned get_catalogue_number() const { return _catalogueNumber; }

    /**
     * @brief Get the classification of the satellite.
     * 
     * @return std::string The classification of the satellite.
     */
    std::string get_classification() const { return _classification; }

    /**
     * @brief Get the launch year of the satellite.
     * 
     * @return std::string The launch year of the satellite.
     */
    std::string get_launch_year() const { return _launchYear; }

    /**
     * @brief Get the launch number of the satellite.
     * 
     * @return std::string The launch number of the satellite.
     */
    std::string get_launch_number() const { return _launchNumber; }

    /**
     * @brief Get the launch piece of the satellite.
     * 
     * @return std::string The launch piece of the satellite.
     */
    std::string get_launch_piece() const { return _launchPiece; }

    /**
     * @brief Get the epoch of the satellite.
     * 
     * @return Date The epoch of the satellite.
     */
    Date get_epoch() const { return _epoch; }

    /**
     * @brief Get the 1st derivative of the mean motion.
     * 
     * @return MeanMotion1stDer The 1st derivative of the mean motion.
     */
    MeanMotion1stDer get_mean_motion_1st_derivative() const { return _meanMotion1st; }

    /**
     * @brief Get the 2nd derivative of the mean motion.
     * 
     * @return MeanMotion2ndDer The 2nd derivative of the mean motion.
     */
    MeanMotion2ndDer get_mean_motion_2nd_derivative() const { return _meanMotion2nd; }

    /**
     * @brief Get the ballistic coefficient of the satellite.
     * 
     * @return BallisticCoefficient The ballistic coefficient of the satellite.
     */
    BallisticCoefficient get_ballistic_coefficient() const { return _ballisticCoefficient; }

    /**
     * @brief Get the ephemeris type of the satellite.
     * 
     * @return std::size_t The ephemeris type of the satellite.
     */
    std::size_t get_ephemeris_type() const { return _ephemerisType; }

    /**
     * @brief Get the element set number of the satellite.
     * 
     * @return std::size_t The element set number of the satellite.
     */
    std::size_t get_element_set_number() const { return _elementSetNo; }

    /**
     * @brief Get the 1st checksum of the satellite.
     * 
     * @return std::size_t The 1st checksum of the satellite.
     */
    std::size_t get_check_sum1() const { return _checkSum1; }

    /**
     * @brief Get the semimajor axis of the satellite.
     * 
     * @return Distance The semimajor axis of the satellite.
     */
    Distance get_semimajor() const { return _elements.get_semimajor(); }

    /**
     * @brief Get the eccentricity of the satellite.
     * 
     * @return Unitless The eccentricity of the satellite.
     */
    Unitless get_eccentricity() const { return _elements.get_eccentricity(); }

    /**
     * @brief Get the inclination of the satellite.
     * 
     * @return Angle The inclination of the satellite.
     */
    Angle get_inclination() const { return _elements.get_inclination(); }

    /**
     * @brief Get the right ascension of the satellite.
     * 
     * @return Angle The right ascension of the satellite.
     */
    Angle get_right_ascension() const { return _elements.get_right_ascension(); }

    /**
     * @brief Get the argument of perigee of the satellite.
     * 
     * @return Angle The argument of perigee of the satellite.
     */
    Angle get_argument_of_perigee() const { return _elements.get_argument_of_perigee(); }

    /**
     * @brief Get the true anomaly of the satellite.
     * 
     * @return Angle The true anomaly of the satellite.
     */
    Angle get_true_anomaly() const { return _elements.get_true_anomaly(); }

    /**
     * @brief Get the mean motion of the satellite.
     * 
     * @return MeanMotion The mean motion of the satellite.
     */
    MeanMotion get_mean_motion() const { return _meanMotion; }

    /**
     * @brief Get the revolution number of the satellite.
     * 
     * @return unsigned The revolution number of the satellite.
     */
    unsigned get_rev_number() const { return _revNumber; }

    /**
     * @brief Get the 2nd checksum of the satellite.
     * 
     * @return std::size_t The 2nd checksum of the satellite.
     */
    std::size_t get_check_sum2() const { return _checkSum2; }

  private:
    // Input data
    std::array<std::string, 2> _rawTLE; //!< The raw TLE data.

    // TLE-specific inputs
    std::string _name; //!< The name of the satellite.
    unsigned _catalogueNumber; //!< The catalogue number of the satellite.
    std::string _classification; //!< The classification of the satellite.
    std::string _launchYear; //!< The launch year of the satellite.
    std::string _launchNumber; //!< The launch number of the satellite.
    std::string _launchPiece; //!< The launch piece of the satellite.

    Date _epoch; //!< The epoch of the satellite.

    MeanMotion _meanMotion; //!< The mean motion of the satellite.
    MeanMotion1stDer _meanMotion1st; //!< The 1st derivative of the mean motion of the satellite.
    MeanMotion2ndDer _meanMotion2nd; //!< The 2nd derivative of the mean motion of the satellite.

    BallisticCoefficient _ballisticCoefficient; //!< The ballistic coefficient of the satellite.

    size_t _ephemerisType; //!< The ephemeris type of the satellite.
    size_t _elementSetNo; //!< The element set number of the satellite.
    size_t _checkSum1; //!< The 1st checksum of the satellite.
    unsigned _revNumber; //!< The revolution number of the satellite.
    size_t _checkSum2; //!< The 2nd checksum of the satellite.

    // Bundle elements into Keplerian set
    Keplerian _elements; //!< The Keplerian elements of the satellite.

    /**
     * @brief Implicit constructor implementation for TwoLineElements.
     * 
     * @param rawTle The raw TLE data.
     * @param sys The astrodynamics system.
     */
    void ctor_impl(const std::array<std::string, 2> rawTle, const AstrodynamicsSystem& sys);
};

} // namespace astro
} // namespace astrea
