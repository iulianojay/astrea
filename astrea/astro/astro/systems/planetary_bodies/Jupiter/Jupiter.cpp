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

OrbitalElements Jupiter::get_elements_at(const Date& date) const
{
    return OrbitalElements(get_elements_at_impl<JupiterEphemerisTable>(date));
}

#endif // ASTREA_BUILD_JUPITER_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea