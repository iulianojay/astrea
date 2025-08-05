#pragma once

#include <astro/frames/Frame.hpp>

namespace waveguide {
namespace astro {

class InertialFrame : public Frame {

  public:
    InertialFrame(const std::string& name, const std::string& origin) :
        Frame(name, origin)
    {
    }
    virtual ~InertialFrame() = default;
};

} // namespace astro
} // namespace waveguide