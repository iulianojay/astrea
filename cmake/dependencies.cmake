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
FetchContent_Declare(
    sqlite3
    URL https://www.sqlite.org/2026/sqlite-amalgamation-3510200.zip
)

FetchContent_MakeAvailable(sqlite3)

add_library(sqlite3 STATIC
    ${sqlite3_SOURCE_DIR}/sqlite3.c
)

target_include_directories(sqlite3
    PUBLIC ${sqlite3_SOURCE_DIR}
)

# Tell FindSQLite3.cmake exactly where SQLite is
set(SQLite3_INCLUDE_DIR
    ${sqlite3_SOURCE_DIR}
    CACHE PATH "SQLite3 include directory"
)

set(SQLite3_LIBRARY
    sqlite3
    CACHE STRING "SQLite3 library"
)
add_library(SQLite3::SQLite3 ALIAS sqlite3)
set(SQLite3_FOUND TRUE)

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
CPMFindPackage(
    NAME sqlite_orm
    GITHUB_REPOSITORY fnc12/sqlite_orm
    GIT_TAG v1.9.1
    GIT_SHALLOW TRUE
)

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

# Date for literally just like one thing please standards committee, adopt this
CPMFindPackage(
    NAME date
    GITHUB_REPOSITORY HowardHinnant/date
    GIT_TAG v3.0.1
    GIT_SHALLOW TRUE
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