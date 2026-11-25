/**
 * @file Geodetic.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Geodetic class and its associated methods.
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
#include <math/operations.hpp>
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
 * @brief Class representing a Geodetic state vector in astrodynamics.
 *
 * This class encapsulates the latitude, longitude, and altitude of a position
 * in geodetic coordinates relative to the surface of a celestial body.
 *
 * @tparam _body_ The celestial body NTTP that defines the reference ellipsoid and frames.
 */
template <IsCelestialBody auto _body_>
class Geodetic : public AngularElementsInterface<Geodetic<_body_>, _body_, Angle, Angle, Distance> {

    using BaseType = AngularElementsInterface<Geodetic<_body_>, _body_, Angle, Angle, Distance>;

    friend inline std::ostream& operator<<(std::ostream& os, Geodetic const& elements)
    {
        using mp_units::si::unit_symbols::deg;
        using mp_units::si::unit_symbols::km;
        os << "[";
        os << elements.get_latitude().in(deg) << ", ";
        os << elements.get_longitude().in(deg);
        if (elements.get_altitude() != 0.0 * km) { os << ", " << elements.get_altitude(); }
        os << "] (Geodetic)";
        return os;
    }

  public:
    template <IsCelestialBody auto B>
    using Self = Geodetic<B>;  // For introspection
    using BaseType::BaseType;  // Inherit constructors from the base class
    using BaseType::operator=; // Inherit assignment operator from the base class

    /**
     * @brief Default constructor for Geodetic.
     *
     * Initializes the Geodetic state vector with zero values.
     */
    Geodetic() = default;

    /**
     * @brief Default destructor for Geodetic.
     */
    ~Geodetic() = default;

    /**
     * @brief Get the latitude of the Geodetic state vector.
     *
     * @return const Angle& Reference to the latitude component of the Geodetic state vector.
     */
    inline constexpr const Angle& get_latitude() const { return this->template get<0>(); }

    /**
     * @brief Get the longitude of the Geodetic state vector.
     *
     * @return const Angle& Reference to the longitude component of the Geodetic state vector.
     */
    inline constexpr const Angle& get_longitude() const { return this->template get<1>(); }

    /**
     * @brief Get the altitude of the Geodetic state vector.
     *
     * @return const Distance& Reference to the altitude component of the Geodetic state vector.
     */
    inline constexpr const Distance& get_altitude() const { return this->template get<2>(); }

    /**
     * @brief Get the latitude of the Geodetic state vector.
     *
     * @return const Angle& Reference to the latitude component of the Geodetic state vector.
     */
    inline constexpr Angle& get_latitude() { return this->template get<0>(); }

    /**
     * @brief Get the longitude of the Geodetic state vector.
     *
     * @return const Angle& Reference to the longitude component of the Geodetic state vector.
     */
    inline constexpr Angle& get_longitude() { return this->template get<1>(); }

    /**
     * @brief Get the altitude of the Geodetic state vector.
     *
     * @return const Distance& Reference to the altitude component of the Geodetic state vector.
     */
    inline constexpr Distance& get_altitude() { return this->template get<2>(); }

    /**
     * @brief Set the latitude of the Geodetic state vector.
     *
     * @param latitude The latitude to set for the Geodetic state vector.
     */
    inline void set_latitude(const Angle& latitude) { this->template get<0>() = latitude; }

    /**
     * @brief Set the longitude of the Geodetic state vector.
     *
     * @param longitude The longitude to set for the Geodetic state vector.
     */
    inline void set_longitude(const Angle& longitude) { this->template get<1>() = longitude; }

    /**
     * @brief Set the altitude of the Geodetic state vector.
     *
     * @param altitude The altitude to set for the Geodetic state vector.
     */
    inline void set_altitude(const Distance& altitude) { this->template get<2>() = altitude; }

    /**
     * @brief Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates.
     *
     * @param rEcef The radius vector in ECEF coordinates.
     * @param requatorial The equatorial radius of the Earth.
     * @param rPolar The polar radius of the Earth.
     * @return The latitude, longitude, and altitude as a tuple.
     */
    template <IsFrame auto frame>
        requires(equivalent(frame, BaseType::_fixed_frame_))
    static inline std::tuple<Angle, Angle, Distance> from_body_fixed(const RadiusVector<frame>& rBodyFixed)
    {
        using mp_units::abs;
        using mp_units::sqrt;
        using mp_units::si::atan2;
        using mp_units::si::unit_symbols::km;
        using mp_units::si::unit_symbols::mm;

        static const unsigned MAX_ITER  = 1e4;
        static const Distance MAX_ERROR = 1.0 * mm;

        const Distance& xEcef = rBodyFixed[0];
        const Distance& yEcef = rBodyFixed[1];
        const Distance& zEcef = rBodyFixed[2];

        static const Distance requatorial = get_equatorial_radius<decltype(frame)::origin>();
        static const Distance rPolar      = get_polar_radius<decltype(frame)::origin>();
        static const Unitless f           = (requatorial - rPolar) / requatorial;
        static const Unitless eSq         = (2.0 - f) * f;

        const auto xSqYSq = xEcef * xEcef + yEcef * yEcef;

        Distance dz  = eSq * zEcef;
        Distance err = 1.0 * km;
        Distance N   = 0.0 * km;
        unsigned ii  = 0;
        while (err > MAX_ERROR && ii < MAX_ITER) {
            const Unitless s = (zEcef + dz) / sqrt(xSqYSq + (zEcef + dz) * (zEcef + dz));
            N                = requatorial / sqrt(1 - eSq * s * s);
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
     * @param requatorial The equatorial radius of the Earth.
     * @param rPolar The polar radius of the Earth.
     * @return The radius vector in ECEF coordinates.
     */
    template <IsFrame auto frame>
        requires(equivalent(frame, BaseType::_fixed_frame_))
    static inline constexpr RadiusVector<frame> to_body_fixed(const Angle& lat, const Angle& lon, const Distance& alt)
    {
        using math::cos;
        using math::sin;

        const Unitless sinLat = sin(lat);
        const Unitless cosLat = cos(lat);

        static constexpr Distance requatorial = get_equatorial_radius<decltype(frame)::origin>();
        static constexpr Distance rPolar      = get_polar_radius<decltype(frame)::origin>();
        static constexpr Unitless f           = (requatorial - rPolar) / requatorial;
        static constexpr Unitless eSq         = (2.0 - f) * f;

        const Distance N = requatorial / math::sqrt(1.0 - eSq * sinLat * sinLat);

        // Ecef coordinates
        return { (N + alt) * cosLat * cos(lon), (N + alt) * cosLat * sin(lon), ((1.0 - eSq) * N + alt) * sinLat };
    }
};

} // namespace astro
} // namespace astrea
