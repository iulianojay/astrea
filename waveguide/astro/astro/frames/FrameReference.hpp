#pragma once

#include <string>

#include <units/typedefs.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/types/typedefs.hpp>

namespace waveguide {
namespace astro {

class FrameReference {
  protected:
    FrameReference()          = default;
    virtual ~FrameReference() = default;

    virtual CartesianVector<Distance, EarthCenteredInertial> get_position(const Date& date) const = 0;
    virtual CartesianVector<Velocity, EarthCenteredInertial> get_velocity(const Date& date) const;
    virtual CartesianVector<Acceleration, EarthCenteredInertial> get_acceleration(const Date& date) const;
};

} // namespace astro
} // namespace waveguide