
SET (CXX_SRCS
${CMAKE_CURRENT_SOURCE_DIR}/dfise_dummy.cc
dfise.cc
dfise_dump.cc
dfise_grid.cc
)

ADD_LIBRARY(dfise ${CXX_SRCS})

SET_SOURCE_FILES_PROPERTIES(dfise_dummy.cc dfise_lex.yy.c dfise_parser.tab.h dfise_parser.tab.c PROPERTIES GENERATED TRUE)

ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/dfise_dummy.cc
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND touch dfise_dummy.cc
    DEPENDS dfise_lex.yy.c dfise_parser.tab.h dfise_lex.l dfise_parser.y
)
ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/dfise_lex.yy.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${FLEX}
    ARGS    -odfise_lex.yy.c dfise_lex.l
    DEPENDS dfise_parser.tab.h dfise_lex.l
)

ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/dfise_parser.tab.c ${CMAKE_CURRENT_SOURCE_DIR}/dfise_parser.tab.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${BISON}
    ARGS -v -d dfise_parser.y
    # these must be read from parser.y
    DEPENDS dfise_parser.y
)



