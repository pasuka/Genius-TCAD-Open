
SET (CXX_SRCS
mixA3_boundary_gate.cc
mixA3_boundary_ohmic.cc
mixA3_boundary_schottky.cc
mixA3_boundary_solderpad.cc
mixA3.cc
)

INCLUDE_DIRECTORIES(${MXML_INCLUDE} ${SPICE_INCLUDE})
ADD_LIBRARY(solver_mixA3 ${CXX_SRCS})

