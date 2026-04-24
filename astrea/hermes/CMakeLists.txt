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
    hermes
    VERSION ${ASTREA_VERSION}
    DESCRIPTION "Transfer Optimization Library"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

# Objects
set(HERMES_BASE ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME})
set(HERMES_SOURCES
    ${HERMES_BASE}/sims-flanagan/Subsegment.cpp
    ${HERMES_BASE}/sims-flanagan/Segment.cpp
    ${HERMES_BASE}/sims-flanagan/Trajectory.cpp
)

# Headers
set(HERMES_HEADERS
    ${HERMES_BASE}/hermes.hpp
    ${HERMES_BASE}/hermes.fwd.hpp

    ${HERMES_BASE}/sims-flanagan/Node.hpp
    ${HERMES_BASE}/sims-flanagan/Subsegment.hpp
    ${HERMES_BASE}/sims-flanagan/Segment.hpp
    ${HERMES_BASE}/sims-flanagan/Trajectory.hpp
)

# Includes
set(HERMES_DIRS
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../math
    ${CMAKE_CURRENT_LIST_DIR}/../astro
    ${CMAKE_CURRENT_LIST_DIR}/../units
    ${CMAKE_CURRENT_LIST_DIR}/../utilities
)
include_directories(${HERMES_DIRS})

# Find library
set(HERMES_LIBS
    mp-units::mp-units
    pagmo::pagmo
)

# Shared library
add_library(${PROJECT_NAME}_shared SHARED ${HERMES_SOURCES} ${HERMES_HEADERS})

if(${BUILD_EPHEMERIDES})
    add_dependencies(${PROJECT_NAME}_shared generated_ephemerides)
endif()

set_target_properties(${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_link_libraries(${PROJECT_NAME}_shared PUBLIC astro_shared math_shared utilities_shared ${HERMES_LIBS})
target_include_directories(${PROJECT_NAME}_shared PUBLIC ${HERMES_DIRS} ${CMAKE_CURRENT_BINARY_DIR}/include)
target_compile_definitions(${PROJECT_NAME}_shared PUBLIC ${EPHEMERIS_COMPILE_DEFINES} "_HERMES_ROOT_=\"${CMAKE_CURRENT_LIST_DIR}\"")

# Static library
if(${BUILD_STATIC})
    add_library(${PROJECT_NAME}_static STATIC ${HERMES_SOURCES} ${HERMES_HEADERS})

    if(${BUILD_EPHEMERIDES})
        add_dependencies(${PROJECT_NAME}_static generated_ephemerides)
    endif()

    set_target_properties(${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1 SUFFIX .a.${PROJECT_VERSION})
    target_link_libraries(${PROJECT_NAME}_static PUBLIC astro_static math_static utilities_static ${HERMES_LIBS})
    target_include_directories(${PROJECT_NAME}_static PUBLIC ${HERMES_DIRS} ${CMAKE_CURRENT_BINARY_DIR}/include)
    target_compile_definitions(${PROJECT_NAME}_static PUBLIC ${EPHEMERIS_COMPILE_DEFINES} "_HERMES_ROOT_=\"${CMAKE_CURRENT_LIST_DIR}\"")
endif()

# Install headers
install(
    DIRECTORY ${HERMES_BASE}
    DESTINATION include
    FILES_MATCHING
    PATTERN *.hpp
    PATTERN *.ipp
    PATTERN *.h
)

# if(${BUILD_EXAMPLES})
# add_subdirectory(examples)
# endif()
if(${BUILD_TESTS})
    add_subdirectory(tests)
endif()