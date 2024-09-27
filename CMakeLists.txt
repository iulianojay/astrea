
cmake_minimum_required(VERSION 3.16.3)

project(astro VERSION 1.0.0 DESCRIPTION "C++ astodynamics library" LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
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
    ${SRC}/element_sets/OrbitalElements.cpp

    ${SRC}/platforms/Constellation.cpp
    ${SRC}/platforms/Plane.cpp
    ${SRC}/platforms/Shell.cpp
    ${SRC}/platforms/Spacecraft.cpp

    ${SRC}/propagation/EquationsOfMotion.cpp
    ${SRC}/propagation/Integrator.cpp
    ${SRC}/propagation/LambertSolver.cpp

    ${SRC}/systems/AstrodynamicsSystem.cpp
    ${SRC}/systems/GravitationalBody.cpp
    ${SRC}/systems/SolarObjectBuilder.cpp
    ${SRC}/systems/SolarObjectFactory.cpp

    ${SRC}/time/Time.cpp

    ${SRC}/utilities/conversions.cpp
    ${SRC}/utilities/math_c.cpp

    ${SRC}/State.cpp
)

include_directories(
    ${INC}
    ${INC}/astro
    ${INC}/astro/constants
    ${INC}/astro/element_sets
    ${INC}/astro/platforms
    ${INC}/astro/propagation
    ${INC}/astro/systems
    ${INC}/astro/time
    ${INC}/astro/types
    ${INC}/astro/utilities
)

include(config/astro_config.cmake)

# # Find packages
# find_package(Arrow REQUIRED)
# find_package(Parquet REQUIRED)

# Shared library
add_library                (${LIBNAME}_shared SHARED ${OBJS} ${HDRS})
set_target_properties      (${LIBNAME}_shared PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${LIBPATH} VERSION ${PROJECT_VERSION} OUTPUT_NAME ${LIBNAME} CLEAN_DIRECT_OUTPUT 1)
target_include_directories (${LIBNAME}_shared PUBLIC ${INCLUDE_DIRS})

# Static library
add_library                (${LIBNAME}_static STATIC ${OBJS} ${HDRS})
set_target_properties      (${LIBNAME}_static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${LIBPATH} VERSION ${PROJECT_VERSION} OUTPUT_NAME ${LIBNAME} CLEAN_DIRECT_OUTPUT 1)
target_include_directories (${LIBNAME}_static PUBLIC ${INCLUDE_DIRS})

# Executable
add_executable             (${EXENAME} ${SRC}/main.cpp)
set_target_properties      (${EXENAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BINPATH} VERSION ${PROJECT_VERSION} OUTPUT_NAME ${EXENAME} CLEAN_DIRECT_OUTPUT 1)
target_include_directories (${EXENAME} PUBLIC ${INCLUDE_DIRS})
target_link_libraries      (${EXENAME} PUBLIC ${LIBNAME}_shared)
# target_link_libraries      (${EXENAME} PUBLIC ${LIBNAME}_shared PRIVATE Arrow::arrow_shared Parquet::parquet_shared)
add_dependencies           (${EXENAME} ${LIBNAME}_shared)

if (BUILD_SWIG)
    include(config/swig.cmake)
endif()