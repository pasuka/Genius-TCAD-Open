
SET (CXX_SRCS
mixA2_boundary_gate.cc
mixA2_boundary_ohmic.cc
mixA2_boundary_schottky.cc
mixA2_boundary_solderpad.cc
mixA2.cc
)

INCLUDE_DIRECTORIES(${MXML_INCLUDE} ${SPICE_INCLUDE})
ADD_LIBRARY(solver_mixA2 ${CXX_SRCS})

