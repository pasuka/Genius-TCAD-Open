
set(CXX_SRCS
  csa.cc
  svd.c
)

add_library(csabathy STATIC ${CXX_SRCS})
target_include_directories(csabathy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

