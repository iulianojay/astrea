
cmake_minimum_required(VERSION 3.16.3)

project(astro VERSION 1.0.0 DESCRIPTION "C++ astodynamics library" LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Utility variables
set(BASE ${CMAKE_CURRENT_SOURCE_DIR})
set(INC ${BASE}/include)
set(SRC ${BASE}/source)
set(TEST ${BASE}/tests)

set(BINPATH ${BASE}/bin)
set(LIBPATH ${BASE}/lib)
set(LIBNAME astro)
set(EXENAME astro_exe)
set(TESTNAME tests)

# Objects
set(OBJS
    ${SRC}/element_sets/OrbitalElements.cpp
    
    ${SRC}/platforms/Constellation.cpp
    ${SRC}/platforms/Plane.cpp
    ${SRC}/platforms/Shell.cpp
    ${SRC}/platforms/Spacecraft.cpp

    ${SRC}/propagation/EquationsOfMotion.cpp
    ${SRC}/propagation/Integrator.cpp
    ${SRC}/propagation/LambertSolver.cpp

    ${SRC}/systems/AstrodynamicsSystem.cpp
    ${SRC}/systems/GravitationalBody.cpp
    ${SRC}/systems/SolarObjectBuilder.cpp
    ${SRC}/systems/SolarObjectFactory.cpp

    ${SRC}/time/Time.cpp

    ${SRC}/utilities/conversions.cpp
    ${SRC}/utilities/math_c.cpp

    ${SRC}/State.cpp
)

include(config/astro_config.cmake)

# Shared library
add_library                (${LIBNAME}_shared SHARED ${OBJS} ${HDRS})
set_target_properties      (${LIBNAME}_shared PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${LIBPATH} VERSION ${PROJECT_VERSION} OUTPUT_NAME ${LIBNAME} CLEAN_DIRECT_OUTPUT 1)
target_include_directories (${LIBNAME}_shared PUBLIC ${INCLUDE_DIRS})

# Static library
add_library                (${LIBNAME}_static STATIC ${OBJS} ${HDRS})
set_target_properties      (${LIBNAME}_static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${LIBPATH} VERSION ${PROJECT_VERSION} OUTPUT_NAME ${LIBNAME} CLEAN_DIRECT_OUTPUT 1)
target_include_directories (${LIBNAME}_static PUBLIC ${INCLUDE_DIRS})

# Executable 
add_executable             (${EXENAME} ${SRC}/main.cpp)
set_target_properties      (${EXENAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BINPATH} VERSION ${PROJECT_VERSION} OUTPUT_NAME ${EXENAME} CLEAN_DIRECT_OUTPUT 1)
target_include_directories (${EXENAME} PUBLIC ${INCLUDE_DIRS})
target_link_libraries      (${EXENAME} PUBLIC ${LIBNAME}_shared)
add_dependencies           (${EXENAME} ${LIBNAME}_shared)

# SWIG-Python 
set(PY_SWIG_PROJECT_NAME py${PROJECT_NAME})

find_package(Python3 COMPONENTS Interpreter Development)
include_directories(${Python3_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(
    ${INC}
    ${INC}/astro
    ${INC}/astro/constants
    ${INC}/astro/element_sets
    ${INC}/astro/platforms
    ${INC}/astro/propagation
    ${INC}/astro/systems
    ${INC}/astro/time
    ${INC}/astro/types
    ${INC}/astro/utilities
)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

set(SWIG_SRC ${BASE}/swig)
list(APPEND SWIG_INTERFACE_FILES
    ${SWIG_SRC}/astro.i
)

set(CMAKE_SWIG_FLAGS "")

set_source_files_properties(${SWIG_INTERFACE_FILES} PROPERTIES CPLUSPLUS ON)
set_source_files_properties(${SWIG_INTERFACE_FILES} PROPERTIES SWIG_FLAGS "-includeall")

set(CMAKE_SWIG_OUTDIR "${CMAKE_CURRENT_BINARY_DIR}/python")
SWIG_ADD_LIBRARY(${PY_SWIG_PROJECT_NAME} LANGUAGE python SOURCES ${SWIG_INTERFACE_FILES} OUTPUT_DIR ${CMAKE_SWIG_OUTDIR})
SWIG_LINK_LIBRARIES(${PY_SWIG_PROJECT_NAME} ${PYTHON_LIBRARIES} ${LIBNAME}_shared)
set_target_properties(${PY_SWIG_PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SWIG_OUTDIR})


# SWIG-Java
set(JAVA_SWIG_PROJECT_NAME jv${PROJECT_NAME})

find_package(Java REQUIRED)
find_package(JNI REQUIRED)
include(UseJava)
include(UseSWIG)

include_directories(${JNI_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${JAVA_INCLUDE_PATH})
include_directories(${JAVA_INCLUDE_PATH2})
include_directories(
    ${INC}
    ${INC}/astro
    ${INC}/astro/constants
    ${INC}/astro/element_sets
    ${INC}/astro/platforms
    ${INC}/astro/propagation
    ${INC}/astro/systems
    ${INC}/astro/time
    ${INC}/astro/types
    ${INC}/astro/utilities
)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

set(SWIG_SRC ${BASE}/swig)
list(APPEND SWIG_INTERFACE_FILES
    ${SWIG_SRC}/astro.i
)

set(CMAKE_SWIG_FLAGS "")

set_source_files_properties(${SWIG_INTERFACE_FILES} PROPERTIES CPLUSPLUS ON)
set_source_files_properties(${SWIG_INTERFACE_FILES} PROPERTIES SWIG_FLAGS "-includeall")
set(CMAKE_SWIG_OUTDIR "${CMAKE_CURRENT_BINARY_DIR}/java")

SWIG_ADD_LIBRARY(${JAVA_SWIG_PROJECT_NAME} LANGUAGE java SOURCES ${SWIG_INTERFACE_FILES})
SWIG_LINK_LIBRARIES(${JAVA_SWIG_PROJECT_NAME} ${LIBNAME}_shared)
set_target_properties(${JAVA_SWIG_PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SWIG_OUTDIR})
set_property(TARGET ${JAVA_SWIG_PROJECT_NAME} PROPERTY SWIG_COMPILE_OPTIONS -package com.mycompany.${JAVA_SWIG_PROJECT_NAME})

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/java/classes")
add_custom_command(
    TARGET ${JAVA_SWIG_PROJECT_NAME} POST_BUILD
    COMMAND "${Java_JAVAC_EXECUTABLE}" -d java/classes java/*.java
    COMMAND "${Java_JAR_EXECUTABLE}" -cfM java/${JAVA_SWIG_PROJECT_NAME}.jar -C java/classes .
)

# Store Path to native JAR in variable:
set(ASTRO_JAR "${CMAKE_CURRENT_BINARY_DIR}/${JAVA_SWIG_PROJECT_NAME}.jar")