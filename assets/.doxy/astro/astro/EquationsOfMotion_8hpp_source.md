

# File EquationsOfMotion.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**equations\_of\_motion**](dir_0a1395a4617b025941a2198784f446c5.md) **>** [**EquationsOfMotion.hpp**](EquationsOfMotion_8hpp.md)

[Go to the documentation of this file](EquationsOfMotion_8hpp.md)


```C++

#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions.hpp>
#include <astro/frames/definitions/primary_frame.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

class EquationsOfMotion {
  public:
    EquationsOfMotion() = default;

    EquationsOfMotion(const ForceModel& forces);

    virtual ~EquationsOfMotion() = default;

    StatePartial operator()(const State& state, const Vehicle& vehicle) const;

    virtual OrbitalElementPartials compute_dynamics(
        const State& state,
        const Vehicle& vehicle,
        const ForceVector<frames::primary>& perts,
        const ForceVector<frames::primary>& control
    ) const = 0;

    virtual AttitudePartials compute_kinematics(
        const State& state,
        const Vehicle& vehicle,
        const TorqueVector<frames::primary>& perts,
        const TorqueVector<frames::primary>& control
    ) const;

    virtual StateTransitionMatrix compute_stm(const State& state, const Vehicle& vehicle) const;

    virtual constexpr std::size_t get_expected_set_id() const = 0;

  protected:
    const ForceModel* forces = nullptr; 
};

} // namespace astro
} // namespace astrea
```


