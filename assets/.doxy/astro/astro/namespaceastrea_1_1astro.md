

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
| namespace | [**detail**](namespaceastrea_1_1astro_1_1detail.md) <br> |
| namespace | [**frames**](namespaceastrea_1_1astro_1_1frames.md) <br> |
| namespace | [**planetary\_bodies**](namespaceastrea_1_1astro_1_1planetary__bodies.md) <br> |
| namespace | [**plotting**](namespaceastrea_1_1astro_1_1plotting.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) <br>_Represents a system of celestial bodies and their interactions._  |
| class | [**AtmosphericForce**](classastrea_1_1astro_1_1AtmosphericForce.md) <br>_Class to compute the atmospheric force on a vehicle._  |
| struct | [**BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) &lt;origin&gt;<br>_Base class for all body fixed frames._  |
| class | [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) <br>_Class representing a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector in astrodynamics._ |
| class | [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) <br>_Class representing a partial derivative of a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._ |
| class | [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) &lt;[**class**](classastrea_1_1astro_1_1CartesianVector.md) [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**class**](classastrea_1_1astro_1_1CartesianVector.md) [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md)&gt;<br>_Class representing a 3D vector in_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _coordinates._ |
| class | [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) <br>[_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._ |
| struct | [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) <br> |
| class | [**Constellation**](classastrea_1_1astro_1_1Constellation.md) &lt;[**class**](classastrea_1_1astro_1_1CartesianVector.md) [**Spacecraft\_T**](classastrea_1_1astro_1_1CartesianVector.md)&gt;<br>_A_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _is a collection of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _, organized into Shells and/or Planes._ |
| class | [**CowellsMethod**](classastrea_1_1astro_1_1CowellsMethod.md) <br>_Class implementing Cowell's method for equations of motion._  |
| class | [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) <br>_Class representing a_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector in astrodynamics._ |
| class | [**Date**](classastrea_1_1astro_1_1Date.md) <br>_Class representing a date in the astrea astro library._  |
| class | [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &lt;[**typename**](classastrea_1_1astro_1_1CartesianVector.md) [**In\_Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**typename**](classastrea_1_1astro_1_1CartesianVector.md) [**Out\_Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md)&gt;<br>_Class representing a direction cosine matrix (DCM) for transforming vectors between state/frames._  |
| struct | [**DynamicFrame**](classastrea_1_1astro_1_1DynamicFrame.md) &lt;[**class**](classastrea_1_1astro_1_1CartesianVector.md) [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md), axis&gt;<br>_Base class for all dynamic state/frames._  |
| class | [**EquationsOfMotion**](classastrea_1_1astro_1_1EquationsOfMotion.md) <br>_Base class for equations of motion in astrodynamics._  |
| class | [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) <br>_The_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _class represents the equinoctial orbital elements._ |
| class | [**EquinoctialPartial**](classastrea_1_1astro_1_1EquinoctialPartial.md) <br>_Class representing a partial derivative of an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._ |
| class | [**EquinoctialVop**](classastrea_1_1astro_1_1EquinoctialVop.md) <br>_Class implementing the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _VOP equations of motion._ |
| class | [**Event**](classastrea_1_1astro_1_1Event.md) <br>_A class representing a_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class serves as a base for user-defined Events and provides a common interface._ |
| class | [**EventDetector**](classastrea_1_1astro_1_1EventDetector.md) <br>_A class for detecting events in the astrea astro platform._  |
| class | [**Force**](classastrea_1_1astro_1_1Force.md) <br>_Abstract base class for force models in astrodynamics._  |
| class | [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) <br>_Class to manage multiple force models and compute the total force on a vehicle._  |
| struct | [**Frame**](structastrea_1_1astro_1_1Frame.md) &lt;origin, axis&gt;<br>_Base class for all state/frames._  |
| class | [**FrameReference**](classastrea_1_1astro_1_1FrameReference.md) <br>_Base class for all frame references._  |
| struct | [**GeneralPerturbations**](structastrea_1_1astro_1_1GeneralPerturbations.md) <br>[_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _structure representing a Ground Position (GP) object from SpaceTrack._ |
| class | [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) <br>_Class representing a_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector in astrodynamics._ |
| class | [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) <br>_Class representing a_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector in astrodynamics._ |
| class | [**ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md) <br>_A class representing an impulsive burn_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _. It triggers when the true anomaly wraps around (i.e. at perigee), and applies the total impulsive delta-v from all thrusters to the vehicle in the velocity direction. TODO: Generalize to a scheduler of some sort and other burn triggers. TODO: Generalize burn direction. TODO: Generalize which thrusters burn._ |
| struct | [**InertialFrame**](structastrea_1_1astro_1_1InertialFrame.md) &lt;origin, axis&gt;<br>_Base class for all inertial state/frames._  |
| class | [**Integrator**](classastrea_1_1astro_1_1Integrator.md) <br>[_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _class for numerical propagation of orbital mechanics problems._ |
| class | [**Interval**](classastrea_1_1astro_1_1Interval.md) <br>_Represents a time interval with a start and end time._  |
| class | [**J2MeanVop**](classastrea_1_1astro_1_1J2MeanVop.md) <br>_Class implementing the J2 Mean VOP equations of motion._  |
| struct | [**JplEphemerisTable**](structastrea_1_1astro_1_1JplEphemerisTable.md) <br>_Base class for any JPL_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _table._ |
| struct | [**JulianDateClock**](structastrea_1_1astro_1_1JulianDateClock.md) <br>_A clock implementation for Julian Dates._  |
| class | [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) <br>_The_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _class represents the_[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _orbital elements._ |
| class | [**KeplerianPartial**](classastrea_1_1astro_1_1KeplerianPartial.md) <br>_Class representing a partial derivative of a_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._ |
| class | [**KeplerianVop**](classastrea_1_1astro_1_1KeplerianVop.md) <br>_Class implementing the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _VOP equations of motion._ |
| class | [**LambertSolver**](classastrea_1_1astro_1_1LambertSolver.md) <br>_Class for solving Lambert's problem._  |
| class | [**LegendreCache**](classastrea_1_1astro_1_1LegendreCache.md) <br> |
| class | [**NBodyForce**](classastrea_1_1astro_1_1NBodyForce.md) <br>_Class to compute the gravitational force due to multiple celestial bodies._  |
| class | [**NullEvent**](classastrea_1_1astro_1_1NullEvent.md) <br>_A class representing a null_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class is used as a placeholder for Events that do not have a defined state or mass._ |
| class | [**NullVehicle**](classastrea_1_1astro_1_1NullVehicle.md) <br>_A class representing a null vehicle in the astrea astro platform. This class is used as a placeholder for vehicles that do not have a defined state or mass._  |
| class | [**OblatenessForce**](classastrea_1_1astro_1_1OblatenessForce.md) <br>_Class to compute the gravitational force due to the oblateness of a celestial body._  |
| class | [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) <br>_Class representing partial derivatives of orbital elements._  |
| class | [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) <br>_Class representing a set of orbital elements._  |
| class | [**Payload**](classastrea_1_1astro_1_1Payload.md) &lt;[**class**](classastrea_1_1astro_1_1CartesianVector.md) [**Payload\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**class**](classastrea_1_1astro_1_1CartesianVector.md) PayloadParameters\_T&gt;<br>[_**Payload**_](classastrea_1_1astro_1_1Payload.md) _class representing a payload on a platform._ |
| class | [**PayloadParameters**](classastrea_1_1astro_1_1PayloadParameters.md) <br>_Class for storing and managing payload parameters._  |
| class | [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) &lt;[**class**](classastrea_1_1astro_1_1CartesianVector.md) [**Payload\_T**](classastrea_1_1astro_1_1CartesianVector.md)&gt;<br>_The_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _class represents a platform that can have payloads attached to it. It provides methods to attach payloads and retrieve the list of attached payloads._ |
| class | [**Plane**](classastrea_1_1astro_1_1Plane.md) &lt;[**class**](classastrea_1_1astro_1_1CartesianVector.md) [**Spacecraft\_T**](classastrea_1_1astro_1_1CartesianVector.md)&gt;<br>_A_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _is a collection of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _that share the same orbital elements._ |
| class | [**Shell**](classastrea_1_1astro_1_1Shell.md) &lt;[**class**](classastrea_1_1astro_1_1CartesianVector.md) [**Spacecraft\_T**](classastrea_1_1astro_1_1CartesianVector.md)&gt;<br>_A_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _is a collection of planes, each containing a set of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _. It is used to represent sub-constellations of satellites in orbit._ |
| class | [**SolarRadiationPressure**](classastrea_1_1astro_1_1SolarRadiationPressure.md) <br>_Class to compute the solar radiation pressure force on a spacecraft._  |
| class | [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) <br>_A class representing a spacecraft in the astrea astro platform. This class encapsulates the properties of a spacecraft, including its mass, dynamic coefficients, and surface areas._  |
| class | [**Spherical**](classastrea_1_1astro_1_1Spherical.md) <br>_Class representing a_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector in astrodynamics._ |
| class | [**State**](classastrea_1_1astro_1_1State.md) <br>_Class representing the state of an astronomical object._  |
| class | [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) <br>_Class to manage the history of states for an object over date._  |
| class | [**StatePartial**](classastrea_1_1astro_1_1StatePartial.md) <br> |
| class | [**StateTransitionMatrix**](classastrea_1_1astro_1_1StateTransitionMatrix.md) <br> |
| class | [**Thruster**](classastrea_1_1astro_1_1Thruster.md) <br>[_**Thruster**_](classastrea_1_1astro_1_1Thruster.md) _class representing a thruster on a platform._ |
| class | [**ThrusterParameters**](classastrea_1_1astro_1_1ThrusterParameters.md) <br>_Class for storing and managing thruster parameters._  |
| class | [**TwoBody**](classastrea_1_1astro_1_1TwoBody.md) <br>_Class implementing the Two Body equations of motion._  |
| class | [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) <br>_Class representing the two-line element (TLE) format for orbital data._  |
| class | [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) <br>_A class representing a vehicle in the astrea astro platform. This class serves as a base for user-defined vehicles and provides a common interface._  |
| struct | [**is\_specialization**](structastrea_1_1astro_1_1is__specialization.md) &lt;[**class**](classastrea_1_1astro_1_1CartesianVector.md) [**T**](classastrea_1_1astro_1_1CartesianVector.md), Template&gt;<br> |
| struct | [**is\_specialization&lt; Template&lt; Args... &gt;, Template &gt;**](structastrea_1_1astro_1_1is__specialization_3_01Template_3_01Args_8_8_8_01_4_00_01Template_01_4.md) &lt;Template, Args&gt;<br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Acceleration**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**AccelerationVector**](#typedef-accelerationvector)  <br>_Type alias for a vector representing acceleration in 3D space._  |
| enum [**EnumType**](namespaceastrea_1_1astro.md#typedef-enumtype) | [**CelestialBodyId**](#enum-celestialbodyid)  <br>_Celestial body identifiers._  |
| enum [**EnumType**](namespaceastrea_1_1astro.md#typedef-enumtype) | [**CelestialBodyType**](#enum-celestialbodytype)  <br>_Celestial body types._  |
| typedef std::unique\_ptr&lt; [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) &gt; | [**CelestialBodyUniquePtr**](#typedef-celestialbodyuniqueptr)  <br>_Unique pointer type for_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _._ |
| typedef [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**In\_Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Out\_Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**DCM**](#typedef-dcm)  <br>_Alias for_ [_**DirectionCosineMatrix**_](classastrea_1_1astro_1_1DirectionCosineMatrix.md) _with a specific output frame type._ |
| typedef [**uint32\_t**](classastrea_1_1astro_1_1CartesianVector.md) | [**EnumType**](#typedef-enumtype)  <br>_Type definition for enumeration types._  |
| enum [**EnumType**](namespaceastrea_1_1astro.md#typedef-enumtype) | [**FrameAxis**](#enum-frameaxis)  <br>_Reference frames axes._  |
| typedef [**JulianDateClock::time\_point**](structastrea_1_1astro_1_1JulianDateClock.md#typedef-time_point) | [**JulianDate**](#typedef-juliandate)  <br>_A type alias for Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _time points._ |
| typedef std::chrono::time\_point&lt; [**JulianDateClock**](structastrea_1_1astro_1_1JulianDateClock.md), [**Duration**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**JulianDateTime**](#typedef-juliandatetime)  <br>_A time point type for Julian Dates, using the_ [_**JulianDateClock**_](structastrea_1_1astro_1_1JulianDateClock.md) _._ |
| typedef [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Distance**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**RadiusVector**](#typedef-radiusvector)  <br>_Type alias for a vector representing a radius in 3D space._  |
| enum [**EnumType**](namespaceastrea_1_1astro.md#typedef-enumtype) | [**SystemCenter**](#enum-systemcenter)  <br>_System center types._  |
| typedef [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)&lt; [**Thruster**](classastrea_1_1astro_1_1Thruster.md) &gt; | [**ThrusterPlatform**](#typedef-thrusterplatform)  <br>[_**Thruster**_](classastrea_1_1astro_1_1Thruster.md) _platform type definition._ |
| typedef [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**UnitVector**](#typedef-unitvector)  <br>_Type alias for a vector representing unit vectors in 3D space._  |
| typedef [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Velocity**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**VelocityVector**](#typedef-velocityvector)  <br>_Type alias for a vector representing velocity in 3D space._  |
| typedef std::remove\_cv\_t&lt; std::remove\_reference\_t&lt; [**T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; &gt; | [**remove\_cv\_ref**](#typedef-remove_cv_ref)  <br> |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; | [**CENTER**](#variable-center)   = `/* multi line expression */`<br> |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) mp\_units::quantity\_point | [**J2K**](#variable-j2k)   = `J2000`<br>_A constant representing the J2000 epoch in Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _format, used as a reference point._ |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) mp\_units::quantity\_point | [**MJDStart**](#variable-mjdstart)   = `MJD0`<br>_A constant representing the start of the Modified Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _epoch._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; | [**NADIR\_RIC**](#variable-nadir_ric)   = `/* multi line expression */`<br> |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; | [**RADIAL\_RIC**](#variable-radial_ric)   = `/* multi line expression */`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|  [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) | [**calculate\_geocentric\_radius**](#function-calculate_geocentric_radius) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & lat, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & rEquitorial, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & rPolar) <br>_Calculate the geocentric radius given latitude and Earth's radii._  |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::earth\_fixed**](structastrea_1_1astro_1_1BodyFixedFrame.md) &gt; | [**convert\_cylindrical\_to\_earth\_fixed**](#function-convert_cylindrical_to_earth_fixed) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & range, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & azimuth, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & elevation) <br>_Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates._  |
|  std::tuple&lt; [**Distance**](classastrea_1_1astro_1_1CartesianVector.md), [**Angle**](classastrea_1_1astro_1_1CartesianVector.md), [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**convert\_earth\_fixed\_to\_cylindrical**](#function-convert_earth_fixed_to_cylindrical) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::earth\_fixed**](structastrea_1_1astro_1_1BodyFixedFrame.md) &gt; & rEcef) <br>_Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates._  |
|  std::tuple&lt; [**Angle**](classastrea_1_1astro_1_1CartesianVector.md), [**Angle**](classastrea_1_1astro_1_1CartesianVector.md), [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**convert\_earth\_fixed\_to\_geocentric**](#function-convert_earth_fixed_to_geocentric) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::earth\_fixed**](structastrea_1_1astro_1_1BodyFixedFrame.md) &gt; & rEcef, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & rEquitorial, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & rPolar) <br>_Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates._  |
|  std::tuple&lt; [**Angle**](classastrea_1_1astro_1_1CartesianVector.md), [**Angle**](classastrea_1_1astro_1_1CartesianVector.md), [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**convert\_earth\_fixed\_to\_geodetic**](#function-convert_earth_fixed_to_geodetic) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::earth\_fixed**](structastrea_1_1astro_1_1BodyFixedFrame.md) &gt; & rEcef, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & rEquitorial, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & rPolar) <br>_Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates._  |
|  std::tuple&lt; [**Distance**](classastrea_1_1astro_1_1CartesianVector.md), [**Angle**](classastrea_1_1astro_1_1CartesianVector.md), [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**convert\_earth\_fixed\_to\_spherical**](#function-convert_earth_fixed_to_spherical) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::earth\_fixed**](structastrea_1_1astro_1_1BodyFixedFrame.md) &gt; & rEcef) <br>_Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**convert\_eccentric\_anomaly\_to\_mean\_anomaly**](#function-convert_eccentric_anomaly_to_mean_anomaly) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & ea, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) ecc) <br>_Convert the eccentric anomaly to the mean anomaly._  |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::earth\_fixed**](structastrea_1_1astro_1_1BodyFixedFrame.md) &gt; | [**convert\_geocentric\_to\_earth\_fixed**](#function-convert_geocentric_to_earth_fixed) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & lat, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & lon, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & alt, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & rEquitorial, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & rPolar) <br>_Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates._  |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::earth\_fixed**](structastrea_1_1astro_1_1BodyFixedFrame.md) &gt; | [**convert\_geodetic\_to\_earth\_fixed**](#function-convert_geodetic_to_earth_fixed) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & lat, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & lon, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & alt, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & rEquitorial, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & rPolar) <br>_Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**convert\_mean\_anomaly\_to\_eccentric\_anomaly**](#function-convert_mean_anomaly_to_eccentric_anomaly) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & ma, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) ecc) <br>_Convert the mean anomaly to the eccentric anomaly using Newton's method._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**convert\_mean\_anomaly\_to\_true\_anomaly**](#function-convert_mean_anomaly_to_true_anomaly) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & ma, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) ecc) <br>_Convert the mean anomaly to the true anomaly. Accurate to O(e^4)._  |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**frames::earth::earth\_fixed**](structastrea_1_1astro_1_1BodyFixedFrame.md) &gt; | [**convert\_spherical\_to\_earth\_fixed**](#function-convert_spherical_to_earth_fixed) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Distance**](classastrea_1_1astro_1_1CartesianVector.md) & range, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & inclination, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & azimuth) <br>_Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates._  |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**convert\_true\_anomaly\_to\_mean\_anomaly**](#function-convert_true_anomaly_to_mean_anomaly) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & ta, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) ecc) <br>_Convert the true anomaly to the mean anomaly. Accurate to O(e^5)._  |
|  [**JulianDate**](namespaceastrea_1_1astro.md#typedef-juliandate) | [**epoch\_to\_julian\_date**](#function-epoch_to_julian_date) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) std::string & epoch, [**const**](classastrea_1_1astro_1_1CartesianVector.md) std::string format="%Y-%m-%[**d**](classastrea_1_1astro_1_1CartesianVector.md) %[**H:**](classastrea_1_1astro_1_1CartesianVector.md)%[**M:**](classastrea_1_1astro_1_1CartesianVector.md)%[**S"**](classastrea_1_1astro_1_1CartesianVector.md)) <br>_Convert a string representation of a date to a JulianDate object._  |
|  [**DCM**](namespaceastrea_1_1astro.md#typedef-dcm)&lt; [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_U**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**get\_dcm**](#function-get_dcm) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date._  |
|  [**DCM**](namespaceastrea_1_1astro.md#typedef-dcm)&lt; [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_U**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**get\_dcm**](#function-get_dcm) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) = delete<br>_Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date._  |
|  [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; [**frames::earth::icrf**](structastrea_1_1astro_1_1InertialFrame.md), [**frames::earth::earth\_fixed**](structastrea_1_1astro_1_1BodyFixedFrame.md) &gt; | [**get\_dcm&lt; frames::earth::icrf, frames::earth::earth\_fixed &gt;**](#function-get_dcm-frames::earth::icrf-frames::earth::earth_fixed) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Get the Direction Cosine Matrix (DCM) for the ECEF frame at a given date._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) std::size\_t | [**get\_variant\_index**](#function-get_variant_index) () <br> |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**julian\_date\_to\_sidereal\_time**](#function-julian_date_to_sidereal_time) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**JulianDate**](namespaceastrea_1_1astro.md#typedef-juliandate) & date) <br>_Convert a JulianDate to a string representation._  |
|  [**bool**](classastrea_1_1astro_1_1CartesianVector.md) | [**nearly\_equal**](#function-nearly_equal) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & first, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & second, [**bool**](classastrea_1_1astro_1_1CartesianVector.md) ignoreFastVariable=[**false**](classastrea_1_1astro_1_1CartesianVector.md), [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) relTol=1.0e-5 \*astrea::detail::unitless) <br>_Checks if two_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _objects are nearly equal._ |
|  [**bool**](classastrea_1_1astro_1_1CartesianVector.md) | [**nearly\_equal**](#function-nearly_equal) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) & first, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) & second, [**bool**](classastrea_1_1astro_1_1CartesianVector.md) ignoreFastVariable=[**false**](classastrea_1_1astro_1_1CartesianVector.md), [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) relTol=1.0e-5 \*astrea::detail::unitless) <br>_Checks if two_ [_**OrbitalElementPartials**_](classastrea_1_1astro_1_1OrbitalElementPartials.md) _objects are nearly equal._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**decltype**](classastrea_1_1astro_1_1CartesianVector.md)([**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md){} \*[**Value\_U**](classastrea_1_1astro_1_1CartesianVector.md){}), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**operator\***](#function-operator) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Value\_U**](classastrea_1_1astro_1_1CartesianVector.md) & scalar, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & vec) <br>_Scalar multiplication operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|  [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**decltype**](classastrea_1_1astro_1_1CartesianVector.md)([**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md){} \*[**Value\_U**](classastrea_1_1astro_1_1CartesianVector.md){}), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**operator/**](#function-operator_1) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Value\_U**](classastrea_1_1astro_1_1CartesianVector.md) & scalar, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & vec) <br>_Scalar division operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_2) (std::ostream & os, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & state) <br>_Overload the output stream operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_3) (std::ostream & os, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md), [**Frame\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & state) <br>_Overload the output stream operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_4) (std::ostream & os, [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_5) (std::ostream & os, [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_6) (std::ostream & os, [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_7) (std::ostream & os, [**Spherical**](classastrea_1_1astro_1_1Spherical.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_8) (std::ostream & os, [**const**](classastrea_1_1astro_1_1CartesianVector.md) std::optional&lt; [**T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; & opt) <br>_Overloaded output stream operator for an optional type._  |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_9) (std::ostream & os, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**GeneralPerturbations**](structastrea_1_1astro_1_1GeneralPerturbations.md) & gp) <br>_Overloaded output stream operator for_ [_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _._ |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_10) (std::ostream & os, [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_11) (std::ostream & os, [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_12) (std::ostream & os, [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_13) (std::ostream & os, [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_14) (std::ostream & os, [**EquinoctialPartial**](classastrea_1_1astro_1_1EquinoctialPartial.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_15) (std::ostream & os, [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_16) (std::ostream & os, [**KeplerianPartial**](classastrea_1_1astro_1_1KeplerianPartial.md) [**const**](classastrea_1_1astro_1_1CartesianVector.md) & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_17) (std::ostream & os, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_18) (std::ostream & os, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_19) (std::ostream & os, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**State**](classastrea_1_1astro_1_1State.md) & state) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_20) (std::ostream & os, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & obj) <br> |
|  [**void**](classastrea_1_1astro_1_1CartesianVector.md) | [**throw\_mismatched\_types**](#function-throw_mismatched_types) () <br>_Throws an exception for mismatched types in orbital elements._  |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**wrap\_angle**](#function-wrap_angle) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) & angle) <br>_Sanitize an angle to ensure it is within the range [0, 2π)._  |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**JulianDate**](namespaceastrea_1_1astro.md#typedef-juliandate) | [**J2000**](#function-j2000) ([**JulianDateClock::duration**](structastrea_1_1astro_1_1JulianDateClock.md#typedef-duration){ 2451545.0 }) <br>_A constant representing the J2000 epoch in Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _format._ |
|  [**constexpr**](classastrea_1_1astro_1_1CartesianVector.md) [**JulianDate**](namespaceastrea_1_1astro.md#typedef-juliandate) | [**MJD0**](#function-mjd0) ([**JulianDateClock::duration**](structastrea_1_1astro_1_1JulianDateClock.md#typedef-duration){ 2400000.5 }) <br>_A constant representing the Modified Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _epoch in Julian_[_**Date**_](classastrea_1_1astro_1_1Date.md) _format._ |


























## Public Types Documentation




### typedef AccelerationVector 

_Type alias for a vector representing acceleration in 3D space._ 
```C++
using astrea::astro::AccelerationVector = typedef CartesianVector<Acceleration, Frame_T>;
```




<hr>



### enum CelestialBodyId 

_Celestial body identifiers._ 
```C++
enum astrea::astro::CelestialBodyId {
    UNSET,
    SUN,
    MERCURY,
    VENUS,
    EARTH,
    MOON,
    MARS,
    PHOBOS,
    DEIMOS,
    JUPITER,
    GANYMEDE,
    CALLISTO,
    IO,
    EUROPA,
    SATURN,
    TITAN,
    RHEA,
    IAPETUS,
    URANUS,
    TITANIA,
    OBERON,
    NEPTUNE,
    TRITON,
    SOLAR_SYSTEM_BARYCENTER,
    MERCURY_BARYCENTER,
    VENUS_BARYCENTER,
    EARTH_BARYCENTER,
    MARS_BARYCENTER,
    JUPITER_BARYCENTER,
    SATURN_BARYCENTER,
    URANUS_BARYCENTER,
    NEPTUNE_BARYCENTER,
    CUSTOM
};
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



### typedef CelestialBodyUniquePtr 

_Unique pointer type for_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _._
```C++
using astrea::astro::CelestialBodyUniquePtr = typedef std::unique_ptr<CelestialBody>;
```




<hr>



### typedef DCM 

_Alias for_ [_**DirectionCosineMatrix**_](classastrea_1_1astro_1_1DirectionCosineMatrix.md) _with a specific output frame type._
```C++
using astrea::astro::DCM = typedef DirectionCosineMatrix<In_Frame_T, Out_Frame_T>;
```



This alias simplifies the usage of [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) by allowing the user to specify the output frame type.




**Template parameters:**


* `Out_Frame_T` The frame type to which the DCM applies. 




        

<hr>



### typedef EnumType 

_Type definition for enumeration types._ 
```C++
using astrea::astro::EnumType = typedef uint32_t;
```




<hr>



### enum FrameAxis 

_Reference frames axes._ 
```C++
enum astrea::astro::FrameAxis {
    ICRF,
    J2000,
    BODY_FIXED,
    LVLH,
    RIC,
    VNB,
    ENU
};
```




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



### typedef RadiusVector 

_Type alias for a vector representing a radius in 3D space._ 
```C++
using astrea::astro::RadiusVector = typedef CartesianVector<Distance, Frame_T>;
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



### typedef ThrusterPlatform 

[_**Thruster**_](classastrea_1_1astro_1_1Thruster.md) _platform type definition._
```C++
using astrea::astro::ThrusterPlatform = typedef PayloadPlatform<Thruster>;
```




<hr>



### typedef UnitVector 

_Type alias for a vector representing unit vectors in 3D space._ 
```C++
using astrea::astro::UnitVector = typedef CartesianVector<Unitless, Frame_T>;
```



This is used for direction vectors that do not have units of distance, velocity, or acceleration. 


        

<hr>



### typedef VelocityVector 

_Type alias for a vector representing velocity in 3D space._ 
```C++
using astrea::astro::VelocityVector = typedef CartesianVector<Velocity, Frame_T>;
```




<hr>



### typedef remove\_cv\_ref 

```C++
using astrea::astro::remove_cv_ref = typedef std::remove_cv_t<std::remove_reference_t<T> >;
```




<hr>
## Public Static Attributes Documentation




### variable CENTER 

```C++
const astro::RadiusVector<astro::frames::dynamic::ric> astrea::astro::CENTER;
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




### function calculate\_geocentric\_radius 

_Calculate the geocentric radius given latitude and Earth's radii._ 
```C++
Distance astrea::astro::calculate_geocentric_radius (
    const  Angle & lat,
    const  Distance & rEquitorial,
    const  Distance & rPolar
) 
```





**Parameters:**


* `lat` The latitude in radians. 
* `rEquitorial` The equatorial radius of the Earth. 
* `rPolar` The polar radius of the Earth. 



**Returns:**

The geocentric radius. 





        

<hr>



### function convert\_cylindrical\_to\_earth\_fixed 

_Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates._ 
```C++
RadiusVector < frames::earth::earth_fixed > astrea::astro::convert_cylindrical_to_earth_fixed (
    const  Distance & range,
    const  Angle & azimuth,
    const  Distance & elevation
) 
```





**Parameters:**


* `range` The range in meters. 
* `azimuth` The azimuth in radians. 
* `elevation` The elevation in meters. 



**Returns:**

The radius vector in ECEF coordinates. 





        

<hr>



### function convert\_earth\_fixed\_to\_cylindrical 

_Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates._ 
```C++
std::tuple< Distance , Angle , Distance > astrea::astro::convert_earth_fixed_to_cylindrical (
    const  RadiusVector < frames::earth::earth_fixed > & rEcef
) 
```





**Parameters:**


* `rEcef` The radius vector in ECEF coordinates. 



**Returns:**

The range, azimuth, and elevation as a tuple. 





        

<hr>



### function convert\_earth\_fixed\_to\_geocentric 

_Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates._ 
```C++
std::tuple< Angle , Angle , Distance > astrea::astro::convert_earth_fixed_to_geocentric (
    const  RadiusVector < frames::earth::earth_fixed > & rEcef,
    const  Distance & rEquitorial,
    const  Distance & rPolar
) 
```





**Parameters:**


* `rEcef` The radius vector in ECEF coordinates. 
* `rEquitorial` The equatorial radius of the Earth. 
* `rPolar` The polar radius of the Earth. 



**Returns:**

The latitude, longitude, and altitude as a tuple. 





        

<hr>



### function convert\_earth\_fixed\_to\_geodetic 

_Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates._ 
```C++
std::tuple< Angle , Angle , Distance > astrea::astro::convert_earth_fixed_to_geodetic (
    const  RadiusVector < frames::earth::earth_fixed > & rEcef,
    const  Distance & rEquitorial,
    const  Distance & rPolar
) 
```





**Parameters:**


* `rEcef` The radius vector in ECEF coordinates. 
* `rEquitorial` The equatorial radius of the Earth. 
* `rPolar` The polar radius of the Earth. 



**Returns:**

The latitude, longitude, and altitude as a tuple. 





        

<hr>



### function convert\_earth\_fixed\_to\_spherical 

_Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates._ 
```C++
std::tuple< Distance , Angle , Angle > astrea::astro::convert_earth_fixed_to_spherical (
    const  RadiusVector < frames::earth::earth_fixed > & rEcef
) 
```





**Parameters:**


* `rEcef` The radius vector in ECEF coordinates. 



**Returns:**

The range, inclination, and azimuth as a tuple. 





        

<hr>



### function convert\_eccentric\_anomaly\_to\_mean\_anomaly 

_Convert the eccentric anomaly to the mean anomaly._ 
```C++
Angle astrea::astro::convert_eccentric_anomaly_to_mean_anomaly (
    const  Angle & ea,
    const  Unitless ecc
) 
```





**Parameters:**


* `ea` The eccentric anomaly. 
* `ecc` The eccentricity. 



**Returns:**

The mean anomaly. 





        

<hr>



### function convert\_geocentric\_to\_earth\_fixed 

_Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates._ 
```C++
RadiusVector < frames::earth::earth_fixed > astrea::astro::convert_geocentric_to_earth_fixed (
    const  Angle & lat,
    const  Angle & lon,
    const  Distance & alt,
    const  Distance & rEquitorial,
    const  Distance & rPolar
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



### function convert\_geodetic\_to\_earth\_fixed 

_Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates._ 
```C++
RadiusVector < frames::earth::earth_fixed > astrea::astro::convert_geodetic_to_earth_fixed (
    const  Angle & lat,
    const  Angle & lon,
    const  Distance & alt,
    const  Distance & rEquitorial,
    const  Distance & rPolar
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
    const  Angle & ma,
    const  Unitless ecc
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
    const  Angle & ma,
    const  Unitless ecc
) 
```





**Parameters:**


* `ma` The mean anomaly. 
* `ecc` The eccentricity. 



**Returns:**

The true anomaly. 





        

<hr>



### function convert\_spherical\_to\_earth\_fixed 

_Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates._ 
```C++
RadiusVector < frames::earth::earth_fixed > astrea::astro::convert_spherical_to_earth_fixed (
    const  Distance & range,
    const  Angle & inclination,
    const  Angle & azimuth
) 
```





**Parameters:**


* `azimuth` The azimuth in radians. 
* `inclination` The inclination in radians. 
* `range` The range in meters. 



**Returns:**

The radius vector in ECEF coordinates. 





        

<hr>



### function convert\_true\_anomaly\_to\_mean\_anomaly 

_Convert the true anomaly to the mean anomaly. Accurate to O(e^5)._ 
```C++
Angle astrea::astro::convert_true_anomaly_to_mean_anomaly (
    const  Angle & ta,
    const  Unitless ecc
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
    const std::string format="%Y-%m-% d % H: % M: % S"
) 
```





**Parameters:**


* `epoch` The date string to convert. 
* `format` The format of the date string, default is "%Y-%m-%d %H:%M:%S". 



**Returns:**

JulianDate The JulianDate representation of the input date. 





        

<hr>



### function get\_dcm 

_Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date._ 
```C++
template<typename Frame_T, typename Frame_U>
inline DCM < Frame_T , Frame_U > astrea::astro::get_dcm (
    const  Date & date
) 
```





**Parameters:**


* `date` The date for which to get the DCM. 



**Returns:**

DirectionCosineMatrix&lt;Frame\_T, Frame\_U&gt; The DCM from Frame\_U to Frame\_T. 





        

<hr>



### function get\_dcm 

_Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date._ 
```C++
template<typename Frame_T, typename Frame_U>
inline DCM < Frame_T , Frame_U > astrea::astro::get_dcm (
    const  Date & date
) = delete
```





**Parameters:**


* `date` The date for which to get the DCM. 



**Returns:**

DirectionCosineMatrix&lt;Frame\_T, Frame\_U&gt; The DCM from Frame\_U to Frame\_T. 





        

<hr>



### function get\_dcm&lt; frames::earth::icrf, frames::earth::earth\_fixed &gt; 

_Get the Direction Cosine Matrix (DCM) for the ECEF frame at a given date._ 
```C++
template<>
inline DirectionCosineMatrix < frames::earth::icrf , frames::earth::earth_fixed > astrea::astro::get_dcm< frames::earth::icrf, frames::earth::earth_fixed > (
    const  Date & date
) 
```





**Parameters:**


* `date` The date for which to get the DCM. 



**Returns:**

DirectionCosineMatrix&lt;frames::earth::icrf, frames::earth::earth\_fixed&gt; The DCM from ECI to ECEF. 





        

<hr>



### function get\_variant\_index 

```C++
template<typename VariantType, typename T, std::size_t index>
constexpr std::size_t astrea::astro::get_variant_index () 
```




<hr>



### function julian\_date\_to\_sidereal\_time 

_Convert a JulianDate to a string representation._ 
```C++
Angle astrea::astro::julian_date_to_sidereal_time (
    const  JulianDate & date
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



### function nearly\_equal 

_Checks if two_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _objects are nearly equal._
```C++
bool astrea::astro::nearly_equal (
    const  OrbitalElements & first,
    const  OrbitalElements & second,
    bool ignoreFastVariable=false,
    Unitless relTol=1.0e-5 *astrea::detail::unitless
) 
```



This function compares two [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) objects for equality within a specified tolerance.




**Parameters:**


* `first` The first [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) object to compare. 
* `second` The second [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) object to compare. 
* `ignoreFastVariable` If true, ignores fast-changing variables in the comparison. 
* `relTol` Relative tolerance for the comparison. 



**Returns:**

true if the two [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) objects are nearly equal 




**Returns:**

false if the two [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) objects are not nearly equal 





        

<hr>



### function nearly\_equal 

_Checks if two_ [_**OrbitalElementPartials**_](classastrea_1_1astro_1_1OrbitalElementPartials.md) _objects are nearly equal._
```C++
bool astrea::astro::nearly_equal (
    const  OrbitalElementPartials & first,
    const  OrbitalElementPartials & second,
    bool ignoreFastVariable=false,
    Unitless relTol=1.0e-5 *astrea::detail::unitless
) 
```



This function compares two [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) objects for equality within a specified tolerance.




**Parameters:**


* `first` The first [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) object to compare. 
* `second` The second [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) object to compare. 
* `ignoreFastVariable` If true, ignores fast-changing variables in the comparison. 
* `relTol` Relative tolerance for the comparison. 



**Returns:**

true if the two [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) objects are nearly equal 




**Returns:**

false if the two [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) objects are not nearly equal 





        

<hr>



### function operator\* 

_Scalar multiplication operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename Value_T, typename Value_U, typename Frame_T>
CartesianVector < decltype ( Value_T {} * Value_U {}), Frame_T > astrea::astro::operator* (
    const  Value_U & scalar,
    const  CartesianVector < Value_T , Frame_T > & vec
) 
```





**Template parameters:**


* `T` The type of the vector components. 
* `U` The type of the scalar to multiply with. 



**Parameters:**


* `scalar` The scalar value to multiply with. 
* `vec` The [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to multiply. 



**Returns:**

[**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt;decltype(Value\_T{} \* Value\_U{}), Frame\_T&gt; A new [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) that is the product of the scalar and the vector. 





        

<hr>



### function operator/ 

_Scalar division operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename Value_T, typename Value_U, typename Frame_T>
CartesianVector < decltype ( Value_T {} * Value_U {}), Frame_T > astrea::astro::operator/ (
    const  Value_U & scalar,
    const  CartesianVector < Value_T , Frame_T > & vec
) 
```





**Template parameters:**


* `T` The type of the vector components. 
* `U` The type of the scalar to divide by. 



**Parameters:**


* `scalar` The scalar value to divide by. 
* `vec` The [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to divide. 



**Returns:**

[**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt;decltype(Value\_T{} \* Value\_U{}), Frame\_T&gt; A new [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) that is the quotient of the scalar and the vector. 





        

<hr>



### function operator&lt;&lt; 

_Overload the output stream operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<class Value_T, class Frame_T>
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const  CartesianVector < Value_T , Frame_T > & state
) 
```





**Template parameters:**


* `Value_T` The type of the vector components. 
* `Frame_T` The type of the frame. 



**Parameters:**


* `os` The output stream. 
* `state` The [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to output. 



**Returns:**

The output stream. 





        

<hr>



### function operator&lt;&lt; 

_Overload the output stream operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<class Value_T, class Frame_T>
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const  CartesianVector < Value_T , Frame_T > & state
) 
```





**Template parameters:**


* `Value_T` The type of the vector components. 
* `Frame_T` The type of the frame. 



**Parameters:**


* `os` The output stream. 
* `state` The [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) to output. 



**Returns:**

The output stream. 





        

<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Cylindrical  const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Geocentric  const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Geodetic  const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Spherical  const & elements
) 
```




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
    const  GeneralPerturbations & gp
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
    TwoLineElements  const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Cartesian  const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    CartesianPartial  const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Equinoctial  const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    EquinoctialPartial  const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Keplerian  const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    KeplerianPartial  const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const  OrbitalElements & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const  OrbitalElementPartials & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const  State & state
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    const  Date & obj
) 
```




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



### function wrap\_angle 

_Sanitize an angle to ensure it is within the range [0, 2π)._ 
```C++
constexpr  Angle astrea::astro::wrap_angle (
    const  Angle & angle
) 
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
static constexpr  JulianDate astrea::astro::J2000 (
    JulianDateClock::duration { 2451545.0 }
) 
```



This is a commonly used epoch in astronomy, representing January 1, 2000, at 12:00 TT. 


        

<hr>



### function MJD0 

_A constant representing the Modified Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _epoch in Julian_[_**Date**_](classastrea_1_1astro_1_1Date.md) _format._
```C++
static constexpr  JulianDate astrea::astro::MJD0 (
    JulianDateClock::duration { 2400000.5 }
) 
```



This is used as a reference point for Modified Julian Dates. 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/astro.fwd.hpp`

