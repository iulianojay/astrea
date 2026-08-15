

# File CelestialBody.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**CelestialBody.hpp**](CelestialBody_8hpp.md)

[Go to the documentation of this file](CelestialBody_8hpp.md)


```C++

#pragma once

#include <mp-units/framework/symbol_text.h>
#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/framework/Axis.hpp>
#include <astro/frames/framework/BodyFixedFrame.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/frames/framework/Frame.hpp>
#include <astro/frames/framework/Origin.hpp>
#include <astro/systems/CelestialBodyParameters.hpp>
#include <astro/systems/system_concepts.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

namespace detail {

struct CelestialBodyBase {};

} // namespace detail

// Reference axes defined by the International Reference Pole (IPM) and the International Reference Meridian (IRM).
template <mp_units::symbol_text _name_>
struct ReferenceAxes : Axis<_name_ + mp_units::symbol_text{ " reference axes" }, axes::icrf> {};

// Geocentric axes defined by the geographic pole and meridian.
template <mp_units::symbol_text _name_>
struct GeocentricAxes : Axis<_name_ + mp_units::symbol_text{ " geocentric axes" }, axes::icrf> {};

template <mp_units::symbol_text _name_, IsOrigin auto _parent_>
struct CelestialBody : Origin<_name_, _parent_>, detail::CelestialBodyBase {
    static constexpr ReferenceAxes<_name_> reference_axes{};
    static constexpr GeocentricAxes<_name_> geocentric_axes{};
};

// ---------------------------------------------------------------------------
// Primary template declarations.
// These live here (not in property_getters.hpp) so that planet headers
// can specialise them without triggering the heavy State/Keplerian/frames include
// chain that property_getters.hpp used to pull in.
// ---------------------------------------------------------------------------

template <auto _body_>
inline consteval CelestialBodyParameters get_celestial_body_parameters() = delete;

template <auto _body_>
inline Density find_atmospheric_density(const State& state)
{
    return Density::zero();
}

template <auto _body_>
inline constexpr CartesianVector<Distance, get_parent_frame(_body_, axes::icrf)> get_position_at(const Date& date);

template <auto _body_>
inline constexpr CartesianVector<Velocity, get_parent_frame(_body_, axes::icrf)> get_velocity_at(const Date& date);

template <auto _body_>
inline constexpr CartesianVector<Acceleration, get_parent_frame(_body_, axes::icrf)> get_acceleration_at(const Date& date);

} // namespace astro
} // namespace astrea

// property_getters.hpp provides lightweight inline helpers (get_mu, get_mass, etc.)
// and get_position_at_impl / get_velocity_at_impl.  It is lightweight — no State.hpp dependency.
#include <astro/systems/property_getters.hpp>
```


