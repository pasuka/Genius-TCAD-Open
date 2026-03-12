
# The flex/bison generated C files (input.yy.c, input.tab.c, pattern.yy.c,
# pattern.tab.c) are pre-generated and committed to the source tree.
# parser.cc and pattern.cc #include them directly inside namespace InputYY /
# PatternYY blocks and must NOT be compiled as separate translation units.

set(CXX_SRCS
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
  ${CMAKE_CURRENT_SOURCE_DIR}
)

