/**
 * @file astro.fwd.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Forward declarations for the astro module
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <astro/frames/instances.fwd.hpp>
#include <astro/frames/typedefs.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

class State;
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

template <class Value_T, class Frame_T>
class CartesianVector;

class StringLiteral;

template <CelestialBodyId origin, FrameAxis axis>
class Frame;

template <CelestialBodyId origin, FrameAxis axis>
    requires(origin != CelestialBodyId::UNSET && origin != CelestialBodyId::CUSTOM)
class InertialFrame;

template <CelestialBodyId origin>
    requires(origin != CelestialBodyId::UNSET)
class BodyFixedFrame;

template <class Frame_T, FrameAxis axis>
    requires(axis != FrameAxis::ICRF && axis != FrameAxis::J2000 && axis != FrameAxis::BODY_FIXED)
class DynamicFrame;

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

// Time
struct IdPair;
class AccessArray;
class RiseSetArray;

class Date;
class Interval;
struct JulianDateClock;

} // namespace astro
} // namespace astrea