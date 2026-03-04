
set(CXX_SRCS
  linear_partitioner.cc
  metis_partitioner.cc
  parmetis_partitioner.cc
  partitioner.cc
)

add_library(partition STATIC ${CXX_SRCS})
target_include_directories(partition PUBLIC ${CMAKE_SOURCE_DIR}/include/partition)

