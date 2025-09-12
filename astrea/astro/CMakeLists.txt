
cmake_minimum_required(VERSION 3.28.3)

project(
    astro 
    VERSION 0.0.1 
    DESCRIPTION "Core Physics and Astrodynamics Library" 
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

# Objects
set(ASTRO_BASE ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME})
set(ASTRO_SOURCES
    ${ASTRO_BASE}/platforms/vehicles/Spacecraft.cpp
    ${ASTRO_BASE}/platforms/Vehicle.cpp
    ${ASTRO_BASE}/platforms/thrusters/Thruster.cpp

    ${ASTRO_BASE}/propagation/numerical/Integrator.cpp
    ${ASTRO_BASE}/propagation/analytic/LambertSolver.cpp
    ${ASTRO_BASE}/propagation/event_detection/Event.cpp
    ${ASTRO_BASE}/propagation/event_detection/EventDetector.cpp
    ${ASTRO_BASE}/propagation/event_detection/events/ImpulsiveBurn.cpp

    ${ASTRO_BASE}/propagation/force_models/AtmosphericForce.cpp
    ${ASTRO_BASE}/propagation/force_models/ForceModel.cpp
    ${ASTRO_BASE}/propagation/force_models/NBodyForce.cpp
    ${ASTRO_BASE}/propagation/force_models/OblatenessForce.cpp
    ${ASTRO_BASE}/propagation/force_models/SolarRadiationPressure.cpp

    ${ASTRO_BASE}/propagation/equations_of_motion/KeplerianVop.cpp
    ${ASTRO_BASE}/propagation/equations_of_motion/CowellsMethod.cpp
    ${ASTRO_BASE}/propagation/equations_of_motion/J2MeanVop.cpp
    ${ASTRO_BASE}/propagation/equations_of_motion/EquinoctialVop.cpp
    ${ASTRO_BASE}/propagation/equations_of_motion/TwoBody.cpp

    ${ASTRO_BASE}/state/State.cpp
    ${ASTRO_BASE}/state/StateHistory.cpp

    ${ASTRO_BASE}/state/angular_elements/instances/Cylindrical.cpp
    ${ASTRO_BASE}/state/angular_elements/instances/Geodetic.cpp
    ${ASTRO_BASE}/state/angular_elements/instances/Spherical.cpp

    ${ASTRO_BASE}/state/orbital_elements/instances/Cartesian.cpp
    ${ASTRO_BASE}/state/orbital_elements/instances/Equinoctial.cpp
    ${ASTRO_BASE}/state/orbital_elements/instances/Keplerian.cpp
    ${ASTRO_BASE}/state/orbital_elements/OrbitalElements.cpp
    
    ${ASTRO_BASE}/state/orbital_data_formats/instances/TwoLineElements.cpp
    ${ASTRO_BASE}/state/orbital_data_formats/instances/GeneralPerturbations.cpp

    ${ASTRO_BASE}/state/frames/FrameReference.cpp

    ${ASTRO_BASE}/systems/AstrodynamicsSystem.cpp
    ${ASTRO_BASE}/systems/CelestialBody.cpp
    ${ASTRO_BASE}/systems/CelestialBodyFactory.cpp

    ${ASTRO_BASE}/time/Date.cpp

    ${ASTRO_BASE}/utilities/conversions.cpp
)

# Headers
set(EXTERN_BASE ${CMAKE_CURRENT_LIST_DIR}/../../extern)
set(ASTRO_HEADERS
    ${ASTRO_BASE}/astro.hpp
    ${ASTRO_BASE}/astro.fwd.hpp

    ${ASTRO_BASE}/platforms/space/Constellation.hpp
    ${ASTRO_BASE}/platforms/space/Constellation.ipp
    ${ASTRO_BASE}/platforms/space/Plane.hpp
    ${ASTRO_BASE}/platforms/space/Plane.ipp
    ${ASTRO_BASE}/platforms/space/Shell.hpp
    ${ASTRO_BASE}/platforms/space/Shell.ipp
    ${ASTRO_BASE}/platforms/vehicles/Spacecraft.hpp
    ${ASTRO_BASE}/platforms/Vehicle.hpp

    ${ASTRO_BASE}/propagation/numerical/Integrator.hpp
    ${ASTRO_BASE}/propagation/numerical/butcher_tableau.hpp
    ${ASTRO_BASE}/propagation/analytic/LambertSolver.hpp
    ${ASTRO_BASE}/propagation/event_detection/Event.hpp
    ${ASTRO_BASE}/propagation/event_detection/EventDetector.hpp
    ${ASTRO_BASE}/propagation/event_detection/events/NullEvent.hpp
    ${ASTRO_BASE}/propagation/event_detection/events/ImpulsiveBurn.hpp

    ${ASTRO_BASE}/propagation/force_models/AtmosphericForce.hpp
    ${ASTRO_BASE}/propagation/force_models/Force.hpp
    ${ASTRO_BASE}/propagation/force_models/ForceModel.hpp
    ${ASTRO_BASE}/propagation/force_models/NBodyForce.hpp
    ${ASTRO_BASE}/propagation/force_models/OblatenessForce.hpp
    ${ASTRO_BASE}/propagation/force_models/SolarRadiationPressure.hpp

    ${ASTRO_BASE}/propagation/equations_of_motion/KeplerianVop.hpp
    ${ASTRO_BASE}/propagation/equations_of_motion/CowellsMethod.hpp
    ${ASTRO_BASE}/propagation/equations_of_motion/EquationsOfMotion.hpp
    ${ASTRO_BASE}/propagation/equations_of_motion/J2MeanVop.hpp
    ${ASTRO_BASE}/propagation/equations_of_motion/EquinoctialVop.hpp
    ${ASTRO_BASE}/propagation/equations_of_motion/TwoBody.hpp

    ${ASTRO_BASE}/state/State.hpp
    ${ASTRO_BASE}/state/StateHistory.hpp

    ${ASTRO_BASE}/state/angular_elements/instances/Cylindrical.hpp
    ${ASTRO_BASE}/state/angular_elements/instances/Geodetic.hpp
    ${ASTRO_BASE}/state/angular_elements/instances/Spherical.hpp
    ${ASTRO_BASE}/state/angular_elements/AngularElements.hpp

    ${ASTRO_BASE}/state/orbital_elements/instances/Cartesian.hpp
    ${ASTRO_BASE}/state/orbital_elements/instances/Equinoctial.hpp
    ${ASTRO_BASE}/state/orbital_elements/instances/Keplerian.hpp
    ${ASTRO_BASE}/state/orbital_elements/OrbitalElements.hpp
    
    ${ASTRO_BASE}/state/orbital_data_formats/instances/TwoLineElements.hpp
    ${ASTRO_BASE}/state/orbital_data_formats/instances/GeneralPerturbations.hpp
    
    ${ASTRO_BASE}/state/frames/instances/EarthCenteredEarthFixed.hpp
    ${ASTRO_BASE}/state/frames/instances/EarthCenteredInertial.hpp
    ${ASTRO_BASE}/state/frames/instances/RadialInTrackCrossTrack.hpp
    ${ASTRO_BASE}/state/frames/types/DirectionCosineMatrix.hpp
    ${ASTRO_BASE}/state/frames/types/InertialFrame.hpp
    ${ASTRO_BASE}/state/frames/types/RotatingFrame.hpp
    ${ASTRO_BASE}/state/frames/Frame.hpp
    ${ASTRO_BASE}/state/frames/FrameReference.hpp

    ${ASTRO_BASE}/systems/AstrodynamicsSystem.hpp
    ${ASTRO_BASE}/systems/Barycenter.hpp
    ${ASTRO_BASE}/systems/CelestialBody.hpp
    ${ASTRO_BASE}/systems/CelestialBodyFactory.hpp

    ${ASTRO_BASE}/time/Date.hpp
    ${ASTRO_BASE}/time/Interval.hpp
    ${ASTRO_BASE}/time/JulianDateClock.hpp

    ${ASTRO_BASE}/types/typedefs.hpp
    ${ASTRO_BASE}/types/tuple_hash.hpp
    ${ASTRO_BASE}/types/variant_util.hpp

    ${ASTRO_BASE}/utilities/conversions.hpp

    # Extern
    ${EXTERN_BASE}/date/date.h
    ${EXTERN_BASE}/nlohmann/json.hpp
)

# Set outputs
set(REL_INSTALL_PATH install/${CMAKE_HOST_SYSTEM_PROCESSOR}-${CMAKE_SYSTEM_NAME}/${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}/${CMAKE_BUILD_TYPE})
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/../../${REL_INSTALL_PATH}/${PROJECT_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)

# Includes
set(ASTRO_DIRS
    ${EXTERN_BASE}
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../math
    ${CMAKE_CURRENT_LIST_DIR}/../snapshot
    ${CMAKE_CURRENT_LIST_DIR}/../units
    ${CMAKE_CURRENT_LIST_DIR}/../utilities
    $ENV{HOME}/open-source/mp-units/src/core/include
    $ENV{HOME}/open-source/mp-units/src/systems/include
)
include_directories(${ASTRO_DIRS})

# # Find library
# find_library(AVRO avrocpp)

# Shared library
add_library                (${PROJECT_NAME}_shared SHARED ${ASTRO_SOURCES} ${ASTRO_HEADERS})
set_target_properties      (${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_link_libraries      (${PROJECT_NAME}_shared PUBLIC math_shared utilities_shared mp-units::mp-units GTest::gtest_main)
target_include_directories (${PROJECT_NAME}_shared PUBLIC ${ASTRO_DIRS})

# Static library
add_library                (${PROJECT_NAME}_static STATIC ${ASTRO_SOURCES} ${ASTRO_HEADERS})
set_target_properties      (${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1 SUFFIX .a.${PROJECT_VERSION})
target_link_libraries      (${PROJECT_NAME}_static PUBLIC math_static utilities_static mp-units::mp-units GTest::gtest_main)
target_include_directories (${PROJECT_NAME}_static PUBLIC ${ASTRO_DIRS})

# Executable
add_executable             (${PROJECT_NAME}_exe ${ASTRO_BASE}/drivers/main.cpp)
set_target_properties      (${PROJECT_NAME}_exe PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_include_directories (${PROJECT_NAME}_exe PUBLIC ${ASTRO_DIRS})
target_link_libraries      (${PROJECT_NAME}_exe PUBLIC ${PROJECT_NAME}_shared)

# Install headers
file(COPY
    DIRECTORY ${ASTRO_BASE}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
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