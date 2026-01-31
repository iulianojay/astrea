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
set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
set(CMAKE_SKIP_BUILD_RPATH ON)
set(CMAKE_INSTALL_MESSAGE LAZY)

add_compile_definitions(gsl_FEATURE_GSL_COMPATIBILITY_MODE=1)

include(cmake/standard_project_settings.cmake)
include(cmake/CPM.cmake)

# add_library(astrea_warnings INTERFACE)
# add_library(astrea_options INTERFACE)

# target_compile_features(astrea_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})
if(CMAKE_COMPILER_IS_GNUCXX AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13.1.0)
    message(FATAL_ERROR "GCC 13.1.0 or greater required.")
endif()

# Include dependencies
find_package(SQLite3 REQUIRED)

CPMFindPackage(
    NAME gsl-lite
    VERSION 1.0.1
    GITHUB_REPOSITORY gsl-lite/gsl-lite
)

CPMFindPackage(
    NAME mp-units
    VERSION 2.5.0
    GITHUB_REPOSITORY mpusz/mp-units
    SOURCE_SUBDIR src
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
    OPTIONS
    "MP_UNITS_BUILD_INSTALL OFF"
)

CPMFindPackage(
    NAME cpr
    GITHUB_REPOSITORY libcpr/cpr
    GIT_TAG dd967cb48ea6bcbad9f1da5ada0db8ac0d532c06
)

CPMFindPackage(
    NAME sqlite_orm
    GITHUB_REPOSITORY fnc12/sqlite_orm
    GIT_TAG v1.9.1
)

CPMFindPackage(
    NAME matplotplusplus
    GITHUB_REPOSITORY alandefreitas/matplotplusplus
    GIT_TAG v1.2.2
)

CPMFindPackage(
    NAME date
    GITHUB_REPOSITORY HowardHinnant/date
    GIT_TAG v3.0.1
)

CPMFindPackage(
    NAME nlohmann_json
    VERSION 3.11.3
    GITHUB_REPOSITORY nlohmann/json
)

CPMFindPackage(
    NAME parallel-hashmap
    GITHUB_REPOSITORY greg7mdp/parallel-hashmap
    GIT_TAG v1.4.0
)

# Doesn't follow standard versioning so use FetchContent
include(FetchContent)
FetchContent_Declare(
    csv
    GIT_REPOSITORY https://github.com/vincentlaucsb/csv-parser.git
    GIT_SHALLOW TRUE
    GIT_TAG 2.3.0
)
FetchContent_MakeAvailable(csv)

# Add google test
set(INSTALL_GTEST OFF)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
CPMFindPackage(
    NAME googletest
    GITHUB_REPOSITORY google/googletest
    VERSION 1.17.0
    OPTIONS
    "INSTALL_GTEST OFF"
)

enable_testing()
include(GoogleTest)

# Get code
add_subdirectory(astrea)
