
SET (CXX_SRCS
boundary_info.cc
boundary_mesh.cc
mesh_base.cc
mesh_communication.cc
mesh_modification.cc
mesh_refinement.cc
mesh_refinement_flagging.cc
mesh_refinement_smoothing.cc
mesh_tools.cc
serial_mesh.cc
serial_mesh_iterators.cc
unstructured_mesh.cc
)
#INCLUDE_DIRECTORIES(${EXPREVAL_INCLUDE})
ADD_LIBRARY(mesh ${CXX_SRCS})

