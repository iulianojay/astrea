/**
 * @file astro.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the astro module
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <units/units.hpp>

#include <astro/state/State.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/state/CartesianVector.hpp>
#include <astro/state/orbital_elements/orbital_elements.hpp>
#include <astro/state/angular_elements/angular_elements.hpp>
#include <astro/state/orbital_data_formats/orbital_data_formats.hpp>

#include <astro/state/frames/Frame.hpp>
#include <astro/state/frames/FrameReference.hpp>
#include <astro/state/frames/frames.hpp>
#include <astro/state/frames/instances/EarthCenteredEarthFixed.hpp>
#include <astro/state/frames/instances/EarthCenteredInertial.hpp>
#include <astro/state/frames/types/DirectionCosineMatrix.hpp>
#include <astro/state/frames/types/InertialFrame.hpp>
#include <astro/state/frames/types/RotatingFrame.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/platforms/space/Constellation.hpp>
#include <astro/platforms/space/Plane.hpp>
#include <astro/platforms/space/Shell.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>

#include <astro/propagation/analytic/LambertSolver.hpp>

#include <astro/propagation/force_models/AtmosphericForce.hpp>
#include <astro/propagation/force_models/Force.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/propagation/force_models/NBodyForce.hpp>
#include <astro/propagation/force_models/OblatenessForce.hpp>
#include <astro/propagation/force_models/SolarRadiationPressure.hpp>

#include <astro/propagation/equations_of_motion/CowellsMethod.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/equations_of_motion/EquinoctialVop.hpp>
#include <astro/propagation/equations_of_motion/J2MeanVop.hpp>
#include <astro/propagation/equations_of_motion/KeplerianVop.hpp>
#include <astro/propagation/equations_of_motion/TwoBody.hpp>

#include <astro/propagation/numerical/Integrator.hpp>
#include <astro/propagation/numerical/rk_constants.h>

#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/systems/Barycenter.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/CelestialBodyFactory.hpp>

#include <astro/time/Date.hpp>
#include <astro/time/Interval.hpp>
#include <astro/time/JulianDateClock.hpp>

#include <astro/types/tuple_hash.hpp>
#include <astro/types/typedefs.hpp>