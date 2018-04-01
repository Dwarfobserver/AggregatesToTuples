
add_executable(make_single_header main.cpp)

target_compile_definitions(make_single_header PRIVATE
    INCLUDES_DIRECTORY="${CMAKE_SOURCE_DIR}/include/"
    TARGET_DIRECTORY="${CMAKE_SOURCE_DIR}/single_include/"
)
