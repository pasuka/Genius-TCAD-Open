
SET (CXX_SRCS
edge.cc
edge_edge2.cc
edge_edge2_fvm.cc
elem.cc
elem_refinement.cc
face_cy_quad4_fvm.cc
face_cy_tri3_fvm.cc
face_quad4.cc
face_quad4_fvm.cc
face_quad.cc
face_tri3.cc
face_tri3_fvm.cc
face_tri.cc
node_elem.cc
plane.cc
polygon.cc
polygon_usample.cc
sphere.cc
)

ADD_LIBRARY(geom ${CXX_SRCS})

