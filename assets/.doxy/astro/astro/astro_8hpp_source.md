

# File astro.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**astro.hpp**](astro_8hpp.md)

[Go to the documentation of this file](astro_8hpp.md)


```C++

#pragma once

#include <astro/frames/CartesianVector.hpp>
#include <astro/state/State.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/state/angular_elements/angular_elements.hpp>
#include <astro/state/orbital_data_formats/orbital_data_formats.hpp>
#include <astro/state/orbital_elements/orbital_elements.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/Frame.hpp>
#include <astro/frames/FrameReference.hpp>
#include <astro/frames/dynamic_frames.hpp>
#include <astro/frames/frame_concepts.hpp>
#include <astro/frames/frames.hpp>
#include <astro/frames/transformations.hpp>

#include <astro/frames/instances/LocalHorizontalLocalVertical.hpp>
#include <astro/frames/instances/RadialInTrackCrossTrack.hpp>
#include <astro/frames/instances/VelocityNormalBinormal.hpp>
#include <astro/frames/instances/body_centered_inertial_frames.hpp>
#include <astro/frames/instances/body_fixed_frames.hpp>
#include <astro/frames/instances/defined_rotations.hpp>
#include <astro/frames/types/BodyFixedFrame.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/frames/types/DynamicFrame.hpp>
#include <astro/frames/types/InertialFrame.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/platforms/space/Constellation.hpp>
#include <astro/platforms/space/Plane.hpp>
#include <astro/platforms/space/Shell.hpp>
#include <astro/platforms/thrusters/Thruster.hpp>
#include <astro/platforms/vehicles/NullVehicle.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>

#include <astro/propagation/analytic/LambertSolver.hpp>

#include <astro/propagation/force_models/AtmosphericForce.hpp>
#include <astro/propagation/force_models/Force.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/propagation/force_models/NBodyForce.hpp>
#include <astro/propagation/force_models/OblatenessForce.hpp>
#include <astro/propagation/force_models/SolarRadiationPressure.hpp>

#include <astro/propagation/equations_of_motion/CowellsMethod.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/equations_of_motion/EquinoctialVop.hpp>
#include <astro/propagation/equations_of_motion/J2MeanVop.hpp>
#include <astro/propagation/equations_of_motion/KeplerianVop.hpp>
#include <astro/propagation/equations_of_motion/TwoBody.hpp>

#include <astro/propagation/event_detection/Event.hpp>
#include <astro/propagation/event_detection/EventDetector.hpp>
#include <astro/propagation/event_detection/events/ImpulsiveBurn.hpp>

#include <astro/propagation/numerical/Integrator.hpp>
#include <astro/propagation/numerical/butcher_tableau.hpp>

#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/CelestialBodyParameters.hpp>
#include <astro/systems/planetary_bodies/planetary_bodies.hpp>

#include <astro/time/Date.hpp>
#include <astro/time/Interval.hpp>
#include <astro/time/JulianDateClock.hpp>

#include <astro/types/tuple_hash.hpp>
#include <astro/types/typedefs.hpp>

#include <astro/utilities/conversions.hpp>
#include <astro/utilities/plotting.hpp>
```


