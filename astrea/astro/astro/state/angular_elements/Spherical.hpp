/**
 * @file Spherical.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Spherical class and its associated methods.
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

#include <mp-units/math.h>
#include <mp-units/systems/si/math.h>

// units
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
 * @brief Class representing a Spherical state vector in astrodynamics.
 *
 * This class encapsulates the position and velocity of a vehicle in Spherical coordinates.
 *
 * @tparam _body_ The celestial body NTTP that defines the reference frames.
 */
template <IsCelestialBody auto _body_>
class Spherical : public AngularElementsInterface<Spherical<_body_>, _body_, Distance, Angle, Angle> {

    using BaseType = AngularElementsInterface<Spherical<_body_>, _body_, Distance, Angle, Angle>;

    friend std::ostream& operator<<(std::ostream& os, Spherical const& elements)
    {
        os << "[";
        os << elements.get_range() << ", ";
        os << elements.get_inclination() << ", ";
        os << elements.get_azimuth();
        os << "] (Spherical)";
        return os;
    }

  public:
    template <IsCelestialBody auto B>
    using Self = Spherical<B>; // For introspection
    using BaseType::BaseType;  // Inherit constructors from the base class
    using BaseType::operator=; // Inherit assignment operator from the base class

    /**
     * @brief Default constructor for Spherical.
     *
     * Initializes the Spherical state vector with zero values.
     */
    Spherical() = default;

    /**
     * @brief Get the range value of the Spherical state vector.
     *
     * @return The range value.
     */
    inline constexpr const Distance& get_range() const { return this->template get<0>(); }

    /**
     * @brief Get the inclination value of the Spherical state vector.
     *
     * @return The inclination value.
     */
    inline constexpr const Angle& get_inclination() const { return this->template get<1>(); }

    /**
     * @brief Get the azimuth value of the Spherical state vector.
     *
     * @return The azimuth value.
     */
    inline constexpr const Angle& get_azimuth() const { return this->template get<2>(); }

    /**
     * @brief Get the range value of the Spherical state vector.
     *
     * @return The range value.
     */
    inline constexpr Distance& get_range() { return this->template get<0>(); }

    /**
     * @brief Get the inclination value of the Spherical state vector.
     *
     * @return The inclination value.
     */
    inline constexpr Angle& get_inclination() { return this->template get<1>(); }

    /**
     * @brief Get the azimuth value of the Spherical state vector.
     *
     * @return The azimuth value.
     */
    inline constexpr Angle& get_azimuth() { return this->template get<2>(); }

    /**
     * @brief Set the range value of the Spherical state vector.
     *
     * @param range The range value.
     */
    inline constexpr void set_range(const Distance& range) { this->template get<0>() = range; }

    /**
     * @brief Set the inclination value of the Spherical state vector.
     *
     * @param inclination The inclination value.
     */
    inline constexpr void set_inclination(const Angle& inclination) { this->template get<1>() = inclination; }

    /**
     * @brief Set the azimuth value of the Spherical state vector.
     *
     * @param azimuth The azimuth value.
     */
    inline constexpr void set_azimuth(const Angle& azimuth) { this->template get<2>() = azimuth; }


    /**
     * @brief Convert a body-fixed radius vector to spherical coordinates.
     *
     * @param rFixed The radius vector in the body-fixed frame.
     * @return The range, inclination, and azimuth as a tuple.
     */
    template <IsFrame auto _frame_>
        requires(IsBodyFixedFrame<decltype(_frame_)>)
    static inline constexpr std::tuple<Distance, Angle, Angle> from_body_fixed(const RadiusVector<_frame_>& rFixed)
    {
        using mp_units::sqrt;
        using mp_units::si::acos;
        using mp_units::si::unit_symbols::rad;

        const Distance range    = rFixed.norm();
        const Angle inclination = acos(rFixed.get_z() / range);

        const Distance& x = rFixed.get_x();
        const Distance& y = rFixed.get_y();

        Angle azimuth;
        if (x == 0.0 && y == 0.0) { azimuth = 0.0 * rad; }
        else {
            azimuth = acos(x / sqrt(x * x + y * y));
            if (y < 0.0) { azimuth = -azimuth; }
        }
        return std::make_tuple(range, inclination, azimuth);
    }


    /**
     * @brief Convert spherical coordinates to a body-fixed radius vector.
     *
     * @param range The range.
     * @param inclination The inclination in radians.
     * @param azimuth The azimuth in radians.
     * @return The radius vector in the body-fixed frame.
     */
    template <IsFrame auto _frame_>
        requires(IsBodyFixedFrame<decltype(_frame_)>)
    static inline constexpr RadiusVector<_frame_> to_body_fixed(const Distance& range, const Angle& inclination, const Angle& azimuth)
    {
        using mp_units::si::cos;
        using mp_units::si::sin;

        return RadiusVector<_frame_>(range * sin(inclination) * cos(azimuth), range * sin(inclination) * sin(azimuth), range * cos(inclination));
    }
};

} // namespace astro
} // namespace astrea
