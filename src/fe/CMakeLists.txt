
set(CXX_SRCS
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

add_library(fe STATIC ${CXX_SRCS})
target_include_directories(fe PUBLIC ${CMAKE_SOURCE_DIR}/include/fe)

