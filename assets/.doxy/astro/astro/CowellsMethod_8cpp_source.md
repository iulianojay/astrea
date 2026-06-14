

# File CowellsMethod.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**equations\_of\_motion**](dir_0a1395a4617b025941a2198784f446c5.md) **>** [**CowellsMethod.cpp**](CowellsMethod_8cpp.md)

[Go to the documentation of this file](CowellsMethod_8cpp.md)


```C++
/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/propagation/equations_of_motion/CowellsMethod.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/math.h>

#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/StateTransitionMatrix.hpp>
#include <astro/propagation/equations_of_motion/TwoBody.hpp>
#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/Cartesian.hpp>


using namespace mp_units;
using namespace mp_units::non_si;
using si::unit_symbols::km;
using si::unit_symbols::s;

namespace astrea {
namespace astro {

CowellsMethod::CowellsMethod(const ForceModel& forces) :
    EquationsOfMotion(forces)
{
}

OrbitalElementPartials CowellsMethod::compute_dynamics(
    const State& state,
    const Vehicle& vehicle,
    const ForceVector<frames::primary>& perts,
    const ForceVector<frames::primary>& control
) const
{
    // Extract
    const GravParam mu = get_mu<frames::primary.origin>();

    const RadiusVector<frames::primary> r   = state.get_position();
    const VelocityVector<frames::primary> v = state.get_velocity();

    // mu/R^3
    const Distance R             = r.norm();
    const auto muOverRadiusCubed = mu / (R * R * R);

    // Derivative
    return CartesianPartial<frames::primary>(v, -muOverRadiusCubed * r + (perts + control) / vehicle.get_mass());
}


StateTransitionMatrix CowellsMethod::compute_stm(const State& state, const Vehicle& vehicle) const
{
    if (forces->size() == 0) {
        // If no perturbations, use two-body STM
        const TwoBody twoBody;
        return twoBody.compute_stm(state, vehicle);
    }
    return StateTransitionMatrix(*this, state, vehicle);
}

} // namespace astro
} // namespace astrea
```


