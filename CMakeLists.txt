PROJECT(GENIUS)
SET(INCLUDE_BASE ${CMAKE_SOURCE_DIR}/include)
SET(PETSC_INCLUDE ${PETSC_DIR}/include)
SET(PETSC_ARCHIVE -L${PETSC_DIR}/lib -lpetsc)
SET(BLAS_ARCHIVE /opt/intel/mkl/lib/intel64/libmkl_intel_lp64.so /opt/intel/mkl/lib/intel64/libmkl_gnu_thread.so /opt/intel/mkl/lib/intel64/libmkl_core.so)
SET(LAPACK_ARCHIVE /opt/intel/mkl/lib/intel64/libmkl_intel_lp64.so /opt/intel/mkl/lib/intel64/libmkl_gnu_thread.so /opt/intel/mkl/lib/intel64/libmkl_core.so)
#SET(SUPERLU_ARCHIVE ${PETSC_DIR}/lib/libsuperlu_4.0.a)
SET(MPI_INCLUDE /opt/intel/compilers_and_libraries_2019.0.117/linux/mpi/intel64/include) #${PETSC_DIR}/include/mpiuni)
SET(MPI_ARCHIVE -L/opt/intel/compilers_and_libraries_2019.0.117/linux/mpi/intel64/lib/release -L/opt/intel/compilers_and_libraries_2019.0.117/linux/mpi/intel64/lib -lmpifort -lmpicxx -lmpi -lrt)
SET(MXML_INCLUDE ${CMAKE_SOURCE_DIR}/src/contrib/mxml)
SET(TREX_INCLUDE ${CMAKE_SOURCE_DIR}/src/contrib/trex)
SET(SPICE_INCLUDE ${CMAKE_SOURCE_DIR}/src/contrib/spice)
SET(KDTREE_INCLUDE ${CMAKE_SOURCE_DIR}/src/contrib/kdtree)
SET(CSABATHY_INCLUDE ${CMAKE_SOURCE_DIR}/src/contrib/csabathy)
SET(NN_INCLUDE ${CMAKE_SOURCE_DIR}/src/contrib/nn)
SET(ANN_INCLUDE ${CMAKE_SOURCE_DIR}/src/contrib/ann)
SET(EXPREVAL_INCLUDE ${CMAKE_SOURCE_DIR}/src/contrib/expreval)
SET(TRIANGLE_INCLUDE ${CMAKE_SOURCE_DIR}/src/contrib/triangle)
SET(DFISE_INCLUDE ${CMAKE_SOURCE_DIR}/src/contrib/dfise)
SET(STANFORD_INCLUDE ${CMAKE_SOURCE_DIR}/src/contrib/stanford)
SET(TIF3D_INCLUDE ${CMAKE_SOURCE_DIR}/src/contrib/tif3d)
SET(TIF_INCLUDE ${CMAKE_SOURCE_DIR}/src/contrib/tif)
SET(SPLINE_INCLUDE ${CMAKE_SOURCE_DIR}/src/contrib/spline)
SET(VTK_INCLUDE /usr/local/include/vtk-5.8)
SET(VTK_ARCHIVE -L/usr/local/lib/vtk-5.8 -lvtkIO -lvtkFiltering -lvtkCommon -lmetis)
SET(FLEX /usr/bin/flex)
SET(BISON /usr/bin/bison)
SET(HAVE_VTK 1)
#SET(CGNS_INCLUDE ${PETSC_DIR}/include)
#SET(CGNS_ARCHIVE ${PETSC_DIR}/lib/libcgns.so)
SET(CGNS_INCLUDE /usr/bin/include)
SET(CGNS_ARCHIVE -lcgns)
INCLUDE_DIRECTORIES(${PETSC_INCLUDE} ${MPI_INCLUDE}
${INCLUDE_BASE}
${INCLUDE_BASE}/base
${INCLUDE_BASE}/bc
${INCLUDE_BASE}/enums
${INCLUDE_BASE}/fe
${INCLUDE_BASE}/geom
${INCLUDE_BASE}/hook
${INCLUDE_BASE}/interpolation
${INCLUDE_BASE}/material
${INCLUDE_BASE}/math
${INCLUDE_BASE}/mesh
${INCLUDE_BASE}/meshgen
${INCLUDE_BASE}/parser
${INCLUDE_BASE}/partition
${INCLUDE_BASE}/quadrature
${INCLUDE_BASE}/solution
${INCLUDE_BASE}/solver
${INCLUDE_BASE}/solver/ddm1
${INCLUDE_BASE}/solver/ddm1r
${INCLUDE_BASE}/solver/ddm2
${INCLUDE_BASE}/solver/ddm_ac
${INCLUDE_BASE}/solver/dg
${INCLUDE_BASE}/solver/doping_analytic
${INCLUDE_BASE}/solver/ebm3
${INCLUDE_BASE}/solver/emfem2d
${INCLUDE_BASE}/solver/hall
${INCLUDE_BASE}/solver/hdm
${INCLUDE_BASE}/solver/mix1
${INCLUDE_BASE}/solver/mixA1
${INCLUDE_BASE}/solver/mixA2
${INCLUDE_BASE}/solver/mixA3
${INCLUDE_BASE}/solver/mole_analytic
${INCLUDE_BASE}/solver/poisson
${INCLUDE_BASE}/solver/ray_tracing
${INCLUDE_BASE}/solver/stress_solver
${INCLUDE_BASE}/source
${INCLUDE_BASE}/utils
)
SET(VERSION_STRING luther)
ADD_SUBDIRECTORY(src)
