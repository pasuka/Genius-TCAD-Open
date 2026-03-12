
FLEX_TARGET(DfiseLexer
  dfise_lex.l
  ${CMAKE_CURRENT_BINARY_DIR}/dfise_lex.yy.c
)
BISON_TARGET(DfiseParser
  dfise_parser.y
  ${CMAKE_CURRENT_BINARY_DIR}/dfise_parser.tab.c
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/dfise_parser.tab.h
)
ADD_FLEX_BISON_DEPENDENCY(DfiseLexer DfiseParser)

# The generated C files are #included directly by dfise.cc inside the
# DFISE namespace, so they must not be compiled as separate translation units.
set_source_files_properties(
  ${FLEX_DfiseLexer_OUTPUTS}
  ${BISON_DfiseParser_OUTPUT_SOURCE}
  PROPERTIES HEADER_FILE_ONLY TRUE
)

set(CXX_SRCS
  ${FLEX_DfiseLexer_OUTPUTS}
  ${BISON_DfiseParser_OUTPUTS}
  dfise.cc
  dfise_dump.cc
  dfise_grid.cc
)

add_library(dfise STATIC ${CXX_SRCS})
target_include_directories(dfise PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

