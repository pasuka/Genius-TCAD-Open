
# dlhook.cc is statically linked into the main executable
add_library(hook STATIC dlhook.cc)
target_include_directories(hook PUBLIC ${CMAKE_SOURCE_DIR}/include/hook)

if(GENIUS_ENABLE_VTK AND VTK_FOUND)
  add_definitions(-DHAVE_VTK)
endif()

# Individual hook plugins — built as MODULE libraries (loaded at runtime via dlopen)
set(_hook_srcs
  cv_hook.cc
  data_hook.cc
  ddm_monitor_hook.cc
  eigenvalue_hook.cc
  gnuplot_hook.cc
  ksp_convergence_hook.cc
  lsmonitor_hook.cc
  mob_monitor_hook.cc
  particle_capture_analytic_hook.cc
  particle_capture_data_hook.cc
  particle_capture_g4_hook.cc
  particle_monitor_hook.cc
  probe_hook.cc
  rawfile_hook.cc
  singularvalue_hook.cc
  spice_monitor_hook.cc
  threshold_hook.cc
  tunneling_hook.cc
)

# VTK-dependent hook
if(GENIUS_ENABLE_VTK AND VTK_FOUND)
  list(APPEND _hook_srcs vtk_hook.cc)
endif()

# CGNS-dependent hook
if(GENIUS_ENABLE_CGNS AND CGNS_LIBRARY AND CGNS_INCLUDE_DIR)
  list(APPEND _hook_srcs cgns_hook.cc)
endif()

foreach(_src ${_hook_srcs})
  get_filename_component(_name ${_src} NAME_WE)
  add_library(${_name} MODULE ${_src})
  set_target_properties(${_name} PROPERTIES
    PREFIX ""
    SUFFIX ".so"
  )
  target_include_directories(${_name} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/hook
    ${CMAKE_SOURCE_DIR}/src/contrib/mxml
    ${CMAKE_SOURCE_DIR}/src/contrib/spice
    ${CMAKE_SOURCE_DIR}/src/contrib/kdtree
  )
  if(GENIUS_ENABLE_VTK AND VTK_FOUND)
    target_include_directories(${_name} PRIVATE ${VTK_INCLUDE_DIRS})
    target_link_libraries(${_name} PRIVATE ${VTK_LIBRARIES})
    if(COMMAND vtk_module_autoinit)
      vtk_module_autoinit(TARGETS ${_name} MODULES ${VTK_LIBRARIES})
    endif()
  endif()
  if(GENIUS_ENABLE_CGNS AND CGNS_INCLUDE_DIR)
    target_include_directories(${_name} PRIVATE ${CGNS_INCLUDE_DIR})
    target_link_libraries(${_name} PRIVATE ${CGNS_LIBRARY})
  endif()
  # On Windows/MinGW, DLLs must have all symbol references resolved at link
  # time.  Link each hook plugin against the genius executable import library
  # so that symbols from the core libraries (e.g. Elem vtable entries) are
  # available.  ENABLE_EXPORTS on the genius target causes CMake/MinGW to
  # produce that import library automatically.
  if(WIN32)
    target_link_libraries(${_name} PRIVATE genius)
  endif()
  install(TARGETS ${_name}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/genius
  )
endforeach()

