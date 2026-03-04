
set(CXX_SRCS
  mxml-attr.c
  mxmldoc.c
  mxml-entity.c
  mxml-file.c
  mxml-index.c
  mxml-node.c
  mxml-private.c
  mxml-search.c
  mxml-set.c
  mxml-string.c
  MXMLUtil.cpp
)

add_library(mxml STATIC ${CXX_SRCS})
target_include_directories(mxml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


