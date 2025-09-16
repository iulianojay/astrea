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