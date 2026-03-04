
set(CXX_SRCS
  delaunay.cc
  istack.cc
  lpi.cc
)

add_library(nn STATIC ${CXX_SRCS})
target_include_directories(nn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


