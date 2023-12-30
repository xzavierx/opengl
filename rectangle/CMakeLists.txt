set(rectangle_SOURCE_FILES
  main.cpp
)

add_executable(rectangle ${rectangle_SOURCE_FILES})
target_link_libraries(rectangle glad glfw)