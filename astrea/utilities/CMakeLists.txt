
cmake_minimum_required(VERSION 3.28.3)

project(
    "utilities" 
    VERSION 0.0.1 
    DESCRIPTION "Simple miscellaneous utilities for Astrea" 
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

# Objects
set(UTILITIES_BASE ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME})
set(UTILITIES_SOURCES
    ${UTILITIES_BASE}/json_util.cpp
    ${UTILITIES_BASE}/string_util.cpp
)

# Find library
# find_library(AVRO avrocpp)

# Headers
set(EXTERN_BASE ${CMAKE_CURRENT_LIST_DIR}/../../extern)
set(UTILITIES_HEADERS
    ${UTILITIES_BASE}/json_util.hpp
    ${UTILITIES_BASE}/ProgressBar.hpp
    ${UTILITIES_BASE}/string_util.hpp
)

# Includes
set(UTILITIES_DIRS
    ${EXTERN_BASE}
    ${CMAKE_CURRENT_LIST_DIR}
)
include_directories(${UTILITIES_DIRS})

# Set outputs
set(REL_INSTALL_PATH install/${CMAKE_HOST_SYSTEM_PROCESSOR}-${CMAKE_SYSTEM_NAME}/${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}/${CMAKE_BUILD_TYPE})
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/../../${REL_INSTALL_PATH}/${PROJECT_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)

# Shared library
add_library           (${PROJECT_NAME}_shared SHARED ${UTILITIES_SOURCES} ${UTILITIES_HEADERS})
set_target_properties (${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_link_libraries (${PROJECT_NAME}_shared PUBLIC mp-units::mp-units cpr::cpr sqlite_orm::sqlite_orm GTest::gtest_main)

# Static library
if (${BUILD_STATIC})
    add_library           (${PROJECT_NAME}_static STATIC ${UTILITIES_SOURCES} ${UTILITIES_HEADERS})
    set_target_properties (${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1 SUFFIX .a.${PROJECT_VERSION})
    target_link_libraries (${PROJECT_NAME}_static PUBLIC mp-units::mp-units cpr::cpr sqlite_orm::sqlite_orm GTest::gtest_main)
endif()

# Install headers
file(COPY
    DIRECTORY ${UTILITIES_BASE}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING
    PATTERN *.hpp
    PATTERN *.h
)

# add_subdirectory(examples EXCLUDE_FROM_ALL)
if(${BUILD_TESTS})
    add_subdirectory(tests)
endif()