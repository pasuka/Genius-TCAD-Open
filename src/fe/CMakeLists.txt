
SET (CXX_SRCS
fe_base.cc
fe_boundary.cc
fe.cc
fe_hermite.cc
fe_hermite_shape_1D.cc
fe_hermite_shape_2D.cc
fe_hermite_shape_3D.cc
fe_lagrange.cc
fe_lagrange_shape_0D.cc
fe_lagrange_shape_1D.cc
fe_lagrange_shape_2D.cc
fe_lagrange_shape_3D.cc
fe_map.cc
number_lookups.cc
)

ADD_LIBRARY(fe ${CXX_SRCS})

