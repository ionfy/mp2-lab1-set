file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_executable(sample_light ${srcs} ${hdrs})
target_link_libraries(sample_light ${MP2_LIBRARY})