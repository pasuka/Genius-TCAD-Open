
add_executable(brkpnts brkpnts.c)
target_link_libraries(brkpnts m)

# Run brkpnts to generate brkpnts.h in the include directory.
# The executable is invoked with the output file path as an argument so that
# no WORKING_DIRECTORY pointing into the source tree is required.  This avoids
# "Access Denied" failures on Windows when cmake tries to cd into the source
# include directory before running the generator.
add_custom_command(
  OUTPUT ${CMAKE_SOURCE_DIR}/include/brkpnts.h
  COMMAND $<TARGET_FILE:brkpnts> ${CMAKE_SOURCE_DIR}/include/brkpnts.h
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS brkpnts
  COMMENT "Generating brkpnts.h"
)

add_custom_target(generate_brkpnts_h ALL
  DEPENDS ${CMAKE_SOURCE_DIR}/include/brkpnts.h
)

