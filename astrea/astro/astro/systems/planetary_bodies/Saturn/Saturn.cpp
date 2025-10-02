#include <astro/systems/planetary_bodies/Saturn/Saturn.hpp>

#include <map>

#ifdef ASTREA_BUILD_SATURN_EPHEMERIS
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <ephemerides/Saturn/SaturnEphemerisTable.hpp>
#endif // ASTREA_BUILD_SATURN_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

using mp_units::non_si::day;
using mp_units::si::unit_symbols::km;

#ifdef ASTREA_BUILD_SATURN_EPHEMERIS

RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const
{
    const auto positionSbFromSsb = get_position_at_impl<SaturnEphemerisTable, frames::solar_system_barycenter::icrf>(date);
    return positionSbFromSsb; // TODO: Add correction for Saturn's position from Saturn barycenter
}

#endif // ASTREA_BUILD_SATURN_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea