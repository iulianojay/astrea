/**
 * @file Cylindrical.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Cylindrical class and its associated methods.
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
#include <mp-units/systems/si.h>

// units
#include <units/units.hpp>

// astro
#include <astro/astro.fwd.hpp>
#include <astro/state/CartesianVector.hpp>
#include <astro/state/frames/frames.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing a Cylindrical state vector in astrodynamics.
 *
 * This class encapsulates the position and velocity of a vehicle in Cylindrical coordinates.
 */
class Cylindrical {

    friend std::ostream& operator<<(std::ostream&, Cylindrical const&);

  public:
    /**
     * @brief Default constructor for Cylindrical.
     *
     * Initializes the Cylindrical state vector with zero values.
     */
    Cylindrical(Unitless scale = 0.0 * astrea::detail::unitless) :
        _range(scale * astrea::detail::distance_unit),
        _azimuth(scale * astrea::detail::angle_unit),
        _elevation(scale * astrea::detail::distance_unit)
    {
    }

    /**
     * @brief Constructor for Cylindrical with azimuth, elevation, and range.
     *
     * @param azimuth Cylindrical azimuth
     * @param elevation Elevation
     * @param range Range
     */
    Cylindrical(const Distance& range, const Angle& azimuth, const Distance& elevation) :
        _range(range),
        _azimuth(azimuth),
        _elevation(elevation)
    {
    }

    /**
     * @brief Constructor for Cylindrical with position and velocity vectors.
     *
     * @param r Radius vector in ECI (position)
     */
    Cylindrical(const RadiusVector<ECI>& r, const Date& date, const CelestialBody* parent);

    /**
     * @brief Constructor for Cylindrical with position and velocity vectors.
     *
     * @param r Radius vector in ECEF (position)
     */
    Cylindrical(const RadiusVector<ECEF>& r, const CelestialBody* parent);

    /**
     * @brief Constructor for Cylindrical from orbital elements.
     *
     * @param elements Orbital elements
     * @param sys Astrodynamics system containing celestial body data
     */
    template <IsOrbitalElements T>
    Cylindrical(const T& elements, const AstrodynamicsSystem& sys, const Date& date)
    {
        *this = Cylindrical(Cartesian(elements, sys).get_position().template in_frame<ECEF>(date), sys.get_center().get());
    }

    /**
     * @brief Copy constructor for Cylindrical.
     *
     * @param other Another Cylindrical object
     */
    Cylindrical(const Cylindrical&);

    /**
     * @brief Move constructor for Cylindrical.
     *
     * @param other Another Cylindrical object
     */
    Cylindrical(Cylindrical&&) noexcept;

    /**
     * @brief Move assignment operator for Cylindrical.
     *
     * @param other Another Cylindrical object
     * @return Cylindrical& Reference to the current object
     */
    Cylindrical& operator=(Cylindrical&&) noexcept;

    /**
     * @brief Copy assignment operator for Cylindrical.
     *
     * @param other Another Cylindrical object
     * @return Cylindrical& Reference to the current object
     */
    Cylindrical& operator=(const Cylindrical&);

    /**
     * @brief Default destructor for Cylindrical.
     */
    ~Cylindrical() = default;

    /**
     * @brief Compares two Cylindrical objects for equality.
     *
     * @param other Another Cylindrical object
     * @return true if the two Cylindrical objects are equal
     * @return false if the two Cylindrical objects are not equal
     */
    bool operator==(const Cylindrical& other) const;

    /**
     * @brief Compares two Cylindrical objects for inequality.
     *
     * @param other Another Cylindrical object
     * @return true if the two Cylindrical objects are not equal
     * @return false if the two Cylindrical objects are equal
     */
    bool operator!=(const Cylindrical& other) const;

    /**
     * @brief Adds two Cylindrical objects.
     *
     * @param other Another Cylindrical object
     * @return Resultant Cylindrical sum.
     */
    Cylindrical operator+(const Cylindrical& other) const;

    /**
     * @brief Adds another Cylindrical object to the current one.
     *
     * @param other Another Cylindrical object
     * @return Reference to the current Cylindrical object after addition.
     */
    Cylindrical& operator+=(const Cylindrical& other);

    /**
     * @brief Subtracts another Cylindrical object from the current one.
     *
     * @param other Another Cylindrical object
     * @return Resultant Cylindrical difference.
     */
    Cylindrical operator-(const Cylindrical& other) const;

    /**
     * @brief Subtracts another Cylindrical object from the current one.
     *
     * @param other Another Cylindrical object
     * @return Reference to the current Cylindrical object after subtraction.
     */
    Cylindrical& operator-=(const Cylindrical& other);

    /**
     * @brief Multiplies the Cylindrical state vector by a scalar.
     *
     * @param multiplier Scalar value to multiply with
     * @return Resultant Cylindrical after multiplication.
     */
    Cylindrical operator*(const Unitless& multiplier) const;

    /**
     * @brief Multiplies the Cylindrical state vector by a scalar.
     *
     * @param multiplier Scalar value to multiply with
     * @return Reference to the current Cylindrical object after multiplication.
     */
    Cylindrical& operator*=(const Unitless& multiplier);

    /**
     * @brief Divides the Cylindrical state vector by another Cylindrical object.
     *
     * @param other Another Cylindrical object
     * @return Resultant vector of unitless values after division.
     */
    std::vector<Unitless> operator/(const Cylindrical& other) const;

    /**
     * @brief Divides the Cylindrical state vector by a scalar.
     *
     * @param divisor Scalar value to divide with
     * @return Resultant Cylindrical after division.
     */
    Cylindrical operator/(const Unitless& divisor) const;

    /**
     * @brief Divides the Cylindrical state vector by a scalar.
     *
     * @param divisor Scalar value to divide with
     * @return Reference to the current Cylindrical object after division.
     */
    Cylindrical& operator/=(const Unitless& divisor);

    /**
     * @brief Converts the Cylindrical state vector to a RadiusVector<ECEF>.
     *
     * @return RadiusVector<ECEF> The position vector in Cylindrical coordinates.
     */
    RadiusVector<ECEF> get_position(const CelestialBody* parent) const;

    /**
     * @brief Converts the Cylindrical state vector to a RadiusVector<ECI>.
     *
     * @return RadiusVector<ECI> The position vector in Cylindrical coordinates.
     */
    RadiusVector<ECI> get_position(const Date& date, const CelestialBody* parent) const;

    /**
     * @brief Get the azimuth of the Cylindrical state vector.
     *
     * @return const Angle& Reference to the azimuth component of the Cylindrical state vector.
     */
    const Angle& get_azimuth() const { return _azimuth; }

    /**
     * @brief Get the elevation of the Cylindrical state vector.
     *
     * @return const Distance& Reference to the elevation component of the Cylindrical state vector.
     */
    const Distance& get_elevation() const { return _elevation; }

    /**
     * @brief Get the range of the Cylindrical state vector.
     *
     * @return const Distance& Reference to the range component of the Cylindrical state vector.
     */
    const Distance& get_range() const { return _range; }

    /**
     * @brief Interpolates between two Cylindrical states at a given time.
     *
     * @param thisTime Time of the current state
     * @param otherTime Time of the other state
     * @param other Other Cylindrical state to interpolate with
     * @param sys Astrodynamics system containing celestial body data
     * @param targetTime Target time for interpolation
     * @return Cylindrical Interpolated Cylindrical state at the target time.
     */
    Cylindrical interpolate(const Time& thisTime, const Time& otherTime, const Cylindrical& other, const Time& targetTime) const;

  private:
    Distance _range;     //!< Range
    Angle _azimuth;      //!< Azimuth
    Distance _elevation; //!< Elevation
};


/**
 * @brief Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates.
 *
 * @param rEcef The radius vector in ECEF coordinates.
 * @return The range, azimuth, and elevation as a tuple.
 */
std::tuple<Distance, Angle, Distance> convert_earth_fixed_to_cylindrical(const RadiusVector<EarthCenteredEarthFixed>& rEcef);


/**
 * @brief Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates.
 *
 * @param range The range in meters.
 * @param azimuth The azimuth in radians.
 * @param elevation The elevation in meters.
 * @return The radius vector in ECEF coordinates.
 */
RadiusVector<EarthCenteredEarthFixed>
    convert_cylindrical_to_earth_fixed(const Distance& range, const Angle& azimuth, const Distance& elevation);

} // namespace astro
} // namespace astrea
