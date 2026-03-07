

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
| class | [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) <br>_Class representing a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector in astrodynamics._ |
| class | [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) <br>_Class representing a partial derivative of a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._ |
| class | [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) &lt;class Value\_T, class Frame\_T&gt;<br>_Class representing a 3D vector in_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _coordinates._ |
| class | [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) <br>[_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._ |
| struct | [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) <br> |
| class | [**Constellation**](classastrea_1_1astro_1_1Constellation.md) &lt;class Spacecraft\_T&gt;<br>_A_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _is a collection of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _, organized into Shells and/or Planes._ |
| class | [**CowellsMethod**](classastrea_1_1astro_1_1CowellsMethod.md) <br>_Class implementing Cowell's method for equations of motion._  |
| class | [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) <br>_Class representing a_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector in astrodynamics._ |
| class | [**Date**](classastrea_1_1astro_1_1Date.md) <br>_Class representing a date in the astrea astro library._  |
| class | [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) &lt;typename In\_Frame\_T, typename Out\_Frame\_T&gt;<br>_Class representing a direction cosine matrix (DCM) for transforming vectors between state/frames._  |
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
| class | [**Payload**](classastrea_1_1astro_1_1Payload.md) &lt;class Payload\_T, class PayloadParameters\_T&gt;<br>[_**Payload**_](classastrea_1_1astro_1_1Payload.md) _class representing a payload on a platform._ |
| class | [**PayloadParameters**](classastrea_1_1astro_1_1PayloadParameters.md) <br>_Class for storing and managing payload parameters._  |
| class | [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) &lt;class Payload\_T&gt;<br>_The_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _class represents a platform that can have payloads attached to it. It provides methods to attach payloads and retrieve the list of attached payloads._ |
| class | [**Plane**](classastrea_1_1astro_1_1Plane.md) &lt;class Spacecraft\_T&gt;<br>_A_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _is a collection of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _that share the same orbital elements._ |
| class | [**Shell**](classastrea_1_1astro_1_1Shell.md) &lt;class Spacecraft\_T&gt;<br>_A_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _is a collection of planes, each containing a set of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _. It is used to represent sub-constellations of satellites in orbit._ |
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
| struct | [**is\_specialization**](structastrea_1_1astro_1_1is__specialization.md) &lt;class T, Template&gt;<br> |
| struct | [**is\_specialization&lt; Template&lt; Args... &gt;, Template &gt;**](structastrea_1_1astro_1_1is__specialization_3_01Template_3_01Args_8_8_8_01_4_00_01Template_01_4.md) &lt;Template, Args&gt;<br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Acceleration, Frame\_T &gt; | [**AccelerationVector**](#typedef-accelerationvector)  <br>_Type alias for a vector representing acceleration in 3D space._  |
| enum [**EnumType**](namespaceastrea_1_1astro.md#typedef-enumtype) | [**CelestialBodyId**](#enum-celestialbodyid)  <br>_Celestial body identifiers._  |
| enum [**EnumType**](namespaceastrea_1_1astro.md#typedef-enumtype) | [**CelestialBodyType**](#enum-celestialbodytype)  <br>_Celestial body types._  |
| typedef std::unique\_ptr&lt; [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) &gt; | [**CelestialBodyUniquePtr**](#typedef-celestialbodyuniqueptr)  <br>_Unique pointer type for_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _._ |
| typedef [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; In\_Frame\_T, Out\_Frame\_T &gt; | [**DCM**](#typedef-dcm)  <br>_Alias for_ [_**DirectionCosineMatrix**_](classastrea_1_1astro_1_1DirectionCosineMatrix.md) _with a specific output frame type._ |
| typedef uint32\_t | [**EnumType**](#typedef-enumtype)  <br>_Type definition for enumeration types._  |
| enum [**EnumType**](namespaceastrea_1_1astro.md#typedef-enumtype) | [**FrameAxis**](#enum-frameaxis)  <br>_Reference frames axes._  |
| typedef [**JulianDateClock::time\_point**](structastrea_1_1astro_1_1JulianDateClock.md#typedef-time_point) | [**JulianDate**](#typedef-juliandate)  <br>_A type alias for Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _time points._ |
| typedef std::chrono::time\_point&lt; [**JulianDateClock**](structastrea_1_1astro_1_1JulianDateClock.md), Duration &gt; | [**JulianDateTime**](#typedef-juliandatetime)  <br>_A time point type for Julian Dates, using the_ [_**JulianDateClock**_](structastrea_1_1astro_1_1JulianDateClock.md) _._ |
| typedef [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Distance, Frame\_T &gt; | [**RadiusVector**](#typedef-radiusvector)  <br>_Type alias for a vector representing a radius in 3D space._  |
| enum [**EnumType**](namespaceastrea_1_1astro.md#typedef-enumtype) | [**SystemCenter**](#enum-systemcenter)  <br>_System center types._  |
| typedef [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md)&lt; [**Thruster**](classastrea_1_1astro_1_1Thruster.md) &gt; | [**ThrusterPlatform**](#typedef-thrusterplatform)  <br>[_**Thruster**_](classastrea_1_1astro_1_1Thruster.md) _platform type definition._ |
| typedef [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Unitless, Frame\_T &gt; | [**UnitVector**](#typedef-unitvector)  <br>_Type alias for a vector representing unit vectors in 3D space._  |
| typedef [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Velocity, Frame\_T &gt; | [**VelocityVector**](#typedef-velocityvector)  <br>_Type alias for a vector representing velocity in 3D space._  |
| typedef std::remove\_cv\_t&lt; std::remove\_reference\_t&lt; T &gt; &gt; | [**remove\_cv\_ref**](#typedef-remove_cv_ref)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  concept | [**HasDcm**](#variable-hasdcm)   = `requires(const [**Date**](classastrea_1_1astro_1_1Date.md)& date) { get\_dcm&lt;Frame\_T, Frame\_U&gt;(date); }`<br>_Concept to determine if a Direction Cosine Matrix (DCM) can be obtained between two frames at a given date._  |
|  concept | [**HasDcmMethod**](#variable-hasdcmmethod)   = `/* multi line expression */`<br>_Concept to determine if a frame class has a member function to obtain the Direction Cosine Matrix (DCM) to another frame at a given date._  |
|  concept | [**HasDirectCartesianConversion**](#variable-hasdirectcartesianconversion)   = `/* multi line expression */`<br>_Concept to check if a type can be converted to_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _elements._ |
|  concept | [**HasDirectEquinoctialConversion**](#variable-hasdirectequinoctialconversion)   = `/* multi line expression */`<br>_Concept to check if a type can be converted to_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _elements._ |
|  concept | [**HasDirectKeplerianConversion**](#variable-hasdirectkeplerianconversion)   = `/* multi line expression */`<br>_Concept to check if a type can be converted to_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _elements._ |
|  concept | [**HasGetCoefficientOfDrag**](#variable-hasgetcoefficientofdrag)   = `/* multi line expression */`<br>_Concept to check if a type has a method to get the coefficient of drag._  |
|  concept | [**HasGetCoefficientOfLift**](#variable-hasgetcoefficientoflift)   = `/* multi line expression */`<br>_Concept to check if a type has a method to get the coefficient of lift._  |
|  concept | [**HasGetCoefficientOfReflectivity**](#variable-hasgetcoefficientofreflectivity)   = `/* multi line expression */`<br>_Concept to check if a type has a method to get the coefficient of reflectivity._  |
|  concept | [**HasGetLiftArea**](#variable-hasgetliftarea)   = `/* multi line expression */`<br>_Concept to check if a type has a method to get the lift area._  |
|  concept | [**HasGetMass**](#variable-hasgetmass)   = `/* multi line expression */`<br>_Concept to check if a type has a method to get the mass._  |
|  concept | [**HasGetName**](#variable-hasgetname)   = `/* multi line expression */`<br>_Concept to check if a type has a method to get the event name._  |
|  concept | [**HasGetRamArea**](#variable-hasgetramarea)   = `/* multi line expression */`<br>_Concept to check if a type has a method to get the ram area._  |
|  concept | [**HasGetSolarArea**](#variable-hasgetsolararea)   = `/* multi line expression */`<br>_Concept to check if a type has a method to get the solar area._  |
|  concept | [**HasInPlaceMathOperators**](#variable-hasinplacemathoperators)   = `/* multi line expression */`<br>_Concept to check if a type has in-place mathematical operators defined._  |
|  concept | [**HasIsTerminal**](#variable-hasisterminal)   = `/* multi line expression */`<br>_Concept to check if a type has a method to determine if an event is terminal._  |
|  concept | [**HasIterpolate**](#variable-hasiterpolate)   = `/* multi line expression */`<br>_Concept to check if a type can be converted to_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _elements._ |
|  concept | [**HasMathOperators**](#variable-hasmathoperators)   = `/* multi line expression */`<br>_Concept to check if a type has mathematical operators defined._  |
|  concept | [**HasMeasureEvent**](#variable-hasmeasureevent)   = `/* multi line expression */`<br>_Concept to check if a type has a method to detect an event._  |
|  concept | [**HasSameAxis**](#variable-hassameaxis)   = `(Frame\_T::get\_axis() == Frame\_U::get\_axis())`<br>_Concept to determine if two frames share the same axis._  |
|  concept | [**HasSameOrigin**](#variable-hassameorigin)   = `(Frame\_T::get\_origin() == Frame\_U::get\_origin())`<br>_Concept to determine if two frames share the same origin._  |
|  concept | [**HasToVector**](#variable-hastovector)   = `/* multi line expression */`<br>_Concept to check if a type can be converted to a vector of Unitless._  |
|  concept | [**HasTriggerEvent**](#variable-hastriggerevent)   = `/* multi line expression */`<br>_Concept to check if a type has a method to trigger a post-event action._  |
|  concept | [**IsBodyFixedFrame**](#variable-isbodyfixedframe)   = `(Frame\_T::get\_axis() == FrameAxis::BODY\_FIXED)`<br>_Concept to determine if a frame is body-fixed._  |
|  concept | [**IsConstructableTo**](#variable-isconstructableto)   = `/* multi line expression */`<br>_Concept to check if a type can be constructed from a set of orbital elements._  |
|  concept | [**IsDynamicFrame**](#variable-isdynamicframe)   = `/* multi line expression */`<br>_Concept to determine if a frame is dynamic (LVLH, RIC, VNB)._  |
|  concept | [**IsGenericallyConstructableEvent**](#variable-isgenericallyconstructableevent)   = `/* multi line expression */`<br>_Concept to check if a type can be generically constructed as a_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|  concept | [**IsGenericallyConstructableVehicle**](#variable-isgenericallyconstructablevehicle)   = `/* multi line expression */`<br>_Concept to check if a type can be generically constructed as a_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._ |
|  concept | [**IsInertialFrame**](#variable-isinertialframe)   = `(Frame\_T::get\_axis() == FrameAxis::ICRF \|\| Frame\_T::get\_axis() == FrameAxis::J2000)`<br>_Concept to determine if a frame is inertial._  |
|  concept | [**IsOrbitalElements**](#variable-isorbitalelements)   = `/* multi line expression */`<br>_Concept to check if a type is an orbital elements type._  |
|  concept | [**IsSameFrame**](#variable-issameframe)   = `HasSameOrigin&lt;Frame\_T, Frame\_U&gt; && HasSameAxis&lt;Frame\_T, Frame\_U&gt;`<br>_Concept to determine if two frames are the same (same origin and same axis)._  |
|  concept | [**IsStaticFrame**](#variable-isstaticframe)   = `/* multi line expression */`<br>_Concept to determine if a frame is static (inertial or body-fixed)._  |
|  concept | [**IsUserDefinedEvent**](#variable-isuserdefinedevent)   = `/* multi line expression */`<br>_Concept to check if a type is a user-defined_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._ |
|  concept | [**IsUserDefinedVehicle**](#variable-isuserdefinedvehicle)   = `/* multi line expression */`<br>_Concept to check if a type is a user-defined vehicle._  |


## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  const [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; | [**CENTER**](#variable-center)   = `/* multi line expression */`<br> |
|  constexpr mp\_units::quantity\_point | [**J2K**](#variable-j2k)   = `J2000`<br>_A constant representing the J2000 epoch in Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _format, used as a reference point._ |
|  constexpr mp\_units::quantity\_point | [**MJDStart**](#variable-mjdstart)   = `MJD0`<br>_A constant representing the start of the Modified Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _epoch._ |
|  const [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; | [**NADIR\_RIC**](#variable-nadir_ric)   = `/* multi line expression */`<br> |
|  const [**astro::RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; [**astro::frames::dynamic::ric**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) &gt; | [**RADIAL\_RIC**](#variable-radial_ric)   = `/* multi line expression */`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|  Distance | [**calculate\_geocentric\_radius**](#function-calculate_geocentric_radius) (const Angle & lat, const Distance & rEquitorial, const Distance & rPolar) <br>_Calculate the geocentric radius given latitude and Earth's radii._  |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; frames::earth::earth\_fixed &gt; | [**convert\_cylindrical\_to\_earth\_fixed**](#function-convert_cylindrical_to_earth_fixed) (const Distance & range, const Angle & azimuth, const Distance & elevation) <br>_Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates._  |
|  std::tuple&lt; Distance, Angle, Distance &gt; | [**convert\_earth\_fixed\_to\_cylindrical**](#function-convert_earth_fixed_to_cylindrical) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; frames::earth::earth\_fixed &gt; & rEcef) <br>_Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates._  |
|  std::tuple&lt; Angle, Angle, Distance &gt; | [**convert\_earth\_fixed\_to\_geocentric**](#function-convert_earth_fixed_to_geocentric) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; frames::earth::earth\_fixed &gt; & rEcef, const Distance & rEquitorial, const Distance & rPolar) <br>_Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates._  |
|  std::tuple&lt; Angle, Angle, Distance &gt; | [**convert\_earth\_fixed\_to\_geodetic**](#function-convert_earth_fixed_to_geodetic) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; frames::earth::earth\_fixed &gt; & rEcef, const Distance & rEquitorial, const Distance & rPolar) <br>_Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates._  |
|  std::tuple&lt; Distance, Angle, Angle &gt; | [**convert\_earth\_fixed\_to\_spherical**](#function-convert_earth_fixed_to_spherical) (const [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; frames::earth::earth\_fixed &gt; & rEcef) <br>_Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates._  |
|  Angle | [**convert\_eccentric\_anomaly\_to\_mean\_anomaly**](#function-convert_eccentric_anomaly_to_mean_anomaly) (const Angle & ea, const Unitless ecc) <br>_Convert the eccentric anomaly to the mean anomaly._  |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; frames::earth::earth\_fixed &gt; | [**convert\_geocentric\_to\_earth\_fixed**](#function-convert_geocentric_to_earth_fixed) (const Angle & lat, const Angle & lon, const Distance & alt, const Distance & rEquitorial, const Distance & rPolar) <br>_Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates._  |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; frames::earth::earth\_fixed &gt; | [**convert\_geodetic\_to\_earth\_fixed**](#function-convert_geodetic_to_earth_fixed) (const Angle & lat, const Angle & lon, const Distance & alt, const Distance & rEquitorial, const Distance & rPolar) <br>_Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates._  |
|  Angle | [**convert\_mean\_anomaly\_to\_eccentric\_anomaly**](#function-convert_mean_anomaly_to_eccentric_anomaly) (const Angle & ma, const Unitless ecc) <br>_Convert the mean anomaly to the eccentric anomaly using Newton's method._  |
|  Angle | [**convert\_mean\_anomaly\_to\_true\_anomaly**](#function-convert_mean_anomaly_to_true_anomaly) (const Angle & ma, const Unitless ecc) <br>_Convert the mean anomaly to the true anomaly. Accurate to O(e^4)._  |
|  [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; frames::earth::earth\_fixed &gt; | [**convert\_spherical\_to\_earth\_fixed**](#function-convert_spherical_to_earth_fixed) (const Distance & range, const Angle & inclination, const Angle & azimuth) <br>_Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates._  |
|  Angle | [**convert\_true\_anomaly\_to\_mean\_anomaly**](#function-convert_true_anomaly_to_mean_anomaly) (const Angle & ta, const Unitless ecc) <br>_Convert the true anomaly to the mean anomaly. Accurate to O(e^5)._  |
|  [**JulianDate**](namespaceastrea_1_1astro.md#typedef-juliandate) | [**epoch\_to\_julian\_date**](#function-epoch_to_julian_date) (const std::string & epoch, const std::string format="%Y-%m-%d %H:%M:%S") <br>_Convert a string representation of a date to a JulianDate object._  |
|  Frame\_U | [**get\_dcm**](#function-get_dcm) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br> |
|  [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md)&lt; frames::earth::icrf, frames::earth::earth\_fixed &gt; | [**get\_dcm&lt; frames::earth::icrf, frames::earth::earth\_fixed &gt;**](#function-get_dcm-frames::earth::icrf-frames::earth::earth_fixed) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Get the Direction Cosine Matrix (DCM) for the ECEF frame at a given date._  |
|  constexpr std::size\_t | [**get\_variant\_index**](#function-get_variant_index) () <br> |
|  Angle | [**julian\_date\_to\_sidereal\_time**](#function-julian_date_to_sidereal_time) (const [**JulianDate**](namespaceastrea_1_1astro.md#typedef-juliandate) & date) <br>_Convert a JulianDate to a string representation._  |
|  bool | [**nearly\_equal**](#function-nearly_equal) (const [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & first, const [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & second, bool ignoreFastVariable=false, Unitless relTol=1.0e-5 \*astrea::detail::unitless) <br>_Checks if two_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _objects are nearly equal._ |
|  bool | [**nearly\_equal**](#function-nearly_equal) (const [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) & first, const [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) & second, bool ignoreFastVariable=false, Unitless relTol=1.0e-5 \*astrea::detail::unitless) <br>_Checks if two_ [_**OrbitalElementPartials**_](classastrea_1_1astro_1_1OrbitalElementPartials.md) _objects are nearly equal._ |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator) (std::ostream & os, [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_1) (std::ostream & os, [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_2) (std::ostream & os, [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_3) (std::ostream & os, [**Spherical**](classastrea_1_1astro_1_1Spherical.md) const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_4) (std::ostream & os, const std::optional&lt; T &gt; & opt) <br>_Overloaded output stream operator for an optional type._  |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_5) (std::ostream & os, const [**GeneralPerturbations**](structastrea_1_1astro_1_1GeneralPerturbations.md) & gp) <br>_Overloaded output stream operator for_ [_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _._ |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_6) (std::ostream & os, [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_7) (std::ostream & os, [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_8) (std::ostream & os, [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_9) (std::ostream & os, [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_10) (std::ostream & os, [**EquinoctialPartial**](classastrea_1_1astro_1_1EquinoctialPartial.md) const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_11) (std::ostream & os, [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_12) (std::ostream & os, [**KeplerianPartial**](classastrea_1_1astro_1_1KeplerianPartial.md) const & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_13) (std::ostream & os, const [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_14) (std::ostream & os, const [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) & elements) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_15) (std::ostream & os, const [**State**](classastrea_1_1astro_1_1State.md) & state) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_16) (std::ostream & os, const [**Date**](classastrea_1_1astro_1_1Date.md) & obj) <br> |
|   | [**requires**](#function-requires) (origin !=CelestialBodyId::UNSET &&origin !=CelestialBodyId::CUSTOM) <br> |
|   | [**requires**](#function-requires) (origin !=CelestialBodyId::UNSET) <br> |
|   | [**requires**](#function-requires) (axis !=FrameAxis::ICRF &&axis !=FrameAxis::J2000 &&axis !=FrameAxis::BODY\_FIXED) <br> |
|   | [**requires**](#function-requires) (std::is\_constructible&lt; Frame\_T &gt;::value) <br>_Overload the output stream operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|   | [**requires**](#function-requires) (!std::is\_constructible&lt; Frame\_T &gt;::value) <br>_Overload the output stream operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|   | [**requires**](#function-requires) (![**is\_specialization**](structastrea_1_1astro_1_1is__specialization.md)&lt; Value\_U, [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) &gt;::value) <br>_Scalar multiplication operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._ |
|   | [**requires**](#function-requires) (Frame\_T::get\_axis()==FrameAxis::J2000 &&Frame\_U::get\_axis()==FrameAxis::ICRF &&HasSameOrigin&lt; Frame\_T, Frame\_U &gt;) <br>_Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date._  |
|  void | [**throw\_mismatched\_types**](#function-throw_mismatched_types) () <br>_Throws an exception for mismatched types in orbital elements._  |
|  constexpr Angle | [**wrap\_angle**](#function-wrap_angle) (const Angle & angle) <br>_Sanitize an angle to ensure it is within the range [0, 2π)._  |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  constexpr [**JulianDate**](namespaceastrea_1_1astro.md#typedef-juliandate) | [**J2000**](#function-j2000) ([**JulianDateClock::duration**](structastrea_1_1astro_1_1JulianDateClock.md#typedef-duration){ 2451545.0 }) <br>_A constant representing the J2000 epoch in Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _format._ |
|  constexpr [**JulianDate**](namespaceastrea_1_1astro.md#typedef-juliandate) | [**MJD0**](#function-mjd0) ([**JulianDateClock::duration**](structastrea_1_1astro_1_1JulianDateClock.md#typedef-duration){ 2400000.5 }) <br>_A constant representing the Modified Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _epoch in Julian_[_**Date**_](classastrea_1_1astro_1_1Date.md) _format._ |


























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
## Public Attributes Documentation




### variable HasDcm 

_Concept to determine if a Direction Cosine Matrix (DCM) can be obtained between two frames at a given date._ 
```C++
concept astrea::astro::HasDcm;
```





**Template parameters:**


* `Frame_T` The first frame type to check. 
* `Frame_U` The second frame type to check. 



**Parameters:**


* `date` The date at which to obtain the DCM. 



**Returns:**

true if the specialization of get\_dcm has been defined, false otherwise. 





        

<hr>



### variable HasDcmMethod 

_Concept to determine if a frame class has a member function to obtain the Direction Cosine Matrix (DCM) to another frame at a given date._ 
```C++
concept astrea::astro::HasDcmMethod;
```





**Template parameters:**


* `Frame_T` The frame type to check. 
* `Frame_U` The target frame type to check. 



**Parameters:**


* `frame` An instance of the frame type. 
* `date` The date at which to obtain the DCM. 



**Returns:**

true if the frame class has a member function get\_dcm for the target frame, false otherwise. 





        

<hr>



### variable HasDirectCartesianConversion 

_Concept to check if a type can be converted to_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _elements._
```C++
concept astrea::astro::HasDirectCartesianConversion;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable HasDirectEquinoctialConversion 

_Concept to check if a type can be converted to_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _elements._
```C++
concept astrea::astro::HasDirectEquinoctialConversion;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable HasDirectKeplerianConversion 

_Concept to check if a type can be converted to_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _elements._
```C++
concept astrea::astro::HasDirectKeplerianConversion;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable HasGetCoefficientOfDrag 

_Concept to check if a type has a method to get the coefficient of drag._ 
```C++
concept astrea::astro::HasGetCoefficientOfDrag;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable HasGetCoefficientOfLift 

_Concept to check if a type has a method to get the coefficient of lift._ 
```C++
concept astrea::astro::HasGetCoefficientOfLift;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable HasGetCoefficientOfReflectivity 

_Concept to check if a type has a method to get the coefficient of reflectivity._ 
```C++
concept astrea::astro::HasGetCoefficientOfReflectivity;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable HasGetLiftArea 

_Concept to check if a type has a method to get the lift area._ 
```C++
concept astrea::astro::HasGetLiftArea;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable HasGetMass 

_Concept to check if a type has a method to get the mass._ 
```C++
concept astrea::astro::HasGetMass;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable HasGetName 

_Concept to check if a type has a method to get the event name._ 
```C++
concept astrea::astro::HasGetName;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable HasGetRamArea 

_Concept to check if a type has a method to get the ram area._ 
```C++
concept astrea::astro::HasGetRamArea;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable HasGetSolarArea 

_Concept to check if a type has a method to get the solar area._ 
```C++
concept astrea::astro::HasGetSolarArea;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable HasInPlaceMathOperators 

_Concept to check if a type has in-place mathematical operators defined._ 
```C++
concept astrea::astro::HasInPlaceMathOperators;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable HasIsTerminal 

_Concept to check if a type has a method to determine if an event is terminal._ 
```C++
concept astrea::astro::HasIsTerminal;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable HasIterpolate 

_Concept to check if a type can be converted to_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _elements._
```C++
concept astrea::astro::HasIterpolate;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable HasMathOperators 

_Concept to check if a type has mathematical operators defined._ 
```C++
concept astrea::astro::HasMathOperators;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable HasMeasureEvent 

_Concept to check if a type has a method to detect an event._ 
```C++
concept astrea::astro::HasMeasureEvent;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable HasSameAxis 

_Concept to determine if two frames share the same axis._ 
```C++
concept astrea::astro::HasSameAxis;
```





**Template parameters:**


* `Frame_T` The first frame type to check. 
* `Frame_U` The second frame type to check. 



**Returns:**

true if both frames share the same axis, false otherwise. 





        

<hr>



### variable HasSameOrigin 

_Concept to determine if two frames share the same origin._ 
```C++
concept astrea::astro::HasSameOrigin;
```





**Template parameters:**


* `Frame_T` The first frame type to check. 
* `Frame_U` The second frame type to check. 



**Returns:**

true if both frames share the same origin, false otherwise. 





        

<hr>



### variable HasToVector 

_Concept to check if a type can be converted to a vector of Unitless._ 
```C++
concept astrea::astro::HasToVector;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable HasTriggerEvent 

_Concept to check if a type has a method to trigger a post-event action._ 
```C++
concept astrea::astro::HasTriggerEvent;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable IsBodyFixedFrame 

_Concept to determine if a frame is body-fixed._ 
```C++
concept astrea::astro::IsBodyFixedFrame;
```





**Template parameters:**


* `Frame_T` The frame type to check. 



**Returns:**

true if the frame is body-fixed, false otherwise. 





        

<hr>



### variable IsConstructableTo 

_Concept to check if a type can be constructed from a set of orbital elements._ 
```C++
concept astrea::astro::IsConstructableTo;
```





**Template parameters:**


* `T` The type to check. 
* `U` The type to construct from. 




        

<hr>



### variable IsDynamicFrame 

_Concept to determine if a frame is dynamic (LVLH, RIC, VNB)._ 
```C++
concept astrea::astro::IsDynamicFrame;
```





**Template parameters:**


* `Frame_T` The frame type to check. 



**Returns:**

true if the frame is dynamic, false otherwise. 





        

<hr>



### variable IsGenericallyConstructableEvent 

_Concept to check if a type can be generically constructed as a_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
concept astrea::astro::IsGenericallyConstructableEvent;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable IsGenericallyConstructableVehicle 

_Concept to check if a type can be generically constructed as a_ [_**Vehicle**_](classastrea_1_1astro_1_1Vehicle.md) _._
```C++
concept astrea::astro::IsGenericallyConstructableVehicle;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable IsInertialFrame 

_Concept to determine if a frame is inertial._ 
```C++
concept astrea::astro::IsInertialFrame;
```





**Template parameters:**


* `Frame_T` The frame type to check. 



**Returns:**

true if the frame is inertial (ICRF or J2000), false otherwise. 





        

<hr>



### variable IsOrbitalElements 

_Concept to check if a type is an orbital elements type._ 
```C++
concept astrea::astro::IsOrbitalElements;
```



This concept checks if a type is a valid orbital elements type, ensuring it meets the requirements for being default constructible, copyable, movable, destructible, and convertible to [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) elements.




**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable IsSameFrame 

_Concept to determine if two frames are the same (same origin and same axis)._ 
```C++
concept astrea::astro::IsSameFrame;
```





**Template parameters:**


* `Frame_T` The first frame type to check. 
* `Frame_U` The second frame type to check. 



**Returns:**

true if both frames are the same, false otherwise. 





        

<hr>



### variable IsStaticFrame 

_Concept to determine if a frame is static (inertial or body-fixed)._ 
```C++
concept astrea::astro::IsStaticFrame;
```





**Template parameters:**


* `Frame_T` The frame type to check. 



**Returns:**

true if the frame is static, false otherwise. 





        

<hr>



### variable IsUserDefinedEvent 

_Concept to check if a type is a user-defined_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _._
```C++
concept astrea::astro::IsUserDefinedEvent;
```





**Template parameters:**


* `T` The type to check. 




        

<hr>



### variable IsUserDefinedVehicle 

_Concept to check if a type is a user-defined vehicle._ 
```C++
concept astrea::astro::IsUserDefinedVehicle;
```





**Template parameters:**


* `T` The type to check. 




        

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
    const Angle & lat,
    const Distance & rEquitorial,
    const Distance & rPolar
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
    const Distance & range,
    const Angle & azimuth,
    const Distance & elevation
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
std::tuple< Distance, Angle, Distance > astrea::astro::convert_earth_fixed_to_cylindrical (
    const RadiusVector < frames::earth::earth_fixed > & rEcef
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
std::tuple< Angle, Angle, Distance > astrea::astro::convert_earth_fixed_to_geocentric (
    const RadiusVector < frames::earth::earth_fixed > & rEcef,
    const Distance & rEquitorial,
    const Distance & rPolar
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
std::tuple< Angle, Angle, Distance > astrea::astro::convert_earth_fixed_to_geodetic (
    const RadiusVector < frames::earth::earth_fixed > & rEcef,
    const Distance & rEquitorial,
    const Distance & rPolar
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
std::tuple< Distance, Angle, Angle > astrea::astro::convert_earth_fixed_to_spherical (
    const RadiusVector < frames::earth::earth_fixed > & rEcef
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



### function convert\_geocentric\_to\_earth\_fixed 

_Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates._ 
```C++
RadiusVector < frames::earth::earth_fixed > astrea::astro::convert_geocentric_to_earth_fixed (
    const Angle & lat,
    const Angle & lon,
    const Distance & alt,
    const Distance & rEquitorial,
    const Distance & rPolar
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
    const Angle & lat,
    const Angle & lon,
    const Distance & alt,
    const Distance & rEquitorial,
    const Distance & rPolar
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



### function convert\_spherical\_to\_earth\_fixed 

_Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates._ 
```C++
RadiusVector < frames::earth::earth_fixed > astrea::astro::convert_spherical_to_earth_fixed (
    const Distance & range,
    const Angle & inclination,
    const Angle & azimuth
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



### function get\_dcm 

```C++
Frame_U astrea::astro::get_dcm (
    const Date & date
) 
```




<hr>



### function get\_dcm&lt; frames::earth::icrf, frames::earth::earth\_fixed &gt; 

_Get the Direction Cosine Matrix (DCM) for the ECEF frame at a given date._ 
```C++
template<>
inline DirectionCosineMatrix < frames::earth::icrf, frames::earth::earth_fixed > astrea::astro::get_dcm< frames::earth::icrf, frames::earth::earth_fixed > (
    const Date & date
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



### function nearly\_equal 

_Checks if two_ [_**OrbitalElements**_](classastrea_1_1astro_1_1OrbitalElements.md) _objects are nearly equal._
```C++
bool astrea::astro::nearly_equal (
    const OrbitalElements & first,
    const OrbitalElements & second,
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
    const OrbitalElementPartials & first,
    const OrbitalElementPartials & second,
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



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Cylindrical const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Geocentric const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Geodetic const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Spherical const & elements
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
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Cartesian const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    CartesianPartial const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Equinoctial const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    EquinoctialPartial const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    Keplerian const & elements
) 
```




<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::astro::operator<< (
    std::ostream & os,
    KeplerianPartial const & elements
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



### function requires 

```C++
template<CelestialBodyId origin, FrameAxis axis>
astrea::astro::requires (
    origin !=CelestialBodyId::UNSET &&origin !=CelestialBodyId::CUSTOM
) 
```




<hr>



### function requires 

```C++
template<CelestialBodyId origin>
astrea::astro::requires (
    origin !=CelestialBodyId::UNSET
) 
```




<hr>



### function requires 

```C++
template<class Frame_T, FrameAxis axis>
astrea::astro::requires (
    axis !=FrameAxis::ICRF &&axis != FrameAxis::J2000 &&axis != FrameAxis::BODY_FIXED
) 
```




<hr>



### function requires 

_Overload the output stream operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<class Value_T, class Frame_T>
astrea::astro::requires (
    std::is_constructible< Frame_T >::value
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



### function requires 

_Overload the output stream operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<class Value_T, class Frame_T>
astrea::astro::requires (
    !std::is_constructible< Frame_T >::value
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



### function requires 

_Scalar multiplication operator for_ [_**CartesianVector**_](classastrea_1_1astro_1_1CartesianVector.md) _._
```C++
template<typename Value_T, typename Value_U, typename Frame_T>
astrea::astro::requires (
    ! is_specialization < Value_U, CartesianVector >::value
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



### function requires 

_Get the Direction Cosine Matrix (DCM) for the J2000 to ICRF at a given date._ 
```C++
template<typename Frame_T, typename Frame_U>
astrea::astro::requires (
    Frame_T::get_axis()== FrameAxis::J2000 &&Frame_U::get_axis()== FrameAxis::ICRF &&HasSameOrigin< Frame_T, Frame_U >
) 
```





**Parameters:**


* `date` The date for which to get the DCM. 



**Returns:**

DirectionCosineMatrix&lt;Frame\_T, Frame\_U&gt; The DCM from Frame\_U to Frame\_T. 





        

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
constexpr Angle astrea::astro::wrap_angle (
    const Angle & angle
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

