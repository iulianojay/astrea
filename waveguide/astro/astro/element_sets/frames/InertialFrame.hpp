#pragma once

#include <astro/element_sets/Frame.hpp>

namespace waveguide {
namespace astro {

template <class T>
class InertialFrame : public Frame<T> {

    static_assert(
        std::is_same<T, CelestialBody>::value || std::is_base_of<T, CelestialBody>::value || std::is_same<T, InertialFrame>::value,
        "Inertial frames must be defined in reference to one of the following types: [CelestialBody, Barycenter, "
        "InertialFrame]."
    );

  public:
    InertialFrame(const T& origin) :
        Frame<T>(origin)
    {
    }
};

// using EarthCenteredInertial = InertialFrame<CelestialBody("Earth")>; // I guess we just make this the default?

} // namespace astro
} // namespace waveguide