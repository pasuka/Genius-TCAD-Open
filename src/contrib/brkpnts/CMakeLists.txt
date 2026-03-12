
add_executable(brkpnts brkpnts.c)
target_link_libraries(brkpnts m)

# Run brkpnts to generate brkpnts.h in the include directory.
# Using OUTPUT-based add_custom_command so that other targets can declare
# a dependency on the generated header and build ordering is enforced.
add_custom_command(
  OUTPUT ${CMAKE_SOURCE_DIR}/include/brkpnts.h
  COMMAND $<TARGET_FILE:brkpnts>
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/include
  DEPENDS brkpnts
  COMMENT "Generating brkpnts.h"
)

add_custom_target(generate_brkpnts_h ALL
  DEPENDS ${CMAKE_SOURCE_DIR}/include/brkpnts.h
)

