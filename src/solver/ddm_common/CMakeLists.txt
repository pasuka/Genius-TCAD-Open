
SET (CXX_SRCS
charge_integral.cc
ddm_solver.cc
gate_current.cc
inter_connect.cc
mixA_solver.cc
mix_inter_connect.cc
mix_solver.cc
mob_semiconductor.cc
)

INCLUDE_DIRECTORIES(${MXML_INCLUDE} ${EXPREVAL_INCLUDE} ${SPICE_INCLUDE})
ADD_LIBRARY(solver_ddm_common ${CXX_SRCS})

