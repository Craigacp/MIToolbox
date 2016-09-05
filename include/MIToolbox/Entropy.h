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
**  This file is part of MIToolbox, licensed under the 3-clause BSD license.
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

