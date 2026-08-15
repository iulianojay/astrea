# Copyright (c) 2025-2026 Jay Iuliano
#
# This file is part of Astrea.
# Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
# Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
# have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.

set(CMAKE_INSTALL_MESSAGE LAZY)

# Get sources
set(BASE ${CMAKE_CURRENT_SOURCE_DIR})
set(DRIVER_NAME astro_nasa_6dof_checkcase_builder)

set(CHECKCASE_DB_HEADERS
    ${BASE}/helpers/AtmosphericCheckcase.hpp
    ${BASE}/helpers/CheckcaseDatabase.hpp
    ${BASE}/helpers/OrbitalCheckcase.hpp
    ${BASE}/helpers/Stats.hpp
)

set(CHECKCASE_DB_SOURCES
    ${BASE}/helpers/AtmosphericCheckcase.cpp
    ${BASE}/helpers/OrbitalCheckcase.cpp
)

set(CHECKCASE_LIBS
    snapshot_shared
    astro_shared
    math_shared
    utilities_shared
    mp-units::mp-units
    sqlite_orm::sqlite_orm
    matplot
    nlohmann_json::nlohmann_json
    csv
    gtl
)

add_library(${DRIVER_NAME}_shared SHARED ${CHECKCASE_DB_SOURCES} ${CHECKCASE_DB_HEADERS})
set_target_properties(${DRIVER_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${DRIVER_NAME} CLEAN_DIRECT_OUTPUT 1)
target_link_libraries(${DRIVER_NAME}_shared PUBLIC ${CHECKCASE_LIBS})
target_include_directories(${DRIVER_NAME}_shared PUBLIC ${ASTRO_DIRS} ${CMAKE_CURRENT_BINARY_DIR}/include)

add_executable(${DRIVER_NAME} ${BASE}/build_database.cpp)
set_target_properties(${DRIVER_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BASE}/bin)
if (NOT MSVC)
    target_compile_options(${DRIVER_NAME} PUBLIC -Wno-parentheses -Wno-unused-but-set-variable -Wno-unused-variable -Wno-unused-local-typedefs)
endif()
target_link_libraries(${DRIVER_NAME} PUBLIC ${DRIVER_NAME}_shared ${CHECKCASE_LIBS})