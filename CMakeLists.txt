# Copyright (c) 2025-2026 Jay Iuliano
#
# This file is part of Astrea.
# Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
# Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
# have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.28.3)

include(cmake/functions.cmake)
configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/version.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/version.hpp
)
get_version_from_git()

message(STATUS "Configuring Astrea version ${ASTREA_VERSION}")
project(
    astrea
    VERSION ${ASTREA_VERSION}
    DESCRIPTION "Astrea: Astrodynamics Back-End Simulation Library"
    LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INSTALL_MESSAGE LAZY)

# add_library(astrea_warnings INTERFACE)
# add_library(astrea_options INTERFACE)

# target_compile_features(astrea_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})
if(CMAKE_COMPILER_IS_GNUCXX AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 14.0.0)
    message(FATAL_ERROR "GCC 14.0.0 or greater required.")
endif()

# Include dependencies
include(cmake/dependencies.cmake)

# Settings after dependencies so there aren't 1000 warnings
include(cmake/standard_project_settings.cmake)

# Get code
add_subdirectory(astrea)

# Package config
include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/astreaConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/astreaConfig.cmake"
    INSTALL_DESTINATION lib/cmake/astrea
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/astreaConfigVersion.cmake"
    VERSION ${ASTREA_VERSION}
    COMPATIBILITY AnyNewerVersion
)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/astreaConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/astreaConfigVersion.cmake"
    DESTINATION lib/cmake/astrea
)
