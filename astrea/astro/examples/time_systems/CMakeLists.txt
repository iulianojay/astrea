
# Example
set(EXAMPLE_NAME time_systems)
add_executable             (${EXAMPLE_NAME}_ex ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
set_target_properties      (${EXAMPLE_NAME}_ex PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
target_include_directories (${EXAMPLE_NAME}_ex PUBLIC ${ASTRO_DIRS})
target_link_libraries      (${EXAMPLE_NAME}_ex PUBLIC ${PROJECT_NAME}_shared)