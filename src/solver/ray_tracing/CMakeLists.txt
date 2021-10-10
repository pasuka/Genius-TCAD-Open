
SET (CXX_SRCS
light_thread.cc
object_tree.cc
ray_tracing.cc
)

INCLUDE_DIRECTORIES(${MXML_INCLUDE} ${EXPREVAL_INCLUDE})
ADD_LIBRARY(solver_ray_tracing ${CXX_SRCS})

