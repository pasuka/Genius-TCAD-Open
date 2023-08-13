#cmake_minimum_required(VERSION 3.16)
PROJECT(GENIUS)

#set(CMAKE_VERBOSE_MAKEFILE on)

#message(${CMAKE_SYSTEM_PROCESSOR})

#cmake_host_system_information(RESULT PRETTY_NAME QUERY PROCESSOR_NAME)
#message(STATUS "${PRETTY_NAME}")

#cmake_host_system_information(RESULT PRETTY_NAME QUERY PROCESSOR_DESCRIPTION)
#message(STATUS "${PRETTY_NAME}")

#message(${CMAKE_SHARED_LIBRARY_SUFFIX})

if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

#-fplugin-arg-python-command='import gcc; help(gcc)'
#-fplugin-arg-python-arg='/mnt/github/gcc-callgraph-plugin/gcc-callgraph-plugin.py'
#-fplugin-arg-python-arg='/mnt/github/gcc-python-plugin/examples/show-callgraph.py'
SET(DEBUG_FLAGS "-O0 -ggdb -pg -fPIC -fno-omit-frame-pointer -fplugin=python -fplugin-arg-python-arg=/mnt/github/gcc-callgraph-plugin/gcc-callgraph-plugin.py -flto -flto-partition=none ")
SET(OPTIMIZE_FLAGS "-march=westmere -mtune=westmere -m64 -msse4.2 -mfpmath=sse+387 -O3  -funroll-loops -fno-omit-frame-pointer")

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DEBUG_FLAGS}")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEBUG_FLAGS}")
#set(CMAKE_CXX_FLAGS "${CMAKE_FORTRAN_FLAGS} ${DEBUG_FLAGS}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OPTIMIZE_FLAGS}")
set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS} ${OPTIMIZE_FLAGS}")
set(CMAKE_Fortran_FLAGS "${CMAKE_FORTRAN_FLAGS} ${OPTIMIZE_FLAGS}")

SET(INCLUDE_BASE ${CMAKE_SOURCE_DIR}/include)
SET(PETSC_INCLUDE $ENV{PETSC_DIR}/$ENV{PETSC_ARCH}/include)
SET(PETSC_ARCHIVE -L$ENV{PETSC_DIR}/$ENV{PETSC_ARCH}/lib -lpetsc)

SET(OMP_ARCHIVE $ENV{ONEAPI_ROOT}/compiler/latest/linux/compiler/lib/intel64_lin/libiomp5.so)

SET(BLAS_ARCHIVE $ENV{MKLROOT}/lib/intel64/libmkl_intel_lp64.so $ENV{MKLROOT}/lib/intel64/libmkl_gnu_thread.so $ENV{MKLROOT}/lib/intel64/libmkl_core.so)
SET(LAPACK_ARCHIVE $ENV{MKLROOT}/lib/intel64/libmkl_intel_lp64.so $ENV{MKLROOT}/lib/intel64/libmkl_gnu_thread.so $ENV{MKLROOT}/lib/intel64/libmkl_core.so)

#SET(SUPERLU_ARCHIVE ${PETSC_DIR}/lib/libsuperlu_4.0.a)
SET(MPI_INCLUDE $ENV{I_MPI_ROOT}/include/) #${PETSC_DIR}/include/mpiuni)
SET(MPI_ARCHIVE -L$ENV{I_MPI_ROOT}/lib -L$ENV{I_MPI_ROOT}/lib/release -lmpifort -lmpicxx -lmpi -lrt)

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

SET(HAVE_VTK 1)
SET(VTK_INCLUDE /usr/local/include/vtk-8.0)
SET(VTK_ARCHIVE -L/usr/local/lib/vtk-8.0 -lvtkIOCore-8.0 -lvtkIOXML-8.0 -lvtkIOXMLParser-8.0 -lvtkFiltersGeneral-8.0 -lvtkCommonCore-8.0 -lvtkCommonDataModel-8.0 -lvtkCommonExecutionModel-8.0 -lvtkCommonMath-8.0 -lvtkCommonMisc-8.0 -lvtkCommonSystem-8.0 -lvtkCommonTransforms-8.0 -lvtkalglib-8.0 -lvtkexpat-8.0 -lvtklz4-8.0 -lvtksys-8.0 -lvtkzlib-8.0 -lmetis)

SET(FLEX /usr/bin/flex)
SET(BISON /usr/bin/bison)
#SET(CGNS_INCLUDE ${PETSC_DIR}/include)
#SET(CGNS_ARCHIVE ${PETSC_DIR}/lib/libcgns.so)
SET(CGNS_INCLUDE /usr/bin/include)
SET(CGNS_ARCHIVE -lcgns)

INCLUDE_DIRECTORIES(
${PETSC_INCLUDE}
${MPI_INCLUDE}
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
