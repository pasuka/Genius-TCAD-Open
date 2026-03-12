/*--------------------------------------------------------------------------

 PROJECT:  SIMULATION GENERATION FRAMEWORK (SIMGEN)

 SUBSYSTEM:  brkpnts.exe
 FILE:	      brkpnts.c
 AUTHOR:     Kevin M. Kramer

 DESCRIPTION:

 This module contains the range limit constant for the Bernoulli, Aux1 and
 Aux2 functions as well as their derivatives.	For more information consult
 "Analysis and Simulation of Electronic Devices" by Siegfried Selberherr
 pages 158 and 159.

--------------------------------------------------------------------------*/


#ifndef __brkpnts_h
#define __brkpnts_h

#define BP0_BERN    -3.742994775023696e+01
#define BP1_BERN    -1.983224379137254e-02
#define BP2_BERN    2.177550998053050e-02
#define BP3_BERN    3.742994775023696e+01
#define BP4_BERN    2.357211588756850e+02
#define BP0_DBERN   -4.117169706049845e+01
#define BP1_DBERN   -3.742994775023696e+01
#define BP2_DBERN   -1.557983451962405e-02
#define BP3_DBERN   8.928625524999144e-03
#define BP4_DBERN   3.742994775023696e+01
#define BP5_DBERN   2.357168893611592e+02
#define BP0_AUX1    -7.942731148743141e-03
#define BP1_AUX1    7.942731148743141e-03
#define BP0_DAUX1   -5.080331665216862e-03
#define BP1_DAUX1   5.080331665216862e-03
#define BP2_DAUX1   -1.919077925061930e+02
#define BP3_DAUX1   1.919077925061930e+02
#define BP4_DAUX1   -2.364129978894499e+02
#define BP5_DAUX1   2.364129978894499e+02
#define BP0_AUX2    -3.673680056967704e+01
#define BP1_AUX2    3.680808162809191e+01
#define BP2_AUX2    2.302585092994049e+02
#define BP0_DAUX2   -2.302585092994049e+02
#define BP1_DAUX2   -3.673680056967704e+01
#define BP2_DAUX2   3.680808162809191e+01
#define BP3_DAUX2   2.302585092994049e+02
#define BP0_MISC    7.097827128183643e+02

#endif
