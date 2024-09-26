
# SWIG-Python
set(PY_SWIG_PROJECT_NAME py${PROJECT_NAME})

set(Python3_INCLUDE_DIR /usr/include/python3.12)
set(Python3_LIBRARY /usr/bin/python3.12)

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
    COMMAND "${Java_JAR_EXECUTABLE}" -cfM java/${JAVA_SWIG_PROJECT_NAME}.jar -C java/classes . java/lib${JAVA_SWIG_PROJECT_NAME}.so
)

# Store Path to native JAR in variable:
set(ASTRO_JAR "${CMAKE_CURRENT_BINARY_DIR}/${JAVA_SWIG_PROJECT_NAME}.jar")