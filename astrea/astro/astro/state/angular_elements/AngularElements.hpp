#pragma once

#include <array>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

class AngularElements {
  public:
    AngularElements()  = default;
    ~AngularElements() = default;

  private:
    std::array<Angle, 3> _angles;                  //!< Euler angles or quaternion
    std::array<AngularRate, 3> _angularVelocities; //!< Euler angular velocities
};


class AngularElementPartials {
  public:
    AngularElementPartials()  = default;
    ~AngularElementPartials() = default;

  private:
    std::array<AngularRate, 3> _angularVelocities;            //!< Euler angular velocities
    std::array<AngularAcceleration, 3> _angularAccelerations; //!< Euler angular accelerations
}


} // namespace astro
} // namespace astrea