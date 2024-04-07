#pragma once

#include <unordered_set>

#include "Frame.hpp"
#include "GravitationalBody.hpp"
#include "SolarObjectFactory.hpp"

template <typename T>
class AstrodynamicsSystem {
public: 

    AstrodynamicsSystem(Frame<T> frame) : referenceFrame(frame) {};
    ~AstrodynamicsSystem(){};

    void add_gravitational_body();

private:
    
    Frame<T> referenceFrame;
    solar_system::SolarObjectFactory bodyFactory;
    std::unordered_set<GravitationalBody> allowedBodies;
};