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
    "helios"
    VERSION ${ASTREA_VERSION}
    DESCRIPTION "Simple Web GUI for Astrea"
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 23)

# Packages only for this
CPMAddPackage(
    NAME webui
    GITHUB_REPOSITORY webui-dev/webui
    GIT_TAG nightly
    GIT_SHALLOW TRUE
    OPTIONS
        "WEBUI_BUILD_EXAMPLES OFF"
)

find_package(OpenMP REQUIRED)

# Objects
set(HELIOS_BASE ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME})
set(HELIOS_SOURCES
    ${HELIOS_BASE}/app/animations.cpp
    ${HELIOS_BASE}/app/propagation.cpp

    ${HELIOS_BASE}/helpers/database_fetcher.cpp
)

# Headers
set(HELIOS_HEADERS
    ${HELIOS_BASE}/app/animations.hpp
    ${HELIOS_BASE}/app/propagation.hpp

    ${HELIOS_BASE}/helpers/database_fetcher.hpp

    ${HELIOS_BASE}/helios.macros.hpp
    ${HELIOS_BASE}/types.hpp
)

# Includes
set(HELIOS_DIRS
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../math
    ${CMAKE_CURRENT_LIST_DIR}/../astro
    ${CMAKE_CURRENT_LIST_DIR}/../snapshot
    ${CMAKE_CURRENT_LIST_DIR}/../units
    ${CMAKE_CURRENT_LIST_DIR}/../utilities
)

# Find library
set(HELIOS_LIBS
    mp-units::mp-units 
    webui 
    OpenMP::OpenMP_CXX
    nlohmann_json::nlohmann_json
    sqlite_orm::sqlite_orm
)

# Shared library
add_library(${PROJECT_NAME}_shared SHARED ${HELIOS_SOURCES} ${HELIOS_HEADERS})
add_library(astrea::helios ALIAS ${PROJECT_NAME}_shared)

if(${BUILD_EPHEMERIDES})
    add_dependencies(${PROJECT_NAME}_shared generated_ephemerides)
endif()

set_target_properties      (${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1 INSTALL_RPATH "$ORIGIN")
target_link_libraries      (${PROJECT_NAME}_shared PUBLIC math_shared utilities_shared astro_shared snapshot_shared ${HELIOS_LIBS})
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME}_shared PRIVATE pthread m dl)
endif()
target_include_directories (${PROJECT_NAME}_shared PUBLIC ${HELIOS_DIRS} ${CMAKE_CURRENT_BINARY_DIR}/include)

if(WIN32)
    target_compile_definitions (${PROJECT_NAME}_shared PUBLIC ${EPHEMERIS_COMPILE_DEFINES} "_HELIOS_ROOT_=\"${CMAKE_CURRENT_LIST_DIR}\"" WIN32_LEAN_AND_MEAN NOMINMAX)
else()
    target_compile_definitions (${PROJECT_NAME}_shared PUBLIC ${EPHEMERIS_COMPILE_DEFINES} "_HELIOS_ROOT_=\"${CMAKE_CURRENT_LIST_DIR}\"")
endif()

# Install shared library (DLL)
install(TARGETS ${PROJECT_NAME}_shared
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Static library
if(${BUILD_STATIC})
    add_library(${PROJECT_NAME}_static STATIC ${HELIOS_SOURCES} ${HELIOS_HEADERS})
    add_library(astrea::helios_static ALIAS ${PROJECT_NAME}_static)

    set_target_properties      (${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1 SUFFIX .a.${PROJECT_VERSION})
    target_link_libraries      (${PROJECT_NAME}_static PUBLIC math_static utilities_static astro_static snapshot_static ${HELIOS_LIBS})
    if(UNIX AND NOT APPLE)
        target_link_libraries(${PROJECT_NAME}_static PRIVATE pthread m dl)
    endif()
    target_include_directories (${PROJECT_NAME}_static PUBLIC ${HELIOS_DIRS} ${CMAKE_CURRENT_BINARY_DIR}/include)
    target_compile_definitions (${PROJECT_NAME}_static PUBLIC ${EPHEMERIS_COMPILE_DEFINES} "_HELIOS_ROOT_=\"${CMAKE_CURRENT_LIST_DIR}\"")

    # Install static library (A)
    install(TARGETS ${PROJECT_NAME}_static
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
endif()

file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/include)

# Install headers
install(
    DIRECTORY ${HELIOS_BASE}
    DESTINATION include
    FILES_MATCHING
    PATTERN *.hpp
    PATTERN *.ipp
    PATTERN *.h
)

# App
add_executable(${PROJECT_NAME}_app ${HELIOS_BASE}/drivers/main.cpp)
target_link_libraries(${PROJECT_NAME}_app PRIVATE helios_shared)
set_target_properties(${PROJECT_NAME}_app PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
    CLEAN_DIRECT_OUTPUT 1
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}
)
target_include_directories(${PROJECT_NAME}_app PUBLIC ${HELIOS_DIRS})

if(${BUILD_TESTS})
    add_subdirectory(tests)
endif()