
SET (CXX_SRCS
electrical_source.cc
field_source.cc
isource.cc
light_lenses.cc
light_source.cc
particle_source.cc
vsource.cc
waveform.cc
)

INCLUDE_DIRECTORIES(${MXML_INCLUDE} ${EXPREVAL_INCLUDE} ${CSABATHY_INCLUDE} ${NN_INCLUDE} ${ANN_INCLUDE} ${KDTREE_INCLUDE})
ADD_LIBRARY(source ${CXX_SRCS})

