
cmake_minimum_required(VERSION 3.28.3)

project(
    waveguide 
    VERSION 0.0.1 
    DESCRIPTION "Waveguide: Nebula Back-End Simulation Library" 
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INSTALL_MESSAGE LAZY)

# add_library(waveguide_warnings INTERFACE)
# add_library(waveguide_options INTERFACE)

# if (PROJECT_IS_TOP_LEVEL) 
#     include(cmake/standard_project_settings.cmake)
#     if (WARNINGS_AS_ERRORS)
#         include(cmake/compiler_warnings.cmake)
#     endif()
# endif()

# target_compile_features(waveguide_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

if (CMAKE_COMPILER_IS_GNUCXX AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13.1.0)
    message(FATAL_ERROR "GCC 13.1.0 or greater required.")
endif()


include(cmake/functions.cmake)

# Include dependencies
find_package(mp-units REQUIRED)
find_package(SQLite3 REQUIRED)

include(FetchContent)
FetchContent_Declare(
    cpr 
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG dd967cb48ea6bcbad9f1da5ada0db8ac0d532c06
) # Replace with your desired git commit from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(
    sqlite_orm 
    GIT_REPOSITORY https://github.com/fnc12/sqlite_orm.git 
    GIT_TAG v1.9.1
)
FetchContent_MakeAvailable(sqlite_orm)

# Add google test
set(INSTALL_GTEST OFF)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

# Get code
add_subdirectory(waveguide)
