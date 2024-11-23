#pragma once

#include "astro/access/access.hpp"

#include "astro/constants/astronomical_constants.h"
#include "astro/constants/math_constants.h"
#include "astro/constants/rk_constants.h"

#include "astro/element_sets/ElementSet.hpp"
#include "astro/element_sets/Frame.hpp"
#include "astro/element_sets/OrbitalElements.hpp"

#include "astro/platforms/access/fov/FieldOfView.hpp"
#include "astro/platforms/access/Antenna.hpp"
#include "astro/platforms/access/Sensor.hpp"

#include "astro/platforms/ground/GroundStation.hpp"

#include "astro/platforms/space/Constellation.hpp"
#include "astro/platforms/space/Shell.hpp"
#include "astro/platforms/space/Plane.hpp"
#include "astro/platforms/space/Spacecraft.hpp"

#include "astro/propagation/Integrator.hpp"
#include "astro/propagation/LambertSolver.hpp"

#include "astro/propagation/force_models/AtmosphericForce.hpp"
#include "astro/propagation/force_models/Force.hpp"
#include "astro/propagation/force_models/ForceModel.hpp"
#include "astro/propagation/force_models/NBodyForce.hpp"
#include "astro/propagation/force_models/OblatenessForce.hpp"
#include "astro/propagation/force_models/SolarRadiationPressureForce.hpp"

#include "astro/propagation/equations_of_motion/CoesVop.hpp"
#include "astro/propagation/equations_of_motion/CowellsMethod.hpp"
#include "astro/propagation/equations_of_motion/EquationsOfMotion.hpp"
#include "astro/propagation/equations_of_motion/J2MeanVop.hpp"
#include "astro/propagation/equations_of_motion/MeesVop.hpp"
#include "astro/propagation/equations_of_motion/TwoBody.hpp"

#include "astro/systems/AstrodynamicsSystem.hpp"
#include "astro/systems/Barycenter.hpp"
#include "astro/systems/GravitationalBody.hpp"
#include "astro/systems/solar_system.hpp"
#include "astro/systems/SolarObjectBuilder.hpp"
#include "astro/systems/SolarObjectFactory.hpp"

#include "astro/time/Date.hpp"
#include "astro/time/Interval.hpp"
#include "astro/time/Time.hpp"
#include "astro/time/access/AccessArray.hpp"
#include "astro/time/access/RiseSetArray.hpp"

#include "astro/types/typedefs.hpp"

#include "astro/utilities/conversions.hpp"
#include "astro/utilities/riseset_utils.hpp"
#include "astro/utilities/math/interpolation.hpp"
#include "astro/utilities/math/math_c.hpp"

#include "astro/State.hpp"

#ifndef SWIG

#include "astro/time/JulianDateClock.hpp"
#include "astro/time/time_units.hpp"

#endif