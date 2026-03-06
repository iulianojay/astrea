

# File astro.fwd.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**astro.fwd.hpp**](astro_8fwd_8hpp.md)

[Go to the documentation of this file](astro_8fwd_8hpp.md)


```C++

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
```


