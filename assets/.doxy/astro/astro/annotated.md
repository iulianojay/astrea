
# Class List


Here are the classes, structs, unions and interfaces with brief descriptions:

* **namespace** [**astrea**](namespaceastrea.md)     
    * **namespace** [**astro**](namespaceastrea_1_1astro.md)     
        * **class** [**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _Represents a system of celestial bodies and their interactions._     
        * **class** [**AtmosphericForce**](classastrea_1_1astro_1_1AtmosphericForce.md) _Class to compute the atmospheric force on a vehicle._     
        * **struct** [**BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Base class for all body fixed frames._     
        * **class** [**Cartesian**](classastrea_1_1astro_1_1Cartesian.md) _Class representing a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector in astrodynamics._    
        * **class** [**CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) _Class representing a partial derivative of a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._    
        * **class** [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) _Class representing a 3D vector in_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _coordinates._    
        * **class** [**CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._    
        * **struct** [**CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md)     
        * **class** [**Constellation**](classastrea_1_1astro_1_1Constellation.md) _A_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _is a collection of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _, organized into Shells and/or Planes._    
            * **class** [**sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _Iterator class for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._    
        * **class** [**CowellsMethod**](classastrea_1_1astro_1_1CowellsMethod.md) _Class implementing Cowell's method for equations of motion._     
        * **class** [**Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) _Class representing a_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector in astrodynamics._    
        * **namespace** [**DOP45**](namespaceastrea_1_1astro_1_1DOP45.md)     
        * **namespace** [**DOP78**](namespaceastrea_1_1astro_1_1DOP78.md)     
        * **class** [**Date**](classastrea_1_1astro_1_1Date.md) _Class representing a date in the astrea astro library._     
        * **class** [**DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) _Class representing a direction cosine matrix (DCM) for transforming vectors between state/frames._     
        * **struct** [**DynamicFrame**](classastrea_1_1astro_1_1DynamicFrame.md) _Base class for all dynamic state/frames._     
        * **class** [**EquationsOfMotion**](classastrea_1_1astro_1_1EquationsOfMotion.md) _Base class for equations of motion in astrodynamics._     
        * **class** [**Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) _The_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _class represents the equinoctial orbital elements._    
        * **class** [**EquinoctialPartial**](classastrea_1_1astro_1_1EquinoctialPartial.md) _Class representing a partial derivative of an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._    
        * **class** [**EquinoctialVop**](classastrea_1_1astro_1_1EquinoctialVop.md) _Class implementing the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _VOP equations of motion._    
        * **class** [**Event**](classastrea_1_1astro_1_1Event.md) _A class representing a_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class serves as a base for user-defined Events and provides a common interface._    
        * **class** [**EventDetector**](classastrea_1_1astro_1_1EventDetector.md) _A class for detecting events in the astrea astro platform._     
        * **class** [**Force**](classastrea_1_1astro_1_1Force.md) _Abstract base class for force models in astrodynamics._     
        * **class** [**ForceModel**](classastrea_1_1astro_1_1ForceModel.md) _Class to manage multiple force models and compute the total force on a vehicle._     
        * **struct** [**Frame**](structastrea_1_1astro_1_1Frame.md) _Base class for all state/frames._     
        * **class** [**FrameReference**](classastrea_1_1astro_1_1FrameReference.md) _Base class for all frame references._     
        * **struct** [**GeneralPerturbations**](structastrea_1_1astro_1_1GeneralPerturbations.md) [_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _structure representing a Ground Position (GP) object from SpaceTrack._    
        * **class** [**Geocentric**](classastrea_1_1astro_1_1Geocentric.md) _Class representing a_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector in astrodynamics._    
        * **class** [**Geodetic**](classastrea_1_1astro_1_1Geodetic.md) _Class representing a_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector in astrodynamics._    
        * **class** [**ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md) _A class representing an impulsive burn_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _. It triggers when the true anomaly wraps around (i.e. at perigee), and applies the total impulsive delta-v from all thrusters to the vehicle in the velocity direction. TODO: Generalize to a scheduler of some sort and other burn triggers. TODO: Generalize burn direction. TODO: Generalize which thrusters burn._    
        * **struct** [**InertialFrame**](structastrea_1_1astro_1_1InertialFrame.md) _Base class for all inertial state/frames._     
        * **class** [**Integrator**](classastrea_1_1astro_1_1Integrator.md) [_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _class for numerical propagation of orbital mechanics problems._    
        * **class** [**Interval**](classastrea_1_1astro_1_1Interval.md) _Represents a time interval with a start and end time._     
        * **class** [**J2MeanVop**](classastrea_1_1astro_1_1J2MeanVop.md) _Class implementing the J2 Mean VOP equations of motion._     
        * **struct** [**JplEphemerisTable**](structastrea_1_1astro_1_1JplEphemerisTable.md) _Base class for any JPL_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _table._    
        * **struct** [**JulianDateClock**](structastrea_1_1astro_1_1JulianDateClock.md) _A clock implementation for Julian Dates._     
        * **class** [**Keplerian**](classastrea_1_1astro_1_1Keplerian.md) _The_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _class represents the_[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _orbital elements._    
        * **class** [**KeplerianPartial**](classastrea_1_1astro_1_1KeplerianPartial.md) _Class representing a partial derivative of a_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._    
        * **class** [**KeplerianVop**](classastrea_1_1astro_1_1KeplerianVop.md) _Class implementing the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _VOP equations of motion._    
        * **class** [**LambertSolver**](classastrea_1_1astro_1_1LambertSolver.md) _Class for solving Lambert's problem._     
        * **class** [**LegendreCache**](classastrea_1_1astro_1_1LegendreCache.md)     
        * **class** [**NBodyForce**](classastrea_1_1astro_1_1NBodyForce.md) _Class to compute the gravitational force due to multiple celestial bodies._     
        * **class** [**NullEvent**](classastrea_1_1astro_1_1NullEvent.md) _A class representing a null_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class is used as a placeholder for Events that do not have a defined state or mass._    
        * **class** [**NullVehicle**](classastrea_1_1astro_1_1NullVehicle.md) _A class representing a null vehicle in the astrea astro platform. This class is used as a placeholder for vehicles that do not have a defined state or mass._     
        * **class** [**OblatenessForce**](classastrea_1_1astro_1_1OblatenessForce.md) _Class to compute the gravitational force due to the oblateness of a celestial body._     
        * **class** [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) _Class representing partial derivatives of orbital elements._     
        * **class** [**OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) _Class representing a set of orbital elements._     
        * **class** [**Payload**](classastrea_1_1astro_1_1Payload.md) [_**Payload**_](classastrea_1_1astro_1_1Payload.md) _class representing a payload on a platform._    
        * **class** [**PayloadParameters**](classastrea_1_1astro_1_1PayloadParameters.md) _Class for storing and managing payload parameters._     
        * **class** [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) _The_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _class represents a platform that can have payloads attached to it. It provides methods to attach payloads and retrieve the list of attached payloads._    
        * **class** [**Plane**](classastrea_1_1astro_1_1Plane.md) _A_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _is a collection of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _that share the same orbital elements._    
        * **namespace** [**RK45**](namespaceastrea_1_1astro_1_1RK45.md)     
        * **namespace** [**RKF45**](namespaceastrea_1_1astro_1_1RKF45.md)     
        * **namespace** [**RKF78**](namespaceastrea_1_1astro_1_1RKF78.md)     
        * **class** [**Shell**](classastrea_1_1astro_1_1Shell.md) _A_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _is a collection of planes, each containing a set of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _. It is used to represent sub-constellations of satellites in orbit._    
            * **class** [**sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _Iterator for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._    
        * **class** [**SolarRadiationPressure**](classastrea_1_1astro_1_1SolarRadiationPressure.md) _Class to compute the solar radiation pressure force on a spacecraft._     
        * **class** [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) _A class representing a spacecraft in the astrea astro platform. This class encapsulates the properties of a spacecraft, including its mass, dynamic coefficients, and surface areas._     
        * **class** [**Spherical**](classastrea_1_1astro_1_1Spherical.md) _Class representing a_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector in astrodynamics._    
        * **class** [**State**](classastrea_1_1astro_1_1State.md) _Class representing the state of an astronomical object._     
        * **class** [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) _Class to manage the history of states for an object over date._     
        * **class** [**StatePartial**](classastrea_1_1astro_1_1StatePartial.md)     
        * **class** [**StateTransitionMatrix**](classastrea_1_1astro_1_1StateTransitionMatrix.md)     
        * **class** [**Thruster**](classastrea_1_1astro_1_1Thruster.md) [_**Thruster**_](classastrea_1_1astro_1_1Thruster.md) _class representing a thruster on a platform._    
        * **class** [**ThrusterParameters**](classastrea_1_1astro_1_1ThrusterParameters.md) _Class for storing and managing thruster parameters._     
        * **class** [**TwoBody**](classastrea_1_1astro_1_1TwoBody.md) _Class implementing the Two Body equations of motion._     
        * **class** [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) _Class representing the two-line element (TLE) format for orbital data._     
        * **class** [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) _A class representing a vehicle in the astrea astro platform. This class serves as a base for user-defined vehicles and provides a common interface._     
        * **namespace** [**detail**](namespaceastrea_1_1astro_1_1detail.md)     
            * **struct** [**EventInner**](structastrea_1_1astro_1_1detail_1_1EventInner.md) _A template class for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _inner implementations._    
            * **struct** [**EventInnerBase**](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md) _Pure virtual base class for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _inner implementations._    
            * **struct** [**VehicleInner**](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) _A template class for vehicle inner implementations._     
            * **struct** [**VehicleInnerBase**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md) _Pure virtual base class for vehicle inner implementations._     
        * **namespace** [**frames**](namespaceastrea_1_1astro_1_1frames.md)     
            * **class** [**EastNorthUp**](classastrea_1_1astro_1_1frames_1_1EastNorthUp.md) _Class representing the East, North, Up (ENU) frame._     
            * **class** [**LocalHorizontalLocalVertical**](classastrea_1_1astro_1_1frames_1_1LocalHorizontalLocalVertical.md) _Class representing the Local Horizontal, Local Vertical (LVLH) frame._     
            * **class** [**RadialInTrackCrossTrack**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) _Class representing the Radial, In-Track, Cross-Track (RIC) frame._     
            * **class** [**VelocityNormalBinormal**](classastrea_1_1astro_1_1frames_1_1VelocityNormalBinormal.md) _Class representing the Velocity, Normal, Binormal (VNB) frame._     
            * **namespace** [**callisto**](namespaceastrea_1_1astro_1_1frames_1_1callisto.md)     
            * **namespace** [**deimos**](namespaceastrea_1_1astro_1_1frames_1_1deimos.md)     
            * **namespace** [**dynamic**](namespaceastrea_1_1astro_1_1frames_1_1dynamic.md)     
            * **namespace** [**earth**](namespaceastrea_1_1astro_1_1frames_1_1earth.md)     
            * **namespace** [**earth\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1earth__barycenter.md)     
            * **namespace** [**europa**](namespaceastrea_1_1astro_1_1frames_1_1europa.md)     
            * **namespace** [**ganymede**](namespaceastrea_1_1astro_1_1frames_1_1ganymede.md)     
            * **namespace** [**iapetus**](namespaceastrea_1_1astro_1_1frames_1_1iapetus.md)     
            * **namespace** [**io**](namespaceastrea_1_1astro_1_1frames_1_1io.md)     
            * **namespace** [**jupiter**](namespaceastrea_1_1astro_1_1frames_1_1jupiter.md)     
            * **namespace** [**jupiter\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1jupiter__barycenter.md)     
            * **namespace** [**mars**](namespaceastrea_1_1astro_1_1frames_1_1mars.md)     
            * **namespace** [**mars\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1mars__barycenter.md)     
            * **namespace** [**mercury**](namespaceastrea_1_1astro_1_1frames_1_1mercury.md)     
            * **namespace** [**mercury\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1mercury__barycenter.md)     
            * **namespace** [**moon**](namespaceastrea_1_1astro_1_1frames_1_1moon.md)     
            * **namespace** [**neptune**](namespaceastrea_1_1astro_1_1frames_1_1neptune.md)     
            * **namespace** [**neptune\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1neptune__barycenter.md)     
            * **namespace** [**oberon**](namespaceastrea_1_1astro_1_1frames_1_1oberon.md)     
            * **namespace** [**phobos**](namespaceastrea_1_1astro_1_1frames_1_1phobos.md)     
            * **namespace** [**rhea**](namespaceastrea_1_1astro_1_1frames_1_1rhea.md)     
            * **namespace** [**saturn**](namespaceastrea_1_1astro_1_1frames_1_1saturn.md)     
            * **namespace** [**saturn\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1saturn__barycenter.md)     
            * **namespace** [**solar\_system\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1solar__system__barycenter.md)     
            * **namespace** [**sun**](namespaceastrea_1_1astro_1_1frames_1_1sun.md)     
            * **namespace** [**titan**](namespaceastrea_1_1astro_1_1frames_1_1titan.md)     
            * **namespace** [**titania**](namespaceastrea_1_1astro_1_1frames_1_1titania.md)     
            * **namespace** [**triton**](namespaceastrea_1_1astro_1_1frames_1_1triton.md)     
            * **namespace** [**uranus**](namespaceastrea_1_1astro_1_1frames_1_1uranus.md)     
            * **namespace** [**uranus\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1uranus__barycenter.md)     
            * **namespace** [**venus**](namespaceastrea_1_1astro_1_1frames_1_1venus.md)     
            * **namespace** [**venus\_barycenter**](namespaceastrea_1_1astro_1_1frames_1_1venus__barycenter.md)     
        * **struct** [**is\_specialization**](structastrea_1_1astro_1_1is__specialization.md) 
        * **struct** [**is\_specialization&lt; Template&lt; Args... &gt;, Template &gt;**](structastrea_1_1astro_1_1is__specialization_3_01Template_3_01Args_8_8_8_01_4_00_01Template_01_4.md) 
        * **namespace** [**planetary\_bodies**](namespaceastrea_1_1astro_1_1planetary__bodies.md)     
            * **class** [**Callisto**](classastrea_1_1astro_1_1planetary__bodies_1_1Callisto.md) _Represents the_ [_**Callisto**_](classastrea_1_1astro_1_1planetary__bodies_1_1Callisto.md) _celestial body._    
            * **class** [**Deimos**](classastrea_1_1astro_1_1planetary__bodies_1_1Deimos.md) _Represents the_ [_**Deimos**_](classastrea_1_1astro_1_1planetary__bodies_1_1Deimos.md) _celestial body._    
            * **class** [**Earth**](classastrea_1_1astro_1_1planetary__bodies_1_1Earth.md) _Represents the_ [_**Earth**_](classastrea_1_1astro_1_1planetary__bodies_1_1Earth.md) _celestial body._    
            * **class** [**Europa**](classastrea_1_1astro_1_1planetary__bodies_1_1Europa.md) _Represents the_ [_**Europa**_](classastrea_1_1astro_1_1planetary__bodies_1_1Europa.md) _celestial body._    
            * **class** [**Ganymede**](classastrea_1_1astro_1_1planetary__bodies_1_1Ganymede.md) _Represents the_ [_**Ganymede**_](classastrea_1_1astro_1_1planetary__bodies_1_1Ganymede.md) _celestial body._    
            * **class** [**Iapetus**](classastrea_1_1astro_1_1planetary__bodies_1_1Iapetus.md) _Represents the_ [_**Iapetus**_](classastrea_1_1astro_1_1planetary__bodies_1_1Iapetus.md) _celestial body._    
            * **class** [**Io**](classastrea_1_1astro_1_1planetary__bodies_1_1Io.md) _Represents the_ [_**Io**_](classastrea_1_1astro_1_1planetary__bodies_1_1Io.md) _celestial body._    
            * **class** [**Jupiter**](classastrea_1_1astro_1_1planetary__bodies_1_1Jupiter.md) _Represents the_ [_**Jupiter**_](classastrea_1_1astro_1_1planetary__bodies_1_1Jupiter.md) _celestial body._    
            * **class** [**Mars**](classastrea_1_1astro_1_1planetary__bodies_1_1Mars.md) _Represents the_ [_**Mars**_](classastrea_1_1astro_1_1planetary__bodies_1_1Mars.md) _celestial body._    
            * **class** [**Mercury**](classastrea_1_1astro_1_1planetary__bodies_1_1Mercury.md) _Represents the_ [_**Mercury**_](classastrea_1_1astro_1_1planetary__bodies_1_1Mercury.md) _celestial body._    
            * **class** [**Moon**](classastrea_1_1astro_1_1planetary__bodies_1_1Moon.md) _Represents the_ [_**Moon**_](classastrea_1_1astro_1_1planetary__bodies_1_1Moon.md) _celestial body._    
            * **class** [**Neptune**](classastrea_1_1astro_1_1planetary__bodies_1_1Neptune.md) _Represents the_ [_**Neptune**_](classastrea_1_1astro_1_1planetary__bodies_1_1Neptune.md) _celestial body._    
            * **class** [**Oberon**](classastrea_1_1astro_1_1planetary__bodies_1_1Oberon.md) _Represents the_ [_**Oberon**_](classastrea_1_1astro_1_1planetary__bodies_1_1Oberon.md) _celestial body._    
            * **class** [**Phobos**](classastrea_1_1astro_1_1planetary__bodies_1_1Phobos.md) _Represents the_ [_**Phobos**_](classastrea_1_1astro_1_1planetary__bodies_1_1Phobos.md) _celestial body._    
            * **class** [**Rhea**](classastrea_1_1astro_1_1planetary__bodies_1_1Rhea.md) _Represents the_ [_**Rhea**_](classastrea_1_1astro_1_1planetary__bodies_1_1Rhea.md) _celestial body._    
            * **class** [**Saturn**](classastrea_1_1astro_1_1planetary__bodies_1_1Saturn.md) _Represents the_ [_**Saturn**_](classastrea_1_1astro_1_1planetary__bodies_1_1Saturn.md) _celestial body._    
            * **class** [**Sun**](classastrea_1_1astro_1_1planetary__bodies_1_1Sun.md) _Represents the_ [_**Sun**_](classastrea_1_1astro_1_1planetary__bodies_1_1Sun.md) _celestial body._    
            * **class** [**Titan**](classastrea_1_1astro_1_1planetary__bodies_1_1Titan.md) _Represents the_ [_**Titan**_](classastrea_1_1astro_1_1planetary__bodies_1_1Titan.md) _celestial body._    
            * **class** [**Titania**](classastrea_1_1astro_1_1planetary__bodies_1_1Titania.md) _Represents the_ [_**Titania**_](classastrea_1_1astro_1_1planetary__bodies_1_1Titania.md) _celestial body._    
            * **class** [**Triton**](classastrea_1_1astro_1_1planetary__bodies_1_1Triton.md) _Represents the_ [_**Triton**_](classastrea_1_1astro_1_1planetary__bodies_1_1Triton.md) _celestial body._    
            * **class** [**Uranus**](classastrea_1_1astro_1_1planetary__bodies_1_1Uranus.md) _Represents the_ [_**Uranus**_](classastrea_1_1astro_1_1planetary__bodies_1_1Uranus.md) _celestial body._    
            * **class** [**Venus**](classastrea_1_1astro_1_1planetary__bodies_1_1Venus.md) _Represents the_ [_**Venus**_](classastrea_1_1astro_1_1planetary__bodies_1_1Venus.md) _celestial body._    
        * **namespace** [**plotting**](namespaceastrea_1_1astro_1_1plotting.md)     
* **struct** [**EventTracker**](structastrea_1_1astro_1_1EventDetector_1_1EventTracker.md) _A struct for tracking events._     
* **namespace** [**frames**](namespaceastrea_1_1astro_1_1frames_1_1_0d17.md) 
* **namespace** [**plotting**](namespaceastrea_1_1astro_1_1plotting_1_1_0d151.md) 
* **namespace** [**matplot**](namespacematplot.md) 
* **namespace** [**mp\_units**](namespacemp__units.md)     
    * **struct** [**quantity\_point\_like\_traits&lt; astrea::astro::Date &gt;**](structmp__units_1_1quantity__point__like__traits_3_01astrea_1_1astro_1_1Date_01_4.md) _Specialization of mp\_units::quantity\_point\_like\_traits for the Date class._     
* **namespace** [**angular**](namespacemp__units_1_1angular.md) 
* **namespace** [**non\_si**](namespacemp__units_1_1non__si.md) 
* **namespace** [**si**](namespacemp__units_1_1si.md) 
* **namespace** [**unit\_symbols**](namespacemp__units_1_1si_1_1unit__symbols.md) 
* **namespace** [**std**](namespacestd.md)     
    * **struct** [**hash&lt; astrea::astro::CelestialBody &gt;**](structstd_1_1hash_3_01astrea_1_1astro_1_1CelestialBody_01_4.md) _Hash function for CelestialBody._     
    * **struct** [**hash&lt; std::tuple&lt; TT... &gt; &gt;**](structstd_1_1hash_3_01std_1_1tuple_3_01TT_8_8_8_01_4_01_4.md)     
* **namespace** [**std**](namespacestd_1_1_0d145.md) 

