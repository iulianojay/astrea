/**
 * @file Keplerian.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Keplerian class and its associated methods.
 * @version 0.1
 * @date 2025-08-02
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
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

#include <astro/astro.fwd.hpp>
#include <astro/element_sets/ElementSet.hpp>
#include <astro/types/typedefs.hpp>
#include <units/units.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief The Keplerian class represents the Keplerian orbital elements.
 *
 * The Keplerian elements are a set of six parameters that describe the orbit of a celestial body.
 * They include the semimajor axis, eccentricity, inclination, right ascension of the ascending node,
 * argument of perigee, and true anomaly.
 */
class Keplerian {

    friend std::ostream& operator<<(std::ostream&, Keplerian const&);

  public:
    /**
     * @brief Constructs a Keplerian object with default values.
     *
     * @param scale A scaling factor to initialize the elements, typically used for unit conversion.
     */
    Keplerian(Unitless scale = 0.0 * detail::unitless) :
        _semimajor(scale * detail::distance_unit),
        _eccentricity(scale * detail::unitless),
        _inclination(scale * detail::angle_unit),
        _rightAscension(scale * detail::angle_unit),
        _argPerigee(scale * detail::angle_unit),
        _trueAnomaly(scale * detail::angle_unit)
    {
    }

    /**
     * @brief Constructs a Keplerian object with specified values.
     *
     * @param semimajor The semimajor axis of the orbit.
     * @param eccentricity The eccentricity of the orbit.
     * @param inclination The inclination of the orbit.
     * @param rightAscension The right ascension of the ascending node.
     * @param argPerigee The argument of perigee.
     * @param trueAnomaly The true anomaly of the orbit.
     */
    Keplerian(const Distance& semimajor, const Unitless& eccentricity, const Angle& inclination, const Angle& rightAscension, const Angle& argPerigee, const Angle& trueAnomaly) :
        _semimajor(semimajor),
        _eccentricity(eccentricity),
        _inclination(inclination),
        _rightAscension(rightAscension),
        _argPerigee(argPerigee),
        _trueAnomaly(trueAnomaly)
    {
    }

    /**
     * @brief Constructs a Keplerian object from another Keplerian object.
     *
     * @param elements The Keplerian elements to copy.
     * @param sys The astrodynamics system context for conversion.
     */
    Keplerian(const Keplerian& elements, const AstrodynamicsSystem& sys) :
        Keplerian(elements)
    {
    }

    /**
     * @brief Constructs a Keplerian object from Cartesian elements.
     *
     * @param elements The Cartesian elements to convert.
     * @param sys The astrodynamics system context for conversion.
     */
    Keplerian(const Cartesian& elements, const AstrodynamicsSystem& sys);

    /**
     * @brief Constructs a Keplerian object from Equinoctial elements.
     *
     * @param elements The Equinoctial elements to convert.
     * @param sys The astrodynamics system context for conversion.
     */
    Keplerian(const Equinoctial& elements, const AstrodynamicsSystem& sys);

    /**
     * @brief A static method to create Keplerian state vectors for a LEO orbit.
     *
     * This method return predefined Keplerian state vectors for various types of orbits.
     *
     * @param system Astrodynamics system containing celestial body data
     * @return Keplerian Predefined Keplerian state vector for a LEO orbit.
     */
    static Keplerian LEO();

    /**
     * @brief A static method to create Keplerian state vectors for a LMEO orbit.
     *
     * This method return predefined Keplerian state vectors for various types of orbits.
     *
     * @param system Astrodynamics system containing celestial body data
     * @return Keplerian Predefined Keplerian state vector for a LMEO orbit.
     */
    static Keplerian LMEO();

    /**
     * @brief A static method to create Keplerian state vectors for a GPS orbit.
     *
     * This method return predefined Keplerian state vectors for various types of orbits.
     *
     * @param system Astrodynamics system containing celestial body data
     * @return Keplerian Predefined Keplerian state vector for a GPS orbit.
     */
    static Keplerian GPS();

    /**
     * @brief A static method to create Keplerian state vectors for a HMEO orbit.
     *
     * This method return predefined Keplerian state vectors for various types of orbits.
     *
     * @param system Astrodynamics system containing celestial body data
     * @return Keplerian Predefined Keplerian state vector for a HMEO orbit.
     */
    static Keplerian HMEO();

    /**
     * @brief A static method to create Keplerian state vectors for a GEO orbit.
     *
     * This method return predefined Keplerian state vectors for various types of orbits.
     *
     * @param system Astrodynamics system containing celestial body data
     * @return Keplerian Predefined Keplerian state vector for a GEO orbit.
     */
    static Keplerian GEO();

    /**
     * @brief Copy constructor for Keplerian.
     *
     * @param other Another Keplerian object
     */
    Keplerian(const Keplerian&);

    /**
     * @brief Move constructor for Keplerian.
     *
     * @param other Another Keplerian object
     */
    Keplerian(Keplerian&&) noexcept;

    /**
     * @brief Move assignment operator for Keplerian.
     *
     * @param other Another Keplerian object
     * @return Keplerian& Reference to the current object
     */
    Keplerian& operator=(Keplerian&&) noexcept;

    /**
     * @brief Copy assignment operator for Keplerian.
     *
     * @param other Another Keplerian object
     * @return Keplerian& Reference to the current object
     */
    Keplerian& operator=(const Keplerian&);

    /**
     * @brief Destructor for Keplerian.
     *
     * Cleans up the Keplerian object.
     */
    ~Keplerian() = default;

    /**
     * @brief Checks if two Keplerian objects are equal.
     *
     * @param other Another Keplerian object
     * @return true if the two Keplerian objects are equal, false otherwise.
     */
    bool operator==(const Keplerian& other) const;

    /**
     * @brief Checks if two Keplerian objects are not equal.
     *
     * @param other Another Keplerian object
     * @return true if the two Keplerian objects are not equal, false otherwise.
     */
    bool operator!=(const Keplerian& other) const;

    /**
     * @brief Adds two Keplerian objects.
     *
     * @param other Another Keplerian object
     * @return Resultant Keplerian sum.
     */
    Keplerian operator+(const Keplerian& other) const;

    /**
     * @brief Adds another Keplerian object to the current one.
     *
     * @param other Another Keplerian object
     * @return Reference to the current Keplerian object after addition.
     */
    Keplerian& operator+=(const Keplerian& other);

    /**
     * @brief Subtracts another Keplerian object from the current one.
     *
     * @param other Another Keplerian object
     * @return Resultant Keplerian after subtraction.
     */
    Keplerian operator-(const Keplerian& other) const;

    /**
     * @brief Subtracts another Keplerian object from the current one.
     *
     * @param other Another Keplerian object
     * @return Reference to the current Keplerian object after subtraction.
     */
    Keplerian& operator-=(const Keplerian& other);

    /**
     * @brief Multiplies the Keplerian state vector by a scalar.
     *
     * @param multiplier Scalar value to multiply with
     * @return Resultant Keplerian after multiplication.
     */
    Keplerian operator*(const Unitless& multiplier) const;

    /**
     * @brief Multiplies the Keplerian state vector by a scalar.
     *
     * @param multiplier Scalar value to multiply with
     * @return Reference to the current Keplerian object after multiplication.
     */
    Keplerian& operator*=(const Unitless& multiplier);

    /**
     * @brief Divides the Keplerian state vector by a time.
     *
     * @param time Time value to divide by
     * @return Resultant KeplerianPartial after division.
     */
    KeplerianPartial operator/(const Time& time) const;

    /**
     * @brief Divides the Keplerian state vector by another Keplerian object.
     *
     * @param other Another Keplerian object
     * @return Resultant vector of unitless values after division.
     */
    Keplerian operator/(const Unitless& divisor) const;

    /**
     * @brief Divides the Keplerian state vector by a scalar.
     *
     * @param divisor Scalar value to divide with
     * @return Reference to the current Keplerian object after division.
     */
    Keplerian& operator/=(const Unitless& divisor);

    /**
     * @brief Get the semimajor axis of the Keplerian state vector.
     *
     * @return const Distance& Reference to the semimajor axis component of the Keplerian state vector.
     */
    const Distance& get_semimajor() const { return _semimajor; }

    /**
     * @brief Get the eccentricity of the Keplerian state vector.
     *
     * @return const Unitless& Reference to the eccentricity component of the Keplerian state vector.
     */
    const Unitless& get_eccentricity() const { return _eccentricity; }

    /**
     * @brief Get the inclination of the Keplerian state vector.
     *
     * @return const Angle& Reference to the inclination component of the Keplerian state vector.
     */
    const Angle& get_inclination() const { return _inclination; }

    /**
     * @brief Get the right ascension of the ascending node of the Keplerian state vector.
     *
     * @return const Angle& Reference to the right ascension component of the Keplerian state vector.
     */
    const Angle& get_right_ascension() const { return _rightAscension; }

    /**
     * @brief Get the argument of perigee of the Keplerian state vector.
     *
     * @return const Angle& Reference to the argument of perigee component of the Keplerian state vector.
     */
    const Angle& get_argument_of_perigee() const { return _argPerigee; }

    /**
     * @brief Get the true anomaly of the Keplerian state vector.
     *
     * @return const Angle& Reference to the true anomaly component of the Keplerian state vector.
     */
    const Angle& get_true_anomaly() const { return _trueAnomaly; }

    /**
     * @brief Returns the size of the Keplerian state vector.
     *
     * @return std::size_t The size of the Keplerian state vector, which is always 6.
     */
    std::size_t size() const { return 6; }

    /**
     * @brief Converts the Keplerian state vector to a vector of unitless values.
     *
     * @return std::vector<Unitless> Vector containing the semimajor axis, eccentricity, inclination, right ascension,
     * argument of perigee, and true anomaly components of the Keplerian state vector.
     */
    constexpr EnumType get_set_id() const { return _setId; }

    /**
     * @brief Interpolates between two Keplerian state vectors.
     *
     * This method performs linear interpolation between two Keplerian state vectors at a specified target time.
     *
     * @param thisTime The time of the first Keplerian state vector.
     * @param otherTime The time of the second Keplerian state vector.
     * @param other The second Keplerian state vector to interpolate with.
     * @param sys The astrodynamics system context for conversion.
     * @param targetTime The target time for interpolation.
     * @return Keplerian Interpolated Keplerian state vector at the target time.
     */
    Keplerian interpolate(const Time& thisTime, const Time& otherTime, const Keplerian& other, const AstrodynamicsSystem& sys, const Time& targetTime) const;

    /**
     * @brief Converts the Keplerian state vector to a vector of unitless values.
     *
     * @return std::vector<Unitless> Vector containing the semimajor axis, eccentricity, inclination, right ascension,
     * argument of perigee, and true anomaly components of the Keplerian state vector.
     */
    std::vector<Unitless> to_vector() const;

  private:
    constexpr static EnumType _setId = std::to_underlying(ElementSet::KEPLERIAN); //!< Set ID for the Keplerian element set

    Distance _semimajor;    //!< Semimajor axis of the orbit
    Unitless _eccentricity; //!< Eccentricity of the orbit
    Angle _inclination;     //!< Inclination of the orbit
    Angle _rightAscension;  //!< Right ascension of the ascending node
    Angle _argPerigee;      //!< Argument of perigee of the orbit
    Angle _trueAnomaly;     //!< True anomaly of the orbit

    /**
     * @brief Sanitize the angles of the Keplerian state vector.
     *
     * This method ensures that all angles are within their valid ranges.
     */
    void sanitize_angles();

    /**
     * @brief Interpolates an angle between two time points.
     *
     * @param times The vector of time points.
     * @param ang The angle at the first time point.
     * @param other The angle at the second time point.
     * @return Angle The interpolated angle at the target time.
     */
    Angle interpolate_angle(const std::vector<Time>& times, const std::vector<Angle>& angles, const Time& targetTime) const;
};

/**
 * @brief Class representing a partial derivative of a Keplerian state vector.
 *
 * This class encapsulates the velocity and acceleration components of a vehicle in Keplerian coordinates.
 * It is used to represent the rate of change of the Keplerian elements with respect to time.
 *
 * @note The KeplerianPartial class is typically used in astrodynamics calculations involving orbital mechanics.
 */
class KeplerianPartial {

    friend std::ostream& operator<<(std::ostream&, KeplerianPartial const&);

  public:
    /**
     * @brief Default constructor for KeplerianPartial.
     *
     * Initializes the KeplerianPartial with zero values.
     */
    KeplerianPartial() = default;

    /**
     * @brief Constructor for KeplerianPartial with velocity and acceleration components.
     *
     * @param semimajorPartial Semimajor axis partial derivative
     * @param eccentricityPartial Eccentricity partial derivative
     * @param inclinationPartial Inclination partial derivative
     * @param rightAscensionPartial Right ascension partial derivative
     * @param argPerigeePartial Argument of perigee partial derivative
     * @param trueAnomalyPartial True anomaly partial derivative
     */
    KeplerianPartial(
        const Velocity& semimajorPartial,
        const UnitlessPerTime& eccentricityPartial,
        const AngularRate& inclinationPartial,
        const AngularRate& rightAscensionPartial,
        const AngularRate& argPerigeePartial,
        const AngularRate& trueAnomalyPartial
    ) :
        _semimajorPartial(semimajorPartial),
        _eccentricityPartial(eccentricityPartial),
        _inclinationPartial(inclinationPartial),
        _rightAscensionPartial(rightAscensionPartial),
        _argPerigeePartial(argPerigeePartial),
        _trueAnomalyPartial(trueAnomalyPartial)
    {
    }

    /**
     * @brief Multiplication operator for KeplerianPartial.
     *
     * This method multiplies the KeplerianPartial by a time value to obtain a Keplerian state vector.
     *
     * @param time Time to multiply the KeplerianPartial by
     * @return Keplerian Resulting Keplerian state vector after multiplication.
     */
    Keplerian operator*(const Time& time) const;

  private:
    Velocity _semimajorPartial;           //!< Semimajor axis partial derivative
    UnitlessPerTime _eccentricityPartial; //!< Eccentricity partial derivative
    AngularRate _inclinationPartial;      //!< Inclination partial derivative
    AngularRate _rightAscensionPartial;   //!< Right ascension partial derivative
    AngularRate _argPerigeePartial;       //!< Argument of perigee partial derivative
    AngularRate _trueAnomalyPartial;      //!< True anomaly partial derivative
};

} // namespace astro
} // namespace waveguide