
set(CXX_SRCS
  expr.cc
  expr_datalist.cc
  expr_except.cc
  expr_func.cc
  expr_funclist.cc
  expr_node.cc
  expr_parser.cc
  expr_vallist.cc
)

add_library(expreval STATIC ${CXX_SRCS})
target_include_directories(expreval PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


