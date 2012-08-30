/*******************************************************************************
** WeightedMutualInformation.h
** Part of the mutual information toolbox
**
** Contains functions to calculate the mutual information of 
** two variables X and Y, I(X;Y), to calculate the joint mutual information
** of two variables X & Z on the variable Y, I(XZ;Y), and the conditional
** mutual information I(x;Y|Z), while using a weight vector to modify
** the calculation.
** 
** Author: Adam Pocock
** Created: 20/6/2011
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

#ifndef __WeightedMutualInformation_H
#define __WeightedMutualInformation_H

#ifdef __cplusplus
extern "C" {
#endif 

/*******************************************************************************
** calculateWeightedMutualInformation returns the log base 2 mutual information 
** between dataVector and targetVector, I_w(X;Y), weighted by weightVector
**
** length(vectors) == vectorLength otherwise it will segmentation fault
*******************************************************************************/
double calculateWeightedMutualInformation(double *dataVector, double *targetVector, double *weightVector, int vectorLength);

/*******************************************************************************
** calculateWeightedConditionalMutualInformation returns the log base 2 
** mutual information between dataVector and targetVector, conditioned on 
** conditionVector, I(X;Y|Z), weighted by weightVector
**
** length(vectors) == vectorLength otherwise it will segmentation fault
*******************************************************************************/
double calculateWeightedConditionalMutualInformation(double *dataVector, double *targetVector, double *conditionVector, double *weightVector, int vectorLength);

#ifdef __cplusplus
}
#endif

#endif

