#pragma once

#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/format.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

#include <astro/units/units.hpp>

namespace astro {

static const mp_units::quantity<mp_units::mag<mp_units::pi>* detail::angle_unit> PI =
    1.0 * (mp_units::mag<mp_units::pi> * detail::angle_unit);
static const mp_units::quantity<mp_units::mag<mp_units::pi>* detail::angle_unit> TWO_PI =
    2.0 * (mp_units::mag<mp_units::pi> * detail::angle_unit);

} // namespace astro