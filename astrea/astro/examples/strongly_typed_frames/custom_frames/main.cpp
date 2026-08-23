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

// Astrea supports a complex system that allows for arbitrary frame definitions as well as a completely
// compile-time interface for computing frame transformations. All frames directly connected to an origin or axis
// defined within the ICRS should be either supported directly or easily constructible.

// In general, a frame is defined by an origin and an axis. The origin is typically a celestial body or a
// barycenter, and the axis is typically a standard set of axes (e.g. ICRF, J2000, Earth-fixed, etc.).
// The origin and axis types are structural types that are used to pass relational information about the frames to
// the compiler, which allows for compile-time checking of frame transformations. Origins contain information about
// the parent origin and hook into the compile-time celestial reference system, allowing their position and velocity
// to be determined automatically. Axes are lest concrete and generally are just tags to signify which rotation
// sequences to use to compute DCMs to other frames.
inline constexpr struct gcrf final : Frame<"gcrf", planets::Earth, axes::icrf> {
} gcrf;
inline constexpr struct eme2000 final : Frame<"eme2000", planets::Earth, axes::j2000> {
} eme2000;

// Custom frames can be defined by simply defining new frame types, and then defining a DCM to other established
// frames. A single DCM should be sufficient to connect a new frame to the entire network of frames connected to the
// ICRS, as long as the DCM is defined to a frame that is already connected to the ICRS.

// Let's define a custom frame with some abstract axis that I've defined. An axis only requires a name, and
// optionally a parent axis to be defined. In this case, we'll add a parent to allow this frame to interface with
// the rest of the frame system more easily.
inline constexpr struct my_axes final : Axis<"MyAxis", axes::icrf> {
} my_axes;

// We could define a custom origin as well, but we'll just use Earth for this example.
// Now we can define our custom frame using the custom axis and the Earth origin.
inline constexpr struct my_earth_frame final : Frame<"my_earth_frame", planets::Earth, my_axes> {
} my_earth_frame;

// If a DCM is defined to a frame in the ICRS, Astrea can compute transformations to any frame connected to that
// frame by a chain of frames with defined DCMs.
namespace astrea {
namespace astro {

template <>
inline constexpr DCM<my_earth_frame, gcrf> get_dcm(const Date& date)
{
    // Compute the DCM from my_frame to gcrf at the given date.
    // This is just an example, so we'll return the identity matrix.
    return DCM<my_earth_frame, gcrf>::identity();
}

} // namespace astro
} // namespace astrea

// Custom origins can be defined similarly, but have more restrictions to work properly
// A simple frame with nothing but a name can be used to define a frame, but it won't be able to connect
// to any of the other defined frames unless it defines a parent origin within the current system of
// origins.
inline constexpr struct my_origin final : Origin<"MyOrigin"> {
} my_origin;
inline constexpr struct my_frame final : Frame<"my_frame", my_origin, my_axes> {
} my_frame;

// If we want this frame to use the same rotation as the previous one, we can just add some requires clauses to
// the DCM definition to allow it to be used if the frames share the same axis.
namespace astrea {
namespace astro {

template <IsFrame auto in_frame, IsFrame auto out_frame>
    requires(equivalent(in_frame.axis, my_axes) && equivalent(out_frame.axis, axes::icrf)) // equivalence is recommended over direct equality
inline constexpr DCM<in_frame, out_frame> get_dcm(const Date& date)
{
    return DCM<in_frame, out_frame>::identity();
}

} // namespace astro
} // namespace astrea

// If we want our origin to hook into the system of origins, we need to define a parent origin that is already in
// the system. This will allow us to compute the position and velocity of our origin automatically, which is
// necessary for frame transformations.
// NOTE: It is required to use a CelestialBody or a Barycenter as the origin base type to properly hook into the system.
// This may be changed in future releases to be more flexible.
inline constexpr struct my_origin_with_parent final : CelestialBody<"MyOriginWithParent", planets::Earth> {
} my_origin_with_parent;

inline constexpr struct my_complete_frame final : Frame<"my_complete_frame", my_origin_with_parent, my_axes> {
} my_complete_frame;

// The frame system still needs a way to locate your origin in space so if you want add a dynamically translating
// origin, you can either make your origin a celestial reference object (a planet, asteroid, barycenter, etc.) or
// you have to use a DynamicFrame, which must be evaluated at runtime and cannot be used in compile-time contexts.

// Adding your origin to the origin system requires that you define a single function specialization that returns
// all the celestial body parameters or specializing the get position/velocity functions for your origin.

// Option 1: This will use orbital elements to determine the origin's position and velocity.
namespace astrea {
namespace astro {

template <>
inline constexpr CelestialBodyParameters get_celestial_body_parameters<my_origin_with_parent>()
{
    using namespace mp_units;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::deg;
    using mp_units::si::unit_symbols::h;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::m;
    using mp_units::si::unit_symbols::rad;
    using mp_units::si::unit_symbols::s;

    // Return the celestial body parameters for my_origin_with_parent.
    // This is just an example, so we'll return some dummy parameters.
    return CelestialBodyParameters{
        .type                   = CelestialBodyType::PLANET,
        .referenceDate          = J2000,
        .mu                     = 3.986004418e14 * m * m * m / s / s,
        .mass                   = 5.97219e24 * kg,
        .equatorialRadius       = 6378.137 * km,
        .polarRadius            = 6356.7523 * km,
        .crashRadius            = 6371.0 * km,
        .sphereOfInfluence      = 924000.0 * km,
        .j2                     = 1.08263e-3,
        .j3                     = -2.5327e-6,
        .axialTilt              = 23.439281 * deg,
        .rotationRate           = 7.2921150e-5 * rad / s,
        .siderealPeriod         = 23.9344696 * h,
        .semimajorAxis          = 149597870.7 * km,
        .eccentricity           = 0.0167086,
        .inclination            = 0.00005 * deg,
        .rightAscension         = -11.26064 * deg,
        .longitudeOfPerigee     = 102.94719 * deg,
        .meanLongitude          = 100.46435 * deg,
        .semimajorAxisRate      = 0.0 * km / s,
        .eccentricityRate       = 0.0 / s,
        .inclinationRate        = 0.0 * deg / s,
        .rightAscensionRate     = 0.0 * deg / s,
        .longitudeOfPerigeeRate = 0.0 * deg / s,
        .meanLongitudeRate      = 0.9856076686 * deg / day,
    };
}

// Option 2: This gives you more control over the position and velocity, but requires more complexity.
template <>
inline constexpr CartesianVector<Distance, get_parent_frame(my_origin_with_parent, axes::icrf)>
    get_position_at<my_origin_with_parent>(const Date& date)
{
    // Return the position of my_origin_with_parent with respect to the origin's parent at the given date.
    // Note that the position must be returned in the frame defined by the origin's parent but the axes are
    // arbitrary. To avoid unnecessary rotations, it's required to return the position w.r.t. the icrf axes.

    // You can use the helper function to define the expected frame generically
    static constexpr auto parent_frame = get_parent_frame(my_origin_with_parent, axes::icrf);

    // This is just an example, so we'll return a static dummy position.
    return CartesianVector<Distance, parent_frame>{ 149597870.7 * km, 0.0 * km, 0.0 * km };
}
template <>
inline constexpr CartesianVector<Velocity, get_parent_frame(my_origin_with_parent, axes::icrf)>
    get_velocity_at<my_origin_with_parent>(const Date& date)
{
    static constexpr auto parent_frame = get_parent_frame(my_origin_with_parent, axes::icrf);
    return CartesianVector<Velocity, parent_frame>{ 0.0 * km / s, 29.78 * km / s, 0.0 * km / s };
}

} // namespace astro
} // namespace astrea

// NOTE: You can defined both of these functions if you want to use your origin as a celestial body anywhere in the code
// The explicit get_position_at and get_velocity_at specializations will take priority when computing the position and
// velocity but the first option is required to to, for example, use your origin for n-body calculations.

// Now with everything defined, your frame is fully connected to the system of frames and you can use it in any
// frame transformation or vector operation that you'd like!
int main()
{
    const auto rMyFrame   = CartesianVector<Length, my_complete_frame>{ 1.0 * km, 2.0 * km, 3.0 * km };
    const auto rGCRF      = rMyFrame.in_frame<gcrf>(J2000);
    const auto rEME2000   = rMyFrame.in_frame<eme2000>(J2000);
    const auto rMarsFixed = rMyFrame.in_frame<frames::mars::mars_fixed>(J2000);

    std::cout << "Position in my_complete_frame: " << rMyFrame << std::endl;
    std::cout << "Position in gcrf: " << rGCRF << std::endl;
    std::cout << "Position in EME2000: " << rEME2000 << std::endl;
    std::cout << "Position in Mars-Centered Mars-Fixed: " << rMarsFixed << std::endl;

    return 0;
}