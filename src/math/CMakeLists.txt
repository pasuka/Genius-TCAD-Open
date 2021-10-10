
SET (CXX_SRCS
adolc_init.cc
csr_matrix.cc
dense_matrix_base.cc
dense_matrix.cc
dense_vector_base.cc
dense_vector.cc
expr_evaluate.cc
numeric_vector.cc
petsc_matrix.cc
petsc_type.cc
petsc_utils.cc
petsc_vector.cc
sparse_matrix.cc
symbolic_matrix.cc
type_tensor.cc
type_vector.cc
)
INCLUDE_DIRECTORIES(${EXPREVAL_INCLUDE})
ADD_LIBRARY(math ${CXX_SRCS})

