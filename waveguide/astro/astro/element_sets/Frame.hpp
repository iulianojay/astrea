#pragma once

#include <string>

#include <units/typedefs.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/types/typedefs.hpp>

namespace waveguide {
namespace astro {

enum class FRAME : EnumType {
    ECI, // Earth-Centered Inertial
    ECEF // Earth-Centered Earth-Fixed
};

struct FramePairHash {
    std::size_t operator()(const std::pair<FRAME, FRAME>& pair) const
    {
        return static_cast<std::size_t>(pair.first) * static_cast<std::size_t>(FRAME::ECEF) + static_cast<std::size_t>(pair.second);
    }
};

class FrameReference {
  protected:
    FrameReference()          = default;
    virtual ~FrameReference() = default;

    virtual CartesianVector<Distance> get_position(const Date& date) const = 0;

    virtual CartesianVector<Velocity> get_velocity(const Date& date) const;

    virtual CartesianVector<Acceleration> get_acceleration(const Date& date) const;
};

template <class FrameReference_T>
class Frame {

    static_assert(std::is_base_of<FrameReference_T, FrameReference>::value);

  protected:
    Frame() = default;
    Frame(const FrameReference_T& origin) :
        name(origin.get_name()),
        origin(&origin)
    {
    }
    virtual ~Frame() = default;

  protected:
    std::string name;
    FrameReference_T* origin;
};


} // namespace astro
} // namespace waveguide