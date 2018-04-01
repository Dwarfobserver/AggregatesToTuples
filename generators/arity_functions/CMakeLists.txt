
add_executable(make_arity_functions main.cpp)

target_compile_definitions(make_arity_functions PRIVATE
    TARGET_DIRECTORY="${CMAKE_SOURCE_DIR}/include/"
)
