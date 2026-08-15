

# Namespace astrea::astro



[**Namespace List**](namespaces.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md)


















## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**DOP45**](namespaceastrea_1_1astro_1_1DOP45.md) <br> |
| namespace | [**DOP78**](namespaceastrea_1_1astro_1_1DOP78.md) <br> |
| namespace | [**RK45**](namespaceastrea_1_1astro_1_1RK45.md) <br> |
| namespace | [**RKF45**](namespaceastrea_1_1astro_1_1RKF45.md) <br> |
| namespace | [**RKF78**](namespaceastrea_1_1astro_1_1RKF78.md) <br> |
| namespace | [**axes**](namespaceastrea_1_1astro_1_1axes.md) <br> |
| namespace | [**barycenters**](namespaceastrea_1_1astro_1_1barycenters.md) <br> |
| namespace | [**detail**](namespaceastrea_1_1astro_1_1detail.md) <br> |
| namespace | [**frames**](namespaceastrea_1_1astro_1_1frames.md) <br> |
| namespace | [**moons**](namespaceastrea_1_1astro_1_1moons.md) <br> |
| namespace | [**planets**](namespaceastrea_1_1astro_1_1planets.md) <br> |
| namespace | [**plotting**](namespaceastrea_1_1astro_1_1plotting.md) <br> |
| namespace | [**star**](namespaceastrea_1_1astro_1_1star.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md) &lt;\_in\_frame\_, \_ref\_frame\_&gt;<br>_Class representing the angular sequence acceleration, which is the time derivative of the angular sequence velocity._  |
| class | [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) &lt;\_in\_frame\_, \_ref\_frame\_&gt;<br>_Class representing a sequence of angular velocities (either Euler or Tait-Bryan) for attitude transformations between frames._  |
| class | [**AtmosphericForce**](classastrea_1_1astro_1_1AtmosphericForce.md) <br>_Class to compute the atmospheric force on a vehicle._  |
| class | [**Attitude**](classastrea_1_1astro_1_1Attitude.md) <br>_Class representing a set of orientation._  |
| class | [**AttitudePartials**](classastrea_1_1astro_1_1AttitudePartials.md) <br>_Class representing partial derivatives of orientation._  |
| struct | [**Axis**](structastrea_1_1astro_1_1Axis.md) &lt;mp\_units::symbol\_text, auto...&gt;<br> |
| struct | [**Axis&lt; \_name\_ &gt;**](structastrea_1_1astro_1_1Axis_3_01__name___01_4.md) &lt;\_name\_&gt;<br> |
| struct | [**Axis&lt; \_name\_, \_parent\_ &gt;**](structastrea_1_1astro_1_1Axis_3_01__name___00_01__parent___01_4.md) &lt;\_name\_, \_parent\_&gt;<br> |
| struct | [**Barycenter**](structastrea_1_1astro_1_1Barycenter.md) &lt;mp\_units::symbol\_text, auto...&gt;<br> |
| struct | [**Barycenter&lt; \_name\_ &gt;**](structastrea_1_1astro_1_1Barycenter_3_01__name___01_4.md) &lt;\_name\_&gt;<br>_No parent, no members._  |
| struct | [**Barycenter&lt; \_name\_, \_parent\_ &gt;**](structastrea_1_1astro_1_1Barycenter_3_01__name___00_01__parent___01_4.md) &lt;\_name\_, \_parent\_&gt;<br>_With parent, no members._  |
| struct | [**BarycentricCoordinateTimeClock**](structastrea_1_1astro_1_1BarycentricCoordinateTimeClock.md) <br>_A clock implementation for Barycentric Coordinate Time (TCB)._  |
| struct | [**BarycentricDynamicalTimeClock**](structastrea_1_1astro_1_1BarycentricDynamicalTimeClock.md) <br>_A clock implementation for Barycentric Dynamical Time (TDB)._  |
| struct | [**BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) &lt;\_name\_, \_origin\_, \_axis\_&gt;<br>_Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._  |
| class | [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) &lt;\_frame\_&gt;<br>_Class representing a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector in astrodynamics._ |
| class | [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) &lt;\_frame\_&gt;<br>_Class representing a partial derivative of a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._ |
| struct | [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) &lt;class Value\_T, \_frame\_&gt;<br>_Class representing a 3D vector in_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _coordinates._ |
| struct | [**CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) &lt;\_name\_, \_parent\_&gt;<br>[_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._ |
| struct | [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) <br>_Structure to hold the parameters of a celestial body._  |
| struct | [**CelestialBodyTypePack**](structastrea_1_1astro_1_1CelestialBodyTypePack.md) &lt;typename...&gt;<br>_Type-list used to attach member bodies to a_ [_**Barycenter**_](structastrea_1_1astro_1_1Barycenter.md) _._ |
| class | [**CircularRestrictedThreeBodyProblem**](classastrea_1_1astro_1_1CircularRestrictedThreeBodyProblem.md) <br>_Class implementing the Circular Restricted Three-Body Problem equations of motion._  |
| class | [**Constellation**](classastrea_1_1astro_1_1Constellation.md) &lt;class Spacecraft\_T&gt;<br>_A_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _is a collection of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _, organized into Shells and/or Planes._ |
| class | [**CowellsMethod**](classastrea_1_1astro_1_1CowellsMethod.md) <br>_Class implementing Cowell's method for equations of motion._  |
| class | [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) &lt;\_body\_&gt;<br>_Class representing a_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector in astrodynamics._ |
| class | [**Date**](classastrea_1_1astro_1_1Date.md) <br>_Class representing a date in the astrea astro library._  |
| struct | [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) &lt;typename Value\_T, \_in\_frame\_, \_out\_frame\_&gt;<br>_Class representing a 3x3 matrix, used for matrices and their rates/accelerations._  |
| class | [**Deorbit**](classastrea_1_1astro_1_1Deorbit.md) <br>_A class representing a deorbit_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class is used as a placeholder for Events that do not have a defined state or mass._ |
| struct | [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &lt;\_in\_frame\_, \_out\_frame\_&gt;<br>_Class representing a direction cosine matrix (DCM) for transforming vectors between state/frames._  |
| class | [**DirectionCosineMatrixAccel**](structastrea_1_1astro_1_1DirectionCosineMatrixAccel.md) &lt;\_in\_frame\_, \_out\_frame\_&gt;<br>_Class representing a direction cosine matrix (DCM) for transforming vectors between state/frames._  |
| struct | [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md) &lt;\_in\_frame\_, \_out\_frame\_&gt;<br>_Class representing a direction cosine matrix (DCM) for transforming vectors between state/frames._  |
| struct | [**DynamicAxis**](structastrea_1_1astro_1_1DynamicAxis.md) <br> |
| struct | [**DynamicFrame**](structastrea_1_1astro_1_1DynamicFrame.md) &lt;typename Self, \_parent\_, \_self\_&gt;<br>_Base class for all dynamic state/frames._  |
| struct | [**DynamicOrigin**](structastrea_1_1astro_1_1DynamicOrigin.md) <br> |
| class | [**EquationsOfMotion**](classastrea_1_1astro_1_1EquationsOfMotion.md) <br>_Base class for equations of motion in astrodynamics._  |
| class | [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) &lt;\_frame\_&gt;<br>_The_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _class represents the equinoctial orbital elements._ |
| class | [**EquinoctialPartial**](classastrea_1_1astro_1_1EquinoctialPartial.md) &lt;\_frame\_&gt;<br>_Class representing a partial derivative of an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._ |
| class | [**EquinoctialVop**](classastrea_1_1astro_1_1EquinoctialVop.md) <br>_Class implementing the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _VOP equations of motion._ |
| class | [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) &lt;sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_&gt;<br>_Class representing a sequence of angles (either Euler or Tait-Bryan) for attitude transformations between frames._  |
| class | [**Event**](classastrea_1_1astro_1_1Event.md) <br>_A class representing a_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class serves as a base for user-defined Events and provides a common interface._ |
| class | [**EventDetector**](classastrea_1_1astro_1_1EventDetector.md) <br>_A class for detecting events in the astrea astro platform._  |
| struct | [**ExtraRegisteredFrames**](structastrea_1_1astro_1_1ExtraRegisteredFrames.md) &lt;typename&gt;<br>_Trait that users specialize to register additional_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _frames._ |
| struct | [**FixedOffsetAxis**](structastrea_1_1astro_1_1FixedOffsetAxis.md) &lt;\_parent\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_&gt;<br> |
| struct | [**FixedOffsetFrame**](structastrea_1_1astro_1_1FixedOffsetFrame.md) &lt;auto...&gt;<br>_Class representing a fixed offset frame, which is defined by a fixed spatial and/or angular offset from a parent frame._  |
| struct | [**FixedOffsetFrame&lt; \_name\_, \_parent\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__name___00_01__parent___00_01__phi___00_01__theta96154ff31cb8eb7d055f0d1372ec2a1e.md) &lt;\_name\_, \_parent\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args&gt;<br>_Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for an angular offset with no spatial misalignment that lets the name be specified._ |
| struct | [**FixedOffsetFrame&lt; \_name\_, \_parent\_, \_x\_, \_y\_, \_z\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__name___00_01__parent___00_01__x___00_01__y___00_01__z___00_01Args_8_8_8_01_4.md) &lt;\_name\_, \_parent\_, \_x\_, \_y\_, \_z\_, Args&gt;<br>_Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for a spatial offset with no angular misalignment that lets the name be specified._ |
| struct | [**FixedOffsetFrame&lt; \_name\_, \_parent\_, \_x\_, \_y\_, \_z\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__name___00_01__parent___00_01__x___00_01__y___00_682f817510ea200b9f1d77fc37d45a92.md) &lt;\_name\_, \_parent\_, \_x\_, \_y\_, \_z\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args&gt;<br>_Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for a combined spatial and angular offset that lets the name be specified._ |
| struct | [**FixedOffsetFrame&lt; \_parent\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__parent___00_01__phi___00_01__theta___00_01__psi_9e091a834f5483531831878cbc7beda5.md) &lt;\_parent\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args&gt;<br>_Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for a pure angular offset (no spatial offset)._ |
| struct | [**FixedOffsetFrame&lt; \_parent\_, \_x\_, \_y\_, \_z\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__parent___00_01__x___00_01__y___00_01__z___00_01Args_8_8_8_01_4.md) &lt;\_parent\_, \_x\_, \_y\_, \_z\_, Args&gt;<br>_Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for a pure spatial offset (no angular misalignment)._ |
| struct | [**FixedOffsetFrame&lt; \_parent\_, \_x\_, \_y\_, \_z\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__parent___00_01__x___00_01__y___00_01__z___00_01_3721297a9a90e06cc0beab0e7a99da8d.md) &lt;\_parent\_, \_x\_, \_y\_, \_z\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args&gt;<br>_Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for a combined spatial and angular offset._ |
| struct | [**FixedOffsetOrigin**](structastrea_1_1astro_1_1FixedOffsetOrigin.md) &lt;\_parent\_, \_x\_, \_y\_, \_z\_&gt;<br> |
| class | [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) <br>_Class to manage multiple force models and compute the total force on a vehicle._  |
| struct | [**Frame**](structastrea_1_1astro_1_1Frame.md) &lt;mp\_units::symbol\_text, auto...&gt;<br> |
| struct | [**Frame&lt; \_name\_, \_origin\_, \_axis\_ &gt;**](structastrea_1_1astro_1_1Frame_3_01__name___00_01__origin___00_01__axis___01_4.md) &lt;\_name\_, \_origin\_, \_axis\_&gt;<br>[_**Frame**_](structastrea_1_1astro_1_1Frame.md) _with name, origin, and axis (no parent)._ |
| struct | [**Frame&lt; \_name\_, \_origin\_, \_axis\_, \_parent\_ &gt;**](structastrea_1_1astro_1_1Frame_3_01__name___00_01__origin___00_01__axis___00_01__parent___01_4.md) &lt;\_name\_, \_origin\_, \_axis\_, \_parent\_&gt;<br>[_**Frame**_](structastrea_1_1astro_1_1Frame.md) _with name, origin, axis, and parent._ |
| struct | [**GeneralPerturbations**](structastrea_1_1astro_1_1GeneralPerturbations.md) <br>[_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _structure representing a Ground Position (GP) object from SpaceTrack._ |
| class | [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) &lt;\_body\_&gt;<br>_Class representing a_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector in astrodynamics._ |
| struct | [**GeocentricAxes**](structastrea_1_1astro_1_1GeocentricAxes.md) &lt;\_name\_&gt;<br> |
| struct | [**GeocentricCoordinateTimeClock**](structastrea_1_1astro_1_1GeocentricCoordinateTimeClock.md) <br>_A clock implementation for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _Coordinate Time (TCG)._ |
| class | [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) &lt;\_body\_&gt;<br>_Class representing a_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector in astrodynamics._ |
| class | [**ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md) <br>_A class representing an impulsive burn_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _. It triggers when the true anomaly wraps around (i.e. at perigee), and applies the total impulsive delta-v from all thrusters to the vehicle in the velocity direction._ |
| class | [**InertiaTensor**](classastrea_1_1astro_1_1InertiaTensor.md) &lt;\_frame\_&gt;<br>_A class representing an inertia matrix in the astrea astro platform._  |
| class | [**Integrator**](classastrea_1_1astro_1_1Integrator.md) <br>[_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _class for numerical propagation of orbital mechanics problems._ |
| struct | [**IntegratorSettings**](structastrea_1_1astro_1_1IntegratorSettings.md) <br> |
| class | [**Interval**](classastrea_1_1astro_1_1Interval.md) <br>_Represents a time interval with a start and end time._  |
| class | [**J2MeanVop**](classastrea_1_1astro_1_1J2MeanVop.md) <br>_Class implementing the J2 Mean VOP equations of motion._  |
| struct | [**JplEphemerisTable**](structastrea_1_1astro_1_1JplEphemerisTable.md) <br>_Base class for any JPL_ [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _table._ |
| struct | [**JulianDateClock**](structastrea_1_1astro_1_1JulianDateClock.md) <br>_A clock implementation for Julian Dates._  |
| class | [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) &lt;\_frame\_&gt;<br>_The_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _class represents the_[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _orbital elements._ |
| class | [**KeplerianPartial**](classastrea_1_1astro_1_1KeplerianPartial.md) &lt;\_frame\_&gt;<br>_Class representing a partial derivative of a_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._ |
| class | [**KeplerianVop**](classastrea_1_1astro_1_1KeplerianVop.md) <br>_Class implementing the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _VOP equations of motion._ |
| class | [**LambertSolver**](classastrea_1_1astro_1_1LambertSolver.md) <br>_Class for solving Lambert's problem._  |
| class | [**LegendreCache**](classastrea_1_1astro_1_1LegendreCache.md) &lt;\_body\_, \_degree\_, \_order\_&gt;<br>_Class to cache Legendre polynomial coefficients for a given celestial_ _body_ _, degree, and order._ |
| class | [**NBodyForce**](classastrea_1_1astro_1_1NBodyForce.md) &lt;bodies&gt;<br>_Class to compute the gravitational force due to multiple celestial bodies._  |
| class | [**NullEvent**](classastrea_1_1astro_1_1NullEvent.md) <br>_A class representing a null_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class is used as a placeholder for Events that do not have a defined state or mass._ |
| class | [**NullVehicle**](classastrea_1_1astro_1_1NullVehicle.md) <br>_A class representing a null vehicle in the astrea astro platform. This class is used as a placeholder for vehicles that do not have a defined state or mass._  |
| class | [**OblatenessForce**](classastrea_1_1astro_1_1OblatenessForce.md) &lt;\_body\_, \_degree\_, \_order\_&gt;<br>_Class to compute the gravitational force due to the oblateness of a celestial_ _body_ _._ |
| class | [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) <br>_Class representing partial derivatives of orbital elements._  |
| class | [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) <br>_Class representing a set of orbital elements._  |
| struct | [**Origin**](structastrea_1_1astro_1_1Origin.md) &lt;mp\_units::symbol\_text, auto...&gt;<br> |
| struct | [**Origin&lt; \_name\_ &gt;**](structastrea_1_1astro_1_1Origin_3_01__name___01_4.md) &lt;\_name\_&gt;<br> |
| struct | [**Origin&lt; \_name\_, \_parent\_ &gt;**](structastrea_1_1astro_1_1Origin_3_01__name___00_01__parent___01_4.md) &lt;\_name\_, \_parent\_&gt;<br> |
| class | [**Payload**](classastrea_1_1astro_1_1Payload.md) &lt;class Payload\_T, class PayloadParameters\_T&gt;<br>[_**Payload**_](classastrea_1_1astro_1_1Payload.md) _class representing a payload on a platform._ |
| class | [**PayloadParameters**](classastrea_1_1astro_1_1PayloadParameters.md) <br>_Class for storing and managing payload parameters._  |
| class | [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) &lt;class Payload\_T&gt;<br>_The_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _class represents a platform that can have payloads attached to it. It provides methods to attach payloads and retrieve the list of attached payloads._ |
| struct | [**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) <br>_Struct to hold the results of a perturbation force computation, including both acceleration and torque._  |
| class | [**PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md) <br>_Abstract base class for force models in astrodynamics._  |
| class | [**Plane**](classastrea_1_1astro_1_1Plane.md) &lt;class Spacecraft\_T&gt;<br>_A_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _is a collection of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _that share the same orbital elements._ |
| class | [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md) &lt;\_in\_frame\_, \_out\_frame\_&gt;<br>_Class representing a quaternion for attitude rotations between frames._  |
| class | [**QuaternionPartial**](classastrea_1_1astro_1_1QuaternionPartial.md) &lt;\_in\_frame\_, \_out\_frame\_&gt;<br>_Class representing the partial derivative of a quaternion with respect to time, used for integration._  |
| struct | [**ReferenceAxes**](structastrea_1_1astro_1_1ReferenceAxes.md) &lt;\_name\_&gt;<br> |
| class | [**Schedule**](classastrea_1_1astro_1_1Schedule.md) <br>_A class representing a_ [_**Schedule**_](classastrea_1_1astro_1_1Schedule.md) _in the astrea astro library. The_[_**Schedule**_](classastrea_1_1astro_1_1Schedule.md) _is responsible for scheduling and managing Events that are set to trigger at specific Dates during propagation._ |
| class | [**Shell**](classastrea_1_1astro_1_1Shell.md) &lt;class Spacecraft\_T&gt;<br>_A_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _is a collection of planes, each containing a set of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _. It is used to represent sub-constellations of satellites in orbit._ |
| class | [**SolarRadiationPressure**](classastrea_1_1astro_1_1SolarRadiationPressure.md) <br>_Class to compute the solar radiation pressure force on a spacecraft._  |
| class | [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) <br>_A class representing a spacecraft in the astrea astro platform. This class encapsulates the properties of a spacecraft, including its mass, dynamic coefficients, and surface areas._  |
| class | [**Spherical**](classastrea_1_1astro_1_1Spherical.md) &lt;\_body\_&gt;<br>_Class representing a_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector in astrodynamics._ |
| class | [**State**](classastrea_1_1astro_1_1State.md) <br>_Class representing the state of an astronomical object. This class encapsulates the orbital elements, epoch, and the astrodynamics system that the state belongs to. It also optionally includes the attitude of the object as a quaternion._  |
| class | [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) <br>_Class to manage the history of states for an object over date._  |
| class | [**StatePartial**](classastrea_1_1astro_1_1StatePartial.md) <br> |
| class | [**StateTransitionMatrix**](classastrea_1_1astro_1_1StateTransitionMatrix.md) <br> |
| struct | [**StepWatcher**](structastrea_1_1astro_1_1StepWatcher.md) <br>_Function wrapper class for watching the state of the integrator at each step. This can be used for plotting or logging the state during propagation._  |
| struct | [**SynodicAxis**](structastrea_1_1astro_1_1SynodicAxis.md) &lt;\_primary\_, \_secondary\_&gt;<br>[_**Axis**_](structastrea_1_1astro_1_1Axis.md) _defined by the line connecting two celestial bodies and the plane of motion of the secondary around the primary._ |
| struct | [**SynodicFrame**](structastrea_1_1astro_1_1SynodicFrame.md) &lt;\_name\_, \_origin\_, \_primary\_, \_secondary\_&gt;<br>_Synodic frame defined by the line connecting two celestial bodies and the plane of motion of the secondary around the primary._  |
| struct | [**TerrestrialTimeClock**](structastrea_1_1astro_1_1TerrestrialTimeClock.md) <br>_A clock implementation for Terrestrial Time (TT)._  |
| class | [**Thruster**](classastrea_1_1astro_1_1Thruster.md) <br>[_**Thruster**_](classastrea_1_1astro_1_1Thruster.md) _class representing a thruster on a platform._ |
| class | [**ThrusterParameters**](classastrea_1_1astro_1_1ThrusterParameters.md) <br>_Class for storing and managing thruster parameters._  |
| struct | [**TopocentricFrame**](structastrea_1_1astro_1_1TopocentricFrame.md) &lt;\_name\_, \_parent\_, \_lat\_, \_lon\_, \_alt\_&gt;<br>_A frame that is topocentric to a given body, defined relative to some body-fixed frame by a specific latitude, longitude, and altitude._  |
| class | [**TurnThrustersOff**](classastrea_1_1astro_1_1TurnThrustersOff.md) <br>_A class representing a_ [_**TurnThrustersOff**_](classastrea_1_1astro_1_1TurnThrustersOff.md) __[_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class is used as a placeholder for Events that do not have a defined state or mass._ |
| class | [**TurnThrustersOn**](classastrea_1_1astro_1_1TurnThrustersOn.md) <br>_A class representing a_ [_**TurnThrustersOn**_](classastrea_1_1astro_1_1TurnThrustersOn.md) __[_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class is used as a placeholder for Events that do not have a defined state or mass._ |
| class | [**TwoBody**](classastrea_1_1astro_1_1TwoBody.md) <br>_Class implementing the Two Body equations of motion._  |
| class | [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) <br>_Class representing the two-line element (TLE) format for orbital data._  |
| class | [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) <br>_A class representing a vehicle in the astrea astro platform. This class serves as a base for user-defined vehicles and provides a common interface._  |
| struct | [**is\_cartesian\_vector**](structastrea_1_1astro_1_1is__cartesian__vector.md) &lt;class T&gt;<br> |
| struct | [**is\_cartesian\_vector&lt; CartesianVector&lt; Value\_T, frame &gt; &gt;**](structastrea_1_1astro_1_1is__cartesian__vector_3_01CartesianVector_3_01Value__T_00_01frame_01_4_01_4.md) &lt;class Value\_T, frame&gt;<br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Acceleration, frame &gt; | [**AccelerationVector**](#typedef-accelerationvector)  <br>_Type alias for a vector representing acceleration in 3D space._  |
| typedef std::tuple&lt; std::decay\_t&lt; decltype(frames::primary)&gt; &gt; | [**AutomaticallyRegisteredFrames**](#typedef-automaticallyregisteredframes)  <br>_The built-in set of_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _frames known to astrea._ |
| typedef [**BarycentricCoordinateTimeClock::time\_point**](structastrea_1_1astro_1_1BarycentricCoordinateTimeClock.md#typedef-time_point) | [**BarycentricCoordinateTime**](#typedef-barycentriccoordinatetime)  <br>_A type alias for Barycentric Coordinate Time time points._  |
| typedef std::chrono::time\_point&lt; [**BarycentricCoordinateTimeClock**](structastrea_1_1astro_1_1BarycentricCoordinateTimeClock.md), Duration &gt; | [**BarycentricCoordinateTimePoint**](#typedef-barycentriccoordinatetimepoint)  <br>_A time point type for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _Coordinate Time, using the_[_**BarycentricCoordinateTimeClock**_](structastrea_1_1astro_1_1BarycentricCoordinateTimeClock.md) _._ |
| typedef [**BarycentricDynamicalTimeClock::time\_point**](structastrea_1_1astro_1_1BarycentricDynamicalTimeClock.md#typedef-time_point) | [**BarycentricDynamicalTime**](#typedef-barycentricdynamicaltime)  <br>_A type alias for Barycentric Dynamical Time time points._  |
| typedef std::chrono::time\_point&lt; [**BarycentricDynamicalTimeClock**](structastrea_1_1astro_1_1BarycentricDynamicalTimeClock.md), Duration &gt; | [**BarycentricDynamicalTimePoint**](#typedef-barycentricdynamicaltimepoint)  <br>_A time point type for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _Coordinate Time, using the_[_**BarycentricDynamicalTimeClock**_](structastrea_1_1astro_1_1BarycentricDynamicalTimeClock.md) _._ |
| typedef [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md)&lt; [**frames::dynamic::body**](structastrea_1_1astro_1_1frames_1_1dynamic_1_1body.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1frames_1_1earth_1_1icrf.md) &gt; | [**BodyAngleVelocities**](#typedef-bodyanglevelocities)  <br>_Type alias for a ICRF-&gt;body angle sequence velocity._  |
| typedef [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; RotationSequence::ZXZ, RotationType::INTRINSIC, [**frames::dynamic::body**](structastrea_1_1astro_1_1frames_1_1dynamic_1_1body.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1frames_1_1earth_1_1icrf.md) &gt; | [**BodyAngles**](#typedef-bodyangles)  <br>_Type alias for a ICRF-&gt;body angle sequence._  |
| typedef [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md)&lt; [**frames::dynamic::body**](structastrea_1_1astro_1_1frames_1_1dynamic_1_1body.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1frames_1_1earth_1_1icrf.md) &gt; | [**BodyAngularAcceleration**](#typedef-bodyangularacceleration)  <br>_Type alias for a ICRF-&gt;body angle sequence acceleration._  |
| typedef [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; [**frames::dynamic::body**](structastrea_1_1astro_1_1frames_1_1dynamic_1_1body.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1frames_1_1earth_1_1icrf.md) &gt; | [**BodyQuaternion**](#typedef-bodyquaternion)  <br>_Type alias for a ICRF-&gt;body quaternion._  |
| typedef [**QuaternionPartial**](classastrea_1_1astro_1_1QuaternionPartial.md)&lt; [**frames::dynamic::body**](structastrea_1_1astro_1_1frames_1_1dynamic_1_1body.md), [**frames::earth::icrf**](structastrea_1_1astro_1_1frames_1_1earth_1_1icrf.md) &gt; | [**BodyQuaternionRate**](#typedef-bodyquaternionrate)  <br>_Type alias for a ICRF-&gt;body quaternion derivative._  |
| typedef [**CircularRestrictedThreeBodyProblem**](classastrea_1_1astro_1_1CircularRestrictedThreeBodyProblem.md) | [**CR3BP**](#typedef-cr3bp)  <br> |
| enum [**EnumType**](namespaceastrea_1_1astro.md#typedef-enumtype) | [**CelestialBodyType**](#enum-celestialbodytype)  <br>_Celestial body types._  |
| typedef std::tuple&lt; mp\_units::quantity&lt; mp\_units::si::unit\_symbols::rad/(astrea::units::unit\_symbols::jc \*astrea::units::unit\_symbols::jc)&gt;, mp\_units::quantity&lt; mp\_units::si::unit\_symbols::rad &gt;, mp\_units::quantity&lt; mp\_units::si::unit\_symbols::rad &gt;, mp\_units::quantity&lt; mp\_units::si::unit\_symbols::rad/astrea::units::unit\_symbols::jc &gt; &gt; | [**CoefficientPack**](#typedef-coefficientpack)  <br>_Type alias for a tuple of linear expansion coefficients._  |
| enum  | [**Coordinate**](#enum-coordinate)  <br> |
| typedef [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**DCM**](#typedef-dcm)  <br>_Alias for_ [_**DirectionCosineMatrix**_](classastrea_1_1astro_1_1DirectionCosineMatrix.md) _with a specific output frame type._ |
| typedef [**DirectionCosineMatrixAccel**](structastrea_1_1astro_1_1DirectionCosineMatrixAccel.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**DcmAccel**](#typedef-dcmaccel)  <br>_Alias for_ [_**DirectionCosineMatrixAccel**_](structastrea_1_1astro_1_1DirectionCosineMatrixAccel.md) _with a specific output frame type._ |
| typedef [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt; \_in\_frame\_, \_out\_frame\_ &gt; | [**DcmRate**](#typedef-dcmrate)  <br>_Alias for_ [_**DirectionCosineMatrixRate**_](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md) _with a specific output frame type._ |
| typedef [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Unitless, frame &gt; | [**Direction**](#typedef-direction)  <br>_Type alias for a vector representing unit vectors in 3D space._  |
| typedef uint32\_t | [**EnumType**](#typedef-enumtype)  <br>_Type definition for enumeration types._  |
| typedef [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Force, frame &gt; | [**ForceVector**](#typedef-forcevector)  <br>_Type alias for a vector representing force vectors in 3D space._  |
| enum [**EnumType**](namespaceastrea_1_1astro.md#typedef-enumtype) | [**FrameAxis**](#enum-frameaxis)  <br>_Reference frames axes._  |
| typedef std::chrono::time\_point&lt; [**GeocentricCoordinateTimeClock**](structastrea_1_1astro_1_1GeocentricCoordinateTimeClock.md), Duration &gt; | [**GeocentricCoordinateDateTime**](#typedef-geocentriccoordinatedatetime)  <br>_A time point type for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _Coordinate Time, using the_[_**GeocentricCoordinateTimeClock**_](structastrea_1_1astro_1_1GeocentricCoordinateTimeClock.md) _._ |
| typedef [**GeocentricCoordinateTimeClock::time\_point**](structastrea_1_1astro_1_1GeocentricCoordinateTimeClock.md#typedef-time_point) | [**GeocentricCoordinateTime**](#typedef-geocentriccoordinatetime)  <br>_A type alias for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _Coordinate Time time points._ |
| typedef [**JulianDateClock::time\_point**](structastrea_1_1astro_1_1JulianDateClock.md#typedef-time_point) | [**JulianDate**](#typedef-juliandate)  <br>_A type alias for Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _time points._ |
| typedef std::chrono::time\_point&lt; [**JulianDateClock**](structastrea_1_1astro_1_1JulianDateClock.md), Duration &gt; | [**JulianDateTime**](#typedef-juliandatetime)  <br>_A time point type for Julian Dates, using the_ [_**JulianDateClock**_](structastrea_1_1astro_1_1JulianDateClock.md) _._ |
| typedef typename [**detail::tuple\_to\_variant**](structastrea_1_1astro_1_1detail_1_1tuple__to__variant.md)&lt; typename [**detail::multi\_tuple\_cat**](structastrea_1_1astro_1_1detail_1_1multi__tuple__cat.md)&lt; typename [**detail::apply\_nttp\_template**](structastrea_1_1astro_1_1detail_1_1apply__nttp__template.md)&lt; [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md), [**detail::AllRegisteredFrames**](namespaceastrea_1_1astro_1_1detail.md#typedef-allregisteredframes) &gt;::type, typename [**detail::apply\_nttp\_template**](structastrea_1_1astro_1_1detail_1_1apply__nttp__template.md)&lt; FrameIndexedTypes, [**detail::AllRegisteredFrames**](namespaceastrea_1_1astro_1_1detail.md#typedef-allregisteredframes) &gt;::type... &gt;::type &gt;::type | [**OrbitalElementPartialVariant**](#typedef-orbitalelementpartialvariant)  <br> |
| typedef typename [**detail::tuple\_to\_variant**](structastrea_1_1astro_1_1detail_1_1tuple__to__variant.md)&lt; typename [**detail::multi\_tuple\_cat**](structastrea_1_1astro_1_1detail_1_1multi__tuple__cat.md)&lt; typename [**detail::apply\_nttp\_template**](structastrea_1_1astro_1_1detail_1_1apply__nttp__template.md)&lt; [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md), [**detail::AllRegisteredFrames**](namespaceastrea_1_1astro_1_1detail.md#typedef-allregisteredframes) &gt;::type, typename [**detail::apply\_nttp\_template**](structastrea_1_1astro_1_1detail_1_1apply__nttp__template.md)&lt; FrameIndexedTypes, [**detail::AllRegisteredFrames**](namespaceastrea_1_1astro_1_1detail.md#typedef-allregisteredframes) &gt;::type... &gt;::type &gt;::type | [**OrbitalElementVariant**](#typedef-orbitalelementvariant)  <br>_Variant of all frame-indexed element types expanded over every registered frame._  |
| typedef [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Distance, frame &gt; | [**RadiusVector**](#typedef-radiusvector)  <br>_Type alias for a vector representing a radius in 3D space._  |
| enum  | [**RotationSequence**](#enum-rotationsequence)  <br>_Enum representing possible Euler angle sequences._  |
| enum  | [**RotationType**](#enum-rotationtype)  <br>_Enum representing whether the rotation sequence is intrinsic or extrinsic._  |
| enum [**EnumType**](namespaceastrea_1_1astro.md#typedef-enumtype) | [**StepMethod**](#enum-stepmethod)  <br>_Enumeration for different Runge-Kutta stepper methods._  |
| enum [**EnumType**](namespaceastrea_1_1astro.md#typedef-enumtype) | [**SystemCenter**](#enum-systemcenter)  <br>_System center types._  |
| typedef std::chrono::time\_point&lt; [**TerrestrialTimeClock**](structastrea_1_1astro_1_1TerrestrialTimeClock.md), Duration &gt; | [**TerrestrialDateTime**](#typedef-terrestrialdatetime)  <br>_A time point type for Terrestrial Time, using the_ [_**TerrestrialTimeClock**_](structastrea_1_1astro_1_1TerrestrialTimeClock.md) _._ |
| typedef [**TerrestrialTimeClock::time\_point**](structastrea_1_1astro_1_1TerrestrialTimeClock.md#typedef-time_point) | [**TerrestrialTime**](#typedef-terrestrialtime)  <br>_A type alias for Terrestrial Time time points._  |
| typedef [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)&lt; [**Thruster**](classastrea_1_1astro_1_1Thruster.md) &gt; | [**ThrusterPlatform**](#typedef-thrusterplatform)  <br>[_**Thruster**_](classastrea_1_1astro_1_1Thruster.md) _platform type definition._ |
| typedef [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Moment, frame &gt; | [**TorqueVector**](#typedef-torquevector)  <br>_Type alias for a vector representing moment vectors in 3D space._  |
| typedef [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Velocity, frame &gt; | [**VelocityVector**](#typedef-velocityvector)  <br>_Type alias for a vector representing velocity in 3D space._  |
| typedef std::remove\_cv\_t&lt; std::remove\_reference\_t&lt; T &gt; &gt; | [**remove\_cv\_ref**](#typedef-remove_cv_ref)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  constexpr bool | [**always\_false**](#variable-always_false)   = `false`<br>_A helper variable template that is always false, used for static\_asserts in templates that should never be instantiated._  |
|  constexpr bool | [**is\_cartesian\_vector\_v**](#variable-is_cartesian_vector_v)   = `[**is\_cartesian\_vector**](structastrea_1_1astro_1_1is__cartesian__vector.md)&lt;T&gt;::value`<br> |


## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  const [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; astro::frames::dynamic::ric &gt; | [**CENTER**](#variable-center)   = `/* multi line expression */`<br> |
|  const size\_t | [**DEFAULT\_SHELL\_ID**](#variable-default_shell_id)   = `SIZE\_MAX`<br> |
|  constexpr mp\_units::quantity\_point | [**J2K**](#variable-j2k)   = `J2000`<br>_A constant representing the J2000 epoch in Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _format, used as a reference point._ |
|  constexpr mp\_units::quantity\_point | [**MJDStart**](#variable-mjdstart)   = `MJD0`<br>_A constant representing the start of the Modified Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _epoch._ |
|  const [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; astro::frames::dynamic::ric &gt; | [**NADIR\_RIC**](#variable-nadir_ric)   = `/* multi line expression */`<br> |
|  const [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; astro::frames::dynamic::ric &gt; | [**RADIAL\_RIC**](#variable-radial_ric)   = `/* multi line expression */`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr bool | [**all\_have\_valid\_transformation**](#function-all_have_valid_transformation) () <br> |
|  constexpr bool | [**all\_have\_valid\_transformation\_impl**](#function-all_have_valid_transformation_impl) (std::index\_sequence&lt; I... &gt;) <br> |
|  constexpr Distance | [**calculate\_geocentric\_radius**](#function-calculate_geocentric_radius) (const Angle & lat) <br>_Calculate the geocentric radius given latitude and Earth's radii._  |
|  consteval bool | [**check\_all\_bodies\_share\_a\_parent**](#function-check_all_bodies_share_a_parent) () <br>_Checks if all bodies in the pack share the same parent._  |
|  consteval auto | [**compose\_name**](#function-compose_name) () <br>_Helper function to compose the name of a_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _based on its parent frame's name and its offset values. This generates a descriptive name that includes the parent frame and the specific offsets applied._ |
|  consteval auto | [**compose\_name**](#function-compose_name) () <br>_Helper function to compose the name of a_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _with both spatial and angular offsets based on its parent frame's name and its offset values. This generates a descriptive name that includes the parent frame and the specific spatial and angular offsets applied._ |
|  std::tuple&lt; Distance, Angle, Distance &gt; | [**convert\_body\_fixed\_to\_cylindrical**](#function-convert_body_fixed_to_cylindrical) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; & rFixed) <br>_Convert a body-fixed radius vector to cylindrical coordinates._  |
|  constexpr std::tuple&lt; Angle, Angle, Distance &gt; | [**convert\_body\_fixed\_to\_geocentric**](#function-convert_body_fixed_to_geocentric) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; frame &gt; & rEcef) <br>_Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates._  |
|  std::tuple&lt; Angle, Angle, Distance &gt; | [**convert\_body\_fixed\_to\_geodetic**](#function-convert_body_fixed_to_geodetic) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; frame &gt; & rBodyFixed) <br>_Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates._  |
|  std::tuple&lt; Distance, Angle, Angle &gt; | [**convert\_body\_fixed\_to\_spherical**](#function-convert_body_fixed_to_spherical) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; & rFixed) <br>_Convert a body-fixed radius vector to spherical coordinates._  |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; | [**convert\_cylindrical\_to\_body\_fixed**](#function-convert_cylindrical_to_body_fixed) (const Distance & range, const Angle & azimuth, const Distance & elevation) <br>_Convert cylindrical coordinates to a body-fixed radius vector._  |
|  Angle | [**convert\_eccentric\_anomaly\_to\_mean\_anomaly**](#function-convert_eccentric_anomaly_to_mean_anomaly) (const Angle & ea, const Unitless ecc) <br>_Convert the eccentric anomaly to the mean anomaly._  |
|  constexpr [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; | [**convert\_geocentric\_to\_body\_fixed**](#function-convert_geocentric_to_body_fixed) (const Angle & lat, const Angle & lon, const Distance & alt) <br>_Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates._  |
|  constexpr [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; frame &gt; | [**convert\_geodetic\_to\_body\_fixed**](#function-convert_geodetic_to_body_fixed) (const Angle & lat, const Angle & lon, const Distance & alt) <br>_Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates._  |
|  Angle | [**convert\_mean\_anomaly\_to\_eccentric\_anomaly**](#function-convert_mean_anomaly_to_eccentric_anomaly) (const Angle & ma, const Unitless ecc) <br>_Convert the mean anomaly to the eccentric anomaly using Newton's method._  |
|  Angle | [**convert\_mean\_anomaly\_to\_true\_anomaly**](#function-convert_mean_anomaly_to_true_anomaly) (const Angle & ma, const Unitless ecc) <br>_Convert the mean anomaly to the true anomaly. Accurate to O(e^4)._  |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; \_frame\_ &gt; | [**convert\_spherical\_to\_body\_fixed**](#function-convert_spherical_to_body_fixed) (const Distance & range, const Angle & inclination, const Angle & azimuth) <br>_Convert spherical coordinates to a body-fixed radius vector._  |
|  Angle | [**convert\_true\_anomaly\_to\_mean\_anomaly**](#function-convert_true_anomaly_to_mean_anomaly) (const Angle & ta, const Unitless ecc) <br>_Convert the true anomaly to the mean anomaly. Accurate to O(e^5)._  |
|  [**JulianDate**](namespaceastrea_1_1astro.md#typedef-juliandate) | [**epoch\_to\_julian\_date**](#function-epoch_to_julian_date) (const std::string & epoch, const std::string format="%Y-%m-%d %H:%M:%S") <br>_Convert a string representation of a date to a JulianDate object._  |
|  consteval bool | [**equivalent**](#function-equivalent) (Lhs lhs, Rhs rhs) <br> |
|  consteval bool | [**equivalent**](#function-equivalent) (Lhs lhs, Rhs rhs) <br> |
|  consteval bool | [**equivalent**](#function-equivalent) (Lhs lhs, Rhs rhs) <br>_Checks if two frames are equivalent, considering their parent frames and any fixed offsets (spatial or angular)._  |
|  consteval bool | [**equivalent**](#function-equivalent) (Lhs t, Rhs u) <br> |
|  consteval auto | [**f\_to\_fixed\_string**](#function-f_to_fixed_string) () <br>_Helper function to convert a double value to a fixed string at compile time. This is used for generating frame names that include the offset values._  |
|  Density | [**find\_atmospheric\_density**](#function-find_atmospheric_density) (const [**State**](classastrea_1_1astro_1_1State.md) & state) <br>_Primary template for atmospheric density — returns zero by default._  |
|  Density | [**find\_atmospheric\_density&lt; moons::Titan &gt;**](#function-find_atmospheric_density-moons::titan) (const [**State**](classastrea_1_1astro_1_1State.md) & state) <br> |
|  Density | [**find\_atmospheric\_density&lt; planets::Earth &gt;**](#function-find_atmospheric_density-planets::earth) (const [**State**](classastrea_1_1astro_1_1State.md) & state) <br>_Find the atmospheric density for Earth using the configured atmosphere model._  |
|  Density | [**find\_atmospheric\_density&lt; planets::Mars &gt;**](#function-find_atmospheric_density-planets::mars) (const [**State**](classastrea_1_1astro_1_1State.md) & state) <br> |
|  Density | [**find\_atmospheric\_density&lt; planets::Venus &gt;**](#function-find_atmospheric_density-planets::venus) (const [**State**](classastrea_1_1astro_1_1State.md) & state) <br> |
|  consteval auto | [**find\_axis\_in\_ancestors**](#function-find_axis_in_ancestors) (Axis\_T axis, Axis\_U target) <br> |
|  consteval auto | [**find\_common\_ancestor**](#function-find_common_ancestor) (Axis\_T axis, Axis\_U axis\_u) <br> |
|  consteval auto | [**find\_common\_ancestor**](#function-find_common_ancestor) () <br>_Finds the closest common ancestor of the given celestial bodies._  |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Acceleration, get\_parent\_frame(\_body\_, [**axes::icrf**](structastrea_1_1astro_1_1axes_1_1icrf.md))&gt; | [**get\_acceleration\_at**](#function-get_acceleration_at) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _fallback for get\_acceleration\_at._ |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Acceleration, frame &gt; | [**get\_acceleration\_at\_impl**](#function-get_acceleration_at_impl) ([**Date**](classastrea_1_1astro_1_1Date.md) date) <br> |
|  constexpr auto | [**get\_acceleration\_relative\_to\_ancestor**](#function-get_acceleration_relative_to_ancestor) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Get the acceleration of a celestial body relative to the root at a specific date._  |
|  constexpr Angle | [**get\_axial\_tilt**](#function-get_axial_tilt) () <br>_Get the axial tilt of the celestial body._  |
|  consteval auto | [**get\_body\_fixed\_frame**](#function-get_body_fixed_frame) () <br>_Get the body-fixed rotating frame for a celestial body._  |
|  consteval [**CelestialBodyType**](namespaceastrea_1_1astro.md#enum-celestialbodytype) | [**get\_body\_type**](#function-get_body_type) () <br>_Get the type of the celestial body._  |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters**](#function-get_celestial_body_parameters) () = delete<br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; moons::Callisto &gt;**](#function-get_celestial_body_parameters-moons::callisto) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; moons::Deimos &gt;**](#function-get_celestial_body_parameters-moons::deimos) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; moons::Europa &gt;**](#function-get_celestial_body_parameters-moons::europa) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; moons::Ganymede &gt;**](#function-get_celestial_body_parameters-moons::ganymede) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; moons::Iapetus &gt;**](#function-get_celestial_body_parameters-moons::iapetus) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; moons::Io &gt;**](#function-get_celestial_body_parameters-moons::io) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; moons::Moon &gt;**](#function-get_celestial_body_parameters-moons::moon) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; moons::Oberon &gt;**](#function-get_celestial_body_parameters-moons::oberon) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; moons::Phobos &gt;**](#function-get_celestial_body_parameters-moons::phobos) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; moons::Rhea &gt;**](#function-get_celestial_body_parameters-moons::rhea) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; moons::Titan &gt;**](#function-get_celestial_body_parameters-moons::titan) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; moons::Titania &gt;**](#function-get_celestial_body_parameters-moons::titania) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; moons::Triton &gt;**](#function-get_celestial_body_parameters-moons::triton) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; planets::Earth &gt;**](#function-get_celestial_body_parameters-planets::earth) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; planets::Jupiter &gt;**](#function-get_celestial_body_parameters-planets::jupiter) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; planets::Mars &gt;**](#function-get_celestial_body_parameters-planets::mars) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; planets::Mercury &gt;**](#function-get_celestial_body_parameters-planets::mercury) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; planets::Neptune &gt;**](#function-get_celestial_body_parameters-planets::neptune) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; planets::Saturn &gt;**](#function-get_celestial_body_parameters-planets::saturn) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; planets::Uranus &gt;**](#function-get_celestial_body_parameters-planets::uranus) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; planets::Venus &gt;**](#function-get_celestial_body_parameters-planets::venus) () <br> |
|  consteval [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) | [**get\_celestial\_body\_parameters&lt; star::Sun &gt;**](#function-get_celestial_body_parameters-star::sun) () <br> |
|  constexpr auto | [**get\_chebyshev\_table\_coefficients**](#function-get_chebyshev_table_coefficients) ([**Date**](classastrea_1_1astro_1_1Date.md) date) <br>_Get the Chebyshev polynomial coefficients for the celestial body at a specific date._  |
|  constexpr Distance | [**get\_crash\_radius**](#function-get_crash_radius) () <br>_Get the crash radius of the celestial body._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; frame, frame\_u &gt; | [**get\_dcm**](#function-get_dcm) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; in\_frame, out\_frame &gt; | [**get\_dcm**](#function-get_dcm) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Get the Direction Cosine Matrix (DCM) for the body-fixed frame at a given date._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; in\_frame, out\_frame &gt; | [**get\_dcm**](#function-get_dcm) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Get the Direction Cosine Matrix (DCM) for a synodic frame at a given date._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; parent, frame &gt; | [**get\_dcm**](#function-get_dcm) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Retrieves the direction cosine matrix representing the fixed angular offset from the parent frame to the given_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _._ |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; in\_frame, out\_frame &gt; | [**get\_dcm**](#function-get_dcm) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_DCM from any Earth-centred ICRF frame (including the canonical_ [_**frames::earth::icrf**_](structastrea_1_1astro_1_1frames_1_1earth_1_1icrf.md) _) to any Earth-centred body-fixed frame._ |
|  constexpr [**DCM**](namespaceastrea_1_1astro.md#typedef-dcm)&lt; frame, frame\_u &gt; | [**get\_dcm**](#function-get_dcm) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) = delete<br>_Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date._  |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**frames::earth::cep**](structastrea_1_1astro_1_1frames_1_1earth_1_1cep.md), frames::earth::itrf &gt; | [**get\_dcm&lt; frames::earth::cep, frames::earth::itrf &gt;**](#function-get_dcm-frames::earth::cep-frames::earth::itrf) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br> |
|  constexpr [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1frames_1_1earth_1_1icrf.md), [**frames::earth::cep**](structastrea_1_1astro_1_1frames_1_1earth_1_1cep.md) &gt; | [**get\_dcm&lt; frames::earth::icrf, frames::earth::cep &gt;**](#function-get_dcm-frames::earth::icrf-frames::earth::cep) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_DCM from_ [_**frames::earth::icrf**_](structastrea_1_1astro_1_1frames_1_1earth_1_1icrf.md) _to_[_**frames::earth::cep**_](structastrea_1_1astro_1_1frames_1_1earth_1_1cep.md) _._ |
|  constexpr [**DcmAccel**](namespaceastrea_1_1astro.md#typedef-dcmaccel)&lt; frame, frame\_u &gt; | [**get\_dcm\_accel**](#function-get_dcm_accel) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) = delete<br> |
|  constexpr auto | [**get\_dcm\_from\_root\_frame**](#function-get_dcm_from_root_frame) () <br>_Retrieves the accumulated direction cosine matrix from the root frame to the given_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _by recursively composing the DCMs along the parent chain._ |
|  constexpr [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md)&lt; in\_frame, out\_frame &gt; | [**get\_dcm\_rate**](#function-get_dcm_rate) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Get the Direction Cosine Matrix (DCM) rate for the body-fixed frame at a given date._  |
|  constexpr [**DcmRate**](namespaceastrea_1_1astro.md#typedef-dcmrate)&lt; frame, frame\_u &gt; | [**get\_dcm\_rate**](#function-get_dcm_rate) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) = delete<br>_Get the Direction Cosine Matrix (DCM) rate for the body-fixed frame at a given date._  |
|  constexpr Unitless | [**get\_eccentricity**](#function-get_eccentricity) ([**Date**](classastrea_1_1astro_1_1Date.md) date) <br>_Get the eccentricity of the celestial body._  |
|  constexpr BodyUnitlessPerTime | [**get\_eccentricity\_rate**](#function-get_eccentricity_rate) () <br>_Get the eccentricity rate of the celestial body._  |
|  constexpr Distance | [**get\_equitorial\_radius**](#function-get_equitorial_radius) () <br>_Get the equatorial radius of the celestial body._  |
|  constexpr auto | [**get\_gravity\_coefficient\_file**](#function-get_gravity_coefficient_file) () <br>_Get the full set of gravitational coefficients of the celestial body._  |
|  constexpr Angle | [**get\_inclination**](#function-get_inclination) ([**Date**](classastrea_1_1astro_1_1Date.md) date) <br>_Get the inclination of the celestial body._  |
|  constexpr BodyAngularVelocity | [**get\_inclination\_rate**](#function-get_inclination_rate) () <br>_Get the inclination rate of the celestial body._  |
|  constexpr Unitless | [**get\_j2**](#function-get_j2) () <br>_Get the J2 gravitational coefficient of the celestial body._  |
|  constexpr Unitless | [**get\_j3**](#function-get_j3) () <br>_Get the J3 gravitational coefficient of the celestial body._  |
|  constexpr [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)&lt; get\_parent\_frame(\_body\_, [**axes::icrf**](structastrea_1_1astro_1_1axes_1_1icrf.md))&gt; | [**get\_keplerian\_elements\_at**](#function-get_keplerian_elements_at) ([**Date**](classastrea_1_1astro_1_1Date.md) date) <br>_Get the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _elements of a celestial body at a specific date using a linear approximation._ |
|  constexpr CoefficientPack | [**get\_linear\_expansion\_coefficients**](#function-get_linear_expansion_coefficients) () <br>_Get the linear expansion coefficients for the celestial body's mean anomaly correction._  |
|  constexpr CoefficientPack | [**get\_linear\_expansion\_coefficients&lt; planets::Jupiter &gt;**](#function-get_linear_expansion_coefficients-planets::jupiter) () <br>_Get the linear expansion coefficients for Jupiter's orbital elements._  |
|  constexpr CoefficientPack | [**get\_linear\_expansion\_coefficients&lt; planets::Neptune &gt;**](#function-get_linear_expansion_coefficients-planets::neptune) () <br>_Get the coefficients for the linear expansion of Neptune's orbital elements._  |
|  constexpr CoefficientPack | [**get\_linear\_expansion\_coefficients&lt; planets::Saturn &gt;**](#function-get_linear_expansion_coefficients-planets::saturn) () <br>_Get the coefficients for the linear expansion of Saturn's orbital elements._  |
|  constexpr CoefficientPack | [**get\_linear\_expansion\_coefficients&lt; planets::Uranus &gt;**](#function-get_linear_expansion_coefficients-planets::uranus) () <br>_Get the coefficients for the linear expansion of Uranus' orbital elements._  |
|  constexpr Angle | [**get\_longitude\_of\_perigee**](#function-get_longitude_of_perigee) ([**Date**](classastrea_1_1astro_1_1Date.md) date) <br>_Get the longitude of perigee of the celestial body._  |
|  constexpr BodyAngularVelocity | [**get\_longitude\_of\_perigee\_rate**](#function-get_longitude_of_perigee_rate) () <br>_Get the longitude of perigee rate of the celestial body._  |
|  constexpr Mass | [**get\_mass**](#function-get_mass) () <br>_Get the mass of the celestial body._  |
|  constexpr Angle | [**get\_mean\_anomaly**](#function-get_mean_anomaly) ([**Date**](classastrea_1_1astro_1_1Date.md) date) <br>_Get the mean anomaly of the celestial body._  |
|  constexpr Angle | [**get\_mean\_longitude**](#function-get_mean_longitude) ([**Date**](classastrea_1_1astro_1_1Date.md) date) <br>_Get the mean longitude of the celestial body._  |
|  constexpr BodyAngularVelocity | [**get\_mean\_longitude\_rate**](#function-get_mean_longitude_rate) () <br>_Get the mean longitude rate of the celestial body._  |
|  constexpr GravParam | [**get\_mu**](#function-get_mu) () <br>_Get the gravitational parameter (mu) of the celestial body or barycenter._  |
|  constexpr auto | [**get\_offset\_from\_frame**](#function-get_offset_from_frame) () <br>_Retrieves the fixed spatial offset from the parent frame to the given_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _._ |
|  constexpr auto | [**get\_offset\_from\_root\_frame**](#function-get_offset_from_root_frame) () <br>_Retrieves the accumulated fixed spatial offset from the root frame to the given_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _by recursively summing the offsets along the parent chain._ |
|  consteval auto | [**get\_parent**](#function-get_parent) (Origin\_T origin) <br> |
|  consteval auto | [**get\_parent**](#function-get_parent) () <br>_Get the parent body of a celestial body._  |
|  consteval auto | [**get\_parent\_frame**](#function-get_parent_frame) (Origin\_T origin, Axis\_T axis) <br> |
|  consteval auto | [**get\_parent\_name**](#function-get_parent_name) (Origin\_T origin) <br> |
|  consteval auto | [**get\_planet\_from\_pack**](#function-get_planet_from_pack) () <br>_Returns the single PLANET in the pack (assumes exactly one exists)._  |
|  constexpr Distance | [**get\_polar\_radius**](#function-get_polar_radius) () <br>_Get the polar radius of the celestial body._  |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Distance, get\_parent\_frame(\_body\_, [**axes::icrf**](structastrea_1_1astro_1_1axes_1_1icrf.md))&gt; | [**get\_position\_at**](#function-get_position_at) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _fallback for get\_position\_at._ |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Distance, frame &gt; | [**get\_position\_at\_impl**](#function-get_position_at_impl) ([**Date**](classastrea_1_1astro_1_1Date.md) date) <br>_Get the position of the celestial body at a specific date in a specified frame using Chebyshev polynomials._  |
|  constexpr auto | [**get\_position\_relative\_to\_ancestor**](#function-get_position_relative_to_ancestor) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Get the position of a celestial body relative to the root at a specific date._  |
|  constexpr auto | [**get\_relative\_acceleration**](#function-get_relative_acceleration) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Get the relative acceleration between two celestial bodies at a specific date._  |
|  constexpr auto | [**get\_relative\_position**](#function-get_relative_position) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Get the relative position between two celestial bodies at a specific date._  |
|  constexpr auto | [**get\_relative\_velocity**](#function-get_relative_velocity) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Get the relative position between two celestial bodies at a specific date._  |
|  constexpr [**RotationSequence**](namespaceastrea_1_1astro.md#enum-rotationsequence) | [**get\_reverse\_sequence**](#function-get_reverse_sequence) ([**RotationSequence**](namespaceastrea_1_1astro.md#enum-rotationsequence) sequence) <br>_Get the reverse of a Tait-Bryan sequence (e.g., XYZ -&gt; ZYX)._  |
|  constexpr Angle | [**get\_right\_ascension**](#function-get_right_ascension) ([**Date**](classastrea_1_1astro_1_1Date.md) date) <br>_Get the right ascension of the celestial body._  |
|  constexpr BodyAngularVelocity | [**get\_right\_ascension\_rate**](#function-get_right_ascension_rate) () <br>_Get the right ascension rate of the celestial body._  |
|  consteval auto | [**get\_root\_frame**](#function-get_root_frame) () <br>_Retrieves the root frame of a given fixed offset frame by recursively traversing the parent chain._  |
|  constexpr AngularVelocity | [**get\_rotation\_rate**](#function-get_rotation_rate) () <br>_Get the rotation rate of the celestial body._  |
|  constexpr Distance | [**get\_semimajor**](#function-get_semimajor) ([**Date**](classastrea_1_1astro_1_1Date.md) date) <br>_Get the semimajor axis of the celestial body._  |
|  constexpr InterplanetaryVelocity | [**get\_semimajor\_rate**](#function-get_semimajor_rate) () <br>_Get the semimajor axis rate of the celestial body._  |
|  constexpr std::array&lt; int, 3 &gt; | [**get\_sequence\_numbers**](#function-get_sequence_numbers) ([**RotationSequence**](namespaceastrea_1_1astro.md#enum-rotationsequence) sequence) <br> |
|  constexpr Time | [**get\_sidereal\_period**](#function-get_sidereal_period) () <br>_Get the sidereal period of the celestial body._  |
|  constexpr Distance | [**get\_sphere\_of\_influence**](#function-get_sphere_of_influence) () <br>_Get the sphere of influence of the celestial body._  |
|  constexpr auto | [**get\_time\_since\_reference\_epoch**](#function-get_time_since_reference_epoch) ([**Date**](classastrea_1_1astro_1_1Date.md) date) <br> |
|  constexpr Angle | [**get\_true\_anomaly**](#function-get_true_anomaly) ([**Date**](classastrea_1_1astro_1_1Date.md) date) <br>_Get the true anomaly of the celestial body._  |
|  constexpr std::size\_t | [**get\_variant\_index**](#function-get_variant_index) () <br> |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Velocity, get\_parent\_frame(\_body\_, [**axes::icrf**](structastrea_1_1astro_1_1axes_1_1icrf.md))&gt; | [**get\_velocity\_at**](#function-get_velocity_at) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _fallback for get\_velocity\_at._ |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Velocity, frame &gt; | [**get\_velocity\_at\_impl**](#function-get_velocity_at_impl) ([**Date**](classastrea_1_1astro_1_1Date.md) date) <br>_Get the velocity of the celestial body at a specific date in a specified frame using Chebyshev polynomials._  |
|  constexpr auto | [**get\_velocity\_relative\_to\_ancestor**](#function-get_velocity_relative_to_ancestor) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Get the velocity of a celestial body relative to the root at a specific date._  |
|  consteval auto | [**get\_x\_offset\_from\_lla**](#function-get_x_offset_from_lla) () <br>_Retrieves the X offset from the given latitude, longitude, and altitude relative to the parent body-fixed frame._  |
|  consteval auto | [**get\_y\_offset\_from\_lla**](#function-get_y_offset_from_lla) () <br>_Retrieves the Y offset from the given latitude, longitude, and altitude relative to the parent body-fixed frame._  |
|  consteval auto | [**get\_z\_offset\_from\_lla**](#function-get_z_offset_from_lla) () <br>_Retrieves the Z offset from the given latitude, longitude, and altitude relative to the parent body-fixed frame._  |
|  consteval auto | [**has\_axis**](#function-has_axis) (Frame\_T, Axis\_T) <br> |
|  consteval auto | [**has\_origin**](#function-has_origin) (Frame\_T, Origin\_T) <br> |
|  consteval bool | [**has\_parent**](#function-has_parent) () <br>_Check if a celestial body has a parent body defined._  |
|  consteval bool | [**has\_same\_axis**](#function-has_same_axis) (T t, U u) <br>_Concept to determine if two frames share the same axis._  |
|  consteval bool | [**has\_same\_origin**](#function-has_same_origin) (T t, U u) <br>_Concept to determine if two frames share the same origin._  |
|  consteval bool | [**has\_same\_parent**](#function-has_same_parent) (T t, U u) <br>_Helper function to determine if two frames share the same parent frame. This is used in the get\_dcm function for FixedOffsetFrames to ensure that the input and output frames share the same parent frame._  |
|  consteval bool | [**has\_same\_parent**](#function-has_same_parent) (T t, U u) <br>_Specialization of has\_same\_parent for frames that are both derived frames. This checks if the parent types are the same._  |
|  consteval bool | [**has\_same\_parent**](#function-has_same_parent) (T t, U u) <br>_Specialization of has\_same\_parent for frames that are both root frames. Root frames are considered to share the same parent (themselves)._  |
|  consteval bool | [**have\_same\_misalignment**](#function-have_same_misalignment) (Lhs lhs, Rhs rhs) <br>_Checks if two fixed offset frames have the same angular misalignment._  |
|  consteval bool | [**have\_same\_offsets**](#function-have_same_offsets) (Lhs lhs, Rhs rhs) <br>_Checks if two fixed offset frames have the same spatial offsets._  |
|  consteval bool | [**is\_aligned\_with\_parent**](#function-is_aligned_with_parent) (Frame\_T frame) <br>_Checks if a fixed offset frame is aligned with its parent frame._  |
|  consteval bool | [**is\_ancestor\_of**](#function-is_ancestor_of) () <br>_Returns true if Ancestor is Body itself or appears anywhere in Body's parent chain._  |
|  constexpr bool | [**is\_proper\_euler\_sequence**](#function-is_proper_euler_sequence) ([**RotationSequence**](namespaceastrea_1_1astro.md#enum-rotationsequence) sequence) <br> |
|  consteval bool | [**is\_same\_body**](#function-is_same_body) () <br>_Check if two celestial bodies are the same._  |
|  constexpr Angle | [**julian\_date\_to\_body\_sidereal\_time**](#function-julian_date_to_body_sidereal_time) ([**JulianDate**](namespaceastrea_1_1astro.md#typedef-juliandate) date) <br>_Compute the equivalent of Greenwich Sidereal Time for an arbitrary celestial body._  |
|  Angle | [**julian\_date\_to\_sidereal\_time**](#function-julian_date_to_sidereal_time) (const [**JulianDate**](namespaceastrea_1_1astro.md#typedef-juliandate) & date) <br>_Convert a JulianDate to a string representation._  |
|  consteval auto | [**make\_frame**](#function-make_frame) (Origin\_T origin, Axis\_T axis) <br> |
|  consteval bool | [**misalignment\_is\_zero**](#function-misalignment_is_zero) (Axis\_T axis) <br> |
|  consteval bool | [**offset\_is\_zero**](#function-offset_is_zero) (Origin\_T origin) <br> |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; decltype(Value\_T{} \*Value\_U{}), frame &gt; | [**operator\***](#function-operator) (const Value\_U & scalar, const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, frame &gt; & vec) <br>_Scalar multiplication operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  constexpr [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; decltype(Value\_T{} \*Value\_U{}), in\_frame, out\_frame &gt; | [**operator\***](#function-operator_1) (const Value\_T & scalar, const [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md)&lt; Value\_U, in\_frame, out\_frame &gt; & matrix) <br>_Multiply the matrix by a scalar value (element-wise multiplication)._  |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; decltype(MomentOfInertia{} \*AngularVelocity{}), in\_frame &gt; | [**operator\***](#function-operator_2) (const [**InertiaTensor**](classastrea_1_1astro_1_1InertiaTensor.md)&lt; in\_frame &gt; & inertiaTensor, const [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md)&lt; in\_frame, ref\_frame &gt; & vec) <br>_Scalar multiplication operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _with an_[_**InertiaTensor**_](classastrea_1_1astro_1_1InertiaTensor.md) _._ |
|  [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; decltype(Value\_U{} \*AngularAcceleration{}), in\_frame &gt; | [**operator\***](#function-operator_3) (const Value\_U & scalar, const [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md)&lt; in\_frame, ref\_frame &gt; & accel) <br>_Scalar multiplication operator for a quantity multiplied by_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _, resulting in a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md)&lt; in\_frame, ref\_frame &gt; | [**operator\***](#function-operator_4) (const Time & time, const [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md)&lt; in\_frame, ref\_frame &gt; & accel) <br>_Scalar multiplication operator for Time multiplied by_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _, resulting in an_[_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._ |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; | [**operator\***](#function-operator_5) (const Unitless & scalar, const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; & vec) <br>_Scalar multiplication operator for EulerAngless._  |
|  constexpr [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; decltype(Value\_T{} \*Value\_U{}), frame &gt; | [**operator/**](#function-operator_6) (const Value\_U & scalar, const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, frame &gt; & vec) <br>_Scalar division operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; | [**operator/**](#function-operator_7) (const Unitless & scalar, const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; & vec) <br>_Scalar division operator for EulerAngless._  |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_8) (std::ostream & os, const [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt; Value\_T, frame &gt; & state) <br>_Overload the output stream operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._ |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_9) (std::ostream & os, [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md)&lt; \_body\_ &gt; const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_10) (std::ostream & os, [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md)&lt; \_body\_ &gt; const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_11) (std::ostream & os, [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md)&lt; \_body\_ &gt; const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_12) (std::ostream & os, [**Spherical**](classastrea_1_1astro_1_1Spherical.md)&lt; \_body\_ &gt; const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_13) (std::ostream & os, const [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md)&lt; in\_frame, ref\_frame &gt; & angleSequenceRate) <br>_Output stream operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._ |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_14) (std::ostream & os, const [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md)&lt; in\_frame, ref\_frame &gt; & angleSequenceAccel) <br>_Output stream operator for_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _._ |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_15) (std::ostream & os, const [**Attitude**](classastrea_1_1astro_1_1Attitude.md) & attitude) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_16) (std::ostream & os, const [**AttitudePartials**](classastrea_1_1astro_1_1AttitudePartials.md) & attitude) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_17) (std::ostream & os, const [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt; sequence, rotation\_type, \_in\_frame\_, \_out\_frame\_ &gt; & angleSequence) <br>_Output stream operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._ |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_18) (std::ostream & os, const [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md)&lt; in\_frame, out\_frame &gt; & quaternion) <br>_Stream insertion operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class, allowing for easy printing of quaternion components._ |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_19) (std::ostream & os, const [**QuaternionPartial**](classastrea_1_1astro_1_1QuaternionPartial.md)&lt; in\_frame, out\_frame &gt; & quaternion) <br>_Stream insertion operator for the_ [_**QuaternionPartial**_](classastrea_1_1astro_1_1QuaternionPartial.md) _class, allowing for easy printing of quaternion derivative components._ |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_20) (std::ostream & os, const std::optional&lt; T &gt; & opt) <br>_Overloaded output stream operator for an optional type._  |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_21) (std::ostream & os, const [**GeneralPerturbations**](structastrea_1_1astro_1_1GeneralPerturbations.md) & gp) <br>_Overloaded output stream operator for_ [_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _._ |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_22) (std::ostream & os, [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_23) (std::ostream & os, [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)&lt; \_frame\_ &gt; const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_24) (std::ostream & os, [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md)&lt; \_frame\_ &gt; const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_25) (std::ostream & os, [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md)&lt; \_frame\_ &gt; const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_26) (std::ostream & os, [**EquinoctialPartial**](classastrea_1_1astro_1_1EquinoctialPartial.md)&lt; \_frame\_ &gt; const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_27) (std::ostream & os, [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md)&lt; \_frame\_ &gt; const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_28) (std::ostream & os, [**KeplerianPartial**](classastrea_1_1astro_1_1KeplerianPartial.md)&lt; \_frame\_ &gt; const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_29) (std::ostream & os, const [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_30) (std::ostream & os, const [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_31) (std::ostream & os, const [**State**](classastrea_1_1astro_1_1State.md) & state) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_32) (std::ostream & os, const [**Date**](classastrea_1_1astro_1_1Date.md) & obj) <br> |
|  bool | [**planes\_are\_nearly\_equal**](#function-planes_are_nearly_equal) (const [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & elem1, const [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & elem2, const Unitless & relTol) <br> |
|  consteval auto | [**quantity\_list\_to\_fixed\_string**](#function-quantity_list_to_fixed_string) () <br>_Helper function to convert a list of quantities to a comma-separated fixed string at compile time. This is used for generating frame names that include multiple offset values._  |
|  consteval auto | [**quantity\_to\_fixed\_string**](#function-quantity_to_fixed_string) () <br>_Helper function to convert a quantity to a fixed string at compile time, including its numerical value and unit symbol. This is used for generating frame names that include the offset values._  |
|  void | [**throw\_mismatched\_types**](#function-throw_mismatched_types) () <br>_Throws an exception for mismatched types in orbital elements._  |
|  constexpr bool | [**variant\_contains**](#function-variant_contains) () <br>_Checks whether type T is one of the alternatives in VariantType._  |
|  constexpr Angle | [**wrap\_angle**](#function-wrap_angle) (const Angle & angle) noexcept<br>_Sanitize an angle to ensure it is within the range [0, 2π)._  |
|  constexpr Angle | [**wrap\_angle\_to\_pi**](#function-wrap_angle_to_pi) (const Angle & angle) noexcept<br>_Sanitize an angle to ensure it is within the range [0, π)._  |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  constexpr [**JulianDate**](namespaceastrea_1_1astro.md#typedef-juliandate) | [**J2000**](#function-j2000) ([**JulianDateClock::duration**](structastrea_1_1astro_1_1JulianDateClock.md#typedef-duration){ 2451545.0 }) <br>_A constant representing the J2000 epoch in Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _format._ |
|  constexpr [**JulianDate**](namespaceastrea_1_1astro.md#typedef-juliandate) | [**MJD0**](#function-mjd0) ([**JulianDateClock::duration**](structastrea_1_1astro_1_1JulianDateClock.md#typedef-duration){ 2400000.5 }) <br>_A constant representing the Modified Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _epoch in Julian_[_**Date**_](classastrea_1_1astro_1_1Date.md) _format._ |


























## Public Types Documentation




### typedef AccelerationVector 

_Type alias for a vector representing acceleration in 3D space._ 
```C++
using astrea::astro::AccelerationVector = typedef CartesianVector<Acceleration, frame>;
```




<hr>



### typedef AutomaticallyRegisteredFrames 

_The built-in set of_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _frames known to astrea._
```C++
using astrea::astro::AutomaticallyRegisteredFrames = typedef std::tuple<std::decay_t<decltype(frames::primary)> >;
```



Add new built-in frames here as additional tuple elements. 


        

<hr>



### typedef BarycentricCoordinateTime 

_A type alias for Barycentric Coordinate Time time points._ 
```C++
using astrea::astro::BarycentricCoordinateTime = typedef BarycentricCoordinateTimeClock::time_point;
```



This is a convenience type alias for TCB time points using the [**BarycentricCoordinateTimeClock**](structastrea_1_1astro_1_1BarycentricCoordinateTimeClock.md). 


        

<hr>



### typedef BarycentricCoordinateTimePoint 

_A time point type for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _Coordinate Time, using the_[_**BarycentricCoordinateTimeClock**_](structastrea_1_1astro_1_1BarycentricCoordinateTimeClock.md) _._
```C++
using astrea::astro::BarycentricCoordinateTimePoint = typedef std::chrono::time_point<BarycentricCoordinateTimeClock, Duration>;
```





**Template parameters:**


* `Duration` The duration type to use for the time point. This should be a duration type that is compatible with [**BarycentricCoordinateTimeClock**](structastrea_1_1astro_1_1BarycentricCoordinateTimeClock.md). 




        

<hr>



### typedef BarycentricDynamicalTime 

_A type alias for Barycentric Dynamical Time time points._ 
```C++
using astrea::astro::BarycentricDynamicalTime = typedef BarycentricDynamicalTimeClock::time_point;
```



This is a convenience type alias for TDB time points using the [**BarycentricDynamicalTimeClock**](structastrea_1_1astro_1_1BarycentricDynamicalTimeClock.md). 


        

<hr>



### typedef BarycentricDynamicalTimePoint 

_A time point type for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _Coordinate Time, using the_[_**BarycentricDynamicalTimeClock**_](structastrea_1_1astro_1_1BarycentricDynamicalTimeClock.md) _._
```C++
using astrea::astro::BarycentricDynamicalTimePoint = typedef std::chrono::time_point<BarycentricDynamicalTimeClock, Duration>;
```





**Template parameters:**


* `Duration` The duration type to use for the time point. This should be a duration type that is compatible with [**BarycentricDynamicalTimeClock**](structastrea_1_1astro_1_1BarycentricDynamicalTimeClock.md). 




        

<hr>



### typedef BodyAngleVelocities 

_Type alias for a ICRF-&gt;body angle sequence velocity._ 
```C++
using astrea::astro::BodyAngleVelocities = typedef AngularVelocities<frames::dynamic::body, frames::earth::icrf>;
```




<hr>



### typedef BodyAngles 

_Type alias for a ICRF-&gt;body angle sequence._ 
```C++
using astrea::astro::BodyAngles = typedef EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, frames::dynamic::body, frames::earth::icrf>;
```




<hr>



### typedef BodyAngularAcceleration 

_Type alias for a ICRF-&gt;body angle sequence acceleration._ 
```C++
using astrea::astro::BodyAngularAcceleration = typedef AngularAccelerations<frames::dynamic::body, frames::earth::icrf>;
```




<hr>



### typedef BodyQuaternion 

_Type alias for a ICRF-&gt;body quaternion._ 
```C++
using astrea::astro::BodyQuaternion = typedef Quaternion<frames::dynamic::body, frames::earth::icrf>;
```




<hr>



### typedef BodyQuaternionRate 

_Type alias for a ICRF-&gt;body quaternion derivative._ 
```C++
using astrea::astro::BodyQuaternionRate = typedef QuaternionPartial<frames::dynamic::body, frames::earth::icrf>;
```




<hr>



### typedef CR3BP 

```C++
using astrea::astro::CR3BP = typedef CircularRestrictedThreeBodyProblem;
```




<hr>



### enum CelestialBodyType 

_Celestial body types._ 
```C++
enum astrea::astro::CelestialBodyType {
    UNSET,
    STAR,
    PLANET,
    MOON
};
```




<hr>



### typedef CoefficientPack 

_Type alias for a tuple of linear expansion coefficients._ 
```C++
using astrea::astro::CoefficientPack = typedef std::tuple< mp_units::quantity<mp_units::si::unit_symbols::rad / (astrea::units::unit_symbols::jc * astrea::units::unit_symbols::jc)>, mp_units::quantity<mp_units::si::unit_symbols::rad>, mp_units::quantity<mp_units::si::unit_symbols::rad>, mp_units::quantity<mp_units::si::unit_symbols::rad / astrea::units::unit_symbols::jc> >;
```



The four fields are (B, C, S, F): Me = L - w + B\*T^2 + C\*cos(F\*T) + S\*sin(F\*T) where T is time since reference epoch in Julian centuries. 


        

<hr>



### enum Coordinate 

```C++
enum astrea::astro::Coordinate {
    X,
    Y,
    Z
};
```




<hr>



### typedef DCM 

_Alias for_ [_**DirectionCosineMatrix**_](classastrea_1_1astro_1_1DirectionCosineMatrix.md) _with a specific output frame type._
```C++
using astrea::astro::DCM = typedef DirectionCosineMatrix<_in_frame_, _out_frame_>;
```



This alias simplifies the usage of [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) by allowing the user to specify the output frame type.




**Template parameters:**


* `_out_frame_` The frame type to which the DCM applies. 




        

<hr>



### typedef DcmAccel 

_Alias for_ [_**DirectionCosineMatrixAccel**_](structastrea_1_1astro_1_1DirectionCosineMatrixAccel.md) _with a specific output frame type._
```C++
using astrea::astro::DcmAccel = typedef DirectionCosineMatrixAccel<_in_frame_, _out_frame_>;
```



This alias simplifies the usage of [**DirectionCosineMatrixAccel**](structastrea_1_1astro_1_1DirectionCosineMatrixAccel.md) by allowing the user to specify the output frame type.




**Template parameters:**


* `_out_frame_` The frame type to which the DCM applies. 




        

<hr>



### typedef DcmRate 

_Alias for_ [_**DirectionCosineMatrixRate**_](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md) _with a specific output frame type._
```C++
using astrea::astro::DcmRate = typedef DirectionCosineMatrixRate<_in_frame_, _out_frame_>;
```



This alias simplifies the usage of [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md) by allowing the user to specify the output frame type.




**Template parameters:**


* `_out_frame_` The frame type to which the DCM applies. 




        

<hr>



### typedef Direction 

_Type alias for a vector representing unit vectors in 3D space._ 
```C++
using astrea::astro::Direction = typedef CartesianVector<Unitless, frame>;
```



This is used for direction vectors that do not have units of distance, velocity, or acceleration. 


        

<hr>



### typedef EnumType 

_Type definition for enumeration types._ 
```C++
using astrea::astro::EnumType = typedef uint32_t;
```




<hr>



### typedef ForceVector 

_Type alias for a vector representing force vectors in 3D space._ 
```C++
using astrea::astro::ForceVector = typedef CartesianVector<Force, frame>;
```



This is used for vectors that represent forces acting on a vehicle. 


        

<hr>



### enum FrameAxis 

_Reference frames axes._ 
```C++
enum astrea::astro::FrameAxis {
    UNSET,
    ICRF,
    J2000,
    FIXED_ROTATING,
    LVLH,
    RIC,
    VNB,
    ENU
};
```




<hr>



### typedef GeocentricCoordinateDateTime 

_A time point type for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _Coordinate Time, using the_[_**GeocentricCoordinateTimeClock**_](structastrea_1_1astro_1_1GeocentricCoordinateTimeClock.md) _._
```C++
using astrea::astro::GeocentricCoordinateDateTime = typedef std::chrono::time_point<GeocentricCoordinateTimeClock, Duration>;
```





**Template parameters:**


* `Duration` The duration type to use for the time point. This should be a duration type that is compatible with [**GeocentricCoordinateTimeClock**](structastrea_1_1astro_1_1GeocentricCoordinateTimeClock.md). 




        

<hr>



### typedef GeocentricCoordinateTime 

_A type alias for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _Coordinate Time time points._
```C++
using astrea::astro::GeocentricCoordinateTime = typedef GeocentricCoordinateTimeClock::time_point;
```



This is a convenience type alias for TCG time points using the [**GeocentricCoordinateTimeClock**](structastrea_1_1astro_1_1GeocentricCoordinateTimeClock.md). 


        

<hr>



### typedef JulianDate 

_A type alias for Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _time points._
```C++
using astrea::astro::JulianDate = typedef JulianDateClock::time_point;
```



This is a convenience type alias for Julian [**Date**](classastrea_1_1astro_1_1Date.md) time points using the [**JulianDateClock**](structastrea_1_1astro_1_1JulianDateClock.md). 


        

<hr>



### typedef JulianDateTime 

_A time point type for Julian Dates, using the_ [_**JulianDateClock**_](structastrea_1_1astro_1_1JulianDateClock.md) _._
```C++
using astrea::astro::JulianDateTime = typedef std::chrono::time_point<JulianDateClock, Duration>;
```





**Template parameters:**


* `Duration` The duration type to use for the time point. This should be a duration type that is compatible with [**JulianDateClock**](structastrea_1_1astro_1_1JulianDateClock.md). 




        

<hr>



### typedef OrbitalElementPartialVariant 

```C++
using astrea::astro::OrbitalElementPartialVariant = typedef typename detail::tuple_to_variant<typename detail::multi_tuple_cat< typename detail::apply_nttp_template<CartesianPartial, detail::AllRegisteredFrames>::type, typename detail::apply_nttp_template<FrameIndexedTypes, detail::AllRegisteredFrames>::type...>::type>::type;
```




<hr>



### typedef OrbitalElementVariant 

_Variant of all frame-indexed element types expanded over every registered frame._ 
```C++
using astrea::astro::OrbitalElementVariant = typedef typename detail::tuple_to_variant<typename detail::multi_tuple_cat< typename detail::apply_nttp_template<Cartesian, detail::AllRegisteredFrames>::type, typename detail::apply_nttp_template<FrameIndexedTypes, detail::AllRegisteredFrames>::type...>::type>::type;
```



The first element type ([**Cartesian**](classastrea_1_1astro_1_1Cartesian.md)) is always included. Any additional frame-indexed templates passed as FrameIndexedTypes are also expanded over all registered frames. Typically used as:



```C++
using ElementVariant = OrbitalElementVariant<Keplerian, Equinoctial>;
```



Adding a frame to [**ExtraRegisteredFrames**](structastrea_1_1astro_1_1ExtraRegisteredFrames.md) automatically adds a new instantiation of every listed template to this variant.


To register frames from user code, see [**ExtraRegisteredFrames**](structastrea_1_1astro_1_1ExtraRegisteredFrames.md) in [**astro/frames/definitions/frame\_registry.hpp**](frame__registry_8hpp.md). 


        

<hr>



### typedef RadiusVector 

_Type alias for a vector representing a radius in 3D space._ 
```C++
using astrea::astro::RadiusVector = typedef CartesianVector<Distance, frame>;
```




<hr>



### enum RotationSequence 

_Enum representing possible Euler angle sequences._ 
```C++
enum astrea::astro::RotationSequence {
    ZXZ,
    XYX,
    YZY,
    ZYZ,
    XZX,
    YXY,
    XYZ,
    YZX,
    ZXY,
    XZY,
    ZYX,
    YXZ
};
```




<hr>



### enum RotationType 

_Enum representing whether the rotation sequence is intrinsic or extrinsic._ 
```C++
enum astrea::astro::RotationType {
    EXTRINSIC,
    INTRINSIC
};
```




<hr>



### enum StepMethod 

_Enumeration for different Runge-Kutta stepper methods._ 
```C++
enum astrea::astro::StepMethod {
    RK45,
    RKF45,
    RKF78,
    DOP45,
    DOP78
};
```




<hr>



### enum SystemCenter 

_System center types._ 
```C++
enum astrea::astro::SystemCenter {
    CENTRAL_BODY,
    BARYCENTER
};
```




<hr>



### typedef TerrestrialDateTime 

_A time point type for Terrestrial Time, using the_ [_**TerrestrialTimeClock**_](structastrea_1_1astro_1_1TerrestrialTimeClock.md) _._
```C++
using astrea::astro::TerrestrialDateTime = typedef std::chrono::time_point<TerrestrialTimeClock, Duration>;
```





**Template parameters:**


* `Duration` The duration type to use for the time point. This should be a duration type that is compatible with [**TerrestrialTimeClock**](structastrea_1_1astro_1_1TerrestrialTimeClock.md). 




        

<hr>



### typedef TerrestrialTime 

_A type alias for Terrestrial Time time points._ 
```C++
using astrea::astro::TerrestrialTime = typedef TerrestrialTimeClock::time_point;
```



This is a convenience type alias for TT time points using the [**TerrestrialTimeClock**](structastrea_1_1astro_1_1TerrestrialTimeClock.md). 


        

<hr>



### typedef ThrusterPlatform 

[_**Thruster**_](classastrea_1_1astro_1_1Thruster.md) _platform type definition._
```C++
using astrea::astro::ThrusterPlatform = typedef PayloadPlatform<Thruster>;
```




<hr>



### typedef TorqueVector 

_Type alias for a vector representing moment vectors in 3D space._ 
```C++
using astrea::astro::TorqueVector = typedef CartesianVector<Moment, frame>;
```



This is used for vectors that represent moments (torques) acting on a vehicle. 


        

<hr>



### typedef VelocityVector 

_Type alias for a vector representing velocity in 3D space._ 
```C++
using astrea::astro::VelocityVector = typedef CartesianVector<Velocity, frame>;
```




<hr>



### typedef remove\_cv\_ref 

```C++
using astrea::astro::remove_cv_ref = typedef std::remove_cv_t<std::remove_reference_t<T> >;
```




<hr>
## Public Attributes Documentation




### variable always\_false 

_A helper variable template that is always false, used for static\_asserts in templates that should never be instantiated._ 
```C++
constexpr bool astrea::astro::always_false;
```




<hr>



### variable is\_cartesian\_vector\_v 

```C++
constexpr bool astrea::astro::is_cartesian_vector_v;
```




<hr>
## Public Static Attributes Documentation




### variable CENTER 

```C++
const astro::RadiusVector<astro::frames::dynamic::ric> astrea::astro::CENTER;
```




<hr>



### variable DEFAULT\_SHELL\_ID 

```C++
const size_t astrea::astro::DEFAULT_SHELL_ID;
```




<hr>



### variable J2K 

_A constant representing the J2000 epoch in Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _format, used as a reference point._
```C++
constexpr mp_units::quantity_point astrea::astro::J2K;
```



This is the same as J2000 but is defined for clarity in contexts where a reference point is needed. 


        

<hr>



### variable MJDStart 

_A constant representing the start of the Modified Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _epoch._
```C++
constexpr mp_units::quantity_point astrea::astro::MJDStart;
```



This is used as a reference point for Modified Julian Dates. 


        

<hr>



### variable NADIR\_RIC 

```C++
const astro::RadiusVector<astro::frames::dynamic::ric> astrea::astro::NADIR_RIC;
```




<hr>



### variable RADIAL\_RIC 

```C++
const astro::RadiusVector<astro::frames::dynamic::ric> astrea::astro::RADIAL_RIC;
```




<hr>
## Public Functions Documentation




### function all\_have\_valid\_transformation 

```C++
template<typename Tuple, typename Primary>
constexpr bool astrea::astro::all_have_valid_transformation () 
```




<hr>



### function all\_have\_valid\_transformation\_impl 

```C++
template<typename Tuple, typename Primary, std::size_t... I>
constexpr bool astrea::astro::all_have_valid_transformation_impl (
    std::index_sequence< I... >
) 
```




<hr>



### function calculate\_geocentric\_radius 

_Calculate the geocentric radius given latitude and Earth's radii._ 
```C++
template<IsCelestialBody auto body>
inline constexpr Distance astrea::astro::calculate_geocentric_radius (
    const Angle & lat
) 
```





**Parameters:**


* `lat` The latitude in radians. 
* `rEquitorial` The equatorial radius of the Earth. 
* `rPolar` The polar radius of the Earth. 



**Returns:**

The geocentric radius. 





        

<hr>



### function check\_all\_bodies\_share\_a\_parent 

_Checks if all bodies in the pack share the same parent._ 
```C++
template<IsCelestialReference auto first, IsCelestialReference auto... rest>
consteval bool astrea::astro::check_all_bodies_share_a_parent () 
```





**Template parameters:**


* `first` The first celestial body in the pack to check. 
* `rest` The remaining celestial bodies in the pack to check. 



**Returns:**

true if all bodies share the same parent, false otherwise. 





        

<hr>



### function compose\_name 

_Helper function to compose the name of a_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _based on its parent frame's name and its offset values. This generates a descriptive name that includes the parent frame and the specific offsets applied._
```C++
template<mp_units::symbol_text _parent_name_, Distance _x_, Distance _y_, Distance _z_>
inline consteval auto astrea::astro::compose_name () 
```



Helper function to compose the name of a [**FixedOffsetFrame**](structastrea_1_1astro_1_1FixedOffsetFrame.md) with ONLY angular offsets based on its parent frame's name and its offset values. This generates a descriptive name that includes the parent frame and the specific angular offsets applied.




**Template parameters:**


* `_parent_name_` The name of the parent frame. 
* `_x_` The fixed offset in the x direction. 
* `_y_` The fixed offset in the y direction. 
* `_z_` The fixed offset in the z direction. 



**Returns:**

A basic\_fixed\_string representing the composed name of the [**FixedOffsetFrame**](structastrea_1_1astro_1_1FixedOffsetFrame.md), including the parent frame's name and the offset values.




**Template parameters:**


* `_parent_name_` The name of the parent frame. 
* `_phi_` The fixed offset angle around the x-axis. 
* `_theta_` The fixed offset angle around the y-axis. 



**Returns:**

A basic\_fixed\_string representing the composed name of the [**FixedOffsetFrame**](structastrea_1_1astro_1_1FixedOffsetFrame.md), including the parent frame's name and the angular offset values. 





        

<hr>



### function compose\_name 

_Helper function to compose the name of a_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _with both spatial and angular offsets based on its parent frame's name and its offset values. This generates a descriptive name that includes the parent frame and the specific spatial and angular offsets applied._
```C++
template<mp_units::symbol_text _parent_name_, Distance _x_, Distance _y_, Distance _z_, Angle _phi_, Angle _theta_, Angle _psi_>
inline consteval auto astrea::astro::compose_name () 
```





**Template parameters:**


* `_parent_name_` The name of the parent frame. 
* `_x_` The fixed offset in the x direction. 
* `_y_` The fixed offset in the y direction. 
* `_z_` The fixed offset in the z direction. 
* `_phi_` The fixed offset angle around the x-axis. 
* `_theta_` The fixed offset angle around the y-axis. 
* `_psi_` The fixed offset angle around the z-axis. 



**Returns:**

A basic\_fixed\_string representing the composed name of the [**FixedOffsetFrame**](structastrea_1_1astro_1_1FixedOffsetFrame.md), including the parent frame's name and the spatial and angular offset values. 





        

<hr>



### function convert\_body\_fixed\_to\_cylindrical 

_Convert a body-fixed radius vector to cylindrical coordinates._ 
```C++
template<IsFrame auto _frame_>
std::tuple< Distance, Angle, Distance > astrea::astro::convert_body_fixed_to_cylindrical (
    const RadiusVector < _frame_ > & rFixed
) 
```





**Parameters:**


* `rFixed` The radius vector in the body-fixed frame. 



**Returns:**

The range, azimuth, and elevation as a tuple. 





        

<hr>



### function convert\_body\_fixed\_to\_geocentric 

_Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates._ 
```C++
template<IsFrame auto frame>
inline constexpr std::tuple< Angle, Angle, Distance > astrea::astro::convert_body_fixed_to_geocentric (
    const RadiusVector < frame > & rEcef
) 
```





**Parameters:**


* `rEcef` The radius vector in ECEF coordinates. 
* `rEquitorial` The equatorial radius of the Earth. 
* `rPolar` The polar radius of the Earth. 



**Returns:**

The latitude, longitude, and altitude as a tuple. 





        

<hr>



### function convert\_body\_fixed\_to\_geodetic 

_Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates._ 
```C++
template<IsFrame auto frame>
inline std::tuple< Angle, Angle, Distance > astrea::astro::convert_body_fixed_to_geodetic (
    const RadiusVector < frame > & rBodyFixed
) 
```





**Parameters:**


* `rEcef` The radius vector in ECEF coordinates. 
* `rEquitorial` The equatorial radius of the Earth. 
* `rPolar` The polar radius of the Earth. 



**Returns:**

The latitude, longitude, and altitude as a tuple. 





        

<hr>



### function convert\_body\_fixed\_to\_spherical 

_Convert a body-fixed radius vector to spherical coordinates._ 
```C++
template<IsFrame auto _frame_>
std::tuple< Distance, Angle, Angle > astrea::astro::convert_body_fixed_to_spherical (
    const RadiusVector < _frame_ > & rFixed
) 
```





**Parameters:**


* `rFixed` The radius vector in the body-fixed frame. 



**Returns:**

The range, inclination, and azimuth as a tuple. 





        

<hr>



### function convert\_cylindrical\_to\_body\_fixed 

_Convert cylindrical coordinates to a body-fixed radius vector._ 
```C++
template<IsFrame auto _frame_>
RadiusVector < _frame_ > astrea::astro::convert_cylindrical_to_body_fixed (
    const Distance & range,
    const Angle & azimuth,
    const Distance & elevation
) 
```





**Parameters:**


* `range` The range. 
* `azimuth` The azimuth in radians. 
* `elevation` The elevation. 



**Returns:**

The radius vector in the body-fixed frame. 





        

<hr>



### function convert\_eccentric\_anomaly\_to\_mean\_anomaly 

_Convert the eccentric anomaly to the mean anomaly._ 
```C++
Angle astrea::astro::convert_eccentric_anomaly_to_mean_anomaly (
    const Angle & ea,
    const Unitless ecc
) 
```





**Parameters:**


* `ea` The eccentric anomaly. 
* `ecc` The eccentricity. 



**Returns:**

The mean anomaly. 





        

<hr>



### function convert\_geocentric\_to\_body\_fixed 

_Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates._ 
```C++
template<IsFrame auto _frame_>
inline constexpr RadiusVector < _frame_ > astrea::astro::convert_geocentric_to_body_fixed (
    const Angle & lat,
    const Angle & lon,
    const Distance & alt
) 
```





**Parameters:**


* `lat` The latitude in radians. 
* `lon` The longitude in radians. 
* `alt` The altitude in meters. 



**Returns:**

The radius vector in ECEF coordinates. 





        

<hr>



### function convert\_geodetic\_to\_body\_fixed 

_Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates._ 
```C++
template<IsFrame auto frame>
inline constexpr RadiusVector < frame > astrea::astro::convert_geodetic_to_body_fixed (
    const Angle & lat,
    const Angle & lon,
    const Distance & alt
) 
```





**Parameters:**


* `lat` The latitude in radians. 
* `lon` The longitude in radians. 
* `alt` The altitude in meters. 
* `rEquitorial` The equatorial radius of the Earth. 
* `rPolar` The polar radius of the Earth. 



**Returns:**

The radius vector in ECEF coordinates. 





        

<hr>



### function convert\_mean\_anomaly\_to\_eccentric\_anomaly 

_Convert the mean anomaly to the eccentric anomaly using Newton's method._ 
```C++
Angle astrea::astro::convert_mean_anomaly_to_eccentric_anomaly (
    const Angle & ma,
    const Unitless ecc
) 
```





**Parameters:**


* `ma` The mean anomaly. 
* `ecc` The eccentricity. 



**Returns:**

The eccentric anomaly. 





        

<hr>



### function convert\_mean\_anomaly\_to\_true\_anomaly 

_Convert the mean anomaly to the true anomaly. Accurate to O(e^4)._ 
```C++
Angle astrea::astro::convert_mean_anomaly_to_true_anomaly (
    const Angle & ma,
    const Unitless ecc
) 
```





**Parameters:**


* `ma` The mean anomaly. 
* `ecc` The eccentricity. 



**Returns:**

The true anomaly. 





        

<hr>



### function convert\_spherical\_to\_body\_fixed 

_Convert spherical coordinates to a body-fixed radius vector._ 
```C++
template<IsFrame auto _frame_>
RadiusVector < _frame_ > astrea::astro::convert_spherical_to_body_fixed (
    const Distance & range,
    const Angle & inclination,
    const Angle & azimuth
) 
```





**Parameters:**


* `range` The range. 
* `inclination` The inclination in radians. 
* `azimuth` The azimuth in radians. 



**Returns:**

The radius vector in the body-fixed frame. 





        

<hr>



### function convert\_true\_anomaly\_to\_mean\_anomaly 

_Convert the true anomaly to the mean anomaly. Accurate to O(e^5)._ 
```C++
Angle astrea::astro::convert_true_anomaly_to_mean_anomaly (
    const Angle & ta,
    const Unitless ecc
) 
```





**Parameters:**


* `ta` The true anomaly. 
* `ecc` The eccentricity. 



**Returns:**

Angle The mean anomaly. 





        

<hr>



### function epoch\_to\_julian\_date 

_Convert a string representation of a date to a JulianDate object._ 
```C++
JulianDate astrea::astro::epoch_to_julian_date (
    const std::string & epoch,
    const std::string format="%Y-%m-%d %H:%M:%S"
) 
```





**Parameters:**


* `epoch` The date string to convert. 
* `format` The format of the date string, default is "%Y-%m-%d %H:%M:%S". 



**Returns:**

JulianDate The JulianDate representation of the input date. 





        

<hr>



### function equivalent 

```C++
template<IsOrigin Lhs, IsOrigin Rhs>
consteval bool astrea::astro::equivalent (
    Lhs lhs,
    Rhs rhs
) 
```




<hr>



### function equivalent 

```C++
template<IsAxis Lhs, IsAxis Rhs>
consteval bool astrea::astro::equivalent (
    Lhs lhs,
    Rhs rhs
) 
```




<hr>



### function equivalent 

_Checks if two frames are equivalent, considering their parent frames and any fixed offsets (spatial or angular)._ 
```C++
template<IsFrame Lhs, IsFrame Rhs>
consteval bool astrea::astro::equivalent (
    Lhs lhs,
    Rhs rhs
) 
```





**Template parameters:**


* `Lhs` The type of the left-hand side frame. 
* `Rhs` The type of the right-hand side frame. 



**Parameters:**


* `lhs` The left-hand side frame instance. 
* `rhs` The right-hand side frame instance. 



**Returns:**

true if both frames are equivalent, false otherwise. 





        

<hr>



### function equivalent 

```C++
template<IsFrame Lhs, IsFrame Rhs>
consteval bool astrea::astro::equivalent (
    Lhs t,
    Rhs u
) 
```





**Template parameters:**


* `Lhs` The type of the left-hand side frame. 
* `Rhs` The type of the right-hand side frame. 



**Parameters:**


* `lhs` The left-hand side frame instance. 
* `rhs` The right-hand side frame instance. 



**Returns:**

true if both frames are equivalent, false otherwise. 





        

<hr>



### function f\_to\_fixed\_string 

_Helper function to convert a double value to a fixed string at compile time. This is used for generating frame names that include the offset values._ 
```C++
template<utilities::double_wrapper _N_>
inline consteval auto astrea::astro::f_to_fixed_string () 
```





**Template parameters:**


* `_N_` The double value to convert to a fixed string, wrapped in a double\_wrapper for constexpr processing. 



**Returns:**

A basic\_fixed\_string representing the double value as a string, suitable for use in frame names. The string will include the numerical value with a specified precision, and will be null-terminated. 





        

<hr>



### function find\_atmospheric\_density 

_Primary template for atmospheric density — returns zero by default._ 
```C++
template<auto _body_>
inline Density astrea::astro::find_atmospheric_density (
    const State & state
) 
```




<hr>



### function find\_atmospheric\_density&lt; moons::Titan &gt; 

```C++
template<>
inline Density astrea::astro::find_atmospheric_density< moons::Titan > (
    const State & state
) 
```




<hr>



### function find\_atmospheric\_density&lt; planets::Earth &gt; 

_Find the atmospheric density for Earth using the configured atmosphere model._ 
```C++
template<>
inline Density astrea::astro::find_atmospheric_density< planets::Earth > (
    const State & state
) 
```





**Parameters:**


* `state` The current [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) state vector (position and velocity). 



**Returns:**

Density The atmospheric density at the position encoded in `state`. 





        

<hr>



### function find\_atmospheric\_density&lt; planets::Mars &gt; 

```C++
template<>
inline Density astrea::astro::find_atmospheric_density< planets::Mars > (
    const State & state
) 
```




<hr>



### function find\_atmospheric\_density&lt; planets::Venus &gt; 

```C++
template<>
inline Density astrea::astro::find_atmospheric_density< planets::Venus > (
    const State & state
) 
```




<hr>



### function find\_axis\_in\_ancestors 

```C++
template<IsAxis Axis_T, IsAxis Axis_U>
inline consteval auto astrea::astro::find_axis_in_ancestors (
    Axis_T axis,
    Axis_U target
) 
```




<hr>



### function find\_common\_ancestor 

```C++
template<IsAxis Axis_T, IsAxis Axis_U>
inline consteval auto astrea::astro::find_common_ancestor (
    Axis_T axis,
    Axis_U axis_u
) 
```




<hr>



### function find\_common\_ancestor 

_Finds the closest common ancestor of the given celestial bodies._ 
```C++
template<IsCelestialReference auto... bodies>
consteval auto astrea::astro::find_common_ancestor () 
```




* 1 body → that body itself.
* ≥ 2 planets → SolarSystemBarycenter (the only common ancestor of independent planets).
* 1 planet → that planet if all other bodies are in its system, else SolarSystemBarycenter.
* 0 planets → only moons, check if they share a parent, else SolarSystemBarycenter.






**Template parameters:**


* `Bodies` The celestial bodies to consider. 



**Returns:**

The common ancestor body value. 





        

<hr>



### function get\_acceleration\_at 

[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _fallback for get\_acceleration\_at._
```C++
template<auto _body_>
inline constexpr CartesianVector < Acceleration, get_parent_frame(_body_, axes::icrf )> astrea::astro::get_acceleration_at (
    const Date & date
) 
```



See get\_position\_at for usage notes. 


        

<hr>



### function get\_acceleration\_at\_impl 

```C++
template<typename Table_T, IsFrame auto frame>
inline constexpr CartesianVector < Acceleration, frame > astrea::astro::get_acceleration_at_impl (
    Date date
) 
```




<hr>



### function get\_acceleration\_relative\_to\_ancestor 

_Get the acceleration of a celestial body relative to the root at a specific date._ 
```C++
template<IsCelestialReference auto body, IsCelestialReference auto ancestor>
constexpr auto astrea::astro::get_acceleration_relative_to_ancestor (
    const Date & date
) 
```





**Parameters:**


* `date` The date at which to get the acceleration. 
* `id` The ID of the celestial body. 



**Returns:**

CartesianVector&lt;Acceleration, frames::solar\_system\_barycenter::icrf&gt; The acceleration vector of the celestial body relative to the root. 





        

<hr>



### function get\_axial\_tilt 

_Get the axial tilt of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr Angle astrea::astro::get_axial_tilt () 
```





**Returns:**

Angle Reference to the axial tilt of the celestial body. 





        

<hr>



### function get\_body\_fixed\_frame 

_Get the body-fixed rotating frame for a celestial body._ 
```C++
template<IsCelestialBody auto body>
inline consteval auto astrea::astro::get_body_fixed_frame () 
```



Returns a Z-rotation body-fixed frame for `body`. For well-known bodies (e.g. Earth) an explicit specialisation in the appropriate platform header returns the canonical named frame instance so that existing DCM specialisations are reused.




**Template parameters:**


* `body` The celestial body NTTP. 



**Returns:**

A constexpr [**BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) value centred at body. 





        

<hr>



### function get\_body\_type 

_Get the type of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline consteval CelestialBodyType astrea::astro::get_body_type () 
```





**Returns:**

CelestialBodyType Reference to the type of the celestial body. 





        

<hr>



### function get\_celestial\_body\_parameters 

```C++
template<auto _body_>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters () = delete
```



Primary template — must be specialised for each body. Uses unconstrained auto _body_ so GCC can match explicit specialisations of the form get\_celestial\_body\_parameters&lt;planets::Earth&gt;(). 


        

<hr>



### function get\_celestial\_body\_parameters&lt; moons::Callisto &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< moons::Callisto > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; moons::Deimos &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< moons::Deimos > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; moons::Europa &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< moons::Europa > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; moons::Ganymede &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< moons::Ganymede > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; moons::Iapetus &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< moons::Iapetus > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; moons::Io &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< moons::Io > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; moons::Moon &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< moons::Moon > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; moons::Oberon &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< moons::Oberon > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; moons::Phobos &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< moons::Phobos > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; moons::Rhea &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< moons::Rhea > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; moons::Titan &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< moons::Titan > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; moons::Titania &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< moons::Titania > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; moons::Triton &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< moons::Triton > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; planets::Earth &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< planets::Earth > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; planets::Jupiter &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< planets::Jupiter > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; planets::Mars &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< planets::Mars > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; planets::Mercury &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< planets::Mercury > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; planets::Neptune &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< planets::Neptune > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; planets::Saturn &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< planets::Saturn > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; planets::Uranus &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< planets::Uranus > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; planets::Venus &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< planets::Venus > () 
```




<hr>



### function get\_celestial\_body\_parameters&lt; star::Sun &gt; 

```C++
template<>
inline consteval CelestialBodyParameters astrea::astro::get_celestial_body_parameters< star::Sun > () 
```




<hr>



### function get\_chebyshev\_table\_coefficients 

_Get the Chebyshev polynomial coefficients for the celestial body at a specific date._ 
```C++
template<typename Table_T>
inline constexpr auto astrea::astro::get_chebyshev_table_coefficients (
    Date date
) 
```





**Template parameters:**


* `Table_T` The Chebyshev table type to use for interpolation. 



**Parameters:**


* `date` The date at which to get the Chebyshev coefficients. 



**Returns:**

A tuple containing references to the x, y, and z Chebyshev coefficient vectors. 





        

<hr>



### function get\_crash\_radius 

_Get the crash radius of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr Distance astrea::astro::get_crash_radius () 
```





**Returns:**

Distance Reference to the crash radius of the celestial body. 





        

<hr>



### function get\_dcm 

_Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date._ 
```C++
template<IsFrame auto frame, IsFrame auto frame_u>
inline constexpr DirectionCosineMatrix < frame, frame_u > astrea::astro::get_dcm (
    const Date & date
) 
```





**Parameters:**


* `date` The date for which to get the DCM. 



**Returns:**

DirectionCosineMatrix&lt;frame, frame\_u&gt; The DCM from frame\_u to frame.


[https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA](https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA)%20TP%2020220014814%20final.pdf 


        

<hr>



### function get\_dcm 

_Get the Direction Cosine Matrix (DCM) for the body-fixed frame at a given date._ 
```C++
template<IsFrame auto in_frame, IsFrame auto out_frame>
inline constexpr DirectionCosineMatrix < in_frame, out_frame > astrea::astro::get_dcm (
    const Date & date
) 
```



Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date.




**Template parameters:**


* `in_frame` The input frame type, must be ICRF and share the same origin as out\_frame. 
* `out_frame` The output frame type, must be FIXED\_ROTATING and share the same origin as in\_frame. 



**Parameters:**


* `date` The date for which to get the DCM. 



**Returns:**

DirectionCosineMatrix&lt;in\_frame, out\_frame&gt; The DCM from in\_frame to out\_frame. 





        

<hr>



### function get\_dcm 

_Get the Direction Cosine Matrix (DCM) for a synodic frame at a given date._ 
```C++
template<IsFrame auto in_frame, IsFrame auto out_frame>
inline constexpr DirectionCosineMatrix < in_frame, out_frame > astrea::astro::get_dcm (
    const Date & date
) 
```



Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date.




**Template parameters:**


* `in_frame` The input frame type, must be ICRF and share the same origin as out\_frame. 
* `out_frame` The output frame type, must be SYNODIC and share the same origin as in\_frame. 



**Parameters:**


* `date` The date for which to get the DCM. 



**Returns:**

DirectionCosineMatrix&lt;in\_frame, out\_frame&gt; The DCM from in\_frame to out\_frame. 





        

<hr>



### function get\_dcm 

_Retrieves the direction cosine matrix representing the fixed angular offset from the parent frame to the given_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _._
```C++
template<IsFrame auto parent, IsFrame auto frame>
inline constexpr DirectionCosineMatrix < parent, frame > astrea::astro::get_dcm (
    const Date & date
) 
```



Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date.




**Template parameters:**


* `frame` The [**FixedOffsetFrame**](structastrea_1_1astro_1_1FixedOffsetFrame.md) type for which to retrieve the DCM. 
* `parent` The parent frame type to which the DCM should be obtained. 



**Returns:**

DirectionCosineMatrix&lt;parent, frame&gt; The direction cosine matrix from the parent frame to the given [**FixedOffsetFrame**](structastrea_1_1astro_1_1FixedOffsetFrame.md). 





        

<hr>



### function get\_dcm 

_DCM from any Earth-centred ICRF frame (including the canonical_ [_**frames::earth::icrf**_](structastrea_1_1astro_1_1frames_1_1earth_1_1icrf.md) _) to any Earth-centred body-fixed frame._
```C++
template<IsFrame auto in_frame, IsFrame auto out_frame>
inline constexpr DirectionCosineMatrix < in_frame, out_frame > astrea::astro::get_dcm (
    const Date & date
) 
```



Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date.


The explicit template&lt;&gt; specialisation was replaced with this constrained template so that HasDcm&lt;earth::icrf, earth::earth\_fixed&gt; (and similar requires-expressions) can find this overload. GCC 15 does not locate explicit template&lt;&gt; specialisations when checking concept requires-expressions with constrained-auto NTTP arguments. 


        

<hr>



### function get\_dcm 

_Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date._ 
```C++
template<IsFrame auto frame, IsFrame auto frame_u>
inline constexpr DCM < frame, frame_u > astrea::astro::get_dcm (
    const Date & date
) = delete
```





**Parameters:**


* `date` The date for which to get the DCM. 



**Returns:**

DirectionCosineMatrix&lt;frame, frame\_u&gt; The DCM from frame\_u to frame.


[https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA](https://ntrs.nasa.gov/api/citations/20220014814/downloads/NASA)%20TP%2020220014814%20final.pdf


Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date.




**Template parameters:**


* `in_frame` The input frame type, must be ICRF and share the same origin as out\_frame. 
* `out_frame` The output frame type, must be FIXED\_ROTATING and share the same origin as in\_frame. 



**Parameters:**


* `date` The date for which to get the DCM. 



**Returns:**

DirectionCosineMatrix&lt;in\_frame, out\_frame&gt; The DCM from in\_frame to out\_frame.


Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date.




**Template parameters:**


* `in_frame` The input frame type, must be ICRF and share the same origin as out\_frame. 
* `out_frame` The output frame type, must be SYNODIC and share the same origin as in\_frame. 



**Parameters:**


* `date` The date for which to get the DCM. 



**Returns:**

DirectionCosineMatrix&lt;in\_frame, out\_frame&gt; The DCM from in\_frame to out\_frame.


Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date.




**Template parameters:**


* `frame` The [**FixedOffsetFrame**](structastrea_1_1astro_1_1FixedOffsetFrame.md) type for which to retrieve the DCM. 
* `parent` The parent frame type to which the DCM should be obtained. 



**Returns:**

DirectionCosineMatrix&lt;parent, frame&gt; The direction cosine matrix from the parent frame to the given [**FixedOffsetFrame**](structastrea_1_1astro_1_1FixedOffsetFrame.md).


Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date.


The explicit template&lt;&gt; specialisation was replaced with this constrained template so that HasDcm&lt;earth::icrf, earth::earth\_fixed&gt; (and similar requires-expressions) can find this overload. GCC 15 does not locate explicit template&lt;&gt; specialisations when checking concept requires-expressions with constrained-auto NTTP arguments. 


        

<hr>



### function get\_dcm&lt; frames::earth::cep, frames::earth::itrf &gt; 

```C++
template<>
inline constexpr DirectionCosineMatrix < frames::earth::cep , frames::earth::itrf > astrea::astro::get_dcm< frames::earth::cep, frames::earth::itrf > (
    const Date & date
) 
```




<hr>



### function get\_dcm&lt; frames::earth::icrf, frames::earth::cep &gt; 

_DCM from_ [_**frames::earth::icrf**_](structastrea_1_1astro_1_1frames_1_1earth_1_1icrf.md) _to_[_**frames::earth::cep**_](structastrea_1_1astro_1_1frames_1_1earth_1_1cep.md) _._
```C++
template<>
inline constexpr DirectionCosineMatrix < frames::earth::icrf , frames::earth::cep > astrea::astro::get_dcm< frames::earth::icrf, frames::earth::cep > (
    const Date & date
) 
```





**Parameters:**


* `date` The date at which to compute the DCM. 



**Returns:**

DirectionCosineMatrix&lt;frames::earth::icrf, frames::earth::cep&gt; The DCM from [**frames::earth::icrf**](structastrea_1_1astro_1_1frames_1_1earth_1_1icrf.md) to [**frames::earth::cep**](structastrea_1_1astro_1_1frames_1_1earth_1_1cep.md) at the given date.




**Note:**

[https://gssc.esa.int/navipedia/index.php?title=ICRF\_to\_CEP](https://gssc.esa.int/navipedia/index.php?title=ICRF_to_CEP) 





        

<hr>



### function get\_dcm\_accel 

```C++
template<IsFrame auto frame, IsFrame auto frame_u>
inline constexpr DcmAccel < frame, frame_u > astrea::astro::get_dcm_accel (
    const Date & date
) = delete
```




<hr>



### function get\_dcm\_from\_root\_frame 

_Retrieves the accumulated direction cosine matrix from the root frame to the given_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _by recursively composing the DCMs along the parent chain._
```C++
template<IsFixedOffsetFrame auto frame>
inline constexpr auto astrea::astro::get_dcm_from_root_frame () 
```




<hr>



### function get\_dcm\_rate 

_Get the Direction Cosine Matrix (DCM) rate for the body-fixed frame at a given date._ 
```C++
template<IsFrame auto in_frame, IsFrame auto out_frame>
inline constexpr DirectionCosineMatrixRate < in_frame, out_frame > astrea::astro::get_dcm_rate (
    const Date & date
) 
```





**Template parameters:**


* `in_frame` The input frame type, must be ICRF and share the same origin as out\_frame. 
* `out_frame` The output frame type, must be FIXED\_ROTATING and share the same origin as in\_frame. 



**Parameters:**


* `date` The date for which to get the DCM rate. 



**Returns:**

DirectionCosineMatrixRate&lt;in\_frame, out\_frame&gt; The DCM rate from in\_frame to out\_frame. 





        

<hr>



### function get\_dcm\_rate 

_Get the Direction Cosine Matrix (DCM) rate for the body-fixed frame at a given date._ 
```C++
template<IsFrame auto frame, IsFrame auto frame_u>
inline constexpr DcmRate < frame, frame_u > astrea::astro::get_dcm_rate (
    const Date & date
) = delete
```





**Template parameters:**


* `in_frame` The input frame type, must be ICRF and share the same origin as out\_frame. 
* `out_frame` The output frame type, must be FIXED\_ROTATING and share the same origin as in\_frame. 



**Parameters:**


* `date` The date for which to get the DCM rate. 



**Returns:**

DirectionCosineMatrixRate&lt;in\_frame, out\_frame&gt; The DCM rate from in\_frame to out\_frame. 





        

<hr>



### function get\_eccentricity 

_Get the eccentricity of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr Unitless astrea::astro::get_eccentricity (
    Date date
) 
```





**Returns:**

Unitless Reference to the eccentricity of the celestial body. 





        

<hr>



### function get\_eccentricity\_rate 

_Get the eccentricity rate of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr BodyUnitlessPerTime astrea::astro::get_eccentricity_rate () 
```





**Returns:**

BodyUnitlessPerTime Reference to the eccentricity rate of the celestial body. 





        

<hr>



### function get\_equitorial\_radius 

_Get the equatorial radius of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr Distance astrea::astro::get_equitorial_radius () 
```





**Returns:**

Distance Reference to the equatorial radius of the celestial body. 





        

<hr>



### function get\_gravity\_coefficient\_file 

_Get the full set of gravitational coefficients of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr auto astrea::astro::get_gravity_coefficient_file () 
```





**Returns:**

Unitless Reference to the full set of gravitational coefficients of the celestial body. 





        

<hr>



### function get\_inclination 

_Get the inclination of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr Angle astrea::astro::get_inclination (
    Date date
) 
```





**Returns:**

Angle Reference to the inclination of the celestial body. 





        

<hr>



### function get\_inclination\_rate 

_Get the inclination rate of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr BodyAngularVelocity astrea::astro::get_inclination_rate () 
```





**Returns:**

BodyAngularVelocity Reference to the inclination rate of the celestial body. 





        

<hr>



### function get\_j2 

_Get the J2 gravitational coefficient of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr Unitless astrea::astro::get_j2 () 
```





**Returns:**

Unitless Reference to the J2 coefficient of the celestial body. 





        

<hr>



### function get\_j3 

_Get the J3 gravitational coefficient of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr Unitless astrea::astro::get_j3 () 
```





**Returns:**

Unitless Reference to the J3 coefficient of the celestial body. 





        

<hr>



### function get\_keplerian\_elements\_at 

_Get the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _elements of a celestial body at a specific date using a linear approximation._
```C++
template<auto _body_>
inline constexpr Keplerian < get_parent_frame(_body_, axes::icrf )> astrea::astro::get_keplerian_elements_at (
    Date date
) 
```



This uses the JPL approximate-positions algorithm: [https://ssd.jpl.nasa.gov/celestial\_bodies/approx\_pos.html](https://ssd.jpl.nasa.gov/celestial_bodies/approx_pos.html)


Bodies that have get\_linear\_expansion\_coefficients specialised use the full perturbation-corrected mean anomaly. All other bodies fall back to the default zero-coefficient implementation (Me = L - w).




**Parameters:**


* `date` The date at which to compute the elements. 



**Returns:**

[**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) The approximate [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) elements at the given date. 





        

<hr>



### function get\_linear\_expansion\_coefficients 

_Get the linear expansion coefficients for the celestial body's mean anomaly correction._ 
```C++
template<IsCelestialReference auto body>
inline constexpr CoefficientPack astrea::astro::get_linear_expansion_coefficients () 
```



Default implementation returns zero coefficients (no perturbation terms), which reduces to Me = L - w. Specialise for bodies that need it (e.g. outer planets).




**Returns:**

CoefficientPack A tuple containing (B, C, S, F) coefficients. 





        

<hr>



### function get\_linear\_expansion\_coefficients&lt; planets::Jupiter &gt; 

_Get the linear expansion coefficients for Jupiter's orbital elements._ 
```C++
template<>
inline constexpr CoefficientPack astrea::astro::get_linear_expansion_coefficients< planets::Jupiter > () 
```



This function returns a tuple containing the coefficients for the linear expansion of Jupiter's orbital elements, which are used to compute the position and velocity of Jupiter over time.




**Returns:**

CoefficientPack A tuple containing the linear expansion coefficients. 





        

<hr>



### function get\_linear\_expansion\_coefficients&lt; planets::Neptune &gt; 

_Get the coefficients for the linear expansion of Neptune's orbital elements._ 
```C++
template<>
inline constexpr CoefficientPack astrea::astro::get_linear_expansion_coefficients< planets::Neptune > () 
```



This function returns a tuple containing the coefficients for the linear expansion of Neptune's orbital elements, which are used to compute the position and velocity of Neptune over time.




**Returns:**

CoefficientPack A tuple containing the coefficients for the linear expansion. 





        

<hr>



### function get\_linear\_expansion\_coefficients&lt; planets::Saturn &gt; 

_Get the coefficients for the linear expansion of Saturn's orbital elements._ 
```C++
template<>
inline constexpr CoefficientPack astrea::astro::get_linear_expansion_coefficients< planets::Saturn > () 
```



This function returns a tuple containing the coefficients used in the linear expansion of Saturn's orbital elements, which are essential for calculating its position and motion over time.




**Returns:**

CoefficientPack A tuple containing the coefficients for the linear expansion. 





        

<hr>



### function get\_linear\_expansion\_coefficients&lt; planets::Uranus &gt; 

_Get the coefficients for the linear expansion of Uranus' orbital elements._ 
```C++
template<>
inline constexpr CoefficientPack astrea::astro::get_linear_expansion_coefficients< planets::Uranus > () 
```



This function returns a tuple containing the coefficients used in the linear expansion of Uranus' orbital elements, which are essential for calculating its position and motion over time.




**Returns:**

CoefficientPack A tuple containing the coefficients for the linear expansion. 





        

<hr>



### function get\_longitude\_of\_perigee 

_Get the longitude of perigee of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr Angle astrea::astro::get_longitude_of_perigee (
    Date date
) 
```





**Returns:**

Angle Reference to the longitude of perigee of the celestial body. 





        

<hr>



### function get\_longitude\_of\_perigee\_rate 

_Get the longitude of perigee rate of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr BodyAngularVelocity astrea::astro::get_longitude_of_perigee_rate () 
```





**Returns:**

BodyAngularVelocity Reference to the longitude of perigee rate of the celestial body. 





        

<hr>



### function get\_mass 

_Get the mass of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr Mass astrea::astro::get_mass () 
```





**Returns:**

Mass Reference to the mass of the celestial body. 





        

<hr>



### function get\_mean\_anomaly 

_Get the mean anomaly of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr Angle astrea::astro::get_mean_anomaly (
    Date date
) 
```





**Returns:**

Angle Reference to the mean anomaly of the celestial body. 





        

<hr>



### function get\_mean\_longitude 

_Get the mean longitude of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr Angle astrea::astro::get_mean_longitude (
    Date date
) 
```





**Returns:**

Angle Reference to the mean longitude of the celestial body. 





        

<hr>



### function get\_mean\_longitude\_rate 

_Get the mean longitude rate of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr BodyAngularVelocity astrea::astro::get_mean_longitude_rate () 
```





**Returns:**

BodyAngularVelocity Reference to the mean longitude rate of the celestial body. 





        

<hr>



### function get\_mu 

_Get the gravitational parameter (mu) of the celestial body or barycenter._ 
```C++
template<IsCelestialReference auto body>
inline constexpr GravParam astrea::astro::get_mu () 
```



For a [**CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md), returns its intrinsic mu from [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md). For a [**Barycenter**](structastrea_1_1astro_1_1Barycenter.md), returns the sum of mu over all member bodies.




**Returns:**

GravParam The gravitational parameter. 





        

<hr>



### function get\_offset\_from\_frame 

_Retrieves the fixed spatial offset from the parent frame to the given_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _._
```C++
template<IsFixedOffsetFrame auto frame>
inline constexpr auto astrea::astro::get_offset_from_frame () 
```




<hr>



### function get\_offset\_from\_root\_frame 

_Retrieves the accumulated fixed spatial offset from the root frame to the given_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _by recursively summing the offsets along the parent chain._
```C++
template<IsFixedOffsetFrame auto frame>
inline constexpr auto astrea::astro::get_offset_from_root_frame () 
```




<hr>



### function get\_parent 

```C++
template<IsOrigin Origin_T>
inline consteval auto astrea::astro::get_parent (
    Origin_T origin
) 
```




<hr>



### function get\_parent 

_Get the parent body of a celestial body._ 
```C++
template<IsCelestialReference auto body>
consteval auto astrea::astro::get_parent () 
```





**Template parameters:**


* `body` The celestial body to get the parent of. 



**Returns:**

The parent body of the given body. 




**Exception:**


* `std::logic_error` if the body does not have a parent. 




        

<hr>



### function get\_parent\_frame 

```C++
template<IsOrigin Origin_T, IsAxis Axis_T>
inline consteval auto astrea::astro::get_parent_frame (
    Origin_T origin,
    Axis_T axis
) 
```




<hr>



### function get\_parent\_name 

```C++
template<IsOrigin Origin_T>
inline consteval auto astrea::astro::get_parent_name (
    Origin_T origin
) 
```




<hr>



### function get\_planet\_from\_pack 

_Returns the single PLANET in the pack (assumes exactly one exists)._ 
```C++
template<IsCelestialReference auto first, IsCelestialReference auto... rest>
consteval auto astrea::astro::get_planet_from_pack () 
```





**Template parameters:**


* `first` The first celestial body in the pack to check. 
* `rest` The remaining celestial bodies in the pack to check. 



**Returns:**

The celestial body in the pack that is a planet. 




**Exception:**


* `std::logic_error` if no planet is found in the pack. 




        

<hr>



### function get\_polar\_radius 

_Get the polar radius of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr Distance astrea::astro::get_polar_radius () 
```





**Returns:**

Distance Reference to the polar radius of the celestial body. 





        

<hr>



### function get\_position\_at 

[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _fallback for get\_position\_at._
```C++
template<auto _body_>
inline constexpr CartesianVector < Distance, get_parent_frame(_body_, axes::icrf )> astrea::astro::get_position_at (
    const Date & date
) 
```



Primary template declarations for ephemeris position/velocity (NTTP-based). Explicit specialisations are provided in planet headers (Chebyshev ephemeris). The primary template definition ([**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) fallback) is provided by [**default\_property\_getters.hpp**](default__property__getters_8hpp.md), which [**celestial\_bodies.hpp**](celestial__bodies_8hpp.md) includes after all planet headers.


Used for bodies that have orbital element parameters but no Chebyshev ephemeris specialisation (e.g. Phobos, Deimos, small moons). The result is expressed in the parent-body ICRF frame derived from the body's parent origin.


Bodies WITH an explicit get\_position\_at specialisation (e.g. Earth, Jupiter when ephemeris is enabled) use that specialisation in preference to this primary template. 


        

<hr>



### function get\_position\_at\_impl 

_Get the position of the celestial body at a specific date in a specified frame using Chebyshev polynomials._ 
```C++
template<typename Table_T, IsFrame auto frame>
inline constexpr CartesianVector < Distance, frame > astrea::astro::get_position_at_impl (
    Date date
) 
```





**Template parameters:**


* `Table_T` The Chebyshev table type to use for interpolation. 
* `frame` The frame type in which to return the position. 



**Parameters:**


* `date` The date at which to get the position of the celestial body. 



**Returns:**

CartesianVector&lt;Distance, frame&gt; The position of the celestial body at the specified date in the specified frame. 





        

<hr>



### function get\_position\_relative\_to\_ancestor 

_Get the position of a celestial body relative to the root at a specific date._ 
```C++
template<IsCelestialReference auto body, IsCelestialReference auto ancestor>
constexpr auto astrea::astro::get_position_relative_to_ancestor (
    const Date & date
) 
```





**Parameters:**


* `date` The date at which to get the position. 
* `id` The ID of the celestial body. 



**Returns:**

CartesianVector&lt;Distance, frames::solar\_system\_barycenter::icrf&gt; The position vector of the celestial body relative to the root. 





        

<hr>



### function get\_relative\_acceleration 

_Get the relative acceleration between two celestial bodies at a specific date._ 
```C++
template<IsCelestialReference auto body1, IsCelestialReference auto body2>
constexpr auto astrea::astro::get_relative_acceleration (
    const Date & date
) 
```





**Parameters:**


* `date` The date at which to get the relative acceleration. 
* `id1` The ID of the first celestial body. 
* `id2` The ID of the second celestial body. 



**Returns:**

CartesianVector&lt;Acceleration, frames::solar\_system\_barycenter::icrf&gt; The relative acceleration vector from id2 to id1. 





        

<hr>



### function get\_relative\_position 

_Get the relative position between two celestial bodies at a specific date._ 
```C++
template<IsCelestialReference auto body1, IsCelestialReference auto body2>
constexpr auto astrea::astro::get_relative_position (
    const Date & date
) 
```





**Parameters:**


* `date` The date at which to get the relative position. 
* `id1` The ID of the first celestial body. 
* `id2` The ID of the second celestial body. 



**Returns:**

CartesianVector&lt;Distance, frame&gt; The relative position vector from id2 to id1. 





        

<hr>



### function get\_relative\_velocity 

_Get the relative position between two celestial bodies at a specific date._ 
```C++
template<IsCelestialReference auto body1, IsCelestialReference auto body2>
constexpr auto astrea::astro::get_relative_velocity (
    const Date & date
) 
```





**Parameters:**


* `date` The date at which to get the relative position. 
* `id1` The ID of the first celestial body. 
* `id2` The ID of the second celestial body. 



**Returns:**

CartesianVector&lt;Velocity, frames::solar\_system\_barycenter::icrf&gt; The relative velocity vector from id2 to id1. 





        

<hr>



### function get\_reverse\_sequence 

_Get the reverse of a Tait-Bryan sequence (e.g., XYZ -&gt; ZYX)._ 
```C++
constexpr RotationSequence astrea::astro::get_reverse_sequence (
    RotationSequence sequence
) 
```




<hr>



### function get\_right\_ascension 

_Get the right ascension of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr Angle astrea::astro::get_right_ascension (
    Date date
) 
```





**Returns:**

Angle Reference to the right ascension of the celestial body. 





        

<hr>



### function get\_right\_ascension\_rate 

_Get the right ascension rate of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr BodyAngularVelocity astrea::astro::get_right_ascension_rate () 
```





**Returns:**

BodyAngularVelocity Reference to the right ascension rate of the celestial body. 





        

<hr>



### function get\_root\_frame 

_Retrieves the root frame of a given fixed offset frame by recursively traversing the parent chain._ 
```C++
template<IsFixedOffsetFrame auto frame>
consteval auto astrea::astro::get_root_frame () 
```





**Template parameters:**


* `frame` The fixed offset frame. 



**Returns:**

The root frame of the given fixed offset frame. 





        

<hr>



### function get\_rotation\_rate 

_Get the rotation rate of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr AngularVelocity astrea::astro::get_rotation_rate () 
```





**Returns:**

AngularVelocity Reference to the rotation rate of the celestial body. 





        

<hr>



### function get\_semimajor 

_Get the semimajor axis of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr Distance astrea::astro::get_semimajor (
    Date date
) 
```





**Returns:**

Distance Reference to the semimajor axis of the celestial body. 





        

<hr>



### function get\_semimajor\_rate 

_Get the semimajor axis rate of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr InterplanetaryVelocity astrea::astro::get_semimajor_rate () 
```





**Returns:**

InterplanetaryVelocity Reference to the semimajor axis rate of the celestial body. 





        

<hr>



### function get\_sequence\_numbers 

```C++
constexpr std::array< int, 3 > astrea::astro::get_sequence_numbers (
    RotationSequence sequence
) 
```




<hr>



### function get\_sidereal\_period 

_Get the sidereal period of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr Time astrea::astro::get_sidereal_period () 
```





**Returns:**

Time Reference to the sidereal period of the celestial body. 





        

<hr>



### function get\_sphere\_of\_influence 

_Get the sphere of influence of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr Distance astrea::astro::get_sphere_of_influence () 
```





**Returns:**

Distance Reference to the sphere of influence of the celestial body. 





        

<hr>



### function get\_time\_since\_reference\_epoch 

```C++
template<IsCelestialBody auto body>
inline constexpr auto astrea::astro::get_time_since_reference_epoch (
    Date date
) 
```




<hr>



### function get\_true\_anomaly 

_Get the true anomaly of the celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr Angle astrea::astro::get_true_anomaly (
    Date date
) 
```





**Returns:**

Angle Reference to the true anomaly of the celestial body. 





        

<hr>



### function get\_variant\_index 

```C++
template<typename VariantType, typename T, std::size_t index>
constexpr std::size_t astrea::astro::get_variant_index () 
```




<hr>



### function get\_velocity\_at 

[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _fallback for get\_velocity\_at._
```C++
template<auto _body_>
inline constexpr CartesianVector < Velocity, get_parent_frame(_body_, axes::icrf )> astrea::astro::get_velocity_at (
    const Date & date
) 
```



See get\_position\_at for usage notes. 


        

<hr>



### function get\_velocity\_at\_impl 

_Get the velocity of the celestial body at a specific date in a specified frame using Chebyshev polynomials._ 
```C++
template<typename Table_T, IsFrame auto frame>
inline constexpr CartesianVector < Velocity, frame > astrea::astro::get_velocity_at_impl (
    Date date
) 
```





**Template parameters:**


* `Table_T` The Chebyshev table type to use for interpolation. 
* `frame` The frame type in which to return the velocity. 



**Parameters:**


* `date` The date at which to get the velocity of the celestial body. 



**Returns:**

CartesianVector&lt;Velocity, frame&gt; The velocity of the celestial body at the specified date in the specified frame. 





        

<hr>



### function get\_velocity\_relative\_to\_ancestor 

_Get the velocity of a celestial body relative to the root at a specific date._ 
```C++
template<IsCelestialReference auto body, IsCelestialReference auto ancestor>
constexpr auto astrea::astro::get_velocity_relative_to_ancestor (
    const Date & date
) 
```





**Parameters:**


* `date` The date at which to get the velocity. 
* `id` The ID of the celestial body. 



**Returns:**

CartesianVector&lt;Velocity, frames::solar\_system\_barycenter::icrf&gt; The velocity vector of the celestial body relative to the root. 





        

<hr>



### function get\_x\_offset\_from\_lla 

_Retrieves the X offset from the given latitude, longitude, and altitude relative to the parent body-fixed frame._ 
```C++
template<IsBodyFixedFrame auto _parent_, Angle _lat_, Angle _lon_, Distance _alt_>
inline consteval auto astrea::astro::get_x_offset_from_lla () 
```





**Template parameters:**


* `_parent_` The parent body-fixed frame. 
* `_lat_` The latitude in the parent frame. 
* `_lon_` The longitude in the parent frame. 
* `_alt_` The altitude in the parent frame. 



**Returns:**

The X offset in the parent frame. 





        

<hr>



### function get\_y\_offset\_from\_lla 

_Retrieves the Y offset from the given latitude, longitude, and altitude relative to the parent body-fixed frame._ 
```C++
template<IsBodyFixedFrame auto _parent_, Angle _lat_, Angle _lon_, Distance _alt_>
inline consteval auto astrea::astro::get_y_offset_from_lla () 
```





**Template parameters:**


* `_parent_` The parent body-fixed frame. 
* `_lat_` The latitude in the parent frame. 
* `_lon_` The longitude in the parent frame. 
* `_alt_` The altitude in the parent frame. 



**Returns:**

The Y offset in the parent frame. 





        

<hr>



### function get\_z\_offset\_from\_lla 

_Retrieves the Z offset from the given latitude, longitude, and altitude relative to the parent body-fixed frame._ 
```C++
template<IsBodyFixedFrame auto _parent_, Angle _lat_, Angle _lon_, Distance _alt_>
inline consteval auto astrea::astro::get_z_offset_from_lla () 
```





**Template parameters:**


* `_parent_` The parent body-fixed frame. 
* `_lat_` The latitude in the parent frame. 
* `_lon_` The longitude in the parent frame. 
* `_alt_` The altitude in the parent frame. 



**Returns:**

The Z offset in the parent frame. 





        

<hr>



### function has\_axis 

```C++
template<IsFrame Frame_T, IsAxis Axis_T>
inline consteval auto astrea::astro::has_axis (
    Frame_T,
    Axis_T
) 
```




<hr>



### function has\_origin 

```C++
template<IsFrame Frame_T, IsOrigin Origin_T>
inline consteval auto astrea::astro::has_origin (
    Frame_T,
    Origin_T
) 
```




<hr>



### function has\_parent 

_Check if a celestial body has a parent body defined._ 
```C++
template<IsCelestialReference auto body>
consteval bool astrea::astro::has_parent () 
```





**Template parameters:**


* `body` The celestial body to check. 



**Returns:**

true if the body has a parent, false otherwise. 





        

<hr>



### function has\_same\_axis 

_Concept to determine if two frames share the same axis._ 
```C++
template<IsFrame T, IsFrame U>
consteval bool astrea::astro::has_same_axis (
    T t,
    U u
) 
```





**Template parameters:**


* `T` The first frame type to check. 
* `U` The second frame type to check. 



**Returns:**

true if both frames share the same axis, false otherwise. 





        

<hr>



### function has\_same\_origin 

_Concept to determine if two frames share the same origin._ 
```C++
template<IsFrame T, IsFrame U>
consteval bool astrea::astro::has_same_origin (
    T t,
    U u
) 
```





**Template parameters:**


* `T` The first frame type to check. 
* `U` The second frame type to check. 



**Returns:**

true if both frames share the same origin, false otherwise. 





        

<hr>



### function has\_same\_parent 

_Helper function to determine if two frames share the same parent frame. This is used in the get\_dcm function for FixedOffsetFrames to ensure that the input and output frames share the same parent frame._ 
```C++
template<IsFrame T, IsFrame U>
consteval bool astrea::astro::has_same_parent (
    T t,
    U u
) 
```





**Template parameters:**


* `T` The type of the first frame. 
* `U` The type of the second frame. 



**Parameters:**


* `t` An instance of the first frame type (not used, only for type deduction). 
* `u` An instance of the second frame type (not used, only for type deduction). 



**Returns:**

true if the frames share the same parent frame, false otherwise. 





        

<hr>



### function has\_same\_parent 

_Specialization of has\_same\_parent for frames that are both derived frames. This checks if the parent types are the same._ 
```C++
template<IsFrame T, IsFrame U>
consteval bool astrea::astro::has_same_parent (
    T t,
    U u
) 
```





**Template parameters:**


* `T` The type of the first frame, must be a derived frame. 
* `U` The type of the second frame, must be a derived frame. 



**Parameters:**


* `t` An instance of the first frame type (not used, only for type deduction). 
* `u` An instance of the second frame type (not used, only for type deduction). 



**Returns:**

true if the frames share the same parent frame, false otherwise. 





        

<hr>



### function has\_same\_parent 

_Specialization of has\_same\_parent for frames that are both root frames. Root frames are considered to share the same parent (themselves)._ 
```C++
template<IsFrame T, IsFrame U>
consteval bool astrea::astro::has_same_parent (
    T t,
    U u
) 
```





**Template parameters:**


* `T` The type of the first frame, must be a root frame. 
* `U` The type of the second frame, must be a root frame. 



**Parameters:**


* `t` An instance of the first frame type (not used, only for type deduction). 
* `u` An instance of the second frame type (not used, only for type deduction). 



**Returns:**

true if the frames share the same parent frame, false otherwise. 





        

<hr>



### function have\_same\_misalignment 

_Checks if two fixed offset frames have the same angular misalignment._ 
```C++
template<IsFixedOffsetFrame Lhs, IsFixedOffsetFrame Rhs>
consteval bool astrea::astro::have_same_misalignment (
    Lhs lhs,
    Rhs rhs
) 
```





**Template parameters:**


* `Lhs` The type of the left-hand side fixed offset frame. 
* `Rhs` The type of the right-hand side fixed offset frame. 



**Parameters:**


* `lhs` The left-hand side fixed offset frame instance. 
* `rhs` The right-hand side fixed offset frame instance. 



**Returns:**

true if both frames have the same angular misalignment, false otherwise. 





        

<hr>



### function have\_same\_offsets 

_Checks if two fixed offset frames have the same spatial offsets._ 
```C++
template<IsFixedOffsetFrame Lhs, IsFixedOffsetFrame Rhs>
consteval bool astrea::astro::have_same_offsets (
    Lhs lhs,
    Rhs rhs
) 
```





**Template parameters:**


* `Lhs` The type of the left-hand side fixed offset frame. 
* `Rhs` The type of the right-hand side fixed offset frame. 



**Parameters:**


* `lhs` The left-hand side fixed offset frame instance. 
* `rhs` The right-hand side fixed offset frame instance. 



**Returns:**

true if both frames have the same spatial offsets, false otherwise. 





        

<hr>



### function is\_aligned\_with\_parent 

_Checks if a fixed offset frame is aligned with its parent frame._ 
```C++
template<IsFixedOffsetFrame Frame_T>
consteval bool astrea::astro::is_aligned_with_parent (
    Frame_T frame
) 
```





**Template parameters:**


* `Frame_T` The type of the fixed offset frame. 



**Parameters:**


* `frame` The fixed offset frame instance. 



**Returns:**

true if the frame is aligned with its parent, false otherwise. 





        

<hr>



### function is\_ancestor\_of 

_Returns true if Ancestor is Body itself or appears anywhere in Body's parent chain._ 
```C++
template<IsCelestialReference auto ancestor, IsCelestialReference auto body>
consteval bool astrea::astro::is_ancestor_of () 
```





**Template parameters:**


* `ancestor` The celestial body to check as an ancestor. 
* `body` The celestial body to check as a descendant. 



**Returns:**

true if Ancestor is the same as Body or is an ancestor of Body, false otherwise. 





        

<hr>



### function is\_proper\_euler\_sequence 

```C++
constexpr bool astrea::astro::is_proper_euler_sequence (
    RotationSequence sequence
) 
```




<hr>



### function is\_same\_body 

_Check if two celestial bodies are the same._ 
```C++
template<IsCelestialReference auto ancestor, IsCelestialReference auto body>
consteval bool astrea::astro::is_same_body () 
```





**Template parameters:**


* `ancestor` The first celestial body to compare. 
* `body` The second celestial body to compare. 



**Returns:**

true if the two bodies are the same, false otherwise. 





        

<hr>



### function julian\_date\_to\_body\_sidereal\_time 

_Compute the equivalent of Greenwich Sidereal Time for an arbitrary celestial body._ 
```C++
template<IsCelestialBody auto body>
inline constexpr Angle astrea::astro::julian_date_to_body_sidereal_time (
    JulianDate date
) 
```



Computes the accumulated rotation angle of the body's prime meridian relative to its inertial reference direction since J2000, using the body's rotation rate.




**Parameters:**


* `date` The Julian date at which to evaluate the angle. 



**Returns:**

Angle The body's prime meridian rotation angle, wrapped to [0, 2π). 





        

<hr>



### function julian\_date\_to\_sidereal\_time 

_Convert a JulianDate to a string representation._ 
```C++
Angle astrea::astro::julian_date_to_sidereal_time (
    const JulianDate & date
) 
```





**Parameters:**


* `date` The JulianDate to convert. 
* `format` The format of the output string, default is "%Y-%m-%d %H:%M:%S". 



**Returns:**

std::string The string representation of the JulianDate.




**Note:**

: This function uses an expantion that only works for Earth-centric sideral times. 





        

<hr>



### function make\_frame 

```C++
template<IsOrigin Origin_T, IsAxis Axis_T>
inline consteval auto astrea::astro::make_frame (
    Origin_T origin,
    Axis_T axis
) 
```




<hr>



### function misalignment\_is\_zero 

```C++
template<IsAxis Axis_T>
consteval bool astrea::astro::misalignment_is_zero (
    Axis_T axis
) 
```




<hr>



### function offset\_is\_zero 

```C++
template<IsOrigin Origin_T>
consteval bool astrea::astro::offset_is_zero (
    Origin_T origin
) 
```




<hr>



### function operator\* 

_Scalar multiplication operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename Value_T, typename Value_U, IsFrame auto frame>
inline constexpr CartesianVector < decltype(Value_T{} *Value_U{}), frame > astrea::astro::operator* (
    const Value_U & scalar,
    const CartesianVector < Value_T, frame > & vec
) 
```





**Template parameters:**


* `T` The type of the vector components. 
* `U` The type of the scalar to multiply with. 



**Parameters:**


* `scalar` The scalar value to multiply with. 
* `vec` The [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to multiply. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt;decltype(Value\_T{} \* Value\_U{}), frame&gt; A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) that is the product of the scalar and the vector. 





        

<hr>



### function operator\* 

_Multiply the matrix by a scalar value (element-wise multiplication)._ 
```C++
template<typename Value_T, typename Value_U, IsFrame auto in_frame, IsFrame auto out_frame>
inline constexpr DcmInterface < decltype(Value_T{} *Value_U{}), in_frame, out_frame > astrea::astro::operator* (
    const Value_T & scalar,
    const DcmInterface < Value_U, in_frame, out_frame > & matrix
) 
```





**Parameters:**


* `scalar` The scalar value to multiply the matrix by. 



**Returns:**

[**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) The resulting matrix from the scalar multiplication. 





        

<hr>



### function operator\* 

_Scalar multiplication operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _with an_[_**InertiaTensor**_](classastrea_1_1astro_1_1InertiaTensor.md) _._
```C++
template<IsFrame auto in_frame, IsFrame auto ref_frame>
CartesianVector < decltype(MomentOfInertia{} *AngularVelocity{}), in_frame > astrea::astro::operator* (
    const InertiaTensor < in_frame > & inertiaTensor,
    const AngularVelocities < in_frame, ref_frame > & vec
) 
```





**Template parameters:**


* `sequence` The specific sequence of rotations (e.g., RotationSequence::ZXZ). 
* `type` Whether the sequence is intrinsic or extrinsic. 
* `in_frame` The input frame type (e.g., ECI, ECEF). 
* `ref_frame` The output frame type (e.g., ECI, ECEF). 



**Parameters:**


* `inertiaTensor` The [**InertiaTensor**](classastrea_1_1astro_1_1InertiaTensor.md) to multiply with. 
* `vec` The [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) to multiply. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt;decltype(MomentOfInertia{} \* AngularVelocity{}), in\_frame&gt; A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) that is the product of the inertia tensor and the angle sequence velocity. 





        

<hr>



### function operator\* 

_Scalar multiplication operator for a quantity multiplied by_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _, resulting in a_[_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename Value_U, IsFrame auto in_frame, IsFrame auto ref_frame>
CartesianVector < decltype(Value_U{} *AngularAcceleration{}), in_frame > astrea::astro::operator* (
    const Value_U & scalar,
    const AngularAccelerations < in_frame, ref_frame > & accel
) 
```





**Template parameters:**


* `Value_U` The type of the scalar quantity. 
* `sequence` The specific sequence of rotations. 
* `type` Whether the sequence is intrinsic or extrinsic. 
* `in_frame` The input frame type. 
* `ref_frame` The output frame type. 



**Parameters:**


* `scalar` The quantity to multiply with. 
* `accel` The [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md) to multiply. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt;decltype(Value\_U{} \* AngularAcceleration{}), in\_frame&gt; The resulting [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md). 





        

<hr>



### function operator\* 

_Scalar multiplication operator for Time multiplied by_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _, resulting in an_[_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._
```C++
template<IsFrame auto in_frame, IsFrame auto ref_frame>
AngularVelocities < in_frame, ref_frame > astrea::astro::operator* (
    const Time & time,
    const AngularAccelerations < in_frame, ref_frame > & accel
) 
```





**Template parameters:**


* `sequence` The specific sequence of rotations. 
* `type` Whether the sequence is intrinsic or extrinsic. 
* `in_frame` The input frame type. 
* `ref_frame` The output frame type. 



**Parameters:**


* `time` The time value to multiply with. 
* `accel` The [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md) to multiply. 



**Returns:**

[**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) The resulting [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md). 





        

<hr>



### function operator\* 

_Scalar multiplication operator for EulerAngless._ 
```C++
template<RotationSequence sequence, RotationType rotation_type, IsFrame auto _in_frame_, IsFrame auto _out_frame_>
EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > astrea::astro::operator* (
    const Unitless & scalar,
    const EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > & vec
) 
```





**Template parameters:**


* `T` The type of the vector components. 
* `U` The type of the scalar to multiply with. 



**Parameters:**


* `scalar` The scalar value to multiply with. 
* `vec` The [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) to multiply. 



**Returns:**

[**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt;sequence, rotation\_type, _in\_frame_, _out\_frame_&gt; A new [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) that is the product of the scalar and the vector. 





        

<hr>



### function operator/ 

_Scalar division operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename Value_T, typename Value_U, IsFrame auto frame>
inline constexpr CartesianVector < decltype(Value_T{} *Value_U{}), frame > astrea::astro::operator/ (
    const Value_U & scalar,
    const CartesianVector < Value_T, frame > & vec
) 
```





**Template parameters:**


* `T` The type of the vector components. 
* `U` The type of the scalar to divide by. 



**Parameters:**


* `scalar` The scalar value to divide by. 
* `vec` The [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to divide. 



**Returns:**

[**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md)&lt;decltype(Value\_T{} \* Value\_U{}), frame&gt; A new [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) that is the quotient of the scalar and the vector. 





        

<hr>



### function operator/ 

_Scalar division operator for EulerAngless._ 
```C++
template<RotationSequence sequence, RotationType rotation_type, IsFrame auto _in_frame_, IsFrame auto _out_frame_>
EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > astrea::astro::operator/ (
    const Unitless & scalar,
    const EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > & vec
) 
```





**Template parameters:**


* `T` The type of the vector components. 
* `U` The type of the scalar to divide by. 



**Parameters:**


* `scalar` The scalar value to divide by. 
* `vec` The [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) to divide. 



**Returns:**

[**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md)&lt;sequence, rotation\_type, _in\_frame_, _out\_frame_&gt; A new [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) that is the quotient of the scalar and the vector. 





        

<hr>



### function operator&lt;&lt; 

_Overload the output stream operator for_ [_**CartesianVector**_](structastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<class Value_T, IsFrame auto frame>
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const CartesianVector < Value_T, frame > & state
) 
```





**Template parameters:**


* `Value_T` The type of the vector components. 
* `frame` The type of the frame. 



**Parameters:**


* `os` The output stream. 
* `state` The [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) to output. 



**Returns:**

The output stream. 





        

<hr>



### function operator&lt;&lt; 

```C++
template<IsCelestialBody auto _body_>
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Cylindrical < _body_ > const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
template<IsCelestialBody auto _body_>
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Geocentric < _body_ > const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
template<IsCelestialBody auto _body_>
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Geodetic < _body_ > const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
template<IsCelestialBody auto _body_>
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Spherical < _body_ > const & elements
) 
```




<hr>



### function operator&lt;&lt; 

_Output stream operator for_ [_**AngularVelocities**_](classastrea_1_1astro_1_1AngularVelocities.md) _._
```C++
template<IsFrame auto in_frame, IsFrame auto ref_frame>
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const AngularVelocities < in_frame, ref_frame > & angleSequenceRate
) 
```





**Template parameters:**


* `sequence` The specific sequence of rotations (e.g., RotationSequence::ZXZ). 
* `type` Whether the sequence is intrinsic or extrinsic. 
* `in_frame` The input frame type (e.g., ECI, ECEF). 
* `ref_frame` The output frame type (e.g., ECI, ECEF). 



**Parameters:**


* `os` The output stream to write to. 
* `angleSequenceRate` The [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) to output. 



**Returns:**

std::ostream& The output stream after writing the [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md). 





        

<hr>



### function operator&lt;&lt; 

_Output stream operator for_ [_**AngularAccelerations**_](classastrea_1_1astro_1_1AngularAccelerations.md) _._
```C++
template<IsFrame auto in_frame, IsFrame auto ref_frame>
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const AngularAccelerations < in_frame, ref_frame > & angleSequenceAccel
) 
```





**Template parameters:**


* `sequence` The specific sequence of rotations (e.g., RotationSequence::ZXZ). 
* `type` Whether the sequence is intrinsic or extrinsic. 
* `in_frame` The input frame type (e.g., ECI, ECEF). 
* `ref_frame` The output frame type (e.g., ECI, ECEF). 



**Parameters:**


* `os` The output stream to write to. 
* `angleSequenceAccel` The [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md) to output. 



**Returns:**

std::ostream& The output stream after writing the [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md). 





        

<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const Attitude & attitude
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const AttitudePartials & attitude
) 
```




<hr>



### function operator&lt;&lt; 

_Output stream operator for_ [_**EulerAngles**_](classastrea_1_1astro_1_1EulerAngles.md) _._
```C++
template<RotationSequence sequence, RotationType rotation_type, IsFrame auto _in_frame_, IsFrame auto _out_frame_>
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const EulerAngles < sequence, rotation_type, _in_frame_, _out_frame_ > & angleSequence
) 
```





**Template parameters:**


* `sequence` The specific sequence of rotations (e.g., RotationSequence::ZXZ). 
* `type` Whether the sequence is intrinsic or extrinsic. 
* `_in_frame_` The input frame type (e.g., ECI, ECEF). 
* `_out_frame_` The output frame type (e.g., ECI, ECEF). 



**Parameters:**


* `os` The output stream to write to. 
* `angleSequence` The [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) to output. 



**Returns:**

std::ostream& The output stream after writing the [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md). 





        

<hr>



### function operator&lt;&lt; 

_Stream insertion operator for the_ [_**Quaternion**_](classastrea_1_1astro_1_1Quaternion.md) _class, allowing for easy printing of quaternion components._
```C++
template<IsFrame auto in_frame, IsFrame auto out_frame>
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const Quaternion < in_frame, out_frame > & quaternion
) 
```





**Template parameters:**


* `in_frame` The input frame type of the quaternion. 
* `out_frame` The output frame type of the quaternion. 



**Parameters:**


* `os` The output stream to insert the quaternion into. 
* `quaternion` The quaternion to be inserted into the stream. 



**Returns:**

A reference to the output stream after inserting the quaternion. 





        

<hr>



### function operator&lt;&lt; 

_Stream insertion operator for the_ [_**QuaternionPartial**_](classastrea_1_1astro_1_1QuaternionPartial.md) _class, allowing for easy printing of quaternion derivative components._
```C++
template<IsFrame auto in_frame, IsFrame auto out_frame>
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const QuaternionPartial < in_frame, out_frame > & quaternion
) 
```





**Template parameters:**


* `in_frame` The input frame type of the quaternion derivative. 
* `out_frame` The output frame type of the quaternion derivative. 



**Parameters:**


* `os` The output stream to insert the quaternion derivative into. 
* `quaternion` The quaternion derivative to be inserted into the stream. 



**Returns:**

A reference to the output stream after inserting the quaternion derivative. 





        

<hr>



### function operator&lt;&lt; 

_Overloaded output stream operator for an optional type._ 
```C++
template<typename T>
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const std::optional< T > & opt
) 
```



This function allows printing the contents of an optional type to an output stream.




**Parameters:**


* `os` The output stream to write to. 
* `opt` The optional object to print. 



**Returns:**

The output stream after writing the optional data. 





        

<hr>



### function operator&lt;&lt; 

_Overloaded output stream operator for_ [_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _._
```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const GeneralPerturbations & gp
) 
```



This function allows printing the contents of a [**GeneralPerturbations**](structastrea_1_1astro_1_1GeneralPerturbations.md) object to an output stream.




**Parameters:**


* `os` The output stream to write to. 
* `gp` The [**GeneralPerturbations**](structastrea_1_1astro_1_1GeneralPerturbations.md) object to print. 



**Returns:**

The output stream after writing the GP data. 





        

<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    TwoLineElements const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
template<IsFrame auto _frame_>
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Cartesian < _frame_ > const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
template<IsFrame auto _frame_>
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    CartesianPartial < _frame_ > const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
template<IsFrame auto _frame_>
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Equinoctial < _frame_ > const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
template<IsFrame auto _frame_>
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    EquinoctialPartial < _frame_ > const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
template<IsFrame auto _frame_>
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Keplerian < _frame_ > const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
template<IsFrame auto _frame_>
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    KeplerianPartial < _frame_ > const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const OrbitalElements & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const OrbitalElementPartials & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const State & state
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const Date & obj
) 
```




<hr>



### function planes\_are\_nearly\_equal 

```C++
inline bool astrea::astro::planes_are_nearly_equal (
    const OrbitalElements & elem1,
    const OrbitalElements & elem2,
    const Unitless & relTol
) 
```




<hr>



### function quantity\_list\_to\_fixed\_string 

_Helper function to convert a list of quantities to a comma-separated fixed string at compile time. This is used for generating frame names that include multiple offset values._ 
```C++
template<auto _first_, auto... _rest_>
inline consteval auto astrea::astro::quantity_list_to_fixed_string () 
```





**Template parameters:**


* `_first_` The first quantity in the list to convert to a fixed string. 
* `_rest_` The remaining quantities in the list to convert to fixed strings. 



**Returns:**

A basic\_fixed\_string representing the list of quantities as a comma-separated string, suitable for use in frame names. The string will be null-terminated. 





        

<hr>



### function quantity\_to\_fixed\_string 

_Helper function to convert a quantity to a fixed string at compile time, including its numerical value and unit symbol. This is used for generating frame names that include the offset values._ 
```C++
template<auto _q_>
inline consteval auto astrea::astro::quantity_to_fixed_string () 
```





**Template parameters:**


* `_q_` The quantity to convert to a fixed string. The quantity must have a unit with a defined symbol. 



**Returns:**

A basic\_fixed\_string representing the quantity as a string, including its numerical value and unit symbol, suitable for use in frame names. The string will be null-terminated. 





        

<hr>



### function throw\_mismatched\_types 

_Throws an exception for mismatched types in orbital elements._ 
```C++
void astrea::astro::throw_mismatched_types () 
```



This function is used to throw an exception when the types of two orbital elements do not match. 

**Exception:**


* `std::runtime_error` with a message indicating the mismatch. 




        

<hr>



### function variant\_contains 

_Checks whether type T is one of the alternatives in VariantType._ 
```C++
template<typename VariantType, typename T, std::size_t index>
constexpr bool astrea::astro::variant_contains () 
```




<hr>



### function wrap\_angle 

_Sanitize an angle to ensure it is within the range [0, 2π)._ 
```C++
inline constexpr Angle astrea::astro::wrap_angle (
    const Angle & angle
) noexcept
```





**Parameters:**


* `ang` The angle to sanitize. 



**Returns:**

The sanitized angle. 





        

<hr>



### function wrap\_angle\_to\_pi 

_Sanitize an angle to ensure it is within the range [0, π)._ 
```C++
inline constexpr Angle astrea::astro::wrap_angle_to_pi (
    const Angle & angle
) noexcept
```





**Parameters:**


* `ang` The angle to sanitize. 



**Returns:**

The sanitized angle. 





        

<hr>
## Public Static Functions Documentation




### function J2000 

_A constant representing the J2000 epoch in Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _format._
```C++
static constexpr JulianDate astrea::astro::J2000 (
    JulianDateClock::duration { 2451545.0 }
) 
```



This is a commonly used epoch in astronomy, representing January 1, 2000, at 12:00 TT. 


        

<hr>



### function MJD0 

_A constant representing the Modified Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _epoch in Julian_[_**Date**_](classastrea_1_1astro_1_1Date.md) _format._
```C++
static constexpr JulianDate astrea::astro::MJD0 (
    JulianDateClock::duration { 2400000.5 }
) 
```



This is used as a reference point for Modified Julian Dates. 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/astro.fwd.hpp`

