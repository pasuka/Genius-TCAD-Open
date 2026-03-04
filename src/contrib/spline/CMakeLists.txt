
set(CXX_SRCS
  spline.cc
)

add_library(spline STATIC ${CXX_SRCS})
target_include_directories(spline PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


