#include <access/platforms/ground/GroundStation.hpp>

#include <mp-units/systems/angular.h>

namespace accesslib {

void GroundStation::generate_id_hash()
{
    _id = std::hash<astro::Angle>()(_latitude) ^ std::hash<astro::Angle>()(_longitude) ^ std::hash<astro::Distance>()(_altitude);
}

} // namespace accesslib