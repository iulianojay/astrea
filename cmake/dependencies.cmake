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

# ---- sqlite3 ----
# Always build SQLite3 from amalgamation for consistent dependency resolution
message(STATUS "Building SQLite3 from amalgamation source...")
CPMAddPackage(
    NAME sqlite3_amalgamation
    URL https://www.sqlite.org/2024/sqlite-amalgamation-3470200.zip
    DOWNLOAD_ONLY YES
)

if(sqlite3_amalgamation_ADDED)
    # Create SQLite3 library from amalgamation
    message(STATUS "Configuring SQLite3 from amalgamation source...")
    add_library(SQLite3 SHARED
        ${sqlite3_amalgamation_SOURCE_DIR}/sqlite3.c
    )
    target_include_directories(SQLite3 PUBLIC
        $<BUILD_INTERFACE:${sqlite3_amalgamation_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
    )
    target_compile_definitions(SQLite3 PRIVATE
        SQLITE_ENABLE_COLUMN_METADATA
        SQLITE_ENABLE_FTS5
        SQLITE_ENABLE_RTREE
    )
    if(WIN32)
        set_target_properties(SQLite3 PROPERTIES
            WINDOWS_EXPORT_ALL_SYMBOLS ON
        )
    endif()
    set_target_properties(SQLite3 PROPERTIES
        OUTPUT_NAME sqlite3
        VERSION 3.47.2
        SOVERSION 0
    )
    add_library(SQLite::SQLite3 ALIAS SQLite3)
    set(SQLite3_FOUND TRUE CACHE BOOL "SQLite3 found" FORCE)
    set(SQLite3_INCLUDE_DIR ${sqlite3_amalgamation_SOURCE_DIR} CACHE PATH "SQLite3 include directory" FORCE)
    set(SQLite3_LIBRARY SQLite3 CACHE STRING "SQLite3 library" FORCE)
    set(SQLite3_LIBRARIES SQLite::SQLite3 CACHE STRING "SQLite3 libraries" FORCE)
    mark_as_advanced(SQLite3_INCLUDE_DIR SQLite3_LIBRARY SQLite3_LIBRARIES)

    # Install and export the custom SQLite3 target for downstream usage
    install(TARGETS SQLite3 EXPORT SQLite3Targets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
    )
    install(DIRECTORY ${sqlite3_amalgamation_SOURCE_DIR}/ DESTINATION include FILES_MATCHING PATTERN "sqlite3.h" PATTERN "sqlite3ext.h")
    install(EXPORT SQLite3Targets NAMESPACE SQLite:: DESTINATION lib/cmake/SQLite3)
endif()

# MP-Units dependency that I need to install for some reason
add_compile_definitions(gsl_FEATURE_GSL_COMPATIBILITY_MODE=1)
CPMFindPackage(
    NAME gsl-lite
    VERSION 1.1.0
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
if(DEFINED mp-units_SOURCE_DIR)
    install(DIRECTORY "${mp-units_SOURCE_DIR}/src/core/include/" DESTINATION include)
    install(DIRECTORY "${mp-units_SOURCE_DIR}/src/systems/include/" DESTINATION include)
endif()

# CPR for HTTP requests
if(WIN32)
    # You need it for both linux and windows but this function breaks the build on linux and is required on windows
    find_package(CURL REQUIRED)
endif()
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
CPMFindPackage(
    NAME sqlite_orm
    GITHUB_REPOSITORY fnc12/sqlite_orm
    GIT_TAG v1.9.1
    GIT_SHALLOW TRUE
    SYSTEM YES
)

# Matplot++ for plotting
CPMFindPackage(
    NAME matplotplusplus
    GITHUB_REPOSITORY alandefreitas/matplotplusplus
    GIT_TAG v1.2.2 # Use latest stable release for better Windows DLL support
    GIT_SHALLOW TRUE
    OPTIONS
    "MATPLOTPP_BUILD_EXAMPLES OFF"
    "MATPLOTPP_BUILD_SHARED_LIBS ON"
    "MATPLOTPP_BUILD_TESTS OFF"
    "BUILD_SHARED_LIBS ON"
)
if(DEFINED matplotplusplus_SOURCE_DIR)
    install(DIRECTORY "${matplotplusplus_SOURCE_DIR}/source/matplot" DESTINATION include)
endif()

# JSON parsing that doesn't suck
CPMFindPackage(
    NAME nlohmann_json
    VERSION 3.12.0
    GITHUB_REPOSITORY nlohmann/json
    GIT_SHALLOW TRUE
)
if(DEFINED nlohmann_json_SOURCE_DIR)
    install(DIRECTORY "${nlohmann_json_SOURCE_DIR}/include/" DESTINATION include)
endif()

# For fast maps
CPMFindPackage(
    NAME gtl
    GITHUB_REPOSITORY greg7mdp/gtl
    GIT_SHALLOW TRUE
    GIT_TAG v1.2.0
)
if(DEFINED gtl_SOURCE_DIR)
    install(DIRECTORY "${gtl_SOURCE_DIR}/include/" DESTINATION include)
endif()

# constexpr math library
CPMFindPackage(
    NAME gcem
    GITHUB_REPOSITORY kthohr/gcem
    GIT_SHALLOW TRUE
    GIT_TAG v1.18.0
)

# CSV Parsing that sucks less
# Doesn't follow standard versioning so use FetchContent
FetchContent_Declare(
    csv
    GIT_REPOSITORY https://github.com/vincentlaucsb/csv-parser.git
    GIT_SHALLOW TRUE
    GIT_TAG 3.1.0
)
FetchContent_MakeAvailable(csv)

# Google test cause I Love massive endless macro heavy tools
if (${BUILD_TESTS})
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
endif()

if (${BUILD_BENCHMARKS})
    CPMFindPackage(
        NAME googlebenchmark
        GITHUB_REPOSITORY google/benchmark
        GIT_SHALLOW TRUE
        VERSION 1.9.5
        OPTIONS
        "BENCHMARK_DOWNLOAD_DEPENDENCIES ON"
    )
endif()