#pragma once

#include <astro/frames/Frame.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/frames/types/InertialFrame.hpp>
#include <astro/time/Date.hpp>
#include <astro/utilities/conversions.hpp>

namespace waveguide {
namespace astro {

class RotatingFrame : public Frame {

  public:
    RotatingFrame(const std::string& name, const std::string& origin, const InertialFrame& parent) :
        Frame(name, origin),
        parentFrame(parent)
    {
    }

  private:
    InertialFrame parentFrame;
};

} // namespace astro
} // namespace waveguide