#pragma once

#include <array>
#include <stdint.h>

#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/format.h>
#include <mp-units/ostream.h>

#include <access/units/units.hpp>

namespace accesslib {

// Quantities
using Gain             = mp_units::quantity<astro::detail::unitless>;
using Frequency        = mp_units::quantity<detail::frequency_unit>;
using Power            = mp_units::quantity<detail::power_unit>;
using PowerFluxDensity = mp_units::quantity<detail::power_unit / mp_units::pow<2>(astro::detail::minor_distance_unit)>;

} // namespace accesslib