
cmake_minimum_required(VERSION 3.28.3)

project(
    "snapshot" 
    VERSION 0.0.1 
    DESCRIPTION "Library for Ingesting and Storing Live Satellite Data" 
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

if (PROJECT_IS_TOP_LEVEL) 
    add_subdirectory(../astro ../astro)
endif()

# Objects
set(SNAPSHOT_BASE ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME})
set(SNAPSHOT_SOURCES
    ${SNAPSHOT_BASE}/interpolation.cpp
    ${SNAPSHOT_BASE}/utils.cpp
)

# Find library
find_library(AVRO avrocpp)

# Headers
set(SNAPSHOT_HEADERS
    ${SNAPSHOT_BASE}/utils.hpp
    ${SNAPSHOT_BASE}/interpolation.hpp
)

# Includes
set(SNAPSHOT_DIRS
    ${CMAKE_CURRENT_LIST_DIR}
)
include_directories(${SNAPSHOT_DIRS})

# Set outputs
set(REL_INSTALL_PATH install/${CMAKE_HOST_SYSTEM_PROCESSOR}-${CMAKE_SYSTEM_NAME}/${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}/${CMAKE_BUILD_TYPE})
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/../../${REL_INSTALL_PATH}/${PROJECT_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)

# # Shared library
# add_library           (${PROJECT_NAME}_shared SHARED ${SNAPSHOT_SOURCES} ${SNAPSHOT_HEADERS})
# set_target_properties (${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)

# # Static library
# add_library           (${PROJECT_NAME}_static STATIC ${SNAPSHOT_SOURCES} ${SNAPSHOT_HEADERS})
# set_target_properties (${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1 SUFFIX .a.${PROJECT_VERSION})

# Executable
add_executable             (${PROJECT_NAME}_exe ${SNAPSHOT_BASE}/drivers/main.cpp)
set_target_properties      (${PROJECT_NAME}_exe PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_include_directories (${PROJECT_NAME}_exe PUBLIC ${SNAPSHOT_DIRS})
target_link_libraries      (${PROJECT_NAME}_exe PUBLIC ${AVRO} astro_shared mp-units::mp-units)

# Install headers
file(COPY
    DIRECTORY ${SNAPSHOT_BASE}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING
    PATTERN *.hpp
    PATTERN *.h
)

# add_subdirectory(examples EXCLUDE_FROM_ALL)
# add_subdirectory(tests EXCLUDE_FROM_ALL)