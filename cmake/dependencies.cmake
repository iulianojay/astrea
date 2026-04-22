# Copyright (c) 2025 Jay Iuliano
#
# This file is part of Astrea.
# Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
# Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
# have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.

include(cmake/CPM.cmake)
include(FetchContent)

# SQLite3 for databases
# Try to find system SQLite3 first, otherwise fetch amalgamation from source
find_package(SQLite3 QUIET)
if(NOT SQLite3_FOUND)
    message(STATUS "SQLite3 not found on system, fetching amalgamation from source...")

    # Download SQLite amalgamation (pre-processed single file distribution)
    CPMAddPackage(
        NAME sqlite3_amalgamation
        URL https://www.sqlite.org/2024/sqlite-amalgamation-3470200.zip
        DOWNLOAD_ONLY YES
    )

    if(sqlite3_amalgamation_ADDED)
        # Create SQLite3 library from amalgamation
        add_library(SQLite3 SHARED
            ${sqlite3_amalgamation_SOURCE_DIR}/sqlite3.c
        )

        target_include_directories(SQLite3 PUBLIC
            $<BUILD_INTERFACE:${sqlite3_amalgamation_SOURCE_DIR}>
            $<INSTALL_INTERFACE:include>
        )

        # Set compile definitions
        target_compile_definitions(SQLite3 PRIVATE
            SQLITE_ENABLE_COLUMN_METADATA
            SQLITE_ENABLE_FTS5
            SQLITE_ENABLE_RTREE
        )

        # Windows-specific: Let CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS handle DLL exports
        if(WIN32)
            set_target_properties(SQLite3 PROPERTIES
                WINDOWS_EXPORT_ALL_SYMBOLS ON
            )
        endif()

        # Set properties
        set_target_properties(SQLite3 PROPERTIES
            OUTPUT_NAME sqlite3
            VERSION 3.47.2
            SOVERSION 0
        )

        # Create alias to match find_package result
        add_library(SQLite::SQLite3 ALIAS SQLite3)

        # Set variables that find_package would set
        set(SQLite3_FOUND TRUE CACHE BOOL "SQLite3 found")
        set(SQLite3_INCLUDE_DIR ${sqlite3_amalgamation_SOURCE_DIR} CACHE PATH "SQLite3 include directory")
        set(SQLite3_LIBRARY SQLite3 CACHE STRING "SQLite3 library")
        set(SQLite3_LIBRARIES SQLite::SQLite3 CACHE STRING "SQLite3 libraries")

        # Export for subdirectories
        mark_as_advanced(SQLite3_INCLUDE_DIR SQLite3_LIBRARY SQLite3_LIBRARIES)
    endif()
endif()

# MP-Units dependency that I need to install for some reason
add_compile_definitions(gsl_FEATURE_GSL_COMPATIBILITY_MODE=1)
CPMFindPackage(
    NAME gsl-lite
    VERSION 1.0.1
    GITHUB_REPOSITORY gsl-lite/gsl-lite
)

# Units
CPMFindPackage(
    NAME mp-units
    VERSION 2.5.0
    GITHUB_REPOSITORY mpusz/mp-units
    GIT_SHALLOW TRUE
    SOURCE_SUBDIR src
    SYSTEM YES
    EXCLUDE_FROM_ALL YES
    OPTIONS
    "MP_UNITS_BUILD_INSTALL OFF"
)

# Patch mp-units for MSVC C++23 compatibility - remove constexpr from template specializations
if(MSVC AND mp-units_ADDED)
    file(READ "${mp-units_SOURCE_DIR}/src/systems/include/mp-units/systems/angular/units.h" MP_UNITS_ANGULAR_CONTENT)
    string(REPLACE "MP_UNITS_INLINE constexpr bool space_before_unit_symbol" "MP_UNITS_INLINE bool space_before_unit_symbol" MP_UNITS_ANGULAR_CONTENT "${MP_UNITS_ANGULAR_CONTENT}")
    file(WRITE "${mp-units_SOURCE_DIR}/src/systems/include/mp-units/systems/angular/units.h" "${MP_UNITS_ANGULAR_CONTENT}")
endif()

# CPR for HTTP requests
CPMFindPackage(
    NAME cpr
    GITHUB_REPOSITORY libcpr/cpr
    GIT_TAG 1.11.0
    GIT_SHALLOW TRUE
    OPTIONS
    "CPR_BUILD_TESTS OFF"
    "BUILD_SHARED_LIBS ON"
)

# SQLite ORM for better interaction with SQLite
# Download only, we'll configure it manually to avoid its dependency search
CPMAddPackage(
    NAME sqlite_orm
    GITHUB_REPOSITORY fnc12/sqlite_orm
    GIT_TAG v1.9.1
    GIT_SHALLOW TRUE
    DOWNLOAD_ONLY YES
)

if(sqlite_orm_ADDED)
    # Create header-only interface library for sqlite_orm
    add_library(sqlite_orm INTERFACE)
    target_include_directories(sqlite_orm INTERFACE
        $<BUILD_INTERFACE:${sqlite_orm_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )

    # Link to our SQLite3 target
    if(TARGET SQLite3)
        target_link_libraries(sqlite_orm INTERFACE SQLite::SQLite3)
    endif()

    # Set compile features
    target_compile_features(sqlite_orm INTERFACE cxx_std_20)

    # Create alias for consistency
    add_library(sqlite_orm::sqlite_orm ALIAS sqlite_orm)
endif()

# Matplot++ for plotting
CPMFindPackage(
    NAME matplotplusplus
    GITHUB_REPOSITORY alandefreitas/matplotplusplus
    GIT_TAG v1.2.2
    GIT_SHALLOW TRUE
    OPTIONS
    "MATPLOTPP_BUILD_EXAMPLES OFF"
    "MATPLOTPP_BUILD_SHARED_LIBS ON"
    "MATPLOTPP_BUILD_TESTS OFF"
)

# JSON parsing that doesn't suck
CPMFindPackage(
    NAME nlohmann_json
    VERSION 3.11.3
    GITHUB_REPOSITORY nlohmann/json
    GIT_SHALLOW TRUE
)

# For fast maps
CPMFindPackage(
    NAME gtl
    GITHUB_REPOSITORY greg7mdp/gtl
    GIT_SHALLOW TRUE
    GIT_TAG v1.2.0
)

# CSV Parsing that sucks less
# Doesn't follow standard versioning so use FetchContent
FetchContent_Declare(
    csv
    GIT_REPOSITORY https://github.com/vincentlaucsb/csv-parser.git
    GIT_SHALLOW TRUE
    GIT_TAG 2.3.0
)
FetchContent_MakeAvailable(csv)

# Google test cause I Love massive endless macro heavy tools
CPMFindPackage(
    NAME googletest
    GITHUB_REPOSITORY google/googletest
    GIT_SHALLOW TRUE
    VERSION 1.17.0
    OPTIONS
    "INSTALL_GTEST OFF"
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
include(GoogleTest)
enable_testing()