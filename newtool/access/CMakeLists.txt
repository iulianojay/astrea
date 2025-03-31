
cmake_minimum_required(VERSION 3.28.3)

project(
    access 
    VERSION 0.0.1 
    DESCRIPTION "Library for Access-Based Simulation and Analysis" 
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

if (PROJECT_IS_TOP_LEVEL) 
    add_subdirectory(../math ../math)
    add_subdirectory(../astro ../astro)
endif()

# Objects
set(ACCESS_BASE ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME})
set(ACCESS_SOURCES
    ${ACCESS_BASE}/access.cpp

    ${ACCESS_BASE}/platforms/Sensor.cpp
    ${ACCESS_BASE}/platforms/ground/GroundStation.cpp
    ${ACCESS_BASE}/platforms/fov/FieldOfView.cpp

    ${ACCESS_BASE}/time/RiseSetArray.cpp
    ${ACCESS_BASE}/time/riseset_utils.cpp
)

# Headers
set(ACCESS_HEADERS
    ${ACCESS_BASE}/access.hpp

    ${ACCESS_BASE}/platforms/Antenna.hpp
    ${ACCESS_BASE}/platforms/Sensor.hpp
    ${ACCESS_BASE}/platforms/ground/GroundStation.hpp
    ${ACCESS_BASE}/platforms/fov/FieldOfView.hpp
    ${ACCESS_BASE}/platforms/vehicles/Viewer.hpp

    ${ACCESS_BASE}/time/AccessArray.hpp
    ${ACCESS_BASE}/time/RiseSetArray.hpp
    ${ACCESS_BASE}/time/riseset_utils.hpp
)

# Set outputs
set(REL_INSTALL_PATH install/${CMAKE_HOST_SYSTEM_PROCESSOR}-${CMAKE_SYSTEM_NAME}/${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}/${CMAKE_BUILD_TYPE})
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/../../${REL_INSTALL_PATH}/${PROJECT_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)

# Includes
set(ACCESS_DIRS
    ${CMAKE_CURRENT_LIST_DIR}
    ${EXTERN_BASE}
    ${CMAKE_INSTALL_PREFIX}/../math/include
    ${CMAKE_INSTALL_PREFIX}/../astro/include
)
include_directories(${ACCESS_DIRS})

# Shared library
add_library           (${PROJECT_NAME}_shared SHARED ${ACCESS_SOURCES} ${ACCESS_HEADERS})
set_target_properties (${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_link_libraries (${PROJECT_NAME}_shared PUBLIC math_shared astro_shared)

# Static library
add_library           (${PROJECT_NAME}_static STATIC ${ACCESS_SOURCES} ${ACCESS_HEADERS})
set_target_properties (${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1 SUFFIX .a.${PROJECT_VERSION})
target_link_libraries (${PROJECT_NAME}_shared PUBLIC math_static astro_static)

# Executable
add_executable             (${PROJECT_NAME}_exe ${ACCESS_BASE}/drivers/main.cpp)
set_target_properties      (${PROJECT_NAME}_exe PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_include_directories (${PROJECT_NAME}_exe PUBLIC ${ACCESS_DIRS})
target_link_libraries      (${PROJECT_NAME}_exe PUBLIC ${PROJECT_NAME}_shared)

# Install headers
file(COPY
    DIRECTORY ${ACCESS_BASE}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING
    PATTERN *.hpp
    PATTERN *.h
)