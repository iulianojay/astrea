#pragma once

class State;

// Time
class Time;
class Date;
class Interval;
struct JulianDateClock;

// Access
struct IdPair;
class AccessArray;
class RiseSetArray;

// Systems
class AstrodynamicsSystem;
class Barycenter;
class CelestialBody;
class CelestialBodyFactory;

// Propagation
class LambertSolver;
class Integrator;
class EquationsOfMotion;

// Platforms
class FieldOfView;
struct Channel;
class Antenna;
class Sensor;
class GroundStation;
class Constellation;
class Plane;
class Shell;
class Spacecraft;

// Element Sets
class ElementSet;
class Cartesian;
class Keplerian;
class Equinoctial;
class OrbitalElements;

template <class T> class Frame;
template <class T> class InertialFrame;
template <class T> class RotatingFrame;
template <class T> class BodyFixedFrame;
template <class T> class FixedOffsetFrame;
template <class T> class DynamicFrame;