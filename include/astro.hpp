#pragma once

#include "astro/constants/astronomical_constants.h"
#include "astro/constants/math_constants.h"
#include "astro/constants/rk_constants.h"

#include "astro/element_sets/ElementSet.hpp"
#include "astro/element_sets/Frame.hpp"
#include "astro/element_sets/OrbitalElements.hpp"

#include "astro/platforms/space/Constellation.hpp"
#include "astro/platforms/space/Shell.hpp"
#include "astro/platforms/space/Plane.hpp"
#include "astro/platforms/space/Spacecraft.hpp"

#include "astro/propagation/EquationsOfMotion.hpp"
#include "astro/propagation/Integrator.hpp"
#include "astro/propagation/LambertSolver.hpp"

#include "astro/systems/AstrodynamicsSystem.hpp"
#include "astro/systems/Barycenter.hpp"
#include "astro/systems/GravitationalBody.hpp"
#include "astro/systems/solar_system.hpp"
#include "astro/systems/SolarObjectBuilder.hpp"
#include "astro/systems/SolarObjectFactory.hpp"

#include "astro/time/Date.hpp"
#include "astro/time/Time.hpp"

#include "astro/types/typedefs.hpp"

#include "astro/utilities/conversions.hpp"
#include "astro/utilities/math_c.hpp"

#include "astro/State.hpp"

#ifndef SWIG

#include "astro/time/JulianDateClock.hpp"
#include "astro/time/time_units.hpp"

#endif