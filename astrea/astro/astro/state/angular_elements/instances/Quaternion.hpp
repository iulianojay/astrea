#pragma once

#include <units/units.hpp>

namespace astrea {
namespace astro {

class Quaternion {
  public:
    Quaternion()  = default;
    ~Quaternion() = default;

    Quaternion(const Unitless& q0, const Unitless& q1, const Unitless& q2, const Unitless& q3);

    Unitless& get_q0();
    const Unitless& get_q0() const;

    Unitless& get_q1();
    const Unitless& get_q1() const;

    Unitless& get_q2();
    const Unitless& get_q2() const;

    Unitless& get_q3();
    const Unitless& get_q3() const;

    Unitless norm() const;
    Quaternion unit() const;

  private:
    Unitless _q0; //!< Quaternion scalar component
    Unitless _q1; //!< Quaternion first vector component
    Unitless _q2; //!< Quaternion second vector component
    Unitless _q3; //!< Quaternion third vector component
};

class QuaternionPartials {
  public:
    QuaternionPartials()  = default;
    ~QuaternionPartials() = default;

  private:
    UnitlessPerTime _qDot0; //!< Quaternion partial of the scalar component
    UnitlessPerTime _qDot1; //!< Quaternion partial of the first vector component
    UnitlessPerTime _qDot2; //!< Quaternion partial of the second vector component
    UnitlessPerTime _qDot3; //!< Quaternion partial of the third vector component
};

} // namespace astro
} // namespace astrea