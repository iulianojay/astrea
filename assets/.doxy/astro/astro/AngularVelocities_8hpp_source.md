

# File AngularVelocities.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md) **>** [**attitude**](dir_d187d1a6cf435d7a067093cc1f3d7926.md) **>** [**AngularVelocities.hpp**](AngularVelocities_8hpp.md)

[Go to the documentation of this file](AngularVelocities_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions/dynamic_frames/tags.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/frames/framework/DirectionCosineMatrix.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/platforms/InertiaTensor.hpp>
#include <astro/state/attitude/EulerAngles.hpp>
#include <astro/types/enums.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {
namespace astro {

template <IsFrame auto _in_frame_, IsFrame auto _ref_frame_>
class AngularVelocities {

    friend class AttitudePartial;
    friend std::ostream& operator<<(std::ostream& os, const AngularVelocities& angularVelocities)
    {
        os << angularVelocities._angularVelocities;
        return os;
    }

  public:
    static constexpr auto in_frame  = _in_frame_;
    static constexpr auto ref_frame = _ref_frame_;

    AngularVelocities() = default;

    AngularVelocities(const AngularVelocity& angle1, const AngularVelocity& angle2, const AngularVelocity& angle3) :
        _angularVelocities(angle1, angle2, angle3)
    {
    }

    AngularVelocities(const CartesianVector<AngularVelocity, in_frame>& angles) :
        _angularVelocities(angles)
    {
    }

    explicit AngularVelocities(const AngularVelocities& other)   = default;
    explicit AngularVelocities(AngularVelocities&& other)        = default;
    AngularVelocities& operator=(const AngularVelocities& other) = default;
    AngularVelocities& operator=(AngularVelocities&& other)      = default;

    AngularVelocity& operator[](std::size_t index) { return _angularVelocities[index]; }

    const AngularVelocity& operator[](std::size_t index) const { return _angularVelocities[index]; }

    CartesianVector<AngularVelocity, in_frame>& get_angular_velocities() { return _angularVelocities; }

    const CartesianVector<AngularVelocity, in_frame>& get_angular_velocities() const { return _angularVelocities; }

    bool operator==(const AngularVelocities& other) const { return _angularVelocities == other._angularVelocities; }

    template <auto in_frame_u, auto ref_frame_u>
    bool operator==(const AngularVelocities<in_frame_u, ref_frame_u>&) const
    {
        return false;
    }

    CartesianVector<AngularVelocity, in_frame> operator+(const CartesianVector<AngularVelocity, in_frame>& other) const
    {
        return { _angularVelocities + other };
    }

    AngularVelocities operator+(const AngularVelocities& other) const
    {
        return { _angularVelocities + other._angularVelocities };
    }

    AngularVelocities& operator+=(const AngularVelocities& other)
    {
        _angularVelocities += other._angularVelocities;
        return *this;
    }

    AngularVelocities operator-() const { return { -_angularVelocities }; }

    CartesianVector<AngularVelocity, in_frame> operator-(const CartesianVector<AngularVelocity, in_frame>& other) const
    {
        return _angularVelocities - other;
    }

    AngularVelocities operator-(const AngularVelocities& other) const
    {
        return { _angularVelocities - other._angularVelocities };
    }

    AngularVelocities& operator-=(const AngularVelocities& other)
    {
        _angularVelocities -= other._angularVelocities;
        return *this;
    }

    template <typename Value_U>
    CartesianVector<decltype(AngularVelocity{} * Value_U{}), in_frame> operator*(const Value_U& scalar) const
    {
        return _angularVelocities * scalar;
    }

    template <RotationSequence sequence, RotationType rotation_type>
    EulerAngles<sequence, rotation_type, in_frame, ref_frame> operator*(const Time& time) const
    {
        return { _angularVelocities * time };
    }

    AngularVelocities operator*(const Unitless& scale) const { return { _angularVelocities * scale }; }

    AngularVelocities& operator*=(const Unitless& scale)
    {
        _angularVelocities *= scale;
        return *this;
    }

    template <typename Value_U>
    CartesianVector<decltype(AngularVelocity{} / Value_U{}), in_frame> operator/(const Value_U& scalar) const
    {
        return _angularVelocities / scalar;
    }

    AngularAccelerations<in_frame, ref_frame> operator/(const Time& time) const
    {
        return { _angularVelocities / time };
    }

    AngularVelocities operator/(const Unitless& scale) const { return { _angularVelocities / scale }; }

    AngularVelocities& operator/=(const Unitless& scale)
    {
        _angularVelocities /= scale;
        return *this;
    }

    template <typename Value_U>
    auto dot(const CartesianVector<Value_U, in_frame>& other) const
    {
        return _angularVelocities.dot(other);
    }

    auto dot(const AngularVelocities& other) const { return _angularVelocities.dot(other._angularVelocities); }

    template <typename Value_U>
    CartesianVector<decltype(AngularVelocity{} * Value_U{}), in_frame> cross(const CartesianVector<Value_U, in_frame>& other) const
    {
        return _angularVelocities.cross(other);
    }

    CartesianVector<decltype(AngularVelocity{} * AngularVelocity{}), in_frame> cross(const AngularVelocities& other) const
    {
        return _angularVelocities.cross(other._angularVelocities);
    }

    std::vector<double> force_to_double_vector() const
    {
        return { _angularVelocities[0].numerical_value_in(_angularVelocities[0].unit),
                 _angularVelocities[1].numerical_value_in(_angularVelocities[1].unit),
                 _angularVelocities[2].numerical_value_in(_angularVelocities[2].unit) };
    }

    AngularVelocities interpolate(const Time& thisTime, const Time& otherTime, const AngularVelocities& other, const Time& targetTime) const
    {
        // Linear interpolation is fine for angular rates
        const std::array<Time, 2> times = { thisTime, otherTime };
        const AngularVelocity interpPhiDot =
            math::fast_interpolate<Time, AngularVelocity>(times, { _angularVelocities[0], other._angularVelocities[0] }, targetTime);
        const AngularVelocity interpThetaDot =
            math::fast_interpolate<Time, AngularVelocity>(times, { _angularVelocities[1], other._angularVelocities[1] }, targetTime);
        const AngularVelocity interpPsiDot =
            math::fast_interpolate<Time, AngularVelocity>(times, { _angularVelocities[2], other._angularVelocities[2] }, targetTime);

        return { interpPhiDot, interpThetaDot, interpPsiDot };
    }

  private:
    CartesianVector<AngularVelocity, in_frame> _angularVelocities;

    static AngularVelocities from_double_vector(const std::vector<double>& vec)
    {
        using mp_units::si::unit_symbols::rad;
        using mp_units::si::unit_symbols::s;

        if (vec.size() != 3) {
            throw std::invalid_argument("Input vector must have exactly 3 components to convert to an AngularVelocities.");
        }
        return { vec[0] * rad / s, vec[1] * rad / s, vec[2] * rad / s };
    }
};

template <IsFrame auto in_frame, IsFrame auto ref_frame>
CartesianVector<decltype(MomentOfInertia{} * AngularVelocity{}), in_frame>
    operator*(const InertiaTensor<in_frame>& inertiaTensor, const AngularVelocities<in_frame, ref_frame>& vec)
{

    return { inertiaTensor[0, 0] * vec[0] + inertiaTensor[0, 1] * vec[1] + inertiaTensor[0, 2] * vec[2],
             inertiaTensor[1, 0] * vec[0] + inertiaTensor[1, 1] * vec[1] + inertiaTensor[1, 2] * vec[2],
             inertiaTensor[2, 0] * vec[0] + inertiaTensor[2, 1] * vec[1] + inertiaTensor[2, 2] * vec[2] };
}

template <IsFrame auto _in_frame_, IsFrame auto _ref_frame_>
class AngularAccelerations {

    friend class Attitude;

  public:
    static constexpr auto in_frame  = _in_frame_;
    static constexpr auto ref_frame = _ref_frame_;

    AngularAccelerations() = default;

    AngularAccelerations(const AngularAcceleration& accel1, const AngularAcceleration& accel2, const AngularAcceleration& accel3) :
        _angularAccels(accel1, accel2, accel3)
    {
    }

    AngularAccelerations(const CartesianVector<AngularAcceleration, in_frame>& accels) :
        _angularAccels(accels)
    {
    }

    AngularAcceleration& operator[](std::size_t index) { return _angularAccels[index]; }

    const AngularAcceleration& operator[](std::size_t index) const { return _angularAccels[index]; }

    CartesianVector<AngularAcceleration, in_frame>& get_angularAccels() { return _angularAccels; }

    const CartesianVector<AngularAcceleration, in_frame>& get_angularAccels() const { return _angularAccels; }

    AngularAccelerations<in_frame, ref_frame> operator+(const AngularAccelerations<in_frame, ref_frame>& other) const
    {
        return { _angularAccels + other._angularAccels };
    }

    AngularAccelerations<in_frame, ref_frame>& operator+=(const AngularAccelerations<in_frame, ref_frame>& other)
    {
        _angularAccels += other._angularAccels;
        return *this;
    }

    AngularAccelerations<in_frame, ref_frame> operator-(const AngularAccelerations<in_frame, ref_frame>& other) const
    {
        return { _angularAccels - other._angularAccels };
    }

    AngularAccelerations<in_frame, ref_frame>& operator-=(const AngularAccelerations<in_frame, ref_frame>& other)
    {
        _angularAccels -= other._angularAccels;
        return *this;
    }

    template <typename Value_U>
    CartesianVector<decltype(AngularAcceleration{} * Value_U{}), in_frame> operator*(const Value_U& scalar) const
    {
        return { _angularAccels * scalar };
    }

    AngularVelocities<in_frame, ref_frame> operator*(const Time& time) const { return { _angularAccels * time }; }

    template <typename Value_U>
    CartesianVector<decltype(AngularAcceleration{} / Value_U{}), in_frame> operator/(const Value_U& scalar) const
    {
        return { _angularAccels / scalar };
    }

    template <typename Value_U>
    auto dot(const CartesianVector<Value_U, in_frame>& other) const
    {
        return _angularAccels.dot(other);
    }

    auto dot(const AngularAccelerations<in_frame, ref_frame>& other) const
    {
        return _angularAccels.dot(other._angularAccels);
    }

    template <typename Value_U>
    CartesianVector<decltype(AngularAcceleration{} * Value_U{}), in_frame> cross(const CartesianVector<Value_U, in_frame>& other) const
    {
        return _angularAccels.cross(other);
    }

    CartesianVector<decltype(AngularAcceleration{} * AngularAcceleration{}), in_frame>
        cross(const AngularAccelerations<in_frame, ref_frame>& other) const
    {
        return _angularAccels.cross(other._angularAccels);
    }

    std::vector<double> force_to_double_vector() const
    {
        return { _angularAccels[0].numerical_value_in(_angularAccels[0].unit),
                 _angularAccels[1].numerical_value_in(_angularAccels[1].unit),
                 _angularAccels[2].numerical_value_in(_angularAccels[2].unit) };
    }

  private:
    CartesianVector<AngularAcceleration, in_frame> _angularAccels;
};

template <typename Value_U, IsFrame auto in_frame, IsFrame auto ref_frame>
CartesianVector<decltype(Value_U{} * AngularAcceleration{}), in_frame>
    operator*(const Value_U& scalar, const AngularAccelerations<in_frame, ref_frame>& accel)
{
    return { scalar * accel.get_angularAccels() };
}

template <IsFrame auto in_frame, IsFrame auto ref_frame>
AngularVelocities<in_frame, ref_frame> operator*(const Time& time, const AngularAccelerations<in_frame, ref_frame>& accel)
{
    return { time * accel.get_angularAccels() };
}

template <IsFrame auto in_frame, IsFrame auto ref_frame>
std::ostream& operator<<(std::ostream& os, const AngularVelocities<in_frame, ref_frame>& angleSequenceRate)
{
    os << "[" << angleSequenceRate[0] << " , " << angleSequenceRate[1] << " , " << angleSequenceRate[2] << "]";
    return os;
}

template <IsFrame auto in_frame, IsFrame auto ref_frame>
std::ostream& operator<<(std::ostream& os, const AngularAccelerations<in_frame, ref_frame>& angleSequenceAccel)
{
    os << "[" << angleSequenceAccel[0] << " , " << angleSequenceAccel[1] << " , " << angleSequenceAccel[2] << "]";
    return os;
}

} // namespace astro
} // namespace astrea
```


