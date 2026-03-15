
set(CXX_SRCS
  triangle.c
)

add_library(triangle STATIC ${CXX_SRCS})
target_compile_definitions(triangle PUBLIC TRILIBRARY)
target_include_directories(triangle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# Triangle relies on exact floating-point arithmetic that is sensitive to
# compiler optimisations.  Compiling with -O0 prevents the compiler from
# reordering or optimising away the carefully crafted epsilon-computation and
# adaptive-precision predicates, which can otherwise cause silent incorrect
# results or crashes (SIGSEGV) at higher optimisation levels.
target_compile_options(triangle PRIVATE -O0)



