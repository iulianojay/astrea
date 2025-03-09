# Includes
set(INCLUDE_BASE ${CMAKE_SOURCE_DIR}/include)
set(INCLUDE_DIRS
    ${INCLUDE_BASE}
    ${INCLUDE_BASE}/astro
    ${INCLUDE_BASE}/astro/access
    ${INCLUDE_BASE}/astro/constants
    ${INCLUDE_BASE}/astro/element_sets
    ${INCLUDE_BASE}/astro/platforms
    ${INCLUDE_BASE}/astro/platforms/access
    ${INCLUDE_BASE}/astro/platforms/access/fov
    ${INCLUDE_BASE}/astro/platforms/ground
    ${INCLUDE_BASE}/astro/platforms/space
    ${INCLUDE_BASE}/astro/platforms/vehicles
    ${INCLUDE_BASE}/astro/propagation
    ${INCLUDE_BASE}/astro/propagation/force_models
    ${INCLUDE_BASE}/astro/propagation/equations_of_motion
    ${INCLUDE_BASE}/astro/systems
    ${INCLUDE_BASE}/astro/time
    ${INCLUDE_BASE}/astro/time/access
    ${INCLUDE_BASE}/astro/types
    ${INCLUDE_BASE}/astro/utilities
    ${INCLUDE_BASE}/astro/utilities/math
)

include_directories(${INCLUDE_DIRECTORIES})

# Headers
set(HEADERS
    ${INCLUDE_BASE}/astro.hpp
    ${INCLUDE_BASE}/astro.fwd.hpp

    ${INCLUDE_BASE}/astro/access/access.hpp

    ${INCLUDE_BASE}/astro/constants/astronomical_constants.h
    ${INCLUDE_BASE}/astro/constants/math_constants.h
    ${INCLUDE_BASE}/astro/constants/rk_constants.h

    ${INCLUDE_BASE}/astro/element_sets/ElementSet.hpp
    ${INCLUDE_BASE}/astro/element_sets/Frame.hpp
    ${INCLUDE_BASE}/astro/element_sets/OrbitalElements.hpp

    ${INCLUDE_BASE}/astro/platforms/access/fov/FieldOfView.hpp
    ${INCLUDE_BASE}/astro/platforms/access/Antenna.hpp
    ${INCLUDE_BASE}/astro/platforms/access/Sensor.hpp

    ${INCLUDE_BASE}/astro/platforms/ground/GroundStation.hpp

    ${INCLUDE_BASE}/astro/platforms/space/Constellation.hpp
    ${INCLUDE_BASE}/astro/platforms/space/Plane.hpp
    ${INCLUDE_BASE}/astro/platforms/space/Shell.hpp
    ${INCLUDE_BASE}/astro/platforms/vehicles/Spacecraft.hpp
    ${INCLUDE_BASE}/astro/platforms/Vehicle.hpp

    ${INCLUDE_BASE}/astro/propagation/Integrator.hpp
    ${INCLUDE_BASE}/astro/propagation/LambertSolver.hpp

    ${INCLUDE_BASE}/astro/propagation/force_models/AtmosphericForce.hpp
    ${INCLUDE_BASE}/astro/propagation/force_models/Force.hpp
    ${INCLUDE_BASE}/astro/propagation/force_models/ForceModel.hpp
    ${INCLUDE_BASE}/astro/propagation/force_models/NBodyForce.hpp
    ${INCLUDE_BASE}/astro/propagation/force_models/OblatenessForce.hpp
    ${INCLUDE_BASE}/astro/propagation/force_models/SolarRadiationPressureForce.hpp

    ${INCLUDE_BASE}/astro/propagation/equations_of_motion/KeplerianVop.hpp
    ${INCLUDE_BASE}/astro/propagation/equations_of_motion/CowellsMethod.hpp
    ${INCLUDE_BASE}/astro/propagation/equations_of_motion/EquationsOfMotion.hpp
    ${INCLUDE_BASE}/astro/propagation/equations_of_motion/J2MeanVop.hpp
    ${INCLUDE_BASE}/astro/propagation/equations_of_motion/EquinoctialVop.hpp
    ${INCLUDE_BASE}/astro/propagation/equations_of_motion/TwoBody.hpp

    ${INCLUDE_BASE}/astro/systems/AstrodynamicsSystem.hpp
    ${INCLUDE_BASE}/astro/systems/Barycenter.hpp
    ${INCLUDE_BASE}/astro/systems/CelestialBody.hpp
    ${INCLUDE_BASE}/astro/systems/CelestialBodyFactory.hpp

    ${INCLUDE_BASE}/astro/time/Date.hpp
    ${INCLUDE_BASE}/astro/time/Interval.hpp
    ${INCLUDE_BASE}/astro/time/JulianDateClock.hpp
    ${INCLUDE_BASE}/astro/time/time_units.hpp
    ${INCLUDE_BASE}/astro/time/Time.hpp
    ${INCLUDE_BASE}/astro/time/access/AccessArray.hpp
    ${INCLUDE_BASE}/astro/time/access/RiseSetArray.hpp

    ${INCLUDE_BASE}/astro/types/typedefs.hpp
    ${INCLUDE_BASE}/astro/types/tuple_hash.hpp

    ${INCLUDE_BASE}/astro/utilities/conversions.hpp
    ${INCLUDE_BASE}/astro/utilities/riseset_utils.hpp
    ${INCLUDE_BASE}/astro/utilities/math/math_c.hpp
    ${INCLUDE_BASE}/astro/utilities/math/interpolation.hpp

    ${INCLUDE_BASE}/astro/State.hpp

    # Extern
    ${INCLUDE_BASE}/extern/nlohmann/json.hpp
)