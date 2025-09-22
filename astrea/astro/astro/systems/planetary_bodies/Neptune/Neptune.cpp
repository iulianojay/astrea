#include <astro/systems/planetary_bodies/Neptune/Neptune.hpp>

#include <map>

#ifdef ASTREA_BUILD_NEPTUNE_EPHEMERIS
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <ephemerides/Neptune/NeptuneEphemerisTable.hpp>
#endif // ASTREA_BUILD_NEPTUNE_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

using mp_units::non_si::day;
using mp_units::si::unit_symbols::km;

#ifdef ASTREA_BUILD_NEPTUNE_EPHEMERIS

OrbitalElements Neptune::get_elements_at(const Date& date) const
{
    return OrbitalElements(get_elements_at_impl<NeptuneEphemerisTable>(date));
}

#endif // ASTREA_BUILD_NEPTUNE_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea