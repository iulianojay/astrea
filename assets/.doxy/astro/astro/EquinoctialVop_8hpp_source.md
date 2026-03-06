

# File EquinoctialVop.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**equations\_of\_motion**](dir_0a1395a4617b025941a2198784f446c5.md) **>** [**EquinoctialVop.hpp**](EquinoctialVop_8hpp.md)

[Go to the documentation of this file](EquinoctialVop_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>

namespace astrea {
namespace astro {

class EquinoctialVop : public EquationsOfMotion {

  public:
    EquinoctialVop(const ForceModel& forces);

    ~EquinoctialVop() = default;

    OrbitalElementPartials operator()(const State& state, const Vehicle& vehicle) const override;

    StateTransitionMatrix compute_stm(const State& state, const Vehicle& vehicle) const override;

    constexpr std::size_t get_expected_set_id() const override { return OrbitalElements::get_set_id<Equinoctial>(); };

  private:
    const Unitless checkTol = 1e-10 * mp_units::one; 
    const ForceModel* forces;                        
};

} // namespace astro
} // namespace astrea
```


