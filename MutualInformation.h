/*******************************************************************************
** MutualInformation.h
** Part of the mutual information toolbox
**
** Contains functions to calculate the mutual information of 
** two variables X and Y, I(X;Y), to calculate the joint mutual information
** of two variables X & Z on the variable Y, I(XZ;Y), and the conditional
** mutual information I(x;Y|Z)
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

#ifndef __MutualInformation_H
#define __MutualInformation_H

#ifdef __cplusplus
extern "C" {
#endif 

/*******************************************************************************
** calculateMutualInformation returns the log base 2 mutual information between
** dataVector and targetVector, I(X;Y)
**
** length(dataVector) == length(targetVector) == vectorLength otherwise there
** will be a segmentation fault
*******************************************************************************/
double calculateMutualInformation(double *dataVector, double *targetVector, int vectorLength);

/*******************************************************************************
** calculateConditionalMutualInformation returns the log base 2 
** mutual information between dataVector and targetVector, conditioned on 
** conditionVector, I(X;Y|Z)
**
** length(dataVector) == length(targetVector) == length(condtionVector) == vectorLength 
** otherwise it will error with a segmentation fault
*******************************************************************************/
double calculateConditionalMutualInformation(double *dataVector, double *targetVector, double *conditionVector, int vectorLength);

#ifdef __cplusplus
}
#endif

#endif

