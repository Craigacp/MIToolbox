/*******************************************************************************
**
**  MIToolbox.h
**  Provides the header files and #defines to ensure compatibility with MATLAB
**  and C/C++. By default it compiles to MATLAB, if COMPILE_C is defined it
**  links to the C memory allocation functions.
**
**  Author: Adam Pocock
**  Created: 17/2/2010
**  Modified: 24/06/2011 - added log base #define
**
**  Copyright 2010/2011 Adam Pocock, The University Of Manchester
**  www.cs.manchester.ac.uk
**
**  This file is part of MIToolbox, licensed under the 3-clause BSD license.
*******************************************************************************/

#ifndef __MIToolbox_H
#define __MIToolbox_H

#include <math.h>
#include <string.h>

#define BASE_TWO 2.0
#define BASE_E M_E

#define LOG_BASE BASE_TWO

#ifdef COMPILE_C
  #define C_IMPLEMENTATION
  #include <stdio.h>
  #include <stdlib.h>
  #define CALLOC_FUNC calloc
  #define FREE_FUNC free
#else
  #define MEX_IMPLEMENTATION
  #include "mex.h"
  #define CALLOC_FUNC mxCalloc
  #define FREE_FUNC mxFree
  #define printf mexPrintf /*for Octave-3.2*/
#endif

#endif

