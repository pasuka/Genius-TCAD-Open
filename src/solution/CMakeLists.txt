
SET (CXX_SRCS
cgns_io.cc
conductor_region.cc
control.cc
dfise_io.cc
external_circuit.cc
external_circuit_pi.cc
external_circuit_rcl.cc
external_circuit_rct.cc
fvm_cell_data.cc
fvm_node_data.cc
fvm_node_info.cc
gdml_io.cc
gmsh_io.cc
insulator_region.cc
location_io.cc
pml_region.cc
resistance_region.cc
semiconductor_region.cc
simulation_region.cc
simulation_system.cc
solution_define.cc
stanford_io.cc
tif3d_io.cc
#tif_io.cc
unv_io.cc
vacuum_region.cc
variable_define.cc
vtk2_io.cc
vtk_io.cc
)
IF(${HAVE_VTK})
ADD_DEFINITIONS(-DHAVE_VTK)
ENDIF(${HAVE_VTK})
INCLUDE_DIRECTORIES(${MXML_INCLUDE} ${TRIANGLE_INCLUDE} ${EXPREVAL_INCLUDE} ${SPICE_INCLUDE} ${CSABATHY_INCLUDE} ${ANN_INCLUDE} ${TREX_INCLUDE} ${DFISE_INCLUDE} ${STANFORD_INCLUDE} ${TIF3D_INCLUDE} ${TIF_INCLUDE} ${VTK_INCLUDE} ${CGNS_INCLUDE})
ADD_LIBRARY(solution ${CXX_SRCS})

