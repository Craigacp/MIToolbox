/*******************************************************************************
** Entropy.h
** Part of the mutual information toolbox
**
** Contains functions to calculate the entropy of a single variable H(X), 
** the joint entropy of two variables H(X,Y), and the conditional entropy
** H(X|Y)
** 
** Author: Adam Pocock
** Created 19/2/2010
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

#ifndef __Entropy_H
#define __Entropy_H

#ifdef __cplusplus
extern "C" {
#endif 

/*******************************************************************************
** calculateEntropy returns the entropy in log base 2 of dataVector
** H(X)
**
** length(dataVector) == vectorLength otherwise there
** will be a segmentation fault
*******************************************************************************/
double calculateEntropy(double *dataVector, int vectorLength);

/*******************************************************************************
** calculateJointEntropy returns the entropy in log base 2 of the joint 
** variable of firstVector and secondVector H(XY)
**
** length(firstVector) == length(secondVector) == vectorLength otherwise there
** will be a segmentation fault
*******************************************************************************/
double calculateJointEntropy(double *firstVector, double *secondVector, int vectorLength);

/*******************************************************************************
** calculateConditionalEntropy returns the entropy in log base 2 of dataVector
** conditioned on conditionVector, H(X|Y)
**
** length(dataVector) == length(conditionVector) == vectorLength otherwise there
** will be a segmentation fault
*******************************************************************************/
double calculateConditionalEntropy(double *dataVector, double *conditionVector, int vectorLength);

#ifdef __cplusplus
}
#endif

#endif

