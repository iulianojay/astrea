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

# Get sources
set(BASE ${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_NAME})
file(GLOB_RECURSE UNIT_TEST_SOURCES CONFIGURE_DEPENDS ${BASE}/*.test.cpp ${BASE}/**/*.test.cpp)
file(GLOB_RECURSE REGRESSION_TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/**/driver.cpp)

# Set install rpath
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH}:\$ORIGIN/../lib")

# Target for all tests
add_custom_target(${PROJECT_NAME}_tests)
add_dependencies(${PROJECT_NAME}_tests ${PROJECT_NAME}_shared)

# Helper files
set(HELPER_HEADERS
)

set(HELPER_SOURCES
)

# Add subdirectories for regressions
# add_subdirectory(some-regression-test)
build_tests(${PROJECT_NAME} "UNIT" "${UNIT_TEST_SOURCES}" "${HELPER_HEADERS}" "${HELPER_SOURCES}")

# build_tests("REGRESSION" "${REGRESSION_TEST_SOURCES}" "${HELPER_HEADERS}" "${HELPER_SOURCES}")