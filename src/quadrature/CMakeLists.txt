
SET (CXX_SRCS
quadrature_build.cc
quadrature.cc
quadrature_conical_2D.cc
quadrature_conical_3D.cc
quadrature_conical.cc
quadrature_gauss_1D.cc
quadrature_gauss_2D.cc
quadrature_gauss_3D.cc
quadrature_gauss.cc
quadrature_jacobi_1D.cc
)
#INCLUDE_DIRECTORIES(${TRIANGLE_INCLUDE})
ADD_LIBRARY(quadrature ${CXX_SRCS})

