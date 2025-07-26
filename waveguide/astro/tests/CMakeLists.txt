cmake_minimum_required(VERSION 3.31.6)

set(CMAKE_INSTALL_MESSAGE LAZY)

# Get sources
set(BASE ${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_NAME})
file(GLOB_RECURSE UNIT_TEST_SOURCES ${BASE}/*.test.cpp ${BASE}/**/*.test.cpp)
file(GLOB_RECURSE REGRESSION_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/**/driver.cpp)

# Set install rpath
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH}:\$ORIGIN/../lib")

# Target for all tests
add_custom_target(${PROJECT_NAME}_tests)
add_dependencies(${PROJECT_NAME}_tests ${PROJECT_NAME}_shared)

# Add subdirectories for regressions
#add_subdirectory(some-regression-test)
        
# Add google test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/releases/download/v1.16.0/googletest-1.16.0.tar.gz
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

include(../../../cmake/functions.cmake)

build_tests(${PROJECT_NAME} "UNIT" "${UNIT_TEST_SOURCES}")
build_tests(${PROJECT_NAME} "REGRESSION" "${REGRESSION_TEST_SOURCES}")
