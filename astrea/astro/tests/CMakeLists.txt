# Copyright (c) 2025 Jay Iuliano
#
# This file is part of Astrea.
# Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
# Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
# have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.28.3)

set(CMAKE_INSTALL_MESSAGE LAZY)

# Option to control whether to run 6DOF checkcases (can be slow)
if(NOT DEFINED RUN_6DOF_CHECKCASES)
    set(RUN_6DOF_CHECKCASES ON CACHE BOOL "Run NASA 6DOF checkcase tests")
endif()

# Add profilers and checkcase tests
if(${BUILD_PROFILERS})
    add_subdirectory(tests/profiling)
endif()

if(${BUILD_CHECKCASE_DATABASE})
    add_subdirectory(tests/nasa_6dof_checkcases)
endif()

# Get sources
set(BASE ${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_NAME})
file(GLOB_RECURSE UNIT_TEST_SOURCES CONFIGURE_DEPENDS ${BASE}/*.test.cpp ${BASE}/**/*.test.cpp)
file(GLOB_RECURSE REGRESSION_TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/**/driver.cpp)

# Filter out 6DOF checkcase tests if RUN_6DOF_CHECKCASES is OFF
if(NOT ${RUN_6DOF_CHECKCASES})
    list(FILTER REGRESSION_TEST_SOURCES EXCLUDE REGEX "nasa_6dof_checkcases")
endif()

# Set install rpath
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH}:\$ORIGIN/../lib")

# Target for all tests
add_custom_target(${PROJECT_NAME}_tests)
add_dependencies(${PROJECT_NAME}_tests ${PROJECT_NAME}_shared)

# Helper files
set(HELPER_HEADERS
    ${BASE}/../tests/utilities/comparisons.hpp
    ${BASE}/../tests/nasa_6dof_checkcases/helpers/AtmosphericCheckcase.hpp
    ${BASE}/../tests/nasa_6dof_checkcases/helpers/CheckcaseDatabase.hpp
    ${BASE}/../tests/nasa_6dof_checkcases/helpers/OrbitalCheckcase.hpp
)

set(HELPER_SOURCES
    ${BASE}/../tests/utilities/comparisons.cpp
    ${BASE}/../tests/nasa_6dof_checkcases/helpers/AtmosphericCheckcase.cpp
    ${BASE}/../tests/nasa_6dof_checkcases/helpers/OrbitalCheckcase.cpp
)

# Build
build_tests(${PROJECT_NAME} "UNIT" "${UNIT_TEST_SOURCES}" "${HELPER_HEADERS}" "${HELPER_SOURCES}")
build_tests(${PROJECT_NAME} "REGRESSION" "${REGRESSION_TEST_SOURCES}" "${HELPER_HEADERS}" "${HELPER_SOURCES}")