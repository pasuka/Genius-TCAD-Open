
set(CXX_SRCS
  triangle.c
)

add_library(triangle STATIC ${CXX_SRCS})
target_compile_definitions(triangle PUBLIC TRILIBRARY)
target_include_directories(triangle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})



