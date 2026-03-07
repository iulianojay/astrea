
# Class Hierarchy

This inheritance list is sorted roughly, but not completely, alphabetically:


* **class** [**astrea::astro::AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _Represents a system of celestial bodies and their interactions._ 
* **class** [**astrea::astro::Force**](classastrea_1_1astro_1_1Force.md) _Abstract base class for force models in astrodynamics._     
    * **class** [**astrea::astro::AtmosphericForce**](classastrea_1_1astro_1_1AtmosphericForce.md) _Class to compute the atmospheric force on a vehicle._ 
    * **class** [**astrea::astro::NBodyForce**](classastrea_1_1astro_1_1NBodyForce.md) _Class to compute the gravitational force due to multiple celestial bodies._ 
    * **class** [**astrea::astro::OblatenessForce**](classastrea_1_1astro_1_1OblatenessForce.md) _Class to compute the gravitational force due to the oblateness of a celestial body._ 
    * **class** [**astrea::astro::SolarRadiationPressure**](classastrea_1_1astro_1_1SolarRadiationPressure.md) _Class to compute the solar radiation pressure force on a spacecraft._ 
* **class** [**astrea::astro::Cartesian**](classastrea_1_1astro_1_1Cartesian.md) _Class representing a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector in astrodynamics._
* **class** [**astrea::astro::CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) _Class representing a partial derivative of a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._
* **class** [**astrea::astro::CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md) _Class representing a 3D vector in_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _coordinates._
* **class** [**astrea::astro::CelestialBody**](classastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._    
    * **class** [**astrea::astro::planetary\_bodies::Callisto**](classastrea_1_1astro_1_1planetary__bodies_1_1Callisto.md) _Represents the_ [_**Callisto**_](classastrea_1_1astro_1_1planetary__bodies_1_1Callisto.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Deimos**](classastrea_1_1astro_1_1planetary__bodies_1_1Deimos.md) _Represents the_ [_**Deimos**_](classastrea_1_1astro_1_1planetary__bodies_1_1Deimos.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Earth**](classastrea_1_1astro_1_1planetary__bodies_1_1Earth.md) _Represents the_ [_**Earth**_](classastrea_1_1astro_1_1planetary__bodies_1_1Earth.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Europa**](classastrea_1_1astro_1_1planetary__bodies_1_1Europa.md) _Represents the_ [_**Europa**_](classastrea_1_1astro_1_1planetary__bodies_1_1Europa.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Ganymede**](classastrea_1_1astro_1_1planetary__bodies_1_1Ganymede.md) _Represents the_ [_**Ganymede**_](classastrea_1_1astro_1_1planetary__bodies_1_1Ganymede.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Iapetus**](classastrea_1_1astro_1_1planetary__bodies_1_1Iapetus.md) _Represents the_ [_**Iapetus**_](classastrea_1_1astro_1_1planetary__bodies_1_1Iapetus.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Io**](classastrea_1_1astro_1_1planetary__bodies_1_1Io.md) _Represents the_ [_**Io**_](classastrea_1_1astro_1_1planetary__bodies_1_1Io.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Jupiter**](classastrea_1_1astro_1_1planetary__bodies_1_1Jupiter.md) _Represents the_ [_**Jupiter**_](classastrea_1_1astro_1_1planetary__bodies_1_1Jupiter.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Mars**](classastrea_1_1astro_1_1planetary__bodies_1_1Mars.md) _Represents the_ [_**Mars**_](classastrea_1_1astro_1_1planetary__bodies_1_1Mars.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Mercury**](classastrea_1_1astro_1_1planetary__bodies_1_1Mercury.md) _Represents the_ [_**Mercury**_](classastrea_1_1astro_1_1planetary__bodies_1_1Mercury.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Moon**](classastrea_1_1astro_1_1planetary__bodies_1_1Moon.md) _Represents the_ [_**Moon**_](classastrea_1_1astro_1_1planetary__bodies_1_1Moon.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Neptune**](classastrea_1_1astro_1_1planetary__bodies_1_1Neptune.md) _Represents the_ [_**Neptune**_](classastrea_1_1astro_1_1planetary__bodies_1_1Neptune.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Oberon**](classastrea_1_1astro_1_1planetary__bodies_1_1Oberon.md) _Represents the_ [_**Oberon**_](classastrea_1_1astro_1_1planetary__bodies_1_1Oberon.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Phobos**](classastrea_1_1astro_1_1planetary__bodies_1_1Phobos.md) _Represents the_ [_**Phobos**_](classastrea_1_1astro_1_1planetary__bodies_1_1Phobos.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Rhea**](classastrea_1_1astro_1_1planetary__bodies_1_1Rhea.md) _Represents the_ [_**Rhea**_](classastrea_1_1astro_1_1planetary__bodies_1_1Rhea.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Saturn**](classastrea_1_1astro_1_1planetary__bodies_1_1Saturn.md) _Represents the_ [_**Saturn**_](classastrea_1_1astro_1_1planetary__bodies_1_1Saturn.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Sun**](classastrea_1_1astro_1_1planetary__bodies_1_1Sun.md) _Represents the_ [_**Sun**_](classastrea_1_1astro_1_1planetary__bodies_1_1Sun.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Titan**](classastrea_1_1astro_1_1planetary__bodies_1_1Titan.md) _Represents the_ [_**Titan**_](classastrea_1_1astro_1_1planetary__bodies_1_1Titan.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Titania**](classastrea_1_1astro_1_1planetary__bodies_1_1Titania.md) _Represents the_ [_**Titania**_](classastrea_1_1astro_1_1planetary__bodies_1_1Titania.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Triton**](classastrea_1_1astro_1_1planetary__bodies_1_1Triton.md) _Represents the_ [_**Triton**_](classastrea_1_1astro_1_1planetary__bodies_1_1Triton.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Uranus**](classastrea_1_1astro_1_1planetary__bodies_1_1Uranus.md) _Represents the_ [_**Uranus**_](classastrea_1_1astro_1_1planetary__bodies_1_1Uranus.md) _celestial body._
    * **class** [**astrea::astro::planetary\_bodies::Venus**](classastrea_1_1astro_1_1planetary__bodies_1_1Venus.md) _Represents the_ [_**Venus**_](classastrea_1_1astro_1_1planetary__bodies_1_1Venus.md) _celestial body._
* **class** [**astrea::astro::Constellation**](classastrea_1_1astro_1_1Constellation.md) _A_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _is a collection of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _, organized into Shells and/or Planes._
* **class** [**astrea::astro::Constellation::sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _Iterator class for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
* **class** [**astrea::astro::EquationsOfMotion**](classastrea_1_1astro_1_1EquationsOfMotion.md) _Base class for equations of motion in astrodynamics._     
    * **class** [**astrea::astro::CowellsMethod**](classastrea_1_1astro_1_1CowellsMethod.md) _Class implementing Cowell's method for equations of motion._ 
    * **class** [**astrea::astro::EquinoctialVop**](classastrea_1_1astro_1_1EquinoctialVop.md) _Class implementing the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _VOP equations of motion._
    * **class** [**astrea::astro::J2MeanVop**](classastrea_1_1astro_1_1J2MeanVop.md) _Class implementing the J2 Mean VOP equations of motion._ 
    * **class** [**astrea::astro::KeplerianVop**](classastrea_1_1astro_1_1KeplerianVop.md) _Class implementing the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _VOP equations of motion._
    * **class** [**astrea::astro::TwoBody**](classastrea_1_1astro_1_1TwoBody.md) _Class implementing the Two Body equations of motion._ 
* **class** [**astrea::astro::Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) _Class representing a_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector in astrodynamics._
* **class** [**astrea::astro::Date**](classastrea_1_1astro_1_1Date.md) _Class representing a date in the astrea astro library._ 
* **class** [**astrea::astro::DirectionCosineMatrix**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) _Class representing a direction cosine matrix (DCM) for transforming vectors between state/frames._ 
* **class** [**astrea::astro::Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) _The_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _class represents the equinoctial orbital elements._
* **class** [**astrea::astro::EquinoctialPartial**](classastrea_1_1astro_1_1EquinoctialPartial.md) _Class representing a partial derivative of an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._
* **class** [**astrea::astro::Event**](classastrea_1_1astro_1_1Event.md) _A class representing a_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class serves as a base for user-defined Events and provides a common interface._
* **class** [**astrea::astro::EventDetector**](classastrea_1_1astro_1_1EventDetector.md) _A class for detecting events in the astrea astro platform._ 
* **class** [**astrea::astro::ForceModel**](classastrea_1_1astro_1_1ForceModel.md) _Class to manage multiple force models and compute the total force on a vehicle._ 
* **class** [**astrea::astro::FrameReference**](classastrea_1_1astro_1_1FrameReference.md) _Base class for all frame references._     
    * **class** [**astrea::astro::NullVehicle**](classastrea_1_1astro_1_1NullVehicle.md) _A class representing a null vehicle in the astrea astro platform. This class is used as a placeholder for vehicles that do not have a defined state or mass._ 
    * **class** [**astrea::astro::PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) _The_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _class represents a platform that can have payloads attached to it. It provides methods to attach payloads and retrieve the list of attached payloads._    
        * **class** [**astrea::astro::Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) _A class representing a spacecraft in the astrea astro platform. This class encapsulates the properties of a spacecraft, including its mass, dynamic coefficients, and surface areas._ 
    * **class** [**astrea::astro::Vehicle**](classastrea_1_1astro_1_1Vehicle.md) _A class representing a vehicle in the astrea astro platform. This class serves as a base for user-defined vehicles and provides a common interface._ 
    * **struct** [**astrea::astro::detail::VehicleInnerBase**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md) _Pure virtual base class for vehicle inner implementations._     
        * **struct** [**astrea::astro::detail::VehicleInner**](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) _A template class for vehicle inner implementations._ 
* **class** [**astrea::astro::Geocentric**](classastrea_1_1astro_1_1Geocentric.md) _Class representing a_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector in astrodynamics._
* **class** [**astrea::astro::Geodetic**](classastrea_1_1astro_1_1Geodetic.md) _Class representing a_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector in astrodynamics._
* **class** [**astrea::astro::ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md) _A class representing an impulsive burn_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _. It triggers when the true anomaly wraps around (i.e. at perigee), and applies the total impulsive delta-v from all thrusters to the vehicle in the velocity direction. TODO: Generalize to a scheduler of some sort and other burn triggers. TODO: Generalize burn direction. TODO: Generalize which thrusters burn._
* **class** [**astrea::astro::Integrator**](classastrea_1_1astro_1_1Integrator.md) [_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _class for numerical propagation of orbital mechanics problems._
* **class** [**astrea::astro::Interval**](classastrea_1_1astro_1_1Interval.md) _Represents a time interval with a start and end time._ 
* **class** [**astrea::astro::Keplerian**](classastrea_1_1astro_1_1Keplerian.md) _The_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _class represents the_[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _orbital elements._
* **class** [**astrea::astro::KeplerianPartial**](classastrea_1_1astro_1_1KeplerianPartial.md) _Class representing a partial derivative of a_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._
* **class** [**astrea::astro::LambertSolver**](classastrea_1_1astro_1_1LambertSolver.md) _Class for solving Lambert's problem._ 
* **class** [**astrea::astro::LegendreCache**](classastrea_1_1astro_1_1LegendreCache.md) 
* **class** [**astrea::astro::NullEvent**](classastrea_1_1astro_1_1NullEvent.md) _A class representing a null_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class is used as a placeholder for Events that do not have a defined state or mass._
* **class** [**astrea::astro::OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) _Class representing partial derivatives of orbital elements._ 
* **class** [**astrea::astro::OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) _Class representing a set of orbital elements._ 
* **class** [**astrea::astro::Payload**](classastrea_1_1astro_1_1Payload.md) [_**Payload**_](classastrea_1_1astro_1_1Payload.md) _class representing a payload on a platform._
* **class** [**astrea::astro::PayloadParameters**](classastrea_1_1astro_1_1PayloadParameters.md) _Class for storing and managing payload parameters._     
    * **class** [**astrea::astro::ThrusterParameters**](classastrea_1_1astro_1_1ThrusterParameters.md) _Class for storing and managing thruster parameters._ 
* **class** [**astrea::astro::Plane**](classastrea_1_1astro_1_1Plane.md) _A_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _is a collection of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _that share the same orbital elements._
* **class** [**astrea::astro::Shell**](classastrea_1_1astro_1_1Shell.md) _A_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _is a collection of planes, each containing a set of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _. It is used to represent sub-constellations of satellites in orbit._
* **class** [**astrea::astro::Shell::sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _Iterator for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._
* **class** [**astrea::astro::Spherical**](classastrea_1_1astro_1_1Spherical.md) _Class representing a_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector in astrodynamics._
* **class** [**astrea::astro::State**](classastrea_1_1astro_1_1State.md) _Class representing the state of an astronomical object._ 
* **class** [**astrea::astro::StateHistory**](classastrea_1_1astro_1_1StateHistory.md) _Class to manage the history of states for an object over date._ 
* **class** [**astrea::astro::StatePartial**](classastrea_1_1astro_1_1StatePartial.md) 
* **class** [**astrea::astro::StateTransitionMatrix**](classastrea_1_1astro_1_1StateTransitionMatrix.md) 
* **class** [**astrea::astro::TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) _Class representing the two-line element (TLE) format for orbital data._ 
* **struct** [**astrea::astro::CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) 
* **struct** [**astrea::astro::Frame**](structastrea_1_1astro_1_1Frame.md) _Base class for all state/frames._ 
* **struct** [**astrea::astro::GeneralPerturbations**](structastrea_1_1astro_1_1GeneralPerturbations.md) [_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _structure representing a Ground Position (GP) object from SpaceTrack._
* **struct** [**astrea::astro::JplEphemerisTable**](structastrea_1_1astro_1_1JplEphemerisTable.md) _Base class for any JPL_ [_**CelestialBody**_](classastrea_1_1astro_1_1CelestialBody.md) _table._
* **struct** [**astrea::astro::JulianDateClock**](structastrea_1_1astro_1_1JulianDateClock.md) _A clock implementation for Julian Dates._ 
* **struct** [**astrea::astro::detail::EventInnerBase**](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md) _Pure virtual base class for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _inner implementations._    
    * **struct** [**astrea::astro::detail::EventInner**](structastrea_1_1astro_1_1detail_1_1EventInner.md) _A template class for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _inner implementations._
* **struct** [**astrea::astro::EventDetector::EventTracker**](structastrea_1_1astro_1_1EventDetector_1_1EventTracker.md) _A struct for tracking events._ 
* **struct** [**mp\_units::quantity\_point\_like\_traits&lt; astrea::astro::Date &gt;**](structmp__units_1_1quantity__point__like__traits_3_01astrea_1_1astro_1_1Date_01_4.md) _Specialization of mp\_units::quantity\_point\_like\_traits for the Date class._ 
* **struct** [**std::hash&lt; astrea::astro::CelestialBody &gt;**](structstd_1_1hash_3_01astrea_1_1astro_1_1CelestialBody_01_4.md) _Hash function for CelestialBody._ 
* **struct** [**std::hash&lt; std::tuple&lt; TT... &gt; &gt;**](structstd_1_1hash_3_01std_1_1tuple_3_01TT_8_8_8_01_4_01_4.md) 
* **class** **DynamicFrame< EastNorthUp, FrameAxis::ENU >**    
    * **class** [**astrea::astro::frames::EastNorthUp**](classastrea_1_1astro_1_1frames_1_1EastNorthUp.md) _Class representing the East, North, Up (ENU) frame._ 
* **class** **DynamicFrame< LocalHorizontalLocalVertical, FrameAxis::LVLH >**    
    * **class** [**astrea::astro::frames::LocalHorizontalLocalVertical**](classastrea_1_1astro_1_1frames_1_1LocalHorizontalLocalVertical.md) _Class representing the Local Horizontal, Local Vertical (LVLH) frame._ 
* **class** **DynamicFrame< RadialInTrackCrossTrack, FrameAxis::RIC >**    
    * **class** [**astrea::astro::frames::RadialInTrackCrossTrack**](classastrea_1_1astro_1_1frames_1_1RadialInTrackCrossTrack.md) _Class representing the Radial, In-Track, Cross-Track (RIC) frame._ 
* **class** **DynamicFrame< VelocityNormalBinormal, FrameAxis::VNB >**    
    * **class** [**astrea::astro::frames::VelocityNormalBinormal**](classastrea_1_1astro_1_1frames_1_1VelocityNormalBinormal.md) _Class representing the Velocity, Normal, Binormal (VNB) frame._ 
* **class** **std::false_type**    
    * **struct** [**astrea::astro::is\_specialization**](structastrea_1_1astro_1_1is__specialization.md) 
* **class** **std::true_type**    
    * **struct** [**astrea::astro::is\_specialization&lt; Template&lt; Args... &gt;, Template &gt;**](structastrea_1_1astro_1_1is__specialization_3_01Template_3_01Args_8_8_8_01_4_00_01Template_01_4.md) 

