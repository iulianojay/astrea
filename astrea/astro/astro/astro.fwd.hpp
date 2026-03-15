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

#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

class State;
class StatePartial;
class StateHistory;

// ELement sets
class Cartesian;
class Keplerian;
class Equinoctial;
class TwoLineElements;
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

template <class Value_T, class Frame_T>
class CartesianVector;

template <CelestialBodyId origin, FrameAxis axis>
struct Frame;

template <CelestialBodyId origin, FrameAxis axis>
    requires(origin != CelestialBodyId::UNSET && origin != CelestialBodyId::CUSTOM)
struct InertialFrame;

template <CelestialBodyId origin>
    requires(origin != CelestialBodyId::UNSET)
struct BodyFixedFrame;

template <class Frame_T, FrameAxis axis>
    requires(axis != FrameAxis::ICRF && axis != FrameAxis::J2000 && axis != FrameAxis::BODY_FIXED)
class DynamicFrame;

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

// Propagation
class EquationsOfMotion;
class Integrator;
class LambertSolver;
class Event;
class EventDetector;

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