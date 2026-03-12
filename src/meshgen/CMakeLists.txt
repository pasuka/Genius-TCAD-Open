
set(CXX_SRCS
  mesh_generation_cy.cc
  mesh_generation_cy2d.cc
  mesh_generation_cy3d.cc
  mesh_generation_quad4.cc
  mesh_generation_struct.cc
  mesh_generation_tri3.cc
)

add_library(meshgen STATIC ${CXX_SRCS})
target_include_directories(meshgen PUBLIC
  ${CMAKE_SOURCE_DIR}/include/meshgen
  ${CMAKE_SOURCE_DIR}/src/contrib/triangle
)

