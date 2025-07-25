
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
    add_subdirectory(../snapshot ../snapshot)
    add_subdirectory(../units ../units)
    add_subdirectory(../utilities ../utilities)
endif()

# Objects
set(EXTERN_BASE ${CMAKE_CURRENT_LIST_DIR}/../../extern)
set(ACCESS_BASE ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME})
set(ACCESS_SOURCES
    ${ACCESS_BASE}/analysis/access_analysis.cpp

    ${ACCESS_BASE}/platforms/sensors/Antenna.cpp
    ${ACCESS_BASE}/platforms/sensors/Sensor.cpp

    ${ACCESS_BASE}/platforms/ground/Grid.cpp
    ${ACCESS_BASE}/platforms/ground/GroundStation.cpp

    ${ACCESS_BASE}/platforms/sensors/fov/FieldOfView.cpp

    ${ACCESS_BASE}/time/RiseSetArray.cpp
    ${ACCESS_BASE}/time/riseset_utils.cpp
)

# Headers
set(ACCESS_HEADERS
    ${ACCESS_BASE}/access.hpp

    ${ACCESS_BASE}/analysis/access_analysis.hpp

    ${ACCESS_BASE}/platforms/sensors/Antenna.hpp
    ${ACCESS_BASE}/platforms/sensors/Sensor.hpp
    ${ACCESS_BASE}/platforms/sensors/SensorPlatform.hpp
    ${ACCESS_BASE}/platforms/sensors/fov/FieldOfView.hpp

    ${ACCESS_BASE}/platforms/ground/Grid.hpp
    ${ACCESS_BASE}/platforms/ground/GroundArchitecture.hpp
    ${ACCESS_BASE}/platforms/ground/GroundPoint.hpp
    ${ACCESS_BASE}/platforms/ground/GroundStation.hpp
    
    ${ACCESS_BASE}/platforms/vehicles/Viewer.hpp

    ${ACCESS_BASE}/time/AccessArray.hpp
    ${ACCESS_BASE}/time/RiseSetArray.hpp
    ${ACCESS_BASE}/time/riseset_utils.hpp
    
    ${ACCESS_BASE}/types/typedefs.hpp
    
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
set(ACCESS_DIRS
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
include_directories(${ACCESS_DIRS})

find_package(SQLite3 REQUIRED)

include(FetchContent)
FetchContent_Declare(sqlite_orm GIT_REPOSITORY https://github.com/fnc12/sqlite_orm.git GIT_TAG v1.9.1)
FetchContent_MakeAvailable(sqlite_orm)

# Shared library
add_library           (${PROJECT_NAME}_shared SHARED ${ACCESS_SOURCES} ${ACCESS_HEADERS})
set_target_properties (${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_link_libraries (${PROJECT_NAME}_shared PUBLIC math_shared astro_shared snapshot_shared mp-units::mp-units sqlite_orm::sqlite_orm)

# Static library
add_library           (${PROJECT_NAME}_static STATIC ${ACCESS_SOURCES} ${ACCESS_HEADERS})
set_target_properties (${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1 SUFFIX .a.${PROJECT_VERSION})
target_link_libraries (${PROJECT_NAME}_shared PUBLIC math_static astro_static snapshot_static mp-units::mp-units sqlite_orm::sqlite_orm)

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

# add_subdirectory(examples EXCLUDE_FROM_ALL)
add_subdirectory(tests)