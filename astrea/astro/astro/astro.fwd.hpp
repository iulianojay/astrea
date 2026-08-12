/**
 * @file astro.fwd.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Forward declarations for the astro module
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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

#include <concepts>

#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

class State;
class StatePartial;
class StateHistory;

// ELement sets
template <IsFrame auto _frame_>
class Cartesian;
template <IsFrame auto _frame_>
class Keplerian;
template <IsFrame auto _frame_>
class Equinoctial;
template <IsFrame auto _frame_>
class CartesianPartial;
template <IsFrame auto _frame_>
class KeplerianPartial;
template <IsFrame auto _frame_>
class EquinoctialPartial;

class TwoLineElements;
class TwoLineElementsPartial;
class GeneralPerturbations;
class OrbitalElements;
class OrbitalElementPartials;

class CartesianStm;
class KeplerianStm;
class EquinoctialStm;
class StateTransitionMatrix;

// Quaternions
template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
class Quaternion;

template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
class QuaternionPartial;

template <RotationSequence sequence, RotationType rotationType, IsFrame auto _in_frame_, IsFrame auto _out_frame_>
class EulerAngles;

template <IsFrame auto _in_frame_, IsFrame auto _ref_frame_>
class AngularVelocities;

template <IsFrame auto _in_frame_, IsFrame auto _ref_frame_>
class AngularAccelerations;

class Attitude;
class AttitudePartials;

// Frames
template <typename Value_T, IsFrame auto _frame_>
struct CartesianVector;

namespace frames {

template <IsFrame auto _parent_>
struct EastNorthUp;
template <IsFrame auto _parent_>
struct LocalHorizontalLocalVertical;
template <IsFrame auto _parent_>
struct RadialInTrackCrossTrack;
template <IsFrame auto _parent_>
struct VelocityNormalBinormal;

} // namespace frames

struct Perifocal;

template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
class DirectionCosineMatrix;

// Platforms
template <class Spacecraft_T>
class Constellation;
template <class Spacecraft_T>
class Plane;
template <class Spacecraft_T>
class Shell;
class Spacecraft;
template <class Payload_T, class PayloadParameters_T>
class Payload;
class PayloadParameters;
template <class Payload_T>
class PayloadPlatform;
class Vehicle;

template <IsFrame auto _frame_>
class InertiaTensor;

// Propagation
class EquationsOfMotion;
class Integrator;
class LambertSolver;
class Event;
class EventDetector;
class Schedule;

class Perturbation;
class ForceModel;
class PerturbingForce;

// Time
class Date;
class Interval;
struct JulianDateClock;

} // namespace astro
} // namespace astrea