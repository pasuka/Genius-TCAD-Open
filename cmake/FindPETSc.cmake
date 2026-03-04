# FindPETSc.cmake
# ---------------
# Finds the PETSc library using the PETSC_DIR and PETSC_ARCH environment
# variables (mirroring the waf build system).
#
# Result variables:
#   PETSc_FOUND          - TRUE if PETSc was found
#   PETSc_INCLUDE_DIRS   - Include directories
#   PETSc_LIBRARIES      - Libraries to link
#
# Imported targets:
#   PETSc::PETSc         - Imported target for PETSc

if(NOT DEFINED ENV{PETSC_DIR})
  message(FATAL_ERROR "PETSC_DIR environment variable is not set. "
    "Please set PETSC_DIR to the root of your PETSc installation.")
endif()

set(_petsc_dir "$ENV{PETSC_DIR}")
set(_petsc_arch "$ENV{PETSC_ARCH}")

# With PETSC_ARCH (typical case)
if(_petsc_arch)
  set(_petsc_arch_dir "${_petsc_dir}/${_petsc_arch}")
else()
  set(_petsc_arch_dir "${_petsc_dir}")
endif()

# Primary include directory (arch-specific generated headers)
find_path(PETSc_ARCH_INCLUDE_DIR
  NAMES petscconf.h
  HINTS "${_petsc_arch_dir}/include"
  NO_DEFAULT_PATH
)

# Common include directory (petsc.h lives here)
find_path(PETSc_COMMON_INCLUDE_DIR
  NAMES petsc.h
  HINTS "${_petsc_dir}/include"
  NO_DEFAULT_PATH
)

# PETSc library
find_library(PETSc_LIBRARY
  NAMES petsc
  HINTS "${_petsc_arch_dir}/lib" "${_petsc_dir}/lib"
  NO_DEFAULT_PATH
)

# Try pkg-config as a fallback if the above didn't find the library
if(NOT PETSc_LIBRARY)
  find_package(PkgConfig QUIET)
  if(PKG_CONFIG_FOUND)
    set(ENV{PKG_CONFIG_PATH} "${_petsc_arch_dir}/lib/pkgconfig:${_petsc_dir}/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
    pkg_check_modules(_petsc_pc QUIET PETSc)
    if(_petsc_pc_FOUND)
      set(PETSc_LIBRARY "${_petsc_pc_LINK_LIBRARIES}")
      if(NOT PETSc_ARCH_INCLUDE_DIR)
        set(PETSc_ARCH_INCLUDE_DIR "${_petsc_pc_INCLUDE_DIRS}")
      endif()
    endif()
  endif()
endif()

# Also try reading petscvariables for additional link flags
set(_petsc_vars_file "${_petsc_arch_dir}/lib/petsc/conf/petscvariables")
if(NOT EXISTS "${_petsc_vars_file}")
  set(_petsc_vars_file "${_petsc_dir}/lib/petsc/conf/petscvariables")
endif()
if(NOT EXISTS "${_petsc_vars_file}")
  set(_petsc_vars_file "${_petsc_arch_dir}/conf/petscvariables")
endif()
if(NOT EXISTS "${_petsc_vars_file}")
  set(_petsc_vars_file "${_petsc_dir}/conf/petscvariables")
endif()

set(PETSc_EXTRA_LIBRARIES "")
if(EXISTS "${_petsc_vars_file}")
  file(STRINGS "${_petsc_vars_file}" _petsc_vars_content)
  foreach(_line ${_petsc_vars_content})
    if(_line MATCHES "^PETSC_WITH_EXTERNAL_LIB\\s*=\\s*(.*)")
      string(STRIP "${CMAKE_MATCH_1}" _ext_libs)
      separate_arguments(_ext_libs_list UNIX_COMMAND "${_ext_libs}")
      list(APPEND PETSc_EXTRA_LIBRARIES ${_ext_libs_list})
    endif()
  endforeach()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PETSc
  REQUIRED_VARS PETSc_LIBRARY PETSc_COMMON_INCLUDE_DIR
  VERSION_VAR PETSc_VERSION
)

if(PETSc_FOUND)
  set(PETSc_INCLUDE_DIRS "")
  if(PETSc_ARCH_INCLUDE_DIR)
    list(APPEND PETSc_INCLUDE_DIRS "${PETSc_ARCH_INCLUDE_DIR}")
  endif()
  list(APPEND PETSc_INCLUDE_DIRS "${PETSc_COMMON_INCLUDE_DIR}")

  set(PETSc_LIBRARIES "${PETSc_LIBRARY}")

  if(NOT TARGET PETSc::PETSc)
    add_library(PETSc::PETSc UNKNOWN IMPORTED)
    set_target_properties(PETSc::PETSc PROPERTIES
      IMPORTED_LOCATION "${PETSc_LIBRARY}"
      INTERFACE_INCLUDE_DIRECTORIES "${PETSc_INCLUDE_DIRS}"
    )
    if(PETSc_EXTRA_LIBRARIES)
      set_target_properties(PETSc::PETSc PROPERTIES
        INTERFACE_LINK_LIBRARIES "${PETSc_EXTRA_LIBRARIES}"
      )
    endif()
  endif()
endif()

mark_as_advanced(PETSc_LIBRARY PETSc_ARCH_INCLUDE_DIR PETSc_COMMON_INCLUDE_DIR)
