
SET (CXX_SRCS
dg_boundary_homo_interface.cc
dg_boundary_is_interface.cc
dg_boundary_ohmic.cc
dg_boundary_resistance_ohmic.cc
dg.cc
dg_conductor.cc
dg_insulator.cc
dg_resistance.cc
dg_semiconductor.cc
)

INCLUDE_DIRECTORIES(${MXML_INCLUDE})
ADD_LIBRARY(solver_dg ${CXX_SRCS})

