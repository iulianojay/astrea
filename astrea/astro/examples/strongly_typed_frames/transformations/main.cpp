/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>

#include <units/units.hpp>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::non_si::day;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

int main()
{
    // Astrea handles aberrations in frame transformations the same it handles standard transformations. By combining
    // strongly-typed units with the strongly-typed frames, it's possible to know, for example, whether a vector
    // rotation requires translation, rotation, aberrations, etc. Astrea provides some simple utilities to represent
    // different CartesianVector types.
    CartesianVector<Distance, frames::earth::icrf> vec0; // A vector with units and frame information
    Direction<frames::earth::icrf> vec1;                 // A vector with frame information assumed to be Unitless
    RadiusVector<frames::earth::icrf> vec2; // A vector with frame information assumed to use the Distance definition as it's value type
    VelocityVector<frames::earth::icrf> vec3; // A vector with frame information assumed to use the Velocity definition as it's value type
    AccelerationVector<frames::earth::icrf> vec4; // A vector with frame information assumed to use the Acceleration definition as it's value type

    // The standard transformation for a position vector is given by:
    //      r2 = DCM_1^2 * r1 + r1->2
    // where r1 is the original vector, DCM_1^2 is the direction cosine matrix for the rotation from frame 1 to frame 2,
    // and r1->2 is the translation vector from frame 1 to frame 2. If vector is a direction vector, it is assumed that
    // the translation is zero (since directions are all relative and not anchored to an origin) and the transformation is given by:
    //      r2 = DCM_1^2 * r1
    // If the vector is a velocity vector, the transformation is given by:
    //      v2 = DCM_1^2 * v1 + d/dt(DCM_1^2) * r1
    // where d/dt(DCM_1^2) is the first time derivative of the DCM. If the vector is an acceleration vector, the
    // transformation is given by the next derivative:
    //      a2 = DCM_1^2 * a1 + 2 * d/dt(DCM_1^2) * v1 + d^2/dt^2(DCM_1^2) * r1
    // where d^2/dt^2(DCM_1^2) is the second time derivative of the DCM.

    // Astrea access the transformation through specializations of `get_dcm`, `get_dcm_rate`, and `get_dcm_accel`. Offsets are handled
    // by the origin system and don't require user input. See the "custom frames" tutorial for more details.

    // For each of these transformations, Astrea hides the complexity behind the simple `in_frame` method.
    Date epoch("2020-02-18 15:08:47.23847");
    CartesianVector<Distance, frames::earth::icrf> r1; // A position vector with Distance value type
    CartesianVector<Distance, frames::earth::earth_fixed> r2 =
        r1.in_frame<frames::earth::earth_fixed>(epoch); // Transforms r1 from Frame1 to Frame2 at the given epoch

    // The same process applies for the other vector types, and the correct transformation is applied based on the type of vector.
    // However, these abbarations require addition information beyond the date, so that information is required.
    CartesianVector<Velocity, frames::earth::icrf> v1; // A velocity vector with Velocity value type
    CartesianVector<Velocity, frames::earth::earth_fixed> v2 =
        v1.in_frame<frames::earth::earth_fixed>(epoch, r1); // Transforms v1 from Frame1 to Frame2 at the given epoch

    CartesianVector<Acceleration, frames::earth::icrf> a1; // An acceleration vector with Acceleration value type
    CartesianVector<Acceleration, frames::earth::earth_fixed> a2 =
        a1.in_frame<frames::earth::earth_fixed>(epoch, r1, v1); // Transforms a1 from Frame1 to Frame2 at the given epoch

    // Sometimes it's desirable to apply a specific transformation, such as a pure rotation without translation or
    // aberrations. In this case, users can call the direct rotations
    auto v2NoAbberation = frames::rotate_vector_into_frame<frames::earth::earth_fixed>(v1, epoch);

    return 0;
}