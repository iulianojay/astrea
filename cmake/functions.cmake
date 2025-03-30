cmake_minimum_required(VERSION 3.31.6)

# Test build function
function(build_tests TEST_TYPE TEST_FILES)

    foreach(TEST_FILE ${TEST_FILES})

        # Get executable name and build target
        if (${TEST_TYPE} STREQUAL "UNIT")
            get_filename_component(TEST_EXE ${TEST_FILE} NAME_WE)
        else()
            cmake_path(GET TEST_FILE PARENT_PATH full_parent_path)
            get_filename_component(TEST_EXE ${full_parent_path} NAME)
        endif()
        add_executable(${TEST_EXE} ${TEST_FILE})    

        # Set properties
        set_target_properties(${TEST_EXE} PROPERTIES OUTPUT_NAME ${TEST_EXE}.exe)
        set(GTEST_CREATE_SHARED_LIBRARY 1)
        set(BUILD_GMOCK OFF)

        # Includes
        target_include_directories(${TEST_EXE} PRIVATE ${CMAKE_INSTALL_PREFIX}/include)

        # Dependencies
        target_link_libraries(${TEST_EXE} PRIVATE ${PROJECT_NAME}_shared GTest::gtest_main)

        # Send to gtest
        gtest_discover_tests(${TEST_EXE})

        # Install
        if (${TEST_TYPE} STREQUAL "UNIT")
            install(TARGETS ${TEST_EXE} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/../tests/${PROJECT_NAME}/unit)
        else()
            install(TARGETS ${TEST_EXE} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/../tests/${PROJECT_NAME}/regression)
        endif()

        add_dependencies(${PROJECT_NAME}_tests ${TEST_EXE})

    endforeach(TEST_FILE ${TEST_FILES})

endfunction()
