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
    helios
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
set(HELIOS_SOURCES)

# Headers
set(HELIOS_HEADERS
    ${HELIOS_BASE}/helios.macros.hpp
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

# App
add_executable(${PROJECT_NAME}_app helios/drivers/main.cpp ${HELIOS_SOURCES} ${HELIOS_HEADERS})
target_link_libraries(${PROJECT_NAME}_app PRIVATE astro_shared snapshot_shared webui OpenMP::OpenMP_CXX)
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME}_app PRIVATE pthread m dl)
endif()
set_target_properties(${PROJECT_NAME}_app PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
    CLEAN_DIRECT_OUTPUT 1
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}
)
target_include_directories(${PROJECT_NAME}_app PUBLIC ${HELIOS_DIRS})

if(WIN32)
    target_compile_definitions(${PROJECT_NAME}_app PUBLIC "_HELIOS_ROOT_=\"${CMAKE_CURRENT_LIST_DIR}\"" WIN32_LEAN_AND_MEAN NOMINMAX)
else()
    target_compile_definitions(${PROJECT_NAME}_app PUBLIC "_HELIOS_ROOT_=\"${CMAKE_CURRENT_LIST_DIR}\"")
endif()
