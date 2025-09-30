#include <astro/systems/planetary_bodies/Mercury/Mercury.hpp>

#include <map>

#ifdef ASTREA_BUILD_MERCURY_EPHEMERIS
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <ephemerides/Mercury/MercuryEphemerisTable.hpp>
#endif // ASTREA_BUILD_MERCURY_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

using mp_units::non_si::day;
using mp_units::si::unit_symbols::km;

#ifdef ASTREA_BUILD_MERCURY_EPHEMERIS

CartesianVector<InterplanetaryDistance, frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const
{
    const auto positionMbFromSsb = get_position_at_impl<MercuryEphemerisTable, frames::solar_system_barycenter::icrf>(date);
    return positionMbFromSsb; // TODO: Add correction for Mercury's position from Mercury barycenter
}

#endif // ASTREA_BUILD_MERCURY_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea