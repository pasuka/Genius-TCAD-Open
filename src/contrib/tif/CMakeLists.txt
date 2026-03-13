
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

# The generated lex/parser files are #included by tif_tool.cc inside namespace TIF.
# Mark them as header-only so CMake does not compile them as separate translation units,
# which would cause duplicate-symbol errors and break the namespace encapsulation.
set_source_files_properties(
  ${FLEX_TifLexer_OUTPUTS}
  ${BISON_TifParser_OUTPUTS}
  PROPERTIES HEADER_FILE_ONLY TRUE
)

add_library(tif STATIC tif_tool.cc)
# Still list the generated files as sources so CMake tracks them as dependencies
# and includes them in IDE project files, even though they are not compiled separately.
target_sources(tif PRIVATE ${FLEX_TifLexer_OUTPUTS} ${BISON_TifParser_OUTPUTS})
target_include_directories(tif PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)


