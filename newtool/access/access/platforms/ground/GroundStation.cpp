#include <access/platforms/ground/GroundStation.hpp>


void GroundStation::generate_id_hash()
{
    id = std::hash<double>()(lla[0]) ^ std::hash<double>()(lla[1]) ^ std::hash<double>()(lla[2]);
}