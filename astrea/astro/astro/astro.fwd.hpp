/**
 * @file astro.fwd.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Forward declarations for the astro module
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

#include <concepts>

#include <astro/frames/frame_concepts.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

class State;
class StatePartial;
class StateHistory;

// ELement sets
template <typename Frame_T>
class Cartesian;
class Keplerian;
class Equinoctial;
class TwoLineElements;
template <typename Frame_T>
class CartesianPartial;
class KeplerianPartial;
class EquinoctialPartial;
class TwoLineElementsPartial;
class GeneralPerturbations;
class OrbitalElements;
class OrbitalElementPartials;

class CartesianStm;
class KeplerianStm;
class EquinoctialStm;
class StateTransitionMatrix;

// Quaternions
template <typename In_Frame_T, typename Out_Frame_T>
class Quaternion;

template <typename In_Frame_T, typename Out_Frame_T>
class QuaternionPartial;

template <RotationSequence sequence, RotationType rotationType, typename In_Frame_T, typename Out_Frame_T>
class EulerAngles;

template <typename In_Frame_T, typename Ref_Frame_T>
class AngularVelocities;

template <typename In_Frame_T, typename Ref_Frame_T>
class AngularAccels;

class Attitude;
class AttitudePartials;

// Frames
template <class Value_T, class Frame_T>
class CartesianVector;

struct LocalHorizontalLocalVertical;
struct RadialInTrackCrossTrack;
struct VelocityNormalBinormal;
struct Perifocal;

template <typename In_Frame_T, typename Out_Frame_T>
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

template <class Frame_T>
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

// Systems
class AstrodynamicsSystem;
class CelestialBody;
struct CelestialBodyParameters;

// Time
class Date;
class Interval;
struct JulianDateClock;

} // namespace astro
} // namespace astrea