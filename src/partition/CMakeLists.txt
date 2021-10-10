
SET (CXX_SRCS
linear_partitioner.cc
metis_partitioner.cc
parmetis_partitioner.cc
partitioner.cc
)
#INCLUDE_DIRECTORIES(${TRIANGLE_INCLUDE})
ADD_LIBRARY(partition ${CXX_SRCS})

