
cmake_minimum_required(VERSION 3.16.3)

project(astro_test VERSION 1.0.0 DESCRIPTION "C++ astodynamics library" LANGUAGES C CXX)

set(CMAKE_C_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Fetch Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(TEST_NAME TwoBodyTest)
set(TEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(BINPATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBPATH ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
set(INCLUDEPATH ${CMAKE_CURRENT_SOURCE_DIR}/../include/)

set(INCLUDE_DIRS 
    ${INCLUDEPATH}
    ${INCLUDEPATH}/astro
    ${INCLUDEPATH}/astro/constants
    ${INCLUDEPATH}/astro/element_sets
    ${INCLUDEPATH}/astro/propagation
    ${INCLUDEPATH}/astro/systems
    ${INCLUDEPATH}/astro/time
    ${INCLUDEPATH}/astro/types
    ${INCLUDEPATH}/astro/utilities
)

# Find library
find_library(ASTROLIB libastro.so PATHS ${LIBPATH})

# Build test executable
add_executable             (${TEST_NAME} ${TEST_ROOT}/test_dynamics.cpp)
set_target_properties      (${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BINPATH} VERSION ${PROJECT_VERSION} OUTPUT_NAME ${TEST_NAME} CLEAN_DIRECT_OUTPUT 1)
target_include_directories (${TEST_NAME} PUBLIC ${INCLUDE_DIRS})
add_dependencies           (${TEST_NAME} GTest::gtest_main)
target_link_libraries      (${TEST_NAME} ${ASTROLIB} GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
