/**
 * @file astro.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the astro module
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <astro/frames/CartesianVector.hpp>
#include <astro/state/State.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/state/angular_elements/angular_elements.hpp>
#include <astro/state/orbital_data_formats/orbital_data_formats.hpp>
#include <astro/state/orbital_elements/orbital_elements.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/Frame.hpp>
#include <astro/frames/dynamic_frames.hpp>
#include <astro/frames/frame_concepts.hpp>
#include <astro/frames/frames.hpp>
#include <astro/frames/transformations.hpp>

#include <astro/frames/DirectionCosineMatrix.hpp>
#include <astro/frames/DynamicFrame.hpp>
#include <astro/frames/instances/LocalHorizontalLocalVertical.hpp>
#include <astro/frames/instances/RadialInTrackCrossTrack.hpp>
#include <astro/frames/instances/VelocityNormalBinormal.hpp>
#include <astro/frames/instances/body_centered_inertial_frames.hpp>
#include <astro/frames/instances/defined_rotations.hpp>
#include <astro/frames/instances/fixed_rotating_frames.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/platforms/space/Constellation.hpp>
#include <astro/platforms/space/Plane.hpp>
#include <astro/platforms/space/Shell.hpp>
#include <astro/platforms/thrusters/Thruster.hpp>
#include <astro/platforms/vehicles/NullVehicle.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>

#include <astro/propagation/analytic/LambertSolver.hpp>

#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/propagation/force_models/Perturbation.hpp>
#include <astro/propagation/force_models/PerturbingForce.hpp>
#include <astro/propagation/force_models/instances/AtmosphericForce.hpp>
#include <astro/propagation/force_models/instances/NBodyForce.hpp>
#include <astro/propagation/force_models/instances/OblatenessForce.hpp>
#include <astro/propagation/force_models/instances/SolarRadiationPressure.hpp>

#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/equations_of_motion/instances/CowellsMethod.hpp>
#include <astro/propagation/equations_of_motion/instances/EquinoctialVop.hpp>
#include <astro/propagation/equations_of_motion/instances/J2MeanVop.hpp>
#include <astro/propagation/equations_of_motion/instances/KeplerianVop.hpp>
#include <astro/propagation/equations_of_motion/instances/TwoBody.hpp>

#include <astro/propagation/event_detection/Event.hpp>
#include <astro/propagation/event_detection/EventDetector.hpp>
#include <astro/propagation/event_detection/events/ImpulsiveBurn.hpp>

#include <astro/propagation/numerical/Integrator.hpp>
#include <astro/propagation/numerical/StepWatcher.hpp>
#include <astro/propagation/numerical/butcher_tableau.hpp>

#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/CelestialBodyParameters.hpp>
#include <astro/systems/planets.hpp>
#include <astro/systems/system_utilities>

#include <astro/time/Date.hpp>
#include <astro/time/Interval.hpp>
#include <astro/time/JulianDateClock.hpp>
#include <astro/time/TerrestrialTimeClock.hpp>

#include <astro/types/tuple_hash.hpp>
#include <astro/types/typedefs.hpp>

#include <astro/utilities/conversions.hpp>