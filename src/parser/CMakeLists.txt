
SET (CXX_SRCS
${CMAKE_CURRENT_SOURCE_DIR}/input_dummy.cc
${CMAKE_CURRENT_SOURCE_DIR}/pattern_dummy.cc
file_include.cc
parser_card.cc
parser.cc
parser_parameter.cc
pattern.cc
pattern_xml.cc
)

INCLUDE_DIRECTORIES(${MXML_INCLUDE})
ADD_LIBRARY(parser ${CXX_SRCS})

SET_SOURCE_FILES_PROPERTIES(input_dummy.cc input.yy.c input.tab.h input.tab.c PROPERTIES GENERATED TRUE)
SET_SOURCE_FILES_PROPERTIES(pattern_dummy.cc pattern.yy.c pattern.tab.h pattern.tab.c PROPERTIES GENERATED TRUE)

ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/input_dummy.cc
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND touch input_dummy.cc
    DEPENDS input.yy.c input.tab.h input.l input.y
)
ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/input.yy.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${FLEX}
    ARGS    -oinput.yy.c input.l
    DEPENDS input.tab.h input.l
)

ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/input.tab.c ${CMAKE_CURRENT_SOURCE_DIR}/input.tab.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${BISON}
    ARGS -v -d input.y
    # these must be read from parser.y
    DEPENDS input.y
)


ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/pattern_dummy.cc
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND touch pattern_dummy.cc
    DEPENDS pattern.yy.c pattern.tab.h pattern.l pattern.y
)
ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/pattern.yy.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${FLEX}
    ARGS    -opattern.yy.c pattern.l
    DEPENDS pattern.tab.h pattern.l
)

ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/pattern.tab.c ${CMAKE_CURRENT_SOURCE_DIR}/pattern.tab.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${BISON}
    ARGS -v -d pattern.y
    # these must be read from parser.y
    DEPENDS pattern.y
)



