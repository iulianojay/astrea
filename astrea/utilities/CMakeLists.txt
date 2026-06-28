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
    "utilities"
    VERSION ${ASTREA_VERSION}
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
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../units
)

# Find library
set(UTILITIES_LIBS
    nlohmann_json::nlohmann_json
    mp-units::mp-units
)

# Shared library
add_library                (${PROJECT_NAME}_shared SHARED ${UTILITIES_SOURCES} ${UTILITIES_HEADERS})
set_target_properties      (${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_link_libraries      (${PROJECT_NAME}_shared PUBLIC ${UTILITIES_LIBS})
target_include_directories (${PROJECT_NAME}_shared PUBLIC ${UTILITIES_DIRS})
add_library                (astrea::utilities ALIAS ${PROJECT_NAME}_shared)

# Install shared library (DLL)
install(TARGETS ${PROJECT_NAME}_shared
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Static library
if(${BUILD_STATIC})
    add_library                (${PROJECT_NAME}_static STATIC ${UTILITIES_SOURCES} ${UTILITIES_HEADERS})
    set_target_properties      (${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1 SUFFIX .a.${PROJECT_VERSION})
    target_link_libraries      (${PROJECT_NAME}_static PUBLIC ${UTILITIES_LIBS})
    target_include_directories (${PROJECT_NAME}_static PUBLIC ${UTILITIES_DIRS})
    add_library                (astrea::utilities_static ALIAS ${PROJECT_NAME}_static)

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
    DIRECTORY ${UTILITIES_BASE}
    DESTINATION include
    FILES_MATCHING
    PATTERN *.hpp
    PATTERN *.ipp
    PATTERN *.h
)

# add_subdirectory(examples EXCLUDE_FROM_ALL)
if(${BUILD_TESTS})
    add_subdirectory(tests)
endif()