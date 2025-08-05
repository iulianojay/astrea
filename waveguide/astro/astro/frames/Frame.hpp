#pragma once

#include <string>

#include <units/typedefs.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/types/typedefs.hpp>

namespace waveguide {
namespace astro {


class Frame {

  protected:
    Frame() = default;
    Frame(const std::string& name, const std::string& origin) :
        name(name),
        origin(origin)
    {
    }
    virtual ~Frame() = default;

  protected:
    std::string name;
    std::string origin;
};


} // namespace astro
} // namespace waveguide