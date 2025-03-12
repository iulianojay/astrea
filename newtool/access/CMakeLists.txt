
cmake_minimum_required(VERSION 3.31.6)

project(
    access 
    VERSION 0.0.1 
    DESCRIPTION "Library for Access-Based Simulation and Analysis" 
    LANGUAGES CXX
)

# Objects
set(ACCESS_BASE ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME})
set(${PROJECT_NAME}_SOURCES
    ${ACCESS_BASE}/access.cpp
    ${ACCESS_BASE}/platforms/Sensor.cpp
    ${ACCESS_BASE}/platforms/fov/FieldOfView.cpp
    ${ACCESS_BASE}/time/RiseSetArray.cpp
)

# Headers
set(ACCESS_HEADERS
    ${ACCESS_BASE}/access.hpp

    ${ACCESS_BASE}/platforms/Antenna.hpp
    ${ACCESS_BASE}/platforms/Sensor.hpp
    ${ACCESS_BASE}/platforms/fov/FieldOfView.hpp

    ${ACCESS_BASE}/time/AccessArray.hpp
    ${ACCESS_BASE}/time/RiseSetArray.hpp
    ${ACCESS_BASE}/time/riseset_utils.hpp
)

# Includes
set(ACCESS_DIRS
    ${ACCESS_BASE}
)

# Set outputs
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)

# Shared library
add_library                (${PROJECT_NAME}_shared SHARED ${ACCESS_SOURCES} ${ACCESS_HEADERS})
set_target_properties      (${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
set_target_properties      (${PROJECT_NAME}_shared PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories (${PROJECT_NAME}_shared PUBLIC ${ACCESS_DIRS})

# Static library
add_library                (${PROJECT_NAME}_static STATIC ${ACCESS_SOURCES} ${ACCESS_HEADERS})
set_target_properties      (${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
set_target_properties      (${PROJECT_NAME}_static PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories (${PROJECT_NAME}_static PUBLIC ${ACCESS_DIRS})

# Copy include
file(COPY
    DIRECTORY ${ACCESS_BASE}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING
    PATTERN *.hpp
)