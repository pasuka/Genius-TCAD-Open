
set(CXX_SRCS
  trex.c
)

add_library(trex STATIC ${CXX_SRCS})
target_include_directories(trex PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


