
FLEX_TARGET(TifLexer
  tif_lex.l
  ${CMAKE_CURRENT_BINARY_DIR}/tif_lex.yy.c
)
BISON_TARGET(TifParser
  tif_parser.y
  ${CMAKE_CURRENT_BINARY_DIR}/tif_parser.tab.c
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/tif_parser.tab.h
)
ADD_FLEX_BISON_DEPENDENCY(TifLexer TifParser)

set(CXX_SRCS
  ${FLEX_TifLexer_OUTPUTS}
  ${BISON_TifParser_OUTPUTS}
  tif_tool.cc
)

add_library(tif STATIC ${CXX_SRCS})
target_include_directories(tif PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)


