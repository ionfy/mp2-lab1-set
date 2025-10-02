file(GLOB cpp_list ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(sample_light ${cpp_list})
target_link_libraries(sample_light ${MP2_LIBRARY})
set_target_properties(sample_light PROPERTIES
    OUTPUT_NAME "${sample}"
    PROJECT_LABEL "${sample}"
    RUNTIME_OUTPUT_DIRECTORY "../")