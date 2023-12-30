
set(rectangle_SOURCE_FILES
  rectangle.cpp
)

add_executable(rectangle ${rectangle_SOURCE_FILES})
target_link_libraries(rectangle glad glfw)


set(triangle_SOURCE_FILES
  triangle.cpp
)

add_executable(triangle ${triangle_SOURCE_FILES})
target_link_libraries(triangle glad glfw)