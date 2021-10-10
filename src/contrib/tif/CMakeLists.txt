
SET (CXX_SRCS
${CMAKE_CURRENT_SOURCE_DIR}/tif_dummy.cc
tif_tool.cc
)

ADD_LIBRARY(tif ${CXX_SRCS})

SET_SOURCE_FILES_PROPERTIES(tif_dummy.cc tif_lex.yy.c tif_parser.tab.h tif_parser.tab.c PROPERTIES GENERATED TRUE)

ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/tif_dummy.cc
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND touch tif_dummy.cc
    DEPENDS tif_lex.yy.c tif_parser.tab.h tif_lex.l tif_parser.y
)
ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/tif_lex.yy.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${FLEX}
    ARGS    -otif_lex.yy.c tif_lex.l
    DEPENDS tif_parser.tab.h tif_lex.l
)

ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/tif_parser.tab.c ${CMAKE_CURRENT_SOURCE_DIR}/tif_parser.tab.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${BISON}
    ARGS -v -d tif_parser.y
    # these must be read from parser.y
    DEPENDS tif_parser.y
)



