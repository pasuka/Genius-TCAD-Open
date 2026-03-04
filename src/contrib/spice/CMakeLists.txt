
set(CXX_SRCS
  schur_solver.cc
  spice_ckt.cc
)

add_library(spice STATIC ${CXX_SRCS})
target_include_directories(spice PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


