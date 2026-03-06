

# File LambertSolver.hpp

[**File List**](files.md) **>** [**analytic**](dir_0032edd3690e3836975e7dd677ed5fa8.md) **>** [**LambertSolver.hpp**](LambertSolver_8hpp.md)

[Go to the documentation of this file](LambertSolver_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

class LambertSolver {
  public:
    LambertSolver() = delete;

    ~LambertSolver() = delete;

    enum class OrbitDirection : EnumType {
        PROGRADE,  
        RETROGRADE 
    };

    static Cartesian solve(const Cartesian& state0, const Time& dt, const GravParam& mu);

    static std::pair<VelocityVector<frames::earth::icrf>, VelocityVector<frames::earth::icrf>> solve(
        const RadiusVector<frames::earth::icrf>& r0,
        const RadiusVector<frames::earth::icrf>& rf,
        const Time& dt,
        const GravParam& mu,
        const OrbitDirection& direction
    );

  private:
    static constexpr unsigned ITER_MAX = 1e4;                     
    static constexpr Unitless TOL      = 1.0e-12 * mp_units::one; 

    static std::pair<Unitless, Unitless> evaluate_stumpff(const Unitless& z);
};

// TODO: Implement Battin algorithm
// TODO: give min time and min energy options

} // namespace astro
} // namespace astrea
```


