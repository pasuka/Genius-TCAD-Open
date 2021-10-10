
SET (CXX_SRCS
cgns_hook
cgns_hook.cc
cv_hook.cc
data_hook.cc
ddm_monitor_hook.cc
dlhook.cc
eigenvalue_hook.cc
gnuplot_hook.cc
#gummel_monitor_hook
#injection_hook.cc
ksp_convergence_hook.cc
lsmonitor_hook.cc
mob_monitor_hook.cc
particle_capture_analytic_hook.cc
particle_capture_data_hook.cc
particle_capture_g4_hook.cc
particle_monitor_hook.cc
probe_hook.cc
rawfile_hook.cc
#shell_hook.cc
singularvalue_hook.cc
spice_monitor_hook.cc
threshold_hook.cc
tunneling_hook.cc
vtk_hook.cc
)
IF(${HAVE_VTK})
ADD_DEFINITIONS(-DHAVE_VTK)
ENDIF(${HAVE_VTK})

INCLUDE_DIRECTORIES(${MXML_INCLUDE} ${SPICE_INCLUDE} ${KDTREE_INCLUDE} ${VTK_INCLUDE})
ADD_LIBRARY(hook ${CXX_SRCS})

