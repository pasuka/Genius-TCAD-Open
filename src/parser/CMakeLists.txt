
# Use CMake's FindFLEX / FindBISON macros for proper dependency tracking
FLEX_TARGET(InputLexer
  input.l
  ${CMAKE_CURRENT_BINARY_DIR}/input.yy.c
)
BISON_TARGET(InputParser
  input.y
  ${CMAKE_CURRENT_BINARY_DIR}/input.tab.c
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/input.tab.h
)
ADD_FLEX_BISON_DEPENDENCY(InputLexer InputParser)

FLEX_TARGET(PatternLexer
  pattern.l
  ${CMAKE_CURRENT_BINARY_DIR}/pattern.yy.c
)
BISON_TARGET(PatternParser
  pattern.y
  ${CMAKE_CURRENT_BINARY_DIR}/pattern.tab.c
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/pattern.tab.h
)
ADD_FLEX_BISON_DEPENDENCY(PatternLexer PatternParser)

set(CXX_SRCS
  ${FLEX_InputLexer_OUTPUTS}
  ${BISON_InputParser_OUTPUTS}
  ${FLEX_PatternLexer_OUTPUTS}
  ${BISON_PatternParser_OUTPUTS}
  file_include.cc
  parser_card.cc
  parser.cc
  parser_parameter.cc
  pattern.cc
  pattern_xml.cc
)

add_library(parser STATIC ${CXX_SRCS})
target_include_directories(parser PUBLIC
  ${CMAKE_SOURCE_DIR}/include/parser
  ${CMAKE_CURRENT_BINARY_DIR}
)

