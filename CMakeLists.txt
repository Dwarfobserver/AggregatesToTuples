
project(aggregates-to-tuples)
cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 17)

# Set MAKE_GENERATORS to true to build the generator programs instead of the tests

if (MAKE_GENERATORS)
    # Anchor executables destination
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY         ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})

    # Add programs which make the single header and the arity functions
    add_subdirectory(generators)
else()
    # Add tests
    file(GLOB SOURCES "tests/*.cpp")
    add_executable(tests ${SOURCES})
    target_include_directories(tests PUBLIC include)

    # Enable tests with ctest
    enable_testing()
    add_test(tests "${CMAKE_BINARY_DIR}/tests")
endif()
