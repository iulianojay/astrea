
cmake_minimum_required(VERSION 3.31.6)

project(
    access 
    VERSION 0.0.1 
    DESCRIPTION "Library for Access-Based Simulation and Analysis" 
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

# Objects
set(ACCESS_BASE ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME})
set(ACCESS_SOURCES
    ${ACCESS_BASE}/access.cpp

    ${ACCESS_BASE}/platforms/Sensor.cpp
    ${ACCESS_BASE}/platforms/ground/GroundStation.cpp
    ${ACCESS_BASE}/platforms/fov/FieldOfView.cpp

    ${ACCESS_BASE}/time/RiseSetArray.cpp
)

# Headers
set(ACCESS_HEADERS
    ${ACCESS_BASE}/access.hpp

    ${ACCESS_BASE}/platforms/Antenna.hpp
    ${ACCESS_BASE}/platforms/Sensor.hpp
    ${ACCESS_BASE}/platforms/ground/GroundStation.hpp
    ${ACCESS_BASE}/platforms/fov/FieldOfView.hpp
    ${ACCESS_BASE}/platforms/vehicles/Viewer.hpp

    ${ACCESS_BASE}/time/AccessArray.hpp
    ${ACCESS_BASE}/time/RiseSetArray.hpp
    ${ACCESS_BASE}/time/riseset_utils.hpp
)

# Set outputs
set(INSTALL_PATHING install/${CMAKE_HOST_SYSTEM_PROCESSOR}-${CMAKE_SYSTEM_NAME}/${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}/${CMAKE_BUILD_TYPE})
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/${INSTALL_PATHING})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)

# Dependencies
if (PROJECT_IS_TOP_LEVEL) 
    set(MATH_BASE ${CMAKE_SOURCE_DIR}/../math)
    set(ASTRO_BASE ${CMAKE_SOURCE_DIR}/../astro)
else()
    set(MATH_BASE ${CMAKE_SOURCE_DIR}/newtool/math)
    set(ASTRO_BASE ${CMAKE_SOURCE_DIR}/newtool/astro)
endif()
find_package(math REQUIRED PATHS ${MATH_BASE}/${INSTALL_PATHING})
find_package(astro REQUIRED PATHS ${ASTRO_BASE}/${INSTALL_PATHING})

# Includes
set(ACCESS_DIRS
    ${CMAKE_CURRENT_LIST_DIR}
    ${EXTERN_BASE}
    ${MATH_BASE}/${INSTALL_PATHING}/include
    ${ASTRO_BASE}/${INSTALL_PATHING}/include
)
include_directories(${ACCESS_DIRS})

# Shared library
add_library           (${PROJECT_NAME}_shared SHARED ${ACCESS_SOURCES} ${ACCESS_HEADERS})
set_target_properties (${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)

# Static library
add_library           (${PROJECT_NAME}_static STATIC ${ACCESS_SOURCES} ${ACCESS_HEADERS})
set_target_properties (${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1 SUFFIX .a.${PROJECT_VERSION})

# Install and export the targets.
file(COPY
    DIRECTORY ${ACCESS_BASE}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING
    PATTERN *.hpp
    PATTERN *.h
)
install(
    TARGETS ${PROJECT_NAME}_shared ${PROJECT_NAME}_static
    EXPORT ${PROJECT_NAME}Config
    ARCHIVE DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
    LIBRARY DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
    RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

export(
    TARGETS ${PROJECT_NAME}_shared ${PROJECT_NAME}_static
    NAMESPACE ${PROJECT_NAME}::
    FILE "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}Config.cmake"
)

install(
    EXPORT ${PROJECT_NAME}Config
    DESTINATION "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/cmake"
    NAMESPACE ${PROJECT_NAME}::
)