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
class Keplerian : public OrbitalElements<Keplerian<_frame_>, _frame_, Distance, Unitless, Angle, Angle, Angle, Angle> {

    template <IsFrame auto frame>
    friend std::ostream& operator<<(std::ostream&, Keplerian<frame> const&);
    friend class OrbitalElements;

  public:
    /**
     * @brief Default constructor for Keplerian.
     */
    Keplerian() = default;

    /**
     * @brief Constructs a Keplerian object from another Keplerian object.
     *
     * @param elements The Keplerian elements to copy.
     * @param sys The astrodynamics system context for conversion.
     */
    Keplerian(const Keplerian<_frame_>& other, const GravParam& mu) :
        _elements(other._elements)
    {
    }

    /**
     * @brief Constructs a Keplerian object from Cartesian elements.
     *
     * @param elements The Cartesian elements to convert.
     * @param sys The astrodynamics system context for conversion.
     */
    Keplerian(const Cartesian<_frame_>& elements, const GravParam& mu);

    /**
     * @brief Constructs a Keplerian object from Equinoctial elements.
     *
     * @param elements The Equinoctial elements to convert.
     * @param sys The astrodynamics system context for conversion.
     */
    Keplerian(const Equinoctial<_frame_>& elements, const GravParam& mu);

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
    Keplerian(const Keplerian<_frame_>&);

    /**
     * @brief Move constructor for Keplerian.
     *
     * @param other Another Keplerian object
     */
    Keplerian(Keplerian<_frame_>&&) noexcept;

    /**
     * @brief Move assignment operator for Keplerian.
     *
     * @param other Another Keplerian object
     * @return Keplerian& Reference to the current object
     */
    Keplerian& operator=(Keplerian<_frame_>&&) noexcept;

    /**
     * @brief Copy assignment operator for Keplerian.
     *
     * @param other Another Keplerian object
     * @return Keplerian& Reference to the current object
     */
    Keplerian& operator=(const Keplerian<_frame_>&);

    /**
     * @brief Destructor for Keplerian.
     *
     * Cleans up the Keplerian object.
     */
    ~Keplerian() = default;

    /**
     * @brief Set the semimajor axis of the Keplerian state vector.
     */
    void set_semimajor(const Distance& semimajor) { get_semimajor() = semimajor; }

    /**
     * @brief Set the eccentricity of the Keplerian state vector.
     */
    void set_eccentricity(const Unitless& eccentricity) { get_eccentricity() = eccentricity; }

    /**
     * @brief Set the inclination of the Keplerian state vector.
     */
    void set_inclination(const Angle& inclination) { get_inclination() = inclination; }

    /**
     * @brief Set the right ascension of the ascending node of the Keplerian state vector.
     */
    void set_right_ascension(const Angle& rightAscension) { get_right_ascension() = rightAscension; }

    /**
     * @brief Get the argument of perigee of the Keplerian state vector.
     */
    void set_argument_of_perigee(const Angle& argPerigee) { get_argument_of_perigee() = argPerigee; }

    /**
     * @brief Get the true anomaly of the Keplerian state vector.
     */
    void set_true_anomaly(const Angle& trueAnomaly) { get_true_anomaly() = trueAnomaly; }

    /**
     * @brief Get the semimajor axis of the Keplerian state vector.
     *
     * @return  Distance& Reference to the semimajor axis component of the Keplerian state vector.
     */
    Distance& get_semimajor() { return this->template get<0>(); }

    /**
     * @brief Get the eccentricity of the Keplerian state vector.
     *
     * @return  Unitless& Reference to the eccentricity component of the Keplerian state vector.
     */
    Unitless& get_eccentricity() { return this->template get<1>(); }

    /**
     * @brief Get the inclination of the Keplerian state vector.
     *
     * @return  Angle& Reference to the inclination component of the Keplerian state vector.
     */
    Angle& get_inclination() { return this->template get<2>(); }

    /**
     * @brief Get the right ascension of the ascending node of the Keplerian state vector.
     *
     * @return  Angle& Reference to the right ascension component of the Keplerian state vector.
     */
    Angle& get_right_ascension() { return this->template get<3>(); }

    /**
     * @brief Get the argument of perigee of the Keplerian state vector.
     *
     * @return  Angle& Reference to the argument of perigee component of the Keplerian state vector.
     */
    Angle& get_argument_of_perigee() { return this->template get<4>(); }

    /**
     * @brief Get the true anomaly of the Keplerian state vector.
     *
     * @return  Angle& Reference to the true anomaly component of the Keplerian state vector.
     */
    Angle& get_true_anomaly() { return this->template get<5>(); }

    /**
     * @brief Get the semimajor axis of the Keplerian state vector.
     *
     * @return const Distance& Reference to the semimajor axis component of the Keplerian state vector.
     */
    const Distance& get_semimajor() const { return this->template get<0>(); }

    /**
     * @brief Get the eccentricity of the Keplerian state vector.
     *
     * @return const Unitless& Reference to the eccentricity component of the Keplerian state vector.
     */
    const Unitless& get_eccentricity() const { return this->template get<1>(); }

    /**
     * @brief Get the inclination of the Keplerian state vector.
     *
     * @return const Angle& Reference to the inclination component of the Keplerian state vector.
     */
    const Angle& get_inclination() const { return this->template get<2>(); }

    /**
     * @brief Get the right ascension of the ascending node of the Keplerian state vector.
     *
     * @return const Angle& Reference to the right ascension component of the Keplerian state vector.
     */
    const Angle& get_right_ascension() const { return this->template get<3>(); }

    /**
     * @brief Get the argument of perigee of the Keplerian state vector.
     *
     * @return const Angle& Reference to the argument of perigee component of the Keplerian state vector.
     */
    const Angle& get_argument_of_perigee() const { return this->template get<4>(); }

    /**
     * @brief Get the true anomaly of the Keplerian state vector.
     *
     * @return const Angle& Reference to the true anomaly component of the Keplerian state vector.
     */
    const Angle& get_true_anomaly() const { return this->template get<5>(); }

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
    Keplerian interpolate(const Time& thisTime, const Time& otherTime, const Keplerian<_frame_>& other, const GravParam& mu, const Time& targetTime) const;

    /**
     * @brief Converts this Keplerian state to Keplerian elements expressed in a different frame.
     *
     * First converts to Cartesian in the native frame, applies the physical frame transformation,
     * then converts the result back to Keplerian elements.
     *
     * @tparam target_frame The target frame.
     * @param epoch The epoch at which to evaluate the frame transformation.
     * @param mu The gravitational parameter of the central body.
     * @return Keplerian<target_frame> This state expressed in the target frame.
     */
    template <IsFrame auto target_frame>
    Keplerian<target_frame> in_frame(const Date& epoch, const GravParam& mu) const;

  private:
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
class KeplerianPartial
    : public OrbitalElements<KeplerianPartial<_frame_>, _frame_, Velocity, UnitlessPerTime, AngularVelocity, AngularVelocity, AngularVelocity, AngularVelocity> {

    template <IsFrame auto frame>
    friend std::ostream& operator<<(std::ostream&, KeplerianPartial<frame> const&);

  public:
    /**
     * @brief Default constructor for KeplerianPartial.
     *
     * Initializes the KeplerianPartial with zero values.
     */
    KeplerianPartial() = default;
};

} // namespace astro
} // namespace astrea

#include <astro/state/orbital_elements/Keplerian.ipp>