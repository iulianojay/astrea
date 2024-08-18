
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