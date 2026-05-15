/**
 * @file GroundPoint.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the GroundPoint class.
 * @date 2025-08-03
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

#include <string>

#include <astro/astro.fwd.hpp>
#include <astro/state/angular_elements/angular_elements.hpp>
#include <units/units.hpp>

#include <trace/platforms/AccessObject.hpp>
#include <trace/types/typedefs.hpp>


namespace astrea {
namespace trace {

/**
 * @brief Represents a point on the ground with latitude, longitude, and altitude.
 *
 * This class is used to define a ground point in terms of its geographic coordinates
 * and altitude above sea level. It can be extended to include additional properties
 * or methods as needed for specific applications.
 */
class GroundPoint : virtual public AccessObject {
  public:
    /**
     * @brief Constructs a GroundPoint with specified latitude, longitude, and altitude.
     *
     * @param latitutde The latitude of the ground point (default is 0 degrees).
     * @param longitude The longitude of the ground point (default is 0 degrees).
     * @param altitude The altitude of the ground point above sea level (default is 0 kilometers).
     */
    GroundPoint(
        const astro::CelestialBody* parent = nullptr,
        const Angle& latitutde             = 0.0 * mp_units::angular::unit_symbols::deg,
        const Angle& longitude             = 0.0 * mp_units::angular::unit_symbols::deg,
        const Distance& altitude           = 0.0 * mp_units::si::unit_symbols::km
    );

    /**
     * @brief Destructor for the GroundPoint class.
     */
    virtual ~GroundPoint() = default;

    /**
     * @brief Equality operator for comparing two GroundPoint objects.
     *
     * @param other The other GroundPoint to compare with.
     * @return true if the two GroundPoint objects are equal, false otherwise.
     */
    bool operator==(const GroundPoint& other) const;

    /**
     * @brief Gets the geodetic coordinates of the ground point.
     *
     * @return const Geodetic& The geodetic coordinates (latitude, longitude, altitude) of the ground point.
     */
    const astro::Geodetic& get_lla() const;

    /**
     * @brief Gets the latitude of the ground point.
     *
     * @return Angle The latitude of the ground point.
     */
    const Angle& get_latitude() const;

    /**
     * @brief Gets the longitude of the ground point.
     *
     * @return Angle The longitude of the ground point.
     */
    const Angle& get_longitude() const;

    /**
     * @brief Gets the altitude of the ground point above sea level.
     *
     * @return Distance The altitude of the ground point.
     */
    const Distance& get_altitude() const;

    /**
     * @brief Gets the parent celestial body of the ground point.
     *
     * @return const CelestialBody* Pointer to the parent celestial body.
     */

    const astro::CelestialBody* get_parent() const;

    /**
     * @brief Get the unique identifier for the ground station.
     *
     * @return std::size_t The unique identifier for the ground station.
     */
    std::size_t get_id() const;

    /**
     * @brief Get the position of the frame in Earth-Centered-Earth-Fixed (ECEF) coordinates.
     *
     * @param date The date for which to get the position.
     * @return CartesianVector<Distance, frames::earth::earth_fixed>
     */
    astro::CartesianVector<Distance, astro::frames::earth::earth_fixed> get_position() const;

    /**
     * @brief Get the position of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the position.
     * @return CartesianVector<Distance, frames::earth::icrf>
     */
    astro::CartesianVector<Distance, astro::frames::earth::icrf> get_inertial_position(const astro::Date& date) const;

    /**
     * @brief Get the velocity of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the velocity.
     * @return CartesianVector<Velocity, frames::earth::icrf>
     */
    astro::CartesianVector<Velocity, astro::frames::earth::icrf> get_inertial_velocity(const astro::Date& date) const;

    /**
     * @brief Get the name of the ground point.
     *
     * @return std::string The name of the ground point, typically derived from its coordinates or a user-defined identifier.
     */
    std::string get_name() const;

  protected:
    const astro::CelestialBody* _parent; //!< Pointer to the parent celestial body
    astro::Geodetic _lla;                //!< Geodetic coordinates of the ground point
    std::size_t _id;                     //!< Unique identifier for the ground station, generated from its properties.
};

} // namespace trace
} // namespace astrea