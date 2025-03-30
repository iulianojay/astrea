cmake_minimum_required(VERSION 3.31.6)

set(CMAKE_INSTALL_MESSAGE LAZY)

# Get sources
file(GLOB_RECURSE UNIT_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_NAME}/*.test.cpp)
file(GLOB_RECURSE REGRESSION_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/**/diver.cpp)

# Set install rpath
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH}:\$ORIGIN/../lib")

# Target for all tests
add_custom_target(${PROJECT_NAME}_tests)
add_dependencies(${PROJECT_NAME}_tests ${PROJECT_NAME}_shared)

# Add subdirectories for regressions
#add_subdirectory(some-regression-test)

build_tests("UNIT" "${UNIT_TEST_SOURCES}")
# build_tests("REGRESSION" "${REGRESSION_TEST_SOURCES}")
