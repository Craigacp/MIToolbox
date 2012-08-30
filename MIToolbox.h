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
**  This file is part of MIToolbox.
**
**  MIToolbox is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  MIToolbox is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with MIToolbox.  If not, see <http://www.gnu.org/licenses/>.
**
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

