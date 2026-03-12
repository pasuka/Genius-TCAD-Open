
set(CXX_SRCS
  cgns_io.cc
  conductor_region.cc
  control.cc
  dfise_io.cc
  external_circuit.cc
  external_circuit_pi.cc
  external_circuit_rcl.cc
  external_circuit_rct.cc
  fvm_cell_data.cc
  fvm_node_data.cc
  fvm_node_info.cc
  gdml_io.cc
  gmsh_io.cc
  insulator_region.cc
  location_io.cc
  pml_region.cc
  resistance_region.cc
  semiconductor_region.cc
  simulation_region.cc
  simulation_system.cc
  solution_define.cc
  stanford_io.cc
  tif3d_io.cc
  #tif_io.cc
  unv_io.cc
  vacuum_region.cc
  variable_define.cc
  vtk2_io.cc
  vtk_io.cc
)

if(GENIUS_ENABLE_VTK AND VTK_FOUND)
  add_definitions(-DHAVE_VTK)
endif()

add_library(solution STATIC ${CXX_SRCS})
target_include_directories(solution PUBLIC ${CMAKE_SOURCE_DIR}/include/solution)
target_link_libraries(solution PRIVATE tif3d stanford expreval)
if(GENIUS_ENABLE_VTK AND VTK_FOUND)
  target_include_directories(solution PRIVATE ${VTK_INCLUDE_DIRS})
endif()
if(GENIUS_ENABLE_CGNS AND CGNS_INCLUDE_DIR)
  target_include_directories(solution PRIVATE ${CGNS_INCLUDE_DIR})
endif()

