/**
 * @file Geodetic.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Geodetic class and its associated methods.
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
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing a Geodetic state vector in astrodynamics.
 *
 * This class encapsulates the position and velocity of a vehicle in Geodetic coordinates.
 */
class Geodetic {

    friend std::ostream& operator<<(std::ostream&, Geodetic const&);

  public:
    /**
     * @brief Default constructor for Geodetic.
     *
     * Initializes the Geodetic state vector with zero values.
     */
    Geodetic(Unitless scale = 0.0 * astrea::detail::unitless) :
        _latitude(scale * astrea::detail::angle_unit),
        _longitude(scale * astrea::detail::angle_unit),
        _altitude(scale * astrea::detail::distance_unit)
    {
    }

    /**
     * @brief Constructor for Geodetic with latitude, longitude, and altitude.
     *
     * @param latitude Geodetic latitude
     * @param longitude Longitude
     * @param altitude Altitude
     */
    Geodetic(const Angle& latitude, const Angle& longitude, const Distance& altitude) :
        _latitude(latitude),
        _longitude(longitude),
        _altitude(altitude)
    {
    }

    /**
     * @brief Constructor for Geodetic with position and velocity vectors.
     *
     * @param r Radius vector in ECI (position)
     */
    Geodetic(const RadiusVector<frames::earth::icrf>& r, const Date& date, const CelestialBody* parent);

    /**
     * @brief Constructor for Geodetic with position and velocity vectors.
     *
     * @param r Radius vector in ECEF (position)
     */
    Geodetic(const RadiusVector<frames::earth::earth_fixed>& r, const CelestialBody* parent);

    /**
     * @brief Constructor for Geodetic from orbital elements.
     *
     * @param elements Orbital elements
     * @param sys Astrodynamics system containing celestial body data
     */
    template <IsOrbitalElements T>
    Geodetic(const T& elements, const AstrodynamicsSystem& sys, const Date& date)
    {
        *this = Geodetic(
            Cartesian(elements, sys.get_mu()).get_position().template in_frame<frames::earth::earth_fixed>(date),
            sys.get_central_body().get()
        );
    }

    /**
     * @brief Copy constructor for Geodetic.
     *
     * @param other Another Geodetic object
     */
    Geodetic(const Geodetic&);

    /**
     * @brief Move constructor for Geodetic.
     *
     * @param other Another Geodetic object
     */
    Geodetic(Geodetic&&) noexcept;

    /**
     * @brief Move assignment operator for Geodetic.
     *
     * @param other Another Geodetic object
     * @return Geodetic& Reference to the current object
     */
    Geodetic& operator=(Geodetic&&) noexcept;

    /**
     * @brief Copy assignment operator for Geodetic.
     *
     * @param other Another Geodetic object
     * @return Geodetic& Reference to the current object
     */
    Geodetic& operator=(const Geodetic&);

    /**
     * @brief Default destructor for Geodetic.
     */
    ~Geodetic() = default;

    /**
     * @brief Compares two Geodetic objects for equality.
     *
     * @param other Another Geodetic object
     * @return true if the two Geodetic objects are equal
     * @return false if the two Geodetic objects are not equal
     */
    bool operator==(const Geodetic& other) const;

    /**
     * @brief Compares two Geodetic objects for inequality.
     *
     * @param other Another Geodetic object
     * @return true if the two Geodetic objects are not equal
     * @return false if the two Geodetic objects are equal
     */
    bool operator!=(const Geodetic& other) const;

    /**
     * @brief Adds two Geodetic objects.
     *
     * @param other Another Geodetic object
     * @return Resultant Geodetic sum.
     */
    Geodetic operator+(const Geodetic& other) const;

    /**
     * @brief Adds another Geodetic object to the current one.
     *
     * @param other Another Geodetic object
     * @return Reference to the current Geodetic object after addition.
     */
    Geodetic& operator+=(const Geodetic& other);

    /**
     * @brief Subtracts another Geodetic object from the current one.
     *
     * @param other Another Geodetic object
     * @return Resultant Geodetic difference.
     */
    Geodetic operator-(const Geodetic& other) const;

    /**
     * @brief Subtracts another Geodetic object from the current one.
     *
     * @param other Another Geodetic object
     * @return Reference to the current Geodetic object after subtraction.
     */
    Geodetic& operator-=(const Geodetic& other);

    /**
     * @brief Multiplies the Geodetic state vector by a scalar.
     *
     * @param multiplier Scalar value to multiply with
     * @return Resultant Geodetic after multiplication.
     */
    Geodetic operator*(const Unitless& multiplier) const;

    /**
     * @brief Multiplies the Geodetic state vector by a scalar.
     *
     * @param multiplier Scalar value to multiply with
     * @return Reference to the current Geodetic object after multiplication.
     */
    Geodetic& operator*=(const Unitless& multiplier);

    /**
     * @brief Divides the Geodetic state vector by another Geodetic object.
     *
     * @param other Another Geodetic object
     * @return Resultant vector of unitless values after division.
     */
    std::vector<Unitless> operator/(const Geodetic& other) const;

    /**
     * @brief Divides the Geodetic state vector by a scalar.
     *
     * @param divisor Scalar value to divide with
     * @return Resultant Geodetic after division.
     */
    Geodetic operator/(const Unitless& divisor) const;

    /**
     * @brief Divides the Geodetic state vector by a scalar.
     *
     * @param divisor Scalar value to divide with
     * @return Reference to the current Geodetic object after division.
     */
    Geodetic& operator/=(const Unitless& divisor);

    /**
     * @brief Converts the Geodetic state vector to a RadiusVector<frames::earth::earth_fixed>.
     *
     * @return RadiusVector<frames::earth::earth_fixed> The position vector in Geodetic coordinates.
     */
    RadiusVector<frames::earth::earth_fixed> get_position(const CelestialBody* parent) const;

    /**
     * @brief Converts the Geodetic state vector to a RadiusVector<frames::earth::icrf>.
     *
     * @return RadiusVector<frames::earth::icrf> The position vector in Geodetic coordinates.
     */
    RadiusVector<frames::earth::icrf> get_position(const Date& date, const CelestialBody* parent) const;

    /**
     * @brief Get the latitude of the Geodetic state vector.
     *
     * @return const Angle& Reference to the latitude component of the Geodetic state vector.
     */
    const Angle& get_latitude() const { return _latitude; }

    /**
     * @brief Get the longitude of the Geodetic state vector.
     *
     * @return const Angle& Reference to the longitude component of the Geodetic state vector.
     */
    const Angle& get_longitude() const { return _longitude; }

    /**
     * @brief Get the altitude of the Geodetic state vector.
     *
     * @return const Distance& Reference to the altitude component of the Geodetic state vector.
     */
    const Distance& get_altitude() const { return _altitude; }

    /**
     * @brief Interpolates between two Geodetic states at a given time.
     *
     * @param thisTime Time of the current state
     * @param otherTime Time of the other state
     * @param other Other Geodetic state to interpolate with
     * @param sys Astrodynamics system containing celestial body data
     * @param targetTime Target time for interpolation
     * @return Geodetic Interpolated Geodetic state at the target time.
     */
    Geodetic interpolate(const Time& thisTime, const Time& otherTime, const Geodetic& other, const Time& targetTime) const;

  private:
    Angle _latitude;    //!< Geodetic Latitude
    Angle _longitude;   //!< Longitude
    Distance _altitude; //!< Altitude
};


/**
 * @brief Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates.
 *
 * @param rEcef The radius vector in ECEF coordinates.
 * @param rEquitorial The equatorial radius of the Earth.
 * @param rPolar The polar radius of the Earth.
 * @return The latitude, longitude, and altitude as a tuple.
 */
template <typename Frame_T>
    requires(IsFixedRotatingFrame<Frame_T>)
std::tuple<Angle, Angle, Distance>
    convert_body_fixed_to_geodetic(const RadiusVector<Frame_T>& rBodyFixed, const Distance& rEquitorial, const Distance& rPolar)
{
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::mm;

    static const unsigned MAX_ITER  = 1e4;
    static const Distance MAX_ERROR = 1.0 * mm;

    const Distance& xEcef = rBodyFixed[0];
    const Distance& yEcef = rBodyFixed[1];
    const Distance& zEcef = rBodyFixed[2];

    const Unitless f   = (rEquitorial - rPolar) / rEquitorial;
    const Unitless eSq = (2.0 - f) * f;

    const auto xSqYSq = xEcef * xEcef + yEcef * yEcef;

    Distance dz  = eSq * zEcef;
    Distance err = 1.0 * km;
    Distance N   = 0.0 * km;
    unsigned ii  = 0;
    while (err > MAX_ERROR && ii < MAX_ITER) {
        const Unitless s = (zEcef + dz) / sqrt(xSqYSq + (zEcef + dz) * (zEcef + dz));
        N                = rEquitorial / sqrt(1 - eSq * s * s);
        err              = abs(dz - N * eSq * s);
        dz               = N * eSq * s;
        ++ii;
    }

    if (ii >= MAX_ITER - 1) { throw std::runtime_error("Conversion from ECEF to LLA failed to converge."); }

    const Angle longitude = atan2(yEcef, xEcef);
    const Angle latitude  = atan2(zEcef + dz, sqrt(xSqYSq));
    Distance altitude     = sqrt(xSqYSq + (zEcef + dz) * (zEcef + dz)) - N;
    if (altitude < 0.0 * km) { altitude = 0.0 * km; }

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
template <typename Frame_T>
    requires(IsFixedRotatingFrame<Frame_T>)
RadiusVector<Frame_T>
    convert_geodetic_to_body_fixed(const Angle& lat, const Angle& lon, const Distance& alt, const Distance& rEquitorial, const Distance& rPolar)
{
    const Unitless sinLat = sin(lat);
    const Unitless cosLat = cos(lat);

    const Unitless f   = (rEquitorial - rPolar) / rEquitorial;
    const Unitless eSq = (2.0 - f) * f;
    const Distance N   = rEquitorial / sqrt(1.0 - eSq * sinLat * sinLat);

    // Ecef coordinates
    return { (N + alt) * cosLat * cos(lon), (N + alt) * cosLat * sin(lon), ((1.0 - eSq) * N + alt) * sinLat };
}

} // namespace astro
} // namespace astrea
