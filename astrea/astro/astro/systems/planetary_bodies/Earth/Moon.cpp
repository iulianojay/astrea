#include <astro/systems/planetary_bodies/Earth/Moon.hpp>

#include <map>

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <ephemerides/Earth/MoonEphemerisTable.hpp>
#endif // ASTREA_BUILD_EARTH_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

using mp_units::non_si::day;
using mp_units::si::unit_symbols::km;

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS

RadiusVector<frames::solar_system_barycenter::icrf> Moon::get_position_at(const Date& date) const
{
    const auto positionMoonFromEarth = get_position_at_impl<MoonEphemerisTable, frames::earth::icrf>(date);
    return positionMoonFromEarth.force_frame_conversion<frames::solar_system_barycenter::icrf>();
}

#endif // ASTREA_BUILD_EARTH_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea