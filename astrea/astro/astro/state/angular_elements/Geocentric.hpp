/**
 * @file Geocentric.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Geocentric class and its associated methods.
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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
#include <math/trig.hpp>
#include <units/units.hpp>

// astro
#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions.hpp>
#include <astro/frames/framework.hpp>
#include <astro/state/framework/AngularElementsInterface.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/system_concepts.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Calculate the geocentric radius given latitude and Earth's radii.
 *
 * @param lat The latitude in radians.
 * @param requatorial The equatorial radius of the Earth.
 * @param rPolar The polar radius of the Earth.
 * @return The geocentric radius.
 */
template <IsCelestialBody auto body>
inline constexpr Distance calculate_geocentric_radius(const Angle& lat)
{
    using math::cos;
    using math::sin;
    using mp_units::pow;

    static constexpr Distance a = get_equatorial_radius<body>();
    static constexpr Distance b = get_polar_radius<body>();
    const Unitless cosLatSq     = pow<2>(cos(lat));
    const Unitless sinLatSq     = pow<2>(sin(lat));
    return sqrt((pow<4>(a) * cosLatSq + pow<4>(b) * sinLatSq) / (pow<2>(a) * cosLatSq + pow<2>(b) * sinLatSq));
}

/**
 * @brief Class representing a Geocentric state vector in astrodynamics.
 *
 * This class encapsulates the position and velocity of a vehicle in Geocentric coordinates.
 *
 * @tparam _body_ The celestial body NTTP that defines the reference ellipsoid and frames.
 */
template <IsCelestialBody auto _body_>
class Geocentric : public AngularElementsInterface<Geocentric<_body_>, _body_, Angle, Angle, Distance> {

    using BaseType = AngularElementsInterface<Geocentric<_body_>, _body_, Angle, Angle, Distance>;

    friend std::ostream& operator<<(std::ostream& os, Geocentric const& elements)
    {
        using mp_units::si::unit_symbols::deg;

        os << "[";
        os << elements.get_latitude().in(deg) << ", ";
        os << elements.get_longitude().in(deg);
        if (elements.get_altitude() != 0.0) { os << ", " << elements.get_altitude(); }
        os << "] (Geocentric)";
        return os;
    }

  public:
    template <IsCelestialBody auto B>
    using Self = Geocentric<B>; // For introspection
    using BaseType::BaseType;   // Inherit constructors from the base class
    using BaseType::operator=;  // Inherit assignment operator from the base class

    /**
     * @brief Default constructor for Geocentric.
     */
    Geocentric() = default;

    /**
     * @brief Default destructor for Geocentric.
     */
    ~Geocentric() = default;

    /**
     * @brief Get the latitude of the Geocentric state vector.
     *
     * @return const Angle& Reference to the latitude component of the Geocentric state vector.
     */
    inline constexpr const Angle& get_latitude() const { return this->template get<0>(); }

    /**
     * @brief Get the longitude of the Geocentric state vector.
     *
     * @return const Angle& Reference to the longitude component of the Geocentric state vector.
     */
    inline constexpr const Angle& get_longitude() const { return this->template get<1>(); }

    /**
     * @brief Get the altitude of the Geocentric state vector.
     *
     * @return const Distance& Reference to the altitude component of the Geocentric state vector.
     */
    inline constexpr const Distance& get_altitude() const { return this->template get<2>(); }

    /**
     * @brief Get the latitude of the Geocentric state vector.
     *
     * @return const Angle& Reference to the latitude component of the Geocentric state vector.
     */
    inline constexpr Angle& get_latitude() { return this->template get<0>(); }

    /**
     * @brief Get the longitude of the Geocentric state vector.
     *
     * @return const Angle& Reference to the longitude component of the Geocentric state vector.
     */
    inline constexpr Angle& get_longitude() { return this->template get<1>(); }

    /**
     * @brief Get the altitude of the Geocentric state vector.
     *
     * @return const Distance& Reference to the altitude component of the Geocentric state vector.
     */
    inline constexpr Distance& get_altitude() { return this->template get<2>(); }

    /**
     * @brief Set the latitude of the Geocentric state vector.

     * @param latitude The latitude to set for the Geocentric state vector.
     */
    inline void set_latitude(const Angle& latitude) { this->template get<0>() = latitude; }

    /**
     * @brief Set the longitude of the Geocentric state vector.
     *
     * @param longitude The longitude to set for the Geocentric state vector.
     */
    inline void set_longitude(const Angle& longitude) { this->template get<1>() = longitude; }

    /**
     * @brief Set the altitude of the Geocentric state vector.
     *
     * @param altitude The altitude to set for the Geocentric state vector.
     */
    inline void set_altitude(const Distance& altitude) { this->template get<2>() = altitude; }

    /**
     * @brief Convertfrom geocentric coordinates to LLA
     *
     * @param rEcef The radius vector in geocentric coordinates.
     * @return The latitude, longitude, and altitude as a tuple.
     */
    template <IsFrame auto frame>
        requires(equivalent(frame, BaseType::_fixed_frame_))
    static inline constexpr std::tuple<Angle, Angle, Distance> from_body_fixed(const RadiusVector<frame>& rEcef)
    {
        using math::atan2;
        using mp_units::sqrt;

        const Distance& x = rEcef[0];
        const Distance& y = rEcef[1];
        const Distance& z = rEcef[2];
        const Distance R  = rEcef.norm();

        const Distance rho = sqrt(x * x + y * y);

        const Angle longitude = atan2(y, x);
        const Angle latitude  = atan2(z, rho);

        const Distance rGeocentric = calculate_geocentric_radius<_body_>(latitude);
        const Distance altitude    = R - rGeocentric;

        return { latitude, longitude, altitude };
    }

    /**
     * @brief Convert from LLA to geocentric coordinates.
     *
     * @param lat The latitude in radians.
     * @param lon The longitude in radians.
     * @param alt The altitude in meters.
     * @return The radius vector in geocentric coordinates.
     */
    template <IsFrame auto frame>
        requires(equivalent(frame, BaseType::_fixed_frame_))
    inline constexpr RadiusVector<frame> convert_geocentric_to_body_fixed(const Angle& lat, const Angle& lon, const Distance& alt)
    {
        using math::cos;
        using math::sin;

        const Distance rGeocentric = calculate_geocentric_radius<_body_>(lat);
        const Distance R           = rGeocentric + alt;

        // Ecef coordinates
        return { R * cos(lat) * cos(lon), R * cos(lat) * sin(lon), R * sin(lat) };
    }
};

} // namespace astro
} // namespace astrea
