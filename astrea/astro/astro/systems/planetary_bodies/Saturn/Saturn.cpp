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

OrbitalElements Saturn::get_elements_at(const Date& date) const
{
    return OrbitalElements(get_elements_at_impl<SaturnEphemerisTable>(date));
}

#endif // ASTREA_BUILD_SATURN_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea