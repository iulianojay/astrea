#include <iostream>

#include <units/units.hpp>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

int main()
{
    // Astrea has tried to create a system of strongly typed frames with some success, but it is still a work in
    // progress. The hope is to have a system that allows for compile-time checking of frame transformations, while also
    // being reasonably easy to use and develop. Right now, many of the difficulties presented by it's current structure
    // are propped up by hard-coding many instances to use ECI instead of a more generic "inertial frame".

    // The Frame class is designed to be a interface class (via the CRTP pattern) that holds simple, common
    // transformations and rules for other transformations. Each frame provides a hard coded function to return a
    // direction cosine matrix (DCM), templated by the frames it converts between. The base frame class is then meant to
    // dispatch to the correct DCM function based on the input and output frame types for a given transformation. While
    // this should work in theory, it proved to be difficult to fully implement. Here's a look at how it exists currently.

    // The CartesianVector class is a simple wrapper around a 3D vector, templated by the united-type and frame the
    // vector is defined in (or with respect to, depending).
    CartesianVector<Length, frames::earth::icrf> rEci{ 1.0 * m, 2.0 * m, 3.0 * m }; // Position in ECI frame

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
    RadiusVector<frames::earth::icrf> rEci2{ 1.0 * m, 2.0 * m, 3.0 * m }; // = CartesianVector<Distance, frames::earth::icrf>
    VelocityVector<frames::earth::icrf> vEci{ 1.0 * m / s, 2.0 * m / s, 3.0 * m / s }; // = CartesianVector<Velocity, frames::earth::icrf>

    // To convert to a static frame (static in that it's definition doesn't change with time), we can use the in_frame
    // method templated to the frame we'd like to convert to.
    Date date;
    CartesianVector<Length, frames::earth::earth_fixed> rEcef = rEci.in_frame<frames::earth::earth_fixed>(date);

    std::cout << std::endl << "Position in ECI: " << rEci << std::endl;
    std::cout << "Position in ECEF: " << rEcef << std::endl;

    // For complex, time-dependent frames, such as those attached to a payload, or vehicle, the frames must be explicitly instantiated
    // to call any vector transformations. They are not required to declare the vector type, however.
    RadiusVector<frames::dynamic::ric> rRic = { 1.0 * m, 2.0 * m, 3.0 * m };

    Spacecraft frameParent;
    frames::dynamic::ric dynamicRicFrame(&frameParent); // RIC frame attached to a spacecraft. As long as the spacecraft has a state
                                                        // history, the frame can be used to transform vectors.

    frames::dynamic::ric instantaneousRicFrame =
        frames::dynamic::ric::instantaneous(rEci2, vEci); // RIC frame defined at a specific time and state. Transformations to/from
                                                          // instantaneous frames are only valid at the time they are defined.

    RadiusVector<frames::earth::icrf> convertedrRic = instantaneousRicFrame.convert_from_this_frame(rRic, date);

    std::cout << "Position in RIC: " << rRic << std::endl;
    std::cout << "Position in instantaneous RIC: " << convertedrRic << std::endl;

    return 0;
}