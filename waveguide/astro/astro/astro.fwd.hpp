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

namespace waveguide {
namespace astro {

class State;
class StateHistory;

// ELement sets
class Cartesian;
class Keplerian;
class Equinoctial;
class CartesianPartial;
class KeplerianPartial;
class EquinoctialPartial;
class OrbitalElements;

template <class T>
class CartesianVector;

template <class T>
class Frame;
template <class T>
class InertialFrame;
template <class T>
class RotatingFrame;
template <class T>
class BodyFixedFrame;
template <class T>
class FixedOffsetFrame;
template <class T>
class DynamicFrame;

// Platforms
template <class Spacecraft_T>
class Constellation;
template <class Spacecraft_T>
class Plane;
template <class Spacecraft_T>
class Shell;
class Spacecraft;

// Propagation
class EquationsOfMotion;
class Integrator;
class LambertSolver;

// Systems
class AstrodynamicsSystem;
class Barycenter;
class CelestialBody;
class CelestialBodyFactory;

// Time
struct IdPair;
class AccessArray;
class RiseSetArray;

class Date;
class Interval;
struct JulianDateClock;

} // namespace astro
} // namespace waveguide