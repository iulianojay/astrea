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

#include <sstream>
#include <string>

#include <mp-units/systems/angular.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>

#include <astro/astro.fwd.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/state/angular_elements.hpp>
#include <astro/systems/property_getters.hpp>
#include <astro/systems/system_concepts.hpp>
#include <astro/time/Date.hpp>
#include <units/units.hpp>

#include <utilities/IdProvider.hpp>

#include <trace/platforms/AccessObject.hpp>
#include <trace/types/typedefs.hpp>


namespace astrea {
namespace trace {

/**
 * @brief Represents a point on the surface of a celestial body with latitude, longitude, and altitude.
 *
 * @tparam _body_ The celestial body NTTP this ground point resides on.
 */
template <astro::IsCelestialBody auto _body_>
class GroundPoint : virtual public AccessObject {
  public:
    static constexpr auto body = _body_; //!< The celestial body this ground point resides on.

    /**
     * @brief Constructs a GroundPoint with specified latitude, longitude, and altitude.
     *
     * @param latitude  The latitude of the ground point (default is 0 degrees).
     * @param longitude The longitude of the ground point (default is 0 degrees).
     * @param altitude  The altitude of the ground point above the surface (default is 0 km).
     */
    GroundPoint(
        const Angle& latitude    = 0.0 * mp_units::angular::unit_symbols::deg,
        const Angle& longitude   = 0.0 * mp_units::angular::unit_symbols::deg,
        const Distance& altitude = 0.0 * mp_units::si::unit_symbols::km
    ) :
        AccessObject(),
        _lla(latitude, longitude, altitude),
        _id(utilities::IdProvider::get_next_id<"Platform">())
    {
    }

    virtual ~GroundPoint() = default;

    /**
     * @brief Equality operator — compares geodetic coordinates.
     */
    bool operator==(const GroundPoint& other) const { return _lla == other._lla; }

    /**
     * @brief Returns the geodetic coordinates of the ground point.
     */
    const astro::Geodetic<_body_>& get_lla() const { return _lla; }

    /**
     * @brief Returns the latitude of the ground point.
     */
    const Angle& get_latitude() const { return _lla.get_latitude(); }

    /**
     * @brief Returns the longitude of the ground point.
     */
    const Angle& get_longitude() const { return _lla.get_longitude(); }

    /**
     * @brief Returns the altitude of the ground point above the surface.
     */
    const Distance& get_altitude() const { return _lla.get_altitude(); }

    /**
     * @brief Returns the unique identifier for this ground point.
     */
    std::size_t get_id() const override { return _id; }

    /**
     * @brief Returns the position in the body-fixed frame.
     */
    auto get_position() const { return _lla.get_position(); }

    /**
     * @brief Returns the inertial position at the given date.
     */
    auto get_position(const astro::Date& date) const { return _lla.get_position(date); }

    /**
     * @brief Returns the inertial velocity at the given date, computed from the body's rotation rate.
     */
    auto get_velocity(const astro::Date& date) const
    {
        using namespace mp_units::si::unit_symbols;
        constexpr auto fixed_frame = astro::Geodetic<_body_>::_fixed_frame_;
        constexpr auto icrf_frame  = astro::Geodetic<_body_>::_icrf_frame_;

        const auto rEcef = _lla.get_position();
        const auto rEcefPlanar = astro::CartesianVector<Distance, fixed_frame>{ rEcef.get_x(), rEcef.get_y(), 0.0 * km };

        const Distance rEcefPlanarNorm = rEcefPlanar.norm();
        const Velocity vEcefMag = rEcefPlanarNorm * astro::get_rotation_rate<_body_>() / mp_units::isq_angle::cotes_angle;

        const astro::CartesianVector<Distance, fixed_frame> z{ 0.0 * km, 0.0 * km, 1.0 * km };
        const auto vEcef = z.cross(rEcefPlanar).direction() * vEcefMag;

        return vEcef.template in_frame<icrf_frame>(date, rEcef);
    }

    /**
     * @brief Returns a human-readable name for the ground point.
     */
    std::string get_name() const
    {
        using mp_units::angular::unit_symbols::deg;
        using mp_units::si::unit_symbols::km;

        std::ostringstream oss;
        oss << "[" << _lla.get_latitude().in(deg) << ", " << _lla.get_longitude().in(deg);
        if (_lla.get_altitude() != 0.0 * km) { oss << ", " << _lla.get_altitude(); }
        oss << "]";
        oss << " (" << decltype(_body_)::name.portable() << ")";

        return oss.str();
    }

  protected:
    astro::Geodetic<_body_> _lla; //!< Geodetic coordinates of the ground point.
    std::size_t _id;              //!< Unique identifier, generated at construction.
};

} // namespace trace
} // namespace astrea