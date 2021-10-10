SET (SUBDIRS
contrib # generate brkpnts.h
base
bc
fe
geom
hook
interpolation
material
math
mesh
meshgen
parser
partition
quadrature
#sip
solution
solver
source
utils
)

FOREACH(SUB ${SUBDIRS})
ADD_SUBDIRECTORY(${SUB})
ENDFOREACH(SUB ${SUBDIRS})
INCLUDE_DIRECTORIES(${MXML_INCLUDE})
ADD_DEFINITIONS(-DPACKAGE_VERSION="\\\"${VERSION_STRING}\\\"")
SET(LIBRARIES
#solver_ddm_common
#solver_ddm1
#solver_ddm1r
#solver_ddm2
#solver_ddm_ac
#solver_dg
#solver_doping_analytic
#solver_ebm3
#solver_emfem2d
#solver_hall
#solver_hdm
#solver_mix1
#solver_mixA1
#solver_mixA2
#solver_mixA3
#solver_mole_analytic
#solver_poisson
#solver_ray_tracing
#solver_stress_solver
#
solution
source
solver
bc
solution
hook # after solution
meshgen # after solution
dfise # after solution
tif3d # after solution
stanford # after solution
solver
spline #after solver
fe # fe after solver
quadrature #after fe
#
interpolation
geom
mesh
material
parser
base
partition
math
utils
mxml
expreval
csabathy
spice
klu
nn
ann
triangle
trex
)
ADD_EXECUTABLE(genius main.cc)
TARGET_LINK_LIBRARIES(genius ${LIBRARIES} ${MPI_ARCHIVE} ${CGNS_ARCHIVE} ${VTK_ARCHIVE} ${PETSC_ARCHIVE} ${LAPACK_ARCHIVE} ${BLAS_ARCHIVE} ${MPI_ARCHIVE} -lgfortran -ldl)
ADD_CUSTOM_COMMAND(TARGET genius POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:genius> ${CMAKE_SOURCE_DIR}/bin
)

