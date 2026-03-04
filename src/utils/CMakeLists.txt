
set(CXX_SRCS
  CogendaHDF5.cc
  dose_rate.cc
  error_vector.cc
  extend_to_3d.cc
  gzstream.cc
  location_maps.cc
  mat_analysis.cc
  monot_cubic_interpolator.cc
  nearest_node_locator.cc
  object_tree.cc
  octree.cc
  point_locator_base.cc
  point_locator_list.cc
  point_locator_tree.cc
  rotate_to_3d.cc
  show_mesh_2d.cc
  statistics.cc
  surface_locator_base.cc
  surface_locator_hub.cc
  surface_locator_list.cc
  surface_locator_sphere.cc
  sync_file.cc
  tree.cc
  tree_node.cc
)

add_library(utils STATIC ${CXX_SRCS})
target_include_directories(utils PUBLIC ${CMAKE_SOURCE_DIR}/include/utils)

