

# File StateTransitionMatrix.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**equations\_of\_motion**](dir_0a1395a4617b025941a2198784f446c5.md) **>** [**state\_transition\_matrix**](dir_7a22b679029b3e67ce8dbba97ffb681f.md) **>** [**StateTransitionMatrix.hpp**](StateTransitionMatrix_8hpp.md)

[Go to the documentation of this file](StateTransitionMatrix_8hpp.md)


```C++

#pragma once

#include <variant>

#include <mp-units/concepts.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

class StateTransitionMatrix {
  public:
    StateTransitionMatrix() = default;

    ~StateTransitionMatrix() = default;

    StateTransitionMatrix(const EquationsOfMotion& eom, const State& state, const Vehicle& vehicle);

    template <std::size_t ii, std::size_t jj, mp_units::Quantity Value_T>
    void set(const Value_T& value)
    {
        _stm[ii][jj] = value.numerical_value_in(value.unit) * mp_units::one;
    }

    std::vector<Unitless> force_to_vector() const;

  private:
    std::array<std::array<Unitless, 6>, 6> _stm; //, KeplerianStm, EquinoctialStm> _stm;
};

} // namespace astro
} // namespace astrea
```


