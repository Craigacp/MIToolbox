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

/* This function returns a different value to the alpha divergence mutual 
** information, and thus is not a correct mutual information
double calculateRenyiMIJoint(double alpha, double *dataVector, double *targetVector, int vectorLength);
*/

#ifdef __cplusplus
}
#endif 

#endif

