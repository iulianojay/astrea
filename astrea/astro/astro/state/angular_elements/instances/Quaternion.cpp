#include <astro/state/angular_elements/instances/Quaternion.hpp>

namespace astrea {
namespace astro {

Quaternion::Quaternion(const Unitless& q0, const Unitless& q1, const Unitless& q2, const Unitless& q3) :
    _q0(q0),
    _q1(q1),
    _q2(q2),
    _q3(q3)
{
}

Unitless& Quaternion::get_q0() { return _q0; }

const Unitless& Quaternion::get_q0() const { return _q0; }

Unitless& Quaternion::get_q1() { return _q1; }

const Unitless& Quaternion::get_q1() const { return _q1; }

Unitless& Quaternion::get_q2() { return _q2; }

const Unitless& Quaternion::get_q2() const { return _q2; }

Unitless& Quaternion::get_q3() { return _q3; }

const Unitless& Quaternion::get_q3() const { return _q3; }

Unitless Quaternion::norm() const { return sqrt(_q0 * _q0 + _q1 * _q1 + _q2 * _q2 + _q3 * _q3); }

Quaternion Quaternion::unit() const
{
    const Unitless n = norm();
    return Quaternion(_q0 / n, _q1 / n, _q2 / n, _q3 / n);
}

} // namespace astro
} // namespace astrea