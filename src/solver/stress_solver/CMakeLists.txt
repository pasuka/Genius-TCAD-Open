
SET (CXX_SRCS
stress_solver.cc
)

INCLUDE_DIRECTORIES(${MXML_INCLUDE})
ADD_LIBRARY(solver_stress_solver ${CXX_SRCS})

