
# Core material files — built as a static library
set(CXX_SRCS
  adolc_init.cc
  material.cc
  material_define.cc
  physical_unit.cc
  PMI.cc
)

add_library(material STATIC ${CXX_SRCS})
target_include_directories(material PUBLIC ${CMAKE_SOURCE_DIR}/include/material)

# Material plugin subdirectories — each built as a MODULE library (loaded at runtime)
set(_material_subdirs
  Air
  Al
  AlGaAs
  Cu
  Diamond
  Elec
  GaAs
  Ge
  Nitride
  NPolySi
  PolySi
  PPolySi
  Si
  SiC4H
  SiO2
  TiSi2
  W
)

foreach(_mat ${_material_subdirs})
  file(GLOB _mat_srcs ${_mat}/*.cc)
  if(_mat_srcs)
    add_library(mat_${_mat} MODULE adolc_init.cc ${_mat_srcs})
    set_target_properties(mat_${_mat} PROPERTIES
      OUTPUT_NAME ${_mat}
      PREFIX ""
      SUFFIX ".so"
    )
    target_include_directories(mat_${_mat} PRIVATE
      ${CMAKE_SOURCE_DIR}/include
      ${CMAKE_SOURCE_DIR}/include/material
    )
    target_link_libraries(mat_${_mat} PRIVATE material)
    install(TARGETS mat_${_mat}
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/genius
    )
  endif()
endforeach()

