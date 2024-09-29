#pragma once

#include <vector>

#include "typedefs.hpp"
#include "Sensor.hpp"

class GroundStation {
public:

    GroundStation();
    ~GroundStation();

private:

    basis_array lla;

    std::vector<Sensor> sensors;
    std::vector<Antenna> antennas;

};