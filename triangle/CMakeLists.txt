set(triangle_SOURCE_FILES
  main.cpp
)

add_executable(triangle ${triangle_SOURCE_FILES})
target_link_libraries(triangle glad glfw)