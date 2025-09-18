#include <astro/state/angular_elements/Quaternion.hpp>

#include <math/interpolation.hpp>

namespace astrea {
namespace astro {

Quaternion::Quaternion(const Unitless& q0, const Unitless& q1, const Unitless& q2, const Unitless& q3) :
    _q0(q0),
    _qVec(q1, q2, q3)
{
}

Quaternion::Quaternion(const Unitless& q0, const CartesianVector<Unitless, EarthCenteredInertial>& qVec) :
    _q0(q0),
    _qVec(qVec)
{
}

Unitless& Quaternion::get_q0() { return _q0; }

const Unitless& Quaternion::get_q0() const { return _q0; }

Unitless& Quaternion::get_q1() { return _qVec.get_x(); }

const Unitless& Quaternion::get_q1() const { return _qVec.get_x(); }

Unitless& Quaternion::get_q2() { return _qVec.get_y(); }

const Unitless& Quaternion::get_q2() const { return _qVec.get_y(); }

Unitless& Quaternion::get_q3() { return _qVec.get_z(); }

const Unitless& Quaternion::get_q3() const { return _qVec.get_z(); }

Unitless Quaternion::norm() const { return sqrt(_q0 * _q0 + _qVec.norm() * _qVec.norm()); }

Quaternion Quaternion::unit() const
{
    const Unitless n = norm();
    return Quaternion(_q0 / n, _qVec.get_x() / n, _qVec.get_y() / n, _qVec.get_z() / n);
}

bool Quaternion::operator==(const Quaternion& other) const { return (_q0 == other._q0) && (_qVec == other._qVec); }

Quaternion Quaternion::operator+(const Quaternion& other) const
{
    return Quaternion(_q0 + other._q0, _qVec + other._qVec);
}

Quaternion& Quaternion::operator+=(const Quaternion& other)
{
    _q0 += other._q0;
    _qVec += other._qVec;
    return *this;
}

Quaternion Quaternion::operator-(const Quaternion& other) const
{
    return Quaternion(_q0 - other._q0, _qVec - other._qVec);
}

Quaternion& Quaternion::operator-=(const Quaternion& other)
{
    _q0 -= other._q0;
    _qVec -= other._qVec;
    return *this;
}

Quaternion Quaternion::operator*(const Unitless& multiplier) const
{
    return Quaternion(_q0 * multiplier, _qVec * multiplier);
}

Quaternion& Quaternion::operator*=(const Unitless& multiplier)
{
    _q0 *= multiplier;
    _qVec *= multiplier;
    return *this;
}

QuaternionPartials Quaternion::operator/(const Time& time) const
{
    return QuaternionPartials(_q0 / time, _qVec / time);
}

std::vector<Unitless> Quaternion::to_vector() const { return { _q0, _qVec.get_x(), _qVec.get_y(), _qVec.get_z() }; }

Quaternion Quaternion::operator/(const Unitless& divisor) const { return Quaternion(_q0 / divisor, _qVec / divisor); }

Quaternion& Quaternion::operator/=(const Unitless& divisor)
{
    _q0 /= divisor;
    _qVec /= divisor;
    return *this;
}

Quaternion
    Quaternion::interpolate(const Time& thisTime, const Time& otherTime, const Quaternion& other, const AstrodynamicsSystem& sys, const Time& targetTime) const
{
    const std::vector<Time> times = { thisTime, otherTime };
    const Unitless interpQ0       = math::interpolate<Time, Unitless>(times, { _q0, other.get_q0() }, targetTime);
    const Unitless interpQ1 = math::interpolate<Time, Unitless>(times, { _qVec.get_x(), other.get_q1() }, targetTime);
    const Unitless interpQ2 = math::interpolate<Time, Unitless>(times, { _qVec.get_y(), other.get_q2() }, targetTime);
    const Unitless interpQ3 = math::interpolate<Time, Unitless>(times, { _qVec.get_z(), other.get_q3() }, targetTime);

    return Quaternion(interpQ0, interpQ1, interpQ2, interpQ3);
}


std::ostream& operator<<(std::ostream& os, Quaternion const& quaternion)
{
    os << "[";
    os << quaternion.get_q0() << ", ";
    os << quaternion.get_q1() << ", ";
    os << quaternion.get_q2() << ", ";
    os << quaternion.get_q3() << ", ";
    os << "] (Quaternion)";
    return os;
}


QuaternionPartials::QuaternionPartials(const UnitlessPerTime& q0Dot, CartesianVector<UnitlessPerTime, EarthCenteredInertial> qVecDot) :
    _q0Dot(q0Dot),
    _qVecDot(qVecDot)
{
}

Quaternion QuaternionPartials::operator*(const Time& time) const { return Quaternion(_q0Dot * time, _qVecDot * time); }

} // namespace astro
} // namespace astrea