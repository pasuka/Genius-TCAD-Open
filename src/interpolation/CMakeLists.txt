
set(CXX_SRCS
  interpolation_1d_linear.cc
  interpolation_1d_spline.cc
  interpolation_2d_csa.cc
  interpolation_2d_nn.cc
  interpolation_3d_nbtet.cc
  interpolation_3d_qshep.cc
)

add_library(interpolation STATIC ${CXX_SRCS})
target_include_directories(interpolation PUBLIC
  ${CMAKE_SOURCE_DIR}/include/interpolation
  ${CMAKE_SOURCE_DIR}/src/contrib/csabathy
)
target_link_libraries(interpolation PRIVATE csabathy ann nn)

