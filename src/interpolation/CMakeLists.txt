
SET (CXX_SRCS
interpolation_1d_linear.cc
interpolation_1d_spline.cc
interpolation_2d_csa.cc
interpolation_2d_nn.cc
interpolation_3d_nbtet.cc
interpolation_3d_qshep.cc
)
INCLUDE_DIRECTORIES(${CSABATHY_INCLUDE})
INCLUDE_DIRECTORIES(${NN_INCLUDE})
INCLUDE_DIRECTORIES(${ANN_INCLUDE})
ADD_LIBRARY(interpolation ${CXX_SRCS})

