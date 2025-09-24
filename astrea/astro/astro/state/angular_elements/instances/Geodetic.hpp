/**
 * @file Geodetic.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Geodetic class and its associated methods.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <iosfwd>

// units
#include <units/units.hpp>

// astro
#include <astro/astro.fwd.hpp>
#include <astro/frames/CartesianVector.hpp>
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
            Cartesian(elements, sys).get_position().template in_frame<frames::earth::earth_fixed>(date),
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
std::tuple<Angle, Angle, Distance>
    convert_earth_fixed_to_geodetic(const RadiusVector<frames::earth::earth_fixed>& rEcef, const Distance& rEquitorial, const Distance& rPolar);


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
RadiusVector<frames::earth::earth_fixed>
    convert_geodetic_to_earth_fixed(const Angle& lat, const Angle& lon, const Distance& alt, const Distance& rEquitorial, const Distance& rPolar);

} // namespace astro
} // namespace astrea
