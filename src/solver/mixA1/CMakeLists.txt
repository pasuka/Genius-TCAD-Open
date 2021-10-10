
SET (CXX_SRCS
mixA1_boundary_gate.cc
mixA1_boundary_ohmic.cc
mixA1_boundary_schottky.cc
mixA1_boundary_solderpad.cc
mixA1.cc
)

INCLUDE_DIRECTORIES(${MXML_INCLUDE} ${SPICE_INCLUDE})
ADD_LIBRARY(solver_mixA1 ${CXX_SRCS})

