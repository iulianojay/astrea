# Copyright (c) 2025 Jay Iuliano
#
# This file is part of Astrea.
# Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
# Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
# have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.28.3)

project(
    astro
    VERSION ${ASTREA_VERSION}
    DESCRIPTION "Core Physics and Astrodynamics Library"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

# Objects
set(ASTRO_BASE ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME})
set(ASTRO_SOURCES
    ${ASTRO_BASE}/platforms/vehicles/NullVehicle.cpp
    ${ASTRO_BASE}/platforms/vehicles/Spacecraft.cpp
    ${ASTRO_BASE}/platforms/Vehicle.cpp
    ${ASTRO_BASE}/platforms/thrusters/Thruster.cpp

    ${ASTRO_BASE}/propagation/numerical/Integrator.cpp

    ${ASTRO_BASE}/propagation/analytic/LambertSolver.cpp

    ${ASTRO_BASE}/propagation/event_detection/Event.cpp
    ${ASTRO_BASE}/propagation/event_detection/EventDetector.cpp
    ${ASTRO_BASE}/propagation/event_detection/Schedule.cpp

    ${ASTRO_BASE}/propagation/event_detection/events/ImpulsiveBurn.cpp
    ${ASTRO_BASE}/propagation/event_detection/events/Deorbit.cpp
    ${ASTRO_BASE}/propagation/event_detection/events/TurnThrustersOn.cpp
    ${ASTRO_BASE}/propagation/event_detection/events/TurnThrustersOff.cpp

    ${ASTRO_BASE}/propagation/force_models/ForceModel.cpp
    ${ASTRO_BASE}/propagation/force_models/instances/AtmosphericForce.cpp
    ${ASTRO_BASE}/propagation/force_models/instances/NBodyForce.cpp
    ${ASTRO_BASE}/propagation/force_models/instances/OblatenessForce.cpp
    ${ASTRO_BASE}/propagation/force_models/instances/SolarRadiationPressure.cpp

    ${ASTRO_BASE}/propagation/equations_of_motion/instances/KeplerianVop.cpp
    ${ASTRO_BASE}/propagation/equations_of_motion/instances/CowellsMethod.cpp
    ${ASTRO_BASE}/propagation/equations_of_motion/EquationsOfMotion.cpp
    ${ASTRO_BASE}/propagation/equations_of_motion/instances/EquinoctialVop.cpp
    ${ASTRO_BASE}/propagation/equations_of_motion/instances/J2MeanVop.cpp
    ${ASTRO_BASE}/propagation/equations_of_motion/instances/TwoBody.cpp

    ${ASTRO_BASE}/propagation/equations_of_motion/StateTransitionMatrix.cpp

    ${ASTRO_BASE}/state/State.cpp
    ${ASTRO_BASE}/state/StateHistory.cpp

    ${ASTRO_BASE}/state/attitude/Attitude.cpp

    ${ASTRO_BASE}/state/angular_elements/instances/Cylindrical.cpp
    ${ASTRO_BASE}/state/angular_elements/instances/Geodetic.cpp
    ${ASTRO_BASE}/state/angular_elements/instances/Geocentric.cpp
    ${ASTRO_BASE}/state/angular_elements/instances/Spherical.cpp

    ${ASTRO_BASE}/state/orbital_elements/instances/Equinoctial.cpp
    ${ASTRO_BASE}/state/orbital_elements/instances/Keplerian.cpp
    ${ASTRO_BASE}/state/orbital_elements/OrbitalElements.cpp

    ${ASTRO_BASE}/state/orbital_data_formats/instances/TwoLineElements.cpp
    ${ASTRO_BASE}/state/orbital_data_formats/instances/GeneralPerturbations.cpp

    ${ASTRO_BASE}/frames/FrameReference.cpp

    ${ASTRO_BASE}/systems/AstrodynamicsSystem.cpp
    ${ASTRO_BASE}/systems/CelestialBody.cpp
    ${ASTRO_BASE}/systems/planetary_bodies/JplEphemerisTable.cpp
    ${ASTRO_BASE}/systems/planetary_bodies/Earth/Earth.cpp
    ${ASTRO_BASE}/systems/planetary_bodies/Earth/Moon.cpp
    ${ASTRO_BASE}/systems/planetary_bodies/Mars/Mars.cpp
    ${ASTRO_BASE}/systems/planetary_bodies/Mercury/Mercury.cpp
    ${ASTRO_BASE}/systems/planetary_bodies/Neptune/Neptune.cpp
    ${ASTRO_BASE}/systems/planetary_bodies/Jupiter/Jupiter.cpp
    ${ASTRO_BASE}/systems/planetary_bodies/Saturn/Saturn.cpp
    ${ASTRO_BASE}/systems/planetary_bodies/Saturn/Titan.cpp
    ${ASTRO_BASE}/systems/planetary_bodies/Sun/Sun.cpp
    ${ASTRO_BASE}/systems/planetary_bodies/Uranus/Uranus.cpp
    ${ASTRO_BASE}/systems/planetary_bodies/Venus/Venus.cpp

    ${ASTRO_BASE}/time/Date.cpp

    ${ASTRO_BASE}/utilities/conversions.cpp
    ${ASTRO_BASE}/utilities/plotting.cpp
)

# Headers
set(ASTRO_HEADERS
    ${ASTRO_BASE}/astro.hpp
    ${ASTRO_BASE}/astro.fwd.hpp

    ${ASTRO_BASE}/frames/instances/body_centered_inertial_frames.hpp
    ${ASTRO_BASE}/frames/instances/body_fixed_frames.hpp
    ${ASTRO_BASE}/frames/instances/defined_rotations.hpp
    ${ASTRO_BASE}/frames/instances/EastNorthUp.hpp
    ${ASTRO_BASE}/frames/instances/LocalHorizontalLocalVertical.hpp
    ${ASTRO_BASE}/frames/instances/RadialInTrackCrossTrack.hpp
    ${ASTRO_BASE}/frames/instances/VelocityNormalBinormal.hpp

    ${ASTRO_BASE}/frames/types/DirectionCosineMatrix.hpp
    ${ASTRO_BASE}/frames/types/InertialFrame.hpp
    ${ASTRO_BASE}/frames/types/BodyFixedFrame.hpp

    ${ASTRO_BASE}/frames/CartesianVector.hpp
    ${ASTRO_BASE}/frames/dynamic_frames.hpp
    ${ASTRO_BASE}/frames/frame_concepts.hpp
    ${ASTRO_BASE}/frames/Frame.hpp
    ${ASTRO_BASE}/frames/FrameReference.hpp
    ${ASTRO_BASE}/frames/frames.hpp
    ${ASTRO_BASE}/frames/transformations.hpp

    ${ASTRO_BASE}/platforms/space/Constellation.hpp
    ${ASTRO_BASE}/platforms/space/Constellation.ipp
    ${ASTRO_BASE}/platforms/space/Plane.hpp
    ${ASTRO_BASE}/platforms/space/Plane.ipp
    ${ASTRO_BASE}/platforms/space/Shell.hpp
    ${ASTRO_BASE}/platforms/space/Shell.ipp

    ${ASTRO_BASE}/platforms/vehicles/Spacecraft.hpp
    ${ASTRO_BASE}/platforms/Vehicle.hpp

    ${ASTRO_BASE}/propagation/numerical/Integrator.hpp
    ${ASTRO_BASE}/propagation/numerical/StepWatcher.hpp
    ${ASTRO_BASE}/propagation/numerical/butcher_tableau.hpp

    ${ASTRO_BASE}/propagation/analytic/LambertSolver.hpp

    ${ASTRO_BASE}/propagation/event_detection/Event.hpp
    ${ASTRO_BASE}/propagation/event_detection/EventDetector.hpp
    ${ASTRO_BASE}/propagation/event_detection/Schedule.hpp

    ${ASTRO_BASE}/propagation/event_detection/events/NullEvent.hpp
    ${ASTRO_BASE}/propagation/event_detection/events/ImpulsiveBurn.hpp
    ${ASTRO_BASE}/propagation/event_detection/events/Deorbit.hpp
    ${ASTRO_BASE}/propagation/event_detection/events/TurnThrustersOn.hpp
    ${ASTRO_BASE}/propagation/event_detection/events/TurnThrustersOff.hpp

    ${ASTRO_BASE}/propagation/force_models/instances/AtmosphericForce.hpp
    ${ASTRO_BASE}/propagation/force_models/PerturbingForce.hpp
    ${ASTRO_BASE}/propagation/force_models/ForceModel.hpp
    ${ASTRO_BASE}/propagation/force_models/instances/NBodyForce.hpp
    ${ASTRO_BASE}/propagation/force_models/instances/OblatenessForce.hpp
    ${ASTRO_BASE}/propagation/force_models/instances/SolarRadiationPressure.hpp

    ${ASTRO_BASE}/propagation/equations_of_motion/instances/KeplerianVop.hpp
    ${ASTRO_BASE}/propagation/equations_of_motion/instances/CowellsMethod.hpp
    ${ASTRO_BASE}/propagation/equations_of_motion/EquationsOfMotion.hpp
    ${ASTRO_BASE}/propagation/equations_of_motion/instances/J2MeanVop.hpp
    ${ASTRO_BASE}/propagation/equations_of_motion/instances/EquinoctialVop.hpp
    ${ASTRO_BASE}/propagation/equations_of_motion/instances/TwoBody.hpp

    ${ASTRO_BASE}/propagation/equations_of_motion/StateTransitionMatrix.hpp

    ${ASTRO_BASE}/state/State.hpp
    ${ASTRO_BASE}/state/StateHistory.hpp

    ${ASTRO_BASE}/state/attitude/Attitude.hpp
    ${ASTRO_BASE}/state/attitude/instances/Quaternion.hpp
    ${ASTRO_BASE}/state/attitude/instances/AngularVelocities.hpp
    ${ASTRO_BASE}/state/attitude/instances/EulerAngles.hpp

    ${ASTRO_BASE}/state/angular_elements/instances/Cylindrical.hpp
    ${ASTRO_BASE}/state/angular_elements/instances/Geocentric.hpp
    ${ASTRO_BASE}/state/angular_elements/instances/Geodetic.hpp
    ${ASTRO_BASE}/state/angular_elements/instances/Spherical.hpp
    ${ASTRO_BASE}/state/angular_elements/AngularElements.hpp

    ${ASTRO_BASE}/state/orbital_elements/instances/Cartesian.hpp
    ${ASTRO_BASE}/state/orbital_elements/instances/Equinoctial.hpp
    ${ASTRO_BASE}/state/orbital_elements/instances/Keplerian.hpp
    ${ASTRO_BASE}/state/orbital_elements/OrbitalElements.hpp

    ${ASTRO_BASE}/state/orbital_data_formats/instances/TwoLineElements.hpp
    ${ASTRO_BASE}/state/orbital_data_formats/instances/GeneralPerturbations.hpp

    ${ASTRO_BASE}/state/attitude/instances/Quaternion.hpp

    ${ASTRO_BASE}/systems/AstrodynamicsSystem.hpp
    ${ASTRO_BASE}/systems/CelestialBody.hpp
    ${ASTRO_BASE}/systems/CelestialBodyParameters.hpp
    ${ASTRO_BASE}/systems/planetary_bodies/planetary_bodies.hpp
    ${ASTRO_BASE}/systems/planetary_bodies/JplEphemerisTable.hpp
    ${ASTRO_BASE}/systems/planetary_bodies/Earth/Earth.hpp
    ${ASTRO_BASE}/systems/planetary_bodies/Earth/Moon.hpp
    ${ASTRO_BASE}/systems/planetary_bodies/Mars/Deimos.hpp
    ${ASTRO_BASE}/systems/planetary_bodies/Mars/Mars.hpp
    ${ASTRO_BASE}/systems/planetary_bodies/Mars/Phobos.hpp
    ${ASTRO_BASE}/systems/planetary_bodies/Mercury/Mercury.hpp
    ${ASTRO_BASE}/systems/planetary_bodies/Neptune/Neptune.hpp
    ${ASTRO_BASE}/systems/planetary_bodies/Neptune/Triton.hpp
    ${ASTRO_BASE}/systems/planetary_bodies/Saturn/Iapetus.hpp
    ${ASTRO_BASE}/systems/planetary_bodies/Saturn/Rhea.hpp
    ${ASTRO_BASE}/systems/planetary_bodies/Saturn/Saturn.hpp
    ${ASTRO_BASE}/systems/planetary_bodies/Saturn/Titan.hpp
    ${ASTRO_BASE}/systems/planetary_bodies/Sun/Sun.hpp
    ${ASTRO_BASE}/systems/planetary_bodies/Uranus/Uranus.hpp
    ${ASTRO_BASE}/systems/planetary_bodies/Uranus/Titania.hpp
    ${ASTRO_BASE}/systems/planetary_bodies/Uranus/Oberon.hpp
    ${ASTRO_BASE}/systems/planetary_bodies/Venus/Venus.hpp

    ${ASTRO_BASE}/time/Date.hpp
    ${ASTRO_BASE}/time/Interval.hpp
    ${ASTRO_BASE}/time/JulianDateClock.hpp

    ${ASTRO_BASE}/types/typedefs.hpp
    ${ASTRO_BASE}/types/tuple_hash.hpp
    ${ASTRO_BASE}/types/variant_util.hpp

    ${ASTRO_BASE}/utilities/conversions.hpp
)

# Build ephemeris files
option(BUILD_SUN "Build Sun Ephemeris" ON)
option(BUILD_MERCURY "Build Mercury Ephemeris" OFF)
option(BUILD_EARTH "Build Earth Ephemeris" ON)
option(BUILD_MARS "Build Mars Ephemeris" OFF)
option(BUILD_VENUS "Build Venus Ephemeris" OFF)
option(BUILD_JUPITER "Build Jupiter Ephemeris" OFF)
option(BUILD_SATURN "Build Saturn Ephemeris" OFF)
option(BUILD_URANUS "Build Uranus Ephemeris" OFF)
option(BUILD_NEPTUNE "Build Neptune Ephemeris" OFF)
set(BUILD_EPHEMERIDES(BUILD_SUN OR BUILD_MERCURY OR BUILD_EARTH OR BUILD_MARS OR BUILD_VENUS OR BUILD_JUPITER OR BUILD_SATURN OR BUILD_URANUS OR BUILD_NEPTUNE))

set(EPHEMERIS_COMPILE_DEFINES "")
generate_ephemeris_files(${CMAKE_CURRENT_LIST_DIR})

# Includes
set(ASTRO_DIRS
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../math
    ${CMAKE_CURRENT_LIST_DIR}/../snapshot
    ${CMAKE_CURRENT_LIST_DIR}/../units
    ${CMAKE_CURRENT_LIST_DIR}/../utilities
)
include_directories(${ASTRO_DIRS})

# Find library
set(ASTRO_LIBS
    mp-units::mp-units
    matplot
    nlohmann_json::nlohmann_json
    sqlite_orm::sqlite_orm
    gtl
)

# Shared library
add_library(${PROJECT_NAME}_shared SHARED ${ASTRO_SOURCES} ${ASTRO_HEADERS})

if(${BUILD_EPHEMERIDES})
    add_dependencies(${PROJECT_NAME}_shared generated_ephemerides)
endif()

set_target_properties      (${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_link_libraries      (${PROJECT_NAME}_shared PUBLIC math_shared utilities_shared ${ASTRO_LIBS})
target_include_directories (${PROJECT_NAME}_shared PUBLIC ${ASTRO_DIRS} ${CMAKE_CURRENT_BINARY_DIR}/include)

if(WIN32)
    target_compile_definitions (${PROJECT_NAME}_shared PUBLIC ${EPHEMERIS_COMPILE_DEFINES} "_ASTRO_ROOT_=\"${CMAKE_CURRENT_LIST_DIR}\"" WIN32_LEAN_AND_MEAN NOMINMAX)
else()
    target_compile_definitions (${PROJECT_NAME}_shared PUBLIC ${EPHEMERIS_COMPILE_DEFINES} "_ASTRO_ROOT_=\"${CMAKE_CURRENT_LIST_DIR}\"")
endif()

# Install shared library (DLL)
install(TARGETS ${PROJECT_NAME}_shared
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Install matplot shared library so dependents (benchmarks, tests) can find it at runtime
install(TARGETS matplot
    LIBRARY DESTINATION lib
)

# Static library
if(${BUILD_STATIC})
    add_library(${PROJECT_NAME}_static STATIC ${ASTRO_SOURCES} ${ASTRO_HEADERS})

    if(${BUILD_EPHEMERIDES})
        add_dependencies(${PROJECT_NAME}_static generated_ephemerides)
    endif()

    set_target_properties      (${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1 SUFFIX .a.${PROJECT_VERSION})
    target_link_libraries      (${PROJECT_NAME}_static PUBLIC math_static utilities_static ${ASTRO_LIBS})
    target_include_directories (${PROJECT_NAME}_static PUBLIC ${ASTRO_DIRS} ${CMAKE_CURRENT_BINARY_DIR}/include)
    target_compile_definitions (${PROJECT_NAME}_static PUBLIC ${EPHEMERIS_COMPILE_DEFINES} "_ASTRO_ROOT_=\"${CMAKE_CURRENT_LIST_DIR}\"")

    # Install static library (A)
    install(TARGETS ${PROJECT_NAME}_static
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
endif()

file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/include)

# Install headers
install(
    DIRECTORY ${ASTRO_BASE}
    DESTINATION include
    FILES_MATCHING
    PATTERN *.hpp
    PATTERN *.ipp
    PATTERN *.h
)

if(${BUILD_EXAMPLES})
    add_subdirectory(examples)
endif()

if(${BUILD_TESTS})
    add_subdirectory(tests)
endif()

if (${BUILD_BENCHMARKS})
    add_subdirectory(benchmarks)
endif()