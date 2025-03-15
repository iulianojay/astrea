
cmake_minimum_required(VERSION 3.31.6)

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
    ${ASTRO_BASE}/platforms/space/Constellation.cpp
    ${ASTRO_BASE}/platforms/space/Plane.cpp
    ${ASTRO_BASE}/platforms/space/Shell.cpp
    
    ${ASTRO_BASE}/platforms/vehicles/Spacecraft.cpp
    ${ASTRO_BASE}/platforms/Vehicle.cpp

    ${ASTRO_BASE}/propagation/Integrator.cpp
    ${ASTRO_BASE}/propagation/LambertSolver.cpp

    ${ASTRO_BASE}/propagation/force_models/AtmosphericForce.cpp
    ${ASTRO_BASE}/propagation/force_models/NBodyForce.cpp
    ${ASTRO_BASE}/propagation/force_models/OblatenessForce.cpp
    ${ASTRO_BASE}/propagation/force_models/SolarRadiationPressureForce.cpp

    ${ASTRO_BASE}/propagation/equations_of_motion/KeplerianVop.cpp
    ${ASTRO_BASE}/propagation/equations_of_motion/CowellsMethod.cpp
    ${ASTRO_BASE}/propagation/equations_of_motion/J2MeanVop.cpp
    ${ASTRO_BASE}/propagation/equations_of_motion/EquinoctialVop.cpp
    ${ASTRO_BASE}/propagation/equations_of_motion/TwoBody.cpp

    ${ASTRO_BASE}/systems/AstrodynamicsSystem.cpp
    ${ASTRO_BASE}/systems/CelestialBody.cpp
    ${ASTRO_BASE}/systems/CelestialBodyFactory.cpp

    ${ASTRO_BASE}/time/Time.cpp

    ${ASTRO_BASE}/utilities/conversions.cpp

    ${ASTRO_BASE}/State.cpp
)

# Headers
if (PROJECT_IS_TOP_LEVEL) 
    set(EXTERN_BASE ${CMAKE_SOURCE_DIR}/../../extern)
else()
    set(EXTERN_BASE ${CMAKE_SOURCE_DIR}/extern)
endif()
set(ASTRO_HEADERS
    ${ASTRO_BASE}/astro.hpp
    ${ASTRO_BASE}/astro.fwd.hpp

    ${ASTRO_BASE}/constants/astronomical_constants.h
    ${ASTRO_BASE}/constants/rk_constants.h

    ${ASTRO_BASE}/element_sets/ElementSet.hpp
    ${ASTRO_BASE}/element_sets/Frame.hpp
    ${ASTRO_BASE}/element_sets/OrbitalElements.hpp

    ${ASTRO_BASE}/platforms/space/Constellation.hpp
    ${ASTRO_BASE}/platforms/space/Plane.hpp
    ${ASTRO_BASE}/platforms/space/Shell.hpp
    ${ASTRO_BASE}/platforms/vehicles/Spacecraft.hpp
    ${ASTRO_BASE}/platforms/Vehicle.hpp

    ${ASTRO_BASE}/propagation/Integrator.hpp
    ${ASTRO_BASE}/propagation/LambertSolver.hpp

    ${ASTRO_BASE}/propagation/force_models/AtmosphericForce.hpp
    ${ASTRO_BASE}/propagation/force_models/Force.hpp
    ${ASTRO_BASE}/propagation/force_models/ForceModel.hpp
    ${ASTRO_BASE}/propagation/force_models/NBodyForce.hpp
    ${ASTRO_BASE}/propagation/force_models/OblatenessForce.hpp
    ${ASTRO_BASE}/propagation/force_models/SolarRadiationPressureForce.hpp

    ${ASTRO_BASE}/propagation/equations_of_motion/KeplerianVop.hpp
    ${ASTRO_BASE}/propagation/equations_of_motion/CowellsMethod.hpp
    ${ASTRO_BASE}/propagation/equations_of_motion/EquationsOfMotion.hpp
    ${ASTRO_BASE}/propagation/equations_of_motion/J2MeanVop.hpp
    ${ASTRO_BASE}/propagation/equations_of_motion/EquinoctialVop.hpp
    ${ASTRO_BASE}/propagation/equations_of_motion/TwoBody.hpp

    ${ASTRO_BASE}/systems/AstrodynamicsSystem.hpp
    ${ASTRO_BASE}/systems/Barycenter.hpp
    ${ASTRO_BASE}/systems/CelestialBody.hpp
    ${ASTRO_BASE}/systems/CelestialBodyFactory.hpp

    ${ASTRO_BASE}/time/Date.hpp
    ${ASTRO_BASE}/time/Interval.hpp
    ${ASTRO_BASE}/time/JulianDateClock.hpp
    ${ASTRO_BASE}/time/time_units.hpp
    ${ASTRO_BASE}/time/Time.hpp

    ${ASTRO_BASE}/types/typedefs.hpp
    ${ASTRO_BASE}/types/tuple_hash.hpp

    ${ASTRO_BASE}/utilities/conversions.hpp

    ${ASTRO_BASE}/State.hpp

    # Extern
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
    ${CMAKE_CURRENT_LIST_DIR}
    ${EXTERN_BASE}
    ${CMAKE_INSTALL_PREFIX}/../math/include
)
include_directories(${ASTRO_DIRS})

# Shared library
add_library           (${PROJECT_NAME}_shared SHARED ${ASTRO_SOURCES} ${ASTRO_HEADERS})
set_target_properties (${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_link_libraries (${PROJECT_NAME}_shared PUBLIC math_shared)

# Static library
add_library           (${PROJECT_NAME}_static STATIC ${ASTRO_SOURCES} ${ASTRO_HEADERS})
set_target_properties (${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1 SUFFIX .a.${PROJECT_VERSION})
target_link_libraries (${PROJECT_NAME}_shared PUBLIC math_static)

# Install headers
file(COPY
    DIRECTORY ${ASTRO_BASE}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING
    PATTERN *.hpp
    PATTERN *.h
)