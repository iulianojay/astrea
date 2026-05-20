/**
 * @file Geocentric.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Geocentric class and its associated methods.
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

// units
#include <units/units.hpp>

// astro
#include <astro/astro.fwd.hpp>
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frame_concepts.hpp>
#include <astro/frames/frames.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/system_concepts.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing a Geocentric state vector in astrodynamics.
 *
 * This class encapsulates the position and velocity of a vehicle in Geocentric coordinates.
 *
 * @tparam _body_ The celestial body NTTP that defines the reference ellipsoid and frames.
 */
template <IsCelestialBody auto _body_>
class Geocentric {

    template <IsCelestialBody auto body>
    friend std::ostream& operator<<(std::ostream&, Geocentric<body> const&);

  public:
    static constexpr auto body          = _body_; //!< The celestial body of this Geocentric state.
    static constexpr auto _icrf_frame_  = get_body_icrf_frame<_body_>();  //!< Inertial frame for the body.
    static constexpr auto _fixed_frame_ = get_body_fixed_frame<_body_>(); //!< Body-fixed rotating frame.

    /**
     * @brief Default constructor for Geocentric.
     *
     * Initializes the Geocentric state vector with zero values.
     */
    Geocentric(Unitless scale = 0.0 * astrea::detail::unitless) :
        _latitude(scale * astrea::detail::angle_unit),
        _longitude(scale * astrea::detail::angle_unit),
        _altitude(scale * astrea::detail::distance_unit)
    {
    }

    /**
     * @brief Constructor for Geocentric with latitude, longitude, and altitude.
     *
     * @param latitude Geocentric latitude
     * @param longitude Longitude
     * @param altitude Altitude
     */
    Geocentric(const Angle& latitude, const Angle& longitude, const Distance& altitude) :
        _latitude(latitude),
        _longitude(longitude),
        _altitude(altitude)
    {
    }

    /**
     * @brief Constructor for Geocentric from an inertial radius vector.
     *
     * @param r Radius vector in the body's inertial frame (position)
     * @param date Date for the frame transformation
     */
    Geocentric(const RadiusVector<_icrf_frame_>& r, const Date& date);

    /**
     * @brief Constructor for Geocentric from a body-fixed radius vector.
     *
     * @param r Radius vector in the body-fixed frame (position)
     */
    Geocentric(const RadiusVector<_fixed_frame_>& r);

    /**
     * @brief Constructor for Geocentric from orbital elements.
     *
     * @param elements Orbital elements
     * @param date Date for the frame transformation
     */
    template <IsOrbitalElements T>
    Geocentric(const T& elements, const Date& date)
    {
        *this = Geocentric<_body_>(Cartesian<_icrf_frame_>(elements).get_position().template in_frame<_fixed_frame_>(date));
    }

    /**
     * @brief Copy constructor for Geocentric.
     *
     * @param other Another Geocentric object
     */
    Geocentric(const Geocentric<_body_>&);

    /**
     * @brief Move constructor for Geocentric.
     *
     * @param other Another Geocentric object
     */
    Geocentric(Geocentric<_body_>&&) noexcept;

    /**
     * @brief Move assignment operator for Geocentric.
     *
     * @param other Another Geocentric object
     * @return Geocentric& Reference to the current object
     */
    Geocentric<_body_>& operator=(Geocentric<_body_>&&) noexcept;

    /**
     * @brief Copy assignment operator for Geocentric.
     *
     * @param other Another Geocentric object
     * @return Geocentric& Reference to the current object
     */
    Geocentric<_body_>& operator=(const Geocentric<_body_>&);

    /**
     * @brief Default destructor for Geocentric.
     */
    ~Geocentric() = default;

    /**
     * @brief Compares two Geocentric objects for equality.
     *
     * @param other Another Geocentric object
     * @return true if the two Geocentric objects are equal
     * @return false if the two Geocentric objects are not equal
     */
    bool operator==(const Geocentric<_body_>& other) const;

    /**
     * @brief Compares two Geocentric objects for inequality.
     *
     * @param other Another Geocentric object
     * @return true if the two Geocentric objects are not equal
     * @return false if the two Geocentric objects are equal
     */
    bool operator!=(const Geocentric<_body_>& other) const;

    /**
     * @brief Adds two Geocentric objects.
     *
     * @param other Another Geocentric object
     * @return Resultant Geocentric sum.
     */
    Geocentric<_body_> operator+(const Geocentric<_body_>& other) const;

    /**
     * @brief Adds another Geocentric object to the current one.
     *
     * @param other Another Geocentric object
     * @return Reference to the current Geocentric object after addition.
     */
    Geocentric<_body_>& operator+=(const Geocentric<_body_>& other);

    /**
     * @brief Subtracts another Geocentric object from the current one.
     *
     * @param other Another Geocentric object
     * @return Resultant Geocentric difference.
     */
    Geocentric<_body_> operator-(const Geocentric<_body_>& other) const;

    /**
     * @brief Subtracts another Geocentric object from the current one.
     *
     * @param other Another Geocentric object
     * @return Reference to the current Geocentric object after subtraction.
     */
    Geocentric<_body_>& operator-=(const Geocentric<_body_>& other);

    /**
     * @brief Multiplies the Geocentric state vector by a scalar.
     *
     * @param multiplier Scalar value to multiply with
     * @return Resultant Geocentric after multiplication.
     */
    Geocentric<_body_> operator*(const Unitless& multiplier) const;

    /**
     * @brief Multiplies the Geocentric state vector by a scalar.
     *
     * @param multiplier Scalar value to multiply with
     * @return Reference to the current Geocentric object after multiplication.
     */
    Geocentric<_body_>& operator*=(const Unitless& multiplier);

    /**
     * @brief Divides the Geocentric state vector by another Geocentric object.
     *
     * @param other Another Geocentric object
     * @return Resultant vector of unitless values after division.
     */
    std::vector<Unitless> operator/(const Geocentric<_body_>& other) const;

    /**
     * @brief Divides the Geocentric state vector by a scalar.
     *
     * @param divisor Scalar value to divide with
     * @return Resultant Geocentric after division.
     */
    Geocentric<_body_> operator/(const Unitless& divisor) const;

    /**
     * @brief Divides the Geocentric state vector by a scalar.
     *
     * @param divisor Scalar value to divide with
     * @return Reference to the current Geocentric object after division.
     */
    Geocentric<_body_>& operator/=(const Unitless& divisor);

    /**
     * @brief Converts the Geocentric state vector to a body-fixed radius vector.
     *
     * @return RadiusVector in the body-fixed frame.
     */
    RadiusVector<_fixed_frame_> get_position() const;

    /**
     * @brief Converts the Geocentric state vector to an inertial radius vector.
     *
     * @param date Date for the frame transformation
     * @return RadiusVector in the body's inertial frame.
     */
    RadiusVector<_icrf_frame_> get_position(const Date& date) const;

    /**
     * @brief Get the latitude of the Geocentric state vector.
     *
     * @return const Angle& Reference to the latitude component of the Geocentric state vector.
     */
    const Angle& get_latitude() const { return _latitude; }

    /**
     * @brief Get the longitude of the Geocentric state vector.
     *
     * @return const Angle& Reference to the longitude component of the Geocentric state vector.
     */
    const Angle& get_longitude() const { return _longitude; }

    /**
     * @brief Get the altitude of the Geocentric state vector.
     *
     * @return const Distance& Reference to the altitude component of the Geocentric state vector.
     */
    const Distance& get_altitude() const { return _altitude; }

    /**
     * @brief Interpolates between two Geocentric states at a given time.
     *
     * @param thisTime Time of the current state
     * @param otherTime Time of the other state
     * @param other Other Geocentric state to interpolate with
     * @param targetTime Target time for interpolation
     * @return Geocentric Interpolated Geocentric state at the target time.
     */
    Geocentric<_body_>
        interpolate(const Time& thisTime, const Time& otherTime, const Geocentric<_body_>& other, const Time& targetTime) const;

  private:
    Angle _latitude;    //!< Geocentric Latitude
    Angle _longitude;   //!< Longitude
    Distance _altitude; //!< Altitude
};

/**
 * @brief Calculate the geocentric radius given latitude and Earth's radii.
 *
 * @param lat The latitude in radians.
 * @param rEquitorial The equatorial radius of the Earth.
 * @param rPolar The polar radius of the Earth.
 * @return The geocentric radius.
 */
Distance calculate_geocentric_radius(const Angle& lat, const Distance& rEquitorial, const Distance& rPolar);

/**
 * @brief Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates.
 *
 * @param rEcef The radius vector in ECEF coordinates.
 * @param rEquitorial The equatorial radius of the Earth.
 * @param rPolar The polar radius of the Earth.
 * @return The latitude, longitude, and altitude as a tuple.
 */
template <IsFrame auto _frame_>
    requires(IsFixedRotatingFrame<_frame_>)
std::tuple<Angle, Angle, Distance>
    convert_body_fixed_to_geocentric(const RadiusVector<_frame_>& rEcef, const Distance& rEquitorial, const Distance& rPolar)
{
    const Distance& x = rEcef[0];
    const Distance& y = rEcef[1];
    const Distance& z = rEcef[2];
    const Distance R  = rEcef.norm();

    const Distance rho = sqrt(x * x + y * y);

    const Angle longitude = atan2(y, x);
    const Angle latitude  = atan2(z, rho);

    const Distance rGeocentric = calculate_geocentric_radius(latitude, rEquitorial, rPolar);
    const Distance altitude    = R - rGeocentric;

    return { latitude, longitude, altitude };
}


/**
 * @brief Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates.
 *
 * @param lat The latitude in radians.
 * @param lon The longitude in radians.
 * @param alt The altitude in meters.
 * @param rEquitorial The equatorial radius of the Earth.
 * @param rPolar The polar radius of the Earth.
 * @return The radius vector in ECEF coordinates.
 */
template <IsFrame auto _frame_>
    requires(IsFixedRotatingFrame<_frame_>)
RadiusVector<_frame_>
    convert_geocentric_to_body_fixed(const Angle& lat, const Angle& lon, const Distance& alt, const Distance& rEquitorial, const Distance& rPolar)
{
    const Distance rGeocentric = calculate_geocentric_radius(lat, rEquitorial, rPolar);
    const Distance R           = rGeocentric + alt;

    // Ecef coordinates
    return { R * cos(lat) * cos(lon), R * cos(lat) * sin(lon), R * sin(lat) };
}

} // namespace astro
} // namespace astrea

#include <astro/state/angular_elements/instances/Geocentric.ipp>
