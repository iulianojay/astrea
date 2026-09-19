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
set(PROFILER_NAME astro_profiler)

add_executable         (${PROFILER_NAME} ${BASE}/main.cpp)
set_target_properties  (${PROFILER_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BASE}/bin)
if (NOT MSVC)
    target_compile_options (${PROFILER_NAME} PUBLIC -Wno-parentheses -Wno-unused-but-set-variable -Wno-unused-variable -Wno-unused-local-typedefs)
endif()
target_link_libraries  (${PROFILER_NAME} PUBLIC astro_shared matplot)