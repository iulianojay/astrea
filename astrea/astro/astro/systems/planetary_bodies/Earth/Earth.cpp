/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/systems/planetary_bodies/Earth/Earth.hpp>

#include <map>

#include <mp-units/math.h>
#include <mp-units/systems/angular.h>

#include <math/math.hpp>

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <ephemerides/Earth/EarthFromEmbEphemerisTable.hpp>
#include <ephemerides/Earth/EmbEphemerisTable.hpp>
#endif // ASTREA_BUILD_EARTH_EPHEMERIS

#include <astro/state/State.hpp>
#include <astro/state/angular_elements/instances/Geodetic.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

Density Earth::find_atmospheric_density(const State& state) const
{
    switch (_atmosphereModel) {
        case EarthAtmosphereModel::JACHIA_ROBERTS: return JacciaRobertsAtmosphere::find_atmospheric_density(state);
        case EarthAtmosphereModel::HARRIS_PRIESTER: return HarrisPriesterAtmosphere::find_atmospheric_density(state);
        case EarthAtmosphereModel::NRLMSISE00:
        case EarthAtmosphereModel::DTM2000:
        default: throw std::runtime_error("Selected atmospheric model not implemented yet");
    }
}

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS

RadiusVector<frames::solar_system_barycenter::icrf> Earth::get_position_at(const Date& date) const
{
    const auto positionEmbFromSsb = get_position_at_impl<EmbEphemerisTable, frames::solar_system_barycenter::icrf>(date);
    const auto positionEarthFromEmb = get_position_at_impl<EarthFromEmbEphemerisTable, frames::earth_barycenter::icrf>(date);
    return positionEmbFromSsb + positionEarthFromEmb.force_frame_conversion<frames::solar_system_barycenter::icrf>();
}

VelocityVector<frames::solar_system_barycenter::icrf> Earth::get_velocity_at(const Date& date) const
{
    const auto velocityEarthFromEmb = get_velocity_at_impl<EarthFromEmbEphemerisTable, frames::earth_barycenter::icrf>(date);
    return velocityEarthFromEmb.force_frame_conversion<frames::solar_system_barycenter::icrf>();
}

#endif // ASTREA_BUILD_EARTH_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea