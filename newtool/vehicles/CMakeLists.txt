
cmake_minimum_required(VERSION 3.28.3)

project(
    vehicles 
    VERSION 0.0.1 
    DESCRIPTION "Library for Simple Math Utilities" 
    LANGUAGES CXX
)

### Go line by line and change Math with Vehicle

set(CMAKE_CXX_STANDARD 23)

# Objects
set(MATH_BASE ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME})
set(MATH_SOURCES
    ${MATH_BASE}/interpolation.cpp
    ${MATH_BASE}/utils.cpp
)

# Headers
set(MATH_HEADERS
    ${MATH_BASE}/utils.hpp
    ${MATH_BASE}/interpolation.hpp

    # Extern
    # $(EXTERN_BASE or something like that)
)

# Do not touch below this line---------

# Includes
set(MATH_DIRS
    ${CMAKE_CURRENT_LIST_DIR}
)
include_directories(${MATH_DIRS})

# Set outputs
set(REL_INSTALL_PATH install/${CMAKE_HOST_SYSTEM_PROCESSOR}-${CMAKE_SYSTEM_NAME}/${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}/${CMAKE_BUILD_TYPE})
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/../../${REL_INSTALL_PATH}/${PROJECT_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)

# Shared library
add_library           (${PROJECT_NAME}_shared SHARED ${MATH_SOURCES} ${MATH_HEADERS})
set_target_properties (${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)

# Static library
add_library           (${PROJECT_NAME}_static STATIC ${MATH_SOURCES} ${MATH_HEADERS})
set_target_properties (${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1 SUFFIX .a.${PROJECT_VERSION})

# Install headers
file(COPY
    DIRECTORY ${MATH_BASE}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING
    PATTERN *.hpp
    PATTERN *.h
)