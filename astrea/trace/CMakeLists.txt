# Copyright (c) 2025 Jay Iuliano
#
# This file is part of Astrea.
# Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
# Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
# have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.28.3)

project(
    trace
    VERSION ${ASTREA_VERSION}
    DESCRIPTION "Library for Trace-Based Simulation and Analysis"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

# Objects
set(TRACE_BASE ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME})
set(TRACE_SOURCES
    ${TRACE_BASE}/analysis/access_analysis.cpp

    ${TRACE_BASE}/platforms/sensors/Antenna.cpp
    ${TRACE_BASE}/platforms/sensors/Sensor.cpp

    ${TRACE_BASE}/platforms/ground/Grid.cpp
    ${TRACE_BASE}/platforms/ground/GroundStation.cpp

    ${TRACE_BASE}/platforms/sensors/fov/FieldOfView.cpp
    ${TRACE_BASE}/platforms/sensors/fov/instances/CircularFieldOfView.cpp
    ${TRACE_BASE}/platforms/sensors/fov/instances/PolygonalFieldOfView.cpp

    ${TRACE_BASE}/risesets/AccessArray.cpp
    ${TRACE_BASE}/risesets/RiseSetArray.cpp
    ${TRACE_BASE}/risesets/riseset_utils.cpp
)

# Headers
set(TRACE_HEADERS
    ${TRACE_BASE}/trace.hpp

    ${TRACE_BASE}/analysis/access_analysis.hpp

    ${TRACE_BASE}/platforms/sensors/Antenna.hpp
    ${TRACE_BASE}/platforms/sensors/Sensor.hpp
    ${TRACE_BASE}/platforms/sensors/fov/FieldOfView.hpp
    ${TRACE_BASE}/platforms/sensors/fov/instances/CircularFieldOfView.hpp
    ${TRACE_BASE}/platforms/sensors/fov/instances/PolygonalFieldOfView.hpp

    ${TRACE_BASE}/platforms/ground/Grid.hpp
    ${TRACE_BASE}/platforms/ground/GroundArchitecture.hpp
    ${TRACE_BASE}/platforms/ground/GroundPoint.hpp
    ${TRACE_BASE}/platforms/ground/GroundStation.hpp

    ${TRACE_BASE}/platforms/vehicles/Viewer.hpp

    ${TRACE_BASE}/risesets/AccessArray.hpp
    ${TRACE_BASE}/risesets/RiseSetArray.hpp
    ${TRACE_BASE}/risesets/riseset_utils.hpp

    ${TRACE_BASE}/types/typedefs.hpp
)

# Includes
set(TRACE_DIRS
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../math
    ${CMAKE_CURRENT_LIST_DIR}/../astro
    ${CMAKE_CURRENT_LIST_DIR}/../snapshot
    ${CMAKE_CURRENT_LIST_DIR}/../units
    ${CMAKE_CURRENT_LIST_DIR}/../utilities
)

# Find library
set(TRACE_LIBS
    mp-units::mp-units
    matplot
    nlohmann_json::nlohmann_json
    csv
    sqlite_orm::sqlite_orm
    date::date
)

# Shared library
add_library                (${PROJECT_NAME}_shared SHARED ${TRACE_SOURCES} ${TRACE_HEADERS})
set_target_properties      (${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_link_libraries      (${PROJECT_NAME}_shared PUBLIC math_shared astro_shared ${TRACE_LIBS})
target_include_directories (${PROJECT_NAME}_shared PUBLIC ${TRACE_DIRS})
target_compile_definitions (${PROJECT_NAME}_shared PUBLIC "_TRACE_ROOT_=\"${CMAKE_CURRENT_LIST_DIR}\"")

# Static library
if(${BUILD_STATIC})
    add_library                (${PROJECT_NAME}_static STATIC ${TRACE_SOURCES} ${TRACE_HEADERS})
    set_target_properties      (${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1 SUFFIX .a.${PROJECT_VERSION})
    target_link_libraries      (${PROJECT_NAME}_static PUBLIC math_static astro_static ${TRACE_LIBS})
    target_include_directories (${PROJECT_NAME}_static PUBLIC ${TRACE_DIRS})
    target_compile_definitions (${PROJECT_NAME}_static PUBLIC "_TRACE_ROOT_=\"${CMAKE_CURRENT_LIST_DIR}\"")
endif()

# Executable
add_executable             (${PROJECT_NAME}_exe ${TRACE_BASE}/drivers/main.cpp)
set_target_properties      (${PROJECT_NAME}_exe PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_include_directories (${PROJECT_NAME}_exe PUBLIC ${TRACE_DIRS})
target_link_libraries      (${PROJECT_NAME}_exe PUBLIC ${PROJECT_NAME}_shared snapshot_shared)
target_compile_options     (${PROJECT_NAME}_exe PUBLIC -Wno-unused-local-typedefs -Wno-uninitialized -Wno-maybe-uninitialized)
add_custom_target          (${PROJECT_NAME}_exe_symlink ALL COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_NAME}_exe ${PROJECT_NAME})

# Install headers
file(COPY
    DIRECTORY ${TRACE_BASE}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING
    PATTERN *.hpp
    PATTERN *.h
)

# add_subdirectory(examples EXCLUDE_FROM_ALL)
if(${BUILD_TESTS})
    add_subdirectory(tests)
endif()