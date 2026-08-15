# Copyright (c) 2025-2026 Jay Iuliano
#
# This file is part of Astrea.
# Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
# Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
# have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.

# add_subdirectory(trace)
add_subdirectory(astro)
add_subdirectory(math)
add_subdirectory(helios)
# add_subdirectory(pathfinder)
add_subdirectory(snapshot)
add_subdirectory(utilities)

# add_subdirectory(units) // ignore until it has compiled files in it

# Install units headers (header-only, no compiled target yet)
install(
    DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/units/units
    DESTINATION include
)

# Aggregate target
add_library(astrea INTERFACE)
add_library(astrea::astrea ALIAS astrea)
target_link_libraries(astrea INTERFACE
    math_shared
    utilities_shared
    astro_shared
    snapshot_shared
    # trace_shared
    # helios_shared
)

# Static aggregate target (only created when BUILD_STATIC is enabled)
if(${BUILD_STATIC})
    add_library(astrea_static INTERFACE)
    add_library(astrea::astrea_static ALIAS astrea_static)
    target_link_libraries(astrea_static INTERFACE
        math_static
        utilities_static
        astro_static
        snapshot_static
        # trace_static
        # helios_static
    )
endif()