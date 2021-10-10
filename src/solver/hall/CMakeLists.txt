
SET (CXX_SRCS
hall.cc
hall_conductor.cc
hall_insulator.cc
hall_resistance.cc
hall_semiconductor.cc
)

INCLUDE_DIRECTORIES(${MXML_INCLUDE})
ADD_LIBRARY(solver_hall ${CXX_SRCS})

