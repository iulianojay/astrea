#pragma once

#ifndef SWIG
  #include <string>
#endif

#include "astro/types/typedefs.hpp"
#include "fwd/systems/GravitationalBody.fwd.hpp"
#include "fwd/platforms/space/Spacecraft.fwd.hpp"


template <class T>
class Frame {

  static_assert(std::is_same<T, GravitationalBody>::value || std::is_base_of<T, GravitationalBody>::value || std::is_same<T, Spacecraft>::value || std::is_same<T, Frame>::value,
                "Frames must be defined in reference to one of the following types: [GravitationalBody, Barycenter, Spacecraft, Frame].");

public:
    Frame() {};
    ~Frame() {};

    std::string name;

private:
    basis_array x, y, z;
    T origin;
};


template <class T>
class InertialFrame : public Frame<T> {

  static_assert(std::is_same<T, GravitationalBody>::value || std::is_base_of<T, GravitationalBody>::value || std::is_same<T, InertialFrame>::value,
                "Inertial frames must be defined in reference to one of the following types: [GravitationalBody, Barycenter, InertialFrame].");

};


template <class T>
class RotatingFrame : public Frame<T> {

  static_assert(std::is_same<T, GravitationalBody>::value || std::is_base_of<T, GravitationalBody>::value,
                "Inertial frames must be defined in reference to one of the following types: [GravitationalBody, Barycenter, InertialFrame].");

};


template <class T>
class BodyFixedFrame : public Frame<T> {

  static_assert(std::is_same<T, GravitationalBody>::value || std::is_base_of<T, GravitationalBody>::value || std::is_same<T, InertialFrame<T>>::value,
                "Body-fixed frames must be defined in reference to one of the following types: [GravitationalBody, Spacecraft].");

};


template <class T>
class FixedOffsetFrame : public Frame<T> {

  static_assert(std::is_same<T, Frame<T>>::value || std::is_base_of<T, Frame<T>>::value,
                "Fixed-offset frames must be defined in reference to one of the following types: [Frame].");

};


template <class T>
class DynamicFrame : public Frame<T> {

};