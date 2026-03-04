
set(CXX_SRCS
  tif3d.cc
)

add_library(tif3d STATIC ${CXX_SRCS})
target_include_directories(tif3d PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


