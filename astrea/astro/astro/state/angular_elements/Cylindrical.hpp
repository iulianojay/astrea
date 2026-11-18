/**
 * @file Cylindrical.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Cylindrical class and its associated methods.
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
 * @brief Class representing a Cylindrical state vector in astrodynamics.
 *
 * This class encapsulates the position and velocity of a vehicle in Cylindrical coordinates.
 *
 * @tparam _body_ The celestial body NTTP that defines the reference frames.
 */
template <IsCelestialBody auto _body_>
class Cylindrical : public AngularElementsInterface<Cylindrical<_body_>, _body_, Distance, Angle, Distance> {

    using BaseType = AngularElementsInterface<Cylindrical<_body_>, _body_, Distance, Angle, Distance>;

    template <IsCelestialBody auto body>
    friend std::ostream& operator<<(std::ostream& os, Cylindrical<body> const& elements)
    {
        os << "[";
        os << elements.get_range() << ", ";
        os << elements.get_azimuth() << ", ";
        os << elements.get_elevation();
        os << "] (Cylindrical)";
        return os;
    }

  public:
    template <IsCelestialBody auto B>
    using Self = Cylindrical<B>; // For introspection
    using BaseType::BaseType;    // Inherit constructors from the base class
    using BaseType::operator=;   // Inherit assignment operator from the base class

    /**
     * @brief Default constructor for Cylindrical.
     */
    Cylindrical() = default;

    /**
     * @brief Get the range value of the Cylindrical state vector.
     *
     * @return The range distance.
     */
    const Distance& get_range() const { return this->template get<0>(); }

    /**
     * @brief Get the azimuth value of the Cylindrical state vector.
     *
     * @return The azimuth angle.
     */
    const Angle& get_azimuth() const { return this->template get<1>(); }

    /**
     * @brief Get the elevation value of the Cylindrical state vector.
     *
     * @return The elevation angle.
     */
    const Distance& get_elevation() const { return this->template get<2>(); }

    /**
     * @brief Convert a body-fixed radius vector to cylindrical coordinates.
     *
     * @param rFixed The radius vector in the body-fixed frame.
     * @return The range, azimuth, and elevation as a tuple.
     */
    template <IsFrame auto _frame_>
        requires(IsBodyFixedFrame<decltype(_frame_)>)
    static std::tuple<Distance, Angle, Distance> from_body_fixed(const RadiusVector<_frame_>& rFixed)
    {
        using mp_units::si::acos;

        const Distance range     = rFixed.norm();
        const Distance elevation = rFixed.get_z();
        Angle azimuth = acos(rFixed.get_x() / sqrt(rFixed.get_x() * rFixed.get_x() + rFixed.get_y() * rFixed.get_y()));
        if (rFixed.get_y() < 0.0) { azimuth = -azimuth; }
        return { range, azimuth, elevation };
    }

    /**
     * @brief Convert cylindrical coordinates to a body-fixed radius vector.
     *
     * @param range The range.
     * @param azimuth The azimuth in radians.
     * @param elevation The elevation.
     * @return The radius vector in the body-fixed frame.
     */
    template <IsFrame auto _frame_>
        requires(IsBodyFixedFrame<decltype(_frame_)>)
    static RadiusVector<_frame_> to_body_fixed(const Distance& range, const Angle& azimuth, const Distance& elevation)
    {
        using mp_units::si::cos;
        using mp_units::si::sin;

        return RadiusVector<_frame_>(range * cos(azimuth), range * sin(azimuth), elevation);
    }
};

} // namespace astro
} // namespace astrea
