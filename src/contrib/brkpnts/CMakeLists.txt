
add_executable(brkpnts brkpnts.c)
target_link_libraries(brkpnts m)

# Run brkpnts to generate brkpnts.h in the include directory
add_custom_command(
  TARGET brkpnts POST_BUILD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/include
  COMMAND $<TARGET_FILE:brkpnts>
  COMMENT "Generating brkpnts.h"
)

