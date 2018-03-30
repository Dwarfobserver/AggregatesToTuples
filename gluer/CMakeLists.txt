
add_executable(gluer gluer.cpp)

target_compile_definitions(gluer PRIVATE
    INCLUDES_DIRECTORY="${CMAKE_SOURCE_DIR}/include/"
    SINGLE_INCLUDE_DIRECTORY="${CMAKE_SOURCE_DIR}/single_include/"
)

