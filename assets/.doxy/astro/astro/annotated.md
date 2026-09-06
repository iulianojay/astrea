
# Class List


Here are the classes, structs, unions and interfaces with brief descriptions:

* **namespace** [**astrea**](namespaceastrea.md)     
    * **namespace** [**astro**](namespaceastrea_1_1astro.md)     
        * **class** [**AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md) _Class representing the angular sequence acceleration, which is the time derivative of the angular sequence velocity._     
        * **class** [**AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) _Class representing a sequence of angular velocities (either Euler or Tait-Bryan) for attitude transformations between frames._     
        * **class** [**AtmosphericForce**](classastrea_1_1astro_1_1AtmosphericForce.md) _Class to compute the atmospheric force on a vehicle._     
        * **class** [**Attitude**](classastrea_1_1astro_1_1Attitude.md) _Class representing a set of orientation._     
        * **class** [**AttitudePartials**](classastrea_1_1astro_1_1AttitudePartials.md) _Class representing partial derivatives of orientation._     
        * **struct** [**Axis**](structastrea_1_1astro_1_1Axis.md) 
        * **struct** [**Axis&lt; \_name\_ &gt;**](structastrea_1_1astro_1_1Axis_3_01__name___01_4.md)     
        * **struct** [**Axis&lt; \_name\_, \_parent\_ &gt;**](structastrea_1_1astro_1_1Axis_3_01__name___00_01__parent___01_4.md)     
        * **struct** [**BadConversionRequest**](structastrea_1_1astro_1_1BadConversionRequest.md) 
        * **struct** [**Barycenter**](structastrea_1_1astro_1_1Barycenter.md) 
        * **struct** [**Barycenter&lt; \_name\_ &gt;**](structastrea_1_1astro_1_1Barycenter_3_01__name___01_4.md) _No parent, no members._ 
        * **struct** [**Barycenter&lt; \_name\_, \_parent\_ &gt;**](structastrea_1_1astro_1_1Barycenter_3_01__name___00_01__parent___01_4.md) _With parent, no members._ 
        * **struct** [**BarycentricCoordinateTimeClock**](structastrea_1_1astro_1_1BarycentricCoordinateTimeClock.md) _A clock implementation for Barycentric Coordinate Time (TCB)._     
        * **struct** [**BarycentricDynamicalTimeClock**](structastrea_1_1astro_1_1BarycentricDynamicalTimeClock.md) _A clock implementation for Barycentric Dynamical Time (TDB)._     
        * **struct** [**BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
        * **class** [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) _Class representing a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector in astrodynamics._    
        * **class** [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) _Class representing a partial derivative of a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._    
        * **struct** [**CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) _Class representing a 3D vector in_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _coordinates._    
        * **struct** [**CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._    
        * **struct** [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) _Structure to hold the parameters of a celestial body._     
        * **struct** [**CelestialBodyTypePack**](structastrea_1_1astro_1_1CelestialBodyTypePack.md) _Type-list used to attach member bodies to a_ [_**Barycenter**_](structastrea_1_1astro_1_1Barycenter.md) _._
        * **class** [**CircularRestrictedThreeBodyProblem**](classastrea_1_1astro_1_1CircularRestrictedThreeBodyProblem.md) _Class implementing the Circular Restricted Three-Body Problem equations of motion._     
        * **class** [**Constellation**](classastrea_1_1astro_1_1Constellation.md) _A_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _is a collection of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _, organized into Shells and/or Planes._    
            * **class** [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _Iterator class for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._    
        * **class** [**CowellsMethod**](classastrea_1_1astro_1_1CowellsMethod.md) _Class implementing Cowell's method for equations of motion._     
        * **class** [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) _Class representing a_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector in astrodynamics._    
        * **namespace** [**DOP45**](namespaceastrea_1_1astro_1_1DOP45.md)     
        * **namespace** [**DOP78**](namespaceastrea_1_1astro_1_1DOP78.md)     
        * **class** [**Date**](classastrea_1_1astro_1_1Date.md) _Class representing a date in the astrea astro library._     
        * **struct** [**DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) _Class representing a 3x3 matrix, used for matrices and their rates/accelerations._     
        * **class** [**Deorbit**](classastrea_1_1astro_1_1Deorbit.md) _A class representing a deorbit_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class is used as a placeholder for Events that do not have a defined state or mass._    
        * **struct** [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) _Class representing a direction cosine matrix (DCM) for transforming vectors between state/frames._     
        * **class** [**DirectionCosineMatrixAccel**](structastrea_1_1astro_1_1DirectionCosineMatrixAccel.md) _Class representing a direction cosine matrix (DCM) for transforming vectors between state/frames._     
        * **struct** [**DirectionCosineMatrixRate**](structastrea_1_1astro_1_1DirectionCosineMatrixRate.md) _Class representing a direction cosine matrix (DCM) for transforming vectors between state/frames._     
        * **struct** [**DynamicAxis**](structastrea_1_1astro_1_1DynamicAxis.md) 
        * **struct** [**DynamicFrame**](structastrea_1_1astro_1_1DynamicFrame.md) _Base class for all dynamic state/frames._     
        * **struct** [**DynamicOrigin**](structastrea_1_1astro_1_1DynamicOrigin.md) 
        * **class** [**EquationsOfMotion**](classastrea_1_1astro_1_1EquationsOfMotion.md) _Base class for equations of motion in astrodynamics._     
        * **class** [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) _The_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _class represents the equinoctial orbital elements._    
        * **class** [**EquinoctialPartial**](classastrea_1_1astro_1_1EquinoctialPartial.md) _Class representing a partial derivative of an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._    
        * **class** [**EquinoctialVop**](classastrea_1_1astro_1_1EquinoctialVop.md) _Class implementing the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _VOP equations of motion._    
        * **class** [**EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) _Class representing a sequence of angles (either Euler or Tait-Bryan) for attitude transformations between frames._     
        * **class** [**Event**](classastrea_1_1astro_1_1Event.md) _A class representing a_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class serves as a base for user-defined Events and provides a common interface._    
        * **class** [**EventDetector**](classastrea_1_1astro_1_1EventDetector.md) _A class for detecting events in the astrea astro platform._     
        * **struct** [**ExtraRegisteredFrames**](structastrea_1_1astro_1_1ExtraRegisteredFrames.md) _Trait that users specialize to register additional_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _frames._    
        * **struct** [**FixedOffsetAxis**](structastrea_1_1astro_1_1FixedOffsetAxis.md)     
            * **struct** [**Misalignment**](structastrea_1_1astro_1_1FixedOffsetAxis_1_1Misalignment.md)     
        * **struct** [**FixedOffsetFrame**](structastrea_1_1astro_1_1FixedOffsetFrame.md) _Class representing a fixed offset frame, which is defined by a fixed spatial and/or angular offset from a parent frame._ 
        * **struct** [**FixedOffsetFrame&lt; \_name\_, \_parent\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__name___00_01__parent___00_01__phi___00_01__theta96154ff31cb8eb7d055f0d1372ec2a1e.md) _Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for an angular offset with no spatial misalignment that lets the name be specified._
        * **struct** [**FixedOffsetFrame&lt; \_name\_, \_parent\_, \_x\_, \_y\_, \_z\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__name___00_01__parent___00_01__x___00_01__y___00_01__z___00_01Args_8_8_8_01_4.md) _Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for a spatial offset with no angular misalignment that lets the name be specified._
        * **struct** [**FixedOffsetFrame&lt; \_name\_, \_parent\_, \_x\_, \_y\_, \_z\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__name___00_01__parent___00_01__x___00_01__y___00_682f817510ea200b9f1d77fc37d45a92.md) _Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for a combined spatial and angular offset that lets the name be specified._
        * **struct** [**FixedOffsetFrame&lt; \_parent\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__parent___00_01__phi___00_01__theta___00_01__psi_9e091a834f5483531831878cbc7beda5.md) _Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for a pure angular offset (no spatial offset)._
        * **struct** [**FixedOffsetFrame&lt; \_parent\_, \_x\_, \_y\_, \_z\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__parent___00_01__x___00_01__y___00_01__z___00_01Args_8_8_8_01_4.md) _Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for a pure spatial offset (no angular misalignment)._
        * **struct** [**FixedOffsetFrame&lt; \_parent\_, \_x\_, \_y\_, \_z\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__parent___00_01__x___00_01__y___00_01__z___00_01_3721297a9a90e06cc0beab0e7a99da8d.md) _Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for a combined spatial and angular offset._
        * **struct** [**FixedOffsetOrigin**](structastrea_1_1astro_1_1FixedOffsetOrigin.md)     
            * **struct** [**Offset**](structastrea_1_1astro_1_1FixedOffsetOrigin_1_1Offset.md)     
        * **class** [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) _Class to manage multiple force models and compute the total force on a vehicle._     
        * **struct** [**Frame**](structastrea_1_1astro_1_1Frame.md) 
        * **struct** [**Frame&lt; \_name\_, \_origin\_, \_axis\_ &gt;**](structastrea_1_1astro_1_1Frame_3_01__name___00_01__origin___00_01__axis___01_4.md) [_**Frame**_](structastrea_1_1astro_1_1Frame.md) _with name, origin, and axis (no parent)._    
        * **struct** [**Frame&lt; \_name\_, \_origin\_, \_axis\_, \_parent\_ &gt;**](structastrea_1_1astro_1_1Frame_3_01__name___00_01__origin___00_01__axis___00_01__parent___01_4.md) [_**Frame**_](structastrea_1_1astro_1_1Frame.md) _with name, origin, axis, and parent._    
        * **struct** [**GeneralPerturbations**](structastrea_1_1astro_1_1GeneralPerturbations.md) [_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _structure representing a Ground Position (GP) object from SpaceTrack._    
        * **class** [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) _Class representing a_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector in astrodynamics._    
        * **struct** [**GeocentricAxes**](structastrea_1_1astro_1_1GeocentricAxes.md) 
        * **struct** [**GeocentricCoordinateTimeClock**](structastrea_1_1astro_1_1GeocentricCoordinateTimeClock.md) _A clock implementation for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _Coordinate Time (TCG)._    
        * **class** [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) _Class representing a_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector in astrodynamics._    
        * **class** [**HarrisPriesterAtmosphere**](classastrea_1_1astro_1_1HarrisPriesterAtmosphere.md) _The Harris-Priester atmospheric model for Earth._     
        * **class** [**ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md) _A class representing an impulsive burn_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _. It triggers when the true anomaly wraps around (i.e. at perigee), and applies the total impulsive delta-v from all thrusters to the vehicle in the velocity direction._    
        * **class** [**InertiaTensor**](classastrea_1_1astro_1_1InertiaTensor.md) _A class representing an inertia matrix in the astrea astro platform._     
        * **class** [**Integrator**](classastrea_1_1astro_1_1Integrator.md) [_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _class for numerical propagation of orbital mechanics problems._    
        * **struct** [**IntegratorSettings**](structastrea_1_1astro_1_1IntegratorSettings.md)     
        * **class** [**Interval**](classastrea_1_1astro_1_1Interval.md) _Represents a time interval with a start and end time._     
        * **class** [**J2MeanVop**](classastrea_1_1astro_1_1J2MeanVop.md) _Class implementing the J2 Mean VOP equations of motion._     
        * **class** [**JacchiaRobertsAtmosphere**](classastrea_1_1astro_1_1JacchiaRobertsAtmosphere.md) _The Jaccia-Roberts atmospheric model for Earth._     
        * **struct** [**JplEphemerisTable**](structastrea_1_1astro_1_1JplEphemerisTable.md) _Base class for any JPL_ [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _table._    
        * **struct** [**JulianDateClock**](structastrea_1_1astro_1_1JulianDateClock.md) _A clock implementation for Julian Dates._     
        * **class** [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) _The_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _class represents the_[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _orbital elements._    
        * **class** [**KeplerianPartial**](classastrea_1_1astro_1_1KeplerianPartial.md) _Class representing a partial derivative of a_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._    
        * **class** [**KeplerianVop**](classastrea_1_1astro_1_1KeplerianVop.md) _Class implementing the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _VOP equations of motion._    
        * **class** [**LambertSolver**](classastrea_1_1astro_1_1LambertSolver.md) _Class for solving Lambert's problem._     
            * **struct** [**Solution**](structastrea_1_1astro_1_1LambertSolver_1_1Solution.md) _Result structure for optimal Lambert solutions._     
        * **class** [**LegendreCache**](classastrea_1_1astro_1_1LegendreCache.md) _Class to cache Legendre polynomial coefficients for a given celestial_ _body_ _, degree, and order._    
        * **class** [**NBodyForce**](classastrea_1_1astro_1_1NBodyForce.md) _Class to compute the gravitational force due to multiple celestial bodies._     
        * **class** [**Nrlmsise00Atmosphere**](classastrea_1_1astro_1_1Nrlmsise00Atmosphere.md)     
        * **class** [**NullEvent**](classastrea_1_1astro_1_1NullEvent.md) _A class representing a null_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class is used as a placeholder for Events that do not have a defined state or mass._    
        * **class** [**NullVehicle**](classastrea_1_1astro_1_1NullVehicle.md) _A class representing a null vehicle in the astrea astro platform. This class is used as a placeholder for vehicles that do not have a defined state or mass._     
        * **class** [**OblatenessForce**](classastrea_1_1astro_1_1OblatenessForce.md) _Class to compute the gravitational force due to the oblateness of a celestial_ _body_ _._    
        * **class** [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) _Class representing partial derivatives of orbital elements._     
        * **class** [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) _Class representing a set of orbital elements._     
        * **struct** [**Origin**](structastrea_1_1astro_1_1Origin.md) 
        * **struct** [**Origin&lt; \_name\_ &gt;**](structastrea_1_1astro_1_1Origin_3_01__name___01_4.md)     
        * **struct** [**Origin&lt; \_name\_, \_parent\_ &gt;**](structastrea_1_1astro_1_1Origin_3_01__name___00_01__parent___01_4.md)     
        * **class** [**Payload**](classastrea_1_1astro_1_1Payload.md) [_**Payload**_](classastrea_1_1astro_1_1Payload.md) _class representing a payload on a platform._    
        * **class** [**PayloadParameters**](classastrea_1_1astro_1_1PayloadParameters.md) _Class for storing and managing payload parameters._     
        * **class** [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) _The_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _class represents a platform that can have payloads attached to it. It provides methods to attach payloads and retrieve the list of attached payloads._    
        * **struct** [**Perturbation**](structastrea_1_1astro_1_1Perturbation.md) _Struct to hold the results of a perturbation force computation, including both acceleration and torque._     
        * **class** [**PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md) _Abstract base class for force models in astrodynamics._     
        * **class** [**Plane**](classastrea_1_1astro_1_1Plane.md) _A_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _is a collection of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _that share the same orbital elements._    
        * **class** [**Quaternion**](classastrea_1_1astro_1_1Quaternion.md) _Class representing a quaternion for attitude rotations between frames._     
        * **class** [**QuaternionPartial**](classastrea_1_1astro_1_1QuaternionPartial.md) _Class representing the partial derivative of a quaternion with respect to time, used for integration._     
        * **namespace** [**RK45**](namespaceastrea_1_1astro_1_1RK45.md)     
        * **namespace** [**RKF45**](namespaceastrea_1_1astro_1_1RKF45.md)     
        * **namespace** [**RKF78**](namespaceastrea_1_1astro_1_1RKF78.md)     
        * **struct** [**ReferenceAxes**](structastrea_1_1astro_1_1ReferenceAxes.md) 
        * **class** [**Schedule**](classastrea_1_1astro_1_1Schedule.md) _A class representing a_ [_**Schedule**_](classastrea_1_1astro_1_1Schedule.md) _in the astrea astro library. The_[_**Schedule**_](classastrea_1_1astro_1_1Schedule.md) _is responsible for scheduling and managing Events that are set to trigger at specific Dates during propagation._    
        * **class** [**Shell**](classastrea_1_1astro_1_1Shell.md) _A_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _is a collection of planes, each containing a set of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _. It is used to represent sub-constellations of satellites in orbit._    
            * **class** [**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _Iterator for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._    
        * **struct** [**SolarFluxData**](structastrea_1_1astro_1_1SolarFluxData.md) _Struct to hold solar flux data._     
        * **class** [**SolarRadiationPressure**](classastrea_1_1astro_1_1SolarRadiationPressure.md) _Class to compute the solar radiation pressure force on a spacecraft._     
        * **class** [**SpaceWeatherData**](classastrea_1_1astro_1_1SpaceWeatherData.md) _Class to hold space weather data read from a file._     
        * **struct** [**SpaceWeatherParameters**](structastrea_1_1astro_1_1SpaceWeatherParameters.md) _Struct to hold space weather parameters for a specific date._     
        * **class** [**SpaceWeatherProvider**](classastrea_1_1astro_1_1SpaceWeatherProvider.md) _Lightweight provider that shares an immutable space weather data snapshot. Using this layer of abstraction for now to enable data hot-swapping in the future if needed._     
        * **class** [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) _A class representing a spacecraft in the astrea astro platform. This class encapsulates the properties of a spacecraft, including its mass, dynamic coefficients, and surface areas._     
        * **class** [**Spherical**](classastrea_1_1astro_1_1Spherical.md) _Class representing a_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector in astrodynamics._    
        * **class** [**State**](classastrea_1_1astro_1_1State.md) _Class representing the state of an astronomical object. This class encapsulates the orbital elements, epoch, and the astrodynamics system that the state belongs to. It also optionally includes the attitude of the object as a quaternion._     
        * **class** [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) _Class to manage the history of states for an object over date._     
        * **class** [**StatePartial**](classastrea_1_1astro_1_1StatePartial.md)     
        * **class** [**StateTransitionMatrix**](classastrea_1_1astro_1_1StateTransitionMatrix.md)     
        * **struct** [**StepWatcher**](structastrea_1_1astro_1_1StepWatcher.md) _Function wrapper class for watching the state of the integrator at each step. This can be used for plotting or logging the state during propagation._     
        * **struct** [**SynodicAxis**](structastrea_1_1astro_1_1SynodicAxis.md) [_**Axis**_](structastrea_1_1astro_1_1Axis.md) _defined by the line connecting two celestial bodies and the plane of motion of the secondary around the primary._    
        * **struct** [**SynodicFrame**](structastrea_1_1astro_1_1SynodicFrame.md) _Synodic frame defined by the line connecting two celestial bodies and the plane of motion of the secondary around the primary._ 
        * **struct** [**TerrestrialTimeClock**](structastrea_1_1astro_1_1TerrestrialTimeClock.md) _A clock implementation for Terrestrial Time (TT)._     
        * **class** [**Thruster**](classastrea_1_1astro_1_1Thruster.md) [_**Thruster**_](classastrea_1_1astro_1_1Thruster.md) _class representing a thruster on a platform._    
        * **class** [**ThrusterParameters**](classastrea_1_1astro_1_1ThrusterParameters.md) _Class for storing and managing thruster parameters._     
        * **struct** [**TopocentricFrame**](structastrea_1_1astro_1_1TopocentricFrame.md) _A frame that is topocentric to a given body, defined relative to some body-fixed frame by a specific latitude, longitude, and altitude._     
        * **class** [**TurnThrustersOff**](classastrea_1_1astro_1_1TurnThrustersOff.md) _A class representing a_ [_**TurnThrustersOff**_](classastrea_1_1astro_1_1TurnThrustersOff.md) __[_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class is used as a placeholder for Events that do not have a defined state or mass._    
        * **class** [**TurnThrustersOn**](classastrea_1_1astro_1_1TurnThrustersOn.md) _A class representing a_ [_**TurnThrustersOn**_](classastrea_1_1astro_1_1TurnThrustersOn.md) __[_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class is used as a placeholder for Events that do not have a defined state or mass._    
        * **class** [**TwoBody**](classastrea_1_1astro_1_1TwoBody.md) _Class implementing the Two Body equations of motion._     
        * **class** [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) _Class representing the two-line element (TLE) format for orbital data._     
        * **class** [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) _A class representing a vehicle in the astrea astro platform. This class serves as a base for user-defined vehicles and provides a common interface._     
        * **namespace** [**axes**](namespaceastrea_1_1astro_1_1axes.md)     
            * **struct** [**cep**](structastrea_1_1astro_1_1axes_1_1cep.md) 
            * **struct** [**icrf**](structastrea_1_1astro_1_1axes_1_1icrf.md) 
            * **struct** [**j2000**](structastrea_1_1astro_1_1axes_1_1j2000.md) 
        * **namespace** [**barycenters**](namespaceastrea_1_1astro_1_1barycenters.md)     
            * **struct** [**EarthMoonBarycenter**](structastrea_1_1astro_1_1barycenters_1_1EarthMoonBarycenter.md) 
            * **struct** [**EarthSunBarycenter**](structastrea_1_1astro_1_1barycenters_1_1EarthSunBarycenter.md) 
            * **struct** [**JupiterSunBarycenter**](structastrea_1_1astro_1_1barycenters_1_1JupiterSunBarycenter.md) 
            * **struct** [**MarsSunBarycenter**](structastrea_1_1astro_1_1barycenters_1_1MarsSunBarycenter.md) 
            * **struct** [**MercurySunBarycenter**](structastrea_1_1astro_1_1barycenters_1_1MercurySunBarycenter.md) 
            * **struct** [**NeptuneSunBarycenter**](structastrea_1_1astro_1_1barycenters_1_1NeptuneSunBarycenter.md) 
            * **struct** [**SaturnSunBarycenter**](structastrea_1_1astro_1_1barycenters_1_1SaturnSunBarycenter.md) 
            * **struct** [**SolarSystemBarycenter**](structastrea_1_1astro_1_1barycenters_1_1SolarSystemBarycenter.md) 
            * **struct** [**UranusSunBarycenter**](structastrea_1_1astro_1_1barycenters_1_1UranusSunBarycenter.md) 
            * **struct** [**VenusSunBarycenter**](structastrea_1_1astro_1_1barycenters_1_1VenusSunBarycenter.md) 
        * **namespace** [**detail**](namespaceastrea_1_1astro_1_1detail.md)     
            * **struct** [**AxisBase**](structastrea_1_1astro_1_1detail_1_1AxisBase.md)     
            * **struct** [**BarycenterBase**](structastrea_1_1astro_1_1detail_1_1BarycenterBase.md) 
            * **struct** [**BodyFixedFrameBase**](structastrea_1_1astro_1_1detail_1_1BodyFixedFrameBase.md) 
            * **struct** [**CelestialBodyBase**](structastrea_1_1astro_1_1detail_1_1CelestialBodyBase.md) 
            * **struct** [**EventInner**](structastrea_1_1astro_1_1detail_1_1EventInner.md) _A template class for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _inner implementations._    
            * **struct** [**EventInnerBase**](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md) _Pure virtual base class for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _inner implementations._    
            * **struct** [**FrameBase**](structastrea_1_1astro_1_1detail_1_1FrameBase.md) _Empty base class for all frames in astrea. This allows us to use std::derived\_from to check if a type is a frame._     
            * **struct** [**OriginBase**](structastrea_1_1astro_1_1detail_1_1OriginBase.md)     
            * **struct** [**SynodicFrameBase**](structastrea_1_1astro_1_1detail_1_1SynodicFrameBase.md) 
            * **struct** [**VehicleInner**](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) _A template class for vehicle inner implementations._     
            * **struct** [**VehicleInnerBase**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md) _Pure virtual base class for vehicle inner implementations._     
            * **struct** [**apply\_nttp\_template**](structastrea_1_1astro_1_1detail_1_1apply__nttp__template.md) 
            * **struct** [**apply\_nttp\_template&lt; T, std::tuple&lt; Frames... &gt; &gt;**](structastrea_1_1astro_1_1detail_1_1apply__nttp__template_3_01T_00_01std_1_1tuple_3_01Frames_8_8_8_01_4_01_4.md)     
            * **struct** [**apply\_template**](structastrea_1_1astro_1_1detail_1_1apply__template.md) 
            * **struct** [**apply\_template&lt; T, std::tuple&lt; Frames... &gt; &gt;**](structastrea_1_1astro_1_1detail_1_1apply__template_3_01T_00_01std_1_1tuple_3_01Frames_8_8_8_01_4_01_4.md)     
            * **struct** [**multi\_tuple\_cat**](structastrea_1_1astro_1_1detail_1_1multi__tuple__cat.md) 
            * **struct** [**multi\_tuple\_cat&lt; First, Rest... &gt;**](structastrea_1_1astro_1_1detail_1_1multi__tuple__cat_3_01First_00_01Rest_8_8_8_01_4.md)     
            * **struct** [**multi\_tuple\_cat&lt; Only &gt;**](structastrea_1_1astro_1_1detail_1_1multi__tuple__cat_3_01Only_01_4.md)     
            * **struct** [**multi\_tuple\_cat&lt;&gt;**](structastrea_1_1astro_1_1detail_1_1multi__tuple__cat_3_4.md)     
            * **struct** [**tuple\_cat\_types**](structastrea_1_1astro_1_1detail_1_1tuple__cat__types.md) 
            * **struct** [**tuple\_cat\_types&lt; std::tuple&lt; As... &gt;, std::tuple&lt; Bs... &gt; &gt;**](structastrea_1_1astro_1_1detail_1_1tuple__cat__types_3_01std_1_1tuple_3_01As_8_8_8_01_4_00_01std8cf8a2c8692dfec60c2615039d60391f.md)     
            * **struct** [**tuple\_to\_variant**](structastrea_1_1astro_1_1detail_1_1tuple__to__variant.md) 
            * **struct** [**tuple\_to\_variant&lt; std::tuple&lt; Ts... &gt;, Extra... &gt;**](structastrea_1_1astro_1_1detail_1_1tuple__to__variant_3_01std_1_1tuple_3_01Ts_8_8_8_01_4_00_01Extra_8_8_8_01_4.md)     
        * **namespace** [**frames**](namespaceastrea_1_1astro_1_1frames.md)     
            * **struct** [**EastNorthUp**](structastrea_1_1astro_1_1frames_1_1EastNorthUp.md) _Class representing the East, North, Up (ENU) frame._     
            * **struct** [**EastNorthUpTag**](structastrea_1_1astro_1_1frames_1_1EastNorthUpTag.md) [_**Frame**_](structastrea_1_1astro_1_1Frame.md) _tag type for_[_**EastNorthUp**_](structastrea_1_1astro_1_1frames_1_1EastNorthUp.md) _, defined outside the class to allow use as a_[_**DynamicFrame**_](structastrea_1_1astro_1_1DynamicFrame.md) _NTTP._    
            * **struct** [**LocalHorizontalLocalVertical**](structastrea_1_1astro_1_1frames_1_1LocalHorizontalLocalVertical.md) _Class representing the Local Horizontal, Local Vertical (LVLH) frame._     
            * **struct** [**LvlhTag**](structastrea_1_1astro_1_1frames_1_1LvlhTag.md) [_**Frame**_](structastrea_1_1astro_1_1Frame.md) _tag type for_[_**LocalHorizontalLocalVertical**_](structastrea_1_1astro_1_1frames_1_1LocalHorizontalLocalVertical.md) _, defined outside the class to allow use as a_[_**DynamicFrame**_](structastrea_1_1astro_1_1DynamicFrame.md) _NTTP._    
            * **struct** [**Perifocal**](structastrea_1_1astro_1_1frames_1_1Perifocal.md) _Class representing the_ [_**Perifocal**_](structastrea_1_1astro_1_1frames_1_1Perifocal.md) _(PQW) frame: P towards periapsis, W along the angular momentum vector, and Q completing the right-handed triad in the orbital plane._    
            * **struct** [**PerifocalTag**](structastrea_1_1astro_1_1frames_1_1PerifocalTag.md) [_**Frame**_](structastrea_1_1astro_1_1Frame.md) _tag type for_[_**Perifocal**_](structastrea_1_1astro_1_1frames_1_1Perifocal.md) _, defined outside the class to allow use as a_[_**DynamicFrame**_](structastrea_1_1astro_1_1DynamicFrame.md) _NTTP._    
            * **struct** [**RadialInTrackCrossTrack**](structastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) _Class representing the Radial, In-Track, Cross-Track (RIC) frame._     
            * **struct** [**RicTag**](structastrea_1_1astro_1_1frames_1_1RicTag.md) [_**Frame**_](structastrea_1_1astro_1_1Frame.md) _tag type for_[_**RadialInTrackCrossTrack**_](structastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) _, defined outside the class to allow use as a_[_**DynamicFrame**_](structastrea_1_1astro_1_1DynamicFrame.md) _NTTP._    
            * **struct** [**VelocityNormalBinormal**](structastrea_1_1astro_1_1frames_1_1VelocityNormalBinormal.md) _Class representing the Velocity, Normal, Binormal (VNB) frame._     
            * **struct** [**VnbTag**](structastrea_1_1astro_1_1frames_1_1VnbTag.md) [_**Frame**_](structastrea_1_1astro_1_1Frame.md) _tag type for_[_**VelocityNormalBinormal**_](structastrea_1_1astro_1_1frames_1_1VelocityNormalBinormal.md) _, defined outside the class to allow use as a_[_**DynamicFrame**_](structastrea_1_1astro_1_1DynamicFrame.md) _NTTP._    
            * **namespace** [**callisto**](namespaceastrea_1_1astro_1_1frames_1_1callisto.md)     
                * **struct** [**callisto\_fixed**](structastrea_1_1astro_1_1frames_1_1callisto_1_1callisto__fixed.md) 
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1callisto_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1callisto_1_1j2000.md) 
            * **namespace** [**deimos**](namespaceastrea_1_1astro_1_1frames_1_1deimos.md)     
                * **struct** [**deimos\_fixed**](structastrea_1_1astro_1_1frames_1_1deimos_1_1deimos__fixed.md) 
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1deimos_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1deimos_1_1j2000.md) 
            * **namespace** [**dynamic**](namespaceastrea_1_1astro_1_1frames_1_1dynamic.md)     
                * **struct** [**body**](structastrea_1_1astro_1_1frames_1_1dynamic_1_1body.md) 
            * **namespace** [**earth**](namespaceastrea_1_1astro_1_1frames_1_1earth.md)     
                * **struct** [**cep**](structastrea_1_1astro_1_1frames_1_1earth_1_1cep.md) 
                * **struct** [**earth\_fixed**](structastrea_1_1astro_1_1frames_1_1earth_1_1earth__fixed.md) 
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1earth_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1earth_1_1j2000.md) 
            * **namespace** [**earth\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1earth__barycenter.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1earth__barycenter_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1earth__barycenter_1_1j2000.md) 
            * **namespace** [**earth\_moon\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1earth__moon__barycenter.md)     
                * **struct** [**ems**](structastrea_1_1astro_1_1frames_1_1earth__moon__barycenter_1_1ems.md) 
            * **namespace** [**earth\_sun\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1earth__sun__barycenter.md)     
                * **struct** [**ess**](structastrea_1_1astro_1_1frames_1_1earth__sun__barycenter_1_1ess.md) 
            * **namespace** [**europa**](namespaceastrea_1_1astro_1_1frames_1_1europa.md)     
                * **struct** [**europa\_fixed**](structastrea_1_1astro_1_1frames_1_1europa_1_1europa__fixed.md) 
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1europa_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1europa_1_1j2000.md) 
            * **namespace** [**ganymede**](namespaceastrea_1_1astro_1_1frames_1_1ganymede.md)     
                * **struct** [**ganymede\_fixed**](structastrea_1_1astro_1_1frames_1_1ganymede_1_1ganymede__fixed.md) 
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1ganymede_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1ganymede_1_1j2000.md) 
            * **namespace** [**iapetus**](namespaceastrea_1_1astro_1_1frames_1_1iapetus.md)     
                * **struct** [**iapetus\_fixed**](structastrea_1_1astro_1_1frames_1_1iapetus_1_1iapetus__fixed.md) 
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1iapetus_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1iapetus_1_1j2000.md) 
            * **namespace** [**io**](namespaceastrea_1_1astro_1_1frames_1_1io.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1io_1_1icrf.md) 
                * **struct** [**io\_fixed**](structastrea_1_1astro_1_1frames_1_1io_1_1io__fixed.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1io_1_1j2000.md) 
            * **namespace** [**jupiter**](namespaceastrea_1_1astro_1_1frames_1_1jupiter.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1jupiter_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1jupiter_1_1j2000.md) 
                * **struct** [**jupiter\_fixed**](structastrea_1_1astro_1_1frames_1_1jupiter_1_1jupiter__fixed.md) 
            * **namespace** [**jupiter\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1jupiter__barycenter.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1jupiter__barycenter_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1jupiter__barycenter_1_1j2000.md) 
            * **namespace** [**jupiter\_sun\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1jupiter__sun__barycenter.md)     
                * **struct** [**jss**](structastrea_1_1astro_1_1frames_1_1jupiter__sun__barycenter_1_1jss.md) 
            * **namespace** [**mars**](namespaceastrea_1_1astro_1_1frames_1_1mars.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1mars_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1mars_1_1j2000.md) 
                * **struct** [**mars\_fixed**](structastrea_1_1astro_1_1frames_1_1mars_1_1mars__fixed.md) 
            * **namespace** [**mars\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1mars__barycenter.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1mars__barycenter_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1mars__barycenter_1_1j2000.md) 
            * **namespace** [**mars\_sun\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1mars__sun__barycenter.md)     
                * **struct** [**mss**](structastrea_1_1astro_1_1frames_1_1mars__sun__barycenter_1_1mss.md) 
            * **namespace** [**mercury**](namespaceastrea_1_1astro_1_1frames_1_1mercury.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1mercury_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1mercury_1_1j2000.md) 
                * **struct** [**mercury\_fixed**](structastrea_1_1astro_1_1frames_1_1mercury_1_1mercury__fixed.md) 
            * **namespace** [**mercury\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1mercury__barycenter.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1mercury__barycenter_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1mercury__barycenter_1_1j2000.md) 
            * **namespace** [**mercury\_sun\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1mercury__sun__barycenter.md)     
                * **struct** [**mss**](structastrea_1_1astro_1_1frames_1_1mercury__sun__barycenter_1_1mss.md) 
            * **namespace** [**moon**](namespaceastrea_1_1astro_1_1frames_1_1moon.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1moon_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1moon_1_1j2000.md) 
                * **struct** [**moon\_fixed**](structastrea_1_1astro_1_1frames_1_1moon_1_1moon__fixed.md) 
            * **namespace** [**neptune**](namespaceastrea_1_1astro_1_1frames_1_1neptune.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1neptune_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1neptune_1_1j2000.md) 
                * **struct** [**neptune\_fixed**](structastrea_1_1astro_1_1frames_1_1neptune_1_1neptune__fixed.md) 
            * **namespace** [**neptune\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1neptune__barycenter.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1neptune__barycenter_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1neptune__barycenter_1_1j2000.md) 
            * **namespace** [**neptune\_sun\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1neptune__sun__barycenter.md)     
                * **struct** [**nss**](structastrea_1_1astro_1_1frames_1_1neptune__sun__barycenter_1_1nss.md) 
            * **namespace** [**oberon**](namespaceastrea_1_1astro_1_1frames_1_1oberon.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1oberon_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1oberon_1_1j2000.md) 
                * **struct** [**oberon\_fixed**](structastrea_1_1astro_1_1frames_1_1oberon_1_1oberon__fixed.md) 
            * **namespace** [**phobos**](namespaceastrea_1_1astro_1_1frames_1_1phobos.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1phobos_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1phobos_1_1j2000.md) 
                * **struct** [**phobos\_fixed**](structastrea_1_1astro_1_1frames_1_1phobos_1_1phobos__fixed.md) 
            * **namespace** [**rhea**](namespaceastrea_1_1astro_1_1frames_1_1rhea.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1rhea_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1rhea_1_1j2000.md) 
                * **struct** [**rhea\_fixed**](structastrea_1_1astro_1_1frames_1_1rhea_1_1rhea__fixed.md) 
            * **namespace** [**saturn**](namespaceastrea_1_1astro_1_1frames_1_1saturn.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1saturn_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1saturn_1_1j2000.md) 
                * **struct** [**saturn\_fixed**](structastrea_1_1astro_1_1frames_1_1saturn_1_1saturn__fixed.md) 
            * **namespace** [**saturn\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1saturn__barycenter.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1saturn__barycenter_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1saturn__barycenter_1_1j2000.md) 
            * **namespace** [**saturn\_sun\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1saturn__sun__barycenter.md)     
                * **struct** [**sss**](structastrea_1_1astro_1_1frames_1_1saturn__sun__barycenter_1_1sss.md) 
            * **namespace** [**solar\_system\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1solar__system__barycenter.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1solar__system__barycenter_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1solar__system__barycenter_1_1j2000.md) 
            * **namespace** [**sun**](namespaceastrea_1_1astro_1_1frames_1_1sun.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1sun_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1sun_1_1j2000.md) 
            * **namespace** [**titan**](namespaceastrea_1_1astro_1_1frames_1_1titan.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1titan_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1titan_1_1j2000.md) 
                * **struct** [**titan\_fixed**](structastrea_1_1astro_1_1frames_1_1titan_1_1titan__fixed.md) 
            * **namespace** [**titania**](namespaceastrea_1_1astro_1_1frames_1_1titania.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1titania_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1titania_1_1j2000.md) 
                * **struct** [**titania\_fixed**](structastrea_1_1astro_1_1frames_1_1titania_1_1titania__fixed.md) 
            * **namespace** [**triton**](namespaceastrea_1_1astro_1_1frames_1_1triton.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1triton_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1triton_1_1j2000.md) 
                * **struct** [**triton\_fixed**](structastrea_1_1astro_1_1frames_1_1triton_1_1triton__fixed.md) 
            * **namespace** [**uranus**](namespaceastrea_1_1astro_1_1frames_1_1uranus.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1uranus_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1uranus_1_1j2000.md) 
                * **struct** [**uranus\_fixed**](structastrea_1_1astro_1_1frames_1_1uranus_1_1uranus__fixed.md) 
            * **namespace** [**uranus\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1uranus__barycenter.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1uranus__barycenter_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1uranus__barycenter_1_1j2000.md) 
            * **namespace** [**uranus\_sun\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1uranus__sun__barycenter.md)     
                * **struct** [**uss**](structastrea_1_1astro_1_1frames_1_1uranus__sun__barycenter_1_1uss.md) 
            * **namespace** [**venus**](namespaceastrea_1_1astro_1_1frames_1_1venus.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1venus_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1venus_1_1j2000.md) 
                * **struct** [**venus\_fixed**](structastrea_1_1astro_1_1frames_1_1venus_1_1venus__fixed.md) 
            * **namespace** [**venus\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1venus__barycenter.md)     
                * **struct** [**icrf**](structastrea_1_1astro_1_1frames_1_1venus__barycenter_1_1icrf.md) 
                * **struct** [**j2000**](structastrea_1_1astro_1_1frames_1_1venus__barycenter_1_1j2000.md) 
            * **namespace** [**venus\_sun\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1venus__sun__barycenter.md)     
                * **struct** [**vss**](structastrea_1_1astro_1_1frames_1_1venus__sun__barycenter_1_1vss.md) 
        * **struct** [**is\_cartesian\_vector**](structastrea_1_1astro_1_1is__cartesian__vector.md) 
        * **struct** [**is\_cartesian\_vector&lt; CartesianVector&lt; Value\_T, frame &gt; &gt;**](structastrea_1_1astro_1_1is__cartesian__vector_3_01CartesianVector_3_01Value__T_00_01frame_01_4_01_4.md) 
        * **namespace** [**moons**](namespaceastrea_1_1astro_1_1moons.md)     
            * **class** [**Callisto**](structastrea_1_1astro_1_1moons_1_1Callisto.md) _Represents the_ [_**Callisto**_](structastrea_1_1astro_1_1moons_1_1Callisto.md) _celestial body._
            * **class** [**Deimos**](structastrea_1_1astro_1_1moons_1_1Deimos.md) _Represents the_ [_**Deimos**_](structastrea_1_1astro_1_1moons_1_1Deimos.md) _celestial body._
            * **class** [**Europa**](structastrea_1_1astro_1_1moons_1_1Europa.md) _Represents the_ [_**Europa**_](structastrea_1_1astro_1_1moons_1_1Europa.md) _celestial body._
            * **class** [**Ganymede**](structastrea_1_1astro_1_1moons_1_1Ganymede.md) _Represents the_ [_**Ganymede**_](structastrea_1_1astro_1_1moons_1_1Ganymede.md) _celestial body._
            * **class** [**Iapetus**](structastrea_1_1astro_1_1moons_1_1Iapetus.md) _Represents the_ [_**Iapetus**_](structastrea_1_1astro_1_1moons_1_1Iapetus.md) _celestial body._
            * **class** [**Io**](structastrea_1_1astro_1_1moons_1_1Io.md) _Represents the_ [_**Io**_](structastrea_1_1astro_1_1moons_1_1Io.md) _celestial body._
            * **class** [**Moon**](structastrea_1_1astro_1_1moons_1_1Moon.md) _Represents the_ [_**Moon**_](structastrea_1_1astro_1_1moons_1_1Moon.md) _celestial body._
            * **class** [**Oberon**](structastrea_1_1astro_1_1moons_1_1Oberon.md) _Represents the_ [_**Oberon**_](structastrea_1_1astro_1_1moons_1_1Oberon.md) _celestial body._
            * **class** [**Phobos**](structastrea_1_1astro_1_1moons_1_1Phobos.md) _Represents the_ [_**Phobos**_](structastrea_1_1astro_1_1moons_1_1Phobos.md) _celestial body._
            * **class** [**Rhea**](structastrea_1_1astro_1_1moons_1_1Rhea.md) _Represents the_ [_**Rhea**_](structastrea_1_1astro_1_1moons_1_1Rhea.md) _celestial body._
            * **class** [**Titan**](structastrea_1_1astro_1_1moons_1_1Titan.md) _Represents the_ [_**Titan**_](structastrea_1_1astro_1_1moons_1_1Titan.md) _celestial body._
            * **class** [**Titania**](structastrea_1_1astro_1_1moons_1_1Titania.md) _Represents the_ [_**Titania**_](structastrea_1_1astro_1_1moons_1_1Titania.md) _celestial body._
            * **class** [**Triton**](structastrea_1_1astro_1_1moons_1_1Triton.md) _Represents the_ [_**Triton**_](structastrea_1_1astro_1_1moons_1_1Triton.md) _celestial body._
        * **namespace** [**planets**](namespaceastrea_1_1astro_1_1planets.md)     
            * **struct** [**BatesProfileParams**](structastrea_1_1astro_1_1planets_1_1BatesProfileParams.md)     
            * **class** [**Earth**](structastrea_1_1astro_1_1planets_1_1Earth.md) _Represents the_ [_**Earth**_](structastrea_1_1astro_1_1planets_1_1Earth.md) _celestial body._
            * **class** [**Jupiter**](structastrea_1_1astro_1_1planets_1_1Jupiter.md) _Represents the_ [_**Jupiter**_](structastrea_1_1astro_1_1planets_1_1Jupiter.md) _celestial body._
            * **class** [**Mars**](structastrea_1_1astro_1_1planets_1_1Mars.md) _Represents the_ [_**Mars**_](structastrea_1_1astro_1_1planets_1_1Mars.md) _celestial body._
            * **class** [**Mercury**](structastrea_1_1astro_1_1planets_1_1Mercury.md) _Represents the_ [_**Mercury**_](structastrea_1_1astro_1_1planets_1_1Mercury.md) _celestial body._
            * **class** [**Neptune**](structastrea_1_1astro_1_1planets_1_1Neptune.md) _Represents the_ [_**Neptune**_](structastrea_1_1astro_1_1planets_1_1Neptune.md) _celestial body._
            * **class** [**Nrlmsise00Atmosphere**](classastrea_1_1astro_1_1planets_1_1Nrlmsise00Atmosphere.md) _The NRLMSISE-00 atmospheric model for_ [_**Earth**_](structastrea_1_1astro_1_1planets_1_1Earth.md) _._    
            * **class** [**Output**](classastrea_1_1astro_1_1planets_1_1Output.md)     
            * **class** [**Saturn**](structastrea_1_1astro_1_1planets_1_1Saturn.md) _Represents the_ [_**Saturn**_](structastrea_1_1astro_1_1planets_1_1Saturn.md) _celestial body._
            * **struct** [**SpeciesModelParams**](structastrea_1_1astro_1_1planets_1_1SpeciesModelParams.md) _Per-species empirical parameters for NRLMSISE-00 diffusive and mixed-region density calculations._     
            * **struct** [**Switch**](structastrea_1_1astro_1_1planets_1_1Switch.md)     
            * **class** [**Uranus**](structastrea_1_1astro_1_1planets_1_1Uranus.md) _Represents the_ [_**Uranus**_](structastrea_1_1astro_1_1planets_1_1Uranus.md) _celestial body._
            * **class** [**Venus**](structastrea_1_1astro_1_1planets_1_1Venus.md) _Represents the_ [_**Venus**_](structastrea_1_1astro_1_1planets_1_1Venus.md) _celestial body._
        * **namespace** [**plotting**](namespaceastrea_1_1astro_1_1plotting.md)     
        * **namespace** [**space\_weather**](namespaceastrea_1_1astro_1_1space__weather.md) 
        * **namespace** [**star**](namespaceastrea_1_1astro_1_1star.md)     
            * **class** [**Sun**](structastrea_1_1astro_1_1star_1_1Sun.md) _Represents the_ [_**Sun**_](structastrea_1_1astro_1_1star_1_1Sun.md) _celestial body._
* **namespace** [**astro**](namespaceastrea_1_1astro_1_1_0d144.md) 
* **namespace** [**astro**](namespaceastrea_1_1astro_1_1_0d8.md) 
* **struct** [**EventTracker**](structastrea_1_1astro_1_1EventDetector_1_1EventTracker.md) _A struct for tracking events._     
* **namespace** [**frames**](namespaceastrea_1_1astro_1_1frames_1_1_0d20.md) 
* **namespace** [**plotting**](namespaceastrea_1_1astro_1_1plotting_1_1_0d208.md) 
* **namespace** [**matplot**](namespacematplot.md) 
* **namespace** [**mp\_units**](namespacemp__units.md)     
    * **struct** [**quantity\_point\_like\_traits&lt; astrea::astro::Date &gt;**](structmp__units_1_1quantity__point__like__traits_3_01astrea_1_1astro_1_1Date_01_4.md) _Specialization of mp\_units::quantity\_point\_like\_traits for the Date class._     
* **namespace** [**non\_si**](namespacemp__units_1_1non__si.md) 
* **namespace** [**si**](namespacemp__units_1_1si.md) 
* **namespace** [**unit\_symbols**](namespacemp__units_1_1si_1_1unit__symbols.md) 
* **namespace** [**std**](namespacestd.md)     
    * **struct** [**hash&lt; std::tuple&lt; TT... &gt; &gt;**](structstd_1_1hash_3_01std_1_1tuple_3_01TT_8_8_8_01_4_01_4.md)     
* **namespace** [**std**](namespacestd_1_1_0d202.md) 

