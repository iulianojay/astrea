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

CartesianVector<InterplanetaryDistance, frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const
{
    static const Earth earth;
    const auto positionEarthFromSsb  = earth.get_position_at(date);
    const auto positionMoonFromEarth = get_position_at_impl<MoonEphemerisTable, frames::earth::icrf>(date);
    return positionEarthFromSsb.translate(positionMoonFromEarth);
}

#endif // ASTREA_BUILD_EARTH_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea