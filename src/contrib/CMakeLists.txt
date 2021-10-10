SET(SUBDIRS
brkpnts
ann
csabathy
dfise
expreval
#kdtree # included as headers
klu
#metis
mxml
nn
#qshep
spice
spline
stanford
tif
tif3d
trex
triangle
)

FOREACH(SUB ${SUBDIRS})
ADD_SUBDIRECTORY(${SUB})
ENDFOREACH(SUB ${SUBDIRS})


