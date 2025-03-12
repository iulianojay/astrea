
cmake_minimum_required(VERSION 3.31.6)

project(
    "math" 
    VERSION 0.0.1 
    DESCRIPTION "Library for Simple Math Utilities" 
    LANGUAGES CXX
)

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
)

# Includes
set(MATH_DIRS
    ${MATH_BASE}
)

# Set outputs
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)

# Shared library
add_library                (${PROJECT_NAME}_shared SHARED ${MATH_SOURCES} ${MATH_HEADERS})
set_target_properties      (${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_include_directories (${PROJECT_NAME}_shared PUBLIC ${MATH_DIRS})

# Static library
add_library                (${PROJECT_NAME}_static STATIC ${MATH_SOURCES} ${MATH_HEADERS})
set_target_properties      (${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)
target_include_directories (${PROJECT_NAME}_static PUBLIC ${MATH_DIRS})

# Copy include
file(COPY
    DIRECTORY ${MATH_BASE}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING
    PATTERN *.hpp
)