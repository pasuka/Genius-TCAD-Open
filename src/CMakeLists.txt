add_subdirectory(contrib)
add_subdirectory(base)
add_subdirectory(bc)
add_subdirectory(fe)
add_subdirectory(geom)
add_subdirectory(hook)
add_subdirectory(interpolation)
add_subdirectory(material)
add_subdirectory(math)
add_subdirectory(mesh)
add_subdirectory(meshgen)
add_subdirectory(parser)
add_subdirectory(partition)
add_subdirectory(quadrature)
add_subdirectory(solution)
add_subdirectory(solver)
add_subdirectory(source)
add_subdirectory(utils)

# ── Main executable ──────────────────────────────────────────────────────────

add_executable(genius main.cc)

target_compile_definitions(genius PRIVATE
  PACKAGE_VERSION="${GENIUS_VERSION_STRING}"
)

# Core static libraries (link order matters for static linking)
set(_genius_core_libs
  solution
  source
  solver
  bc
  hook
  meshgen
  dfise
  tif3d
  stanford
  spline
  fe
  quadrature
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

target_link_libraries(genius PRIVATE
  ${_genius_core_libs}
  MPI::MPI_CXX
  PETSc::PETSc
  ${LAPACK_LIBRARIES}
  ${BLAS_LIBRARIES}
  ${CMAKE_DL_LIBS}
  gfortran
)

if(GENIUS_ENABLE_VTK AND VTK_FOUND)
  target_link_libraries(genius PRIVATE ${VTK_LIBRARIES})
  # VTK 9+ requires vtk_module_autoinit so that VTK object factories
  # (readers, writers, etc.) are properly registered at start-up.
  if(COMMAND vtk_module_autoinit)
    vtk_module_autoinit(TARGETS genius MODULES ${VTK_LIBRARIES})
  endif()
endif()

if(GENIUS_ENABLE_CGNS AND CGNS_LIBRARY)
  target_link_libraries(genius PRIVATE ${CGNS_LIBRARY})
  target_include_directories(genius PRIVATE ${CGNS_INCLUDE_DIR})
endif()

if(GENIUS_ENABLE_HDF5 AND HDF5_FOUND)
  target_link_libraries(genius PRIVATE ${HDF5_LIBRARIES})
endif()

# ── Install rules ────────────────────────────────────────────────────────────

install(TARGETS genius
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/lib/
  DESTINATION ${CMAKE_INSTALL_DATADIR}/genius
  FILES_MATCHING
    PATTERN "*.xml"
    PATTERN "*.def"
)

