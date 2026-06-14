

# File TurnThrustersOn.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**event\_detection**](dir_283e5a6c8e70b5075f630fb83b6454d7.md) **>** [**events**](dir_ffe0d0558a41319d577ebe8d35f3c9da.md) **>** [**TurnThrustersOn.hpp**](TurnThrustersOn_8hpp.md)

[Go to the documentation of this file](TurnThrustersOn_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

class TurnThrustersOn {

  public:
    TurnThrustersOn();

    std::string get_name() const;

    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const;

    void trigger_action(const Time& time, State& state, Vehicle& vehicle) const;

    bool is_terminal() const;
};

} // namespace astro
} // namespace astrea
```


