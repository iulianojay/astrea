#include <astro/systems/planetary_bodies/Uranus/Uranus.hpp>

#include <map>

#ifdef ASTREA_BUILD_URANUS_EPHEMERIS
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <ephemerides/Uranus/UranusEphemerisTable.hpp>
#endif // ASTREA_BUILD_URANUS_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

using mp_units::non_si::day;
using mp_units::si::unit_symbols::km;

#ifdef ASTREA_BUILD_URANUS_EPHEMERIS

OrbitalElements Uranus::get_elements_at(const Date& date) const
{
    return OrbitalElements(get_elements_at_impl<UranusEphemerisTable>(date));
}

#endif // ASTREA_BUILD_URANUS_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea