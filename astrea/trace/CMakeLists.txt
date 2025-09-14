
cmake_minimum_required(VERSION 3.28.3)

project(
    trace 
    VERSION 0.0.1 
    DESCRIPTION "Library for Trace-Based Simulation and Analysis" 
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

# Objects
set(EXTERN_BASE ${CMAKE_CURRENT_LIST_DIR}/../../extern)
set(TRACE_BASE ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME})
set(TRACE_SOURCES
    ${TRACE_BASE}/analysis/access_analysis.cpp

    ${TRACE_BASE}/platforms/sensors/Antenna.cpp
    ${TRACE_BASE}/platforms/sensors/Sensor.cpp

    ${TRACE_BASE}/platforms/ground/Grid.cpp
    ${TRACE_BASE}/platforms/ground/GroundStation.cpp

    ${TRACE_BASE}/platforms/sensors/fov/FieldOfView.cpp

    ${TRACE_BASE}/risesets/AccessArray.cpp
    ${TRACE_BASE}/risesets/RiseSetArray.cpp
    ${TRACE_BASE}/risesets/riseset_utils.cpp
)

# Headers
set(TRACE_HEADERS
    ${TRACE_BASE}/trace.hpp

    ${TRACE_BASE}/analysis/access_analysis.hpp

    ${TRACE_BASE}/platforms/sensors/Antenna.hpp
    ${TRACE_BASE}/platforms/sensors/Sensor.hpp
    ${TRACE_BASE}/platforms/sensors/fov/FieldOfView.hpp

    ${TRACE_BASE}/platforms/ground/Grid.hpp
    ${TRACE_BASE}/platforms/ground/GroundArchitecture.hpp
    ${TRACE_BASE}/platforms/ground/GroundPoint.hpp
    ${TRACE_BASE}/platforms/ground/GroundStation.hpp
    
    ${TRACE_BASE}/platforms/vehicles/Viewer.hpp

    ${TRACE_BASE}/risesets/AccessArray.hpp
    ${TRACE_BASE}/risesets/RiseSetArray.hpp
    ${TRACE_BASE}/risesets/riseset_utils.hpp
    
    ${TRACE_BASE}/types/typedefs.hpp
    
    ${EXTERN_BASE}/nlohmann/json.hpp
    ${EXTERN_BASE}/csv-parser/csv.hpp
)

# Set outputs
set(REL_INSTALL_PATH install/${CMAKE_HOST_SYSTEM_PROCESSOR}-${CMAKE_SYSTEM_NAME}/${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}/${CMAKE_BUILD_TYPE})
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/../../${REL_INSTALL_PATH}/${PROJECT_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)

# Includes
set(TRACE_DIRS
    ${EXTERN_BASE}
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../math
    ${CMAKE_CURRENT_LIST_DIR}/../astro
    ${CMAKE_CURRENT_LIST_DIR}/../snapshot
    ${CMAKE_CURRENT_LIST_DIR}/../units
    ${CMAKE_CURRENT_LIST_DIR}/../utilities
    $ENV{HOME}/open-source/mp-units/src/core/include
    $ENV{HOME}/open-source/mp-units/src/systems/include
)
include_directories(${TRACE_DIRS})

# Shared library
add_library           (${PROJECT_NAME}_shared SHARED ${TRACE_SOURCES} ${TRACE_HEADERS})
set_target_properties (${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_link_libraries (${PROJECT_NAME}_shared PUBLIC math_shared astro_shared snapshot_shared mp-units::mp-units GTest::gtest_main)

# Static library
add_library           (${PROJECT_NAME}_static STATIC ${TRACE_SOURCES} ${TRACE_HEADERS})
set_target_properties (${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1 SUFFIX .a.${PROJECT_VERSION})
target_link_libraries (${PROJECT_NAME}_static PUBLIC math_static astro_static snapshot_static mp-units::mp-units GTest::gtest_main)

# Executable
add_executable             (${PROJECT_NAME}_exe ${TRACE_BASE}/drivers/main.cpp)
set_target_properties      (${PROJECT_NAME}_exe PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_include_directories (${PROJECT_NAME}_exe PUBLIC ${TRACE_DIRS})
target_link_libraries      (${PROJECT_NAME}_exe PUBLIC ${PROJECT_NAME}_shared)
target_compile_options     (${PROJECT_NAME}_exe PUBLIC -Wno-unused-local-typedefs -Wno-uninitialized)
add_custom_target          (${PROJECT_NAME}_exe_symlink ALL COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_NAME}_exe ${PROJECT_NAME})

# Install headers
file(COPY
    DIRECTORY ${TRACE_BASE}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING
    PATTERN *.hpp
    PATTERN *.h
)

# add_subdirectory(examples EXCLUDE_FROM_ALL)
if(${BUILD_TESTS})
    add_subdirectory(tests)
endif()