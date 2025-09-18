#pragma once

#include <complex>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/state/CartesianVector.hpp>

namespace astrea {
namespace astro {

class QuaternionPartials;

using QuaternionVector     = CartesianVector<Unitless, EarthCenteredInertial>;
using QuaternionVectorRate = CartesianVector<UnitlessPerTime, EarthCenteredInertial>;

class Quaternion {

    friend std::ostream& operator<<(std::ostream&, Quaternion const&);

  public:
    Quaternion()  = default;
    ~Quaternion() = default;

    Quaternion(const Unitless& q0, const Unitless& q1, const Unitless& q2, const Unitless& q3);

    Quaternion(const Unitless& q0, const CartesianVector<Unitless, EarthCenteredInertial>& qVec);

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

    bool operator==(const Quaternion& other) const;

    Quaternion operator+(const Quaternion& other) const;

    Quaternion& operator+=(const Quaternion& other);

    Quaternion operator-(const Quaternion& other) const;

    Quaternion& operator-=(const Quaternion& other);

    Quaternion operator*(const Unitless& multiplier) const;

    Quaternion& operator*=(const Unitless& multiplier);

    QuaternionPartials operator/(const Time& time) const;

    std::vector<Unitless> to_vector() const;

    Quaternion operator/(const Unitless& divisor) const;

    Quaternion& operator/=(const Unitless& divisor);

    Quaternion
        interpolate(const Time& thisTime, const Time& otherTime, const Quaternion& other, const AstrodynamicsSystem& sys, const Time& targetTime) const;

  private:
    Unitless _q0;           //!< Quaternion scalar component
    QuaternionVector _qVec; //!< Quaternion vector component
};

class QuaternionPartials {
  public:
    QuaternionPartials() = default;
    QuaternionPartials(const UnitlessPerTime& q0Dot, CartesianVector<UnitlessPerTime, EarthCenteredInertial> qVecDot);
    ~QuaternionPartials() = default;

    Quaternion operator*(const Time& time) const;

  private:
    UnitlessPerTime _q0Dot;                                           //!< Quaternion scalar component
    CartesianVector<UnitlessPerTime, EarthCenteredInertial> _qVecDot; //!< Quaternion vector component
};

} // namespace astro
} // namespace astrea