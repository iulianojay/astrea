

# File astro.fwd.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**astro.fwd.hpp**](astro_8fwd_8hpp.md)

[Go to the documentation of this file](astro_8fwd_8hpp.md)


```C++

#pragma once

#include <concepts>

#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

class State;
class StatePartial;
class StateHistory;

// ELement sets
template <IsFrame auto _frame_>
class Cartesian;
template <IsFrame auto _frame_>
class Keplerian;
template <IsFrame auto _frame_>
class Equinoctial;
template <IsFrame auto _frame_>
class CartesianPartial;
template <IsFrame auto _frame_>
class KeplerianPartial;
template <IsFrame auto _frame_>
class EquinoctialPartial;

class TwoLineElements;
class TwoLineElementsPartial;
class GeneralPerturbations;
class OrbitalElements;
class OrbitalElementPartials;

class CartesianStm;
class KeplerianStm;
class EquinoctialStm;
class StateTransitionMatrix;

// Quaternions
template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
class Quaternion;

template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
class QuaternionPartial;

template <RotationSequence sequence, RotationType rotationType, IsFrame auto _in_frame_, IsFrame auto _out_frame_>
class EulerAngles;

template <IsFrame auto _in_frame_, IsFrame auto _ref_frame_>
class AngularVelocities;

template <IsFrame auto _in_frame_, IsFrame auto _ref_frame_>
class AngularAccelerations;

class Attitude;
class AttitudePartials;

// Frames
template <typename Value_T, IsFrame auto _frame_>
struct CartesianVector;

namespace frames {

template <IsFrame auto _parent_>
struct EastNorthUp;
template <IsFrame auto _parent_>
struct LocalHorizontalLocalVertical;
template <IsFrame auto _parent_>
struct RadialInTrackCrossTrack;
template <IsFrame auto _parent_>
struct VelocityNormalBinormal;
template <IsFrame auto _parent_>
struct Perifocal;

} // namespace frames

template <IsFrame auto _in_frame_, IsFrame auto _out_frame_>
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

template <IsFrame auto _frame_>
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

// Time
class Date;
class Interval;
struct JulianDateClock;

} // namespace astro
} // namespace astrea
```


