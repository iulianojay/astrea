#pragma once

class State;

// ELement sets
class OrbitalElements;
class Cartesian;
class Keplerian;
class Equinoctial;

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
