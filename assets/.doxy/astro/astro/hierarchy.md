
# Class Hierarchy

This inheritance list is sorted roughly, but not completely, alphabetically:


* **class** [**astrea::astro::AngularAccelerations**](classastrea_1_1astro_1_1AngularAccelerations.md) _Class representing the angular sequence acceleration, which is the time derivative of the angular sequence velocity._ 
* **class** [**astrea::astro::AngularVelocities**](classastrea_1_1astro_1_1AngularVelocities.md) _Class representing a sequence of angular velocities (either Euler or Tait-Bryan) for attitude transformations between frames._ 
* **class** [**astrea::astro::PerturbingForce**](classastrea_1_1astro_1_1PerturbingForce.md) _Abstract base class for force models in astrodynamics._     
    * **class** [**astrea::astro::AtmosphericForce**](classastrea_1_1astro_1_1AtmosphericForce.md) _Class to compute the atmospheric force on a vehicle._ 
    * **class** [**astrea::astro::NBodyForce**](classastrea_1_1astro_1_1NBodyForce.md) _Class to compute the gravitational force due to multiple celestial bodies._ 
    * **class** [**astrea::astro::OblatenessForce**](classastrea_1_1astro_1_1OblatenessForce.md) _Class to compute the gravitational force due to the oblateness of a celestial_ _body_ _._
    * **class** [**astrea::astro::SolarRadiationPressure**](classastrea_1_1astro_1_1SolarRadiationPressure.md) _Class to compute the solar radiation pressure force on a spacecraft._ 
* **class** [**astrea::astro::Attitude**](classastrea_1_1astro_1_1Attitude.md) _Class representing a set of orientation._ 
* **class** [**astrea::astro::AttitudePartials**](classastrea_1_1astro_1_1AttitudePartials.md) _Class representing partial derivatives of orientation._ 
* **class** [**astrea::astro::Cartesian**](classastrea_1_1astro_1_1Cartesian.md) _Class representing a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector in astrodynamics._
* **class** [**astrea::astro::CartesianPartial**](classastrea_1_1astro_1_1CartesianPartial.md) _Class representing a partial derivative of a_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _state vector._
* **class** [**astrea::astro::EquationsOfMotion**](classastrea_1_1astro_1_1EquationsOfMotion.md) _Base class for equations of motion in astrodynamics._     
    * **class** [**astrea::astro::CircularRestrictedThreeBodyProblem**](classastrea_1_1astro_1_1CircularRestrictedThreeBodyProblem.md) _Class implementing the Circular Restricted Three-Body Problem equations of motion._ 
    * **class** [**astrea::astro::CowellsMethod**](classastrea_1_1astro_1_1CowellsMethod.md) _Class implementing Cowell's method for equations of motion._ 
    * **class** [**astrea::astro::EquinoctialVop**](classastrea_1_1astro_1_1EquinoctialVop.md) _Class implementing the_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _VOP equations of motion._
    * **class** [**astrea::astro::J2MeanVop**](classastrea_1_1astro_1_1J2MeanVop.md) _Class implementing the J2 Mean VOP equations of motion._ 
    * **class** [**astrea::astro::KeplerianVop**](classastrea_1_1astro_1_1KeplerianVop.md) _Class implementing the_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _VOP equations of motion._
    * **class** [**astrea::astro::TwoBody**](classastrea_1_1astro_1_1TwoBody.md) _Class implementing the Two Body equations of motion._ 
* **class** [**astrea::astro::Constellation**](classastrea_1_1astro_1_1Constellation.md) _A_ [_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _is a collection of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _, organized into Shells and/or Planes._
* **class** [**astrea::astro::Constellation::sat\_iterator**](classastrea_1_1astro_1_1Constellation_1_1sat__iterator.md) _Iterator class for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Constellation**_](classastrea_1_1astro_1_1Constellation.md) _._
* **class** [**astrea::astro::Cylindrical**](classastrea_1_1astro_1_1Cylindrical.md) _Class representing a_ [_**Cylindrical**_](classastrea_1_1astro_1_1Cylindrical.md) _state vector in astrodynamics._
* **class** [**astrea::astro::Date**](classastrea_1_1astro_1_1Date.md) _Class representing a date in the astrea astro library._ 
* **class** [**astrea::astro::Deorbit**](classastrea_1_1astro_1_1Deorbit.md) _A class representing a deorbit_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class is used as a placeholder for Events that do not have a defined state or mass._
* **struct** [**astrea::astro::DcmInterface**](structastrea_1_1astro_1_1DcmInterface.md) _Class representing a 3x3 matrix, used for matrices and their rates/accelerations._ 
* **class** [**astrea::astro::Equinoctial**](classastrea_1_1astro_1_1Equinoctial.md) _The_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _class represents the equinoctial orbital elements._
* **class** [**astrea::astro::EquinoctialPartial**](classastrea_1_1astro_1_1EquinoctialPartial.md) _Class representing a partial derivative of an_ [_**Equinoctial**_](classastrea_1_1astro_1_1Equinoctial.md) _state vector._
* **class** [**astrea::astro::EulerAngles**](classastrea_1_1astro_1_1EulerAngles.md) _Class representing a sequence of angles (either Euler or Tait-Bryan) for attitude transformations between frames._ 
* **class** [**astrea::astro::Event**](classastrea_1_1astro_1_1Event.md) _A class representing a_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class serves as a base for user-defined Events and provides a common interface._
* **class** [**astrea::astro::EventDetector**](classastrea_1_1astro_1_1EventDetector.md) _A class for detecting events in the astrea astro platform._ 
* **class** [**astrea::astro::ForceModel**](classastrea_1_1astro_1_1ForceModel.md) _Class to manage multiple force models and compute the total force on a vehicle._ 
* **class** [**astrea::astro::Geocentric**](classastrea_1_1astro_1_1Geocentric.md) _Class representing a_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _state vector in astrodynamics._
* **class** [**astrea::astro::Geodetic**](classastrea_1_1astro_1_1Geodetic.md) _Class representing a_ [_**Geodetic**_](classastrea_1_1astro_1_1Geodetic.md) _state vector in astrodynamics._
* **class** [**astrea::astro::HarrisPriesterAtmosphere**](classastrea_1_1astro_1_1HarrisPriesterAtmosphere.md) _The Harris-Priester atmospheric model for Earth._ 
* **class** [**astrea::astro::ImpulsiveBurn**](classastrea_1_1astro_1_1ImpulsiveBurn.md) _A class representing an impulsive burn_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _. It triggers when the true anomaly wraps around (i.e. at perigee), and applies the total impulsive delta-v from all thrusters to the vehicle in the velocity direction._
* **class** [**astrea::astro::InertiaTensor**](classastrea_1_1astro_1_1InertiaTensor.md) _A class representing an inertia matrix in the astrea astro platform._ 
* **class** [**astrea::astro::Integrator**](classastrea_1_1astro_1_1Integrator.md) [_**Integrator**_](classastrea_1_1astro_1_1Integrator.md) _class for numerical propagation of orbital mechanics problems._
* **class** [**astrea::astro::Interval**](classastrea_1_1astro_1_1Interval.md) _Represents a time interval with a start and end time._ 
* **class** [**astrea::astro::JacchiaRobertsAtmosphere**](classastrea_1_1astro_1_1JacchiaRobertsAtmosphere.md) _The Jaccia-Roberts atmospheric model for Earth._ 
* **class** [**astrea::astro::Keplerian**](classastrea_1_1astro_1_1Keplerian.md) _The_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _class represents the_[_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _orbital elements._
* **class** [**astrea::astro::KeplerianPartial**](classastrea_1_1astro_1_1KeplerianPartial.md) _Class representing a partial derivative of a_ [_**Keplerian**_](classastrea_1_1astro_1_1Keplerian.md) _state vector._
* **class** [**astrea::astro::LambertSolver**](classastrea_1_1astro_1_1LambertSolver.md) _Class for solving Lambert's problem._ 
* **class** [**astrea::astro::LegendreCache**](classastrea_1_1astro_1_1LegendreCache.md) _Class to cache Legendre polynomial coefficients for a given celestial_ _body_ _, degree, and order._
* **class** [**astrea::astro::Nrlmsise00Atmosphere**](classastrea_1_1astro_1_1Nrlmsise00Atmosphere.md) 
* **class** [**astrea::astro::NullEvent**](classastrea_1_1astro_1_1NullEvent.md) _A class representing a null_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class is used as a placeholder for Events that do not have a defined state or mass._
* **class** [**astrea::astro::NullVehicle**](classastrea_1_1astro_1_1NullVehicle.md) _A class representing a null vehicle in the astrea astro platform. This class is used as a placeholder for vehicles that do not have a defined state or mass._ 
* **class** [**astrea::astro::OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) _Class representing partial derivatives of orbital elements._ 
* **class** [**astrea::astro::OrbitalElements**](classastrea_1_1astro_1_1OrbitalElements.md) _Class representing a set of orbital elements._ 
* **class** [**astrea::astro::Payload**](classastrea_1_1astro_1_1Payload.md) [_**Payload**_](classastrea_1_1astro_1_1Payload.md) _class representing a payload on a platform._
* **class** [**astrea::astro::PayloadParameters**](classastrea_1_1astro_1_1PayloadParameters.md) _Class for storing and managing payload parameters._     
    * **class** [**astrea::astro::ThrusterParameters**](classastrea_1_1astro_1_1ThrusterParameters.md) _Class for storing and managing thruster parameters._ 
* **class** [**astrea::astro::PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) _The_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _class represents a platform that can have payloads attached to it. It provides methods to attach payloads and retrieve the list of attached payloads._
* **class** [**astrea::astro::Plane**](classastrea_1_1astro_1_1Plane.md) _A_ [_**Plane**_](classastrea_1_1astro_1_1Plane.md) _is a collection of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _that share the same orbital elements._
* **class** [**astrea::astro::Quaternion**](classastrea_1_1astro_1_1Quaternion.md) _Class representing a quaternion for attitude rotations between frames._ 
* **class** [**astrea::astro::QuaternionPartial**](classastrea_1_1astro_1_1QuaternionPartial.md) _Class representing the partial derivative of a quaternion with respect to time, used for integration._ 
* **class** [**astrea::astro::Schedule**](classastrea_1_1astro_1_1Schedule.md) _A class representing a_ [_**Schedule**_](classastrea_1_1astro_1_1Schedule.md) _in the astrea astro library. The_[_**Schedule**_](classastrea_1_1astro_1_1Schedule.md) _is responsible for scheduling and managing Events that are set to trigger at specific Dates during propagation._
* **class** [**astrea::astro::Shell**](classastrea_1_1astro_1_1Shell.md) _A_ [_**Shell**_](classastrea_1_1astro_1_1Shell.md) _is a collection of planes, each containing a set of_[_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _. It is used to represent sub-constellations of satellites in orbit._
* **class** [**astrea::astro::Shell::sat\_iterator**](classastrea_1_1astro_1_1Shell_1_1sat__iterator.md) _Iterator for iterating over all_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _in the_[_**Shell**_](classastrea_1_1astro_1_1Shell.md) _._
* **class** [**astrea::astro::SpaceWeatherData**](classastrea_1_1astro_1_1SpaceWeatherData.md) _Class to hold space weather data read from a file._ 
* **class** [**astrea::astro::SpaceWeatherProvider**](classastrea_1_1astro_1_1SpaceWeatherProvider.md) _Lightweight provider that shares an immutable space weather data snapshot. Using this layer of abstraction for now to enable data hot-swapping in the future if needed._ 
* **class** [**astrea::astro::Spherical**](classastrea_1_1astro_1_1Spherical.md) _Class representing a_ [_**Spherical**_](classastrea_1_1astro_1_1Spherical.md) _state vector in astrodynamics._
* **class** [**astrea::astro::State**](classastrea_1_1astro_1_1State.md) _Class representing the state of an astronomical object. This class encapsulates the orbital elements, epoch, and the astrodynamics system that the state belongs to. It also optionally includes the attitude of the object as a quaternion._ 
* **class** [**astrea::astro::StateHistory**](classastrea_1_1astro_1_1StateHistory.md) _Class to manage the history of states for an object over date._ 
* **class** [**astrea::astro::StatePartial**](classastrea_1_1astro_1_1StatePartial.md) 
* **class** [**astrea::astro::StateTransitionMatrix**](classastrea_1_1astro_1_1StateTransitionMatrix.md) 
* **class** [**astrea::astro::TurnThrustersOff**](classastrea_1_1astro_1_1TurnThrustersOff.md) _A class representing a_ [_**TurnThrustersOff**_](classastrea_1_1astro_1_1TurnThrustersOff.md) __[_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class is used as a placeholder for Events that do not have a defined state or mass._
* **class** [**astrea::astro::TurnThrustersOn**](classastrea_1_1astro_1_1TurnThrustersOn.md) _A class representing a_ [_**TurnThrustersOn**_](classastrea_1_1astro_1_1TurnThrustersOn.md) __[_**Event**_](classastrea_1_1astro_1_1Event.md) _in the astrea astro platform. This class is used as a placeholder for Events that do not have a defined state or mass._
* **class** [**astrea::astro::TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) _Class representing the two-line element (TLE) format for orbital data._ 
* **class** [**astrea::astro::Vehicle**](classastrea_1_1astro_1_1Vehicle.md) _A class representing a vehicle in the astrea astro platform. This class serves as a base for user-defined vehicles and provides a common interface._ 
* **struct** [**astrea::astro::detail::OriginBase**](structastrea_1_1astro_1_1detail_1_1OriginBase.md)     
    * **struct** [**astrea::astro::Origin&lt; \_name\_ &gt;**](structastrea_1_1astro_1_1Origin_3_01__name___01_4.md)     
        * **struct** [**astrea::astro::Barycenter&lt; \_name\_ &gt;**](structastrea_1_1astro_1_1Barycenter_3_01__name___01_4.md) _No parent, no members._ 
    * **struct** [**astrea::astro::Origin&lt; \_name\_, \_parent\_ &gt;**](structastrea_1_1astro_1_1Origin_3_01__name___00_01__parent___01_4.md)     
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
        * **struct** [**astrea::astro::Barycenter&lt; \_name\_, \_parent\_ &gt;**](structastrea_1_1astro_1_1Barycenter_3_01__name___00_01__parent___01_4.md) _With parent, no members._ 
        * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
* **struct** [**astrea::astro::detail::CelestialBodyBase**](structastrea_1_1astro_1_1detail_1_1CelestialBodyBase.md)     
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
    * **struct** [**astrea::astro::CelestialBody**](structastrea_1_1astro_1_1CelestialBody.md) [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _class represents a celestial body in an astrodynamics system._
* **class** [**astrea::astro::planets::Nrlmsise00Atmosphere**](classastrea_1_1astro_1_1planets_1_1Nrlmsise00Atmosphere.md) _The NRLMSISE-00 atmospheric model for_ [_**Earth**_](structastrea_1_1astro_1_1planets_1_1Earth.md) _._
* **class** [**astrea::astro::planets::Output**](classastrea_1_1astro_1_1planets_1_1Output.md) 
* **struct** [**astrea::astro::Axis**](structastrea_1_1astro_1_1Axis.md) 
* **struct** [**astrea::astro::detail::AxisBase**](structastrea_1_1astro_1_1detail_1_1AxisBase.md)     
    * **struct** [**astrea::astro::Axis&lt; \_name\_ &gt;**](structastrea_1_1astro_1_1Axis_3_01__name___01_4.md) 
    * **struct** [**astrea::astro::Axis&lt; \_name\_, \_parent\_ &gt;**](structastrea_1_1astro_1_1Axis_3_01__name___00_01__parent___01_4.md) 
* **struct** [**astrea::astro::BadConversionRequest**](structastrea_1_1astro_1_1BadConversionRequest.md) 
* **struct** [**astrea::astro::Barycenter**](structastrea_1_1astro_1_1Barycenter.md) 
* **struct** [**astrea::astro::detail::BarycenterBase**](structastrea_1_1astro_1_1detail_1_1BarycenterBase.md)     
    * **struct** [**astrea::astro::Barycenter&lt; \_name\_ &gt;**](structastrea_1_1astro_1_1Barycenter_3_01__name___01_4.md) _No parent, no members._ 
    * **struct** [**astrea::astro::Barycenter&lt; \_name\_, \_parent\_ &gt;**](structastrea_1_1astro_1_1Barycenter_3_01__name___00_01__parent___01_4.md) _With parent, no members._ 
* **struct** [**astrea::astro::BarycentricCoordinateTimeClock**](structastrea_1_1astro_1_1BarycentricCoordinateTimeClock.md) _A clock implementation for Barycentric Coordinate Time (TCB)._ 
* **struct** [**astrea::astro::BarycentricDynamicalTimeClock**](structastrea_1_1astro_1_1BarycentricDynamicalTimeClock.md) _A clock implementation for Barycentric Dynamical Time (TDB)._ 
* **struct** [**astrea::astro::Frame**](structastrea_1_1astro_1_1Frame.md)     
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
* **struct** [**astrea::astro::detail::BodyFixedFrameBase**](structastrea_1_1astro_1_1detail_1_1BodyFixedFrameBase.md)     
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
    * **struct** [**astrea::astro::BodyFixedFrame**](structastrea_1_1astro_1_1BodyFixedFrame.md) _Body-fixed frame defined by a celestial body and its reference axes. The origin is at the center of mass of the body, and the axes are fixed to the body._ 
* **struct** [**astrea::astro::CartesianVector**](structastrea_1_1astro_1_1CartesianVector.md) _Class representing a 3D vector in_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _coordinates._
* **struct** [**astrea::astro::CelestialBodyParameters**](structastrea_1_1astro_1_1CelestialBodyParameters.md) _Structure to hold the parameters of a celestial body._ 
* **struct** [**astrea::astro::CelestialBodyTypePack**](structastrea_1_1astro_1_1CelestialBodyTypePack.md) _Type-list used to attach member bodies to a_ [_**Barycenter**_](structastrea_1_1astro_1_1Barycenter.md) _._
* **struct** [**astrea::astro::DynamicFrame**](structastrea_1_1astro_1_1DynamicFrame.md) _Base class for all dynamic state/frames._ 
* **struct** [**astrea::astro::Origin**](structastrea_1_1astro_1_1Origin.md) 
* **struct** [**astrea::astro::ExtraRegisteredFrames**](structastrea_1_1astro_1_1ExtraRegisteredFrames.md) _Trait that users specialize to register additional_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _frames._
* **struct** [**astrea::astro::FixedOffsetAxis::Misalignment**](structastrea_1_1astro_1_1FixedOffsetAxis_1_1Misalignment.md) 
* **struct** [**astrea::astro::FixedOffsetFrame**](structastrea_1_1astro_1_1FixedOffsetFrame.md) _Class representing a fixed offset frame, which is defined by a fixed spatial and/or angular offset from a parent frame._ 
* **struct** [**astrea::astro::FixedOffsetOrigin::Offset**](structastrea_1_1astro_1_1FixedOffsetOrigin_1_1Offset.md) 
* **struct** [**astrea::astro::detail::FrameBase**](structastrea_1_1astro_1_1detail_1_1FrameBase.md) _Empty base class for all frames in astrea. This allows us to use std::derived\_from to check if a type is a frame._     
    * **struct** [**astrea::astro::Frame&lt; \_name\_, \_origin\_, \_axis\_ &gt;**](structastrea_1_1astro_1_1Frame_3_01__name___00_01__origin___00_01__axis___01_4.md) [_**Frame**_](structastrea_1_1astro_1_1Frame.md) _with name, origin, and axis (no parent)._
    * **struct** [**astrea::astro::Frame&lt; \_name\_, \_origin\_, \_axis\_, \_parent\_ &gt;**](structastrea_1_1astro_1_1Frame_3_01__name___00_01__origin___00_01__axis___00_01__parent___01_4.md) [_**Frame**_](structastrea_1_1astro_1_1Frame.md) _with name, origin, axis, and parent._
* **struct** [**astrea::astro::GeneralPerturbations**](structastrea_1_1astro_1_1GeneralPerturbations.md) [_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _structure representing a Ground Position (GP) object from SpaceTrack._
* **struct** [**astrea::astro::GeocentricCoordinateTimeClock**](structastrea_1_1astro_1_1GeocentricCoordinateTimeClock.md) _A clock implementation for_ [_**Geocentric**_](classastrea_1_1astro_1_1Geocentric.md) _Coordinate Time (TCG)._
* **struct** [**astrea::astro::IntegratorSettings**](structastrea_1_1astro_1_1IntegratorSettings.md) 
* **struct** [**astrea::astro::JplEphemerisTable**](structastrea_1_1astro_1_1JplEphemerisTable.md) _Base class for any JPL_ [_**CelestialBody**_](structastrea_1_1astro_1_1CelestialBody.md) _table._
* **struct** [**astrea::astro::JulianDateClock**](structastrea_1_1astro_1_1JulianDateClock.md) _A clock implementation for Julian Dates._ 
* **struct** [**astrea::astro::LambertSolver::Solution**](structastrea_1_1astro_1_1LambertSolver_1_1Solution.md) _Result structure for optimal Lambert solutions._ 
* **struct** [**astrea::astro::Perturbation**](structastrea_1_1astro_1_1Perturbation.md) _Struct to hold the results of a perturbation force computation, including both acceleration and torque._ 
* **struct** [**astrea::astro::SolarFluxData**](structastrea_1_1astro_1_1SolarFluxData.md) _Struct to hold solar flux data._ 
* **struct** [**astrea::astro::SpaceWeatherParameters**](structastrea_1_1astro_1_1SpaceWeatherParameters.md) _Struct to hold space weather parameters for a specific date._ 
* **struct** [**astrea::astro::StepWatcher**](structastrea_1_1astro_1_1StepWatcher.md) _Function wrapper class for watching the state of the integrator at each step. This can be used for plotting or logging the state during propagation._ 
* **struct** [**astrea::astro::detail::SynodicFrameBase**](structastrea_1_1astro_1_1detail_1_1SynodicFrameBase.md)     
    * **struct** [**astrea::astro::SynodicFrame**](structastrea_1_1astro_1_1SynodicFrame.md) _Synodic frame defined by the line connecting two celestial bodies and the plane of motion of the secondary around the primary._ 
    * **struct** [**astrea::astro::SynodicFrame**](structastrea_1_1astro_1_1SynodicFrame.md) _Synodic frame defined by the line connecting two celestial bodies and the plane of motion of the secondary around the primary._ 
    * **struct** [**astrea::astro::SynodicFrame**](structastrea_1_1astro_1_1SynodicFrame.md) _Synodic frame defined by the line connecting two celestial bodies and the plane of motion of the secondary around the primary._ 
    * **struct** [**astrea::astro::SynodicFrame**](structastrea_1_1astro_1_1SynodicFrame.md) _Synodic frame defined by the line connecting two celestial bodies and the plane of motion of the secondary around the primary._ 
    * **struct** [**astrea::astro::SynodicFrame**](structastrea_1_1astro_1_1SynodicFrame.md) _Synodic frame defined by the line connecting two celestial bodies and the plane of motion of the secondary around the primary._ 
    * **struct** [**astrea::astro::SynodicFrame**](structastrea_1_1astro_1_1SynodicFrame.md) _Synodic frame defined by the line connecting two celestial bodies and the plane of motion of the secondary around the primary._ 
    * **struct** [**astrea::astro::SynodicFrame**](structastrea_1_1astro_1_1SynodicFrame.md) _Synodic frame defined by the line connecting two celestial bodies and the plane of motion of the secondary around the primary._ 
    * **struct** [**astrea::astro::SynodicFrame**](structastrea_1_1astro_1_1SynodicFrame.md) _Synodic frame defined by the line connecting two celestial bodies and the plane of motion of the secondary around the primary._ 
    * **struct** [**astrea::astro::SynodicFrame**](structastrea_1_1astro_1_1SynodicFrame.md) _Synodic frame defined by the line connecting two celestial bodies and the plane of motion of the secondary around the primary._ 
    * **struct** [**astrea::astro::SynodicFrame**](structastrea_1_1astro_1_1SynodicFrame.md) _Synodic frame defined by the line connecting two celestial bodies and the plane of motion of the secondary around the primary._ 
* **struct** [**astrea::astro::TerrestrialTimeClock**](structastrea_1_1astro_1_1TerrestrialTimeClock.md) _A clock implementation for Terrestrial Time (TT)._ 
* **struct** [**astrea::astro::detail::EventInnerBase**](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md) _Pure virtual base class for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _inner implementations._    
    * **struct** [**astrea::astro::detail::EventInner**](structastrea_1_1astro_1_1detail_1_1EventInner.md) _A template class for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _inner implementations._
* **struct** [**astrea::astro::detail::VehicleInnerBase**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md) _Pure virtual base class for vehicle inner implementations._     
    * **struct** [**astrea::astro::detail::VehicleInner**](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) _A template class for vehicle inner implementations._ 
* **struct** [**astrea::astro::detail::apply\_nttp\_template**](structastrea_1_1astro_1_1detail_1_1apply__nttp__template.md) 
* **struct** [**astrea::astro::detail::apply\_nttp\_template&lt; T, std::tuple&lt; Frames... &gt; &gt;**](structastrea_1_1astro_1_1detail_1_1apply__nttp__template_3_01T_00_01std_1_1tuple_3_01Frames_8_8_8_01_4_01_4.md) 
* **struct** [**astrea::astro::detail::apply\_template**](structastrea_1_1astro_1_1detail_1_1apply__template.md) 
* **struct** [**astrea::astro::detail::apply\_template&lt; T, std::tuple&lt; Frames... &gt; &gt;**](structastrea_1_1astro_1_1detail_1_1apply__template_3_01T_00_01std_1_1tuple_3_01Frames_8_8_8_01_4_01_4.md) 
* **struct** [**astrea::astro::detail::multi\_tuple\_cat**](structastrea_1_1astro_1_1detail_1_1multi__tuple__cat.md) 
* **struct** [**astrea::astro::detail::multi\_tuple\_cat&lt; First, Rest... &gt;**](structastrea_1_1astro_1_1detail_1_1multi__tuple__cat_3_01First_00_01Rest_8_8_8_01_4.md) 
* **struct** [**astrea::astro::detail::multi\_tuple\_cat&lt; Only &gt;**](structastrea_1_1astro_1_1detail_1_1multi__tuple__cat_3_01Only_01_4.md) 
* **struct** [**astrea::astro::detail::multi\_tuple\_cat&lt;&gt;**](structastrea_1_1astro_1_1detail_1_1multi__tuple__cat_3_4.md) 
* **struct** [**astrea::astro::detail::tuple\_cat\_types**](structastrea_1_1astro_1_1detail_1_1tuple__cat__types.md) 
* **struct** [**astrea::astro::detail::tuple\_cat\_types&lt; std::tuple&lt; As... &gt;, std::tuple&lt; Bs... &gt; &gt;**](structastrea_1_1astro_1_1detail_1_1tuple__cat__types_3_01std_1_1tuple_3_01As_8_8_8_01_4_00_01std8cf8a2c8692dfec60c2615039d60391f.md) 
* **struct** [**astrea::astro::detail::tuple\_to\_variant**](structastrea_1_1astro_1_1detail_1_1tuple__to__variant.md) 
* **struct** [**astrea::astro::detail::tuple\_to\_variant&lt; std::tuple&lt; Ts... &gt;, Extra... &gt;**](structastrea_1_1astro_1_1detail_1_1tuple__to__variant_3_01std_1_1tuple_3_01Ts_8_8_8_01_4_00_01Extra_8_8_8_01_4.md) 
* **struct** [**astrea::astro::planets::BatesProfileParams**](structastrea_1_1astro_1_1planets_1_1BatesProfileParams.md) 
* **struct** [**astrea::astro::planets::SpeciesModelParams**](structastrea_1_1astro_1_1planets_1_1SpeciesModelParams.md) _Per-species empirical parameters for NRLMSISE-00 diffusive and mixed-region density calculations._ 
* **struct** [**astrea::astro::planets::Switch**](structastrea_1_1astro_1_1planets_1_1Switch.md) 
* **struct** [**astrea::astro::EventDetector::EventTracker**](structastrea_1_1astro_1_1EventDetector_1_1EventTracker.md) _A struct for tracking events._ 
* **struct** [**mp\_units::quantity\_point\_like\_traits&lt; astrea::astro::Date &gt;**](structmp__units_1_1quantity__point__like__traits_3_01astrea_1_1astro_1_1Date_01_4.md) _Specialization of mp\_units::quantity\_point\_like\_traits for the Date class._ 
* **struct** [**std::hash&lt; std::tuple&lt; TT... &gt; &gt;**](structstd_1_1hash_3_01std_1_1tuple_3_01TT_8_8_8_01_4_01_4.md) 
* **class** **std::false_type**    
    * **struct** [**astrea::astro::is\_cartesian\_vector**](structastrea_1_1astro_1_1is__cartesian__vector.md) 
* **class** **std::true_type**    
    * **struct** [**astrea::astro::is\_cartesian\_vector&lt; CartesianVector&lt; Value\_T, frame &gt; &gt;**](structastrea_1_1astro_1_1is__cartesian__vector_3_01CartesianVector_3_01Value__T_00_01frame_01_4_01_4.md) 

