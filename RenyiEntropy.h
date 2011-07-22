/*******************************************************************************
** RenyiEntropy.h
** Part of the mutual information toolbox
**
** Contains functions to calculate the Renyi alpha entropy of a single variable 
** H_\alpha(X), the Renyi joint entropy of two variables H_\alpha(X,Y), and the 
** conditional Renyi entropy H_\alpha(X|Y)
** 
** Author: Adam Pocock
** Created 26/3/2010
**
**  Copyright 2010 Adam Pocock, The University Of Manchester
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

#ifndef __Renyi_Entropy_H
#define __Renyi_Entropy_H

#ifdef __cplusplus
extern "C" {
#endif 

/*******************************************************************************
** calculateRenyiEntropy returns the Renyi entropy in log base 2 of dataVector
** H_{\alpha}(X), for \alpha != 1
**
** length(dataVector) == vectorLength otherwise there
** will be a segmentation fault
*******************************************************************************/
double calculateRenyiEntropy(double alpha, double *dataVector, int vectorLength);

/*******************************************************************************
** calculateJointRenyiEntropy returns the Renyi entropy in log base 2 of the 
** joint variable of firstVector and secondVector H_{\alpha}(XY), 
** for \alpha != 1
**
** length(firstVector) == length(secondVector) == vectorLength otherwise there
** will be a segmentation fault
*******************************************************************************/
double calculateJointRenyiEntropy(double alpha, double *firstVector, double *secondVector, int vectorLength);

/*  This function does not return a valid conditonal entropy as it has no 
**  meaning in Renyi's extension of entropy
double calculateConditionalRenyiEntropy(double alpha, double *dataVector, double *conditionVector, int vectorLength);
*/

#ifdef __cplusplus
}
#endif

#endif

