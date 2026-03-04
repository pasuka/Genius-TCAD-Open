
set(CXX_SRCS
  boundary_condition.cc
  boundary_condition_collector.cc
  boundary_mos_channel_elem.cc
  boundary_nearest_point.cc
)

add_library(bc STATIC ${CXX_SRCS})
target_include_directories(bc PUBLIC ${CMAKE_SOURCE_DIR}/include/bc)

