# Copyright (c) 2025 Jay Iuliano
#
# This file is part of Astrea.
# Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
# Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
# have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.28.3)

project(
    "snapshot"
    VERSION ${ASTREA_VERSION}
    DESCRIPTION "Library for Ingesting and Storing Live Satellite Data"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

# Objects
set(SNAPSHOT_BASE ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME})
set(SNAPSHOT_SOURCES
    ${SNAPSHOT_BASE}/http-queries/ethz/EthzClient.cpp
    ${SNAPSHOT_BASE}/http-queries/spacetrack/SpaceTrackClient.cpp
)

# Headers
set(SNAPSHOT_HEADERS
    ${SNAPSHOT_BASE}/database/Database.hpp
    ${SNAPSHOT_BASE}/http-queries/ethz/EthzClient.hpp
    ${SNAPSHOT_BASE}/http-queries/spacetrack/SpaceTrackClient.hpp
    ${SNAPSHOT_BASE}/types/typedefs.hpp
)

# Includes
set(SNAPSHOT_DIRS
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../astro
    ${CMAKE_CURRENT_LIST_DIR}/../utilities
)

# Find library
set(SNAPSHOT_LIBS
    mp-units::mp-units
    nlohmann_json::nlohmann_json
    cpr::cpr
    sqlite_orm::sqlite_orm
)

# Shared library
add_library                (${PROJECT_NAME}_shared SHARED ${SNAPSHOT_SOURCES} ${SNAPSHOT_HEADERS})
set_target_properties      (${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_link_libraries      (${PROJECT_NAME}_shared PUBLIC astro_shared utilities_shared ${SNAPSHOT_LIBS})
target_include_directories (${PROJECT_NAME}_shared PUBLIC ${SNAPSHOT_DIRS})

if(WIN32)
    target_compile_definitions (${PROJECT_NAME}_shared PUBLIC "_SNAPSHOT_ROOT_=\"${CMAKE_CURRENT_LIST_DIR}\"" WIN32_LEAN_AND_MEAN NOMINMAX)
else()
    target_compile_definitions (${PROJECT_NAME}_shared PUBLIC "_SNAPSHOT_ROOT_=\"${CMAKE_CURRENT_LIST_DIR}\"")
endif()

# Install shared library (DLL)
install(TARGETS ${PROJECT_NAME}_shared
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Static library
if(${BUILD_STATIC})
    add_library                (${PROJECT_NAME}_static STATIC ${SNAPSHOT_SOURCES} ${SNAPSHOT_HEADERS})
    set_target_properties      (${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1 SUFFIX .a.${PROJECT_VERSION})
    target_link_libraries      (${PROJECT_NAME}_static PUBLIC astro_shared utilities_static ${SNAPSHOT_LIBS})
    target_include_directories (${PROJECT_NAME}_static PUBLIC ${SNAPSHOT_DIRS})
    target_compile_definitions (${PROJECT_NAME}_static PUBLIC "_SNAPSHOT_ROOT_=\"${CMAKE_CURRENT_LIST_DIR}\"")

    # Install static library (A)
    install(TARGETS ${PROJECT_NAME}_static
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
endif()

# Executable
add_executable             (${PROJECT_NAME}_exe ${SNAPSHOT_BASE}/drivers/main.cpp)
set_target_properties      (${PROJECT_NAME}_exe PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1 RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin/snapshot)
target_include_directories (${PROJECT_NAME}_exe PUBLIC ${SNAPSHOT_DIRS})
target_link_libraries      (${PROJECT_NAME}_exe PUBLIC ${PROJECT_NAME}_shared)
target_compile_options     (${PROJECT_NAME}_exe PUBLIC -Wno-unused-local-typedefs)
# add_custom_target          (${PROJECT_NAME}_exe_symlink ALL COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_NAME}_exe ${PROJECT_NAME})

file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/include)

# Install headers
install(
    DIRECTORY ${SNAPSHOT_BASE}
    DESTINATION include
    FILES_MATCHING
    PATTERN *.hpp
    PATTERN *.ipp
    PATTERN *.h
)

if(${BUILD_EXAMPLES})
    # add_subdirectory(examples)
endif()

if(${BUILD_TESTS})
    # add_subdirectory(tests)
endif()