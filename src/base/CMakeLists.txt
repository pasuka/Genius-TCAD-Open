
set(CXX_SRCS
  dof_object.cc
  genius_env.cc
  log.cc
  memory_log.cc
  perf_log.cc
)

add_library(base STATIC ${CXX_SRCS})
target_include_directories(base PUBLIC ${CMAKE_SOURCE_DIR}/include/base)
if(WIN32)
  target_link_libraries(base PUBLIC Psapi)
endif()

