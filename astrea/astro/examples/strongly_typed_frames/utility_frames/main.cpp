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
using mp_units::si::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

int main()
{
    // Astrea's frame system comes built in with some utility types to make building out custom frames easier.
    // For example, a BodyFixedFrame is a frame that is fixed to the surface of a celestial body, and has an origin at
    // the center of mass of the body. By inheriting from this class, we can create a new frame that is fixed to the
    // surface of Earth.
    struct my_earth_frame final : BodyFixedFrame<"my_earth_frame", planets::Earth> {
    } my_earth_frame;

    // NOTE: The current implementation of the BodyFixedFrame uses the "Reference" axis of the body. This is defined as
    // the axes that are aligned with the International Reference Pole (IRP) and International Reference Meridian (IRM)
    // of the body. This is slightly different than the "Geocentric" axes, which are aligned with the geographic pole
    // and meridian of the body.

    // Astrea also provides a utility type for synodic frames, defined at a barcenter and rotating with the synodic
    // period of two celestial bodies. For example, we can define a synodic frame at the Solar System Barycenter (SSB)
    // that rotates with the synodic period of Earth and Mars:
    struct ssb_earth_mars_synodic final
        : SynodicFrame<"ssb_earth_mars_synodic", barycenters::SolarSystemBarycenter, planets::Earth, planets::Mars> {
    } ssb_earth_mars_synodic;

    // The final simple utility frame class Astrea hosts is the FixedOffsetFrame. This frame can hold a time-fixed
    // offset and/or misalignment from another frame. This is typically useful for satellite frames where it may be
    // common to define a unique frame for each component on the satellite. These frames are particularly useful because
    // all translations and rotations between these frames are guaranteed to be evaluated at compile time.
    struct my_payload_frame final
        : FixedOffsetFrame<frames::dynamic::body, Distance(1.0 * m), Distance(2.0 * m), Distance(3.0 * m), Angle(10.0 * deg), Angle(0.0 * deg), Angle(15.0 * deg), RotationSequence::XYZ> {
    } my_payload_frame;

    return 0;
}