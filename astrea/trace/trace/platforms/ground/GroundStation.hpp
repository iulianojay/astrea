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

    ~GroundStation() = default;

    std::size_t get_id() const override { return Base::_id; }

    std::string get_name() const { return _name; }

  private:
    std::string _name; //!< Human-readable name of the ground station.
};

} // namespace trace
} // namespace astrea