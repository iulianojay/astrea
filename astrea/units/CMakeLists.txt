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
    "units"
    VERSION ${ASTREA_VERSION}
    DESCRIPTION "Library for Utilities for United Types"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

# Objects
set(UNITS_BASE ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME})
set(UNITS_SOURCES
)

# Headers
set(UNITS_HEADERS
    ${UNITS_BASE}/constants.hpp
    ${UNITS_BASE}/custom.hpp
    ${UNITS_BASE}/detail.hpp
    ${UNITS_BASE}/hash.hpp
    ${UNITS_BASE}/time.hpp
    ${UNITS_BASE}/typedefs.hpp
)

# Includes
set(UNITS_DIRS
    ${CMAKE_CURRENT_LIST_DIR}
)

# Find library
set(UNITS_LIBS
    mp-units::mp-units
)

# Shared library
add_library                (${PROJECT_NAME}_shared SHARED ${UNITS_SOURCES} ${UNITS_HEADERS})
set_target_properties      (${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_link_libraries      (${PROJECT_NAME}_shared PUBLIC ${UNITS_LIBS})
target_include_directories (${PROJECT_NAME}_shared PUBLIC ${UNITS_DIRS})

# Static library
if(${BUILD_STATIC})
    add_library                (${PROJECT_NAME}_static STATIC ${UNITS_SOURCES} ${UNITS_HEADERS})
    set_target_properties      (${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1 SUFFIX .a.${PROJECT_VERSION})
    target_link_libraries      (${PROJECT_NAME}_static PUBLIC ${UNITS_LIBS})
    target_include_directories (${PROJECT_NAME}_static PUBLIC ${UNITS_DIRS})
endif()

file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/include)

# Install headers
file(COPY
    DIRECTORY ${UNITS_BASE}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING
    PATTERN *.hpp
    PATTERN *.h
)

# add_subdirectory(examples EXCLUDE_FROM_ALL)
# if(${BUILD_TESTS})
# add_subdirectory(tests)
# endif()