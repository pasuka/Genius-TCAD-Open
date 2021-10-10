
SET (CXX_SRCS
boundary_condition.cc
boundary_condition_collector.cc
boundary_mos_channel_elem.cc
boundary_nearest_point.cc
)
INCLUDE_DIRECTORIES(${MXML_INCLUDE} ${TREX_INCLUDE})
ADD_LIBRARY(bc ${CXX_SRCS})

