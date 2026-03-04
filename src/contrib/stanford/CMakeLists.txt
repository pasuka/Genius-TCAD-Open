
set(CXX_SRCS
  medici.cc
  silvaco.cc
  stanford.cc
  suprem.cc
)

add_library(stanford STATIC ${CXX_SRCS})
target_include_directories(stanford PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


