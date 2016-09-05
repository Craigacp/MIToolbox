/*******************************************************************************
** RenyiMutualInformation.h
** Part of the mutual information toolbox
**
** Contains functions to calculate the Renyi mutual information of 
** two variables X and Y, I_\alpha(X;Y), using the Renyi alpha divergence and 
** the joint entropy difference
** 
** Author: Adam Pocock
** Created 26/3/2010
**
**  Copyright 2010 Adam Pocock, The University Of Manchester
**  www.cs.manchester.ac.uk
**
**  This file is part of MIToolbox, licensed under the 3-clause BSD license.
*******************************************************************************/

#ifndef __Renyi_MutualInformation_H
#define __Renyi_MutualInformation_H

#ifdef __cplusplus
extern "C" {
#endif 

/*******************************************************************************
** calculateRenyiMIDivergence returns the log base 2 Renyi mutual information
** between dataVector and targetVector, I_{\alpha}(X;Y), for \alpha != 1
** This uses Renyi's generalised alpha divergence as the difference measure
** instead of the KL-divergence as in Shannon's Mutual Information
**
** length(dataVector) == length(targetVector) == vectorLength otherwise there
** will be a segmentation fault
*******************************************************************************/
double calculateRenyiMIDivergence(double alpha, double *dataVector, double *targetVector, int vectorLength);

/****************************************************************************** 
** This function returns a different value to the alpha divergence mutual 
** information, and thus is not a correct mutual information.
******************************************************************************/
double calculateRenyiMIJoint(double alpha, double *dataVector, double *targetVector, int vectorLength);

#ifdef __cplusplus
}
#endif 

#endif

