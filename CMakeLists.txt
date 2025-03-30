
cmake_minimum_required(VERSION 3.31.6)

project(
    newtool 
    VERSION 0.0.1 
    DESCRIPTION "New Tool Back-End Simulation Library" 
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(newtool_warnings INTERFACE)
add_library(newtool_options INTERFACE)

if (PROJECT_IS_TOP_LEVEL) 
    include(cmake/standard_project_settings.cmake)
    include(cmake/prevent_in_source_builds.cmake)
    if (WARNINGS_AS_ERRORS)
        include(cmake/compiler_warnings.cmake)
    endif()
endif()

target_compile_features(newtool_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

if (CMAKE_COMPILER_IS_GNUCXX AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13.1.0)
    message(FATAL_ERROR "GCC 13.1.0 or greater required.")
endif()

include(cmake/functions.cmake)

add_subdirectory(newtool)
