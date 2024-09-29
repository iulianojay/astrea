#pragma once

#include "FieldOfView.hpp"
#include "RiseSetArray.hpp"


struct Access {
    int targetId;
    RiseSetArray accessTimes;
    bool twoWay;
};


class SensorBase {

public:

    SensorBase(const FieldOfView& fov) : fov(fov) {}
    ~SensorBase();

    const bool contains(const basis_array& target) const {
        return fov.contains(target);
    }

private:

    int id;
    int parentId;
    const FieldOfView fov;
    std::vector<Access> accesses;

};


class Sensor : public SensorBase {
public:

    using SensorBase::SensorBase;

};


class Antenna : public SensorBase {
public:

    using SensorBase::SensorBase;

private:

    double frequency;
    double wavelength;
    double gain;

};