/**
 * @file GroundStation.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the GroundStation class.
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
#include <vector>

#include <astro/systems/system_concepts.hpp>
#include <astro/time/Date.hpp>
#include <units/units.hpp>

#include <trace/platforms/ground/GroundPoint.hpp>
#include <trace/platforms/sensors/Sensor.hpp>

namespace astrea {
namespace trace {

/**
 * @brief Ground station on the surface of a celestial body, with sensors.
 *
 * @tparam _body_ The celestial body NTTP this station resides on.
 */
template <astro::IsCelestialBody auto _body_>
class GroundStation : public GroundPoint<_body_>, public SensorPlatform {
    using Base = GroundPoint<_body_>;

  public:
    /**
     * @brief Constructs a GroundStation.
     *
     * @param latitude  Geodetic latitude.
     * @param longitude Longitude.
     * @param altitude  Altitude above the surface (default 0 km).
     * @param name      Human-readable name (default "Unnamed").
     * @param sensors   Sensor parameters to attach (default none).
     */
    GroundStation(
        const Angle& latitude,
        const Angle& longitude,
        const Distance& altitude                     = 0.0 * mp_units::si::unit_symbols::km,
        const std::string name                       = "Unnamed",
        const std::vector<SensorParameters>& sensors = {}
    ) :
        Base(latitude, longitude, altitude),
        SensorPlatform(),
        _name(name)
    {
        for (const auto& sp : sensors) {
            attach_payload(sp);
        }
    }

    /**
     * @brief Default destructor for GroundStation
     */
    ~GroundStation() = default;

    /**
     * @brief Gets the unique identifier for this ground station.
     *
     * @return std::size_t The unique identifier for this ground station.
     */
    std::size_t get_id() const override { return Base::_id; }

    /**
     * @brief Gets the human-readable name of the ground station.
     *
     * @return std::string The name of the ground station.
     */
    std::string get_name() const { return _name; }

    /**
     * @brief Gets the position of the ground station in the body-fixed frame.
     *
     * @return astro::RadiusVector<astro::frames::Geodetic<_body_>::_fixed_frame_> The position of the ground station in the body-fixed frame.
     */
    auto get_position() const { return Base::get_position(); }

    /**
     * @brief Gets the inertial position of the spacecraft at a specific date.
     *
     * @param date The date at which to retrieve the position.
     * @return astro::RadiusVector<astro::frames::earth::icrf> The inertial position of the spacecraft.
     */
    astro::RadiusVector<astro::frames::earth::icrf> get_position(const astro::Date& date) const
    {
        return Base::get_position(date);
    }

    /**
     * @brief Gets the inertial velocity of the spacecraft at a specific date.
     *
     * @param date The date at which to retrieve the velocity.
     * @return astro::VelocityVector<astro::frames::earth::icrf> The inertial velocity of the spacecraft.
     */
    astro::VelocityVector<astro::frames::earth::icrf> get_velocity(const astro::Date& date) const
    {
        return Base::get_velocity(date);
    }

  private:
    std::string _name; //!< Human-readable name of the ground station.
};

} // namespace trace
} // namespace astrea