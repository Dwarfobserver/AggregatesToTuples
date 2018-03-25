
project(aggregates-to-tuples)
cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "tests/*.cpp")
add_executable(tests ${SOURCES})
target_include_directories(tests PUBLIC include)

enable_testing()
add_test(tests "${CMAKE_BINARY_DIR}/tests")
