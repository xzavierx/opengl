set(SOURCE_FILES
  src/glad.c
)

add_library(glad ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(glad PUBLIC ./include)