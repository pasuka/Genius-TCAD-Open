
set(CXX_SRCS
  boundary_info.cc
  boundary_mesh.cc
  mesh_base.cc
  mesh_communication.cc
  mesh_modification.cc
  mesh_refinement.cc
  mesh_refinement_flagging.cc
  mesh_refinement_smoothing.cc
  mesh_tools.cc
  serial_mesh.cc
  serial_mesh_iterators.cc
  unstructured_mesh.cc
)

add_library(mesh STATIC ${CXX_SRCS})
target_include_directories(mesh PUBLIC ${CMAKE_SOURCE_DIR}/include/mesh)

