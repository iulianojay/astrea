#pragma once

#ifndef SWIG
    #include <vector>
#endif

#include <access/platforms/Sensor.hpp>

struct Channel {
    double frequency;
    double bandwidth;
};


class Antenna : public Sensor {
public:

    using Sensor::Sensor;

private:

    double gain;
    double wavelength;
    std::vector<Channel> channels;

};


#ifdef SWIG

%template(AntennaVector) std::vector<Antenna>;

#endif