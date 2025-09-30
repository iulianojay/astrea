#include <astro/systems/planetary_bodies/Jupiter/Jupiter.hpp>

#include <map>

#ifdef ASTREA_BUILD_JUPITER_EPHEMERIS
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <ephemerides/Jupiter/JupiterEphemerisTable.hpp>
#endif // ASTREA_BUILD_JUPITER_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

#ifdef ASTREA_BUILD_JUPITER_EPHEMERIS

CartesianVector<InterplanetaryDistance, frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const
{
    const auto positionJbFromSsb = get_position_at_impl<JupiterEphemerisTable, frames::solar_system_barycenter::icrf>(date);
    return positionJbFromSsb; // TODO: Add correction for Jupiter's position from Jupiter barycenter
}

#endif // ASTREA_BUILD_JUPITER_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea