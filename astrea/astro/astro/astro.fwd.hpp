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

namespace astrea {
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

template <class Frame_T>
class Frame;
template <class Frame_T>
class InertialFrame;
template <class Frame_T, class Parent_Frame_T>
class RotatingFrame;
template <class Frame_T>
class DynamicFrame;

template <typename In_Frame_T, typename Out_Frame_T>
class DirectionCosineMatrix;

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
} // namespace astrea