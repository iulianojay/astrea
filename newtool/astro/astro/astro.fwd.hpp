#pragma once

class State;

// ELement sets
class OrbitalElements;

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
class FieldOfView;

struct Channel;
class Antenna;
class Sensor;

class GroundStation;

class Constellation;
class Plane;
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
class Time;
