cmake_minimum_required(VERSION 3.28.3)

# Test build function
function(build_tests CURRENT_PROJECT TEST_TYPE TEST_FILES)

    foreach(TEST_FILE ${TEST_FILES})

        message(" -- Building Test: ${TEST_FILE}")

        # Get executable name and build target
        if (${TEST_TYPE} STREQUAL "UNIT")
            get_filename_component(TEST_EXE ${TEST_FILE} NAME_WE)
        else()
            cmake_path(GET TEST_FILE PARENT_PATH full_parent_path)
            get_filename_component(TEST_EXE ${full_parent_path} NAME)
        endif()
        set(TEST_EXE ${TEST_EXE}.test)
        add_executable(${TEST_EXE} ${TEST_FILE})

        # Set properties
        target_compile_options(${TEST_EXE} PUBLIC -Wno-parentheses -Wno-unused-but-set-variable -Wno-unused-variable -Wno-unused-local-typedefs)
        set_target_properties(${TEST_EXE} PROPERTIES OUTPUT_NAME ${TEST_EXE})
        set(GTEST_CREATE_SHARED_LIBRARY 1)
        set(BUILD_GMOCK OFF)

        # Includes
        target_include_directories(${TEST_EXE} PRIVATE ${CMAKE_INSTALL_PREFIX}/include ${CMAKE_INSTALL_PREFIX}/extern)

        # Dependencies
        target_link_libraries(${TEST_EXE} PRIVATE ${CURRENT_PROJECT}_shared GTest::gtest_main)

        # Install
        if (${TEST_TYPE} STREQUAL "UNIT")
            set_target_properties(${TEST_EXE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin/unit)
        else()
            set_target_properties(${TEST_EXE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin/regression)
        endif()

        # Send to gtest
        gtest_discover_tests(${TEST_EXE} DISCOVERY_MODE PRE_TEST)

        add_dependencies(${CURRENT_PROJECT}_tests ${TEST_EXE})

    endforeach(TEST_FILE ${TEST_FILES})

endfunction()

# Example build function
function(build_examples CURRENT_PROJECT EXAMPLE_FILES)

    foreach(EXAMPLE_FILE ${EXAMPLE_FILES})

        cmake_path(GET EXAMPLE_FILE PARENT_PATH EXAMPLE_DIRECTORY)
        get_filename_component(EXAMPLE_NAME ${EXAMPLE_DIRECTORY} NAME)

        message(" -- Building Example: ${EXAMPLE_NAME}")

        add_executable         (${EXAMPLE_NAME} ${EXAMPLE_FILE})
        set_target_properties  (${EXAMPLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${EXAMPLE_DIRECTORY}/bin)
        target_compile_options (${EXAMPLE_NAME} PUBLIC -Wno-parentheses -Wno-unused-but-set-variable -Wno-unused-variable -Wno-unused-local-typedefs)
        target_link_libraries  (${EXAMPLE_NAME} PUBLIC ${CURRENT_PROJECT}_shared)

    endforeach(EXAMPLE_FILE ${EXAMPLE_FILES})

endfunction()

function(generate_ephemeris_files PROJECT_SOURCE_DIRECTORY)

    set(PLANETARY_BASE ${ASTRO_BASE}/systems/planetary_bodies)
    set(BODY_HEADERS "")
    set(BODY_SOURCES "")

    message(" -- Ephemeris Generation Options:")
    message(" ---- BUILD_SUN: ${BUILD_SUN}")
    message(" ---- BUILD_MERCURY: ${BUILD_MERCURY}")
    message(" ---- BUILD_EARTH: ${BUILD_EARTH}")
    message(" ---- BUILD_MARS: ${BUILD_MARS}")
    message(" ---- BUILD_VENUS: ${BUILD_VENUS}")
    message(" ---- BUILD_JUPITER: ${BUILD_JUPITER}")
    message(" ---- BUILD_SATURN: ${BUILD_SATURN}")
    message(" ---- BUILD_URANUS: ${BUILD_URANUS}")
    message(" ---- BUILD_NEPTUNE: ${BUILD_NEPTUNE}")

    set(SYSTEM_BODIES "")
    set(BODY_EPHEMERIS_HEADERS "")
    set(BODY_EPHEMERIS_SOURCES "")
    if (${BUILD_SUN})
        build_system_ephemeris(Sun Sun)
    endif()

    if (${BUILD_MERCURY})
        build_system_ephemeris(Mercury Mercury)
    endif()

    if (${BUILD_VENUS})
        build_system_ephemeris(Venus Venus)
    endif()

    set(ALL_DEFINES "")
    if (${BUILD_EARTH})
        set(SYSTEM_BODIES Earth Moon)
        build_system_ephemeris(Earth "${SYSTEM_BODIES}")
        set(ALL_DEFINES ${ALL_DEFINES} ASTREA_BUILD_EARTH_EPHEMERIS)
    endif()

    if (${BUILD_MARS})
        set(SYSTEM_BODIES Mars) # Phobos Deimos)
        build_system_ephemeris(Mars "${SYSTEM_BODIES}")
        set(ALL_DEFINES ${ALL_DEFINES} ASTREA_BUILD_MARS_EPHEMERIS)
    endif()
    
    if (${BUILD_JUPITER})
        set(SYSTEM_BODIES Jupiter) # Io Europa Ganymede Callisto)
        build_system_ephemeris(Jupiter "${SYSTEM_BODIES}")
        set(ALL_DEFINES ${ALL_DEFINES} ASTREA_BUILD_JUPITER_EPHEMERIS)
    endif()

    if (${BUILD_SATURN})
        set(SYSTEM_BODIES Saturn) # Titan Rhea Iapetus)
        build_system_ephemeris(Saturn "${SYSTEM_BODIES}")
        set(ALL_DEFINES ${ALL_DEFINES} ASTREA_BUILD_SATURN_EPHEMERIS)
    endif()

    if (${BUILD_URANUS})
        set(SYSTEM_BODIES Uranus) # Titania Oberon)
        build_system_ephemeris(Uranus "${SYSTEM_BODIES}")
        set(ALL_DEFINES ${ALL_DEFINES} ASTREA_BUILD_URANUS_EPHEMERIS)
    endif()

    if (${BUILD_NEPTUNE})
        set(SYSTEM_BODIES Neptune) # Triton)
        build_system_ephemeris(Neptune "${SYSTEM_BODIES}")
        set(ALL_DEFINES ${ALL_DEFINES} ASTREA_BUILD_NEPTUNE_EPHEMERIS)
    endif()
    set(EPHEMERIS_COMPILE_DEFINES ${ALL_DEFINES} PARENT_SCOPE)
    
    string(REPLACE ";"  ", " PRINTABLE_BODIES "${ALL_BODIES}")
    message(" -- Bodies to Compile Ephemerides for: " ${PRINTABLE_BODIES})
    string(REPLACE ";"  "\n\t" PRINTABLE_HEADERS "${BODY_EPHEMERIS_HEADERS}")
    string(REPLACE ";"  "\n\t" PRINTABLE_SOURCES "${BODY_EPHEMERIS_SOURCES}")
    message(" -- Compiled Ephemeride HEADERS: \n\t" ${PRINTABLE_HEADERS})
    message(" -- Compiled Ephemeride SOURCES: \n\t" ${PRINTABLE_SOURCES})
    
    string(REPLACE ";"  " " PYTHONIC_BODIES "${ALL_BODIES}")
    add_custom_command(
        OUTPUT
            ${BODY_EPHEMERIS_HEADERS}
            ${BODY_EPHEMERIS_SOURCES}
        COMMAND python3 ${PROJECT_SOURCE_DIRECTORY}/pyastro/jpl_ephemeris_parser.py -o ${CMAKE_CURRENT_BINARY_DIR}/include/ephemerides --bodies ${PYTHONIC_BODIES}
        DEPENDS
            ${PROJECT_SOURCE_DIRECTORY}/pyastro/jpl_ephemeris_parser.py
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIRECTORY}
        COMMENT " -- Generating Ephemerides for: ${PRINTABLE_BODIES}"
    )
    add_custom_target(generated_ephemerides 
        DEPENDS ${BODY_EPHEMERIS_HEADERS} ${BODY_EPHEMERIS_SOURCES}
    )

    set(ASTRO_HEADERS ${ASTRO_HEADERS} ${BODY_EPHEMERIS_HEADERS} PARENT_SCOPE)
    set(ASTRO_SOURCES ${ASTRO_SOURCES} ${BODY_EPHEMERIS_SOURCES} PARENT_SCOPE)

endfunction()

function(build_system_ephemeris BODY_SYSTEM SYSTEM_BODIES)

    set(ALL_BODIES ${ALL_BODIES} ${SYSTEM_BODIES} PARENT_SCOPE)
    set(PLANETARY_BASE ${CMAKE_CURRENT_BINARY_DIR}/include/ephemerides)

    set(ALL_EPHEMERIS_HEADERS "")
    set(ALL_EPHEMERIS_SOURCES "")
    foreach(BODY ${SYSTEM_BODIES})

        if (BODY STREQUAL "Earth")
            set(ALL_EPHEMERIS_HEADERS ${ALL_EPHEMERIS_HEADERS} "${PLANETARY_BASE}/${BODY_SYSTEM}/EarthFromEmbEphemerisTable.hpp")
            set(ALL_EPHEMERIS_SOURCES ${ALL_EPHEMERIS_SOURCES} "${PLANETARY_BASE}/${BODY_SYSTEM}/EarthFromEmbEphemerisTable.cpp")
            set(ALL_EPHEMERIS_HEADERS ${ALL_EPHEMERIS_HEADERS} "${PLANETARY_BASE}/${BODY_SYSTEM}/EMBEphemerisTable.hpp")
            set(ALL_EPHEMERIS_SOURCES ${ALL_EPHEMERIS_SOURCES} "${PLANETARY_BASE}/${BODY_SYSTEM}/EMBEphemerisTable.cpp")
        elseif (BODY STREQUAL "Moon")
            set(ALL_EPHEMERIS_HEADERS ${ALL_EPHEMERIS_HEADERS} "${PLANETARY_BASE}/${BODY_SYSTEM}/MoonGcrfTable.hpp")
            set(ALL_EPHEMERIS_SOURCES ${ALL_EPHEMERIS_SOURCES} "${PLANETARY_BASE}/${BODY_SYSTEM}/MoonGcrfTable.cpp")
        else()
            set(ALL_EPHEMERIS_HEADERS ${ALL_EPHEMERIS_HEADERS} "${PLANETARY_BASE}/${BODY_SYSTEM}/${BODY}EphemerisTable.hpp")
            set(ALL_EPHEMERIS_SOURCES ${ALL_EPHEMERIS_SOURCES} "${PLANETARY_BASE}/${BODY_SYSTEM}/${BODY}EphemerisTable.cpp")
        endif()

    endforeach()
    
    set(BODY_EPHEMERIS_HEADERS ${BODY_EPHEMERIS_HEADERS} ${ALL_EPHEMERIS_HEADERS} PARENT_SCOPE)
    set(BODY_EPHEMERIS_SOURCES ${BODY_EPHEMERIS_SOURCES} ${ALL_EPHEMERIS_SOURCES} PARENT_SCOPE)

endfunction()