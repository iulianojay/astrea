/**
 * @file Spherical.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Spherical class and its associated methods.
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
 * @brief Class representing a Spherical state vector in astrodynamics.
 *
 * This class encapsulates the position and velocity of a vehicle in Spherical coordinates.
 */
class Spherical {

    friend std::ostream& operator<<(std::ostream&, Spherical const&);

  public:
    /**
     * @brief Default constructor for Spherical.
     *
     * Initializes the Spherical state vector with zero values.
     */
    Spherical(Unitless scale = 0.0 * astrea::detail::unitless) :
        _range(scale * astrea::detail::distance_unit),
        _inclination(scale * astrea::detail::angle_unit),
        _azimuth(scale * astrea::detail::angle_unit)
    {
    }

    /**
     * @brief Constructor for Spherical with azimuth, inclination, and range.
     *
     * @param azimuth Spherical azimuth
     * @param inclination Inclination
     * @param range Range
     */
    Spherical(const Distance& range, const Angle& inclination, const Angle& azimuth) :
        _range(range),
        _inclination(inclination),
        _azimuth(azimuth)
    {
    }

    /**
     * @brief Constructor for Spherical with position and velocity vectors.
     *
     * @param r Radius vector in ECI (position)
     */
    Spherical(const RadiusVector<frames::earth::icrf>& r, const Date& date, const CelestialBody* parent);

    /**
     * @brief Constructor for Spherical with position and velocity vectors.
     *
     * @param r Radius vector in ECEF (position)
     */
    Spherical(const RadiusVector<frames::earth::earth_fixed>& r, const CelestialBody* parent);

    /**
     * @brief Constructor for Spherical from orbital elements.
     *
     * @param elements Orbital elements
     * @param sys Astrodynamics system containing celestial body data
     */
    template <IsOrbitalElements T>
    Spherical(const T& elements, const AstrodynamicsSystem& sys, const Date& date)
    {
        *this = Spherical(
            Cartesian(elements, sys).get_position().template in_frame<frames::earth::earth_fixed>(date),
            sys.get_central_body().get()
        );
    }

    /**
     * @brief Copy constructor for Spherical.
     *
     * @param other Another Spherical object
     */
    Spherical(const Spherical&);

    /**
     * @brief Move constructor for Spherical.
     *
     * @param other Another Spherical object
     */
    Spherical(Spherical&&) noexcept;

    /**
     * @brief Move assignment operator for Spherical.
     *
     * @param other Another Spherical object
     * @return Spherical& Reference to the current object
     */
    Spherical& operator=(Spherical&&) noexcept;

    /**
     * @brief Copy assignment operator for Spherical.
     *
     * @param other Another Spherical object
     * @return Spherical& Reference to the current object
     */
    Spherical& operator=(const Spherical&);

    /**
     * @brief Default destructor for Spherical.
     */
    ~Spherical() = default;

    /**
     * @brief Compares two Spherical objects for equality.
     *
     * @param other Another Spherical object
     * @return true if the two Spherical objects are equal
     * @return false if the two Spherical objects are not equal
     */
    bool operator==(const Spherical& other) const;

    /**
     * @brief Compares two Spherical objects for inequality.
     *
     * @param other Another Spherical object
     * @return true if the two Spherical objects are not equal
     * @return false if the two Spherical objects are equal
     */
    bool operator!=(const Spherical& other) const;

    /**
     * @brief Adds two Spherical objects.
     *
     * @param other Another Spherical object
     * @return Resultant Spherical sum.
     */
    Spherical operator+(const Spherical& other) const;

    /**
     * @brief Adds another Spherical object to the current one.
     *
     * @param other Another Spherical object
     * @return Reference to the current Spherical object after addition.
     */
    Spherical& operator+=(const Spherical& other);

    /**
     * @brief Subtracts another Spherical object from the current one.
     *
     * @param other Another Spherical object
     * @return Resultant Spherical difference.
     */
    Spherical operator-(const Spherical& other) const;

    /**
     * @brief Subtracts another Spherical object from the current one.
     *
     * @param other Another Spherical object
     * @return Reference to the current Spherical object after subtraction.
     */
    Spherical& operator-=(const Spherical& other);

    /**
     * @brief Multiplies the Spherical state vector by a scalar.
     *
     * @param multiplier Scalar value to multiply with
     * @return Resultant Spherical after multiplication.
     */
    Spherical operator*(const Unitless& multiplier) const;

    /**
     * @brief Multiplies the Spherical state vector by a scalar.
     *
     * @param multiplier Scalar value to multiply with
     * @return Reference to the current Spherical object after multiplication.
     */
    Spherical& operator*=(const Unitless& multiplier);

    /**
     * @brief Divides the Spherical state vector by another Spherical object.
     *
     * @param other Another Spherical object
     * @return Resultant vector of unitless values after division.
     */
    std::vector<Unitless> operator/(const Spherical& other) const;

    /**
     * @brief Divides the Spherical state vector by a scalar.
     *
     * @param divisor Scalar value to divide with
     * @return Resultant Spherical after division.
     */
    Spherical operator/(const Unitless& divisor) const;

    /**
     * @brief Divides the Spherical state vector by a scalar.
     *
     * @param divisor Scalar value to divide with
     * @return Reference to the current Spherical object after division.
     */
    Spherical& operator/=(const Unitless& divisor);

    /**
     * @brief Converts the Spherical state vector to a RadiusVector<frames::earth::earth_fixed>.
     *
     * @return RadiusVector<frames::earth::earth_fixed> The position vector in Spherical coordinates.
     */
    RadiusVector<frames::earth::earth_fixed> get_position(const CelestialBody* parent) const;

    /**
     * @brief Converts the Spherical state vector to a RadiusVector<frames::earth::icrf>.
     *
     * @return RadiusVector<frames::earth::icrf> The position vector in Spherical coordinates.
     */
    RadiusVector<frames::earth::icrf> get_position(const Date& date, const CelestialBody* parent) const;

    /**
     * @brief Get the azimuth of the Spherical state vector.
     *
     * @return const Angle& Reference to the azimuth component of the Spherical state vector.
     */
    const Angle& get_azimuth() const { return _azimuth; }

    /**
     * @brief Get the inclination of the Spherical state vector.
     *
     * @return const Angle& Reference to the inclination component of the Spherical state vector.
     */
    const Angle& get_inclination() const { return _inclination; }

    /**
     * @brief Get the range of the Spherical state vector.
     *
     * @return const Distance& Reference to the range component of the Spherical state vector.
     */
    const Distance& get_range() const { return _range; }

    /**
     * @brief Interpolates between two Spherical states at a given time.
     *
     * @param thisTime Time of the current state
     * @param otherTime Time of the other state
     * @param other Other Spherical state to interpolate with
     * @param sys Astrodynamics system containing celestial body data
     * @param targetTime Target time for interpolation
     * @return Spherical Interpolated Spherical state at the target time.
     */
    Spherical interpolate(const Time& thisTime, const Time& otherTime, const Spherical& other, const Time& targetTime) const;

  private:
    Distance _range;    //!< Range
    Angle _inclination; //!< Inclination
    Angle _azimuth;     //!< Azimuth
};


/**
 * @brief Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates.
 *
 * @param rEcef The radius vector in ECEF coordinates.
 * @return The range, inclination, and azimuth as a tuple.
 */
std::tuple<Distance, Angle, Angle> convert_earth_fixed_to_spherical(const RadiusVector<frames::earth::earth_fixed>& rEcef);


/**
 * @brief Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates.
 *
 * @param azimuth The azimuth in radians.
 * @param inclination The inclination in radians.
 * @param range The range in meters.
 * @return The radius vector in ECEF coordinates.
 */
RadiusVector<frames::earth::earth_fixed>
    convert_spherical_to_earth_fixed(const Distance& range, const Angle& inclination, const Angle& azimuth);

} // namespace astro
} // namespace astrea
