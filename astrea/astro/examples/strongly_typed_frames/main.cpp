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

#include <iostream>

#include <units/units.hpp>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::non_si::day;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

int main()
{
    // Astrea supports a system of strongly typed frames which allows for compile-time checking of frame
    // transformations, while also being reasonably simple to extend.

    // The Frame class is a compile-time interface that allows rules to be imposed on frame-supporting types,
    // and frame transformations. A frame in Astrea is defined by an origin (typically a celestial body), and an
    // axis. Currently, Astrea only supports pre-defined origins for static frames (that is, the center is inertially
    // fixed), and a series of pre-defined axes. Future releases may allow for completely customized origins and axes.

    // Astrea provides definitions for many commonly used frames
    using ECI  = frames::earth::icrf;        // static
    using ECEF = frames::earth::earth_fixed; // static
    using RIC  = frames::dynamic::ric;       // dynamic

    // The CartesianVector class is a simple wrapper around a 3D vector, templated by the united-type and the frame the vector is defined in (or with respect to, depending).
    CartesianVector<Length, ECI> rEci{ 1.0 * m, 2.0 * m, 3.0 * m }; // Position in ECI frame

    // The vector utility also several common vector operations, such as dot and cross products.
    auto rEciMag   = rEci.norm();
    auto rEciUnit  = rEci.unit();
    auto rEciDot   = rEci.dot(rEci);
    auto rEciCross = rEci.cross(rEci);

    std::cout << "rEci: " << rEci << std::endl;
    std::cout << "rEciMag: " << rEciMag << std::endl;
    std::cout << "rEciUnit: " << rEciUnit << std::endl;
    std::cout << "rEciDot: " << rEciDot << std::endl;
    std::cout << "rEciCross: " << rEciCross << std::endl;

    // There are also some convenience type definitions for common cartesian vector types.
    RadiusVector<ECI> rEci2{ 1.0 * m, 2.0 * m, 3.0 * m };              // = CartesianVector<Distance, ECI>
    VelocityVector<ECI> vEci{ 1.0 * m / s, 2.0 * m / s, 3.0 * m / s }; // = CartesianVector<Velocity, ECI>

    // To convert to a static frame, we can use the in_frame method templated to the frame we'd like to convert to.
    Date date;
    CartesianVector<Length, ECEF> rEcefJ2000 = rEci.in_frame<ECEF>(date);
    CartesianVector<Length, ECEF> rEcef      = rEci.in_frame<ECEF>(date + 0.5 * day);

    std::cout << std::endl << "Position in ECI: " << rEci << std::endl;
    std::cout << "Position in ECEF @ J2000: " << rEcefJ2000 << std::endl;
    std::cout << "Position in ECEF @ J2000 + 12 hours: " << rEcef << std::endl;

    // Implicit frame switches are not allowed, but can be forced in special circumstances
    // CartesianVector<Length, ECEF> rEcefImplicit = rEci; // Compiler will fail!
    CartesianVector<Length, ECEF> rEcefForced = rEci.force_frame_conversion<ECEF>();

    // Implicit transformation to/from dynamic frames are not allowed
    // CartesianVector<Length, RIC> rRic = rEci.in_frame<RIC>(J2000); // Compiler will fail!

    // Frames do not necessarily need to be fully defined to be used
    class MyFrame;
    CartesianVector<Length, MyFrame> rCustom{ 1.0 * m, 2.0 * m, 3.0 * m };

    // But the definition needs to be complete to use frame transformations
    // CartesianVector<Length, ECI> rEci = rCustom.in_frame<ECI>(date); // Compiler will fail!

    // For complex, time-dependent frames, such as those attached to a payload, or vehicle, the frames must be explicitly instantiated
    // to call any vector transformations. They are not required to declare the vector type, however.
    RadiusVector<RIC> rRic = { 1.0 * m, 2.0 * m, 3.0 * m };

    // Dynamic frames can either be attached to a FrameReference object (such as a spacecraft), or defined instantaneously at a specific state.
    Spacecraft frameParent;
    RIC dynamicRicFrame(&frameParent); // RIC frame attached to a spacecraft. As long as the spacecraft has a state
                                       // history, the frame can be used to transform vectors.

    RIC instantaneousRicFrame =
        RIC::instantaneous(rEci2, vEci); // RIC frame defined at a specific time and state. Transformations to/from
                                         // instantaneous frames are only valid at the time they are defined.

    // Convert from RIC to ECI using the instantaneous dynamic frame
    // Note: here we use the convert_from_this_frame method, as we are converting from RIC to ECI.
    // While static frames handle the direction of conversion automatically, dynamic frames do not and
    // require the user to specify the direction by calling the appropriate method.
    RadiusVector<ECI> convertedrRic = instantaneousRicFrame.convert_from_this_frame(rRic, date);

    std::cout << "Position in RIC: " << rRic << std::endl;
    std::cout << "Position in instantaneous RIC: " << convertedrRic << std::endl;

    return 0;
}