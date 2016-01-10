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
**  This file is part of MIToolbox, licensed under the 3-clause BSD license.
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

