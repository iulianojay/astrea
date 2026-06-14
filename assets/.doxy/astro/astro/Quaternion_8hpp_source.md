

# File Quaternion.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md) **>** [**attitude**](dir_d187d1a6cf435d7a067093cc1f3d7926.md) **>** [**Quaternion.hpp**](Quaternion_8hpp.md)

[Go to the documentation of this file](Quaternion_8hpp.md)


```C++

#pragma once

#include <stdexcept>

#include <mp-units/core.h>
#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/frames/framework/DirectionCosineMatrix.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/state/attitude/EulerAngles.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
class Quaternion {

    friend class Attitude;
    friend std::ostream& operator<<(std::ostream& os, const Quaternion& quaternion)
    {
        os << "[s: " << quaternion._s << ", u: " << quaternion._u << "]";
        return os;
    }

  public:
    static constexpr auto in_frame  = _in_frame_;
    static constexpr auto out_frame = _out_frame_;

    Quaternion() :
        _s(1.0 * mp_units::one),
        _u(CartesianVector<Unitless, in_frame>())
    {
        normalize();
    }

    Quaternion(const CartesianVector<Unitless, in_frame>& vec) :
        _s(0.0 * mp_units::one),
        _u(vec)
    {
        normalize();
    }

    Quaternion(const Unitless& s, const CartesianVector<Unitless, in_frame>& vec) :
        _s(s),
        _u(vec)
    {
        normalize();
    }

    Quaternion(const Unitless& s, const Unitless& x, const Unitless& y, const Unitless& z) :
        _s(s),
        _u(x, y, z)
    {
        normalize();
    }

    Quaternion(const Quaternion& other) = default;

    Quaternion(Quaternion&& other) = default;

    Quaternion& operator=(const Quaternion& other) = default;

    Quaternion& operator=(Quaternion&& other) = default;

    bool operator==(const Quaternion& other) const { return _s == other._s && _u == other._u; }

    Quaternion(const DirectionCosineMatrix<in_frame, out_frame>& dcm)
    {
        // Convert the DCM to a quaternion using Shepperd's numerically stable algorithm
        const auto trace = dcm.trace();
        const auto& xx   = dcm[0, 0];
        const auto& xy   = dcm[0, 1];
        const auto& xz   = dcm[0, 2];
        const auto& yy   = dcm[1, 1];
        const auto& yx   = dcm[1, 0];
        const auto& yz   = dcm[1, 2];
        const auto& zx   = dcm[2, 0];
        const auto& zy   = dcm[2, 1];
        const auto& zz   = dcm[2, 2];

        // Case 1: Trace > 0 - Most numerically stable when rotation angle < 120°
        // Ref: Shepperd (1978), Eq. 15
        if (trace > 0) {
            const auto r = sqrt(trace + 1.0) * 2.0;
            _s           = 0.25 * r;
            _u[0]        = (zy - yz) / r;
            _u[1]        = (xz - zx) / r;
            _u[2]        = (yx - xy) / r;
        }
        // Case 2: xx is the largest diagonal element
        // Ref: Shepperd (1978), Eq. 16 - Stable when rotation is primarily about x-axis
        else if ((xx > yy) && (xx > zz)) {
            const auto r = sqrt(1.0 + xx - yy - zz) * 2.0;
            _s           = (zy - yz) / r;
            _u[0]        = 0.25 * r;
            _u[1]        = (yx + xy) / r;
            _u[2]        = (zx + xz) / r;
        }
        // Case 3: yy is the largest diagonal element
        // Ref: Shepperd (1978), Eq. 17 - Stable when rotation is primarily about y-axis
        else if (yy > zz) {
            const auto r = sqrt(1.0 + yy - xx - zz) * 2.0;
            _s           = (xz - zx) / r;
            _u[0]        = (yx + xy) / r;
            _u[1]        = 0.25 * r;
            _u[2]        = (zy + yz) / r;
        }
        // Case 4: zz is the largest diagonal element
        // Ref: Shepperd (1978), Eq. 18 - Stable when rotation is primarily about z-axis
        else {
            const auto r = sqrt(1.0 + zz - xx - yy) * 2.0;
            _s           = (yx - xy) / r;
            _u[0]        = (zx + xz) / r;
            _u[1]        = (zy + yz) / r;
            _u[2]        = 0.25 * r;
        }
        normalize();
    }

    template <RotationSequence sequence, RotationType rotation_type>
    Quaternion(const EulerAngles<sequence, rotation_type, in_frame, out_frame>& angleSequence) :
        Quaternion(angleSequence.to_dcm())
    {
    }

    Quaternion(const Angle& angle, const CartesianVector<Unitless, in_frame>& axis) :
        _s(mp_units::angular::cos(angle / 2.0)),
        _u(axis * mp_units::angular::sin(angle / 2.0))
    {
    }

    DirectionCosineMatrix<in_frame, out_frame> to_dcm() const
    {
        const auto& x = _u.get_x();
        const auto& y = _u.get_y();
        const auto& z = _u.get_z();
        const auto& s = _s;

        return DirectionCosineMatrix<in_frame, out_frame>{
            { std::array<Unitless, 3>{ s * s + x * x - y * y - z * z, 2.0 * (x * y - s * z), 2.0 * (x * z + s * y) },
              std::array<Unitless, 3>{ 2.0 * (x * y + s * z), s * s - x * x + y * y - z * z, 2.0 * (y * z - s * x) },
              std::array<Unitless, 3>{ 2.0 * (x * z - s * y), 2.0 * (y * z + s * x), s * s - x * x - y * y + z * z } }
        };
    }

    template <RotationSequence sequence, RotationType rotation_type>
    EulerAngles<sequence, rotation_type, in_frame, out_frame> to_euler_angles() const
    {
        using namespace mp_units;
        using namespace mp_units::angular;
        using mp_units::angular::unit_symbols::rad;

        const bool isProper = is_proper_euler_sequence(sequence);
        auto [i, j, k]      = get_sequence_numbers(sequence);

        if (isProper) { k = 6 - i - j; }

        const Unitless eps = (i - j) * (j - k) * (k - i) / 2 * one;

        const Unitless a = isProper ? _s : _s - _u[j - 1];
        const Unitless b = isProper ? _u[i - 1] : _u[i - 1] + _u[k - 1] * eps;
        const Unitless c = isProper ? _u[j - 1] : _u[j - 1] + _s;
        const Unitless d = isProper ? _u[k - 1] * eps : _u[k - 1] * eps - _u[i - 1];

        const Unitless aPlusBSquared = a * a + b * b;
        const Unitless cPlusDSquared = c * c + d * d;
        Angle theta2                 = acos(2.0 * aPlusBSquared / (aPlusBSquared + cPlusDSquared) - 1.0 * one);
        const Angle thetaPlus        = atan2(b, a);
        const Angle thetaMinus       = atan2(d, c);

        Angle theta1, theta3;
        static constexpr Angle piOver2 = std::numbers::pi / 2.0 * rad;
        if (is_eq_zero(theta2)) {
            theta1 = 0.0 * rad;
            theta3 = 2 * thetaPlus - theta1;
        }
        else if (theta2 == piOver2) {
            theta1 = 0.0 * rad;
            theta3 = 2 * thetaMinus + theta1;
        }
        else {
            theta1 = thetaPlus - thetaMinus;
            theta3 = thetaPlus + thetaMinus;
        }

        if (!isProper) {
            theta3 = eps * theta3;
            theta2 = theta2 - piOver2;
        }
        return { theta1, theta2, theta3 };
    }

    Quaternion<in_frame, out_frame> operator+(const Quaternion<in_frame, out_frame>& other) const
    {
        return { _s + other._s, _u + other._u };
    }

    Quaternion<in_frame, out_frame>& operator+=(const Quaternion<in_frame, out_frame>& other)
    {
        *this = *this + other;
        normalize();
        return *this;
    }

    Quaternion<in_frame, out_frame> operator-() const { return { -_s, -_u }; }

    Quaternion<in_frame, out_frame> operator-(const Quaternion<in_frame, out_frame>& other) const
    {
        return *this + (-other);
    }

    Quaternion<in_frame, out_frame>& operator-=(const Quaternion<in_frame, out_frame>& other)
    {
        *this = *this - other;
        normalize();
        return *this;
    }

    Quaternion<in_frame, out_frame> operator*(const Unitless& scalar) const { return *this; }

    Quaternion<in_frame, out_frame>& operator*=(const Unitless& scalar) { return *this; }

    Quaternion<in_frame, out_frame> operator/(const Unitless& scalar) const { return *this; }

    Quaternion<in_frame, out_frame>& operator/=(const Unitless& scalar) { return *this; }

    template <IsFrame auto out_frameu_>
    Quaternion<in_frame, out_frameu_> operator*(const Quaternion<out_frame, out_frameu_>& other) const
    {
        const auto& x1 = _u.get_x();
        const auto& y1 = _u.get_y();
        const auto& z1 = _u.get_z();
        const auto& x2 = other.get_vector_part().get_x();
        const auto& y2 = other.get_vector_part().get_y();
        const auto& z2 = other.get_vector_part().get_z();
        const auto& s1 = _s;
        const auto& s2 = other.get_scalar_part();

        return { s1 * s2 - (x1 * x2 + y1 * y2 + z1 * z2),
                 s1 * x2 + x1 * s2 + y1 * z2 - z1 * y2,
                 s1 * y2 - x1 * z2 + y1 * s2 + z1 * x2,
                 s1 * z2 + x1 * y2 - y1 * x2 + z1 * s2 };
    }

    QuaternionPartial<in_frame, out_frame> operator/(const Time& dt) const
    {
        return QuaternionPartial<in_frame, out_frame>{ _s / dt, _u / dt };
    }

    template <typename Value_T>
    CartesianVector<Value_T, out_frame> rotate_vector(const CartesianVector<Value_T, in_frame>& vec) const
    {
        // Rotate the vector using the quaternion: v' = q * v * q^-1
        // results in a quaternion with vector part 2(u ⋅ v)u + (s2 - u ⋅ u)v + 2s(u * v)
        // This forces a frame conversion because there is no coherent way to keep the strong typing through the
        // intermediate operations and still result in a meaningful rotation. This means we can't have a nice interface
        // where users rotate by calling q * v * q.conjugate() but it's fine for now.
        return (2.0 * _u.dot(vec) * _u + (_s * _s - _u.dot(_u)) * vec + 2.0 * _s * _u.cross(vec)).template force_frame_conversion<out_frame>();
    }

    Quaternion<out_frame, in_frame> conjugate() const
    {
        return { _s, -_u.template force_frame_conversion<out_frame>() };
    }

    Quaternion<out_frame, in_frame> inverse() const
    {
        const Unitless scale = 1.0 / norm_squared();
        return { _s * scale, -_u.template force_frame_conversion<out_frame>() * scale };
    }

    Unitless norm() const { return mp_units::sqrt(norm_squared()); }

    Unitless norm_squared() const { return _s * _s + _u.dot(_u); }

    void normalize()
    {
        using namespace mp_units;

        const Unitless nSq = norm_squared();
        if (is_eq_zero(nSq)) { throw std::runtime_error("Cannot normalize a quaternion with zero norm."); }
        else if (isnan(nSq) || isinf(nSq)) {
            throw std::runtime_error("Cannot normalize a quaternion with non-finite norm.");
        }

        // https://stackoverflow.com/questions/11667783/quaternion-and-normalization
        if (abs(1.0 * one - nSq) < 2.107342e-08 * one) { _normalize(2.0 * one / (1.0 * one + nSq)); }
        else {
            _normalize(1.0 * one / sqrt(nSq));
        }
    }

    const Unitless& get_scalar_part() const { return _s; }

    const CartesianVector<Unitless, in_frame>& get_vector_part() const { return _u; }

    std::vector<Unitless> force_to_vector() const { return { _s, _u[0], _u[1], _u[2] }; }

    Unitless dot(const Quaternion<in_frame, out_frame>& other) const { return _s * other._s + _u.dot(other._u); }

    Quaternion<in_frame, out_frame>
        interpolate(const Time& thisTime, const Time& otherTime, const Quaternion<in_frame, out_frame>& other, const Time& targetTime) const
    {
        using namespace mp_units;
        using namespace mp_units::angular;
        using mp_units::angular::unit_symbols::rad;

        // Calculate angle between them.
        const Unitless cosHalfTheta = this->dot(other);

        // Return one if quaternions are the same
        if (abs(cosHalfTheta) >= 1.0 * one) { return *this; }

        // Catch inversions
        const auto qOther = (cosHalfTheta < 0.0 * one) ? -other : other;

        // Calculate temporary values.
        const Angle halfTheta       = acos(cosHalfTheta);
        const Unitless sinHalfTheta = sqrt(1.0 * one - cosHalfTheta * cosHalfTheta);

        // if theta = 180 degrees { result is not fully defined
        // we could rotate around any axis normal to either
        if (abs(sinHalfTheta) < 1.0e-3 * one) {
            // Do the math manually to avoid normalization until construction
            return { 0.5 * (_s + qOther._s),
                     0.5 * (_u[0] + qOther._u[0]),
                     0.5 * (_u[1] + qOther._u[1]),
                     0.5 * (_u[2] + qOther._u[2]) };
        }

        // calculate quaternion
        const Unitless tRatio = (targetTime - thisTime) / (otherTime - thisTime);
        const Unitless ratioA = sin((1.0 * one - tRatio) * halfTheta) / sinHalfTheta;
        const Unitless ratioB = sin(tRatio * halfTheta) / sinHalfTheta;

        return { _s * ratioA + qOther._s * ratioB,
                 _u[0] * ratioA + qOther._u[0] * ratioB,
                 _u[1] * ratioA + qOther._u[1] * ratioB,
                 _u[2] * ratioA + qOther._u[2] * ratioB };
    }

  private:
    Unitless _s;                            
    CartesianVector<Unitless, in_frame> _u; 

    void _normalize(const Unitless& scale)
    {
        _s *= scale;
        _u[0] *= scale;
        _u[1] *= scale;
        _u[2] *= scale;
    }

    static Quaternion<in_frame, out_frame> from_vector(const std::vector<Unitless>& vec)
    {
        if (vec.size() != 4) {
            throw std::invalid_argument("Input vector must have exactly 4 components to convert to a Quaternion.");
        }
        return { vec[0], vec[1], vec[2], vec[3] };
    }
};

template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
class QuaternionPartial {

    friend class AttitudePartial;

  public:
    static constexpr auto in_frame  = _in_frame_;
    static constexpr auto out_frame = _out_frame_;

    QuaternionPartial() = default;

    QuaternionPartial(const UnitlessPerTime& sDot, const CartesianVector<UnitlessPerTime, in_frame>& uDot) :
        _sDot(sDot),
        _uDot(uDot)
    {
    }

    const UnitlessPerTime& get_scalar_part() const { return _sDot; }

    const CartesianVector<UnitlessPerTime, in_frame>& get_vector_part() const { return _uDot; }

    Quaternion<in_frame, out_frame> operator*(const Time& dt) const
    {
        return Quaternion<in_frame, out_frame>{ _sDot * dt, _uDot * dt };
    }

    std::vector<Unitless> force_to_vector() const
    {
        return { _sDot / _sDot.unit, _uDot[0] / _uDot[0].unit, _uDot[1] / _uDot[1].unit, _uDot[2] / _uDot[2].unit };
    }

  private:
    UnitlessPerTime _sDot;                            
    CartesianVector<UnitlessPerTime, in_frame> _uDot; 
};

template <IsFrame auto in_frame, IsFrame auto out_frame>
std::ostream& operator<<(std::ostream& os, const Quaternion<in_frame, out_frame>& quaternion)
{
    const auto& s = quaternion.get_scalar_part();
    const auto& u = quaternion.get_vector_part();
    os << "[" << s << " | " << u[0] << " , " << u[1] << " , " << u[2] << "]";
    return os;
}

template <IsFrame auto in_frame, IsFrame auto out_frame>
std::ostream& operator<<(std::ostream& os, const QuaternionPartial<in_frame, out_frame>& quaternion)
{
    const auto& sDot = quaternion.get_scalar_part();
    const auto& uDot = quaternion.get_vector_part();
    os << "[" << sDot << " | " << uDot[0] << " , " << uDot[1] << " , " << uDot[2] << "]";
    return os;
}

} // namespace astro
} // namespace astrea

// C++ circular-include bullshit. Can we please just use modules?
#include <astro/state/attitude/EulerAngles.ipp>
```


