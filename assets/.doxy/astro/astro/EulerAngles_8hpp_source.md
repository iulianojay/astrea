

# File EulerAngles.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md) **>** [**attitude**](dir_d187d1a6cf435d7a067093cc1f3d7926.md) **>** [**EulerAngles.hpp**](EulerAngles_8hpp.md)

[Go to the documentation of this file](EulerAngles_8hpp.md)


```C++

#pragma once

#include <math/interpolation.hpp>
#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/frames/framework/DirectionCosineMatrix.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/types/enums.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {
namespace astro {

constexpr RotationSequence get_reverse_sequence(RotationSequence sequence)
{
    switch (sequence) {
        case RotationSequence::XYZ: return RotationSequence::ZYX;
        case RotationSequence::YZX: return RotationSequence::XZY;
        case RotationSequence::ZXY: return RotationSequence::YXZ;
        case RotationSequence::XZY: return RotationSequence::YZX;
        case RotationSequence::ZYX: return RotationSequence::XYZ;
        case RotationSequence::YXZ: return RotationSequence::ZXY;
        default:
            // For Euler sequences, the reverse is the same sequence with reversed angles, so we can just return the same sequence type
            return sequence;
    }
}

constexpr bool is_proper_euler_sequence(RotationSequence sequence)
{
    switch (sequence) {
        case RotationSequence::ZXZ:
        case RotationSequence::XYX:
        case RotationSequence::YZY:
        case RotationSequence::ZYZ:
        case RotationSequence::XZX:
        case RotationSequence::YXY: return true;
        default: return false;
    }
}

constexpr std::array<int, 3> get_sequence_numbers(RotationSequence sequence)
{
    switch (sequence) {
        case RotationSequence::ZXZ: return std::array{ 3, 1, 3 };
        case RotationSequence::XZX: return std::array{ 1, 3, 1 };
        case RotationSequence::YXY: return std::array{ 2, 1, 2 };
        case RotationSequence::XYX: return std::array{ 1, 2, 1 };
        case RotationSequence::YZY: return std::array{ 2, 3, 2 };
        case RotationSequence::ZYZ: return std::array{ 3, 2, 3 };
        case RotationSequence::XYZ: return std::array{ 1, 2, 3 };
        case RotationSequence::XZY: return std::array{ 1, 3, 2 };
        case RotationSequence::YZX: return std::array{ 2, 3, 1 };
        case RotationSequence::YXZ: return std::array{ 2, 1, 3 };
        case RotationSequence::ZXY: return std::array{ 3, 1, 2 };
        case RotationSequence::ZYX: return std::array{ 3, 2, 1 };
    }
}

template <RotationSequence sequence_t, RotationType rotation_t, IsFrame auto _in_frame_, IsFrame auto _out_frame_, RotationSequence sequence_u, RotationType rotation_u, IsFrame auto _in_frame_u_, IsFrame auto _out_frame_u_>
concept IsSameEulerAngles =
    (sequence_t == sequence_u) && // Must both be the same specific sequence (e.g., ZXZ)
    (rotation_t == rotation_u) && // Must both be the same rotation type (intrinsic or extrinsic)
    std::is_same_v<decltype(_in_frame_), decltype(_in_frame_u_)> && // Must have the same input frame
    std::is_same_v<decltype(_out_frame_), decltype(_out_frame_u_)>; // Must have the same output frame

template <RotationSequence sequence_t, RotationType rotation_t, IsFrame auto _in_frame_, IsFrame auto _out_frame_, RotationSequence sequence_u, RotationType rotation_u, IsFrame auto _in_frame_u_, IsFrame auto _out_frame_u_>
concept IsEquivalentEulerAngles =
    (get_reverse_sequence(sequence_t) == sequence_u) && // Must be the reverse sequence (e.g., ZXZ vs ZXZ with reversed angles)
    (rotation_t != rotation_u) &&                       // Must be opposite rotation types (intrinsic vs extrinsic)
    std::is_same_v<decltype(_in_frame_), decltype(_in_frame_u_)> && // Must have the same input frame
    std::is_same_v<decltype(_out_frame_), decltype(_out_frame_u_)>; // Must have the same output frame

template <RotationSequence sequence_t, RotationType rotation_t, IsFrame auto _in_frame_, IsFrame auto _out_frame_, RotationSequence sequence_u, RotationType rotation_u, IsFrame auto _in_frame_u_, IsFrame auto _out_frame_u_>
concept IsCompatibleEulerAngles =
    IsSameEulerAngles<sequence_t, rotation_t, _in_frame_, _out_frame_, sequence_u, rotation_u, _in_frame_u_, _out_frame_u_> ||
    IsEquivalentEulerAngles<sequence_t, rotation_t, _in_frame_, _out_frame_, sequence_u, rotation_u, _in_frame_u_, _out_frame_u_>;

template <RotationSequence sequence, RotationType rotation_type, IsFrame auto _in_frame_, IsFrame auto _out_frame_>
class EulerAngles {

    friend class Attitude;
    friend std::ostream& operator<<(std::ostream& os, const EulerAngles& euler)
    {
        os << euler._angles;
        return os;
    }

  public:
    static constexpr auto in_frame  = _in_frame_;
    static constexpr auto out_frame = _out_frame_;

    EulerAngles() = default;

    EulerAngles(const Angle& angle1, const Angle& angle2, const Angle& angle3) :
        _angles(angle1, angle2, angle3)
    {
        wrap_angles();
    }

    EulerAngles(const CartesianVector<Angle, _in_frame_>& angles) :
        _angles(angles)
    {
        wrap_angles();
    }

    explicit EulerAngles(const EulerAngles& other)   = default;
    explicit EulerAngles(EulerAngles&& other)        = default;
    EulerAngles& operator=(const EulerAngles& other) = default;
    EulerAngles& operator=(EulerAngles&& other)      = default;

    template <RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
        requires(IsEquivalentEulerAngles<sequence, rotation_type, _in_frame_, _out_frame_, sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>)
    EulerAngles(const EulerAngles<sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>& other) :
        _angles(other._angles.reverse())
    {
    }

    template <RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
        requires(IsEquivalentEulerAngles<sequence, rotation_type, _in_frame_, _out_frame_, sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>)
    EulerAngles(EulerAngles<sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>&& other) :
        _angles(other._angles.reverse())
    {
    }

    template <RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
        requires(IsEquivalentEulerAngles<sequence, rotation_type, _in_frame_, _out_frame_, sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>)
    EulerAngles& operator=(const EulerAngles<sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>& other)
    {
        _angles = other._angles.reverse();
        return *this;
    }

    template <RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
        requires(IsEquivalentEulerAngles<sequence, rotation_type, _in_frame_, _out_frame_, sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>)
    EulerAngles& operator=(EulerAngles<sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>&& other)
    {
        _angles = other._angles.reverse();
        return *this;
    }

    template <RotationSequence sequence_u, RotationType rotation_type_u>
        requires(!IsCompatibleEulerAngles<sequence, rotation_type, _in_frame_, _out_frame_, sequence_u, rotation_type_u, _in_frame_, _out_frame_>)
    EulerAngles(const EulerAngles<sequence_u, rotation_type_u, _in_frame_, _out_frame_>& other);

    EulerAngles<get_reverse_sequence(sequence), rotation_type, _out_frame_, _in_frame_> get_inverse_sequence() const
    {
        return { -_angles.reverse() };
    }


    Angle& operator[](std::size_t index) { return _angles[index]; }

    const Angle& operator[](std::size_t index) const { return _angles[index]; }

    CartesianVector<Angle, _in_frame_>& get_angles() { return _angles; }

    const CartesianVector<Angle, _in_frame_>& get_angles() const { return _angles; }

    DirectionCosineMatrix<_in_frame_, _out_frame_> to_dcm() const
    {
        // Intrinsic sequences are applied directly in the order they are specified (the static DCM factories
        // implement the intrinsic composition convention: R_seq0(a) * R_seq1(b) * R_seq2(c)).
        // Extrinsic sequences are equivalent to the reverse sequence applied intrinsically with the angles in
        // reverse order (e.g. extrinsic XYZ(a,b,c) == intrinsic ZYX(c,b,a)), so we dispatch to the reverse
        // sequence's factory with the angle order reversed.
        if constexpr (rotation_type == RotationType::INTRINSIC) {
            return DirectionCosineMatrix<_in_frame_, _out_frame_>::template from_euler_angles<sequence>(_angles[0], _angles[1], _angles[2]);
        }
        else {
            return DirectionCosineMatrix<_in_frame_, _out_frame_>::template from_euler_angles<get_reverse_sequence(sequence)>(
                _angles[2], _angles[1], _angles[0]
            );
        }
    }

    template <RotationType rotation_u>
        requires(rotation_type != rotation_u)
    EulerAngles<get_reverse_sequence(sequence), rotation_u, _in_frame_, _out_frame_> to_rotation_type() const
    {
        return { _angles.reverse() };
    }

    template <RotationType rotation_u>
        requires(rotation_type == rotation_u)
    EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_> to_rotation_type() const
    {
        return { _angles };
    }

    // Explicitly deleted copy/move assignment/constructor to prevent implicit frame switches, rotation type conversions, and sequence conversions.
    template <RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
        requires(!IsCompatibleEulerAngles<sequence, rotation_type, _in_frame_, _out_frame_, sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>)
    EulerAngles(const EulerAngles<sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>& other) = delete;

    template <RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
        requires(!IsCompatibleEulerAngles<sequence, rotation_type, _in_frame_, _out_frame_, sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>)
    EulerAngles(EulerAngles<sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>&& other) = delete;

    template <RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
        requires(!IsCompatibleEulerAngles<sequence, rotation_type, _in_frame_, _out_frame_, sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>)
    EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>&
        operator=(const EulerAngles<sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>& other) = delete;

    template <RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
        requires(!IsCompatibleEulerAngles<sequence, rotation_type, _in_frame_, _out_frame_, sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>)
    EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>&
        operator=(EulerAngles<sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>&& other) = delete;

    bool operator==(const EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>& other) const
    {
        return _angles == other._angles;
    }

    template <RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
        requires(IsEquivalentEulerAngles<sequence, rotation_type, _in_frame_, _out_frame_, sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>)
    bool operator==(const EulerAngles<sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>& other) const
    {
        return _angles == other.get_angles().reverse();
    }

    template <RotationSequence sequence_u, RotationType rotation_type_u, auto _in_frame_u_, auto _out_frame_u_>
        requires(!IsCompatibleEulerAngles<sequence, rotation_type, _in_frame_, _out_frame_, sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>)
    bool operator==(const EulerAngles<sequence_u, rotation_type_u, _in_frame_u_, _out_frame_u_>& other) const
    {
        return false;
    }

    EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>
        operator+(const EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>& other) const
    {
        return { _angles + other._angles };
    }

    EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>&
        operator+=(const EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>& other)
    {
        _angles += other._angles;
        wrap_angles();
        return *this;
    }

    EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>
        operator-(const EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>& other) const
    {
        return { _angles - other._angles };
    }

    EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_> operator-() const { return { -_angles }; }

    EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>&
        operator-=(const EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>& other)
    {
        _angles -= other._angles;
        wrap_angles();
        return *this;
    }

    EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_> operator*(const Unitless& scalar) const
    {
        return { _angles * scalar };
    }

    EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>& operator*=(const Unitless& scalar)
    {
        _angles *= scalar;
        wrap_angles();
        return *this;
    }

    AngularVelocities<_in_frame_, _out_frame_> operator/(const Time& time) const { return { _angles / time }; }

    EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_> operator/(const Unitless& scalar) const
    {
        return { _angles / scalar };
    }

    EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>& operator/=(const Unitless& scalar)
    {
        _angles /= scalar;
        wrap_angles();
        return *this;
    }

    auto dot(const EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>& other) const
    {
        return _angles.dot(other._angles);
    }

    template <typename Value_U>
    auto dot(const CartesianVector<Value_U, _in_frame_>& other) const
    {
        return _angles.dot(other);
    }

    auto cross(const EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>& other) const
    {
        return _angles.cross(other._angles);
    }

    template <typename Value_U>
    auto cross(const CartesianVector<Value_U, _in_frame_>& other) const
    {
        return _angles.cross(other);
    }

    Angle norm() const { return _angles.norm(); }

    std::vector<double> force_to_double_vector() const
    {
        return { _angles[0].numerical_value_in(_angles[0].unit),
                 _angles[1].numerical_value_in(_angles[1].unit),
                 _angles[2].numerical_value_in(_angles[2].unit) };
    }

    EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_> interpolate(
        const Time& thisTime,
        const Time& otherTime,
        const EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>& other,
        const Time& targetTime
    ) const
    {
        static_assert(false, "Don't do this. Just use the Quaternion.");
    }

  private:
    CartesianVector<Angle, _in_frame_> _angles;

    void wrap_angles()
    {
        _angles[0] = wrap_angle(_angles[0]);       // φ - [0, 2π)
        _angles[1] = wrap_angle_to_pi(_angles[1]); // θ - [0, π)
        _angles[2] = wrap_angle(_angles[2]);       // ψ - [0, 2π)
    }

    static EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_> from_double_vector(const std::vector<double>& vec)
    {
        using mp_units::si::unit_symbols::rad;

        if (vec.size() != 3) {
            throw std::invalid_argument("Input vector must have exactly 3 components to convert to an EulerAngles.");
        }
        return { vec[0] * rad, vec[1] * rad, vec[2] * rad };
    }
};

template <RotationSequence sequence, RotationType rotation_type, IsFrame auto _in_frame_, IsFrame auto _out_frame_>
EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>
    operator*(const Unitless& scalar, const EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>& vec)
{
    return vec * scalar;
}

template <RotationSequence sequence, RotationType rotation_type, IsFrame auto _in_frame_, IsFrame auto _out_frame_>
EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>
    operator/(const Unitless& scalar, const EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>& vec)
{
    return vec / scalar;
}

template <RotationSequence sequence, RotationType rotation_type, IsFrame auto _in_frame_, IsFrame auto _out_frame_>
std::ostream& operator<<(std::ostream& os, const EulerAngles<sequence, rotation_type, _in_frame_, _out_frame_>& angleSequence)
{
    os << "[" << angleSequence[0] << " , " << angleSequence[1] << " , " << angleSequence[2] << "]";
    return os;
}

} // namespace astro
} // namespace astrea
```


