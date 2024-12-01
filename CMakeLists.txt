
cmake_minimum_required(VERSION 3.16.3)

project(astro VERSION 1.0.0 DESCRIPTION "C++ astodynamics library" LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Utility variables
set(BASE ${CMAKE_CURRENT_SOURCE_DIR})
set(INC ${BASE}/include)
set(SRC ${BASE}/source)
set(TEST ${BASE}/tests)

set(BINPATH ${BASE}/bin/${OS})
set(LIBPATH ${BASE}/lib/${OS})
set(LIBNAME astro)
set(EXENAME astro_exe)
set(TESTNAME tests)

# Objects
set(OBJS
    ${SRC}/access/access.cpp

    ${SRC}/element_sets/OrbitalElements.cpp

    ${SRC}/platforms/access/fov/FieldOfView.cpp
    ${SRC}/platforms/access/Sensor.cpp

    ${SRC}/platforms/ground/GroundStation.cpp

    ${SRC}/platforms/space/Constellation.cpp
    ${SRC}/platforms/space/Plane.cpp
    ${SRC}/platforms/space/Shell.cpp
    ${SRC}/platforms/vehicles/Spacecraft.cpp
    ${SRC}/platforms/Vehicle.cpp

    ${SRC}/propagation/Integrator.cpp
    ${SRC}/propagation/LambertSolver.cpp

    ${SRC}/propagation/force_models/AtmosphericForce.cpp
    ${SRC}/propagation/force_models/NBodyForce.cpp
    ${SRC}/propagation/force_models/OblatenessForce.cpp
    ${SRC}/propagation/force_models/SolarRadiationPressureForce.cpp

    ${SRC}/propagation/equations_of_motion/KeplerianVop.cpp
    ${SRC}/propagation/equations_of_motion/CowellsMethod.cpp
    ${SRC}/propagation/equations_of_motion/J2MeanVop.cpp
    ${SRC}/propagation/equations_of_motion/EquinoctialVop.cpp
    ${SRC}/propagation/equations_of_motion/TwoBody.cpp

    ${SRC}/systems/AstrodynamicsSystem.cpp
    ${SRC}/systems/GravitationalBody.cpp
    ${SRC}/systems/SolarObjectBuilder.cpp
    ${SRC}/systems/SolarObjectFactory.cpp

    ${SRC}/time/Time.cpp
    ${SRC}/time/access/RiseSetArray.cpp

    ${SRC}/utilities/conversions.cpp
    ${SRC}/utilities/riseset_utils.cpp
    ${SRC}/utilities/math/math_c.cpp
    ${SRC}/utilities/math/interpolation.cpp

    ${SRC}/State.cpp
)

include_directories(
    ${INC}
    ${INC}/astro
    ${INC}/astro/access
    ${INC}/astro/constants
    ${INC}/astro/element_sets
    ${INC}/astro/platforms
    ${INC}/astro/platforms/access
    ${INC}/astro/platforms/access/fov
    ${INC}/astro/platforms/ground
    ${INC}/astro/platforms/space
    ${INC}/astro/platforms/vehicles
    ${INC}/astro/propagation
    ${INC}/astro/propagation/force_models
    ${INC}/astro/propagation/equations_of_motion
    ${INC}/astro/systems
    ${INC}/astro/time
    ${INC}/astro/time/access
    ${INC}/astro/types
    ${INC}/astro/utilities
    ${INC}/astro/utilities/math

    ${INC}/fwd/constants
    ${INC}/fwd/element_sets
    ${INC}/fwd/platforms
    ${INC}/fwd/platforms/access
    ${INC}/fwd/platforms/access/fov
    ${INC}/fwd/platforms/ground
    ${INC}/fwd/platforms/space
    ${INC}/fwd/propagation
    ${INC}/fwd/systems
    ${INC}/fwd/time
    ${INC}/fwd/time/access
    ${INC}/fwd/types
    ${INC}/fwd/utilities
)

include(config/astro_config.cmake)

# Set outputs
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBPATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBPATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINPATH})

# Shared library
add_library                (${LIBNAME}_shared SHARED ${OBJS} ${HDRS})
set_target_properties      (${LIBNAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${LIBNAME} CLEAN_DIRECT_OUTPUT 1)
target_include_directories (${LIBNAME}_shared PUBLIC ${INCLUDE_DIRS})

# Static library
add_library                (${LIBNAME}_static STATIC ${OBJS} ${HDRS})
set_target_properties      (${LIBNAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${LIBNAME} CLEAN_DIRECT_OUTPUT 1)
target_include_directories (${LIBNAME}_static PUBLIC ${INCLUDE_DIRS})

# Executable
add_executable             (${EXENAME} ${SRC}/main.cpp)
set_target_properties      (${EXENAME} PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories (${EXENAME} PUBLIC ${INCLUDE_DIRS})
target_link_libraries      (${EXENAME} PUBLIC ${LIBNAME}_shared)
add_dependencies           (${EXENAME} ${LIBNAME}_shared)

if (BUILD_SWIG)
    include(config/swig.cmake)
endif()