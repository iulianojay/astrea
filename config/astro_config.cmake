
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

    ${INC}/astro/access/access.hpp

    ${INC}/astro/constants/astronomical_constants.h
    ${INC}/astro/constants/math_constants.h
    ${INC}/astro/constants/rk_constants.h

    ${INC}/astro/element_sets/ElementSet.hpp
    ${INC}/astro/element_sets/Frame.hpp
    ${INC}/astro/element_sets/OrbitalElements.hpp

    ${INC}/astro/platforms/access/fov/FieldOfView.hpp
    ${INC}/astro/platforms/access/Antenna.hpp
    ${INC}/astro/platforms/access/Sensor.hpp

    ${INC}/astro/platforms/ground/GroundStation.hpp

    ${INC}/astro/platforms/space/Constellation.hpp
    ${INC}/astro/platforms/space/Plane.hpp
    ${INC}/astro/platforms/space/Shell.hpp
    ${INC}/astro/platforms/vehicles/Spacecraft.hpp
    ${INC}/astro/platforms/Vehicle.hpp

    ${INC}/astro/propagation/Integrator.hpp
    ${INC}/astro/propagation/LambertSolver.hpp

    ${INC}/astro/propagation/force_models/AtmosphericForce.hpp
    ${INC}/astro/propagation/force_models/Force.hpp
    ${INC}/astro/propagation/force_models/ForceModel.hpp
    ${INC}/astro/propagation/force_models/NBodyForce.hpp
    ${INC}/astro/propagation/force_models/OblatenessForce.hpp
    ${INC}/astro/propagation/force_models/SolarRadiationPressureForce.hpp

    ${INC}/astro/propagation/equations_of_motion/KeplerianVop.hpp
    ${INC}/astro/propagation/equations_of_motion/CowellsMethod.hpp
    ${INC}/astro/propagation/equations_of_motion/EquationsOfMotion.hpp
    ${INC}/astro/propagation/equations_of_motion/J2MeanVop.hpp
    ${INC}/astro/propagation/equations_of_motion/EquinoctialVop.hpp
    ${INC}/astro/propagation/equations_of_motion/TwoBody.hpp

    ${INC}/astro/systems/AstrodynamicsSystem.hpp
    ${INC}/astro/systems/Barycenter.hpp
    ${INC}/astro/systems/CelestialBody.hpp
    ${INC}/astro/systems/CelestialBodyFactory.hpp

    ${INC}/astro/time/Date.hpp
    ${INC}/astro/time/Interval.hpp
    ${INC}/astro/time/JulianDateClock.hpp
    ${INC}/astro/time/time_units.hpp
    ${INC}/astro/time/Time.hpp
    ${INC}/astro/time/access/AccessArray.hpp
    ${INC}/astro/time/access/RiseSetArray.hpp

    ${INC}/astro/types/typedefs.hpp
    ${INC}/astro/types/tuple_hash.hpp

    ${INC}/astro/utilities/conversions.hpp
    ${INC}/astro/utilities/riseset_utils.hpp
    ${INC}/astro/utilities/math/math_c.hpp
    ${INC}/astro/utilities/math/interpolation.hpp

    ${INC}/astro/State.hpp

    # Forward declaration headers
    ${INC}/fwd/element_sets/ElementSet.fwd.hpp
    ${INC}/fwd/element_sets/Frame.fwd.hpp
    ${INC}/fwd/element_sets/OrbitalElements.fwd.hpp

    ${INC}/fwd/platforms/access/fov/FieldOfView.fwd.hpp
    ${INC}/fwd/platforms/access/Antenna.fwd.hpp
    ${INC}/fwd/platforms/access/Sensor.fwd.hpp

    ${INC}/fwd/platforms/ground/GroundStation.fwd.hpp

    ${INC}/fwd/platforms/space/Constellation.fwd.hpp
    ${INC}/fwd/platforms/space/Plane.fwd.hpp
    ${INC}/fwd/platforms/space/Shell.fwd.hpp
    ${INC}/fwd/platforms/space/Spacecraft.fwd.hpp

    ${INC}/fwd/propagation/Integrator.fwd.hpp
    ${INC}/fwd/propagation/LambertSolver.fwd.hpp

    ${INC}/fwd/propagation/equations_of_motion/EquationsOfMotion.fwd.hpp

    ${INC}/fwd/systems/AstrodynamicsSystem.fwd.hpp
    ${INC}/fwd/systems/Barycenter.fwd.hpp
    ${INC}/fwd/systems/CelestialBody.fwd.hpp
    ${INC}/fwd/systems/CelestialBodyFactory.fwd.hpp

    ${INC}/fwd/time/Date.fwd.hpp
    ${INC}/fwd/time/Interval.fwd.hpp
    ${INC}/fwd/time/JulianDateClock.fwd.hpp
    ${INC}/fwd/time/Time.fwd.hpp
    ${INC}/fwd/time/access/AccessArray.fwd.hpp
    ${INC}/fwd/time/access/RiseSetArray.fwd.hpp

    ${INC}/fwd/State.fwd.hpp

    # Extern
    ${INC}/extern/nlohmann/json.hpp
)

# Compiler flags
set(DEBUG_FLAGS "-g -DWL=64 -m64 -fPIC -mfpmath=387 -fpermissive -DLINUX")
set(RELEASE_FLAGS "-O3 -DWL=64 -m64 -fPIC -mfpmath=387 -ffast-math -fpermissive -DLINUX")
set(RELWITHHDEBINFO_FLAGS "${RELEASE_FLAGS} -g")

set(C_FLAGS "-std=c20")
set(CXX_FLAGS "-std=c++20")

# if (${OS} STREQUAL linux)
    set(C_FLAGS "${C_FLAGS} -Wall")
    set(CXX_FLAGS "${CXX_FLAGS} -Wall")
# else()
#     set(C_FLAGS "${C_FLAGS} -Wl,--kill-at")
#     set(CXX_FLAGS "${CXX_FLAGS} -Wl,--kill-at")
# endif()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${DEBUG_FLAGS} ${C_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DEBUG_FLAGS} ${CXX_FLAGS}")

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${RELEASE_FLAGS} ${C_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${RELEASE_FLAGS} ${CXX_FLAGS}")

set(CMAKE_C_FLAGS_RELWITHHDEBINFO "${CMAKE_C_FLAGS_RELWITHHDEBINFO} ${RELWITHHDEBINFO_FLAGS} ${C_FLAGS}")
set(CMAKE_CXX_FLAGS_RELWITHHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHHDEBINFO} ${RELWITHHDEBINFO_FLAGS} ${CXX_FLAGS}")