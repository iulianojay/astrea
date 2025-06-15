#pragma once

#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/format.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

#include <astro/types/typedefs.hpp>
#include <astro/units/units.hpp>

namespace accesslib {

constexpr astro::Velocity speed_of_light_in_vacuum = 1.0 * mp_units::si::si2019::speed_of_light_in_vacuum;

} // namespace accesslib