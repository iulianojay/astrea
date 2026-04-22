# Copyright (c) 2025 Jay Iuliano
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
    DESCRIPTION "Astrea: Nebula Back-End Simulation Library"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INSTALL_MESSAGE LAZY)

# Windows DLL support
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    set(BUILD_SHARED_LIBS ON)
endif()

# Build options
option(BUILD_TESTS "Build test suite" OFF)
option(BUILD_EXAMPLES "Build example programs" OFF)
option(BUILD_STATIC "Build static libraries" OFF)
option(BUILD_PROFILERS "Build profiling tools" OFF)
option(BUILD_CHECKCASE_DATABASE "Build checkcase database" OFF)
option(RUN_6DOF_CHECKCASES "Run NASA 6DOF checkcase tests" OFF)

# Work around mp-units "constant" keyword issue with MSVC
if(MSVC)
    add_compile_definitions(_SILENCE_CXX23_DEPRECATION_WARNINGS)
endif()

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
