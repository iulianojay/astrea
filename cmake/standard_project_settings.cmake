# Copyright (c) 2025 Jay Iuliano
# 
# This file is part of Astrea.
# Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
# Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
# have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.

# Compiler flags - Platform specific
if(MSVC)
    # MSVC (Visual Studio) flags
    set(COMMON_FLAGS "/DWL=64 /bigobj /Zc:preprocessor /Zc:lambda")
    set(DEBUG_FLAGS "${COMMON_FLAGS} /Od /Zi")
    set(RELEASE_FLAGS "${COMMON_FLAGS} /O2 /fp:fast")
    set(RELWITHHDEBINFO_FLAGS "${RELEASE_FLAGS} /Zi")

    set(C_FLAGS "/W3")
    set(CXX_FLAGS "/W3 /EHsc /std:c++latest /permissive- /Zc:__cplusplus")

    # Disable specific MSVC warnings if needed
    # add_compile_options(/wd4996) # Disable deprecation warnings
elseif(MINGW)
    # MinGW (Windows GCC) flags
    set(COMMON_FLAGS "-DWL=64 -m64 -fPIC")
    set(DEBUG_FLAGS "${COMMON_FLAGS} -g -fno-inline -fno-inline-small-functions -fno-default-inline -O0")
    set(RELEASE_FLAGS "${COMMON_FLAGS} -O3 -ffinite-loops")
    set(RELWITHHDEBINFO_FLAGS "${RELEASE_FLAGS} -g")

    set(C_FLAGS "-Wall -Wl,--kill-at")
    set(CXX_FLAGS "-Wall -Wl,--kill-at -fpermissive")
elseif(UNIX AND NOT APPLE)
    # Linux GCC flags
    set(COMMON_FLAGS "-DWL=64 -m64 -fPIC -mfpmath=387 -DLINUX -Wno-interference-size")
    set(DEBUG_FLAGS "${COMMON_FLAGS} -g -fno-inline -fno-inline-small-functions -fno-default-inline --coverage -O0")
    set(RELEASE_FLAGS "${COMMON_FLAGS} -O3 -ffinite-loops")
    set(RELWITHHDEBINFO_FLAGS "${RELEASE_FLAGS} -g")

    set(C_FLAGS "-Wall")
    set(CXX_FLAGS "-Wall -fpermissive")
else()
    # Other platforms (macOS, etc.)
    set(COMMON_FLAGS "-DWL=64 -m64 -fPIC")
    set(DEBUG_FLAGS "${COMMON_FLAGS} -g -O0")
    set(RELEASE_FLAGS "${COMMON_FLAGS} -O3")
    set(RELWITHHDEBINFO_FLAGS "${RELEASE_FLAGS} -g")

    set(C_FLAGS "-Wall")
    set(CXX_FLAGS "-Wall")
endif()

set(CMAKE_C_FLAGS_DEBUG            "${C_FLAGS} ${DEBUG_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE          "${C_FLAGS} ${RELEASE_FLAGS}")
set(CMAKE_C_FLAGS_RELWITHDEBINFO   "${C_FLAGS} ${RELWITHHDEBINFO_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG          "${CXX_FLAGS} ${DEBUG_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE        "${CXX_FLAGS} ${RELEASE_FLAGS}")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CXX_FLAGS} ${RELWITHHDEBINFO_FLAGS}")