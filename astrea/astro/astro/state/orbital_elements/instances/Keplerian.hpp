/**
 * @file Keplerian.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Keplerian class and its associated methods.
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <iosfwd>

#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief The Keplerian class represents the Keplerian orbital elements.
 *
 * The Keplerian elements are a set of six parameters that describe the orbit of a celestial body.
 * They include the semimajor axis, eccentricity, inclination, right ascension of the ascending node,
 * argument of perigee, and true anomaly.
 */
template <IsFrame auto _frame_>
class Keplerian {

    template <IsFrame auto frame>
    friend std::ostream& operator<<(std::ostream&, Keplerian<frame> const&);
    friend class OrbitalElements;

  public:
    static constexpr auto frame = _frame_; //!< The reference frame of the Keplerian elements.

    /**
     * @brief Constructs a Keplerian object with default values.
     *
     * @param scale A scaling factor to initialize the elements, typically used for unit conversion.
     */
    Keplerian(Unitless scale = 0.0 * astrea::detail::unitless) :
        _semimajor(scale * astrea::detail::distance_unit),
        _eccentricity(scale * astrea::detail::unitless),
        _inclination(scale * astrea::detail::angle_unit),
        _rightAscension(scale * astrea::detail::angle_unit),
        _argPerigee(scale * astrea::detail::angle_unit),
        _trueAnomaly(scale * astrea::detail::angle_unit)
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
    Keplerian(const Keplerian<frame>& elements, const GravParam& mu) :
        Keplerian(elements)
    {
    }

    /**
     * @brief Constructs a Keplerian object from Cartesian elements.
     *
     * @param elements The Cartesian elements to convert.
     * @param sys The astrodynamics system context for conversion.
     */
    Keplerian(const Cartesian<frame>& elements, const GravParam& mu);

    /**
     * @brief Constructs a Keplerian object from Equinoctial elements.
     *
     * @param elements The Equinoctial elements to convert.
     * @param sys The astrodynamics system context for conversion.
     */
    Keplerian(const Equinoctial<frame>& elements, const GravParam& mu);

    /**
     * @brief A static method to create Keplerian state vectors for a LEO orbit.
     *
     * This method return predefined Keplerian state vectors for various types of orbits.
     *
     * @param mu Gravitational parameter of the central body
     * @return Keplerian Predefined Keplerian state vector for a LEO orbit.
     */
    static Keplerian LEO();

    /**
     * @brief A static method to create Keplerian state vectors for a LMEO orbit.
     *
     * This method return predefined Keplerian state vectors for various types of orbits.
     *
     * @param mu Gravitational parameter of the central body
     * @return Keplerian Predefined Keplerian state vector for a LMEO orbit.
     */
    static Keplerian LMEO();

    /**
     * @brief A static method to create Keplerian state vectors for a GPS orbit.
     *
     * This method return predefined Keplerian state vectors for various types of orbits.
     *
     * @param mu Gravitational parameter of the central body
     * @return Keplerian Predefined Keplerian state vector for a GPS orbit.
     */
    static Keplerian GPS();

    /**
     * @brief A static method to create Keplerian state vectors for a HMEO orbit.
     *
     * This method return predefined Keplerian state vectors for various types of orbits.
     *
     * @param mu Gravitational parameter of the central body
     * @return Keplerian Predefined Keplerian state vector for a HMEO orbit.
     */
    static Keplerian HMEO();

    /**
     * @brief A static method to create Keplerian state vectors for a GEO orbit.
     *
     * This method return predefined Keplerian state vectors for various types of orbits.
     *
     * @param mu Gravitational parameter of the central body
     * @return Keplerian Predefined Keplerian state vector for a GEO orbit.
     */
    static Keplerian GEO();

    /**
     * @brief Copy constructor for Keplerian.
     *
     * @param other Another Keplerian object
     */
    Keplerian(const Keplerian<frame>&);

    /**
     * @brief Move constructor for Keplerian.
     *
     * @param other Another Keplerian object
     */
    Keplerian(Keplerian<frame>&&) noexcept;

    /**
     * @brief Move assignment operator for Keplerian.
     *
     * @param other Another Keplerian object
     * @return Keplerian& Reference to the current object
     */
    Keplerian& operator=(Keplerian<frame>&&) noexcept;

    /**
     * @brief Copy assignment operator for Keplerian.
     *
     * @param other Another Keplerian object
     * @return Keplerian& Reference to the current object
     */
    Keplerian& operator=(const Keplerian<frame>&);

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
    bool operator==(const Keplerian<frame>& other) const;

    /**
     * @brief Checks if two Keplerian objects are not equal.
     *
     * @param other Another Keplerian object
     * @return true if the two Keplerian objects are not equal, false otherwise.
     */
    bool operator!=(const Keplerian<frame>& other) const;

    /**
     * @brief Adds two Keplerian objects.
     *
     * @param other Another Keplerian object
     * @return Resultant Keplerian sum.
     */
    Keplerian operator+(const Keplerian<frame>& other) const;

    /**
     * @brief Adds another Keplerian object to the current one.
     *
     * @param other Another Keplerian object
     * @return Reference to the current Keplerian object after addition.
     */
    Keplerian& operator+=(const Keplerian<frame>& other);

    /**
     * @brief Subtracts another Keplerian object from the current one.
     *
     * @param other Another Keplerian object
     * @return Resultant Keplerian after subtraction.
     */
    Keplerian operator-(const Keplerian<frame>& other) const;

    /**
     * @brief Subtracts another Keplerian object from the current one.
     *
     * @param other Another Keplerian object
     * @return Reference to the current Keplerian object after subtraction.
     */
    Keplerian& operator-=(const Keplerian<frame>& other);

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
    KeplerianPartial<_frame_> operator/(const Time& time) const;

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
     * @brief Set the semimajor axis of the Keplerian state vector.
     */
    void set_semimajor(const Distance& semimajor) { _semimajor = semimajor; }

    /**
     * @brief Set the eccentricity of the Keplerian state vector.
     */
    void set_eccentricity(const Unitless& eccentricity) { _eccentricity = eccentricity; }

    /**
     * @brief Set the inclination of the Keplerian state vector.
     */
    void set_inclination(const Angle& inclination) { _inclination = inclination; }

    /**
     * @brief Set the right ascension of the ascending node of the Keplerian state vector.
     */
    void set_right_ascension(const Angle& rightAscension) { _rightAscension = rightAscension; }

    /**
     * @brief Get the argument of perigee of the Keplerian state vector.
     */
    void set_argument_of_perigee(const Angle& argPerigee) { _argPerigee = argPerigee; }

    /**
     * @brief Get the true anomaly of the Keplerian state vector.
     */
    void set_true_anomaly(const Angle& trueAnomaly) { _trueAnomaly = trueAnomaly; }

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
     * @brief Get the mean anomaly of the Keplerian state vector.
     *
     * @return Angle Mean anomaly of the Keplerian state vector.
     */
    Angle get_mean_anomaly() const;

    /**
     * @brief Get the mean motion of the Keplerian state vector.
     *
     * @param mu Gravitational parameter of the central body
     * @return MeanMotion Mean motion of the Keplerian state vector.
     */
    MeanMotion get_mean_motion(const GravParam& mu) const;

    /**
     * @brief Get the orbital period of the Keplerian state vector.
     *
     * @param mu Gravitational parameter of the central body
     * @return Time Orbital period of the Keplerian state vector.
     */
    Time get_orbital_period(const GravParam& mu) const;

    /**
     * @brief Interpolates between two Keplerian state vectors.
     *
     * This method performs linear interpolation between two Keplerian state vectors at a specified target time.
     *
     * @param thisTime The time of the first Keplerian state vector.
     * @param otherTime The time of the second Keplerian state vector.
     * @param other The second Keplerian state vector to interpolate with.
     * @param mu The gravitational parameter of the central body.
     * @param targetTime The target time for interpolation.
     * @return Keplerian Interpolated Keplerian state vector at the target time.
     */
    Keplerian interpolate(const Time& thisTime, const Time& otherTime, const Keplerian<frame>& other, const GravParam& mu, const Time& targetTime) const;

    /**
     * @brief Converts the Keplerian state vector to a vector of unitless values.
     *
     * @return std::vector<Unitless> Vector containing the semimajor axis, eccentricity, inclination, right ascension,
     * argument of perigee, and true anomaly components of the Keplerian state vector.
     */
    std::vector<Unitless> force_to_vector() const;

  private:
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
    void wrap_angles();

    /**
     * @brief Interpolates an angle between two time points.
     *
     * @param times The vector of time points.
     * @param ang The angle at the first time point.
     * @param other The angle at the second time point.
     * @return Angle The interpolated angle at the target time.
     */
    Angle interpolate_angle(const std::array<Time, 2>& times, const std::array<Angle, 2>& angles, const Time& targetTime) const;


    /**
     * @brief Creates a Keplerian object from a vector of unitless values.
     *
     * @param vec Vector containing the components of the Keplerian state vector.
     * @return Keplerian Constructed Keplerian object.
     */
    static Keplerian from_vector(const std::vector<Unitless>& vec);
};

/**
 * @brief Class representing a partial derivative of a Keplerian state vector.
 *
 * This class encapsulates the velocity and acceleration components of a vehicle in Keplerian coordinates.
 * It is used to represent the rate of change of the Keplerian elements with respect to time.
 *
 * @note The KeplerianPartial class is typically used in astrodynamics calculations involving orbital mechanics.
 */
template <IsFrame auto _frame_>
class KeplerianPartial {

    template <IsFrame auto frame>
    friend std::ostream& operator<<(std::ostream&, KeplerianPartial<frame> const&);

  public:
    static constexpr auto frame = _frame_; //!< The reference frame of the Keplerian partial derivatives.

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
        const AngularVelocity& inclinationPartial,
        const AngularVelocity& rightAscensionPartial,
        const AngularVelocity& argPerigeePartial,
        const AngularVelocity& trueAnomalyPartial
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
    Keplerian<_frame_> operator*(const Time& time) const;

    /**
     * @brief Converts the KeplerianPartial state vector to a vector of unitless values.
     *
     * @return std::vector<Unitless> Vector containing the components of the KeplerianPartial state vector.
     */
    std::vector<Unitless> force_to_vector() const;

  private:
    Velocity _semimajorPartial;             //!< Semimajor axis partial derivative
    UnitlessPerTime _eccentricityPartial;   //!< Eccentricity partial derivative
    AngularVelocity _inclinationPartial;    //!< Inclination partial derivative
    AngularVelocity _rightAscensionPartial; //!< Right ascension partial derivative
    AngularVelocity _argPerigeePartial;     //!< Argument of perigee partial derivative
    AngularVelocity _trueAnomalyPartial;    //!< True anomaly partial derivative
};

} // namespace astro
} // namespace astrea

#include <astro/state/orbital_elements/instances/Keplerian.ipp>