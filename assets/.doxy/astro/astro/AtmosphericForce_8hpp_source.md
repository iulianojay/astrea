

# File AtmosphericForce.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md) **>** [**AtmosphericForce.hpp**](AtmosphericForce_8hpp.md)

[Go to the documentation of this file](AtmosphericForce_8hpp.md)


```C++

#pragma once

#include <map>
#include <tuple>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/force_models/PerturbingForce.hpp>

namespace astrea {
namespace astro {

class AtmosphericForce : public PerturbingForce {

  public:
    AtmosphericForce() = default;

    ~AtmosphericForce() = default;

    Perturbation compute_perturbation(const State& state, const Vehicle& vehicle) const override;

    std::unique_ptr<PerturbingForce> clone() const override { return std::make_unique<AtmosphericForce>(*this); }
};

} // namespace astro
} // namespace astrea
```


