
SET (CXX_SRCS
mesh_generation_cy.cc
mesh_generation_cy2d.cc
mesh_generation_cy3d.cc
mesh_generation_quad4.cc
mesh_generation_struct.cc
mesh_generation_tri3.cc
)
INCLUDE_DIRECTORIES(${TRIANGLE_INCLUDE})
ADD_LIBRARY(meshgen ${CXX_SRCS})

