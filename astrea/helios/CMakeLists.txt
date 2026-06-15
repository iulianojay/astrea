# Copyright (c) 2026 Jay Iuliano
#
# This file is part of Astrea.
# Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
# Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
# have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.

CPMAddPackage(
    NAME webui
    GITHUB_REPOSITORY webui-dev/webui
    GIT_TAG nightly
    GIT_SHALLOW TRUE
    OPTIONS
        "WEBUI_BUILD_EXAMPLES OFF"
)

find_package(OpenMP REQUIRED)

add_executable(helios_app helios/drivers/main.cpp)

target_link_libraries(helios_app PRIVATE astro_shared snapshot_shared webui OpenMP::OpenMP_CXX)

if(UNIX AND NOT APPLE)
    target_link_libraries(helios_app PRIVATE pthread m dl)
endif()

set_target_properties(helios_app PROPERTIES
    OUTPUT_NAME helios
    CLEAN_DIRECT_OUTPUT 1
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin/helios
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/templates/
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/helios/templates
)
