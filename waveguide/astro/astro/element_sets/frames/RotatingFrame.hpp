#pragma once

#include <astro/element_sets/Frame.hpp>

namespace waveguide {
namespace astro {

template <class T>
class RotatingFrame : public Frame<T> {

  public:
    RotatingFrame(const InertialFrame<T>& parent) :
        parentFrame(parent),
        rotationMatrix() // Initialize with an identity matrix or a specific rotation matrix
    {
    }

  private:
    InertialFrame<T> parentFrame;
    DCM rotationMatrix; // rotation matrix from parent frame to this frame
};


// class EarthCenteredEarthFixed : public RotatingFrame<EarthCenteredInertial> {

//   public:
//     EarthCenteredEarthFixed() :
//         RotatingFrame(EarthCenteredInertial())
//     {
//     }
// };

} // namespace astro
} // namespace waveguide