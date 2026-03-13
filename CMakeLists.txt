cmake_minimum_required(VERSION 3.16)
project(Genius VERSION 1.9.0 LANGUAGES C CXX Fortran)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Position-independent code (needed for shared/module libs)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Module path for custom Find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(GNUInstallDirs)
include(CheckIncludeFile)
include(CheckTypeSize)

# ── Required dependencies ────────────────────────────────────────────────────

find_package(MPI REQUIRED)
find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
find_package(PETSc REQUIRED)

# ── Optional dependencies ────────────────────────────────────────────────────

option(GENIUS_ENABLE_VTK  "Enable VTK support"  ON)
option(GENIUS_ENABLE_CGNS "Enable CGNS support" ON)
option(GENIUS_ENABLE_HDF5 "Enable HDF5 support" OFF)
option(GENIUS_ENABLE_SLEPC "Enable SLEPc support" OFF)

if(GENIUS_ENABLE_VTK)
  # Request specific components so that VTK 9+ populates VTK_LIBRARIES with
  # the corresponding imported targets (VTK::IOXML etc.), which in turn expose
  # the correct include directories via their INTERFACE_INCLUDE_DIRECTORIES.
  find_package(VTK QUIET COMPONENTS IOXML CommonDataModel CommonCore)
  if(VTK_FOUND)
    message(STATUS "VTK found: ${VTK_VERSION}")
  else()
    message(STATUS "VTK not found; VTK support disabled")
    set(GENIUS_ENABLE_VTK OFF)
  endif()
endif()

if(GENIUS_ENABLE_CGNS)
  find_library(CGNS_LIBRARY NAMES cgns)
  find_path(CGNS_INCLUDE_DIR NAMES cgnslib.h)
  if(CGNS_LIBRARY AND CGNS_INCLUDE_DIR)
    message(STATUS "CGNS found: ${CGNS_LIBRARY}")
  else()
    message(STATUS "CGNS not found; CGNS support disabled")
    set(GENIUS_ENABLE_CGNS OFF)
  endif()
endif()

if(GENIUS_ENABLE_HDF5)
  find_package(HDF5 QUIET)
  if(NOT HDF5_FOUND)
    set(GENIUS_ENABLE_HDF5 OFF)
  endif()
endif()

if(GENIUS_ENABLE_SLEPC)
  find_library(SLEPC_LIBRARY NAMES slepc)
  find_path(SLEPC_INCLUDE_DIR NAMES slepc.h)
  if(NOT (SLEPC_LIBRARY AND SLEPC_INCLUDE_DIR))
    set(GENIUS_ENABLE_SLEPC OFF)
  endif()
endif()

# ── Version string (via git) ─────────────────────────────────────────────────

find_package(Git QUIET)
set(GENIUS_VERSION_STRING "")
if(GIT_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE _git_hash
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  if(_git_hash)
    set(GENIUS_VERSION_STRING "git-${_git_hash}")
  endif()
endif()
if(NOT GENIUS_VERSION_STRING)
  string(TIMESTAMP GENIUS_VERSION_STRING "%Y%m%d")
endif()
message(STATUS "Genius version string: ${GENIUS_VERSION_STRING}")

# ── config.h generation ──────────────────────────────────────────────────────

# Platform detection (variable names match config.h.in #cmakedefine directives)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(LINUX 1)
  set(DLLHOOK 1)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(WINDOWS 1)
  set(WIN32 1)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  set(DARWIN 1)
endif()

# Type sizes
check_type_size("double"         SIZEOF_DOUBLE)
check_type_size("float"          SIZEOF_FLOAT)
check_type_size("int"            SIZEOF_INT)
check_type_size("long int"       SIZEOF_LONG_INT)
check_type_size("long long int"  SIZEOF_LONG_LONG_INT)
check_type_size("short int"      SIZEOF_SHORT_INT)
check_type_size("void *"         SIZEOF_VOID_P)

# Standard headers
check_include_file("fcntl.h"       HAVE_FCNTL_H)
check_include_file("float.h"       HAVE_FLOAT_H)
check_include_file("fenv.h"        HAVE_FENV_H)
check_include_file("limits.h"      HAVE_LIMITS_H)
check_include_file("stddef.h"      HAVE_STDDEF_H)
check_include_file("stdlib.h"      HAVE_STDLIB_H)
check_include_file("string.h"      HAVE_STRING_H)
check_include_file("stdio.h"       HAVE_STDIO_H)
check_include_file("assert.h"      HAVE_ASSERT_H)
check_include_file("sys/time.h"    HAVE_SYS_TIME_H)
check_include_file("sys/types.h"   HAVE_SYS_TYPES_H)
check_include_file("sys/stat.h"    HAVE_SYS_STAT_H)
check_include_file("memory.h"      HAVE_MEMORY_H)
check_include_file("strings.h"     HAVE_STRINGS_H)
check_include_file("inttypes.h"    HAVE_INTTYPES_H)
check_include_file("stdint.h"      HAVE_STDINT_H)
check_include_file("unistd.h"      HAVE_UNISTD_H)

# C++ feature checks
include(CheckCXXSourceCompiles)
check_cxx_source_compiles(
  "#include <tr1/unordered_map>\nint main(){std::tr1::unordered_map<int,int> m; return 0;}"
  HAVE_TR1_UNORDERED_MAP)
check_cxx_source_compiles(
  "#include <tr1/unordered_set>\nint main(){std::tr1::unordered_set<int> s; return 0;}"
  HAVE_TR1_UNORDERED_SET)
check_cxx_source_compiles(
  "#include <unordered_map>\nint main(){std::unordered_map<int,int> m; return 0;}"
  HAVE_TR1_UNORDERED_MAP_WITH_STD_HEADER)
check_cxx_source_compiles(
  "#include <unordered_set>\nint main(){std::unordered_set<int> s; return 0;}"
  HAVE_TR1_UNORDERED_SET_WITH_STD_HEADER)
check_cxx_source_compiles(
  "#include <limits>\nint main(){double d = std::numeric_limits<double>::max(); return 0;}"
  HAVE_STD_LIMITS)
check_cxx_source_compiles(
  "namespace Foo{} int main(){return 0;}"
  HAVE_NAMESPACES)
check_cxx_source_compiles(
  "#include <sstream>\nint main(){std::ostringstream s; return 0;}"
  HAVE_SSTREAM)

# PETSc/VTK/CGNS feature flags for config.h
set(HAVE_PETSC 1)
set(WITH_PETSCSCALAR_DOUBLE 1)

if(GENIUS_ENABLE_VTK AND VTK_FOUND)
  set(HAVE_VTK 1)
  # Check for vtkConfigure.h
  find_path(_vtk_cfg_dir NAMES vtkConfigure.h HINTS ${VTK_INCLUDE_DIRS})
  if(_vtk_cfg_dir)
    set(HAVE_VTKCONFIGURE_H 1)
  endif()
endif()

if(GENIUS_ENABLE_CGNS AND CGNS_LIBRARY AND CGNS_INCLUDE_DIR)
  set(HAVE_CGNS 1)
  set(HAVE_CGNSLIB_H 1)
endif()

configure_file(
  "${CMAKE_SOURCE_DIR}/cmake/config.h.in"
  "${CMAKE_BINARY_DIR}/include/config.h"
)

# ── Global include directories ───────────────────────────────────────────────

set(INCLUDE_BASE ${CMAKE_SOURCE_DIR}/include)

# These are used by subdirectory targets via target_include_directories,
# but we also set them globally so that the existing per-module CMakeLists
# (which use INCLUDE_DIRECTORIES) continue to work during migration.
include_directories(
  ${CMAKE_BINARY_DIR}/include
  ${INCLUDE_BASE}
  ${INCLUDE_BASE}/base
  ${INCLUDE_BASE}/bc
  ${INCLUDE_BASE}/enums
  ${INCLUDE_BASE}/fe
  ${INCLUDE_BASE}/geom
  ${INCLUDE_BASE}/hook
  ${INCLUDE_BASE}/interpolation
  ${INCLUDE_BASE}/material
  ${INCLUDE_BASE}/math
  ${INCLUDE_BASE}/mesh
  ${INCLUDE_BASE}/meshgen
  ${INCLUDE_BASE}/parser
  ${INCLUDE_BASE}/partition
  ${INCLUDE_BASE}/quadrature
  ${INCLUDE_BASE}/solution
  ${INCLUDE_BASE}/solver
  ${INCLUDE_BASE}/solver/ddm1
  ${INCLUDE_BASE}/solver/ddm1r
  ${INCLUDE_BASE}/solver/ddm2
  ${INCLUDE_BASE}/solver/ddm_ac
  ${INCLUDE_BASE}/solver/dg
  ${INCLUDE_BASE}/solver/doping_analytic
  ${INCLUDE_BASE}/solver/ebm3
  ${INCLUDE_BASE}/solver/emfem2d
  ${INCLUDE_BASE}/solver/hall
  ${INCLUDE_BASE}/solver/hdm
  ${INCLUDE_BASE}/solver/mix1
  ${INCLUDE_BASE}/solver/mixA1
  ${INCLUDE_BASE}/solver/mixA2
  ${INCLUDE_BASE}/solver/mixA3
  ${INCLUDE_BASE}/solver/mole_analytic
  ${INCLUDE_BASE}/solver/poisson
  ${INCLUDE_BASE}/solver/ray_tracing
  ${INCLUDE_BASE}/solver/stress_solver
  ${INCLUDE_BASE}/source
  ${INCLUDE_BASE}/utils
  ${CMAKE_SOURCE_DIR}/src/contrib/ann
  ${CMAKE_SOURCE_DIR}/src/contrib/dfise
  ${CMAKE_SOURCE_DIR}/src/contrib/kdtree
  ${CMAKE_SOURCE_DIR}/src/contrib/expreval
  ${CMAKE_SOURCE_DIR}/src/contrib/triangle
  ${CMAKE_SOURCE_DIR}/src/contrib/mxml
  ${CMAKE_SOURCE_DIR}/src/contrib/trex
  ${CMAKE_SOURCE_DIR}/src/contrib/nn
  ${CMAKE_SOURCE_DIR}/src/contrib/csabathy
  ${CMAKE_SOURCE_DIR}/src/contrib/spice
  ${PETSc_INCLUDE_DIRS}
  ${MPI_CXX_INCLUDE_DIRS}
)

add_subdirectory(src)
