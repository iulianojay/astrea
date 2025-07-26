#include <access/platforms/ground/GroundStation.hpp>

#include <mp-units/systems/angular.h>

namespace waveguide {
namespace accesslib {

void GroundStation::generate_id_hash()
{
    _id = std::hash<Angle>()(_latitude) ^ std::hash<Angle>()(_longitude) ^ std::hash<Distance>()(_altitude);
}

} // namespace accesslib
} // namespace waveguide