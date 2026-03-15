
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
target_link_libraries(material PUBLIC parser)

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

# material.cc constructs filenames as "lib<MaterialName>.dll" (Windows) or
# "lib<MaterialName>.so" (Linux/macOS), so the module libraries must carry the
# "lib" prefix and the platform-appropriate suffix to match at runtime.
if(WIN32)
  set(_mat_suffix ".dll")
else()
  set(_mat_suffix ".so")
endif()

foreach(_mat ${_material_subdirs})
  file(GLOB _mat_srcs ${_mat}/*.cc)
  if(_mat_srcs)
    add_library(mat_${_mat} MODULE adolc_init.cc ${_mat_srcs})
    set_target_properties(mat_${_mat} PROPERTIES
      OUTPUT_NAME ${_mat}
      PREFIX "lib"
      SUFFIX ${_mat_suffix}
    )
    target_include_directories(mat_${_mat} PRIVATE
      ${CMAKE_SOURCE_DIR}/include
      ${CMAKE_SOURCE_DIR}/include/material
    )
    target_link_libraries(mat_${_mat} PRIVATE material)
    install(TARGETS mat_${_mat}
      LIBRARY DESTINATION lib
      RUNTIME DESTINATION lib
    )
  endif()
endforeach()

