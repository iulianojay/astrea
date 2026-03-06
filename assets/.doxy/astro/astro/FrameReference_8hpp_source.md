

# File FrameReference.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**FrameReference.hpp**](FrameReference_8hpp.md)

[Go to the documentation of this file](FrameReference_8hpp.md)


```C++

#pragma once

#include <string>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/instances/body_centered_inertial_frames.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

class FrameReference {
  public:
    FrameReference() = default;

    virtual ~FrameReference() = default;

    virtual std::string get_name() const = 0; 

    virtual CartesianVector<Distance, frames::earth::icrf> get_inertial_position(const Date& date) const = 0;

    virtual CartesianVector<Velocity, frames::earth::icrf> get_inertial_velocity(const Date& date) const = 0;

    virtual CartesianVector<Acceleration, frames::earth::icrf> get_inertial_acceleration(const Date& date) const;
};

} // namespace astro
} // namespace astrea
```


