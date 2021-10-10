
SET (CXX_SRCS
mix1_boundary_gate.cc
mix1_boundary_ohmic.cc
mix1_boundary_schottky.cc
mix1_boundary_solderpad.cc
mix1.cc
)

INCLUDE_DIRECTORIES(${MXML_INCLUDE} ${SPICE_INCLUDE})
ADD_LIBRARY(solver_mix1 ${CXX_SRCS})

