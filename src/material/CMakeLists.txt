SET (CXX_SRCS
adolc_init.cc
material.cc
material_define.cc
physical_unit.cc
PMI.cc
)

SET (SUBDIRS
	4H-SiC
Air
Al
AlGaAs
Cu
Elec
GaAs
Ge
Nitride
NPolySi
PolySi
PPolySi
Si
SiC4H
SiO2
W
)

FOREACH(SUB ${SUBDIRS})
file(GLOB MSRCS ${SUB}/*.cc)
ADD_LIBRARY(${SUB} SHARED  adolc_init.cc ${MSRCS})
ADD_CUSTOM_COMMAND(TARGET ${SUB} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${SUB}> ${CMAKE_SOURCE_DIR}/lib
)
ENDFOREACH(SUB ${SUBDIRS})


ADD_LIBRARY(material ${CXX_SRCS})

