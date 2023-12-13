set(helloworld_SOURCE_FILES
  main.cpp
)

add_executable(helloworld ${helloworld_SOURCE_FILES})
target_link_libraries(helloworld glad glfw)