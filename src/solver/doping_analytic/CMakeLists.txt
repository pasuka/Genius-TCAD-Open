
SET (CXX_SRCS
doping_analytic.cc
doping_fun.cc
)

INCLUDE_DIRECTORIES(${MXML_INCLUDE} ${CSABATHY_INCLUDE} ${NN_INCLUDE} ${ANN_INCLUDE})
ADD_LIBRARY(solver_doping_analytic ${CXX_SRCS})

