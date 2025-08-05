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

template <class Value_T, class Frame_T>
class CartesianVector;

class Frame;
class InertialFrame;
class RotatingFrame;
template <class T>
class BodyFixedFrame;
class FixedOffsetFrame;
template <class T>
class DynamicFrame;

class EarthCenteredInertial;
class EarthCenteredEarthFixed;

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