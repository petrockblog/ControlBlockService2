cmake_minimum_required(VERSION 2.8.5)

add_subdirectory(lib/googletest)

include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}/
        ${gmock_SOURCE_DIR}/include
        ${gmock_SOURCE_DIR}/
)

add_executable(sample_tests controlblock/sampletest.cpp)
target_link_libraries(sample_tests gtest gtest_main)