
project(aggregates-to-tuples)
cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 17)

# Add tests

file(GLOB SOURCES "tests/*.cpp")
add_executable(tests ${SOURCES})
target_include_directories(tests PUBLIC include)

enable_testing()
add_test(tests "${CMAKE_BINARY_DIR}/tests")

# Add programs which make the single header and the arity functions

add_subdirectory(generators)
