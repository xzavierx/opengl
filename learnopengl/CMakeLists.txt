set(hello_triangle_SOURCE_FILES
  hello_triangle.cpp
)

add_executable(hello_triangle ${hello_triangle_SOURCE_FILES})
target_link_libraries(hello_triangle glad glfw)

set(hello_triangle_indexed_SOURCE_FILES
  hello_triangle_indexed.cpp
)

add_executable(hello_triangle_indexed ${hello_triangle_indexed_SOURCE_FILES})
target_link_libraries(hello_triangle_indexed glad glfw)

# shaders_uniform
set(shaders_uniform_SOURCE_FILES
  shaders_uniform.cpp
)

add_executable(shaders_uniform ${shaders_uniform_SOURCE_FILES})
target_link_libraries(shaders_uniform glad glfw)

set(hello_triangle_exercise1_SOURCE_FILES
  hello_triangle_exercise1.cpp
)

add_executable(hello_triangle_exercise1 ${hello_triangle_exercise1_SOURCE_FILES})
target_link_libraries(hello_triangle_exercise1 glad glfw)

# hello_triangle_exercise2
set(hello_triangle_exercise2_SOURCE_FILES
  hello_triangle_exercise2.cpp
)

add_executable(hello_triangle_exercise2 ${hello_triangle_exercise2_SOURCE_FILES})
target_link_libraries(hello_triangle_exercise2 glad glfw)

# hello_triangle_exercise3
set(hello_triangle_exercise3_SOURCE_FILES
  hello_triangle_exercise3.cpp
)

add_executable(hello_triangle_exercise3 ${hello_triangle_exercise3_SOURCE_FILES})
target_link_libraries(hello_triangle_exercise3 glad glfw)

# shaders_interpolation
set(shaders_interpolation_SOURCE_FILES
  shaders_interpolation.cpp
)

add_executable(shaders_interpolation ${shaders_interpolation_SOURCE_FILES})
target_link_libraries(shaders_interpolation glad glfw)