
cmake_minimum_required(VERSION 3.16.3)

project(astro VERSION 1.0.0 DESCRIPTION "C++ astodynamics library" LANGUAGES C CXX)

set(CMAKE_C_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Utility variables
set(BASE ${CMAKE_CURRENT_SOURCE_DIR})
set(INC ${BASE}/include)
set(SRC ${BASE}/source)
set(TEST ${BASE}/tests)

set(BINPATH ${BASE}/bin)
set(LIBPATH ${BASE}/lib)
set(LIBNAME astro)
set(EXENAME astro_exe)
set(TESTNAME tests)

# Includes
set(INCLUDE_DIRS
    ${INC}
    ${INC}/astro
    ${INC}/astro/constants
    ${INC}/astro/element_sets
    ${INC}/astro/propagation
    ${INC}/astro/systems
    ${INC}/astro/time
    ${INC}/astro/types
    ${INC}/astro/utilities
    ${SRC}
    ${LIBPATH}

    ${INC}/frozen
)

# Objects
set(OBJS
    ${SRC}/element_sets/OrbitalElements.cpp

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

    ${SRC}/Spacecraft.cpp
    ${SRC}/State.cpp
)

# Headers
set(HDRS
    ${INC}/astro.hpp

    ${INC}/astro/constants/astronomical_constants.h
    ${INC}/astro/constants/math_constants.h
    ${INC}/astro/constants/rk_constants.h

    ${INC}/astro/element_sets/ElementSet.hpp
    ${INC}/astro/element_sets/Frame.hpp
    ${INC}/astro/element_sets/OrbitalElements.hpp

    ${INC}/astro/propagation/EquationsOfMotion.hpp
    ${INC}/astro/propagation/Integrator.hpp
    ${INC}/astro/propagation/LambertSolver.hpp
    
    ${INC}/astro/systems/AstrodynamicsSystem.hpp
    ${INC}/astro/systems/Barycenter.hpp
    ${INC}/astro/systems/GravitationalBody.hpp
    ${INC}/astro/systems/solar_system.hpp
    ${INC}/astro/systems/SolarObjectBuilder.hpp
    ${INC}/astro/systems/SolarObjectFactory.hpp
    
    ${INC}/astro/time/Date.hpp
    ${INC}/astro/time/Interval.hpp
    ${INC}/astro/time/JulianDateClock.hpp
    ${INC}/astro/time/time_units.hpp
    ${INC}/astro/time/Time.hpp

    ${INC}/astro/types/typedefs.hpp

    ${INC}/astro/utilities/conversions.hpp
    ${INC}/astro/utilities/math_c.hpp

    ${INC}/astro/Spacecraft.hpp
    ${INC}/astro/State.hpp
)

# Compiler flags
set(DEBUG_FLAGS "-g -DWL=64 -m64 -fPIC -DLINUX")
set(RELEASE_FLAGS "-O3 -DWL=64 -m64 -fPIC -DLINUX")
set(RELWITHHDEBINFO_FLAGS "${RELEASE_FLAGS} -g")

set(C_FLAGS "-std=c20 -mfpmath=387")
set(CXX_FLAGS "-std=c++20 -mfpmath=387")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${DEBUG_FLAGS} ${C_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DEBUG_FLAGS} ${CXX_FLAGS}")

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${RELEASE_FLAGS} ${C_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${RELEASE_FLAGS} ${CXX_FLAGS}")

set(CMAKE_C_FLAGS_RELWITHHDEBINFO "${CMAKE_C_FLAGS_RELWITHHDEBINFO} ${RELWITHHDEBINFO_FLAGS} ${C_FLAGS}")
set(CMAKE_CXX_FLAGS_RELWITHHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHHDEBINFO} ${RELWITHHDEBINFO_FLAGS} ${CXX_FLAGS}")

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
add_dependencies           (${EXENAME} ${LIBNAME}_shared)