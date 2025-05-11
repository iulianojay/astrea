#include <access/platforms/ground/GroundStation.hpp>

namespace accesslib {

void GroundStation::generate_id_hash()
{
    // TODO: Fix
    // id = std::hash<astro::Angle>()(latitude) ^ std::hash<astro::Angle>()(longitude) ^ std::hash<astro::Distance>()(altitude);
    id = 0;
}

} // namespace accesslib