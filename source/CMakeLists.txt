# Objects
set(SOURCE_BASE ${CMAKE_SOURCE_DIR}/source)
set(SOURCES
    ${SOURCE_BASE}/access/access.cpp

    ${SOURCE_BASE}/element_sets/OrbitalElements.cpp

    ${SOURCE_BASE}/platforms/access/fov/FieldOfView.cpp
    ${SOURCE_BASE}/platforms/access/Sensor.cpp

    ${SOURCE_BASE}/platforms/ground/GroundStation.cpp

    ${SOURCE_BASE}/platforms/space/Constellation.cpp
    ${SOURCE_BASE}/platforms/space/Plane.cpp
    ${SOURCE_BASE}/platforms/space/Shell.cpp
    ${SOURCE_BASE}/platforms/vehicles/Spacecraft.cpp
    ${SOURCE_BASE}/platforms/Vehicle.cpp

    ${SOURCE_BASE}/propagation/Integrator.cpp
    ${SOURCE_BASE}/propagation/LambertSolver.cpp

    ${SOURCE_BASE}/propagation/force_models/AtmosphericForce.cpp
    ${SOURCE_BASE}/propagation/force_models/NBodyForce.cpp
    ${SOURCE_BASE}/propagation/force_models/OblatenessForce.cpp
    ${SOURCE_BASE}/propagation/force_models/SolarRadiationPressureForce.cpp

    ${SOURCE_BASE}/propagation/equations_of_motion/KeplerianVop.cpp
    ${SOURCE_BASE}/propagation/equations_of_motion/CowellsMethod.cpp
    ${SOURCE_BASE}/propagation/equations_of_motion/J2MeanVop.cpp
    ${SOURCE_BASE}/propagation/equations_of_motion/EquinoctialVop.cpp
    ${SOURCE_BASE}/propagation/equations_of_motion/TwoBody.cpp

    ${SOURCE_BASE}/systems/AstrodynamicsSystem.cpp
    ${SOURCE_BASE}/systems/CelestialBody.cpp
    ${SOURCE_BASE}/systems/CelestialBodyFactory.cpp

    ${SOURCE_BASE}/time/Time.cpp
    ${SOURCE_BASE}/time/access/RiseSetArray.cpp

    ${SOURCE_BASE}/utilities/conversions.cpp
    ${SOURCE_BASE}/utilities/riseset_utils.cpp
    ${SOURCE_BASE}/utilities/math/math_c.cpp
    ${SOURCE_BASE}/utilities/math/interpolation.cpp

    ${SOURCE_BASE}/State.cpp
)

include(${CMAKE_SOURCE_DIR}/cmake/astro_config.cmake)

# Set outputs
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)

# Shared library
add_library                (${PROJECT_NAME}_shared SHARED ${SOURCES} ${HEADERS})
set_target_properties      (${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_include_directories (${PROJECT_NAME}_shared PUBLIC ${INCLUDE_DIRS})

# Static library
add_library                (${PROJECT_NAME}_static STATIC ${SOURCES} ${HEADERS})
set_target_properties      (${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_include_directories (${PROJECT_NAME}_static PUBLIC ${INCLUDE_DIRS})

# Executable
add_executable             (${PROJECT_NAME} ${SOURCE_BASE}/main.cpp)
set_target_properties      (${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
target_include_directories (${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_link_libraries      (${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_shared)
add_dependencies           (${PROJECT_NAME} ${PROJECT_NAME}_shared)

# Copy include
file(COPY
    DIRECTORY ${INCLUDE_BASE}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING
    PATTERN *.hpp
)

if (BUILD_SWIG)
    include(config/swig.cmake)
endif()