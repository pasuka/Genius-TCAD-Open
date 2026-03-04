
set(CXX_SRCS
  electrical_source.cc
  field_source.cc
  isource.cc
  light_lenses.cc
  light_source.cc
  particle_source.cc
  vsource.cc
  waveform.cc
)

add_library(source STATIC ${CXX_SRCS})
target_include_directories(source PUBLIC ${CMAKE_SOURCE_DIR}/include/source)

