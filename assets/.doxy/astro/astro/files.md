
# File List

Here is a list of all files with brief descriptions:


* **dir** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md)     
    * **dir** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md)     
        * **dir** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md)     
            * **dir** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md)     
                * **file** [**CartesianVector.hpp**](CartesianVector_8hpp.md) _This file defines the CartesianVector class, which represents a 3D vector in Cartesian coordinates._     
                * **file** [**Frame.hpp**](Frame_8hpp.md) _Definition for a Frame in astrea._     
                * **file** [**FrameReference.cpp**](FrameReference_8cpp.md)     
                * **file** [**FrameReference.hpp**](FrameReference_8hpp.md) _Header file for the FrameReference class in the astro namespace._     
                * **dir** [**instances**](dir_a85615e9ad779999123e94bfb15c8545.md)     
                    * **file** [**EastNorthUp.hpp**](EastNorthUp_8hpp.md) _Header file for the EastNorthUp class in the astro namespace._     
                    * **file** [**LocalHorizontalLocalVertical.hpp**](LocalHorizontalLocalVertical_8hpp.md) _Header file for the LocalHorizontalLocalVertical class in the astro namespace._     
                    * **file** [**RadialInTrackCrossTrack.hpp**](RadialInTrackCrossTrack_8hpp.md) _Header file for the RadialInTrackCrossTrack class in the astro namespace._     
                    * **file** [**VelocityNormalBinormal.hpp**](VelocityNormalBinormal_8hpp.md) _Header file for the VelocityNormalBinormal class in the astro namespace._     
                    * **file** [**body\_centered\_inertial\_frames.hpp**](body__centered__inertial__frames_8hpp.md) _Header file for all (most? common?) body-centered inertial frames._     
                    * **file** [**body\_fixed\_frames.hpp**](body__fixed__frames_8hpp.md) _Header file for body-fixed frames. Just ECEF right now._     
                    * **file** [**defined\_rotations.hpp**](defined__rotations_8hpp.md) _Header file for defined rotations between common frames._     
                * **dir** [**types**](dir_6f58486cdc039e35eca8cf5d1aadadc3.md)     
                    * **file** [**BodyFixedFrame.hpp**](BodyFixedFrame_8hpp.md) _Header file for the BodyFixedFrame class in the astro namespace._     
                    * **file** [**DirectionCosineMatrix.hpp**](DirectionCosineMatrix_8hpp.md) _Header file for the DirectionCosineMatrix class in the astro namespace._     
                    * **file** [**DynamicFrame.hpp**](DynamicFrame_8hpp.md) _Header file for the DynamicFrame class in the astro namespace._     
                    * **file** [**InertialFrame.hpp**](InertialFrame_8hpp.md) _Header file for the InertialFrame class in the astro namespace._     
                * **file** [**dynamic\_frames.hpp**](dynamic__frames_8hpp.md) _Header file for dynamic frames._ 
                * **file** [**frame\_concepts.hpp**](frame__concepts_8hpp.md) _Definitions for frame concepts and other compile-time utilities._     
                * **file** [**frames.hpp**](frames_8hpp.md) 
                * **file** [**transformations.hpp**](transformations_8hpp.md) _Definitions for frame transformations and other utilities._     
            * **dir** [**platforms**](dir_2552b27872b33d254ad75ac21654b66a.md)     
                * **file** [**Payload.hpp**](Payload_8hpp.md) _Payload class definition for astrea access platform._     
                * **file** [**PayloadPlatform.hpp**](PayloadPlatform_8hpp.md) _This file defines the PayloadPlatform class, which represents a platform that can have payloads attached to it._     
                * **file** [**Vehicle.cpp**](Vehicle_8cpp.md)     
                * **file** [**Vehicle.hpp**](Vehicle_8hpp.md) _A class representing a vehicle in the astrea astro platform._     
                * **dir** [**space**](dir_4e8e97ad8c5ab106f4208fffe0057899.md)     
                    * **file** [**Constellation.hpp**](Constellation_8hpp.md)     
                    * **file** [**Plane.hpp**](Plane_8hpp.md)     
                    * **file** [**Shell.hpp**](Shell_8hpp.md)     
                * **dir** [**thrusters**](dir_c4651317ac77989e0950f932d02daf86.md)     
                    * **file** [**Thruster.cpp**](Thruster_8cpp.md)     
                    * **file** [**Thruster.hpp**](Thruster_8hpp.md) _Thruster class definition for astrea access platform._     
                * **dir** [**vehicles**](dir_6209fec1d31cfd277683fcd634983a45.md)     
                    * **file** [**NullVehicle.cpp**](NullVehicle_8cpp.md)     
                    * **file** [**NullVehicle.hpp**](NullVehicle_8hpp.md) _A class representing a null vehicle in the astrea astro platform._     
                    * **file** [**Spacecraft.cpp**](Spacecraft_8cpp.md)     
                    * **file** [**Spacecraft.hpp**](Spacecraft_8hpp.md) _A class representing a spacecraft in the astrea astro platform._     
            * **dir** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md)     
                * **dir** [**analytic**](dir_0032edd3690e3836975e7dd677ed5fa8.md)     
                    * **file** [**LambertSolver.cpp**](LambertSolver_8cpp.md)     
                    * **file** [**LambertSolver.hpp**](LambertSolver_8hpp.md) _This file defines the LambertSolver class, which provides methods for solving Lambert's problem._     
                * **dir** [**equations\_of\_motion**](dir_0a1395a4617b025941a2198784f446c5.md)     
                    * **file** [**CowellsMethod.cpp**](CowellsMethod_8cpp.md)     
                    * **file** [**CowellsMethod.hpp**](CowellsMethod_8hpp.md) _Header file for the Cowell's Method equations of motion class._     
                    * **file** [**EquationsOfMotion.hpp**](EquationsOfMotion_8hpp.md) _Header file for the base class of equations of motion._     
                    * **file** [**EquinoctialVop.cpp**](EquinoctialVop_8cpp.md)     
                    * **file** [**EquinoctialVop.hpp**](EquinoctialVop_8hpp.md) _Header file for the Equinoctial VOP equations of motion class._     
                    * **file** [**J2MeanVop.cpp**](J2MeanVop_8cpp.md)     
                    * **file** [**J2MeanVop.hpp**](J2MeanVop_8hpp.md) _Header file for the J2 Mean VOP equations of motion class._     
                    * **file** [**KeplerianVop.cpp**](KeplerianVop_8cpp.md)     
                    * **file** [**KeplerianVop.hpp**](KeplerianVop_8hpp.md) _Header file for the Keplerian VOP equations of motion class._     
                    * **file** [**TwoBody.cpp**](TwoBody_8cpp.md)     
                    * **file** [**TwoBody.hpp**](TwoBody_8hpp.md) _Header file for the Two Body equations of motion class._     
                    * **dir** [**state\_transition\_matrix**](dir_7a22b679029b3e67ce8dbba97ffb681f.md)     
                        * **file** [**StateTransitionMatrix.cpp**](StateTransitionMatrix_8cpp.md)     
                        * **file** [**StateTransitionMatrix.hpp**](StateTransitionMatrix_8hpp.md) _Header file for the StateTransitionMatrix class._     
                * **dir** [**event\_detection**](dir_283e5a6c8e70b5075f630fb83b6454d7.md)     
                    * **file** [**Event.cpp**](Event_8cpp.md)     
                    * **file** [**Event.hpp**](Event_8hpp.md) _A class representing an Event in the astrea astro library._     
                    * **file** [**EventDetector.cpp**](EventDetector_8cpp.md)     
                    * **file** [**EventDetector.hpp**](EventDetector_8hpp.md) _A class for detecting events in the astrea astro platform._     
                    * **dir** [**events**](dir_ffe0d0558a41319d577ebe8d35f3c9da.md)     
                        * **file** [**ImpulsiveBurn.cpp**](ImpulsiveBurn_8cpp.md)     
                        * **file** [**ImpulsiveBurn.hpp**](ImpulsiveBurn_8hpp.md) _A class representing a null Event in the astrea astro platform._     
                        * **file** [**NullEvent.hpp**](NullEvent_8hpp.md) _A class representing a null Event in the astrea astro platform._     
                * **dir** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md)     
                    * **file** [**AtmosphericForce.cpp**](AtmosphericForce_8cpp.md)     
                    * **file** [**AtmosphericForce.hpp**](AtmosphericForce_8hpp.md) _Header file for the AtmosphericForce class, which computes the atmospheric force on a vehicle._     
                    * **file** [**Force.hpp**](Force_8hpp.md) _Header file for the Force class, which defines the interface for force models in astrodynamics._     
                    * **file** [**ForceModel.cpp**](ForceModel_8cpp.md)     
                    * **file** [**ForceModel.hpp**](ForceModel_8hpp.md) _Header file for the ForceModel class, which manages multiple force models and computes the total force on a vehicle._     
                    * **file** [**NBodyForce.cpp**](NBodyForce_8cpp.md)     
                    * **file** [**NBodyForce.hpp**](NBodyForce_8hpp.md)     
                    * **file** [**OblatenessForce.cpp**](OblatenessForce_8cpp.md)     
                    * **file** [**OblatenessForce.hpp**](OblatenessForce_8hpp.md) _Header file for the NBodyForce class, which computes the gravitational force due to multiple celestial bodies._     
                    * **file** [**SolarRadiationPressure.cpp**](SolarRadiationPressure_8cpp.md)     
                    * **file** [**SolarRadiationPressure.hpp**](SolarRadiationPressure_8hpp.md)     
                * **dir** [**numerical**](dir_89452d20321c19f5539a283cd906a79c.md)     
                    * **file** [**Integrator.cpp**](Integrator_8cpp.md)     
                    * **file** [**Integrator.hpp**](Integrator_8hpp.md) _Numerical integrator for orbital mechanics propagation._     
                    * **file** [**butcher\_tableau.hpp**](butcher__tableau_8hpp.md) _Constants for Runge-Kutta methods used in numerical integration._     
            * **dir** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md)     
                * **file** [**State.cpp**](State_8cpp.md)     
                * **file** [**State.hpp**](State_8hpp.md) _Class representing the state of an astronomical object._     
                * **file** [**StateHistory.cpp**](StateHistory_8cpp.md)     
                * **file** [**StateHistory.hpp**](StateHistory_8hpp.md) _Header file for StateHistory class._     
                * **dir** [**angular\_elements**](dir_8f2f7499654791f4fc4240f01fb9baf6.md)     
                    * **file** [**AngularElements.hpp**](AngularElements_8hpp.md) 
                    * **file** [**angular\_elements.hpp**](angular__elements_8hpp.md) _Utility header to include all angular element headers._ 
                    * **dir** [**instances**](dir_1a50007be9f0149ab221abcea88ff37f.md)     
                        * **file** [**Cylindrical.cpp**](Cylindrical_8cpp.md)     
                        * **file** [**Cylindrical.hpp**](Cylindrical_8hpp.md) _This file defines the Cylindrical class and its associated methods._     
                        * **file** [**Geocentric.cpp**](Geocentric_8cpp.md)     
                        * **file** [**Geocentric.hpp**](Geocentric_8hpp.md) _This file defines the Geocentric class and its associated methods._     
                        * **file** [**Geodetic.cpp**](Geodetic_8cpp.md)     
                        * **file** [**Geodetic.hpp**](Geodetic_8hpp.md) _This file defines the Geodetic class and its associated methods._     
                        * **file** [**Spherical.cpp**](Spherical_8cpp.md)     
                        * **file** [**Spherical.hpp**](Spherical_8hpp.md) _This file defines the Spherical class and its associated methods._     
                * **dir** [**orbital\_data\_formats**](dir_dce17fbadb9e43f0864b0608daddb5e0.md)     
                    * **dir** [**instances**](dir_8b2b76eceb189c78e8c8535df8f613d6.md)     
                        * **file** [**GeneralPerturbations.cpp**](GeneralPerturbations_8cpp.md)     
                        * **file** [**GeneralPerturbations.hpp**](GeneralPerturbations_8hpp.md) _GeneralPerturbations data structure for the astro module._     
                        * **file** [**TwoLineElements.cpp**](TwoLineElements_8cpp.md)     
                        * **file** [**TwoLineElements.hpp**](TwoLineElements_8hpp.md) _Header file for the TwoLineElements class._     
                    * **file** [**orbital\_data\_formats.hpp**](orbital__data__formats_8hpp.md) _Utility header to include all orbital data format headers._ 
                * **dir** [**orbital\_elements**](dir_6eb62f1e639545772a8b9a71f7b1d0b7.md)     
                    * **file** [**OrbitalElements.cpp**](OrbitalElements_8cpp.md)     
                    * **file** [**OrbitalElements.hpp**](OrbitalElements_8hpp.md) _This file defines the OrbitalElements class and its associated methods._     
                    * **dir** [**instances**](dir_2296e922a578ce2ef4a64c83384e553c.md)     
                        * **file** [**Cartesian.cpp**](Cartesian_8cpp.md)     
                        * **file** [**Cartesian.hpp**](Cartesian_8hpp.md) _This file defines the Cartesian class and its associated methods._     
                        * **file** [**Equinoctial.cpp**](Equinoctial_8cpp.md)     
                        * **file** [**Equinoctial.hpp**](Equinoctial_8hpp.md) _This file defines the Equinoctial class and its associated methods._     
                        * **file** [**Keplerian.cpp**](Keplerian_8cpp.md)     
                        * **file** [**Keplerian.hpp**](Keplerian_8hpp.md) _This file defines the Keplerian class and its associated methods._     
                    * **file** [**orbital\_elements.hpp**](orbital__elements_8hpp.md) _Utility header to include all orbital element headers._ 
            * **dir** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md)     
                * **file** [**AstrodynamicsSystem.cpp**](AstrodynamicsSystem_8cpp.md)     
                * **file** [**AstrodynamicsSystem.hpp**](AstrodynamicsSystem_8hpp.md) _Header file for the AstrodynamicsSystem class, which manages celestial bodies and their interactions._     
                * **file** [**CelestialBody.cpp**](CelestialBody_8cpp.md)     
                * **file** [**CelestialBody.hpp**](CelestialBody_8hpp.md) _Header file for the CelestialBody class, which represents a celestial body in an astrodynamics system._     
                * **file** [**CelestialBodyParameters.hpp**](CelestialBodyParameters_8hpp.md) _Header file for the CelestialBodyParameters class, which represents planetary data in an astrodynamics system._     
                * **dir** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md)     
                    * **file** [**JplEphemerisTable.cpp**](JplEphemerisTable_8cpp.md)     
                    * **file** [**JplEphemerisTable.hpp**](JplEphemerisTable_8hpp.md)     
                    * **dir** [**Earth**](dir_75c6709890bdaeca67b81158f928802c.md)     
                        * **file** [**Earth.cpp**](Earth_8cpp.md)     
                        * **file** [**Earth.hpp**](Earth_8hpp.md) _Header file for the Earth class._     
                        * **file** [**Moon.cpp**](Moon_8cpp.md)     
                        * **file** [**Moon.hpp**](Moon_8hpp.md) _Header file for the Moon class._     
                    * **dir** [**Jupiter**](dir_c4fa1b5971c1990efd87a43a39eac238.md)     
                        * **file** [**Callisto.hpp**](Callisto_8hpp.md) _Header file for the Callisto class._     
                        * **file** [**Europa.hpp**](Europa_8hpp.md) _Header file for the Europa class._     
                        * **file** [**Ganymede.hpp**](Ganymede_8hpp.md) _Header file for the Ganymede class._     
                        * **file** [**Io.hpp**](Io_8hpp.md) _Header file for the Io class._     
                        * **file** [**Jupiter.cpp**](Jupiter_8cpp.md)     
                        * **file** [**Jupiter.hpp**](Jupiter_8hpp.md) _Header file for the Jupiter class._     
                    * **dir** [**Mars**](dir_262a2d2e73be89b2c0c48090ebaaa7f9.md)     
                        * **file** [**Deimos.hpp**](Deimos_8hpp.md) _Header file for the Deimos class._     
                        * **file** [**Mars.cpp**](Mars_8cpp.md)     
                        * **file** [**Mars.hpp**](Mars_8hpp.md) _Header file for the Mars class._     
                        * **file** [**Phobos.hpp**](Phobos_8hpp.md) _Header file for the Phobos class._     
                    * **dir** [**Mercury**](dir_b1a5af1521642f4d9f72715b19091401.md)     
                        * **file** [**Mercury.cpp**](Mercury_8cpp.md)     
                        * **file** [**Mercury.hpp**](Mercury_8hpp.md) _Header file for the Mercury class._     
                    * **dir** [**Neptune**](dir_218149e19931632c0aa773ce91bba6d7.md)     
                        * **file** [**Neptune.cpp**](Neptune_8cpp.md)     
                        * **file** [**Neptune.hpp**](Neptune_8hpp.md) _Header file for the Neptune class._     
                        * **file** [**Triton.hpp**](Triton_8hpp.md) _Header file for the Triton class._     
                    * **dir** [**Saturn**](dir_a10a33e87be611798e598d7dfa84b38d.md)     
                        * **file** [**Iapetus.hpp**](Iapetus_8hpp.md) _Header file for the Iapetus class._     
                        * **file** [**Rhea.hpp**](Rhea_8hpp.md) _Header file for the Rhea class._     
                        * **file** [**Saturn.cpp**](Saturn_8cpp.md)     
                        * **file** [**Saturn.hpp**](Saturn_8hpp.md) _Header file for the Saturn class._     
                        * **file** [**Titan.cpp**](Titan_8cpp.md)     
                        * **file** [**Titan.hpp**](Titan_8hpp.md) _Header file for the Titan class._     
                    * **dir** [**Sun**](dir_2bae9223f0a869dce705c7092e11bc6c.md)     
                        * **file** [**Sun.cpp**](Sun_8cpp.md)     
                        * **file** [**Sun.hpp**](Sun_8hpp.md) _Header file for the Sun class._     
                    * **dir** [**Uranus**](dir_7b592d311fa9a0d617c41c2d0e8e5c61.md)     
                        * **file** [**Oberon.hpp**](Oberon_8hpp.md) _Header file for the Oberon class._     
                        * **file** [**Titania.hpp**](Titania_8hpp.md) _Header file for the Titania class._     
                        * **file** [**Uranus.cpp**](Uranus_8cpp.md)     
                        * **file** [**Uranus.hpp**](Uranus_8hpp.md) _Header file for the Uranus class._     
                    * **dir** [**Venus**](dir_c031715b0a158a554841f23d3696455e.md)     
                        * **file** [**Venus.cpp**](Venus_8cpp.md)     
                        * **file** [**Venus.hpp**](Venus_8hpp.md) _Header file for the Venus class._     
                    * **file** [**planetary\_bodies.hpp**](planetary__bodies_8hpp.md) _Header file that includes all planetary bodies._ 
            * **dir** [**time**](dir_0abd23a91674297917c73da93ecec0fe.md)     
                * **file** [**Date.cpp**](Date_8cpp.md)     
                * **file** [**Date.hpp**](Date_8hpp.md) _Date class for handling time in the astrea astro library._     
                * **file** [**Interval.hpp**](Interval_8hpp.md) _This file defines the Interval class, which represents a time interval with a start and end time._     
                * **file** [**JulianDateClock.hpp**](JulianDateClock_8hpp.md) _A clock implementation for Julian Dates. Adapted from_ [https://stackoverflow.com/questions/33964461/handling-julian-days-in-c11-14](https://stackoverflow.com/questions/33964461/handling-julian-days-in-c11-14) _._    
            * **dir** [**types**](dir_81b398d2ba04cf47420d9ac22d356bcf.md)     
                * **file** [**enums.hpp**](enums_8hpp.md) _Enumeration types for astrodynamics._     
                * **file** [**tuple\_hash.hpp**](tuple__hash_8hpp.md) _This file provides a hash function for tuples._     
                * **file** [**type\_traits.hpp**](type__traits_8hpp.md) _Type traits for astrea astro library._     
                * **file** [**typedefs.hpp**](typedefs_8hpp.md) _Contains type definitions for the astrea astro library._     
                * **file** [**variant\_util.hpp**](variant__util_8hpp.md) _Utility functions for working with std::variant._     
            * **dir** [**utilities**](dir_68b93ce2887c47fc193a24ece16ebbe5.md)     
                * **file** [**conversions.cpp**](conversions_8cpp.md)     
                * **file** [**conversions.hpp**](conversions_8hpp.md) _This file contains functions for converting between different coordinate systems and formats in astrodynamics._     
                * **file** [**plotting.cpp**](plotting_8cpp.md)     
                * **file** [**plotting.hpp**](plotting_8hpp.md)     
            * **file** [**astro.fwd.hpp**](astro_8fwd_8hpp.md) _Forward declarations for the astro module._     
            * **file** [**astro.hpp**](astro_8hpp.md) _Header file for the astro module._ 
            * **file** [**astro.macros.hpp**](astro_8macros_8hpp.md) _Macros for the astro module._     

