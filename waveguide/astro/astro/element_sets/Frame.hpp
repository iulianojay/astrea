#pragma once

#include <string>

#include <astro/astro.fwd.hpp>
#include <astro/types/typedefs.hpp>

namespace waveguide {
namespace astro {


class FrameReference {
  protected:
    FrameReference()          = default;
    virtual ~FrameReference() = default;

    virtual RadiusVector get_position(const Date& date) const = 0;
    virtual VelocityVector get_velocity(const Date& date) const
    {
        using mp_units::si::unit_symbols::km;
        using mp_units::si::unit_symbols::s;
        return VelocityVector{ 0.0 * km / s, 0.0 * km / s, 0.0 * km / s };
    };
    virtual AccelerationVector get_acceleration(const Date& date) const
    {
        using mp_units::si::unit_symbols::km;
        using mp_units::si::unit_symbols::s;
        return AccelerationVector{ 0.0 * km / s / s, 0.0 * km / s / s, 0.0 * km / s / s };
    };
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


class DirectionCosineMatrix {
  public:
    DirectionCosineMatrix()          = default;
    virtual ~DirectionCosineMatrix() = default;

    virtual RadiusVector operator*(const RadiusVector& vec) const             = 0;
    virtual VelocityVector operator*(const VelocityVector& vec) const         = 0;
    virtual AccelerationVector operator*(const AccelerationVector& vec) const = 0;
};
using DCM = DirectionCosineMatrix;


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


template <class T>
class FixedOffsetFrame : public Frame<T> {

  private:
    Frame<T> parentFrame;
    RadiusVector offset; // offset in parent frame coordinates
};


template <class T>
class DynamicFrame : public Frame<T> {
};

} // namespace astro
} // namespace waveguide