

# File Attitude.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md) **>** [**attitude**](dir_d187d1a6cf435d7a067093cc1f3d7926.md) **>** [**Attitude.hpp**](Attitude_8hpp.md)

[Go to the documentation of this file](Attitude_8hpp.md)


```C++

#pragma once

#include <iosfwd>
#include <variant>

#include <units/units.hpp>

// Astro
#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions.hpp>
#include <astro/frames/definitions/dynamic_frames/tags.hpp>
#include <astro/state/attitude/AngularVelocities.hpp>
#include <astro/state/attitude/EulerAngles.hpp>
#include <astro/state/attitude/Quaternion.hpp>
#include <astro/types/type_traits.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/types/variant_util.hpp>

namespace astrea {
namespace astro {

using BodyQuaternion = Quaternion<frames::dynamic::body, frames::earth::icrf>;

using BodyQuaternionRate = QuaternionPartial<frames::dynamic::body, frames::earth::icrf>;

using BodyAngles = EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, frames::dynamic::body, frames::earth::icrf>;

using BodyAngleVelocities = AngularVelocities<frames::dynamic::body, frames::earth::icrf>;

using BodyAngularAcceleration = AngularAccelerations<frames::dynamic::body, frames::earth::icrf>;

template <typename T>
concept IsAttitude = requires(T) {
    std::is_same<T, remove_cv_ref<T>>::value;
    std::is_default_constructible<T>::value;
    std::is_copy_constructible<T>::value;
    std::is_move_constructible<T>::value;
    std::is_destructible<T>::value;
    requires !std::is_same<T, Attitude>::value;
};

class AttitudePartials; // Forward declaration

class Attitude {

    friend std::ostream& operator<<(std::ostream& os, const Attitude& state);
    friend class StateTransitionMatrix;
    friend class State;

  public:
    Attitude() = default;

    Attitude(const BodyQuaternion& orientation, const BodyAngleVelocities& angularVelocity);

    template <RotationSequence sequence, RotationType rotationType>
    Attitude(const EulerAngles<sequence, rotationType, frames::dynamic::body, frames::earth::icrf>& angleSequence, const BodyAngleVelocities& angleSequenceVelocity) :
        _orientation(angleSequence),
        _angularVelocity(angleSequenceVelocity)
    {
    }

    const BodyQuaternion& get_orientation() const { return _orientation; }

    const BodyAngleVelocities& get_angular_velocity() const { return _angularVelocity; }

    bool operator==(const Attitude& other) const;

    Attitude operator+(const Attitude& other) const;

    Attitude& operator+=(const Attitude& other);

    Attitude operator-(const Attitude& other) const;

    Attitude& operator-=(const Attitude& other);

    Attitude operator*(const Unitless& multiplier) const;

    Attitude& operator*=(const Unitless& multiplier);

    AttitudePartials operator/(const Time& divisor) const;

    std::vector<double> force_to_double_vector() const;

    Attitude operator/(const Unitless& divisor) const;

    Attitude& operator/=(const Unitless& divisor);

    Attitude interpolate(const Time& thisTime, const Time& otherTime, const Attitude& other, const Time& targetTime) const;

  private:
    BodyQuaternion _orientation;          
    BodyAngleVelocities _angularVelocity; 

    static Attitude from_double_vector(const std::vector<double>& vec);
};

class AttitudePartials {

    friend std::ostream& operator<<(std::ostream& os, const AttitudePartials& state);

    friend class StatePartial;

  public:
    AttitudePartials() = default;

    AttitudePartials(const BodyQuaternionRate& orientationRate, const BodyAngularAcceleration& angularAcceleration);

    Attitude operator*(const Time& time) const;

    std::vector<double> force_to_double_vector() const;

  private:
    BodyQuaternionRate _orientationRate; 
    BodyAngularAcceleration _angularAcceleration; 
};

} // namespace astro
} // namespace astrea
```


