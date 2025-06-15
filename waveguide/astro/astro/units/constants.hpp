#pragma once

#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/format.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

#include <astro/types/typedefs.hpp>
#include <astro/units/units.hpp>

namespace astro {

static const Angle PI     = 1.0 * (mp_units::mag<mp_units::pi> * detail::angle_unit);
static const Angle TWO_PI = 2.0 * (mp_units::mag<mp_units::pi> * detail::angle_unit);

constexpr mp_units::quantity<mp_units::mag<mp_units::pi> * detail::angle_unit> n_pi(const double& mag)
{
    return mag * (mp_units::mag<mp_units::pi> * detail::angle_unit);
}

constexpr mp_units::quantity<detail::unitless> n_pi_mag(const double& mag)
{
    return mag * (mp_units::mag<mp_units::pi> * detail::unitless);
}

} // namespace astro