#pragma once

#include <vector>

#include "Frame.hpp"
#include "GravitationalBody.hpp"

template <class T>
class Barycenter : public GravitationalBody {
public:

    Barycenter(std::vector<GravitationalBody> bodies, InertialFrame<T> frame) : referenceFrame(frame) {};
    ~Barycenter() {};

private:
    
    basis center;
    const InertialFrame<T> referenceFrame;
};